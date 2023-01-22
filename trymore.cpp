#include <iostream>
#include <stack>
using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;
};

Node *newNode(char data)
{
    Node *node = new Node;
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

void printTree(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->data << " ";
    printTree(root->left);
    printTree(root->right);
}

bool isOperator(char c)
{
    // Add all the operator characters here
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '>' || c == '<' || c == '=' || c == '&' || c == '|' || c == '!')
    {
        return true;
    }
    return false;
}

string convertToPostfix(string prefix)
{
    stack<string> s;
    for (int i = prefix.length() - 1; i >= 0; i--)
    {
        cout << 103 << endl;
        if (!isOperator(prefix[i]))
        {
            string op(1, prefix[i]);
            s.push(op);
        }
        else
        {
            if (prefix[i] == '!')
            {
                cout << 101 << endl;
                string temp(1, prefix[i]);
                s.push(temp);
                cout << 102 << endl;
            }
            else
            {
                string op1 = s.top();
                s.pop();
                string op2 = s.top();
                s.pop();
                string temp = op1 + op2 + prefix[i];
                s.push(temp);
            }
        }
    }
    return s.top();
}

Node *constructTree(string postfix)
{
    stack<Node *> st;
    Node *t, *t1, *t2;
    // Traverse through every character of
    // input expression
    for (int i = 0; i < postfix.length(); i++)
    {
        // If operand, simply push into stack
        if (!isOperator(postfix[i]))
        {
            t = newNode(postfix[i]);
            st.push(t);
        }
        else
        {
            cout << 10 << endl;
            t = newNode(postfix[i]);
            cout << 11 << endl;
            if (postfix[i] == '!')
            {
                cout << 12 << endl;
                t1 = st.top();
                cout << 2 << endl;
                st.pop();
                cout << 3 << endl;
                t->right = t1;
                cout << 4 << endl;
            }
            else
            {
                cout << 9 << endl;
                t1 = st.top();
                cout << 5 << endl;
                st.pop();
                cout << 6 << endl;
                t2 = st.top();
                cout << 7 << endl;
                st.pop();
                cout << 8 << endl;
                t->right = t1;
                t->left = t2;
            }
            cout << 1 << endl;
            st.push(t);
        }
    }
    return st.top();
}

int main()
{
    string prefixExpression = "!A^Bv!E>F^!G^H";
    string postfixExpression = convertToPostfix(prefixExpression);
    Node *root = constructTree(postfixExpression);

    cout << "Expression tree: " << endl;
    printTree(root);
    return 0;
}