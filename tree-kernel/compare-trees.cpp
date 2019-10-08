/*
Copyright (c) 2019, Matt Post

Takes tab-delimited trees on STDIN, computes kernel between all pairs.
*/

#include <string>
#include "tree_parser.h"
#include "tree-kernel.h"
#include "sentence.h"
#include "util.h"

#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
  string line;
  int lineno = 0;

  double decay = 0.5;
  bool all_trees = true;
  bool include_leaves = false;
  bool normalize = true;

  for (int i = 1; i < argc; i++) {
    if (string("-h").compare(argv[i]) == 0) {
      cerr << "Usage: compare-trees [-h]\n";
      return 1;

    } else if (string("-d").compare(argv[i]) == 0) {
      decay = stod(argv[i+1]);
      cerr << "- setting decay to " << decay << endl;
      i++;

    } else if (string("-l").compare(argv[i]) == 0) {
      cerr << "- comparing leaves\n";
      include_leaves = true;

    } else if (string("-n").compare(argv[i]) == 0) {
      cerr << "- not normalizing\n";
      normalize = false;

    } else {
      cout << "No such flag " << argv[i] << endl;
      return 1;
    }
  }

  while (getline(cin, line)) {
    lineno++;

    // build a list of the trees
    vector<Tree const*> trees;
    string::size_type tabpos, startpos = 0;
    while ((tabpos = line.find("\t", startpos)) != string::npos) {
      string tree = line.substr(startpos, tabpos - startpos);
      Tree const* parsed_tree = make_tree(tree);
      if (parsed_tree != NULL)
        trees.push_back(parsed_tree);

      startpos = tabpos + 1;
    }
    if (startpos != 0) {
      string tree = line.substr(startpos);
      Tree const* parsed_tree = make_tree(tree);
      if (parsed_tree != NULL)
        trees.push_back(parsed_tree);
    }

    double score = 0;
    double z = 0;
    for (vector<Tree const*>::iterator tree1 = trees.begin();
         tree1 != trees.end();
         tree1++) {
      for (vector<Tree const*>::iterator tree2 = tree1 + 1;
           tree2 != trees.end();
           tree2++) {

        double overlap = kernel_value(*tree1, *tree2, all_trees, include_leaves, decay);
        double norm = sqrt(kernel_value(*tree1, *tree1, all_trees, include_leaves, decay) * kernel_value(*tree2, *tree2, all_trees, include_leaves, decay));
        score += overlap;
        if (normalize)
          z += norm;
        else
          z = 1;
        // cout << "CMP\n" << *tree1 << endl << *tree2 << endl;
        // cout << z << endl << endl;
        // cout << overlap << " / " << z << " = " << overlap / z << endl;
        // cout << overlap << endl;
        // cout << overlap << " " << norm << endl;
      }
    }
    cout << (score / z) << endl;
  }

  return 0;
}
