# C++ Graph Algorithms (Pakistan Train Routes)

## Overview
This workspace demonstrates core graph algorithms in C++ using a real-world style dataset of Pakistan train routes. It includes two C++ programs and a CSV dataset to practice graph representations and classic traversal/shortest-path/minimum-spanning-tree techniques.

## Files
- main2.cpp: Reads a CSV of city-to-city distances, builds an adjacency matrix, and provides a menu-driven interface for graph operations.
- test1.cpp: A small fixed graph (5 nodes) that demonstrates adjacency list/matrix output and algorithm executions.
- pakistan_train_routes.csv: Sample routes with Origin, Destination, and Distance columns.

## What You Can Learn
- Graph representations: adjacency matrix and adjacency list output.
- Traversal algorithms: BFS and DFS.
- Shortest path: Dijkstra's algorithm.
- Minimum spanning tree: Prim's and Kruskal's algorithms.
- Basic data structures: custom queue and stack implementations in main2.cpp.

## How It Works
### main2.cpp
- Parses pakistan_train_routes.csv into an adjacency matrix (max 20 cities).
- Offers a menu to:
  1. Display all cities
  2. Display adjacency matrix
  3. Display adjacency list
  4. BFS traversal
  5. DFS traversal
  6. Dijkstra
  7. Prim's
  8. Kruskal
- Uses custom Queue and Stack classes for BFS/DFS.

### test1.cpp
- Builds a fixed 5-node undirected weighted graph.
- Prints adjacency list and matrix.
- Runs BFS, DFS, Dijkstra, Prim's, and Kruskal's (called as prims at the end).

## Benefits of Learning This
- Builds intuition for real-world routing problems (transportation, networks, logistics).
- Reinforces algorithmic thinking with visible outputs and comparisons.
- Demonstrates how data files map into graph structures.
- Provides a clean sandbox to experiment with algorithm correctness and performance.

