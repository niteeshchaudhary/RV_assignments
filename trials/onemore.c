#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node
{
    char value;
    struct Node *left;
    struct Node *right;
};

struct Node *create_node(char value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int is_constant(char ch){
    if (ch >= 'A' && ch <= 'Z')
        return 1;
    if (ch >= 'a' && ch <= 'z')
        return 1;
    return 0;
}

struct Node* parse_expression(const char* expr) {
    if(expr == NULL || strlen(expr) == 0)
        return NULL;
    if (is_constant(expr[0])){
        struct Node* node = create_node(expr[0]);
        return node;
    }
    struct Node* root = create_node(expr[0]);
    int i = 1;
    if (root->value == '!') {
        root->right = parse_expression(expr + i);
        if(root->right == NULL) {
            free(root);
            return NULL;
        }
    } else if(root->value == 'v' || root->value == '^' || root->value == '>') {
        root->left = parse_expression(expr + i);
        if(root->left == NULL) {
            free(root);
            return NULL;
        }
        i += strlen(expr + i);
        root->right = parse_expression(expr + i);
        if(root->right == NULL) {
            free(root);
            return NULL;
        }
    } else {
        free(root);
        return NULL;
    }
    return root;
}


void print_tree_indented(struct Node* root) {
    if (root == NULL) {
        printf("yo");
        return;
    }
    printf("%c", root->value);
    if (root->left != NULL) {
        printf(" /");
        print_tree_indented(root->left);
    }
    if (root->right != NULL) {
        printf(" \\");
        print_tree_indented(root->right);
    }
    printf("\n");
}



int main(int argc, char **argv)
{
    const char *expr = "!Rv!G";
    struct Node *root = parse_expression(expr);
    print_tree_indented(root);
    return 0;
}