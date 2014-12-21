#include "decision_tree.h"

using namespace std;

attr::attr()
{
	name = min_value = max_value = 0;
}

attr::attr(int a, int b ,int c)
{
	name = a;
	min_value = b;
	max_value = c;
}

decision_tree::decision_tree()
{
	initial();

	main_menu();
}

void decision_tree::initial()
{
    for(int i = 0 ; i < 25 ; i++)
    {
        for(int j = 0 ; j < 6 ; j++)
        {
            choseroad[i][j] = -3 ;
        }
    }
    MAX_SAMPLE = 0;
    complete_tree = false;
}

void decision_tree::main_menu()
{
	string str_buf;
    while(1)
    {
		cout << "----------------------" << endl;
        cout << "	MENU" << endl;
        cout << "----------------------" << endl;
        cout << "1. Testing mode" << endl;
        cout << "2. Training mode" << endl;	//The first part : produce the decision tree.
        cout << endl;
        cout << "Enter option : " << ends;

		getline(cin, str_buf);
        int option = atoi(str_buf.c_str());
        cin.clear();
	//	cin.sync();			// can't not use in un*x system

        switch(option)
        {
        case 1:
            //testingMain();		//Entrance of the testing mode
            break;
        case 2:
            trainingMain();		//Entrance of the training mode
            break;
        default:
            cout << "This is an invalid option." << endl;
            break;
        }//end switch

        cout << "Do you want to continue [y/N]? " << ends;

		getline(cin, str_buf);
		char cont = str_buf[0];

        if(cont != 'y' && cont != 'Y')
		{
            break;
		}
    }//end while

}

decision_tree::~decision_tree()
{
}

void decision_tree::trainingMain()
/************************************************************************
	Entrance of the training mode;
------------------------------------------------------------------------
	input : none;
	return : none;
************************************************************************/
{
	string str_buf;
    while(1)
    {
        /** Build the tree, then output the tree.csv **/
        
		/*  path : record the path
		 *	parm1 : attribute
		 *  parm2 : 0 -> attribute name
		 *			1 -> record the number which is matched will go
		 */
        int path[25][2];

        for(int i=0; i<25; i++)
        {
            path[i][0]=25;
            path[i][1]=25;
        }

        read_file();

        gain_tree(path);
        save_tree();

		cout << "End Training." << endl;
        cout << "Do you want to continue training [y/N]? " << ends;

		getline(cin, str_buf);
        char cont = str_buf[0];

        if(cont != 'y' && cont != 'Y'){
			cout << "Return to MENU ..."<<endl;
			usleep(500000);
			break;
        }

    }//end while
    return;
}//end trainingMain()

void decision_tree::read_file()
{
	string input_file = "TraData700.csv";
    fstream train_file;
	train_file.open( input_file.c_str() , fstream::in );

	string input_buf;
	vector<int> input_num;

	int tmp;

	if( !train_file.is_open() )
	{
		cout << "Can't open the training file " << input_file << endl;
		exit(-1);
	}

	for(int i=0; getline(train_file,input_buf); i++)
	{
		input_num.clear();
		for(size_t j=0; j < input_buf.length() ; j++ )
		{
			if( input_buf[j] == ',' )
			{
				input_buf[j] = ' ';
			}
		}
		stringstream ss(input_buf);
		for(int j=0; ss >> tmp ; j++ )
		{
			input_num.push_back(tmp);
		}
		attribute.push_back(input_num);
		MAX_SAMPLE = i+1;
	}

    train_file.close();
}

void decision_tree::gain_tree(int path[25][2],int root,int branch)
{
	// count attributes have gone
	int path_length = 0;
	
	// check all attribute have been gone
	for(path_length = 0;path[path_length][0]!=25;path_length++);
	
	// pass attribute 1 , 3 , 9
	if(path_length == 24 - 3)
	{
		complete_tree = true;
		return;
	}

	
	attr next_attr;
	next_attr = entropy(path);//compute the entropies to choose the attribute
	
	/* When first time in gain tree, it will record the first attribute to go
	 * Ex: choseroad[24][0] = 3 means first the decision tree will look the attribute 3 in the first
	 */
	choseroad[root][branch] = next_attr.name;
	
	// if the maximum informaction conent = 0 , it doesn't need to know the subtree
	if(next_attr.name < 0)
	{
		return;
	}
	for(int i = next_attr.min_value ; i <= next_attr.max_value ; i++)
	{
		path[path_length][0] = next_attr.name;
		path[path_length][1] = i;
		gain_tree(path,next_attr.name,i);
		path[path_length][0] = 25;
		path[path_length][1] = 25;
		
		if( complete_tree )
		{
			return;
		}
	}
}

void decision_tree::save_tree()
{
    fstream tree;
    tree.open( "tree.csv" , fstream::out | fstream::trunc);
    int i,j;

    for(i=0 ; i < 25 ; i++)
    {
        for(j=0 ; j < 6 ; j++)
        {
            tree << choseroad[i][j] ;
            if( j < 5 )
            {
                tree << ',' ;
            }
        }
        tree << endl ;
    }
    tree.close();
}

attr decision_tree::entropy(int path[25][2])
{
	attr min_attr(0 , INT_MAX , 0);
	
	// record the maximum entropy
	double min_number = DBL_MAX;

	/* node : record the subtree's node
	 * parm1 : sample node
	 * parm2 : 0 -> answer is '1'
	 *		   1 -> answer is '2' */
	int **node = NULL;  

	// dynamic allocate 'node' memory and initialize value
	node = new int* [MAX_SAMPLE];
	for( int i = 0 ; i < MAX_SAMPLE ; i++ )
	{
		node[i] = new int [2];
		node[i][0]=-1;
		node[i][1]=-1;
	}
	
	//Pick the parent nodes
	int i,j;
	int number;					  //number  : the number through the nodes of the path
	int answer1=0,answer2=0;      //the index of (node:1 , 2.)
	int counter=0;                //counter : the number of the nodes
	
	for(i=0;i<MAX_SAMPLE;i++)
	{
		number=0;						//number(initialize)
		if(path[0][0]==25)				//When no path, pick all of the nodes.
		{
			if(attribute[i][24] == 1)	//When the answer =1, record (node:1).
			{
				node[answer1][0]=i;
				answer1++;
			}
			else						//When the answer =2, record (node:2).
			{
				node[answer2][1]=i;
				answer2++;
			}
			counter++;
			continue;
		}
		//  When having path, check whether the node is in the path or not.
		for(j=0;j<24 && path[j][0]!=25 ;j++)
		{
			if(attribute      [i]        [path[j][0]] == path[j][1])
						/* in Node i*/	/* in attr(path) */  /* the branch */
			{
				number++;          //number  : the number through the nodes of the path ++;
			}
		}
		if(number==j)             //When the path number = the number of satisfying the conditions
		{
			if(attribute[i][24] == 1)//When the answer =1, record (node:1).
			{
				node[answer1][0]=i;
				answer1++;
			}
			else                     //When the answer =2, record (node:2).
			{
				node[answer2][1]=i;
				answer2++;
			}
			counter++;
		}
	}
	if(node[0][0]== -1 && node[0][1] == -1)      //When none of nodes is in the path,return none.
	{
		min_attr.name = -3;
		return min_attr;
	}
	else if(node[0][0]== -1 && node[0][1] != -1) //When the nodes (answer = 2) is in the path,return -2.
	{
		min_attr.name = -2;
		return min_attr;
	}
	else if(node[0][0]!= -1 && node[0][1] == -1) //When the nodes (answer = 1) is in the path,return -1.
	{
		min_attr.name = -1;
		return min_attr;
	}

	//compute the entropy and get the minimum information content
	for(i=0;i<24;i++)               //Check all attributes.
	{
		for(j=0;j<24 &&    path[j][0] != i    &&  path[j][0] !=25 ;j++);
					 //the attr in path, filter it.  //the attr not in path
		if(path[j][0] == i || i==1 || i==3 || i==9) //When the range isn't 0~5, filter it.
		{
			continue;
		}
		int subnode_number[6][2]={{0}};					//the number of the sub-node : 1 , 2.
		double info_content=0;							//the entropy (information content)
		for(j=0; j<answer1 && node[j][0]!=-1 ;j++)      //get the number of the sub-node : 1.
		{	
			subnode_number[attribute      [node[j][0]]                 [i]     ][0]++;
			/*the nodes in sub-tree*//* the next attr */
			/*        the value(branch) in the  attribute				*/
			/*                  (the number of the sub-node : 1) ++                   */
		}
		for(j=0; j<answer2 && node[j][1]!=-1 ;j++)
		{
			subnode_number[attribute      [node[j][1]]                 [i]     ][1]++;
			/*the nodes in sub-tree*//* the next attr */
			/*        the value(branch) in the  attribute      */
			/*                  (the number of the sub-node : 2) ++                    */
		}
		//compute the entropy.
		double prob0 , prob1;
		for(j=0;j<6;j++)
		{
			prob0 = (double)subnode_number[j][0]/counter;
			prob1 = (double)subnode_number[j][1]/counter;
			if( prob0 != 0 )
			{
				info_content += - prob0 * log(prob0) / log(2.0);
			}
			if( prob1 != 0 )
			{
				info_content += - prob1 * log(prob1) / log(2.0);
			}
		}
		if(min_number > info_content) // check whether the entropy of the attribute is  min(best) or not.
		{
			min_number = info_content;
			min_attr.name = i;
		}
	}
	//find the min & max in the attribute.
	for(int i=0;i<MAX_SAMPLE;i++)
	{
		if(attribute[i][min_attr.name] > min_attr.max_value)
		{
			min_attr.max_value = attribute[i][min_attr.name];
		}
		else if(attribute[i][min_attr.name] < min_attr.min_value)
		{
			min_attr.min_value = attribute[i][min_attr.name];
		}
	}

	for( int i = 0 ; i < MAX_SAMPLE ; i++ )
	{
		delete [] node[i];
	}
	delete [] node;
	return min_attr;//return the (best) attribute.
}
