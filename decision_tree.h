#include <fstream>
#include <math.h>
#define MAX_SAMPLE 700

using namespace std;

#ifndef DECISON_TREE_H_INCLUDED
#define DECISON_TREE_H_INCLUDED

class decision_tree
{private:  int entropy(int sequence[25][2]);
           int attribute[MAX_SAMPLE][25];
           int choseroad[25][6];
  public: void read_file();
          void gain_tree(bool invaild[MAX_SAMPLE],int sequence[25][2],int root=24);
          void save_tree();
           decision_tree();
};

#endif // DECISON_TREE_H_INCLUDED
