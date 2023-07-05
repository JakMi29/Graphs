#include "catch2/catch.hpp"
#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"
#include "graphs/shortest_path_algorithms.hpp"
#include "graphs/vertices/list_vertex.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
void createRandomGraph(int vertices, int filling)
{

    for(int amount = 0; amount < 1; amount++)
    {
        std::string sciezka =
            "C:\\\\Users\\\\jakub\\\\OneDrive\\\\Pulpit\\\\graf (4)\\\\graf\\\\PAMSIGrafy\\\\sprawozdanie\\\\";
        sciezka += std::to_string(amount);
        sciezka += ".txt";
        std::ofstream plik(sciezka);
        std::vector<std::vector<int>> lists;

        for(int i = 0; i < vertices; i++)
        {
            std::vector<int> innerVector;
            for(int j = 0; j < vertices; j++)
            {
                innerVector.push_back(j);
            }
            lists.push_back(innerVector);
        }
        if(plik.is_open())
        {
            int amountOfEdges = (int)vertices * (vertices - 1) * filling / 100;
            plik << vertices << " " << amountOfEdges << std::endl;
            int a, b, c;
            for(int i = 0; i < amountOfEdges; i++)
            {
                a = std::rand() % vertices;
                c = std::rand() % 1000;
                std::random_shuffle(lists[a].begin(), lists[a].end());
                b = lists[a].front();
                std::remove(lists[a].begin(), lists[a].end(), b);
                plik << a << " " << b << " " << c << std::endl;
            }
        }
    }
}
void testDijkstra(int vertices, int lista)
{
    Graph* graph;
    ShortestPathResult result;
    for(int amount = 0; amount < 1; amount++)
    {
        std::string sciezka =
            "C:\\\\Users\\\\jakub\\\\OneDrive\\\\Pulpit\\\\graf (4)\\\\graf\\\\PAMSIGrafy\\\\sprawozdanie\\\\";
        sciezka += std::to_string(amount);
        sciezka += ".txt";
        for(int q = 0; q < vertices; q++)
        {
            std::ifstream inputFile(sciezka);
            if(lista)
                graph = new AdjacencyListGraph(inputFile);
            else
                graph = new AdjacencyMatrixGraph(inputFile);
            dijkstra(*graph, q, result);
            delete graph;
        }
    }
}
void testBellman(int vertices, int lista)
{
    Graph* graph;
    ShortestPathResult result;
    for(int amount = 0; amount < 1; amount++)
    {
        std::string sciezka =
            "C:\\\\Users\\\\jakub\\\\OneDrive\\\\Pulpit\\\\graf (4)\\\\graf\\\\PAMSIGrafy\\\\sprawozdanie\\\\";
        sciezka += std::to_string(amount);
        sciezka += ".txt";
        for(int q = 0; q < vertices; q++)
        {
            std::ifstream inputFile(sciezka);
            if(lista)
                graph = new AdjacencyListGraph(inputFile);
            else
                graph = new AdjacencyMatrixGraph(inputFile);
            bellmanFord(*graph, q, result);
            delete graph;
        }
    }
}
void menu()
{
    int a, b, c, d;
    int choice;
    std::string path;
    while(choice != 1 && choice != 2)
    {
        std::cout << "Enter file path to create graph" << std::endl;
        std::getline(std::cin, path);
        std::cout << "Choose graph implementation;" << std::endl;
        std::cout << "1. adjacency List." << std::endl;
        std::cout << "2. adjacency Matrix." << std::endl;
        std::cin >> choice;
    }
    size_t pozycja = 0;
    while((pozycja = path.find('\\', pozycja)) != std::string::npos)
    {
        path.replace(pozycja, 1, "\\\\");
        pozycja += 2;
    }
    std::cout << path;
    std::ifstream inputFile(path);
    Graph* graph;
    switch(choice)
    {
        case 1:
            graph = new AdjacencyMatrixGraph(inputFile);
            break;
        case 2:
            graph = new AdjacencyListGraph(inputFile);
            break;
        default:
            std::cout << "bład";
            break;
    }
    while(choice != 15)
    {
        std::cout << "Choose graph implementation;" << std::endl;
        std::cout << "1. Print graph." << std::endl;
        std::cout << "2. Remove edge." << std::endl;
        std::cout << "3. Remove vertex." << std::endl;
        std::cout << "4. Add edge." << std::endl;
        std::cout << "5. Add vertex." << std::endl;
        std::cout << "6. End edge vertices ." << std::endl;
        std::cout << "7. Opposite vertex to vertex relative by edge." << std::endl;
        std::cout << "8. Are two vertices adjacent." << std::endl;
        std::cout << "9. Replace vertex value." << std::endl;
        std::cout << "10. Replace edge weight." << std::endl;
        std::cout << "11. Show all edges." << std::endl;
        std::cout << "12. Show all vertices." << std::endl;
        std::cout << "13. Show incident edges to vertex." << std::endl;
        std::cout << "14. Shortest path." << std::endl;
        std::cout << "15. Exit." << std::endl;
        std::cin >> choice;
        switch(choice)
        {
            case 1:
                graph->print();
                break;
            case 2:
                std::cout << "Podaj początek, koniec oraz wagę krawędzi" << std::endl;
                std::cin >> a >> b >> c;
                graph->userRequiredToRemoveEdge(a, b, c);
                break;
            case 3:
                std::cout << "Podaj wartość wierzchołka dp usunięcia" << std::endl;
                std::cin >> a;
                graph->userRequiredToRemoveVertex(a);
                break;
            case 4:
                std::cout << "Podaj wartośc wierzchołka początkowego, końcowego oraz wagę krawędzi" << std::endl;
                std::cin >> a >> b >> c;
                graph->userRequiredToAddEdge(a, b, c);
                break;
            case 5:
                std::cout << "Podaj wartość wierzchołka, który chcesz dodać" << std::endl;
                std::cin >> a;
                graph->userRequiredToAddVertex(a);
                break;
            case 6:
                std::cout << "Podaj wartości krawędzi aby odczytać wierzchołek początkowqy i końcowy" << std::endl;
                std::cin >> a >> b >> c;
                graph->userRequiredToEndVertices(a, b, c);
                break;
            case 7:
                std::cout << "Podaj wartość wierzchołka oraz krawędz aby zobaczyc przeciwlely wierzchołek" << std::endl;
                std::cin >> a >> b >> c >> d;
                graph->userRequiredToOpposite(a, b, c, d);
                break;
            case 8:
                std::cout << "Podaj wartości wierzchołków, aby dowiedzieć czy z pierwszego wychodzi krawędz do drugiego"
                          << std::endl;
                std::cin >> a >> b;
                graph->userRequiredToAreAdjacent(a, b);
                break;
            case 9:
                std::cout << "Podaj wartośc wierzchołka oraz jego nową martość" << std::endl;
                std::cin >> a >> b;
                graph->userRequiredToEditVertex(a, b);
                break;
            case 10:
                std::cout << "  wage oraz nową wagę krawędzi" << std::endl;
                std::cin >> a >> b >> c >> d;
                graph->userRequiredToEditEdge(a, b, c, d);
                break;
            case 11:
                graph->userRequiredEdges();
                break;
            case 12:
                graph->userRequiredVertices();
                break;
            case 13:
                std::cout << "podaj wierzcholek aby zobaczyc wychodzące krawedzie" << std::endl;
                std::cin >> a;
                graph->userRequiredVertexIncidentList(a);
                break;
            case 14:
            {
                ShortestPathResult result;
                int choice2;
                int vertex;
                std::cout << "wybierz algorytm z ktorego chcesz skorzystac:" << std::endl;
                std::cout << "1. Dijkstra:" << std::endl;
                std::cout << "2. Bellman-Ford" << std::endl;
                std::cin>>choice2;
                std::cout << "wybierz wierzcholek z ktorego dla którego chcesz znac najkrotsze sciezki" << std::endl;
                std::cin>>vertex;

                for(const auto& item : graph->vertices())
                {
                    if(item->getValue() == vertex)
                    {
                        if(choice2==1)
                        {
                            dijkstra((*graph),vertex,result);
                        }
                        else
                        {
                            bellmanFord((*graph),vertex,result);
                        }

                        for(const auto& result1 : result)
                        {
                            std::cout<<result1.first<<" "<<result1.second.first<<" ";
                            for(const auto & second : result1.second.second)
                            {
                                std::cout<< second<<" ";
                            }
                            std::cout<<std::endl;
                        }
                    }
                }
                std::cout<<"w grafie nie ma takiego wierzcholka"<<std::endl;}
                break;
            case 15:
                break;
            default:
                std::cout << "Wrong choice";
                break;
        }
    }
    delete graph;
}
void sprawko(){
    std::list<int> list = {25, 50, 75, 100};

    for(const auto& item : list)
    {
        for(int i = 0; i < 2; i++)
        {
            createRandomGraph(10, item);
            auto start = clock();
            testDijkstra(10, i);
            auto stop = clock();
            auto duration = (double)(stop - start) / (double)CLOCKS_PER_SEC;
            std::cout << "Graph with " << 10 << " vertices, filling: " << item
                      << ", graph implementation: " << ((i != 1) ? "adjacencyMatrix" : "adjacencyList");
            std::cout << ", algorithm: dijkstra time: " << std::fixed << duration << std::setprecision(8) << "s"
                      << std::endl;
            start = clock();
            testBellman(10, i);
            stop = clock();
            duration = (double)(stop - start) / (double)CLOCKS_PER_SEC;
            std::cout << "Graph with" << 10 << " vertices, filling: " << item << " "
                      << "graph implementation: " << ((i != 1) ? "adjacencyMatrix" : "adjacencyList");
            std::cout << ", algorithm: bellman time: " << std::fixed << duration << std::setprecision(8) << "s"
                      << std::endl;
        }
    }
}
int main(int argc, char* argv[])
{
    menu();
}
