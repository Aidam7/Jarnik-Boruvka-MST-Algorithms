#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WEIGHT 100
#define NUMBER_OF_NODES 12

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct Node {
  char name;
  int index;
} Node;

// TODO: Is there a need to have nodes inside graph when edges have them?
// Could be optimized by using ArrayList for neighbors and edge_weights;
typedef struct Graph {
  struct Node **nodes; // Points to array of pointers
  int index_of_last_node;
  struct Edge **edges; // Points to array of pointers
  int index_of_last_edge;
} Graph;

typedef struct Edge {
  Node *from;
  Node *to;
  int weight;
} Edge;

Graph *create_graph();
Node *create_node(Graph *graph, char node_name);
void add_edge(Graph *graph, Node *from, Node *to, int weight);
void print_graph(Graph *graph);
Graph *boruvka_mst(Graph *input_graph);

int main() {
  printf("Hello world!\n");

  // Create same structure as here
  // https://cs.wikipedia.org/wiki/Bor%C5%AFvk%C5%AFv_algoritmus
  // to be able to easily check results
  Graph *GRAPH = create_graph();
  Node *A_NODE = create_node(GRAPH, 'A');
  Node *B_NODE = create_node(GRAPH, 'B');
  Node *C_NODE = create_node(GRAPH, 'C');
  Node *D_NODE = create_node(GRAPH, 'D');
  Node *E_NODE = create_node(GRAPH, 'E');
  Node *F_NODE = create_node(GRAPH, 'F');
  Node *G_NODE = create_node(GRAPH, 'G');
  Node *H_NODE = create_node(GRAPH, 'H');
  Node *I_NODE = create_node(GRAPH, 'I');
  Node *J_NODE = create_node(GRAPH, 'J');
  Node *K_NODE = create_node(GRAPH, 'K');
  Node *L_NODE = create_node(GRAPH, 'L');

  add_edge(GRAPH, A_NODE, B_NODE, 13);
  add_edge(GRAPH, A_NODE, C_NODE, 6);

  add_edge(GRAPH, B_NODE, A_NODE, 13);
  add_edge(GRAPH, B_NODE, C_NODE, 7);
  add_edge(GRAPH, B_NODE, D_NODE, 1);

  add_edge(GRAPH, C_NODE, A_NODE, 6);
  add_edge(GRAPH, C_NODE, B_NODE, 7);
  add_edge(GRAPH, C_NODE, D_NODE, 14);
  add_edge(GRAPH, C_NODE, E_NODE, 8);
  add_edge(GRAPH, C_NODE, H_NODE, 20);

  add_edge(GRAPH, D_NODE, B_NODE, 1);
  add_edge(GRAPH, D_NODE, C_NODE, 14);
  add_edge(GRAPH, D_NODE, E_NODE, 9);
  add_edge(GRAPH, D_NODE, F_NODE, 3);

  add_edge(GRAPH, E_NODE, C_NODE, 8);
  add_edge(GRAPH, E_NODE, D_NODE, 9);
  add_edge(GRAPH, E_NODE, F_NODE, 2);
  add_edge(GRAPH, E_NODE, J_NODE, 18);

  add_edge(GRAPH, F_NODE, D_NODE, 3);
  add_edge(GRAPH, F_NODE, E_NODE, 2);

  add_edge(GRAPH, G_NODE, H_NODE, 15);
  add_edge(GRAPH, G_NODE, I_NODE, 5);
  add_edge(GRAPH, G_NODE, K_NODE, 10);
  add_edge(GRAPH, G_NODE, J_NODE, 19);

  add_edge(GRAPH, H_NODE, C_NODE, 20);
  add_edge(GRAPH, H_NODE, G_NODE, 15);
  add_edge(GRAPH, H_NODE, J_NODE, 17);

  add_edge(GRAPH, I_NODE, G_NODE, 5);
  add_edge(GRAPH, I_NODE, K_NODE, 11);

  add_edge(GRAPH, J_NODE, H_NODE, 17);
  add_edge(GRAPH, J_NODE, G_NODE, 19);
  add_edge(GRAPH, J_NODE, K_NODE, 16);
  add_edge(GRAPH, J_NODE, L_NODE, 4);

  add_edge(GRAPH, K_NODE, L_NODE, 12);
  add_edge(GRAPH, K_NODE, J_NODE, 16);
  add_edge(GRAPH, K_NODE, G_NODE, 10);
  add_edge(GRAPH, K_NODE, I_NODE, 11);

  add_edge(GRAPH, L_NODE, K_NODE, 12);
  add_edge(GRAPH, L_NODE, J_NODE, 4);

  printf("FROM:\n");
  print_graph(GRAPH);

  Graph *final_mst = boruvka_mst(GRAPH);

  printf("TO:\n");
  printf("%c ", final_mst->edges[0]->from->name);
  printf("%c ", final_mst->edges[0]->to->name);
  printf("%c ", final_mst->edges[1]->from->name);
  printf("%c ", final_mst->edges[1]->to->name);
  printf("%c ", final_mst->edges[2]->from->name);
  printf("%c ", final_mst->edges[2]->to->name);
  printf("%c ", final_mst->edges[3]->from->name);
  printf("%c ", final_mst->edges[3]->to->name);
  printf("%c ", final_mst->edges[4]->from->name);
  printf("%c ", final_mst->edges[4]->to->name);

  return 0;
}

Graph *create_graph() {
  Graph *new_graph = malloc(sizeof(Graph));

  new_graph->nodes = malloc(NUMBER_OF_NODES * sizeof(Node *));
  for (int i = 0; i < NUMBER_OF_NODES; i++) {
    new_graph->nodes[i] = NULL;
  }

  // At max, we could connect every node with every node
  new_graph->edges = malloc(NUMBER_OF_NODES * NUMBER_OF_NODES * sizeof(Edge *));
  for (int i = 0; i < NUMBER_OF_NODES; i++) {
    new_graph->edges[i] = NULL;
  }

  new_graph->index_of_last_node = -1;
  new_graph->index_of_last_edge = -1;
  return new_graph;
}

Node *create_node(Graph *graph, char node_name) {
  Node *new_node = malloc(sizeof(Node));

  new_node->name = node_name;
  new_node->index = graph->index_of_last_node + 1;
  graph->index_of_last_node++;

  return new_node;
}

void add_edge(Graph *graph, Node *from, Node *to, int weight) {
  int new_edge_index = graph->index_of_last_edge + 1;

  Edge *new_edge = malloc(sizeof(Edge));
  new_edge->from = from;
  new_edge->to = to;
  new_edge->weight = weight;

  graph->edges[new_edge_index] = new_edge;
  graph->index_of_last_edge = new_edge_index;
}

void print_graph(Graph *graph) {
  for (int i = 0; i <= graph->index_of_last_edge; i++) {
    Edge *current = graph->edges[i];
    if (current != NULL) {
      printf("%c => %c ; %d\n", current->from->name, current->to->name,
             current->weight);
    }
  }
}

// mst == minimal spanning tree
Graph *boruvka_mst(Graph *input_graph) {
  Graph *minimum_spanning_tree = create_graph();

  int number_of_nodes = input_graph->index_of_last_node + 1;

  int *components = malloc(number_of_nodes * sizeof(int));
  int *cheapest = malloc(number_of_nodes * sizeof(int));
  int *cheapest_edge = malloc(number_of_nodes * sizeof(int));
  int *tree = malloc(number_of_nodes * sizeof(int));

  for (int i = 0; i < number_of_nodes; i++) {
    components[i] = i;
    cheapest[i] = INT_MAX;
    cheapest_edge[i] = -1;
    tree[i] = i;
  }

  while (number_of_nodes > 1) {
    int new_component_count = 0;
    int *new_components = malloc(number_of_nodes * sizeof(int));
    for (int i = 0; i < number_of_nodes; i++) {
      if (tree[i] == i) {
        new_components[new_component_count++] = components[i];
      }
    }

    for (int i = 0; i < number_of_nodes; i++) {
      Edge *current_edge = input_graph->edges[i];
      int u = components[current_edge->from->index];
      int v = components[current_edge->to->index];
      int w = current_edge->weight;
      if (u != v) {
        if (w < cheapest[u]) {
          cheapest[u] = w;
          cheapest_edge[u] = i;
        }
        if (w < cheapest[v]) {
          cheapest[v] = w;
          cheapest_edge[v] = i;
        }
      }
    }

    for (int i = 0; i < new_component_count; i++) {
      if (cheapest_edge[i] != -1) {
        minimum_spanning_tree->edges[number_of_nodes - 2] =
            input_graph->edges[cheapest_edge[i]];

        int u = components[input_graph->edges[cheapest_edge[i]]->from->index];
        int v = components[input_graph->edges[cheapest_edge[i]]->to->index];
        if (u != v) {
          for (int j = 0; j < number_of_nodes; j++) {
            if (components[j] == v) {
              components[j] = u;
            }
          }
        }
        number_of_nodes--;
      }
    }

    for (int i = 0; i < number_of_nodes; i++) {
      tree[i] = components[i];
    }

    free(new_components);
  }

  free(components);
  free(cheapest);
  free(cheapest_edge);
  free(tree);

  return minimum_spanning_tree;
}
