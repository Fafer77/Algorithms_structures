#include "treap.h"
#include <random>
using namespace std;

static mt19937 rng(random_device{}());
static double randomPriority()
{
    uniform_real_distribution<double> dist(0.0, 1.0);
}

TreapNode::TreapNode(int k) : key(k), priority(randomPriority()),
                              left(nullptr), right(nullptr) {}

Treap::Treap() : root(nullptr) {}
Treap::~Treap() { deleteSubtree(root); }

void Treap::deleteSubtree(TreapNode *t)
{
    if (!t)
        return;
    deleteSubtree(t->left);
    deleteSubtree(t->right);
    delete t;
}

TreapNode *Treap::find(int key)
{
    TreapNode *curr = root;
    while (curr != nullptr && curr->key != key)
    {
        if (key > curr->key)
            curr = curr->right;
        else
            curr = curr->left;
    }
    return curr;
}

void Treap::rotateRight(TreapNode *&y)
{
    TreapNode *x = y->left;
    y->left = x->right;
    x->right = y;
    y = x;
}

void Treap::rotateLeft(TreapNode *&y)
{
    TreapNode *x = y->right;
    y->right = x->left;
    x->left = y;
    y = x;
}

TreapNode *Treap::insert(TreapNode *t, int key)
{
    if (!t)
        return new TreapNode(key);

    if (key < t->key)
    {
        t->left = insert(t->left, key);
        if (t->left->priority > t->priority)
            rotateRight(t);
    }
    else if (key > t->key)
    {
        t->right = insert(t->right, key);
        if (t->right->priority > t->priority)
            rotateLeft(t);
    }

    return t;
}

TreapNode *Treap::del(TreapNode *t, int key)
{
    if (!t)
        return t;

    if (key < t->key)
        del(t->left, key);
    else if (key > t->key)
        del(t->right, key);
}
