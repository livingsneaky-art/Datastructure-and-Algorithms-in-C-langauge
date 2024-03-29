#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTEX 5
#define MAX 10 /** undirected: 5(5-1) / 2 **/
#define INFINITY 9999

/* An unweighted, undirected Edge */
typedef struct {
	int vertex;
	int adj_vertex;
}edgeType;

typedef struct {
	edgeType Edge[MAX];
	int edge_count;
}EdgeList;

typedef int MATRIX[MAX_VERTEX][MAX_VERTEX]; // static
typedef int ** MATRIX_1; // dynamic
/**
 *      Dijkstra's algorithm is used to get the shortest path from 1 vertex to the rest.
 *      This is called single source shortest path.
 *
 *      This dijkstra's algorithm follows the concept of a minimum priority queue.
 *       Here, we set the distance of every other vertex except the source vertex
 *          to be INFINITY because we still have to visit them in order for us to
 *          know the distance.
 * 
 *       Since this algorthim finds the shortest path from 1 source to every other vertex,
 *          it makes sense to use a minimum priority queue. :)
 *      Although it is tedious to implement because u have to create insert and deleteMin()
 *         functions for the priority queue, it is faster than the other implementation.
 * 
 *      Note: Time Complexity calculation is based on an adjacency list representation,
 *              where we only loop the edges and not the vertices. 
 *              (When we loop the neighboring vertices in a list, we are technically looping
 *                the number of edges this vertex has. In a matrix, we are really looping
 *                  all vertices.)
 * 
 *      Your task is to create the dijkstra's algorithm using a 
 *          priority queue in an adjacency list representation.
 *              Hint: U do not need to convert the adj list to adj matrix unlike the
 *              native dijkstra's algorithm.
 * 
 * 
 **/

typedef struct {
    int vertex;
    int weight;
} Node;

typedef struct {
    Node node[MAX_VERTEX];
    int last_index;
} PQ;

void insert(PQ *Q, int vertex, int weight)
{
    if (Q->last_index < MAX_VERTEX - 1) {

        int current, parent;
        current = ++Q->last_index;
        
        parent = (current - 1) / 2;
        while (current > 0 && Q->node[parent].weight > weight) {
            Q->node[current] = Q->node[parent];
            current = parent;
            parent = (parent - 1) / 2;
        }
        Q->node[current].vertex = vertex;
        Q->node[current].weight = weight;
    }
}

Node deleteMin(PQ *Q)
{
    Node node;
    if (Q->last_index >= 0) {
        int current = 0, child = 1;

        node = Q->node[current];
        Q->node[current] = Q->node[Q->last_index--];

        Node temp;
        while (child <= Q->last_index) {
            if (child + 1 <= Q->last_index && Q->node[child].weight > Q->node[child + 1].weight) {
                child++;
            }

            if (Q->node[current].weight > Q->node[child].weight) {
                temp = Q->node[current];
                Q->node[current] = Q->node[child];
                Q->node[child] = temp;

                current = child;
                child = 2 * child + 1;
            } else {
                break;
            }
        }
    }
    return node;
}

// O (V (log V + E log V))
// O (V log V + VE log V)
// O (V+E log V)
int *dijkstra(MATRIX M, int source)
{
    // create an empty PQ
    PQ Q = {.last_index = -1};

    // initialize distance to be infinity
    // This time we give all vertices a distance of infinity
    // because we have to first visit the node before we get
    // to know the distance
    int *distance = (int *) malloc (MAX_VERTEX * sizeof(int));
    if (!distance) return NULL;
    for (int i = 0; i < MAX_VERTEX; i++) distance[i] = INFINITY;

    // starting from the source, we let the distance be 0
    // source -> source (it has a distance of 0)
    // We insert that to PQ because this is our first vertex
    distance[source] = 0;
    insert(&Q, source, 0);

    Node temp;
    // O (V) where N is the number of vertices
    // Until PQ is empty, we perform the operation.
    while (Q.last_index > -1) {
        // we have to remove the minimum distance from the PQ
        temp = deleteMin(&Q); // O (log V)
        int current_vertex = temp.vertex;

        // O (E)
        // Get all the neighboring vertex relative to the current_vertex
        for (int neighbor = 0; neighbor < MAX_VERTEX; neighbor++) {
            // The vertex and the neighboring vertex must be connected 
            // (there is a path - which means the distance cannot be INFINITY)
            // The neighboring vertex must not be the current vertex
            if (M[current_vertex][neighbor] != INFINITY && M[current_vertex][neighbor] != 0) {
                
                // if there is a shorter path through the current_vertex going to the neighboring vertex
                // then we update the distance of the neighboring vertex and then insert that to the PQ
                // Note that inserting a vertex to the PQ will make the node "visited" or some sort.
                if (distance[neighbor] > distance[current_vertex] + M[current_vertex][neighbor]) {
                    distance[neighbor] = distance[current_vertex] + M[current_vertex][neighbor];
                    insert(&Q, neighbor, distance[neighbor]); // O (log V)
                }
            }
        }
    }

    return distance;
    
}

void displayShortestDistance(int distance[], int source)
{
    printf("\n\nSource vertex: %d", source);
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("\nShortest distance from %d to %d: %d", source, i, distance[i]);
}

void displayMatrix(MATRIX M)
{
    printf("%3c", ' ');
    for (int i = 0; i < MAX_VERTEX; i++)
        printf("%4d ", i);

    for (int i = 0; i < MAX_VERTEX; i++) {
        printf("\n%d: ", i);
        for (int j = 0; j < MAX_VERTEX; j++)
            printf("%4d ", M[i][j]);
    }
}

void main()
{
    MATRIX M = {
        {9999, 30, 25, 9999, 50},
        {30, 9999, 9999, 90, 30},
        {25, 9999, 9999, 40, 9999},
        {9999, 90, 40, 9999, 10},
        {50, 30, 9999, 10, 9999}
    };

    displayMatrix(M);

    /**
     *  graph is undirected
     *  where (x) is the node
     *  and --y-- is the weight
     * 
     * 
     * 
     *                  (2) -------25-------(0)
     *                   |                   | \   
     *                   |                   |  \ 
     *                   |                  30   \ 
     *                   |                   |    \
     *                   |                   |     50
     *                   40         |------ (1)     \   
     *                   |          |         \      \
     *                   |          |          \      |
     *                   |  ---90----          30     | 
     *                   | /                     \    | 
     *                  (3) ---------10----------(4)--|
     **/


    int source = 0;
    int *shortest_distance = dijkstra(M, source);
    displayShortestDistance(shortest_distance, source);

}
