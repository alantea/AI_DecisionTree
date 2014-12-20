#include "decision_tree.h"

using namespace std;

int main()
{
	// The first part : produce the decision tree.
	decision_tree goal;
	bool invaild[MAX_SAMPLE] = {0};
	int sequence[25][2];
	
	for(int i=0;i<25;i++)
	{
		sequence[i][0]=25;
		sequence[i][1]=25;
	}
	
	goal.read_file();
	goal.gain_tree(invaild,sequence);
	goal.save_tree();
	
	// The second part : test the data.

	return 0;
}
