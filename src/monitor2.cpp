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
unordered_map<char, queue<int>> flques;

int depth = 1;
int wait = 0;
int time = 0;
int maxwait=0;

class tree
{
    public:
        char val;
        int ltime = 0;
        int utime = 0;
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
    if (order['U'].size() > 0 && order['U'].front() >= l && order['U'].front() <= r)
    {

        int i = order['U'].front();
        order['U'].pop();
        tr->ltime = atoi(arr.substr(i + 2, arr.length()).c_str());
        string stime = to_string(tr->ltime);
        int len = stime.length();


        tr->utime = atoi(arr.substr(i + 3 + len, arr.length()).c_str());
        string etime = to_string(tr->utime);
        int len2 = etime.length();
        maxwait=max(maxwait, tr->utime-tr->ltime);

        tr->val = 'U';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 4 + len2 + len, r, d + 1);
        return tr;
    }
    if (order['E'].size() > 0 && order['E'].front() >= l && order['E'].front() <= r)
    {
        // check for E in arr
        int i = order['E'].front();
        order['E'].pop();
        tr->utime = atoi(arr.substr(i + 1, arr.length()).c_str());
        string stime = to_string(tr->utime);
        maxwait=max(maxwait, tr->utime);
        int len = stime.length();
        tr->val = 'E';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1 + len, r, d + 1);
        return tr;
    }
    if (order['X'].size() > 0 && order['X'].front() >= l && order['X'].front() <= r)
    {
        int i = order['X'].front();
        order['X'].pop();
        tr->utime = 1;
        maxwait=max(maxwait, tr->utime);
        tr->val = 'X';
        tr->left = NULL;
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

     int uutil(int x, int y)
    {
        return x ;
    }

    int nnot(int x)
    {
        return !x;
    }

    int nnext(int x)
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
        else if (parseTree->val == 'U')
        {
            int tl = evaluate(leftC, um);
            if (tl == 1)
                return 1;
            int rs = Oper.uuntil(tl, evaluate(rightC, um));
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
        else if (parseTree->val == 'v')
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
        if (parseTree->val == 'X')
        {

            int rs = Oper.nnext(evaluate(rightC, um));
            return rs;
        }
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
    string exp = "AU[20,35]E23BvC";
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
                    flques[chars[j]].push(i);
                    j++;
                }
            }
            if (wait == 0)
                writefile << evaluate(tr, um) << "\n";
            time++;
        }
        line++;
    }
    writefile.close();
    readfile.close();
    return 0;
}