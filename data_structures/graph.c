#include "graph.h"

enum {WHITE, GREY, BLACK};
typedef struct gNodeSt *gNodeImp;

typedef struct gVertexSt{
	char id[32];
	double x, y;
	int color;
	int dist;
	struct gVertexSt *p;
	gNodeImp node;
} *gVertexImp;

typedef struct edgeSt{
	gVertexImp source, destiny;
	char street[32];
	char bRight[32];
	char bLeft[32];
	double length;
	double speed;
} *edgeImp;

typedef struct gNodeSt{
	gVertexImp vertex;
	edgeImp edge;
	struct gNodeSt *next;
} *gNodeImp;

typedef struct graphSt{
	int nVertexes;
	gNodeImp *vertexes;
	int free;
} *graphImp;

Graph createGraph(int size){
	graphImp graph = (graphImp) malloc(sizeof(struct graphSt));

	graph->nVertexes = size;
	graph->vertexes = (gNodeImp*) malloc(size * sizeof(gNodeImp));
	memset(graph->vertexes, 0, size * sizeof(gNodeImp));
	graph->free = 0;

	return graph;
}

double getGraphVertexDist(GNode n){
	gNodeImp node = (gNodeImp) n;

	return node->vertex->dist;
}

bool addVertex(Graph g, char *id, double x, double y){
    graphImp graph = (graphImp) g;

	if(graph->free >= graph->nVertexes) return false;

	gVertexImp vertex = (gVertexImp ) malloc(sizeof(struct gVertexSt));
	strcpy(vertex->id, id);
	vertex->x = x;
	vertex->y = y;

	gNodeImp node = (gNodeImp) malloc(sizeof(struct gNodeSt));
	node->vertex = vertex;
	node->edge = NULL;
	node->next = NULL;
	vertex->node = node;

	graph->vertexes[graph->free] = node;
	graph->free++;

	return true;
}

bool addEdge(Graph g, char *id1, char *id2, char *street, char *bR, char *bL, double length, double speed){
    graphImp graph = (graphImp) g;
	gVertexImp v1 = NULL, v2 = NULL;
	gNodeImp n;

	for(int i = 0; i < graph->free; i++){
		if(!strcmp(id1, graph->vertexes[i]->vertex->id)){
			n = graph->vertexes[i];
			v1 = n->vertex;
		}
		if(!strcmp(id2, graph->vertexes[i]->vertex->id))
			v2 = graph->vertexes[i]->vertex;

        if(v1 != NULL && v2 != NULL) break;
	}

	if(v1 == NULL || v2 == NULL) return false;

	edgeImp edge = (edgeImp) malloc(sizeof(struct edgeSt));
	edge->source = v1;
	edge->destiny = v2;
	strcmp(edge->street, street);
	strcmp(edge->bRight, bR);
	strcmp(edge->bLeft, bL);
	edge->length = length;
	edge->speed = speed;

	gNodeImp newNode = (gNodeImp) malloc(sizeof(struct gNodeSt));
	newNode->vertex = v2;
	newNode->edge = edge;
	newNode->next = NULL;

	while(n->next != NULL)
		n = n->next;

	n->next = newNode;

	return true;
}

void depthSearch_Aux(graphImp graph, gNodeImp u, int cont){
	u->vertex->color = GREY;
	u->vertex->dist = cont;

	for(gNodeImp v = u->next; v != NULL; v = v->next){
		if(v->vertex->color == WHITE){
			v->vertex->p = u->vertex;
			depthSearch_Aux(graph, v->vertex->node, cont + 1);
		}
	}

	u->vertex->color = BLACK;
}

bool depthSearch(graphImp graph, char *id){
	gNodeImp start = NULL;

	for(int i = 0; i < graph->free; i++){
		if(!strcmp(graph->vertexes[i]->vertex->id, id)){
			start = graph->vertexes[i];
			break;
		}
	}

	if(start == NULL) return false;

	for(int i = 0; i < graph->free; i++){
		graph->vertexes[i]->vertex->color = WHITE;
		graph->vertexes[i]->vertex->p = NULL;

	}

	int cont = 0;
	depthSearch_Aux(graph, start, cont);

	return true;
}

bool widthSearch(graphImp graph, char *id){
	gNodeImp start = NULL;
	for(int i = 0; i < graph->free; i++){
		if(!strcmp(graph->vertexes[i]->vertex->id, id)){
			start = graph->vertexes[i];
			break;
		}
	}

	if(start == NULL) return false;

	for(int i = 0; i < graph->free; i++){
		graph->vertexes[i]->vertex->color = WHITE;
		graph->vertexes[i]->vertex->p = NULL;
		graph->vertexes[i]->vertex->dist = -1;
	}

	start->vertex->color = BLACK;
	start->vertex->dist = 0;
	start->vertex->p = NULL;

	Queue queue = createQueue();
	insertQueue(queue, start);

	while(getQueueSize(queue) != 0){
		gNodeImp u = removeQueue(queue);

		for(gNodeImp v = u->next; v != NULL; v = v->next){
			if(v->vertex->color == WHITE){
				v->vertex->color = BLACK;
				v->vertex->dist = u->vertex->dist + 1;
				v->vertex->p = u->vertex;
				insertQueue(queue, v->vertex->node);
			}
		}
	}
}

void relax_Dijkstra(gNodeImp u, gNodeImp v, bool itsSpeed){
	double edgeWeight;

	if(itsSpeed)
		edgeWeight = v->edge->speed;
	else
		edgeWeight = v->edge->length;

	printf("%lf\n", edgeWeight);

	if(v->vertex->dist < 0){
		v->vertex->dist = u->vertex->dist + edgeWeight;
		v->vertex->p = u->vertex;
	}
	else{
		if(v->vertex->dist > u->vertex->dist + edgeWeight){
			v->vertex->dist = u->vertex->dist + edgeWeight;
			v->vertex->p = u->vertex;
		}
	}
}

bool shortestWat_Dijkstra(Graph g, char *id, bool itsSpeed){
	graphImp graph = (graphImp) g;

	gNodeImp start = NULL;
	for(int i = 0; i < graph->free; i++){
		if(!strcmp(graph->vertexes[i]->vertex->id, id)){
			start = graph->vertexes[i];
			break;
		}
	}

	if(start == NULL) return false;

	Queue priorQueue = createQueue();

	for(int i = 0; i < graph->free; i++){
		graph->vertexes[i]->vertex->dist = -1;
		graph->vertexes[i]->vertex->p = NULL;
		insertQueue(priorQueue, graph->vertexes[i]);
	}
	start->vertex->dist = 0;

	while(getQueueSize(priorQueue) != 0){
		gNodeImp u = removePrior(priorQueue);

		for(gNodeImp v = u->next; v != NULL; v = v->next){
			relax_Dijkstra(u, v, itsSpeed);
		}
	}

	return true;
}

void printVertexInformation(Graph g){
	graphImp graph = (graphImp) g;

	for(int i = 0; i < graph->free; i++){
		printf("id: %s dist: %d ant: %s\n", graph->vertexes[i]->vertex->id, graph->vertexes[i]->vertex->dist, graph->vertexes[i]->vertex->p->id);
	}
}

void destroyGraph(Graph g){
	graphImp graph = (graphImp) g;

	for(int i = 0; i < graph->free; i++){
		gNodeImp node = graph->vertexes[i];

		free(node->vertex);
		while(node != NULL){
			free(node->edge);

			gNodeImp nextNode = node->next;
			free(node);
			node = nextNode;
		}
	}
	free(graph->vertexes);
	free(graph);
}