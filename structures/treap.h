#pragma once

struct TreapNode
{
    int key;
    double priority;
    TreapNode *left, *right;
    TreapNode(int k);
};

class Treap
{
public:
    Treap();
    ~Treap();

    TreapNode *insert(TreapNode *t, int key);
    TreapNode *del(TreapNode *t, int key);
    TreapNode *find(int key);

private:
    TreapNode *root;
    void rotateRight(TreapNode *&y);
    void rotateLeft(TreapNode *&y);
    void deleteSubtree(TreapNode *t);
};
