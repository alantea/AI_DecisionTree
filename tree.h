#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

// C++ library
#include <map>
#include <string>
#include <sstream>
#include <fstream>

class tree
{
	private:
		void initial_child(tree &now);
		void save_node(std::fstream &out, tree &now);
		void read_node(std::fstream &fin, tree &now);
	public:
		int value;
		std::map<int , tree> child;

		void initial();
		void save(std::string output_file);
		void read(std::string input_file);
};

#endif
