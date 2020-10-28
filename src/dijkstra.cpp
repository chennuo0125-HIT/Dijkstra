#include <queue>
#include <limits>
#include "dijkstra.h"

AdjacentList::AdjacentList(int nodes_num, const vector<Edge> &edges)
{
    nodes.resize(nodes_num);
    nodes.reserve(nodes_num);

    // set default nodes
    for (int i = 0; i < nodes_num; i++)
    {
        nodes[i].idx = i;
        nodes[i].weight = -1.0;
        nodes[i].next = NULL;
    }

    // insert edge
    for (int i = 0; i < edges.size(); i++)
    {
        Node *last_next = nodes[edges[i].idx1].next;
        Node *node = new Node(edges[i].idx2, edges[i].weight);
        nodes[edges[i].idx1].next = node;
        node->next = last_next;

        Node *last_next1 = nodes[edges[i].idx2].next;
        Node *node1 = new Node(edges[i].idx1, edges[i].weight);
        nodes[edges[i].idx2].next = node1;
        node1->next = last_next1;
    }

    // debug for view adjacent list whether is ok
    // for (int i = 0; i < nodes.size(); i++)
    // {
    //     cout << "node " << i << " : ";
    //     Node *node = nodes[i].next;
    //     while (node)
    //     {
    //         cout << node->idx << " ";
    //         node = node->next;
    //     }
    //     cout << endl;
    // }
}

AdjacentList::~AdjacentList()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        Node *node = nodes[i].next;
        while (node)
        {
            Node *next = node->next;
            delete node;
            node = nullptr;
            node = next;
        }
    }
}

Dijkstra::Dijkstra(int nodes_num, const vector<Edge> &edges) : alist_(nodes_num, edges) {}

void Dijkstra::planPath(int sidx, int eidx, double &length, list<int> &passed_nodes)
{
    vector<int> parents(alist_.nodes.size(), -1);                               // record parent node for each node
    vector<double> lengths(alist_.nodes.size(), numeric_limits<double>::max()); // record all node's smallest path
    vector<bool> visited(alist_.nodes.size(), false);                           // record whether the node has achieved
    priority_queue<VisNode> vis_nodes;                                          // record visiting node

    // init by start index
    parents[sidx] = -1;
    lengths[sidx] = 0;
    vis_nodes.push(VisNode(sidx, 0));

    // update node state
    while (vis_nodes.size() != 0)
    {
        // get min length node
        VisNode vis_node = vis_nodes.top();
        vis_nodes.pop();
        if (visited[vis_node.idx])
            continue;
        visited[vis_node.idx] = true;
        // cout << "visited node " << vis_node.idx << " length is " << lengths[vis_node.idx] << endl;

        // arrive target
        if (vis_node.idx == eidx)
            break;

        // update visit nodes , lengths, and parents
        Node *node = alist_.nodes[vis_node.idx].next;
        while (node)
        {
            if (!visited[node->idx] && lengths[node->idx] > lengths[vis_node.idx] + node->weight)
            {
                lengths[node->idx] = lengths[vis_node.idx] + node->weight;
                parents[node->idx] = vis_node.idx;
            }

            vis_nodes.push(VisNode(node->idx, lengths[node->idx]));

            node = node->next;
        }
    }

    // extract result
    length = lengths[eidx];
    passed_nodes.push_back(eidx);
    int parent = parents[eidx];
    while (parent >= 0)
    {
        passed_nodes.push_front(parent);
        parent = parents[parent];
    }
}