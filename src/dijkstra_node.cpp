#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include "dijkstra.h"

using namespace std;

void readEdge(ifstream &in_file, vector<Edge> &edges, map<string, int> &nodes_map)
{
    edges.clear();
    nodes_map.clear();

    string line;
    while (getline(in_file, line))
    {
        stringstream ss(line);
        string sid, tid;
        double weight;
        ss >> sid;
        ss >> tid;
        ss >> weight;

        // add new node
        if (nodes_map.find(sid) == nodes_map.end())
            nodes_map.insert(pair<string, int>(sid, nodes_map.size()));
        if (nodes_map.find(tid) == nodes_map.end())
            nodes_map.insert(pair<string, int>(tid, nodes_map.size()));

        // add new edge
        Edge edge;
        edge.idx1 = nodes_map.find(sid)->second;
        edge.idx2 = nodes_map.find(tid)->second;
        edge.weight = weight;
        edges.push_back(edge);
    }

    // debug
    // cout << "map:" << endl;
    // for (auto it = nodes_map.begin(); it != nodes_map.end(); it++)
    // {
    //     cout << it->first << " -> " << it->second << endl;
    // }
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "please input: rosrun bim plan_path_node edges_file start_node target_node !!!" << endl;
        return 0;
    }

    // read local edge
    vector<Edge> edges;
    map<string, int> nodes_map;
    ifstream in_file(argv[1]);
    if (!in_file.is_open())
    {
        cout << "cant open file " << argv[1] << endl;
        return 0;
    }
    readEdge(in_file, edges, nodes_map);
    cout << "total nodes size " << nodes_map.size() << ", edges size " << edges.size() << endl;

    // search start and end node index
    int sidx, tidx;
    if (nodes_map.find(argv[2]) == nodes_map.end())
    {
        cout << "cant find node " << argv[2] << " in edge file !!!" << endl;
        return 0;
    }
    if (nodes_map.find(argv[3]) == nodes_map.end())
    {
        cout << "cant find node " << argv[3] << " in edge file !!!" << endl;
        return 0;
    }
    sidx = nodes_map.find(argv[2])->second;
    tidx = nodes_map.find(argv[3])->second;
    cout << "start node " << argv[2] << " -> " << sidx << endl;
    cout << "end node " << argv[3] << " -> " << tidx << endl;

    // plan
    double length;
    list<int> passed_nodes;
    Dijkstra planner(nodes_map.size(), edges); //instantiation planner
    planner.planPath(sidx, tidx, length, passed_nodes);

    // recover index to nodes name
    map<int, string> inv_nodes_map;
    for (auto it = nodes_map.begin(); it != nodes_map.end(); it++)
        inv_nodes_map.insert(pair<int, string>(it->second, it->first));

    cout << "path length is " << length << endl;
    cout << "passed node: ";
    for (auto it = passed_nodes.begin(); it != passed_nodes.end(); it++)
        cout << inv_nodes_map.find(*it)->second << " ";
    cout << endl;

    return 0;
}