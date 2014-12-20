#include "decison_tree.h"

int decision_tree::entropy(int sequence[25][2])
{int min_attr = 0;
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
        {if(attribute      [i]        [sequence[j][0]] == sequence[j][1] || sequence[j][1]==25)
                     /* in Node i*/ /* in attr(path) */  /* the branch */   /* the last attr */
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
        min_attr   = i;
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
        {train_file >> attribute[i][j] >> delimiter ;
        }
    }
 train_file.close();
}

void decision_tree::gain_tree(bool invaild[MAX_SAMPLE],int sequence[25][2],int root)
{int vaild_number = 0;
 for(vaild_number=0;vaild_number < MAX_SAMPLE && invaild[vaild_number] == 0;vaild_number++);
 if(vaild_number == MAX_SAMPLE)  //Test whether it goes through all nodes.
   {return;
   }
 else
   {int next_attr = 0 ;
    next_attr = entropy(sequence);//compute the entropies to choose the attribute.
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
