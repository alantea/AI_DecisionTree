#ifndef DECISON_TREE_H_INCLUDED
#define DECISON_TREE_H_INCLUDED

// C library
#include <cmath>

// C++ library
#include <fstream>

// define value
#define MAX_SAMPLE 700

using namespace std;

class decision_tree
{
	private:
		int entropy(int sequence[25][2]);
        int attribute[MAX_SAMPLE][25];
        int choseroad[25][6];
	public:
        decision_tree();
		void read_file();
        void gain_tree(bool invaild[MAX_SAMPLE],int sequence[25][2],int root=24);
        void save_tree();
};

#endif // DECISON_TREE_H_INCLUDED
