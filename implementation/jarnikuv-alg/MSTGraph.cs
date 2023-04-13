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
            List<Edge> MST = new List<Edge>();
            var queue = new List<Edge>();
            foreach (var edge in edges)
            {
                queue.Add(edge);
            }
            queue = queue.OrderBy(x => x.Weight).ToList();
            int i = 0;
            while (queue.Count > 0)
            {
                List<Edge> destinations = new List<Edge>();
                destinations.AddRange(queue.Where(x => x.From == i).ToList());
                if (destinations.Count == 0)
                {
                    destinations.AddRange(queue.Where(x => x.To == i).ToList());
                }

                if (destinations.Count == 0)
                {
                    i = MST[MST.Count - 1].From;
                    break;
                }
                i = destinations[0].To;
                queue.Remove(destinations[0]);
                MST.Add(destinations[0]);
            }
            return MST;
        }

        // Find the parent of a node in the parent array
        private int find_parent_node(int[] parent, int i) => parent[i] == i ? i : (parent[i] = find_parent_node(parent, parent[i]));
    }
}
