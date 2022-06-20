#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

struct Vertex
{
    int value;
    bool visited;
};

// stack variables

int stack[MAX];
int top = -1;

// graph variables

// array of vertices
struct Vertex *lstVertices[MAX];

// adjacency matrix
int adjMatrix[MAX][MAX];

// vertex count
int vertexCount = 0;

// stack functions

void push(int item)
{
    stack[++top] = item;
}

int pop()
{
    return stack[top--];
}

int peek()
{
    return stack[top];
}

bool isStackEmpty()
{
    return top == -1;
}

// graph functions

// add vertex to the vertex list
void addVertex(int value)
{
    struct Vertex *vertex = (struct Vertex *)malloc(sizeof(struct Vertex));
    vertex->value = value;
    vertex->visited = false;
    lstVertices[vertexCount++] = vertex;
}

// add edge to edge array
void addEdge(int start, int end)
{
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1;
}

// display the vertex
void displayVertex(int vertexIndex)
{
    printf("%d ", lstVertices[vertexIndex]->value);
}

// get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex)
{
    int i;

    for (i = 0; i < vertexCount; i++)
    {
        if (adjMatrix[vertexIndex][i] == 1 && lstVertices[i]->visited == false)
        {
            return i;
        }
    }

    return -1;
}

void depthFirstSearch()
{
    int i;

    // mark first node as visited
    lstVertices[0]->visited = true;

    // display the vertex
    displayVertex(0);

    // push vertex index in stack
    push(0);

    while (!isStackEmpty())
    {
        // get the unvisited vertex of vertex which is at top of the stack
        int unvisitedVertex = getAdjUnvisitedVertex(peek());

        // no adjacent vertex found
        if (unvisitedVertex == -1)
        {
            pop();
        }
        else
        {
            lstVertices[unvisitedVertex]->visited = true;
            displayVertex(unvisitedVertex);
            push(unvisitedVertex);
        }
    }

    // stack is empty, search is complete, reset the visited flag
    for (i = 0; i < vertexCount; i++)
    {
        lstVertices[i]->visited = false;
    }
}

int main()
{
    int i, j;

    for (i = 0; i < MAX; i++)     // set adjacency {
        for (j = 0; j < MAX; j++) // matrix to 0
            adjMatrix[i][j] = 0;

    addVertex(0);
    addVertex(1);
    addVertex(2);
    addVertex(3);
    addVertex(4);

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(2, 4);

    printf("Depth First Search:\n");
    depthFirstSearch();

    return 0;
}