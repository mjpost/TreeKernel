#ifndef SENTENCE_NODE_H
#define SENTENCE_NODE_H

/*
Copyright (c) 2011,2015 Jeff Donner

    Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

    The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <vector>
#include <string>
#include <iosfwd>
#include <stdint.h>
#include <memory.h>

// Improvements:
// * Make the tag types enums; leaf text is never a tag, at least not
//   the way we implement it here, so it's not a conflict.
// * 'cache' productions; probably worth it.
//
// Both are tree / node....
class Node
{
public:
   typedef std::vector<Node*> Nodes;
public:
   Node(std::string const& tag)
   : tag_(tag)
   {}

   const std::string& label() const {
     return tag_;
   }

   // terminal nodes have no nodes as children
   bool is_terminal() const;

   /// Typical 3-way comparison
   static int productions_cmp(Node const& one, Node const& two);

   /// Slightly optimized for eq / ne
   static bool productions_equal(Node const* one, Node const* two);

   /// Yes by value (NVRO). Of course that's not actually the problem,
   /// it's the content that gets created every time we call this.
   std::string productions() const;

   static bool production_is_less(Node const* one, Node const* two);

   void add_child(Node* child) {
      /// &&& other checks, as to whether we're over a maximum
      Child elt(child);
      children_.push_back(elt);
   }

   void add_child(std::string const& word) {
      Child elt(word);
      children_.push_back(elt);
   }
   Nodes children() const;

   /// tag and production, for debugging
   std::string id_string() const;

   void pretty_print(std::ostream& os, int level) const;

private:
   // helper to pretty_print
   static void indent(std::ostream& os, int level);

private:
   struct Child;
   friend struct Child;
   /// 'discriminated union', a link to a child. Can embed a string
   /// though, for a terminal child.
   struct Child
   {
      Child(Node* tree)
      : node_(tree)
      {}

      Child(std::string const& text)
      : tok_(text)
      , node_(0)
      {}
      /// Tag, type detecter
      bool is_node() const { return this->node_ != 0; }
      /// Tag, type detecter
      bool is_text() const { return !is_node(); }

      /// Immediate text, if it's a 'text child'; not the full production.
      std::string const& text() const { return this->tok_; }

      /// Full Node* child; unsafe, you must first check the type
      Node* node() const { return this->node_; }

      /// Specialized; saves a bit of time over full 3-way
      static bool production_component_is_less(
         Child const& one, Child const& two);

      /// standard 3-way
      static int production_component_cmp(Child const& one,
                                          Child const& two) {
         return ::strcmp(one.production_component(),
                         two.production_component());
      }
      /// This child's part of the parent's production. Ok for both
      /// full node and embedded string. It returns the leaf name
      /// for leaves or otherwise the nonterminal name.
      char const* production_component() const {
         if (is_text()) return text().c_str();
         else return node_->tag_.c_str();
      }

   public:
      // wants to be a union, but std::string has a ctor
      // &&& Implement these as a Variant (or boost::any), to save
      // memory and cache pressure. Alexandrescu has one (as does
      // Boost, which Christopher Diggens claims to have a faster version of).
      // http://www.codeproject.com/KB/architecture/union_list.aspx
      //
      // Meh - not sure we'd get any space saving from a discriminated
      // union; node_* doubles as a type tag (I doubt any valid string
      // is pure 0).
      std::string tok_;
      Node* node_;
   };

   typedef std::vector<Child> Children;

   Children const& child_links() const { return children_; }

private:
   const std::string tag_;
   Children children_;
};

#endif // SENTENCE_NODE_H
