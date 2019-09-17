/*
Copyright (c) 2019, Matt Post

Takes two tab-delimited trees per line on STDIN, computes the SST kernel.
*/

#include <string>
#include "tree_parser.h"
#include "tree-kernel.h"
#include "sentence.h"
#include "util.h"

using namespace std;

int main()
{
   string line;
   int lineno = 0;
   while (getline(cin, line)) {
     lineno++;
     string::size_type tabpos = line.find("\t");
     if (tabpos == string::npos) {
       cerr << "[" << lineno << "] No tab found" << endl;
       cout << endl;
       continue;
     }

     string tree1_str = line.substr(0, tabpos);
     string tree2_str = line.substr(tabpos + 1);
     double value = kernel_value(tree1_str, tree2_str, true);
     cout << value << endl;
   }

   return 0;
}
