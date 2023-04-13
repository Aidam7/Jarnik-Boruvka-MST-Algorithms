namespace jarnikuv_alg
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

        public List<Edge> JarnikMST()
        {
            List<Edge> minimumSpanningTree = new List<Edge>();
            bool[] visited = new bool[number_of_nodes * 2];
            visited[0] = true;

            int visited_count = 1;
            while (visited_count < number_of_nodes) {
                Edge? minEdge = null;
                foreach (Edge edge in edges) {
                    if (visited[edge.From] && !visited[edge.To]) {
                        if (minEdge == null || edge.Weight < minEdge.Weight) {
                            minEdge = edge;
                        }
                    }
                    else if (visited[edge.To] && !visited[edge.From]) {
                        if (minEdge == null || edge.Weight < minEdge.Weight) {
                            minEdge = edge;
                        }
                    }
                }

                if (minEdge == null) {
                    throw new Exception("Tree is not connected.");
                }

                minimumSpanningTree.Add(minEdge);
                if (!visited[minEdge.From]) {
                    visited[minEdge.From] = true;
                    visited_count++;
                }
                if (!visited[minEdge.To]) {
                    visited[minEdge.To] = true;
                    visited_count++;
                }
            }

            return minimumSpanningTree;
        }
    }
}
