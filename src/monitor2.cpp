#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdlib.h>
#include <fstream>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

unordered_map<char, queue<int>> order;
unordered_map<char, vector<int>> flques;

int depth = 1;
int wait = 0;
int time = 0;
int maxwait = 1;
int F=0;
int G=1;
int minwait = -100;

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
        maxwait = max(maxwait, tr->utime);
        minwait = max(minwait, tr->utime);

        tr->val = 'U';
        tr->left = construct_tree(arr, l, i - 1, d + 1);
        tr->right = construct_tree(arr, i + 4 + len2 + len, r, d + 1);
        return tr;
    }
    if (order['X'].size() > 0 && order['X'].front() >= l && order['X'].front() <= r)
    {
        int i = order['X'].front();
        order['X'].pop();
        tr->utime = 2;
        maxwait = max(maxwait, tr->utime);
        minwait = max(minwait, tr->utime - tr->ltime);
        tr->val = 'X';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1, r, d + 1);
        return tr;
    }
    if (order['F'].size() > 0 && order['F'].front() >= l && order['F'].front() <= r)
    {
        // check for F in arr
        int i = order['F'].front();
        order['F'].pop();
        // tr->utime = atoi(arr.substr(i + 1, arr.length()).c_str());
        string stime = to_string(tr->utime);
        //maxwait = max(maxwait, tr->utime);
       // minwait = max(minwait, 1);
        //int len = stime.length();
        tr->val = 'F';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1 , r, d + 1);
        return tr;
    }
    if (order['E'].size() > 0 && order['E'].front() >= l && order['E'].front() <= r)
    {
        // check for E in arr
        int i = order['E'].front();
        order['E'].pop();
        tr->utime = atoi(arr.substr(i + 1, arr.length()).c_str());
        string stime = to_string(tr->utime);
        maxwait = max(maxwait, tr->utime);
        minwait = max(minwait, 1);
        int len = stime.length();
        tr->val = 'E';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1 + len, r, d + 1);
        return tr;
    }
    if (order['H'].size() > 0 && order['H'].front() >= l && order['H'].front() <= r)
    {
        // check for E in arr
        int i = order['H'].front();
        order['H'].pop();
        tr->utime = atoi(arr.substr(i + 1, arr.length()).c_str());
        string stime = to_string(tr->utime);
        maxwait = max(maxwait, tr->utime);
        minwait = max(minwait, tr->utime);
        int len = stime.length();
        tr->val = 'H';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1 + len, r, d + 1);
        return tr;
    }
    if (order['G'].size() > 0 && order['G'].front() >= l && order['G'].front() <= r)
    {
        // check for E in arr
        int i = order['G'].front();
        order['G'].pop();
        // tr->utime = atoi(arr.substr(i + 1, arr.length()).c_str());
        // string stime = to_string(tr->utime);
        // maxwait = max(maxwait, tr->utime);
        // minwait = max(minwait, 1);

        tr->val = 'G';
        tr->left = NULL;
        tr->right = construct_tree(arr, i + 1 , r, d + 1);
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

    int uuntil(char x, char y, int lsize, int usize)
    {
        cout<<flques[x].size()<<" "<<x<<" "<<y;
        if (flques[y].size() >= usize)
        {
            for (int i = 0;i<lsize-1;i++)
            {
                if (flques[x][i] == 0)
                {
                    cout << "Yeh!" << flques[x][i] << "\n";
                    return 0;
                }
            }
            for (int i = lsize; i <= usize && flques[x][i-1]; i++)
            {
                cout << flques[y][i] << " ";
                if (flques[y][i] == 1)
                    return 1;
            }
            return 0;
        }
        else if (flques[y].size() >= lsize)
        {
            for (int i = lsize; i < flques[y].size(); i++)
            {

                if (flques[y][i] == 1)
                {
                    cout << "Yeh!" << flques[y][i] << "\n";
                    return 1;
                }
            }

            exit(0);
        }
        else
        {
            cout << " fault"<<"\n";
            return 0;
        }
    }

    int nnot(int x)
    {
        return !x;
    }

    int nnext(char x)
    {
        if (flques[x].size() >= 2)
        {
            // cout << time -1<< " " << flques[x][1] << "\n";
            return flques[x][1];
        }
        else
        {
            cout << "fault";
            return 0;
        }
    }

    int atleastOneF(char x)
    {
        if (flques[x].size() >= 1)
        {
            if (flques[x][0] == 1 || F==1){
                F=1;
                return 1;
            }
            
            return 0;
        }
        else
        {
            cout<<"fault\n";
            exit(0);
        }
    }
    int allwaysG(char x)
    {
        if (flques[x].size() >= 1)
        {
            if (flques[x][0] == 1 && G==1)
            {
                    return 1;
            }
            G=0;
            return 0;
        }
        else
        {
            cout<<"fault\n";

            exit(0);
        }
    }

    int allways(char x, int size)
    {
        if (flques[x].size() >= size)
        {
            for (int i = 0; i < size; i++)
            {
                if (flques[x][i] != 1)
                    return 0;
            }
            return 1;
        }
        else
        {
            cout<<"fault\n";
            exit(0);
        }
    }

    int atleastOne(char x, int size)
    {
        if (flques[x].size() >= size)
        {
            for (int i = 0; i < size; i++)
            {
                if (flques[x][i] == 1)
                    return 1;
            }
            return 0;
        }
        else
        {
            for (int i = 0; i < flques[x].size(); i++)
            {

                if (flques[x][i] == 1)
                {
                    cout << "Yeh!" << flques[x][i] << "\n";
                    return 1;
                }
            }

            exit(0);
        }
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
        else if (parseTree->val == 'v')
        {
            int tl = evaluate(leftC, um);
            if (tl == 1)
                return 1;
            int rs = Oper.oor(tl, evaluate(rightC, um));
            return rs;
        }
        else if (parseTree->val == 'U')
        {
            int rs = Oper.uuntil(leftC->val, rightC->val, parseTree->ltime, parseTree->utime);
            return rs;
        }
    }
    else if (rightC)
    {
        if (parseTree->val == 'X')
        {
            int rs = Oper.nnext(rightC->val);
            return rs;
        }
        if (parseTree->val == 'E')
        {
            int rs = Oper.atleastOne(rightC->val, parseTree->utime);
            return rs;
        }
        if (parseTree->val == 'F')
        {
            int rs = Oper.atleastOneF(rightC->val);
            return rs;
        }
         if (parseTree->val == 'H')
        {
            int rs = Oper.allways(rightC->val, parseTree->utime);
            return rs;
        }
         if (parseTree->val == 'G')
        {
            int rs = Oper.allwaysG(rightC->val);
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
    ifstream readfile(argc > 1 ? argv[1] : "../testcases2/property2/system1.input");
    ofstream writefile(argc == 3 ? argv[2] : "user.verdict");
    string exp = "GA";
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
            int j = 0;
            for (int i = 0; i < mytext.size(); i++)
            {
                if (mytext[i] != ',')
                {
                    int bin = int(mytext[i] - 48);
                    flques[chars[j]].push_back(bin);
                    j++;
                }
            }

            wait++;
            time++;
            cout << "maxwait: " << maxwait << " wait: " << wait << " time: " << time << "\n";
            if (wait == maxwait)
            {
                for (int i = 0; i < j; i++)
                {
                    um[chars[i]] = flques[chars[i]][0];
                }
                writefile << evaluate(tr, um) << "\n";
                for (int i = 0; i < j; i++)
                {
                    flques[chars[i]].erase(flques[chars[i]].begin());
                }

                wait = flques[chars[0]].size();
            }
        }
        line++;
    }

    while (flques[chars[0]].size() >= minwait)
    {
        cout << "%" << flques[chars[0]].size() << "\n";
        for (int i = 0; i < chars.size(); i++)
        {
            um[chars[i]] = flques[chars[i]][0];
        }
        writefile << evaluate(tr, um) << "\n";
        for (int i = 0; i < chars.size(); i++)
        {
            flques[chars[i]].erase(flques[chars[i]].begin());
        }
        cout << "%" << flques[chars[0]].size() << "\n";
    }
    writefile.close();
    readfile.close();
    return 0;
}