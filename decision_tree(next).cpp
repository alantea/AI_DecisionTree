#include "decison_tree.h"

attr decision_tree::entropy(int sequence[25][2])
{attr min_attr = { 0 , 5 , 0};
 double min_number = MAX_SAMPLE;
 int node[MAX_SAMPLE][2];      //the node : 1 , 2.
 for(int i=0;i<MAX_SAMPLE;i++) //node(initialize)
    {node[i][0]=-1;
     node[i][1]=-1;
    }
 //Pick the parent nodes
 int i,j,number;               //number  : the number through the nodes of the path
 int answer1=0,answer2=0;      //the index of (node:1 , 2.)
 int counter=0;                //counter : the number of the nodes
 for(i=0;i<MAX_SAMPLE;i++)
    {number=0;                 //number(initialize)
     if(sequence[0][0]==25)    //When no path, pick all of the nodes.
       {if(attribute[i][24] == 1)//When the answer =1, record (node:1).
          {node[answer1][0]=i;
           answer1++;
          }
        else                     //When the answer =2, record (node:2).
          {node[answer2][1]=i;
           answer2++;
          }
        counter++;
        continue;
       }
                               //  When having path, check whether the node is in the path or not.
     for(j=0;sequence[j][0] != 25;j++)
        {if(attribute      [i]        [sequence[j][0]] == sequence[j][1])
                     /* in Node i*/ /* in attr(path) */  /* the branch */
           {number++;          //number  : the number through the nodes of the path ++;
           }
        }
     if(number==j)             //When the path number = the number of satisfying the conditions
       {if(attribute[i][24] == 1)//When the answer =1, record (node:1).
          {node[answer1][0]=i;
           answer1++;
          }
        else                     //When the answer =2, record (node:2).
          {node[answer2][1]=i;
           answer2++;
          }
        counter++;
       }
    }
     if(node[0][0]== -1 && node[0][1] == -1)      //When none of nodes is in the path,return none.
       {min_attr.name = -3;
        return min_attr;
       }
     else if(node[0][0]== -1 && node[0][1] != -1) //When the nodes (answer = 2) is in the path,return -2.
       {min_attr.name = -2;
        return min_attr;
       }
     else if(node[0][0]!= -1 && node[0][1] == -1) //When the nodes (answer = 1) is in the path,return -1.
       {min_attr.name = -1;
        return min_attr;
       }
 //compute the entropy.
 for(i=0;i<25;i++)               //Check all attributes.
    {for(j=0;       sequence[j][0] != i    &&  sequence[j][0] !=25 ;j++);
             //the attr in path, filter it.  //the attr not in path
     if(sequence[j][0] == i || i==1 || i==3 || i==9) //When the range isn't 0~5, filter it.
       {continue;
       }
     int subnode_number[6][2]={{0}};         //the number of the sub-node : 1 , 2.
     double info_content=0;                  //the entropy (information content)
     for(j=0; node[j][0]!=-1 ;j++)           //get the number of the sub-node : 1.
        {subnode_number[attribute      [node[j][0]]                 [i]     ][0]++;
                                 /*the nodes in sub-tree*//* the next attr */
                        /*        the value(branch) in the  attribute      */
         /*                  (the number of the sub-node : 1) ++                    */
        }
     for(j=0; node[j][1]!=-1 ;j++)
        {subnode_number[attribute      [node[j][1]]                [i]     ][1]++;
                                 /*the nodes in sub-tree*//* the next attr */
                        /*        the value(branch) in the  attribute      */
         /*                  (the number of the sub-node : 2) ++                    */
        }
     //compute the entropy.
     double prob0 = (double)subnode_number[j][0]/counter;
     double prob1 = (double)subnode_number[j][1]/counter;
     for(j=0;j<6;j++)
        {info_content=-prob0 * log(prob0)/log(2.0)
                      -prob1 * log(prob1)/log(2.0)
                      + info_content;
        }
     if(min_number > info_content) // check whether the entropy of the attribute is  min(best) or not.
       {min_number = info_content;
        min_attr.name = i;
       }
    }
 //find the min & max in the attribute.
 for(int i=0;i<MAX_SAMPLE;i++)
    {if(attribute[i][min_attr.name] > min_attr.max_value)
       {min_attr.max_value = attribute[i][min_attr.name];
       }
     else if(attribute[i][min_attr.name] < min_attr.min_value)
       {min_attr.min_value = attribute[i][min_attr.name];
       }
    }
 return min_attr;//return the (best) attribute.
}

decision_tree::decision_tree()
{int i,j;
 for(i=0 ; i < 25 ; i++)
    {for(j=0 ; j < 6 ; j++)
        {choseroad[i][j] = -3 ;
        }
    }
}

void decision_tree::read_file()
{fstream train_file;
 train_file.open( "TraData700.csv" , fstream::in );
 int i,j;
 char delimiter;
 for(i=0 ; i < MAX_SAMPLE ; i++)
    {for(j=0 ; j < 25 ; j++)
        {train_file >> attribute[i][j];
         if(j!=24)
           {train_file >> delimiter;
           }
        }
    }
 train_file.close();
}

void decision_tree::gain_tree(int sequence[25][2],int root,int branch)
{int path_length = 0;
 for(path_length = 0;sequence[path_length][0]!=25;path_length++);
 if(path_length == 24)
   {return;
   }
 attr next_attr = {0,0,0} ;
 next_attr = entropy(sequence);//compute the entropies to choose the attribute.
 choseroad[root][branch] = next_attr.name;
 sequence[path_length][0]= next_attr.name;
 if(next_attr.name < 0)
   {return;
   }
 for(int i = next_attr.min_value ; i <= next_attr.max_value ; i++)
    {sequence[path_length][1] = i;
     gain_tree(sequence,next_attr.name,i);
     sequence[path_length][1] = 25;
    }
}

void decision_tree::save_tree()
{fstream tree;
 tree.open( "tree.csv" , fstream::out | fstream::trunc);
 int i,j;
 for(i=0 ; i < 25 ; i++)
    {for(j=0 ; j < 6 ; j++)
        {tree << choseroad[i][j] ;
         if( j < 5 )
           {tree << ',' ;
           }
        }
     tree << '\n' ;
    }
 tree.close();
}
