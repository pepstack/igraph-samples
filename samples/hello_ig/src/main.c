/**
 * main.c
 *   A simple demo shows how to use igraph C APIs.
 */
#include <stdio.h>
#include <igraph.h>


int main(int argc, char *argv[])
{
    igraph_t graph;
    igraph_vector_t edges;

    igraph_real_t data[] = {
        /* from vid, to vid */
        0, 1,
        0, 2,
        0, 5,
        1, 2,
        1, 4,
        2, 4,
        1, 3,
        3, 5
    };

    igraph_vector_view(&edges, data, sizeof(data)/sizeof(igraph_real_t));

    igraph_empty(&graph, 6, IGRAPH_UNDIRECTED);
    igraph_add_edges(&graph, &edges, 0);

    igraph_add_vertices(&graph, 2, 0);
    igraph_add_edge(&graph, 6,4);
    igraph_add_edge(&graph, 6,5);
    igraph_add_edge(&graph, 7,5);
    igraph_add_edge(&graph, 7,3);

    printf("[hello igraph] vertices: %d, edges: %d\n", (int)igraph_vcount(&graph), (int)igraph_ecount(&graph));

    igraph_destroy(&graph);
    return 0;
}