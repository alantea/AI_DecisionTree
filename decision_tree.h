#ifndef DECISON_TREE_H_INCLUDED
#define DECISON_TREE_H_INCLUDED

// C library
#include <cstdlib>
#include <cmath>
#include <unistd.h>	 //for usleep() only

// C++ library
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

class decision_tree
{
	private:
        void initial();

        void main_menu();
		void trainingMain();	// Entrance of the training mode
		int entropy(int sequence[25][2]);

		int MAX_SAMPLE;	// count the total sample
//      int attribute[MAX_SAMPLE][25];
		std::vector<std::vector<int> > attribute;
        int choseroad[25][6];
	public:
        decision_tree();
        ~decision_tree();

		void read_file();
 //       void gain_tree(bool invaild[MAX_SAMPLE],int sequence[25][2],int root=24);
        void gain_tree(bool *invaild,int sequence[25][2],int root=24);
        void save_tree();
};

#endif // DECISON_TREE_H_INCLUDED
