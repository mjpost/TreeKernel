#include "tree_parser.h"

using namespace std;

void lex_only(string tree_text, string tree_name)
{
   cout << "lexing..." << tree_name << endl;
   TreeLexer lexer(tree_text);
   Token tok = lexer.next_token();
   int x = 0;
   while (tok.type != TreeLexer::EOS_TYPE and x < 10) {
      cout << "[" << tok.text << "] ";
      tok = lexer.next_token();
      ++x;
   }
   cout << endl;
}

void test_tree(string tree_text, string tree_name)
{
   cout << '\n' << tree_name << endl;
   //   lex_only(tree_text, tree_name);
   TreeLexer lexer(tree_text);
   TreeParser parser(lexer);
   Tree const* t = 0;
   try {
      t = parser.match_and_eat_tree();
   }
   catch (string& ex) {
      cout << "failed parse: " << ex << endl;
   }

   if (t) {
//      cout << "printing in order:" << endl;
//      t->print_inorder(cout);
      t->print_nice(cout, 0);
   }
}

int main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;
  string line;
  int lineno = 0;
  while (getline(cin, line)) {
    lineno++;
    test_tree(line, to_string(lineno));
  }

  return 0;
}
