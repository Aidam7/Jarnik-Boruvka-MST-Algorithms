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
            /*
             * node[] jarnikAlgorithm(graph, weight)
                Queue q //fronta
                q.addAllVetices(graph.vertices) //pridej vsechny uzly do fronty
    
                distances = new int[q.size()] //pole vzdalenosti
                distances[0] = 0 //koren
                for i in 1 -> distances.length - 1 do                                 
                    distances[i] = +inf //ostatni uzly jsou nekonecne daleko
     
                predecessors = new node[q.size()] //pole predchudcu
                predecessors[0] = null //koren nema predchudce
    
                while !queue.empty() do //dokud neni fronta prazdna
                    u = queue.extractMin() //vrat prvek v minimalni vzdalenosti
                    for node in descendants(u) do //pro vsechny potomky u
                        if queue.contains(node) AND weight(u, node) < d[node] //pokud se nektery z potomku priblizil k dosud postavene kostre
                            then predecessors[node] = u //u je tedy jeho predek
                                 d[node] = weight(u, node) //nastav nvou vzdalenost    
    
                return predecessors //vrat pole predchudcu
             */



            List<Edge> MST = new List<Edge>();

            // Create a parent array to keep track of components
            int[] parent = new int[number_of_nodes];
            for (int i = 0; i < number_of_nodes; i++)
            {
                parent[i] = i;
            }

            return MST;
        }

        // Find the parent of a node in the parent array
        private int find_parent_node(int[] parent, int i) => parent[i] == i ? i : (parent[i] = find_parent_node(parent, parent[i]));
    }
}
