# 4D-Memory-Allocator
A program that works with a 4d linked list/graph structure 

This program was written in C, to explore memory management with allocation and deallocation of memory.

This program which originally started as a linked list, has been expanded to a 4d linked list/graph structure, in which the nodes are linked in 4 directions: next, prev, up, and down.

The program allows the user to add, remove, and visualize the structure.

The program also allows the user to free the structure, which will free all the nodes in the structure.

The program allows the user to add to the structure in many different ways, including adding to the end, start, top, or bottom, it also utilizes a breadth first algorithm to add to the structure, which addes to the first available node in the structure found by the breadth first algorithm.

This program also has two print functions, one that prints the structure in a depth first manner, and one that prints the structure in a breadth first manner. 

The program also has a free function which first used a breadth first algorithm to find all the nodes in the structure, then it frees all the nodes in the structure.