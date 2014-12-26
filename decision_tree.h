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
	private:
		void initial_child(tree &now);
		void save_node(std::fstream &out, tree &now);
		void read_node(std::fstream &fin, tree &now);
	public:
		int value;
		std::map<int , tree> child;

		void initial();
		void save(std::string output_file);
		void read(std::string input_file);
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
		std::vector<std::vector<int> > attribute;	// training data

		int MAX_SAMPLE;								// count the total sample
        int choseroad[25][6];						// decision tree's path

        void initial();
        void main_menu();

		// Testing mode
        void testing_main();						//Entrance of the testing mode
        void gain_tree(int path[25][2] ,tree &parent ,int root = 24,int branch=0 );
		attr entropy(int path[25][2]);
		
		// Training mode
		void training_main();						// Entrance of the training mode
		void search_tree();
		
		// both two mode
		void read_file(std::string input_file);
		
	public:
        decision_tree();
        ~decision_tree();

};

#endif // DECISON_TREE_H_INCLUDED
