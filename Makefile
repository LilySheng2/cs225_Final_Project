# Executable names:

EXE = main
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = FileIO.o main.o graph.o highlyConnected.o pageRank.o UndirectedGraph.o

OBJS = FileIO.o main.o graph.o highlyConnected.o pageRank.o UndirectedGraph.o

# Generated files

# Use the cs225 makefile template:
include cs225/make/cs225.mk