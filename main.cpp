#include "decision_tree.h"
#include <iostream>

using namespace std;

int main()
{
    while(1)
    {
        cout << "1. Testing mode" << endl;
        cout << "2. Training mode" << endl;	//The first part : produce the decision tree.

        int option;
        cin >> option;

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

        cout << "Do you want to continued ? [y/n]" << endl;

        char cont;
        cin >> cont;

        if(cont != 'y' && cont != 'Y')
            break;
    }//end while

	return 0;
}
