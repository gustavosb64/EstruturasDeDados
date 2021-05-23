typedef int elem;
typedef struct node_ Node;
typedef struct tree_ Tree;

Tree* CreateTree();
int IsEmptyTree(Tree *T);
int TreeHeight(Node *node);
int IsInABB(Tree *T, elem x);
Node* SearchABB(Node *node, elem x);
int AddABB(Tree *T, elem x);
int InsertNode(Node **node, elem x);
int RemoveABB(Tree *T, elem x);
//int RemoveNode(Node **node, elem x);
int RemoveNode(Tree *T, elem x);
int remover(Node **p, elem *x);
void FreeTree(Node *node);

void PrintPreOrdem(Node *node);
void PrintPosOrdem(Node *node);
void PrintEmOrdem(Node *node);
