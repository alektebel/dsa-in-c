/**
 * Breadth First Search Implementation
 */

#include "breadth_first_search.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Graph* bfs_graph_create(int num_vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;
    
    graph->num_vertices = num_vertices;
    graph->adjacency_list = (GraphNode**)calloc(num_vertices, sizeof(GraphNode*));
    if (!graph->adjacency_list) {
        free(graph);
        return NULL;
    }
    
    return graph;
}

bool bfs_graph_add_edge(Graph *graph, int from, int to, bool directed) {
    // TODO: Add edge to adjacency list
    return false;
}

BFSResult* bfs_search(Graph *graph, int start) {
    // TODO: Implement BFS from start vertex
    // 1. Create queue and enqueue start
    // 2. While queue not empty:
    //    - Dequeue vertex
    //    - Visit all unvisited neighbors
    //    - Enqueue neighbors and record distance
    return NULL;
}

BFSResult* bfs_search_all(Graph *graph) {
    // TODO: BFS on all components
    return NULL;
}

int bfs_shortest_path(Graph *graph, int start, int target, int *path, int max_length) {
    // TODO: Find shortest path
    // 1. Run BFS from start
    // 2. Reconstruct path from parent pointers
    return -1;
}

int bfs_shortest_distance(Graph *graph, int start, int target) {
    // TODO: Find shortest distance
    // Run BFS and return distance[target]
    return -1;
}

bool bfs_is_bipartite(Graph *graph) {
    // TODO: Check bipartiteness
    // Use BFS with 2-coloring
    // If we can color with 2 colors, graph is bipartite
    return false;
}

int bfs_vertices_at_distance(Graph *graph, int start, int distance, 
                             int *vertices, int max_vertices) {
    // TODO: Find vertices at exact distance
    return 0;
}

int bfs_connected_components(Graph *graph, int *components) {
    // TODO: Find connected components
    // Run BFS from each unvisited vertex
    return 0;
}

BFSResult* bfs_multi_source(Graph *graph, int *sources, int num_sources) {
    // TODO: Multi-source BFS
    // Enqueue all sources initially with distance 0
    return NULL;
}

Queue* queue_create(void) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

bool queue_enqueue(Queue *queue, int vertex) {
    // TODO: Add to rear of queue
    return false;
}

int queue_dequeue(Queue *queue) {
    // TODO: Remove from front of queue
    return -1;
}

bool queue_is_empty(Queue *queue) {
    return queue && queue->size == 0;
}

void queue_destroy(Queue *queue) {
    // TODO: Free all queue nodes
    if (queue) {
        free(queue);
    }
}

void bfs_result_destroy(BFSResult *result) {
    if (result) {
        if (result->visited_order) free(result->visited_order);
        if (result->parent) free(result->parent);
        if (result->distance) free(result->distance);
        if (result->visited) free(result->visited);
        free(result);
    }
}

void bfs_graph_destroy(Graph *graph) {
    // TODO: Free all adjacency lists
    if (graph) {
        if (graph->adjacency_list) free(graph->adjacency_list);
        free(graph);
    }
}

void bfs_graph_print(Graph *graph) {
    printf("Graph with %d vertices:\n", graph->num_vertices);
    // TODO: Print adjacency lists
}
