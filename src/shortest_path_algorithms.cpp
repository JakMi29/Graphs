#include "graphs/shortest_path_algorithms.hpp"
typedef std::pair<int, Vertex*> iPair;
//int INT_MAX=1000000000;
void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    result.insert(std::make_pair(sourceIndex, std::make_pair(0, std::vector<int>{sourceIndex})));
    Vertex* source;
    std::map<int, bool> visited;
    std::map<int, int> dist;

    for(const auto& item : graph.getVertexList())
    {
        if(item->getValue() == sourceIndex)
            source = item;
        visited.insert(std::make_pair(item->getValue(), false));
        dist.insert(std::make_pair(item->getValue(), INT_MAX));
    }
    dist[sourceIndex] = 0;
    std::priority_queue<iPair, std::vector<iPair>, std::greater<>> pq;
    pq.emplace(0, source);

    while(!pq.empty())
    {
        Vertex* vertex = pq.top().second;
        pq.pop();
        int i = vertex->getValue();
        for(const auto& item : graph.incidentEdges(vertex))
        {
            if(item->getWeight() + dist[i] < dist[item->getEndVertex()->getValue()] && !visited[i] &&
               dist[i] != INT_MAX)
            {
                dist[item->getEndVertex()->getValue()] = item->getWeight() + dist[i];
                if(result.find(item->getEndVertex()->getValue()) != result.end())
                {
                    result.erase(item->getEndVertex()->getValue());
                    result.insert(
                        std::make_pair(item->getEndVertex()->getValue(),
                                       std::make_pair(dist[item->getEndVertex()->getValue()], std::vector<int>{})));

                        result[item->getEndVertex()->getValue()].second=result[i].second;

                    result[item->getEndVertex()->getValue()].second.push_back(item->getEndVertex()->getValue());
                }
                else
                {
                    result.insert(
                        std::make_pair(item->getEndVertex()->getValue(),
                                       std::make_pair(dist[item->getEndVertex()->getValue()], std::vector<int>{})));

                    result[item->getEndVertex()->getValue()].second=result[i].second;

                    result[item->getEndVertex()->getValue()].second.push_back(item->getEndVertex()->getValue());
                }
                if(!visited[i])
                    pq.emplace(dist[item->getEndVertex()->getValue()], item->getEndVertex());
            }
        }
        visited[i] = true;
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    result.insert(std::make_pair(sourceIndex, std::make_pair(0, std::vector<int>{sourceIndex})));
    std::map<int, int> dist;

    for(const auto& item : graph.getVertexList())
    {
        if(item->getValue() == sourceIndex)
            dist.insert(std::make_pair(item->getValue(), INT_MAX));
    }
    result.insert(std::make_pair(sourceIndex, std::make_pair(0, std::vector<int>{sourceIndex})));

    for(const auto& item : graph.getVertexList())
    {
        dist.insert(std::make_pair(item->getValue(), INT_MAX));
    }
    dist[sourceIndex] = 0;

    for(int i = 0; i < graph.getVertexList().size(); i++)
    {
        for(const auto& item : graph.edges())
        {
            int u = item->getBeginVertex()->getValue();
            int v = item->getEndVertex()->getValue();
            int weight = item->getWeight();

            if(dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[item->getEndVertex()->getValue()] = item->getWeight() + dist[u];
                if(result.find(item->getEndVertex()->getValue()) != result.end())
                {
                    result.erase(item->getEndVertex()->getValue());
                    result.insert(
                        std::make_pair(item->getEndVertex()->getValue(),
                                       std::make_pair(dist[item->getEndVertex()->getValue()], std::vector<int>{})));
                    result[item->getEndVertex()->getValue()].second=result[u].second;
                    result[item->getEndVertex()->getValue()].second.push_back(item->getEndVertex()->getValue());
                }
                else
                {
                    result.insert(
                        std::make_pair(item->getEndVertex()->getValue(),
                                       std::make_pair(dist[item->getEndVertex()->getValue()], std::vector<int>{})));
                    result[item->getEndVertex()->getValue()].second=result[u].second;
                    result[item->getEndVertex()->getValue()].second.push_back(item->getEndVertex()->getValue());
                }
            }
        }
    }


        for(const auto& item : graph.edges())
        {
            int u = item->getBeginVertex()->getValue();
            int v = item->getEndVertex()->getValue();
            int weight = item->getWeight();
        if(dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            printf("Graph contains negative weight cycle");
            return false;
        }
    }
    return true;
}


