#ifndef DECISON_TREE_H_INCLUDED
#define DECISON_TREE_H_INCLUDED

// C library
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <climits>
#include <unistd.h>	 //for usleep() only

// C++ library
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

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
        void initial();

        void main_menu();
        void testingMain();							//Entrance of the testing mode
		void trainingMain();						// Entrance of the training mode
		attr entropy(int path[25][2]);				

		int MAX_SAMPLE;								// count the total sample
		std::vector<std::vector<int> > attribute;	// training data
        int choseroad[25][6];						// decision tree's path
		bool complete_tree;
	public:
        decision_tree();
        ~decision_tree();

		void read_file();
        void gain_tree(int path[25][2],int root=24,int branch=0);
        void save_tree();
};

#endif // DECISON_TREE_H_INCLUDED
