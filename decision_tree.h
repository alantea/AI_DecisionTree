#ifndef DECISON_TREE_H_INCLUDED
#define DECISON_TREE_H_INCLUDED

// C library
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <climits>
#include <ctime>
#include <unistd.h>	 //for usleep() only

// C++ library
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

class tree
{
public:
	int value;
	std::map<int , tree> child;
};

class attr
{
	public:
		attr();
		attr( int , int , int );
		int name;		// attribute name
		int min_value;	// training data minimum value in column "name"
		int max_value;	// training data maximum value in column "name"
};

class decision_tree
{
	private:
		tree dctree;

        void initial();

        void main_menu();
        void testing_main();						//Entrance of the testing mode
		void training_main();						// Entrance of the training mode
		attr entropy(int path[25][2]);

		int MAX_SAMPLE;								// count the total sample
		std::vector<std::vector<int> > attribute;	// training data
        int choseroad[25][6];						// decision tree's path
		bool complete_tree;

		void save_node(std::fstream &out, tree now);
		void read_node(std::fstream &in, tree now);
	public:
        decision_tree();
        ~decision_tree();

		void read_file(std::string input_file);
        void gain_tree(int path[25][2] ,tree &parent ,int root = 24,int branch=0 );
        void save_tree(std::string output_file);
		
		void reset_data();		
		void read_tree(std::string input_file);
		void search_tree();
};

#endif // DECISON_TREE_H_INCLUDED
