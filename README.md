# Computer Systems and C Programming

A seven-project progression through low-level programming, algorithms, data structures, compression, cryptography, and probabilistic filtering—all implemented in C.

This repository emphasizes understanding systems from first principles. Rather than relying on high-level libraries, the projects implement core algorithms and supporting data structures directly, measure their behavior, and expose them through focused command-line tools.

## Projects

| Directory | Project | Core concepts |
| --- | --- | --- |
| [`asgn1/`](asgn1/) | Pass the Pigs simulation | Control flow, arrays, pseudorandom simulation |
| [`asgn2/`](asgn2/) | Numerical methods library | Series approximations, convergence, floating-point analysis |
| [`asgn3/`](asgn3/) | Sorting workbench | Insertion, Shell, Heap, and Quick Sort; operation instrumentation |
| [`asgn4/`](asgn4/) | Traveling Salesperson solver | Graphs, depth-first search, backtracking, path optimization |
| [`asgn5/`](asgn5/) | Huffman codec | Frequency histograms, priority queues, trees, bit-level I/O |
| [`asgn6/`](asgn6/) | RSA cryptosystem | Number theory, prime generation, modular arithmetic, public-key encryption |
| [`asgn7/`](asgn7/) | Bloom-filter word classifier | Bloom filters, hash tables, binary search trees, keyed hashing |

## Highlights

### Algorithm analysis

The sorting workbench implements four algorithms behind a shared interface and records their comparisons and element moves. Configurable input size, random seed, and output limits make it possible to compare empirical behavior across algorithms and data distributions.

```bash
./asgn3/sorting -a -n 1000 -p 20 -r 1337
```

### Graph search and backtracking

The Traveling Salesperson solver represents weighted graphs with an adjacency matrix and performs depth-first search to find a minimum-cost Hamiltonian cycle. It maintains explicit stack and path abstractions, supports directed and undirected inputs, and can print every candidate tour explored.

```bash
./asgn4/tsp -u -i graph.txt
```

### Lossless compression

The Huffman codec builds a frequency histogram, constructs an optimal prefix-code tree with a priority queue, serializes the tree, and writes encoded data through bit-level I/O routines. The decoder reconstructs the tree and restores the original byte stream.

```text
input bytes → histogram → Huffman tree → code table → packed bitstream
packed bitstream → rebuilt tree → decoded bytes
```

```bash
./asgn5/encode -i input.bin -o input.huf -v
./asgn5/decode -i input.huf -o restored.bin -v
cmp input.bin restored.bin
```

### Public-key cryptography

The RSA project implements the mathematics and file-processing pipeline for key generation, encryption, and decryption. It includes Euclid's algorithm, modular inverses, modular exponentiation, Miller-Rabin primality testing, random-prime generation, and RSA block operations using GMP arbitrary-precision integers.

```text
keygen  → public key + private key
encrypt → plaintext blocks → modular exponentiation → ciphertext
decrypt → ciphertext blocks → modular exponentiation → plaintext
```

```bash
./asgn6/keygen -b 256 -n rsa.pub -d rsa.priv
./asgn6/encrypt -i message.txt -o message.rsa -n rsa.pub
./asgn6/decrypt -i message.rsa -o restored.txt -n rsa.priv
```

### Probabilistic filtering

The final project combines a Bloom filter with a hash table of binary search trees. The Bloom filter provides a memory-efficient first pass; probable matches are then resolved against exact stored words. The implementation uses a bit vector and multiple keyed SPECK hashes and can report lookup statistics.

## Build

### Requirements

- A POSIX-compatible C development environment
- `clang`
- `make`
- `pkg-config` and GMP for the RSA project

Each project is self-contained and has its own Makefile:

```bash
make -C asgn1
make -C asgn2
make -C asgn3
make -C asgn4
make -C asgn5
make -C asgn6
make -C asgn7
```

> [!NOTE]
> These projects were written for their original course toolchain. Recent Clang releases diagnose some legacy C declarations more strictly, while the Makefiles promote every warning to an error. On a newer toolchain, the source may require minor standards-compatibility updates or a local `CFLAGS` override. The RSA project also requires the GMP development headers and library to be discoverable through `pkg-config`.

Build only the project you want to explore, then use its local README or the program's `-h` option for command details. Clean generated binaries and object files with:

```bash
make -C asgn5 clean
```

## Repository structure

```text
.
├── asgn1/  simulation and introductory C
├── asgn2/  mathematical approximations
├── asgn3/  instrumented sorting algorithms
├── asgn4/  graph search and TSP
├── asgn5/  Huffman encoder and decoder
├── asgn6/  RSA key generation and file encryption
├── asgn7/  Bloom-filter word classifier
└── notes/  course notes
```

Several directories also include design documents and technical writeups that describe the implementation strategy and analyze results.

## Technical focus

- disciplined C memory management and modular interfaces
- Make-based multi-file builds
- numerical approximation and convergence
- algorithm instrumentation and empirical comparison
- recursive graph traversal and backtracking
- queues, stacks, trees, graphs, hash tables, and bit vectors
- binary file formats and bit-level I/O
- arbitrary-precision arithmetic and public-key cryptography
- probabilistic data structures and collision handling

## Scope

These projects were created as a hands-on exploration of computer-systems fundamentals. The cryptographic implementation is educational and should not be used to protect production data.
