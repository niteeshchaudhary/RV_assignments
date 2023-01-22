#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
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

tree *construct_tree(string arr, int l, int r)
{
    tree *tr = new tree(' ');
    for (int i = l; i <= r; i++)
    {
        if (arr[i] == '>')
        {
            tr->val = '>';
            tr->left = construct_tree(arr, l, i - 1);
            tr->right = construct_tree(arr, i + 1, r);
            return tr;
        }
    }
    for (int i = l; i <= r; i++)
    {
        if (arr[i] == '^')
        {
            tr->val = '^';
            tr->left = construct_tree(arr, l, i - 1);
            tr->right = construct_tree(arr, i + 1, r);
            return tr;
        }
    }
    for (int i = l; i <= r; i++)
    {
        if (arr[i] == 'v')
        {
            tr->val = 'v';
            tr->left = construct_tree(arr, l, i - 1);
            tr->right = construct_tree(arr, i + 1, r);
            return tr;
        }
    }
    for (int i = l; i <= r; i++)
    {
        if (arr[i] == '!')
        {
            tr->val = '!';
            tr->left = NULL;
            tr->right = construct_tree(arr, i + 1, r);
            return tr;
        }
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

    string exp = "!Rv!G";
    unordered_map<char, int> um;
    um['A'] = 1;
    um['B'] = 1;
    um['C'] = 1;
    um['K'] = 1;
    um['H'] = 0;
    um['R'] = 0;
    um['G'] = 0;
    tree *tr = construct_tree(exp, 0, exp.size() - 1);
    print_tree(tr, 0);
    cout << endl
         << "*" << evaluate(tr, um);
    // postorder(tr);
    // print_tree_indented(tr);
    return 0;
}