#ifndef DECISON_TREE_H_INCLUDED
#define DECISON_TREE_H_INCLUDED

// C library
#include <cstdlib>
#include <cmath>
#include <unistd.h>

// C++ library
#include <fstream>
#include <iostream>
#include <string>

// define value
int const MAX_SAMPLE = 700;

class decision_tree
{
	private:
        void initial();
        
        void main_menu();
		void trainingMain();	//Entrance of the training mode
	
		int entropy(int sequence[25][2]);
        int attribute[MAX_SAMPLE][25];
        int choseroad[25][6];
	public:
        decision_tree();
        ~decision_tree();

		void read_file();
        void gain_tree(bool invaild[MAX_SAMPLE],int sequence[25][2],int root=24);
        void save_tree();
};

#endif // DECISON_TREE_H_INCLUDED
