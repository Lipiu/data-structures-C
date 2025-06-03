#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char* name;
    short id;
    short group;
    float income;
};
typedef struct Student Student;
typedef struct Student* PStudent;

struct Vertex{
    Student* info;
    struct Neighbour* adjacentList;
    struct Vertex* next;
};
typedef struct Vertex Vertex;

struct Neighbour{
    struct Vertex* mainVertex;
    struct Neighbour* nextVertex;
};
typedef struct Neighbour Neighbour;

void insertVertex(Vertex**, Student*);
void addEdge(Vertex**, int, int);