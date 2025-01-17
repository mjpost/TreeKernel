CXXFLAGS=-O2 -Wall -Wextra
CXX=g++ -std=c++0x
INCLUDE=-I/usr/include -I../tree-parser
LIB_SOURCES=\
	node.cpp \
	sentence.cpp \
	tree-kernel.cpp
TEST_SOURCES=\
	test-tree-kernel.cpp
SOURCES=\
  compare-trees.cpp
OBJDIR=.objs
LIB_OBJECTS=$(addprefix $(OBJDIR)/, $(LIB_SOURCES:.cpp=.o))
TEST_OBJECTS=$(addprefix $(OBJDIR)/, $(TEST_SOURCES:.cpp=.o))
OBJECTS=$(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
LIBSDIR=../tree-parser
LIBS=tree_parser

TEST_TARGET=test-tree-kernel
LIB_TARGET=libtree_kernel.a
TARGET=compare-trees

all: $(LIB_TARGET) $(TEST_TARGET) $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

# $@ is the target (objs/foo.o), and $< is the input foo.cpp
$(OBJDIR)/%.o: %.cpp $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(LIB_TARGET): $(LIB_OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

$(TEST_TARGET): $(LIB_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(LIB_OBJECTS) $(TEST_OBJECTS) -L$(LIBSDIR) -l$(LIBS) -o $@

$(TARGET): $(LIB_OBJECTS) $(OBJECTS)
	$(CXX) $(LIB_OBJECTS) $(OBJECTS) -L$(LIBSDIR) -l$(LIBS) -o $@

clean:
	rm -f $(LIB_TARGET)
	rm -f $(TEST_TARGET)
	rm -f $(LIB_OBJECTS) $(TEST_OBJECTS)
