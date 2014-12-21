#include <fstream>
#include <math.h>
#define MAX_SAMPLE 700

using namespace std;

struct attr
{int name;
 int min_value;
 int max_value;
};

#ifndef DECISON_TREE_H_INCLUDED
#define DECISON_TREE_H_INCLUDED

class decision_tree
{private: attr entropy(int sequence[25][2]);
           int attribute[MAX_SAMPLE][25];
           int choseroad[25][6];
  public: void read_file();
          void gain_tree(int sequence[25][2],int root=24,int branch=0);
          void save_tree();
           decision_tree();
};

#endif // DECISON_TREE_H_INCLUDED
