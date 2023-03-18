using System;
using System.Collections.Generic;

namespace boruvkuv_alg
{
    internal class Program
    {
        static void Main()
        {
            MSTGraph graph = new MSTGraph(6);

            graph.AddEdge(0, 1, 4);
            graph.AddEdge(0, 2, 3);
            graph.AddEdge(1, 2, 1);
            graph.AddEdge(1, 3, 2);
            graph.AddEdge(2, 3, 4);
            graph.AddEdge(3, 4, 2);
            graph.AddEdge(4, 5, 6);

            var MinimumSpanningTree = graph.BoruvkaMST();

            Console.WriteLine("Minimum spanning tree:");
            foreach (Edge edge in MinimumSpanningTree)
            {
                Console.WriteLine($"{edge.From} - {edge.To} ({edge.Weight})");
            }
        }
    }
}
