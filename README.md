A C++ implementation of tree kernels per Alessandro Moschitti's 2006
paper, "Making Tree Kernels Practical for Natural Language Learning"

This consists of two directories, tree-parser and tree-kernel itself.
tree-parser parses Penn Tree Bank forms of sentences as produced by
the [Standford Parser](http://nlp.stanford.edu/software/lex-parser.shtml),
[(example)](http://nlp.stanford.edu:8080/parser) among others. Eg:

     (ROOT
       (S
         (NP (PRP$ My) (NN dog))
         (ADVP (RB also))
         (VP (VBZ likes)
           (S
             (VP (VBG eating)
               (NP (NN sausage)))))
         (. .)))


This is MIT licensed (see LICENSE), and commercially useable. If you
need a different one just ask.

To be useful this needs to be integrated into an SVM library, the two candidates I had in mind were:
    libSVM - [github](https://github.com/cjlin1/libsvm), [home](http://www.csie.ntu.edu.tw/~cjlin/libsvm)
and:
    Dlib - [home](http://dlib.net/ml.html)

Build tree-parser before tree-kernel, as tree-kernel uses
tree-parser. tree-kernel relies on the current directory structure,
though that should be easy enough to change. This is GNU Makefile, and
GCC based, but it's not too complicated and should be easily tweakable
for other systems.

There are several optimizations possible - templating out sigma,
making NodePairsDeltaTable an unordered_map, but most of all, storing
the Nodes in Sentence in a vector and using indices as pointers to
them (to save memory and cache). C bindings would be nice, too.

If you make any improvements I'll be happy to take them. Of course,
you can just do what you want with it, subject to the LICENSE.
