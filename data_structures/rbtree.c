#include "rbtree.h"

enum {RED, BLACK};

typedef struct stNode{
    Element element;
    int color;
    struct stNode* parent;
    struct stNode* left;
    struct stNode* right;
} *NodeImp;

typedef struct stTree{
	NodeImp root;
	NodeImp nil;
	int (*comparator)(Element, Element);
} *TreeImp;

Tree createRBTree(int (*comparator)(Element, Element)){
	TreeImp tree = (TreeImp) malloc(sizeof(struct stTree));
	tree->nil = (NodeImp) malloc(sizeof(struct stNode));
	tree->nil->color = BLACK;
	tree->nil->element = NULL;
	tree->root = tree->nil;
	tree->comparator = comparator;
	return tree;
}

Element getElement(Tree t, Node n){
	TreeImp tree = (TreeImp) t;
    NodeImp node = (NodeImp) n;

    if(node != tree->nil)
        return node->element;
    return NULL;
}

Node getTreeRoot(Tree t){
	TreeImp tree = (TreeImp) t;

	return tree->root;
}

void rotateRight(TreeImp tree, NodeImp node){
    NodeImp l = node->left;

	node->left = l->right;
    if(l->right != tree->nil)
        l->right->parent = node;

    l->parent = node->parent;
    if(node->parent == tree->nil)
    	tree->root = l;
    else if(node->parent->left == node)
    	node->parent->left = l;
    else
    	node->parent->right = l;
    
    l->right = node;
    node->parent = l;
}

void rotateLeft(TreeImp tree, NodeImp node){
    NodeImp r = node->right;

    node->right = r->left;
    if(r->left != tree->nil)
    	r->left->parent = node;

    r->parent = node->parent;
    if(node->parent == tree->nil)
    	tree->root = r;
    else if(node->parent->left == node)
    	node->parent->left = r;
    else
    	node->parent->right = r;

    r->left = node;
    node->parent = r;
}

Node findNode(Tree t, Element element){
    TreeImp tree = (TreeImp) t;
    NodeImp node = tree->root;

    while(node != tree->nil){
    	int result = tree->comparator(element, node->element);

    	if(result < 0)
    		node = node->left;
    	else if(result > 0)
    		node = node->right;
    	else
    		return node;
    }

    return NULL;
}

void fixInsert(TreeImp tree, NodeImp node){

	while(node != tree->root && node->parent != tree->root && node->parent->color == RED){
		if(node->parent == node->parent->parent->left){
			NodeImp uncle = node->parent->parent->right;
			if(uncle->color == RED){
				//First Case
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else{
				if(node == node->parent->right){
					//Second Case
					node = node->parent;
					rotateLeft(tree, node);
				}
				//Third Case
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateRight(tree, node->parent->parent);
			}
		}
		else{
			NodeImp uncle = node->parent->parent->left;
			if(uncle->color == RED){
				//Fourth Case
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else{
				if(node == node->parent->left){
					//Fifth Case
					node = node->parent;
					rotateRight(tree, node);
				}
				//Sixth Case
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rotateLeft(tree, node->parent->parent);
			}
		}
	}
	tree->root->color = BLACK;
}

void insertNode(Tree t, Element element){
	TreeImp tree = (TreeImp) t;

	NodeImp node = (NodeImp) malloc(sizeof(struct stNode));
	node->left = tree->nil;
	node->right = tree->nil;
	node->color = RED;
	node->element = element;

	if(tree->root == tree->nil){
		node->parent = tree->nil;
		tree->root = node;
	}
	else{
		NodeImp previousNode;
		NodeImp currentNode = tree->root;
		int compareResult;

		while(currentNode != tree->nil){
			previousNode = currentNode;
			compareResult = tree->comparator(element, currentNode->element);

			if(compareResult < 0)
				currentNode = currentNode->left;
			else
				currentNode = currentNode->right;
		}
		node->parent = previousNode;
		if(compareResult < 0)
			previousNode->left = node;
		else
			previousNode->right = node;
	}

	fixInsert(tree, node);
}

void fixRemove(TreeImp tree, NodeImp node){
	NodeImp replacement;
	NodeImp x;
	NodeImp xs; // x's sibling

	bool xLeftChild;

	//First Step
	if(node->left == tree->nil && node->right == tree->nil){
		// Two nil children
		replacement = tree->nil;
		x = replacement;
		x->parent = node->parent;
		if(node->parent != tree->nil && node->parent->left == node)
			xLeftChild = true;
		else
			xLeftChild = false;
	}
	else if(node->left == tree->nil && node->right != tree->nil){
		// One nil child on the left
		replacement = node->right;
		x = replacement;
		x->parent = node->parent;
		xLeftChild = false;
	}
	else if(node->left != tree->nil && node->right == tree->nil){
		// One nil child on the right
		replacement = node->left;
		x = replacement;
		x->parent = node->parent;
		xLeftChild = true;
	}
	else{
		// Zero nil children

		replacement = node->right;
		// Find successor to node
		while(replacement->left != tree->nil)
			replacement = replacement->left;
		x = replacement->right;
		if(replacement != node->right){
			//replacement->parent->left = x;
			replacement->left = node->left;
			replacement->right = node->right;
			replacement->left->parent = replacement;
			replacement->right->parent = replacement;
			x->parent = replacement->parent;
			x->parent->left = x;
			xLeftChild = true;
		}
		else{
			x->parent = replacement;
			replacement->left = node->left;
			node->left->parent = replacement;
			xLeftChild = false;
		}
	}

	// Finish replace removed node with it's replacement
	if(node->parent != tree->nil){
		if(node->parent->left == node)
			node->parent->left = replacement;
		else
			node->parent->right = replacement;
	}
	else{
		tree->root = replacement;
	}

	if(replacement != tree->nil)
		replacement->parent = node->parent;

	// Second Step
	if(node->color == RED && (replacement->color == RED || replacement == tree->nil)){
		return;
	}
	else if(node->color == RED && replacement->color == BLACK){
		replacement->color = RED;
	}
	else if(node->color == BLACK && replacement->color == RED){
		replacement->color = BLACK;
		return;
	}

	// Third Step
	while(x != tree->root){
		// Find x's sibling
		if(xLeftChild)
			xs = x->parent->right;
		else
			xs = x->parent->left;

		if(x->color == RED){
			// Zero Case
			x->color = BLACK;
			return;
		}
		else{
			if(xs->color == RED){
				// First Case
				xs->color = BLACK;
				x->parent->color = RED;
				if(xLeftChild){
					rotateLeft(tree, x->parent);
					xs = x->parent->right;
				}
				else{
					rotateRight(tree, x->parent);
					xs = x->parent->left;
				}
			}
			if(xs->color == BLACK){
				if(xs->left->color == BLACK && xs->right->color == BLACK){
					//Second Case
					xs->color = RED;
					x = x->parent;
					xLeftChild = x == x->parent->left;
					if(x->color == RED){
						x->color = BLACK;
						return;
					}
					continue;
				}
				else if(xLeftChild && xs->left->color == RED && xs->right->color == BLACK
					|| !xLeftChild && xs->right->color == RED && xs->left->color == BLACK){
					// Third Case
					xs->color = RED;
					if(xLeftChild){
						xs->left->color = BLACK;
						rotateRight(tree, xs);
						xs = x->parent->right;
					}
					else{
						xs->right->color = BLACK;
						rotateLeft(tree, xs);
						xs = x->parent->left;
					}
				}
				// Fourth Case
				xs->color = x->parent->color;
				x->parent->color = BLACK;
				if(x->parent->left == x){
					xs->right->color = BLACK;
					rotateLeft(tree, x->parent);
				}
				else{
					xs->left->color = BLACK;
					rotateRight(tree, x->parent);
				}
				return;
			}
		}
	}
}

void removeNode(Tree t, Element element){
	TreeImp tree = (TreeImp) t;

	NodeImp node = findNode(tree, element);

	if(node == tree->nil)
		return;

	fixRemove(tree, node);

	free(node->element);
	free(node);
}

void destroyNodes(TreeImp tree, NodeImp node){

	if(node->left != tree->nil)
		destroyNodes(tree, node->left);
	free(node->element);
	if(node->right != tree->nil)
		destroyNodes(tree, node->right);

	free(node);
}

void destroyRBTree(Tree t){
    TreeImp tree = (TreeImp) t;
    
    if(tree->root != tree->nil){
    	destroyNodes(tree, tree->root);
    }
    free(tree->nil);
    free(tree);
}

Element getElementById(Tree t, char id[], char *(getID)(Element)){
    TreeImp tree = (TreeImp) t;
    NodeImp node = tree->root;

    while(node != tree->nil){
		int result = strcmp(id, getID(node->element));
		
    	if(result < 0)
    		node = node->left;
    	else if(result > 0)
    		node = node->right;
    	else
    		return node->element;
    }
    
    return NULL;
}

/*Element getElementByIdInLists(Node t1, Node t2, Node t3, Node t4, char id[]){
    Element element;

    element = getElementById(t1, id);
    if(element == NULL)
        element = getElementById(t2, id);
    if(element == NULL)
        element = getElementById(t3, id);
    if(element == NULL)
        element = getElementById(t4, id);

    return element;
}*/

/*void printTree(Node n, int level){
	NodeImp node = (NodeImp) n;

	if(node == NULL){
		return;
	}
	else{
		for(int i = 0; i < level; i++){
			printf("   ");
		}
		printf("%s\n", Pessoa_getCpf(node->element));
		printArvore(node->left, level + 1);
		printArvore(node->right, level + 1);
	}
}*/

void printTreeElements(Tree t, Node n, FILE *arqSVG, void (*printElement)(FILE*, Element)){
	TreeImp tree = (TreeImp) t;
	NodeImp node = (NodeImp) n;

	if(node == tree->nil) return; 

	if(node != tree->nil)
		printTreeElements(tree, node->left, arqSVG, printElement);

	printElement(arqSVG, node->element);

	if(node != tree->nil)
		printTreeElements(tree, node->right, arqSVG, printElement);

}

/*int Y_PRINT_ARVORE = 15;

void printTreeInSVG_util(TreeImp tree, Node n, int x, FILE* svg){
	NodeImp node = (NodeImp) n;

	if(node == tree->nil) return;

	x+=20;
	Arvore_escreverSvg_util(tree, node->left, x, svg);

	fprintf(svg, "<circle cx=\"%d\" cy=\"%d\" r=\"5\" stroke=\"black\" fill=\"%s\" stroke-width=\"2\" />\n", 
            Y_PRINT_ARVORE,
            x,
            node->color == RED ? "red" : "black");
	fprintf(svg, "<text x=\"%d\" y=\"%d\" fill=\"white\" font-size=\"5\">%s</text>",
        Y_PRINT_ARVORE, 
        x, 
        Pessoa_getCpf(node->element));
	Y_PRINT_ARVORE+=13;

	Arvore_escreverSvg_util(tree, node->right, x, svg);
}

void printTreeInSVG(Tree t, FILE* svg){
	TreeImp tree = (TreeImp) t;
	NodeImp node = (NodeImp) tree->root;

	fprintf(svg, "<svg width=\"1000\" height=\"1000\">\n");
	Arvore_escreverSvg_util(tree, node, 0, svg);
	fprintf(svg, "</svg>\n");
}*/