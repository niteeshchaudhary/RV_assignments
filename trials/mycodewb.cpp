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

void print_tree(tree *root, int level)
{
    if (root == NULL)
        return;
    print_tree(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("  ");

    cout << root->val;
    printf("\n");
    print_tree(root->left, level + 1);
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

string processExpression(string s)
{
    string news = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ')
            news += s[i];
    }
    return news;
}
int main(int argc, char *argv[])
{
    string mytext = "";
    unordered_map<char, int> um;
    um['R'] = 1;
    um['G'] = 1;

    string exp = " !  R   v      !                                   G";
    exp = processExpression(exp);

    readexpr(exp);
    tree *tr = construct_tree(exp, 0, exp.size() - 1, 1);
    vector<char> chars;

    print_tree(tr, 0);
    cout << endl
         << "*" << evaluate(tr, um);
    return 0;
}