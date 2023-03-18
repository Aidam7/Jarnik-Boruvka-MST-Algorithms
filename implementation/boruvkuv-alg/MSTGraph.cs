namespace boruvkuv_alg
{
    public class MSTGraph
    {
        private readonly int number_of_nodes;
        private readonly List<Edge> edges = new List<Edge>();

        public MSTGraph(int _number_of_nodes)
        {
            number_of_nodes = _number_of_nodes;
        }

        public void AddEdge(int from, int to, int weight) => edges.Add(new Edge(from, to, weight));

        public List<Edge> BoruvkaMST()
        {
            List<Edge> MST = new List<Edge>();

            // Create a parent array to keep track of components
            int[] parent = new int[number_of_nodes];
            for (int i = 0; i < number_of_nodes; i++) {
                parent[i] = i;
            }

            // Loop until there is only one component left
            while (MST.Count < number_of_nodes - 1) {
                // Create an array to keep track of the minimum edge for each component
                int[] minEdge = new int[number_of_nodes];
                for (int i = 0; i < number_of_nodes; i++) {
                    minEdge[i] = -1;
                }

                // Find the minimum-weight edge for each component
                for (int i = 0; i < edges.Count; i++) {
                    int current_from = edges[i].From;
                    int current_to = edges[i].To;
                    int current_weight = edges[i].Weight;

                    int set1 = find_parent_node(parent, current_from);
                    int set2 = find_parent_node(parent, current_to);

                    if (set1 == set2) {
                        // The vertices are already in the same component
                        continue;
                    }

                    if (minEdge[set1] == -1 || current_weight < edges[minEdge[set1]].Weight) {
                        minEdge[set1] = i;
                    }

                    if (minEdge[set2] == -1 || current_weight < edges[minEdge[set2]].Weight) {
                        minEdge[set2] = i;
                    }
                }

                // Add the minimum-weight edges to the MST
                for (int i = 0; i < number_of_nodes; i++) {
                    if (minEdge[i] != -1) {
                        int current_from = edges[minEdge[i]].From;
                        int current_to = edges[minEdge[i]].To;
                        int current_weight = edges[minEdge[i]].Weight;

                        int set1 = find_parent_node(parent, current_from);
                        int set2 = find_parent_node(parent, current_to);

                        if (set1 != set2) {
                            MST.Add(new Edge(current_from, current_to, current_weight));
                            parent[set1] = set2;
                        }
                    }
                }
            }

            return MST;
        }

        // Find the parent of a node in the parent array
        private int find_parent_node(int[] parent, int i) => parent[i] == i ? i : (parent[i] = find_parent_node(parent, parent[i]));
    }
}
