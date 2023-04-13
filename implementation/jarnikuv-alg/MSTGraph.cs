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
            HashSet<int> visited = new HashSet<int> {
                0
            };

            while (visited.Count < number_of_nodes)
            {
                Edge? minEdge = null;
                foreach (Edge edge in edges) {
                    if (visited.Contains(edge.From) && !visited.Contains(edge.To)) {
                        if (minEdge == null || edge.Weight < minEdge.Weight) {
                            minEdge = edge;
                        }
                    }
                    else if (visited.Contains(edge.To) && !visited.Contains(edge.From)) {
                        if (minEdge == null || edge.Weight < minEdge.Weight) {
                            minEdge = edge;
                        }
                    }
                }

                if (minEdge == null) {
                    throw new Exception("Fuck");
                }

                minimumSpanningTree.Add(minEdge);
                visited.Add(minEdge.From);
                visited.Add(minEdge.To);
            }

            return minimumSpanningTree;
        }
    }
}
