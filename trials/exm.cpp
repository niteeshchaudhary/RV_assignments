#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

class BinaryTree
{

private:
    string key;
    BinaryTree *leftChild;
    BinaryTree *rightChild;

public:
    BinaryTree(string rootObj)
    {
        this->key = rootObj;
        this->leftChild = NULL;
        this->rightChild = NULL;
    }

    void insertLeft(string newNode)
    {
        if (this->leftChild == NULL)
        {
            this->leftChild = new BinaryTree(newNode);
        }
        else
        {
            BinaryTree *t = new BinaryTree(newNode);
            t->leftChild = this->leftChild;
            this->leftChild = t;
        }
    }

    void insertRight(string newNode)
    {
        if (this->rightChild == NULL)
        {
            this->rightChild = new BinaryTree(newNode);
        }
        else
        {
            BinaryTree *t = new BinaryTree(newNode);
            t->rightChild = this->rightChild;
            this->rightChild = t;
        }
    }

    BinaryTree *getRightChild()
    {
        return this->rightChild;
    }

    BinaryTree *getLeftChild()
    {
        return this->leftChild;
    }

    void setRootVal(string obj)
    {
        this->key = obj;
    }

    string getRootVal()
    {
        return this->key;
    }
};

BinaryTree *buildParseTree(string fpexp)
{
    string buf;
    stringstream ss(fpexp);
    vector<string> fplist;
    while (ss >> buf)
    {
        fplist.push_back(buf);
    }
    stack<BinaryTree *> pStack;
    BinaryTree *eTree = new BinaryTree("");
    pStack.push(eTree);
    BinaryTree *currentTree = eTree;

    string arr[] = {"+", "-", "*", "/"};
    vector<string> vect(arr, arr + (sizeof(arr) / sizeof(arr[0])));

    string arr2[] = {"+", "-", "*", "/", ")"};
    vector<string> vect2(arr2, arr2 + (sizeof(arr2) / sizeof(arr2[0])));

    for (unsigned int i = 0; i < fplist.size(); i++)
    {

        if (fplist[i] == "(")
        {
            currentTree->insertLeft("");
            pStack.push(currentTree);
            currentTree = currentTree->getLeftChild();
        }

        else if (find(vect.begin(), vect.end(), fplist[i]) != vect.end())
        {
            currentTree->setRootVal(fplist[i]);
            currentTree->insertRight("");
            pStack.push(currentTree);
            currentTree = currentTree->getRightChild();
        }

        else if (fplist[i] == ")")
        {
            currentTree = pStack.top();
            pStack.pop();
        }

        else if (find(vect2.begin(), vect2.end(), fplist[i]) == vect2.end())
        {
            try
            {
                currentTree->setRootVal(fplist[i]);
                BinaryTree *parent = pStack.top();
                pStack.pop();
                currentTree = parent;
            }

            catch (string ValueError)
            {
                cerr << "token " << fplist[i] << " is not a valid integer" << endl;
            }
        }
    }
    return eTree;
}

void postorder(BinaryTree *tree)
{
    if (tree != NULL)
    {
        postorder(tree->getLeftChild());
        postorder(tree->getRightChild());
        cout << tree->getRootVal() << endl;
    }
}

void preorder(BinaryTree *tree)
{
    if (tree != NULL)
    {
        cout << tree->getRootVal() << endl;
        postorder(tree->getLeftChild());
        postorder(tree->getRightChild());
    }
}

void inorder(BinaryTree *tree)
{
    if (tree != NULL)
    {

        postorder(tree->getLeftChild());
        cout << tree->getRootVal() << endl;
        postorder(tree->getRightChild());
    }
}

void print_tree_indented(BinaryTree *root)
{
    if (root == NULL)
    {
        printf("yo");
        return;
    }
    cout << root->getRootVal();
    if (root->getLeftChild() != NULL)
    {
        printf(" /");
        print_tree_indented(root->getLeftChild());
    }
    if (root->getRightChild() != NULL)
    {
        printf(" \\");
        print_tree_indented(root->getRightChild());
    }
    printf("\n");
}
void print_tree(BinaryTree *root, int level)
{
    if (root == NULL)
        return;
    print_tree(root->getRightChild(), level + 1);
    for (int i = 0; i < level; i++)
        printf("      ");

    cout << root->getRootVal();
    printf("\n");
    print_tree(root->getLeftChild(), level + 1);
}

void bfsprint(BinaryTree *root, int level)
{
    if (root == NULL)
        return;
    int nodes = pow(2, level);
    int gap = nodes - 1;
    int total = nodes + gap;
    int spcl = total / 2;
    int spcm = total;
    int lv = 0;
    queue<BinaryTree *> q;
    q.push(root);
    int itr = 1;
    for (int i = 0; i < spcl; i++)
    {
        printf(" ");
    }
    while (!q.empty())
    {
        BinaryTree *temp = q.front();
        q.pop();

        cout << temp->getRootVal();
        if (temp->getLeftChild() != NULL)
        {
            q.push(temp->getLeftChild());
        }
        else if(lv<level)
        {
            BinaryTree *t = new BinaryTree(" ");
            q.push(t);
        }
        if (temp->getLeftChild() != NULL)
        {
            q.push(temp->getRightChild());
        }
        else if(lv<level)
        {
            BinaryTree *t = new BinaryTree(" ");
            q.push(t);
        }
        itr++;
        double logrs = log2(itr);
        if (logrs == int(logrs))
        {
            printf("\n");
            lv++;
            spcm = spcl;
            spcl = spcl / 2;
            for (int i = 0; i < spcl; i++)
            {
                printf(" ");
            }
        }
        else
        {
            for (int i = 0; i < spcm; i++)
            {
                printf(" ");
            }
        }
    }
}

int main()
{

    BinaryTree *pt = buildParseTree("( ( ( 4 + 7 ) - 8 ) * ( 3 - 2 ) )");

    inorder(pt);
    //bfsprint(pt, 5);
    //print_tree_indented(pt);
     print_tree(pt, 0);

    return 0;
}
