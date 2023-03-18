#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WEIGHT 100
#define NUMBER_OF_NODES 12

typedef int bool;
#define TRUE 1
#define FALSE 0

// Could be optimized by using ArrayList for neighbors and edge_weights;
typedef struct Node {
  char name;
  struct Node **neighbors; // Points to array of pointers
  int *edge_weights;
  int index_of_last_neighbor;
} Node;

Node *create_node(char node_name);
void add_neighbor(Node *node, Node *neighbor, int neighbor_weight);
void print_neigbors(Node *node);

// Node **boruvka_mst(Node **nodes, int num_nodes);
Node **boruvka_mst(Node **nodes, int num_nodes);

int main() {
  printf("Hello world!\n");

  // Create same structure as here
  // https://cs.wikipedia.org/wiki/Bor%C5%AFvk%C5%AFv_algoritmus
  // to be able to easily check results
  Node *A_NODE = create_node('A');
  Node *B_NODE = create_node('B');
  Node *C_NODE = create_node('C');
  Node *D_NODE = create_node('D');
  Node *E_NODE = create_node('E');
  Node *F_NODE = create_node('F');
  Node *G_NODE = create_node('G');
  Node *H_NODE = create_node('H');
  Node *I_NODE = create_node('I');
  Node *J_NODE = create_node('J');
  Node *K_NODE = create_node('K');
  Node *L_NODE = create_node('L');

  add_neighbor(A_NODE, B_NODE, 13);
  add_neighbor(A_NODE, C_NODE, 6);

  add_neighbor(B_NODE, A_NODE, 13);
  add_neighbor(B_NODE, C_NODE, 7);
  add_neighbor(B_NODE, D_NODE, 1);

  add_neighbor(C_NODE, A_NODE, 6);
  add_neighbor(C_NODE, B_NODE, 7);
  add_neighbor(C_NODE, D_NODE, 14);
  add_neighbor(C_NODE, E_NODE, 8);
  add_neighbor(C_NODE, H_NODE, 20);

  add_neighbor(D_NODE, B_NODE, 1);
  add_neighbor(D_NODE, C_NODE, 14);
  add_neighbor(D_NODE, E_NODE, 9);
  add_neighbor(D_NODE, F_NODE, 3);

  add_neighbor(E_NODE, C_NODE, 8);
  add_neighbor(E_NODE, D_NODE, 9);
  add_neighbor(E_NODE, F_NODE, 2);
  add_neighbor(E_NODE, J_NODE, 18);

  add_neighbor(F_NODE, D_NODE, 3);
  add_neighbor(F_NODE, E_NODE, 2);

  add_neighbor(G_NODE, H_NODE, 15);
  add_neighbor(G_NODE, I_NODE, 5);
  add_neighbor(G_NODE, K_NODE, 10);
  add_neighbor(G_NODE, J_NODE, 19);

  add_neighbor(H_NODE, C_NODE, 20);
  add_neighbor(H_NODE, G_NODE, 15);
  add_neighbor(H_NODE, J_NODE, 17);

  add_neighbor(I_NODE, G_NODE, 5);
  add_neighbor(I_NODE, K_NODE, 11);

  add_neighbor(J_NODE, H_NODE, 17);
  add_neighbor(J_NODE, G_NODE, 19);
  add_neighbor(J_NODE, K_NODE, 16);
  add_neighbor(J_NODE, L_NODE, 4);

  add_neighbor(K_NODE, L_NODE, 12);
  add_neighbor(K_NODE, J_NODE, 16);
  add_neighbor(K_NODE, G_NODE, 10);
  add_neighbor(K_NODE, I_NODE, 11);

  add_neighbor(L_NODE, K_NODE, 12);
  add_neighbor(L_NODE, J_NODE, 4);

  // print_neigbors(A_NODE);
  // print_neigbors(B_NODE);
  // print_neigbors(C_NODE);
  // print_neigbors(D_NODE);
  // print_neigbors(E_NODE);
  // print_neigbors(F_NODE);
  // print_neigbors(G_NODE);
  // print_neigbors(H_NODE);
  // print_neigbors(I_NODE);
  // print_neigbors(J_NODE);
  // print_neigbors(K_NODE);
  // print_neigbors(L_NODE);

  Node **node_collection = malloc(NUMBER_OF_NODES * sizeof(Node *));
  node_collection[0] = A_NODE;
  node_collection[1] = B_NODE;
  node_collection[2] = C_NODE;
  node_collection[3] = D_NODE;
  node_collection[4] = E_NODE;
  node_collection[5] = F_NODE;
  node_collection[6] = G_NODE;
  node_collection[7] = H_NODE;
  node_collection[8] = I_NODE;
  node_collection[9] = J_NODE;
  node_collection[10] = K_NODE;
  node_collection[11] = L_NODE;

  Node **final_mst = boruvka_mst(node_collection, NUMBER_OF_NODES);

  printf("f_node: %c", final_mst[0]->name);

  return 0;
}

Node *create_node(char node_name) {
  Node *new_node = malloc(sizeof(Node));

  new_node->name = node_name;

  // At worst, we could connect every node with every node
  // These two for loops could be replaced by memset
  new_node->neighbors = malloc(NUMBER_OF_NODES * sizeof(Node *));
  for (int i = 0; i < NUMBER_OF_NODES; i++) {
    new_node->neighbors[i] = NULL;
  }

  new_node->edge_weights = malloc(NUMBER_OF_NODES * sizeof(int));
  for (int i = 0; i < NUMBER_OF_NODES; i++) {
    new_node->edge_weights[i] = NULL;
  }

  new_node->index_of_last_neighbor = -1;
  return new_node;
}

void add_neighbor(Node *node, Node *neighbor, int neighbor_weight) {
  int new_number_of_neighbors = node->index_of_last_neighbor + 1;

  node->neighbors[new_number_of_neighbors] = neighbor;

  node->edge_weights[new_number_of_neighbors] = neighbor_weight;
  node->index_of_last_neighbor = new_number_of_neighbors;
}

// Depth-first
void print_neigbors(Node *node) {
  printf("%c has %d neighbors.\n", node->name,
         node->index_of_last_neighbor + 1);
  for (int i = 0; i <= node->index_of_last_neighbor; i++) {
    Node *neighbor = node->neighbors[i];
    int neighbor_edge_weight = node->edge_weights[i];
    printf("%c has neighbor %c with weight %d\n", node->name, neighbor->name,
           neighbor_edge_weight);
  }
  printf("\n");
}

// mst == minimal spanning tree
Node **boruvka_mst(Node **nodes, int number_of_nodes) {
  int number_of_mst_edges = 0;

  Node **mst_edges = malloc((number_of_nodes - 1) * sizeof(Node *));

  // Could be replaced by memset
  bool *is_in_mst = malloc(number_of_nodes * sizeof(bool));
  for (int i = 0; i < number_of_nodes; i++) {
    is_in_mst[i] = FALSE;
  }
}
