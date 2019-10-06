#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 100

struct TreeNode
{
    char* data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* makeEmpty(struct TreeNode* root)
{
    if(root != NULL)
    {
        makeEmpty(root->left);
        makeEmpty(root->right);
        free(root);
    }
    return NULL;
}

struct TreeNode* insert(struct TreeNode* root, char* x)
{
    if(root == NULL)
    {
        root = malloc(sizeof(struct TreeNode));
        root->data = x;
        root->left = root->right = NULL;
    }
    else if(strcmp(x,root->data) < 0)
        root->left = insert(root->left, x);
    else if(strcmp(x,root->data)> 0 )
        root->right = insert(root->right, x);
    return root;
}

struct TreeNode* findMin(struct TreeNode* root)
{
    if(root == NULL)
        return NULL;
    else if(root->left == NULL)
        return root;
    else
        return findMin(root->left);
}

struct TreeNode* findMax(struct TreeNode* root)
{
    if(root == NULL)
        return NULL;
    else if(root->right == NULL)
        return root;
    else
        return findMax(root->right);
}

struct TreeNode* find(struct TreeNode* root, char* x)
{
    if(root == NULL)
        return NULL;
    else if(strcmp(x,root->data) < 0)
        return find(root->left, x);
    else if(strcmp(x,root->data) > 0)
        return find(root->right, x);
    else
        return root;
}

int findHeight(struct TreeNode* root)
{
    int lefth, righth;
    if(root == NULL)
        return -1;
    lefth = findHeight(root->left);
    righth = findHeight(root->right);
    return (lefth > righth ? lefth : righth)+1;
}

struct TreeNode* delete(struct TreeNode* root, char* x)
{
    struct TreeNode* temp;
    if(root == NULL)
        return NULL;
    else if(strcmp(x,root->data)<0)
        root->left = delete(root->left, x);
    else if(strcmp(x,root->data) > 0)
        root->right = delete(root->right, x);
    else if(root->left && root->right)
    {
        temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, root->data);
    }
    else
    {
        temp = root;
        if(root->left == NULL)
            root = root->right;
        else if(root->right == NULL)
            root = root->left;
        free(temp);
    }
    return root;
}

void inorder(struct TreeNode* root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    printf("%s ", root->data);
    inorder(root->right);
}



typedef struct T{
    char *string;
    char *string2;
}T;

void addrel(char* entity1, char* entity2, char* relationship);
void addent(char* entity);

int compLT(T x, T y){
    if(strcmp(x.string,y.string) < 0)
        return 1;
    if( strcmp(x.string,y.string) == 0 ) {
        if (strlen(x.string2) > 0 && strlen(y.string2) > 0) {
            if (strcmp(x.string2, y.string2) < 0) {
                return 1;
            }
        }
    }
    return 0;
}
int compEQ(T x, T y){
    if(strcmp(x.string,y.string) == 0 ){
        if( strlen(x.string2) > 0 && strlen(y.string2) > 0) {
            if (strcmp(x.string2, y.string2) == 0)
                return 1;
        }
        else
            return 1;
    }
    return 0;
}

typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
    struct Node_ *left;
    struct Node_ *right;
    struct Node_ *parent;
    nodeColor color;
    T data;
} Node;

typedef struct entities_{
    struct entities_ *left;
    struct entities_ *right;
    struct entities_ *parent;
    char* data;
}E_Node;

typedef struct V{
    char* receiver;
    int n_receivers;
    struct TreeNode* Root_senders;
}V;


typedef struct receivers_{
    struct receivers_ *left;
    struct receivers_ *right;
    struct receivers_ *parent;
    nodeColor color;
    V data;
}V_Node;

typedef struct R{
    char* relationship;
    int max;
    int n_elements;
    Node* Root_Sender;
    V_Node* Root_Receiver;
    E_Node* max_receiver_tree;
}R;


int r_compLT(R x, R y){
    if(strcmp(x.relationship,y.relationship) < 0)
        return 1;
    return 0;
}

int r_compEQ(R x, R y){
    if(strcmp(x.relationship,y.relationship) == 0 )
            return 1;
    return 0;
}

int e_compLT(char* x, char* y){
    if(strcmp(x,y) < 0)
        return 1;
    return 0;
}

int e_compEQ(char* x, char* y){
    if(strcmp(x,y) == 0 )
        return 1;
    return 0;
}

int v_compLT(V x, V y){
    if(strcmp(x.receiver,y.receiver) < 0)
        return 1;
    return 0;
}

int v_compEQ(V x, V y){
    if(strcmp(x.receiver,y.receiver) == 0 )
        return 1;
    return 0;
}


typedef struct relations_{
    struct relations_ *left;
    struct relations_ *right;
    struct relations_ *parent;
    nodeColor color;
    R data;
}R_Node;



#define NIL &sentinel
Node sentinel = { NIL, NIL, 0, BLACK, 0};

#define R_NIL &sentinel_r
R_Node sentinel_r = { R_NIL, R_NIL, 0, BLACK, 0};


#define E_NIL &sentinel_e
E_Node sentinel_e = { E_NIL, E_NIL, 0, 0};

#define V_NIL &sentinel_v
V_Node sentinel_v = { V_NIL, V_NIL, 0, BLACK, 0};



void r_rotateLeft(R_Node *x,R_Node ** T) {


    R_Node *y = x->right;
    x->right = y->left;
    if (y->left != R_NIL) y->left->parent = x;

    if (y != R_NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        *T = y;
    }

    y->left = x;
    if (x != R_NIL) x->parent = y;
}

void v_rotateLeft(V_Node *x,V_Node ** T) {

    V_Node *y = x->right;

    x->right = y->left;
    if (y->left != V_NIL) y->left->parent = x;

    if (y != V_NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        *T = y;
    }

    y->left = x;
    if (x != V_NIL) x->parent = y;
}

void rotateLeft(Node *x,Node ** T) {

    Node *y = x->right;

    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        *T = y;
    }

    y->left = x;
    if (x != NIL) x->parent = y;
}

void r_rotateRight(R_Node *x,R_Node** T) {

    R_Node *y = x->left;

    x->left = y->right;
    if (y->right != R_NIL) y->right->parent = x;

    if (y != R_NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        *T = y;
    }

    y->right = x;
    if (x != R_NIL) x->parent = y;
}

void v_rotateRight(V_Node *x,V_Node** T) {

    V_Node *y = x->left;

    x->left = y->right;
    if (y->right != V_NIL) y->right->parent = x;

    if (y != V_NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        *T = y;
    }
    y->right = x;
    if (x != V_NIL) x->parent = y;
}

void rotateRight(Node *x,Node** T) {

    Node *y = x->left;

    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        *T = y;
    }
    y->right = x;
    if (x != NIL) x->parent = y;
}

void r_insertFixup(R_Node *x,R_Node** T) {

    while (x != *T && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            R_Node *y = x->parent->parent->right;
            if (y->color == RED) {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->right) {
                    x = x->parent;
                    r_rotateLeft(x,T);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                r_rotateRight(x->parent->parent,T);
            }
        } else {

            R_Node *y = x->parent->parent->left;
            if (y->color == RED) {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->left) {
                    x = x->parent;
                    r_rotateRight(x,T);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                r_rotateLeft(x->parent->parent,T);
            }
        }
    }
    (*T)->color = BLACK;
}

void v_insertFixup(V_Node *x,V_Node** T) {

    while (x != *T && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            V_Node *y = x->parent->parent->right;
            if (y->color == RED) {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->right) {
                    x = x->parent;
                    v_rotateLeft(x,T);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                v_rotateRight(x->parent->parent,T);
            }
        } else {

            V_Node *y = x->parent->parent->left;
            if (y->color == RED) {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->left) {
                    x = x->parent;
                    v_rotateRight(x,T);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                v_rotateLeft(x->parent->parent,T);
            }
        }
    }
    (*T)->color = BLACK;
}


void insertFixup(Node *x,Node** T) {

    while (x != *T && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;
            if (y->color == RED) {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->right) {
                    x = x->parent;
                    rotateLeft(x,T);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent,T);
            }
        } else {

            Node *y = x->parent->parent->left;
            if (y->color == RED) {

                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x,T);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent,T);
            }
        }
    }
    (*T)->color = BLACK;
}

Node *insertNode(T data,Node** T) {
    Node *current, *parent, *x;

    current = *T;
    parent = 0;
    while (current != NIL) {
        if (compEQ(data, current->data)) return (current);
        parent = current;
        current = compLT(data, current->data) ?
                  current->left : current->right;
    }

    if ((x = malloc (sizeof(*x))) == 0) {
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;

    if(parent) {
        if(compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        *T = x;
    }

    insertFixup(x,T);
    return(x);
}

R_Node *r_insertNode(R data,R_Node** T) {
    R_Node *current, *parent, *x;

    current = *T;
    parent = 0;
    while (current != R_NIL) {
        if (r_compEQ(data, current->data)) return (current);
        parent = current;
        current = r_compLT(data, current->data) ?
                  current->left : current->right;
    }

    if ((x = malloc (sizeof(*x))) == 0) {
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = R_NIL;
    x->right = R_NIL;
    x->color = RED;

    if(parent) {
        if(r_compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        *T = x;
    }

    r_insertFixup(x,T);
    return(x);
}

E_Node *e_insertNode(char* data,E_Node** T) {
    E_Node *current, *parent, *x;

    current = *T;
    parent = 0;
    while (current != E_NIL) {
        if (e_compEQ(data, current->data)) return (current);
        parent = current;
        current = e_compLT(data, current->data) ?
                  current->left : current->right;
    }

    if ((x = malloc (sizeof(*x))) == 0) {
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = E_NIL;
    x->right = E_NIL;

    if(parent) {
        if(e_compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        *T = x;
    }

    // e_insertFixup(x,T);
    return(x);
}

V_Node *v_insertNode(V data,V_Node** T) {
    V_Node *current, *parent, *x;

    current = *T;
    parent = 0;
    while (current != V_NIL) {
        if (v_compEQ(data, current->data)) return (current);
        parent = current;
        current = v_compLT(data, current->data) ?
                  current->left : current->right;
    }

    if ((x = malloc (sizeof(*x))) == 0) {
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = V_NIL;
    x->right = V_NIL;
    x->color = RED;

    if(parent) {
        if(v_compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        *T = x;
    }

    v_insertFixup(x,T);
    return(x);
}

void deleteFixup(Node *x,Node** T) {


    while (x != *T && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft (x->parent,T);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight (w,T);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft (x->parent,T);
                x = *T;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight (x->parent,T);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft (w,T);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight (x->parent,T);
                x = *T;
            }
        }
    }
    x->color = BLACK;
}

void r_deleteFixup(R_Node *x,R_Node** T) {

    while (x != *T && x->color == BLACK) {
        if (x == x->parent->left) {
            R_Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                r_rotateLeft (x->parent,T);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    r_rotateRight (w,T);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                r_rotateLeft (x->parent,T);
                x = *T;
            }
        } else {
            R_Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                r_rotateRight (x->parent,T);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    r_rotateLeft (w,T);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                r_rotateRight (x->parent,T);
                x = *T;
            }
        }
    }
    x->color = BLACK;
}

void v_deleteFixup(V_Node *x,V_Node** T) {

    while (x != *T && x->color == BLACK) {
        if (x == x->parent->left) {
            V_Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                v_rotateLeft (x->parent,T);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    v_rotateRight (w,T);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                v_rotateLeft (x->parent,T);
                x = *T;
            }
        } else {
            V_Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                v_rotateRight (x->parent,T);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    v_rotateLeft (w,T);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                v_rotateRight (x->parent,T);
                x = *T;
            }
        }
    }
    x->color = BLACK;
}


void deleteNode(Node *z,Node**T) {
    Node *x, *y;
    if (!z || z == NIL) return;
    if (z->left == NIL || z->right == NIL) {
        y = z;
    } else {
        y = z->right;
        while (y->left != NIL) y = y->left;
    }

    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        *T = x;

    if (y != z) z->data = y->data;


    if (y->color == BLACK)
        deleteFixup (x,T);

    free (y);
}

void r_deleteNode(R_Node *z,R_Node**T) {
    R_Node *x, *y;
    if (!z || z == R_NIL) return;
    if (z->left == R_NIL || z->right == R_NIL) {
        y = z;
    } else {
        y = z->right;
        while (y->left != R_NIL) y = y->left;
    }
    if (y->left != R_NIL)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        *T = x;

    if (y != z) z->data = y->data;


    if (y->color == BLACK)
        r_deleteFixup(x, T);

    free(y);
}

void v_deleteNode(V_Node *z,V_Node**T) {
    V_Node *x, *y;
    if (!z || z == V_NIL) return;
    if (z->left == V_NIL || z->right == V_NIL) {
        y = z;
    } else {
        y = z->right;
        while (y->left != V_NIL) y = y->left;
    }

    if (y->left != V_NIL)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        *T = x;

    if (y != z) z->data = y->data;


    if (y->color == BLACK)
        v_deleteFixup(x, T);

    free(y);
}

void e_deleteNode(E_Node *z,E_Node**T) {
    E_Node *x, *y;
    if (!z || z == E_NIL) return;
    if (z->left == E_NIL || z->right == E_NIL) {
        y = z;
    } else {
        y = z->right;
        while (y->left != E_NIL) y = y->left;
    }
    if (y->left != E_NIL)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        *T = x;

    if (y != z) z->data = y->data;



    free(y);
}

Node *findNode(T data,Node** T) {
    Node *current = *T;
    while(current != NIL)
        if(compEQ(data, current->data))
            return (current);
        else
            current = compLT (data, current->data) ?
                      current->left : current->right;
    return(0);
}

R_Node *r_findNode(R data,R_Node** T) {
    R_Node *current = *T;
    while(current != R_NIL)
        if(r_compEQ(data, current->data))
            return (current);
        else
            current = r_compLT (data, current->data) ?
                      current->left : current->right;
    return(0);
}

E_Node *e_findNode(char* data,E_Node** T) {
    E_Node *current = *T;
    while(current != E_NIL)
        if(e_compEQ(data, current->data))
            return (current);
        else
            current = e_compLT (data, current->data) ?
                      current->left : current->right;
    return(0);
}

V_Node *v_findNode(V data,V_Node** T) {
    V_Node *current = *T;
    while(current != V_NIL)
        if(v_compEQ(data, current->data))
            return (current);
        else
            current = v_compLT (data, current->data) ?
                      current->left : current->right;
    return(0);
}

void printTree(E_Node* T){
    E_Node* temp = T;
    if (temp != E_NIL)
    {
        printTree(temp->left);
        printf(" %s  ", (temp->data));
        printTree(temp->right);
    }
}

void printTree2(Node* T){
    Node* temp = T;
    if (temp != NIL)
    {
        printTree2(temp->left);
        printf(" %s %s  ", (temp->data).string,(temp->data).string2);
        printTree2(temp->right);
    }
}

void e_deleteTree(E_Node* node)
{
    if (node == E_NIL) return;
    e_deleteTree(node->left);
    e_deleteTree(node->right);
    free(node);
}

void v_deleteTree(V_Node* node)
{
    if (node == V_NIL) return;
    v_deleteTree(node->left);
    v_deleteTree(node->right);
    free(node);
}

void r_deleteTree(R_Node* node)
{
    if (node == R_NIL) return;

    r_deleteTree(node->left);
    r_deleteTree(node->right);

    free(node);
}

void deleteTree(Node* node)
{
    if (node == NIL) return;

    deleteTree(node->left);
    deleteTree(node->right);

    free(node);
}

void report();

void delrel(char* entity1, char* entity2, char* relationship);

void delent(char* entity);


E_Node* Entity_Root = E_NIL;
R_Node* Relation_Root = R_NIL;


int main() {
    char buffer[BUFFER_SIZE] = "";
    char* command;
    char *entity1;
    char *entity2;
    char *relationship;

    do{
        fgets(buffer,BUFFER_SIZE,stdin);
        command = strtok(buffer," ");
        if(strcmp(command,"addent") == 0){
            entity1 = strtok(NULL,"\"");
            addent(entity1);
        }
        else if(strcmp(command,"delent") == 0){
            entity1 = strtok(NULL,"\"");
            delent(entity1);
        }
        else if(strcmp(command,"addrel") == 0){
            entity1 = strtok(NULL,"\"");
            entity2 = strtok(NULL,"\"");
            entity2 = strtok(NULL,"\"");
            relationship = strtok(NULL,"\"");
            relationship = strtok(NULL,"\"");
            addrel(entity1,entity2,relationship);

        }
        else if(strcmp(command,"delrel") == 0){
            entity1 = strtok(NULL,"\"");
            entity2 = strtok(NULL,"\"");
            entity2 = strtok(NULL,"\"");
            relationship = strtok(NULL,"\"");
            relationship = strtok(NULL,"\"");
            delrel(entity1,entity2,relationship);
        }
        else if (strcmp(command,"report\n") == 0){
            report();
        }

    } while(strcmp(command,"end\n") != 0);

    //printTree(Entity_Root);



    return 0;

}



void addent(char* entity){
    E_Node* found;
    char* new;
    new = malloc(strlen(entity) * sizeof(char)+1);
    strcpy(new,entity);
    found = e_findNode(new,&Entity_Root);
    if(found == NULL)
        e_insertNode(new,&Entity_Root);
    else
        free(new);
}



void addrel(char* entity1, char* entity2, char* relationship){
    T sender; V receiver;R new_rel;
    Node* rel;R_Node* r_search;E_Node* first_entity;E_Node * second_entity;V_Node* rec;
    first_entity = e_findNode(entity1,&Entity_Root);
    second_entity = e_findNode(entity2,&Entity_Root);
    if ( first_entity == NULL || second_entity == NULL)
        return;
    receiver.receiver = second_entity->data;
    new_rel.relationship = relationship;
    r_search = r_findNode(new_rel,&Relation_Root);
    if(r_search != NULL) {  // SE IL TIPO DI RELAZIONE ESISTE
        sender.string = first_entity->data;
        sender.string2 = second_entity->data;
        rel = findNode(sender, &(r_search->data.Root_Sender));
        if (rel != NULL)
            return;
        r_search->data.n_elements += 1;
        insertNode(sender, &(r_search->data.Root_Sender));
        rec = v_findNode(receiver, &(r_search->data.Root_Receiver));
        if (rec != NULL) {  // SE IL RICEVENTE AVEVA GIA' UN COLLEGAMENTO ENTRANTE
            rec->data.n_receivers += 1;
            rec->data.Root_senders = insert(rec->data.Root_senders,first_entity->data);
            if (rec->data.n_receivers == r_search->data.max) {
                char* new_max_rec;
                new_max_rec = rec->data.receiver;
                e_insertNode(new_max_rec,&(r_search->data.max_receiver_tree));

            } else if (rec->data.n_receivers > r_search->data.max) {
                char* new_max_rec;
                r_search->data.max = rec->data.n_receivers;
                new_max_rec = rec->data.receiver;
                e_deleteTree(r_search->data.max_receiver_tree);
                r_search->data.max_receiver_tree = E_NIL;

                e_insertNode(new_max_rec,&(r_search->data.max_receiver_tree));



            }
        } else {  // SE IL RICEVENTE NON RICEVEVA NULLA PRIMA
            receiver.n_receivers = 1;
            receiver.Root_senders = NULL;
            receiver.Root_senders = insert(receiver.Root_senders,first_entity->data);
            v_insertNode(receiver, &(r_search->data.Root_Receiver));
            if(r_search->data.max == 1){
                char* new_max_rec;
                new_max_rec = receiver.receiver;
                e_insertNode(new_max_rec,&(r_search->data.max_receiver_tree));
            }

            }


        }

    else{  // IL TIPO DI RELAZIONE NON ESISTE
        char* new_max_rec;
        sender.string =  first_entity->data;
        sender.string2 = second_entity->data;
        receiver.n_receivers = 1;
        receiver.Root_senders = NULL;
        receiver.Root_senders = insert(receiver.Root_senders,first_entity->data);
        new_rel.relationship = malloc(sizeof(char)*strlen(relationship)+1);
        strcpy(new_rel.relationship,relationship);
        new_rel.max = 1;
        new_rel.n_elements = 1;
        new_rel.Root_Receiver = V_NIL;
        new_rel.Root_Sender = NIL;
        new_rel.max_receiver_tree = E_NIL;
        insertNode(sender,&(new_rel.Root_Sender));
        v_insertNode(receiver,&new_rel.Root_Receiver);
        new_max_rec = receiver.receiver;
        e_insertNode(new_max_rec,&new_rel.max_receiver_tree);
        r_insertNode(new_rel,&Relation_Root);
    }


    }






void produce_max_rec(E_Node* T)  {
    E_Node* temp = T;
    if (temp != E_NIL)
    {
        produce_max_rec(temp->left);
        putc('"',stdout);
        fputs((temp->data),stdout);
        putc('"',stdout);
        putc(' ',stdout);
        produce_max_rec(temp->right);
    }

}

void produce_output(R_Node* T){
    R_Node* temp = T;
    if (temp != R_NIL)
    {
        produce_output(temp->left);
        putc('"',stdout);
        fputs((temp->data).relationship,stdout);
        putc('"',stdout);
        putc(' ',stdout);
        produce_max_rec((temp->data).max_receiver_tree);
        printf("%d; ", temp->data.max);
        produce_output(temp->right);
    }


}

void report(){
    R_Node* temp = Relation_Root;
    if (temp != R_NIL)
    {
        produce_output(Relation_Root);
        printf("\n");
    }
    else{
        printf("none\n");
    }

}

void fix_max_rec(V_Node* root,E_Node** max_root,int max){
    V_Node* temp = root;
    if (temp != V_NIL)
    {
        fix_max_rec(temp->left,max_root,max);
        if(temp->data.n_receivers == max){
            char* new_max;
            new_max = temp->data.receiver;
            e_insertNode(new_max,max_root);
        }
        fix_max_rec(temp->right,max_root,max);
    }
}



int find_send_node(char* data,char* rel,Node** T) {
    Node *current = *T;
    while(current != NIL)
        if(strcmp(data,current->data.string) == 0){
            delrel(data,current->data.string2,rel);
            return 1;
        }
        else{
            if(strcmp(data,current->data.string) < 0)
                current = current->left;
            else
                current = current->right;
        }

    return(0);
}


void del_senders(struct TreeNode* T,char*rec,char*rel){
    struct TreeNode* temp = T;
    if (temp != NULL)
    {
        del_senders(temp->right,rec,rel);
        del_senders(temp->left,rec,rel);
        delrel(temp->data,rec,rel);
    }
}

void del_all_type(R_Node* root,char* ent){
    R_Node* temp = root;
    V rec;V_Node* search;
    if (temp != R_NIL)
    {
        del_all_type(temp->left,ent);
        del_all_type(temp->right,ent);
        while(find_send_node(ent,temp->data.relationship,&temp->data.Root_Sender) == 1){
        }
        rec.receiver = ent;
        search = v_findNode(rec,&temp->data.Root_Receiver);
        if(search != NULL){
            del_senders(search->data.Root_senders,ent,temp->data.relationship);
        }


    }
}

void delent(char* entity){
    E_Node* search;
    search = e_findNode(entity,&Entity_Root);
    if(search == NULL)
        return;
    del_all_type(Relation_Root,entity);
    free(search->data);
    e_deleteNode(search,&Entity_Root);


}



void delrel(char* entity1, char* entity2, char* relationship){
    R_Node* r_search; Node* s_search;V_Node* rec_search;
    R rel;T sender;V rec;
    rel.relationship = relationship;
    r_search = r_findNode(rel,&Relation_Root);
    if(r_search == NULL) // SE IL TIPO DI REL NON ESISTE
        return;
    sender.string = entity1;
    sender.string2 = entity2;
    s_search = findNode(sender,&(r_search->data.Root_Sender));
    if(s_search == NULL) // SE LA REL NON ESISTE
        return;
    if(r_search->data.n_elements == 1){ // SE IL TIPO DI REL HA UNA SOLA REL
        deleteTree(r_search->data.Root_Sender);
        e_deleteTree(r_search->data.max_receiver_tree);
        r_search->data.max_receiver_tree = E_NIL;
        (r_search->data.Root_Receiver)->data.Root_senders = makeEmpty((r_search->data.Root_Receiver)->data.Root_senders );
        v_deleteTree(r_search->data.Root_Receiver);
        r_search->data.Root_Receiver = V_NIL;
        r_search->data.Root_Sender = NIL;
        free(r_search->data.relationship);
        r_deleteNode(r_search,&Relation_Root);
    }
    else{  // IL TIPO DI REL HA PIU' REL
        r_search->data.n_elements -= 1;
        deleteNode(s_search,&(r_search->data.Root_Sender));
        rec.receiver = entity2;
        rec_search = v_findNode(rec,&(r_search->data.Root_Receiver));
        rec_search->data.Root_senders = delete(rec_search->data.Root_senders,entity1);

        if(rec_search->data.n_receivers < r_search->data.max){ // SE IL RICEVENTE NON E' IL MASSIMO RICEVENTE
            if(rec_search->data.n_receivers == 1){
                v_deleteNode(rec_search,&(r_search->data.Root_Receiver));
            }
            else{
                rec_search->data.n_receivers -= 1;
            }
        }
        else{ // IL RICEVENTE E' IL MAX REC
           if( (r_search->data.max_receiver_tree)->left != E_NIL ||  (r_search->data.max_receiver_tree)->right != E_NIL){
               // CI SONO PIU' MAX REC
               char* max_rec;
               E_Node* max_search;
               max_rec = rec.receiver;
               max_search = e_findNode(max_rec,&(r_search->data.max_receiver_tree));
               e_deleteNode(max_search,&(r_search->data.max_receiver_tree));
               if(rec_search->data.n_receivers == 1){
                   v_deleteNode(rec_search,&(r_search->data.Root_Receiver));
               }
               else{
                   rec_search->data.n_receivers -= 1;
               }
           }

           else{ // IL REC E' L'UNICO MAX REC ( DEVO RICALCOLARE IL MAX REC )
               e_deleteTree(r_search->data.max_receiver_tree);
               rec_search->data.n_receivers -= 1;
               r_search->data.max_receiver_tree = E_NIL;
               r_search->data.max -= 1;
               fix_max_rec(r_search->data.Root_Receiver,&(r_search->data.max_receiver_tree),r_search->data.max);

           }
        }

    }







}








