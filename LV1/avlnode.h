struct AVLNode_
{
    char x;
    int height;
    struct AVLNode_* left;
    struct AVLNode_* right;
};
typedef struct AVLNode_ AVLNode;