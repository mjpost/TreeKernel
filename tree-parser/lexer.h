#ifndef LEXER_H
#define LEXER_H

/***
 * Excerpted from "Language Implementation Patterns",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/tpdsl for more book information.
***/

#include <string>
#include "token.h"
#include <iostream>


class Lexer {
public:
   enum {
      EOF = -1, // &&& this chokes with c++0x
      EOF_TYPE   = 0
   };

   Lexer(std::string input)
   : input(input)
   , p(0)
   , c(input[p])
   { }

   /** Move one character; detect "end of file" */
   void consume() {
      ++p;

      if (input.length() <= p) {
         c = EOF;
      }
      else {
         c = input[p];
//         std::cout << "lexer; consumed, now c==: [" << c << "]" << std::endl;
      }
   }

   /** Ensure x is next character on the input stream */
   void match(char x) {
      if (c == x)
         consume();
      else
         throw std::string("expecting ") + x + "; found " + c;
   }

   virtual Token next_token() = 0;

   std::string input;
   unsigned p;             // index into input of current character
   char c;            // current character
};

#endif // LEXER_H
