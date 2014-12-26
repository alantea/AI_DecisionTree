#include "tree.h"

using namespace std;

void tree::initial()
{
	initial_child(*this);
	this->child.clear();
	this->value = -99;
}

void tree::initial_child(tree &now)
{
	for( map<int,tree>::iterator i = now.child.begin() ; i != now.child.end() ; ++i )
	{
		initial_child( i->second );
	}
	now.child.clear();
	now.value = -99;
}

void tree::read(std::string input_file)
{
    fstream tree_file;
	tree_file.open( input_file.c_str() , fstream::in );

	read_node( tree_file , *this );

    tree_file.close();
}

void tree::read_node(std::fstream &fin, tree &now)
{
	string buf;
	tree tmp;
	int branch;

	getline( fin , buf );
	for( size_t i = 0 ; i < buf.length() ; i++ )
	{
		if( buf[i] == ',' )
		{
			buf[i] = ' ';
		}
	}

	stringstream ss(buf);

	// get the attribute name
	ss >> now.value;

	// insert the branch into child
	while( ss >> branch )
	{
		now.child[branch] = tmp;
	}

	// recursive to read the node
	for( map<int,tree>::iterator i = now.child.begin() ; i != now.child.end() ; ++i )
	{
		read_node( fin , i->second );
	}
}
