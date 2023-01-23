#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
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

void postorder(BinaryTree *tree)
{
    if (tree != NULL)
    {
        postorder(tree->getLeftChild());
        postorder(tree->getRightChild());
        cout << tree->getRootVal() << endl;
    }
}

BinaryTree *buildParseTree(string fpexp)
{
    string buf;
    // stringstream ss(fpexp);
    vector<string> fplist;
    // while (ss >> buf)
    // {
    //     fplist.push_back(buf);
    //     cout<<"|"<<buf;
    // }
    for (int i = 0; i < fpexp.size(); i++)
    {
        string str1(1, fpexp[i]);
        fplist.push_back(str1);
        cout << "," << fpexp[i];
    }
    cout << endl;
    stack<BinaryTree *> pStack;
    BinaryTree *eTree = new BinaryTree("");
    pStack.push(eTree);
    BinaryTree *currentTree = eTree;

    string arr[] = {"!", ">", "^", "v"};
    vector<string> vect(arr, arr + (sizeof(arr) / sizeof(arr[0])));

    string arr2[] = {"!", ">", "^", "v", ")"};
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
            cout << " * " << fplist[i] << endl;
            if (fplist[i] == "!")
            {
                currentTree->insertLeft("");
                currentTree->setRootVal(fplist[i]);
                currentTree->insertRight("");
                pStack.push(currentTree);
                currentTree = currentTree->getRightChild();
            }
            else
            {
                currentTree = pStack.top();
                pStack.pop();
                currentTree->setRootVal(fplist[i]);
                currentTree->insertRight("");
                pStack.push(currentTree);
                currentTree = currentTree->getRightChild();
            }
        }

        else if (fplist[i] == ")")
        {
            currentTree = pStack.top();
            pStack.pop();
        }
        else if (find(vect2.begin(), vect2.end(), fplist[i]) == vect2.end())
        {
            if (i == 0)
            {
                currentTree->insertLeft("");
                pStack.push(currentTree);
                currentTree = currentTree->getLeftChild();
            }
            try
            {
                currentTree->setRootVal(fplist[i]);
                BinaryTree *parent = pStack.top();
                pStack.pop();
                currentTree = parent;
                cout << currentTree->getRootVal() << "# ";
                postorder(currentTree);
                cout << "#" << endl;
            }

            catch (string ValueError)
            {
                cerr << "token " << fplist[i] << " is not a valid integer" << endl;
            }
        }
    }
    return eTree;
}

class Operator
{
public:
    int add(int x, int y)
    {
        return x + y;
    }

    int sub(int x, int y)
    {
        return x - y;
    }

    int mul(int x, int y)
    {
        return x * y;
    }

    int div(int x, int y)
    {
        return x / y;
    }
    bool iimplies(int x, int y)
    {
        return !x || y;
    }

    bool oor(int x, int y)
    {
        return x || y;
    }

    bool aand(int x, int y)
    {
        return x && y;
    }

    bool nnot(int x)
    {
        return !x;
    }
};

int to_int(string str)
{
    stringstream convert(str);
    int x = 0;
    convert >> x;
    return x;
}

string tostr(int num)
{
    string str;
    ostringstream convert;
    convert << num;
    str = convert.str();
    return str;
}

string evaluate(BinaryTree *parseTree)
{
    Operator Oper;

    BinaryTree *leftC = parseTree->getLeftChild();
    BinaryTree *rightC = parseTree->getRightChild();

    if (leftC && rightC)
    {
        if (parseTree->getRootVal() == "^")
        {
            return tostr(Oper.aand(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        }
        else if (parseTree->getRootVal() == "v")
        {
            return tostr(Oper.oor(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        }
        else if (parseTree->getRootVal() == "!")
        {
            return tostr(Oper.nnot(to_int(evaluate(rightC))));
        }
        else
        {
            return tostr(Oper.iimplies(to_int(evaluate(leftC)), to_int(evaluate(rightC))));
        }
    }
    else
    {
        return parseTree->getRootVal();
    }
}

int main()
{
    BinaryTree *pt = buildParseTree("!1");
    postorder(pt);
    cout << "*" << evaluate(pt);
    return 0;
}