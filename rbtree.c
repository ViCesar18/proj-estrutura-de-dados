#include "rbtree.h"

enum {RED, BLACK};

typedef struct stNode{
    Element element;
    int color;
    Node parent;
    Node left;
    Node right;
} *Node;

Tree createTree(){
    return NULL;
}

Tree initialize(Tree p, Element element){
    Node tree = (Node) p;

    tree = (Node) malloc(sizeof(struct stNode));
    tree->left = tree->right = NULL;
    tree->parent = p;
    tree->element = element;
    tree->color = RED;

    return tree;
}

Tree grandparent(Tree n){
    Node node = (Node) n;

    if(node == NULL || node->parent == NULL)
        return NULL;
    else
        return node->parent->parent;
}

Tree getRight(Tree n){
    Node node = (Node) n;

    if(node != NULL)
        return node->right;
    return NULL;
}

Tree getLeft(Tree n){
    Node node = (Node) n;

    if(node != NULL)
        return node->left;
    return NULL;
}

Element getElement(Tree n){
    Node node = (Node) n;

    if(node != NULL)
        return node->element;
    return NULL;
}

Tree uncle(Tree n){
    Node node = (Node) n;
    
    Node g = grandparent(n);
    if(node == NULL || g == NULL)
        return NULL;
    else if(node->parent == g->right)
        return g->left;
    else
        return g->right;
}

Tree sibling(Tree n){
    Node node = (Node) n;

    if(node == NULL)
        return NULL;
    else if(node == node->parent->left)
        return node->parent->right;
    else
        return node->parent->left;
}

Tree colorOf(Tree n){
    Node node = (Node) n;

    return n == NULL ? BLACK : node->color;
}

void nNodes(Tree n, int *size){
    Node node = (Node) n;

    (*size++);

    if(node->left != NULL)
        getSize(node->left, &(*size));
    if(node->right != NULL)
        getSize(node->right, &(*size));
}

void insertNode(Tree* tree, Element element, int comparator(Element, Element)){
    Node* node = (Node*) tree;

    int pl = 0;
    Node ptr, btr = NULL, newNode;

    /*Maneira foda*/
    for(ptr = *node; ptr != NULL;
    btr = ptr, ptr = ((pl = comparator(element, ptr->element)) ? ptr->right : ptr->left));

    /*Maneira clara*/
    /*for(ptr = *node; ptr != NULL; ptr = (comparator(element, ptr->element) ? ptr->right : ptr->left)){
        btr = ptr;
        pl = comparator(element, ptr->element);
    }*/

    newNode = initialize(btr, element);

    if(btr != NULL)
        (pl) ? (btr->right = newNode) : (btr->left = newNode);
    
    insertUtil(newNode);
    for(ptr = newNode; ptr != NULL; btr = ptr, ptr = ptr->parent);
    *node = btr;
}

void insertUtil(Tree n){
    Node node = (Node) n;

    Node u = uncle(n), g = grandparent(n), p = node->parent;

    if(p == NULL)
        node->color = BLACK;
    else if(p->color == BLACK)
        return;
    else if(u != NULL && u->color == RED){
        p->color = BLACK;
        u->color = BLACK;
        g->color = RED;

        insertUtil(g);
    }
    else{
        if(node == p->right && p == g->left){
            rotateLeft(p);
            node = node->left;
        }
        else if(node == p->left && p == g->right){
            rotateRight(p);
            node = node->right;
        }

        g = grandparent(n);
        p = node->parent;

        p->color = BLACK;
        g->color = RED;

        if(node == p->left)
            rotateRight(g);
        else
            rotateLeft(g);
    }
}

void replaceNode(Tree *t, Tree o, Tree n){
    Node* tree = (Node*) t;
    Node nodeSub = (Node) o;
    Node node = (Node) n;
    
    if(nodeSub->parent == NULL)
        *tree = node;
    else{
        if(nodeSub == nodeSub->parent->left)
            nodeSub->parent->left = node;
        else
            nodeSub->parent->right = node;
    }

    if(node != NULL)
        node->parent = node->parent;
}

void removeNode(Tree *t, Element element, int comparator(Element, Element)){
    Node* tree = (Node*) t;

    Node n = findNode(&tree, element, comparator), c;

    if(n == NULL)
        return;
    if(n->left != NULL && n->right != NULL){
        Node pred = n->left;
        while(pred->right != NULL)
            pred = pred->right;
        n = pred;
    }

    c = n->right == NULL ? n->left : n->right;
    if(n->color == BLACK){
        n->color = colorOf(c);
        removeUtil(n);
    }

    replaceNode(&tree, n, c);
    free(n);
}

void removeUtil(Tree n){
    Node node = (Node) n;

    if(node->parent == NULL)
        return;
    
    Node s = sibling(n);
    if(colorOf(s) == RED){
        node->parent->color = RED;
        s->color = BLACK;
        if(node == node->parent->left)
            rotateLeft(node);
        else
            rotateRight(node);
    }
    else if(colorOf(node->parent) == BLACK && colorOf(s) == BLACK && colorOf(s->left) == BLACK && colorOf(s->right) == BLACK){
        s->color = RED;
        removeUtil(node->parent);
    }
    else if(colorOf(node->parent) == RED && colorOf(s) == BLACK && colorOf(s->left) == BLACK && colorOf(s->right) == BLACK){
        s->color = RED;
        node->parent->color = BLACK;
    }
    else{
        if(node == node->parent->left && colorOf(s) == BLACK && colorOf(s->left) == RED && colorOf(s->right) == BLACK){
            s->color = RED;
            s->left->color = BLACK;
            rotateRight(s);
        }
        else if(node == node->parent->right && colorOf(s) == BLACK && colorOf(s->right) == RED && colorOf(s->left) == BLACK){
            s->color = RED;
            s->right->color = BLACK;
            rotateLeft(s);
        }

        s->color = colorOf(node->parent);
        node->parent->color = BLACK;
        if(node == node->parent->left){
            s->right->color = BLACK;
            rotateLeft(node->parent);
        }
        else{
            s->left->color = BLACK;
            rotateRight(node->parent);
        }
    }
}

void rotateRight(Tree n){
    Node node = (Node) n;

    Node l = node->left;
    Node p = node->parent;

    if(l->right != NULL)
        l->right->parent = node;
    
    node->left = l->right;
    node->parent = l;
    l->right = node;
    l->parent = p;

    if(p != NULL){
        if(p->right == node)
            p->right = l;
        else
            p->left = l;
    }
}

void rotateLeft(Tree n){
    Node node = (Node) n;

    Node r = node->right;
    Node p = node->parent;

    if(r->left != NULL)
        r->left->parent = node;
    
    node->right = r->left;
    node->parent = r;
    r->left = node;
    r->parent = p;

    if(p != NULL){
        if(p->right == node)
            p->right = r;
        else
            p->left = r;
    }
}

Tree findNode(Tree *t, Element element, int comparator(Element, Element)){
    Node* tree = (Node*) t;
    Node ptr;

    for(ptr = *tree; ptr != NULL && ptr->element != element; ptr = comparator(element, ptr->element) ? ptr->right : ptr->left);

    return ptr;
}

void freeRBTree(Tree t){
    Node tree = (Node) tree;
    
    if(tree == NULL)
        return;
    freeRBTree(tree->left);
    freeRBTree(tree->right);
    free(tree);
}

Tree getElementById(Tree n, char id[]){
    Node node = (Node) n;

    if(strcmp(getFormId(node->element), id))
        node = getElementById(node->left, id);
    else
        node = getElementById(node->right, id);
    
    return n;
}

Element getElementByIdInLists(Tree t1, Tree t2, Tree t3, Tree t4, char id[]){
    Element element;

    element = getElementById(t1, id);
    if(element == NULL)
        element = getElementById(t2, id);
    if(element == NULL)
        element = getElementById(t3, id);
    if(element == NULL)
        element = getElementById(t4, id);

    return element;
}

void printTree(Tree treeAux, FILE *arqOut, void print(FILE*, Element)){
    Node tree = (Node) treeAux;
    int j = 0;

    printf(arqOut, tree->element);
    printTree(tree->left, arqOut, print);
    printTree(tree->right, arqOut, print);
}

void printBuildingTree(Tree blockAux, Tree buildingAux, FILE *arqOut){
    Node building = (Node) buildingAux;
    Node blockRoot = (Node) blockAux;

    /*for(int i = buildings->start; i != NULO; i = buildings->node[i].next){
        block = getElementById(blocks, getBuildingCep(buildings->node[i].element), type);
        
        printBuilding(arqOut, buildings->node[i].element, block);
    }*/
        
    Block block = getElementById(blockRoot, getBuildingCep(building->element));
    printBuilding(arqOut, building->element, block);
    printBuildingTree(blockRoot, building->left, arqOut);
    printBuildingtree(blockRoot, building->right, arqOut);
}