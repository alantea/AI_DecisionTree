#include "decision_tree.h"

using namespace std;

int main()
{
	string str_buf;
    while(1)
    {
		cout << "----------------------" << endl;
        cout << "	MENU" << endl;
        cout << "----------------------" << endl;
        cout << "1. Testing mode" << endl;
        cout << "2. Training mode" << endl;	//The first part : produce the decision tree.
        cout << endl;
        cout << "Enter option : " << ends;

		getline(cin, str_buf);
        int option = atoi(str_buf.c_str());
        cin.clear();
	//	cin.sync();			// can't not use in un*x system

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

        cout << "Do you want to continued [y/N]? " << ends;

		getline(cin, str_buf);
		char cont = str_buf[0];

        if(cont != 'y' && cont != 'Y')
		{
            break;
		}
    }//end while

	return 0;
}
