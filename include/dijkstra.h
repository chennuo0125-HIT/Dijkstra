#pragma once
#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Node
{
    int idx;
    double weight;
    Node *next;
    Node() : next(nullptr) {}
    Node(int idx, double weight) : idx(idx), weight(weight), next(nullptr) {}
};

struct Edge
{
    int idx1;
    int idx2;
    double weight;
};

struct VisNode
{
    int idx;
    double length;
    VisNode() {}
    VisNode(int idx, double length) : idx(idx), length(length) {}
    friend bool operator<(VisNode n1, VisNode n2) { return n1.length > n2.length; }
};

struct AdjacentList
{
    vector<Node> nodes;

    AdjacentList() : nodes(0) {}
    AdjacentList(int nodes_num, const vector<Edge> &edges);
    ~AdjacentList();
};

class Dijkstra
{
public:
    Dijkstra() {}
    Dijkstra(int nodes_num, const vector<Edge> &edges);

    void planPath(int sidx, int eidx, double &length, list<int> &passed_nodes);

private:
    AdjacentList alist_;
};
