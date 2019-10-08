/*
Copyright (c) 2019, Matt Post

Takes tab-delimited trees on STDIN, computes kernel between all pairs.
*/

#include <string>
#include "tree_parser.h"
#include "tree-kernel.h"
#include "sentence.h"
#include "util.h"

using namespace std;

int main(int argc, char **argv)
{
  string line;
  int lineno = 0;
  while (getline(cin, line)) {
    lineno++;

    // build a list of the trees
    vector<string> trees;
    string::size_type tabpos, startpos = 0;
    while ((tabpos = line.find("\t", startpos)) != string::npos) {
      string tree = line.substr(startpos, tabpos - startpos);
      trees.push_back(tree);
      startpos = tabpos + 1;
    }
    if (startpos != 0)
      trees.push_back(line.substr(startpos));

    double score = 0;
    for (vector<string>::iterator tree1 = trees.begin();
         tree1 != trees.end();
         tree1++) {
      for (vector<string>::iterator tree2 = tree1 + 1;
           tree2 != trees.end();
           tree2++) {

        double overlap = kernel_value(*tree1, *tree2);
        score += overlap;
        // cout << "CMP\n" << *tree1 << endl << *tree2 << endl;
        // cout << z << endl << endl;
        // cout << overlap << " / " << z << " = " << overlap / z << endl;
        // cout << overlap << endl;
      }
    }
    cout << score << endl;
  }

  return 0;
}
