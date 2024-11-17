#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define MAX_VERTICES 80
#define INF INT_MAX
#define V 15 // Number of vertices in the graph

// Structure to represent a graph
typedef struct {
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

// Function to initialize the graph
void initGraph(Graph *g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adj[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// Function to add an edge to the graph
void addEdge(Graph *g, int src, int dest, int weight) {
    g->adj[src][dest] = weight;
}

// Dijkstra's algorithm
void dijkstra(Graph *g, int src, int *dist) {
    bool visited[MAX_VERTICES] = {false};
    for (int i = 0; i < g->vertices; i++) {
        dist[i] = g->adj[src][i];
    }
    dist[src] = 0;
    visited[src] = true;

    for (int count = 0; count < g->vertices - 1; count++) {
        int min_distance = INF, min_index = -1;

        // Find the vertex with the minimum distance
        for (int v = 0; v < g->vertices; v++) {
            if (!visited[v] && dist[v] < min_distance) {
                min_distance = dist[v];
                min_index = v;
            }
        }

        if (min_index == -1) break; // All reachable vertices processed
        visited[min_index] = true;

        // Update distances of the adjacent vertices
        for (int v = 0; v < g->vertices; v++) {
            if (!visited[v] && g->adj[min_index][v] != INF &&
                dist[min_index] != INF && dist[min_index] + g->adj[min_index][v] < dist[v]) {
                dist[v] = dist[min_index] + g->adj[min_index][v];
            }
        }
    }
}

// Bellman-Ford algorithm
int bellmanFord(Graph *g, int src, int *dist) {
    for (int i = 0; i < g->vertices; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    // Relax edges
    for (int i = 1; i < g->vertices; i++) {
        for (int u = 0; u < g->vertices; u++) {
            for (int v = 0; v < g->vertices; v++) {
                if (g->adj[u][v] != INF && dist[u] != INF && dist[u] + g->adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + g->adj[u][v];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < g->vertices; u++) {
        for (int v = 0; v < g->vertices; v++) {
            if (g->adj[u][v] != INF && dist[u] != INF && dist[u] + g->adj[u][v] < dist[v]) {
                return 0; // Negative cycle detected
            }
        }
    }
    return 1; // No negative cycle
}

int main() {
    Graph g;
    initGraph(&g, V);

    // Updated graph with new edge weights
    addEdge(&g, 0, 1, 4);
    addEdge(&g, 0, 2, 1);
    addEdge(&g, 0, 3, 2);
    addEdge(&g, 1, 4, 5);
    addEdge(&g, 1, 5, 2);
    addEdge(&g, 2, 5, 8);
    addEdge(&g, 2, 6, 7);
    addEdge(&g, 3, 7, 3);
    addEdge(&g, 4, 8, 6);
    addEdge(&g, 5, 9, 3);
    addEdge(&g, 6, 10, 4);
    addEdge(&g, 7, 11, 2);
    addEdge(&g, 8, 12, 5);
    addEdge(&g, 9 , 13, 1);
    addEdge(&g, 10, 14, 6);
    addEdge(&g, 11, 15, 3);

    int distDijkstra[MAX_VERTICES];
    int distBellman[MAX_VERTICES];

    clock_t start, end;

    // Measuring Dijkstra's execution time
    start = clock();
    dijkstra(&g, 0, distDijkstra);
    end = clock();
    double dijkstra_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Measuring Bellman-Ford execution time
    start = clock();
    int hasNegativeCycle = bellmanFord(&g, 0, distBellman);
    end = clock();
    double bellman_ford_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the results
    printf("Dijkstra's Algorithm Result: ");
    for (int i = 0; i < V; i++) {
        printf("%d ", distDijkstra[i]);
    }
    printf("\n");

    if (hasNegativeCycle) {
        printf("Bellman-Ford Algorithm Result: ");
        for (int i = 0; i < V; i++) {
            printf("%d ", distBellman[i]);
        }
        printf("\n");
    } else {
        printf("Bellman-Ford Algorithm: Negative cycle detected\n");
    }

    // Display execution times
    printf("Dijkstra's Algorithm Time: %f seconds\n", dijkstra_time);
    printf("Bellman-Ford Algorithm Time: %f seconds\n", bellman_ford_time);

    return 0;
}
