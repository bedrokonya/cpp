#include<iostream>
#include<vector>

using namespace std;
class Edge
{
public:
    int dest; // Куда ведет ребро
    int start_time; // во сколько автобус отправляется
    int finish_time; // во сколько автобус приходит
};
vector<vector<Edge>> graph;
vector<int> dist; // Кратчайшие расстояния от стартовой вершины
vector<int> used;
int main() {
    int n; // Количество городов
    int departure_time, start_city, finish_city, m; // m - количество рейсов, start - город, из которого отправляется, departure_time - когда из этого города отправляется, finish - город, в который он собирается ехать
    cout << "Enter the number of cities:\n";
    cin >> n;
    cout << "Enter the departure time:\n";
    cin >> departure_time;
    cout << "Enter the start city:\n";
    cin >> start_city;
    cout << "Enter the finish city:\n";
    cin >> finish_city;
    cout << "Enter the number of journeys:\n";
    cin >> m;
    graph.resize(n + 1);
    dist.resize(n + 1);
    used.resize(n + 1);
    cout << "Enter the data about races:\n";
    for (int i = 0; i < m; ++i) {
        int from, dest, st, fin;
        cin >> from >> dest >> st >> fin;
        graph[from].push_back(Edge{dest, st, fin});
    }
    // Инициализируем все расстояния "бесконечностями"
    for (int i = 1; i <= n; ++i) {
        dist[i] = 200000000;
    }
    
    dist[start_city] = departure_time;
    for (int i = 0; i < n; ++i) {
        int min = 2000000000;
        int pos = -1;
        for (int j = 1; j <= n; ++j) {
            if (dist[j] < min && used[j] == 0) {
                min = dist[j];
                pos = j;
            }
        }
        used[pos] = 10;
        for (int j = 0; j < graph[pos].size(); ++j) {
            if (min <= graph[pos][j].start_time && dist[graph[pos][j].dest] > graph[pos][j].finish_time) {
                dist[graph[pos][j].dest] = graph[pos][j].finish_time;
            }
        }
    }
    cout << "The least time at which you can arrive:\n"<< dist[finish_city] << " o'clock\n";
    
    return 0;
}