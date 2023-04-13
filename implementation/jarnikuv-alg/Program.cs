namespace jarnikuv_alg
{
    internal class Program
    {
        static void Main(string[] args)
        {/*
                    0
                   / \
                  1 - 2
                 /   / \
                3   4 - 5
                 \ /
                  6
            */
            MSTGraph graph = new MSTGraph(7);

            graph.AddEdge(0, 1, 4);
            graph.AddEdge(0, 2, 3);

            graph.AddEdge(1, 2, 5);
            graph.AddEdge(1, 3, 2);

            graph.AddEdge(2, 4, 8);
            graph.AddEdge(2, 5, 1);

            graph.AddEdge(3, 6, 8);

            graph.AddEdge(4, 5, 6);
            graph.AddEdge(4, 6, 2);

            List<Edge> MinimumSpanningTree = graph.JarnikMST();

            Console.WriteLine("Minimum spanning tree:");
            foreach (Edge edge in MinimumSpanningTree)
            {
                Console.WriteLine($"{edge.From} - {edge.To} ({edge.Weight})");
            }
        }
    }
}