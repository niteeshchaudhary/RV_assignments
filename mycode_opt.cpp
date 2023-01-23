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
            return rs;
        }
    }

    return um[parseTree->val];
}

void printTree(tree *tr, int sz, int depth)
{
    queue<pair<tree *, int>> qu;
    int lvl = 0;
    qu.push(make_pair(tr, 1));
    int lim = sz;
    int chng = 0;
    while (!qu.empty())
    {
        pair<tree *, int> pr = qu.front();
        qu.pop();

        if (lvl != pr.second)
        {
            cout << "\n";
            lim = int(pow(2, depth - lvl)) - 1;
            lvl = pr.second;
            if (lvl == depth + 1)
            {
                break;
            }
            // cout << "|" << lim << "|";
            chng = 0;
        }
        else
        {
            if (chng != 1)
            {
                lim = lim * 2 + 1;
                chng = 1;
            }
            // cout << "|" << lim << "|";
        }
        // cout << "|" << lim << "|"<< "\n";
        for (int ii = 0; ii < lim; ii++)
        {
            cout << " ";
        }
        cout << pr.first->val;
        if (pr.first->left)
        {
            qu.push(make_pair(pr.first->left, pr.second + 1));
        }
        else
        {
            qu.push(make_pair(new tree(' '), pr.second + 1));
        }
        if (pr.first->right)
        {
            qu.push(make_pair(pr.first->right, pr.second + 1));
        }
        else
        {
            qu.push(make_pair(new tree(' '), pr.second + 1));
        }
        // cout << lim << " ";
    }
    cout << "\n";
}

int main()
{
    string mytext = "";
    unordered_map<char, int> um;

    // Read from the text file
    ifstream readfile("testcases/testcases/property2/system4.input");
    ofstream writefile("testcases/testcases/property2/user.verdict");

    string exp = "!Av!BvCvDv!Dv!E>F^!G^GvF^!G^H";
    readexpr(exp);
    tree *tr = construct_tree(exp, 0, exp.size() - 1, 1);
    vector<char> chars;
    int line = 0;
    while (getline(readfile, mytext))
    {
        // Output the text from the file
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
            // cout << mytext << endl;

            for (int i = 0, j = 0; i < mytext.size(); i++)
            {
                if (mytext[i] != ',')
                {
                    um[chars[j]] = int(mytext[i] - 48);
                    j++;
                }
            }
            writefile << evaluate(tr, um) << "\n";
            // cout << "*" << evaluate(tr, um) << endl;
        }
        line++;
    }

    cout <<"Tree Depth" <<depth << " ";
    if (depth > 6)
    {
        print_tree(tr, 0);
    }
    else
    {
        printTree(tr, exp.size(), depth);
    }

    writefile.close();
    readfile.close();
    return 0;
}