using namespace std;

Tree const* make_tree(string const& tree_text)
{
   TreeLexer lexer(tree_text);
   TreeParser parser(lexer);
   Tree const* t = 0;
   try {
      t = parser.match_and_eat_tree();
   }
   catch (string& ex) {
      cout << "failed parse: " << ex << endl;
   }

//   t->pretty_print(cout, 0);

   return t;
}

double kernel_value(string one, string two, bool want_sst_not_st = true)
{
   Tree const* t1 = make_tree(one);
   Tree const* t2 = make_tree(two);

   Sentence s1(t1);
   Sentence s2(t2);

   double value = kernel_value(s1, s2, want_sst_not_st);
   return value;
}

