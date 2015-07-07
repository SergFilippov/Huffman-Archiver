#ifndef NODE_H
#define NODE_H

class Node
{
public:
    char byte;
    int count;
    Node* left;
    Node* right;
    Node()
        : left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r)
    {
        left = l;
        right = r;
        count = l->count + r->count;
    }
};

#endif // NODE_H
