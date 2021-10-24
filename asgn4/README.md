Assignment 4 - The Preambulations of Denver Long

This program takes in input from the user and creates a graph containing the set of vertices and
the set of edges that connect the vertices. The graph is represented with an adjaceny matrix.
The program performs a depth-first search on the graph to find the shortest Hamiltonian path.

Building

Build the program with:
make

Running

Run the program with:
$ ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]

OPTIONS
    -u             Use undirected graph.
    -v             Enable verbose printing.
    -h             Program usage and help. 
    -i infile      Input containing graph (default: stdin)
    -o outfile     Output of computed path (default: stdout)