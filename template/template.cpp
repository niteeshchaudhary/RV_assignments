#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdlib.h>
#include <fstream>
#include <queue>
#include <math.h>
using namespace std;

unordered_map<char, queue<int>> order;
int depth = 1;
class tree
{
public:
    char val;
    tree *left;
    tree *right;
    tree(char data)
    {
        val = data;
        left = NULL;
        right = NULL;
    }
};
void readexpr(string expr)
{
    for (int i = 0; i < expr.size(); i++)
    {
        order[expr[i]].push(i);
    }
}
tree *construct_tree(string arr, int l, int r, int d)
{
    tree *tr = new tree(' ');
    if (depth < d)
    {
        depth = d;
    }

    if (order['>'].size() > 0 && order['>'].front() >= l && order['>'].front() <= r)
    {
        int i = order['>'].front();
        order['>'].pop();
        tr->val = '>';
        tr->left = construct_tree(arr, l, i - 1, d + 1);
        tr->right = construct_tree(arr, i + 1, r, d + 1);
        return tr;
    }
    if (order['^'].size() > 0 && order['^'].front() >= l && order['^'].front() <= r)
    {
        int i = order['^'].front();
        order['^'].pop();
        tr->val = '^';
        tr->left = construct_tree(arr, l, i - 1, d + 1);
        tr->right = construct_tree(arr, i + 1, r, d + 1);
        return tr;
    }
    if (order['v'].size() > 0 && order['v'].front() >= l && order['v'].front() <= r)
    {
        int i = order['v'].front();
        order['v'].pop();
        tr->val = 'v';
        tr->left = construct_tree(arr, l, i - 1, d + 1);
        tr->right = construct_tree(arr, i + 1, r, d + 1);
        return tr;
    }
    if (order['!'].size() > 0 && order['!'].front() >= l && order['!'].front() <= r)
    {
        int i = order['!'].front();
        order['!'].pop();
        tr->val = '!';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1, r, d + 1);
        return tr;
        return tr;
    }
    if (l == r)
    {
        tr = new tree(arr[l]);
    }
    return tr;
}
class Operator
{
public:
    int iimplies(int x, int y)
    {
        return !x || y;
    }

    int oor(int x, int y)
    {
        return x || y;
    }

    int aand(int x, int y)
    {
        return x && y;
    }

    int nnot(int x)
    {
        return !x;
    }
};
int evaluate(tree *parseTree, unordered_map<char, int> um)
{
    Operator Oper;

    tree *leftC = parseTree->left;
    tree *rightC = parseTree->right;

    if (leftC && rightC)
    {
        if (parseTree->val == '>')
        {
            int tl = evaluate(leftC, um);
            if (tl == 0)
                return 1;
            int rs = Oper.iimplies(tl, evaluate(rightC, um));
            return rs;
        }
        else if (parseTree->val == '^')
        {
            int tl = evaluate(leftC, um);
            if (tl == 0)
                return tl;
            int rs = Oper.aand(tl, evaluate(rightC, um));
            return rs;
        }
        else
        {
            int tl = evaluate(leftC, um);
            if (tl == 1)
                return 1;
            int rs = Oper.oor(tl, evaluate(rightC, um));
            return rs;
        }
    }
    else if (rightC)
    {
        if (parseTree->val == '!')
        {

            int rs = Oper.nnot(evaluate(rightC, um));
            return rs;
        }
    }
    return um[parseTree->val];
}
int main(int argc, char *argv[])
{
    string mytext = "";
    unordered_map<char, int> um;
    ifstream readfile(argv[1]);
    ofstream writefile(argc == 3 ? argv[2] : "user.verdict");
    string exp;
    readexpr(exp);
    tree *tr = construct_tree(exp, 0, exp.size() - 1, 1);
    vector<char> chars;
    int line = 0;
    while (getline(readfile, mytext))
    {
        if (line == 0)
        {
            for (int i = 0; i < mytext.size(); i++)
            {
                if (mytext[i] != ',')
                {
                    um[mytext[i]] = 0;
                    chars.push_back(mytext[i]);
                }
            }
        }
        else
        {
            for (int i = 0, j = 0; i < mytext.size(); i++)
            {
                if (mytext[i] != ',')
                {
                    um[chars[j]] = int(mytext[i] - 48);
                    j++;
                }
            }
            writefile << evaluate(tr, um) << "\n";
        }
        line++;
    }
    writefile.close();
    readfile.close();
    return 0;
}