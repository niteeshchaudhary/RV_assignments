#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdlib.h>
#include <queue>
using namespace std;

unordered_map<char, queue<int>> order;
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
tree *construct_tree(string arr, int l, int r)
{
    tree *tr = new tree(' ');

    if (order['>'].size() > 0 && order['>'].front() >= l && order['>'].front() <= r)
    {
        int i = order['>'].front();
        order['>'].pop();
        tr->val = '>';
        tr->left = construct_tree(arr, l, i - 1);
        tr->right = construct_tree(arr, i + 1, r);
        return tr;
    }
    if (order['^'].size() > 0 && order['^'].front() >= l && order['^'].front() <= r)
    {
        int i = order['^'].front();
        order['^'].pop();
        tr->val = '^';
        tr->left = construct_tree(arr, l, i - 1);
        tr->right = construct_tree(arr, i + 1, r);
        return tr;
    }
    if (order['v'].size() > 0 && order['v'].front() >= l && order['v'].front() <= r)
    {
        int i = order['v'].front();
        order['v'].pop();
        tr->val = 'v';
        tr->left = construct_tree(arr, l, i - 1);
        tr->right = construct_tree(arr, i + 1, r);
        return tr;
    }
    if (order['!'].size() > 0 && order['!'].front() >= l && order['!'].front() <= r)
    {
        int i = order['!'].front();
        order['!'].pop();
        tr->val = '!';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1, r);
        return tr;
        return tr;
    }
    if (l == r)
    {
        tr = new tree(arr[l]);
    }
    return tr;
}
void postorder(tree *tr)
{
    if (tr != NULL)
    {
        postorder(tr->left);
        postorder(tr->right);
        cout << tr->val << endl;
    }
}

void print_tree(tree *root, int level)
{
    if (root == NULL)
        return;
    print_tree(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("      ");

    cout << root->val;
    printf("\n");
    print_tree(root->left, level + 1);
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

int evaluate(tree *parseTree, unordered_map<char, int> um)
{
    Operator Oper;

    tree *leftC = parseTree->left;
    tree *rightC = parseTree->right;

    if (leftC && rightC)
    {
        if (parseTree->val == '>')
        {
            int rs = Oper.iimplies(evaluate(leftC, um), evaluate(rightC, um));
            // cout << ">" << rs << endl;
            return rs;
            // return Oper.iimplies(evaluate(leftC, um), evaluate(rightC, um));
        }
        else if (parseTree->val == '^')
        {
            int rs = Oper.aand(evaluate(leftC, um), evaluate(rightC, um));
            // cout << "^" << rs << endl;
            return rs;
        }
        else // if (parseTree->val == 'v')
        {
            int rs = Oper.oor(evaluate(leftC, um), evaluate(rightC, um));
            // cout << "v" << rs << endl;
            return rs;
        }
    }
    else if (rightC)
    {
        if (parseTree->val == '!')
        {

            int rs = Oper.nnot(evaluate(rightC, um));
            //   cout << "!" << rs << endl;
            return rs;
        }
    }

    // if(parseTree->val=='0'){
    //     return 0;
    // }
    // else{
    //     return 1;
    // }
    // cout << "{" << parseTree->val << endl;
    return um[parseTree->val];
}

int main()
{

    string exp = "!Av!BvCvDv!Dv!E>F^!G^GvF^!G^H";
    readexpr(exp);
    tree *tr = construct_tree(exp, 0, exp.size() - 1);
    unordered_map<char, int> um;
    um['A'] = 0;
    um['B'] = 0;
    um['C'] = 0;
    um['D'] = 1;
    um['E'] = 1;
    um['F'] = 1;
    um['G'] = 0;
    um['H'] = 1;
    um['K'] = 1;

    um['R'] = 1;

    print_tree(tr, 0);
    cout << endl
         << "*" << evaluate(tr, um);
    // postorder(tr);
    // print_tree_indented(tr);
    return 0;
}