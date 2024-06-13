#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_SIZE 10

typedef struct graphNode{
    int vertex;
    struct graphNode* next;
} graphNode;

typedef struct graph{
    int vertexnum;
    graphNode* adj_list[MAX_VERTEX_SIZE];
} graph;

void Init(graph* g);
void InsertVertex(graph *g, int v); // 정점의 이름을 입력받으면 정점을 생성하는 함수
void InsertEdge(graph *g, int v1, int v2); // 정점 두개를 입력받아 간선을 생성하는 함수
int IsEmpty(graph *g); // 그래프가 비어있는지 확인하는 함수
void printGraph(graph *g); // 그래프를 출력하는 함수
void DFS(graph *g, int v); //시작 정점인 v를 입력받아 깊이 우선 탐색
void BFS(graph *g, int v); //시작 정점인 v를 입력받아 너비 우선 탐색


void Init(graph* g){
    g->vertexnum = 0;   //정점의 수를 0으로 설정한다.
    for(int i = 0; i < MAX_VERTEX_SIZE; i++){
        g->adj_list[i] = NULL;  //생성된 정점의 연결리스트를 모두 NULL로 초기화한다.
    } 
}

void InsertVertex(graph* g, int v){
    if(g->vertexnum >= MAX_VERTEX_SIZE){    //정점의 수가 MAX_VERTEX_SIZE(10)보다 크면 경고문을 출력하고 리턴한다. 
        printf("Graph is full!!\n");
        return;
    }
    if(v < 0 || v > 9){
        printf("invaild vertex number!!\nInput 0~9 number.");   //입력된 정점의 이름이 0~9 사이가 아니라면 경고문을 출력하고 리턴한다.
        return;
    }
    if(g->adj_list[v] != NULL) {    //이미존재하는 정점의 이름이 입력된 경우에 경고문을 출력하고 리턴한다.
        printf("Vertex already exists!!\n");
        return;
    }
    g->adj_list[v] = (graphNode*)malloc(sizeof(graphNode)); //adj_list[v]에 메모리를 할당한다.
    g->adj_list[v]->vertex = v; //adj_list[v]의 vertex에 v를 저장한다.
    g->adj_list[v]->next = NULL;    //adj_list[v]의 next를 NULL로 초기화한다.
    g->vertexnum++; //정점의 수를 1 증가시킨다.
}

void InsertEdge(graph *g, int v1, int v2){
    if(g->adj_list[v1] == NULL || g->adj_list[v2] == NULL){ //입력된 정점이 존재하지 않는 경우 경고문을 출력하고 리턴한다.
        printf("Vertices not found!!\n");
        return;
    }
    graphNode* edge = (graphNode*)malloc(sizeof(graphNode)); //간선을 생성하기 위해 메모리를 할당한다.
    edge->vertex = v2;  //edge의 vertex에 v2를 저장한다.
    edge->next = g->adj_list[v1]->next; //edge의 next에 adj_list[v1]의 next를 저장한다.
    g->adj_list[v1]->next = edge;   //adj_list[v1]의 next에 edge를 저장한다.
}

int IsEmpty(graph *g){ //그래프가 비어있는지 확인하는 함수
    return g->vertexnum == 0;
}

void printGraph(graph *g){
    if (IsEmpty(g)){ //그래프가 비어있는 경우 경고문을 출력하고 리턴한다.
        printf("Graph is empty!!\n");
        return;
    }
    for(int i = 0; i < MAX_VERTEX_SIZE; i++){
        if(g->adj_list[i] != NULL){     //adj_list[i]가 NULL이 아닌경우
            printf("Vertex %d:", i);   //정점의 이름을 출력한다.
            graphNode* temp = g->adj_list[i];  //temp에 adj_list[i]를 저장한다.
            while(temp != NULL){   //temp가 NULL이 아닐때까지 반복
                if(temp->vertex == 1){
                    continue;
                }
                printf(" -> %d", temp->vertex); //temp의 vertex를 출력한다.
                temp = temp->next; //temp를 다음 노드로 이동한다.
            }
            printf("\n");
        }
    }
}

void DFS(graph *g, int v) {//책에 나온 두번째 방법인 반복법을 이용한 깊이 우선 탐색
    int visited[MAX_VERTEX_SIZE] = {0}; //방문한 정점을 저장하는 배열을 0으로 초기화한다.
    graphNode* stack[MAX_VERTEX_SIZE];  //스택을 생성한다.
    int top = -1;   //top을 -1로 초기화한다.
    stack[++top] = g->adj_list[v];   //스택에 시작 정점을 넣는다.
    visited[v] = TRUE;  //시작 정점을 방문했다고 표시한다.
    printf("%d ", v);   //시작 정점을 출력한다.
    while(top != -1){   //스택이 비어있지 않을때까지 반복
        graphNode* temp = stack[top];   //temp에 스택의 top을 저장한다.
        while(temp != NULL){    //temp가 NULL이 아닐때까지 반복
            if(visited[temp->vertex] == FALSE){ //temp의 vertex를 방문하지 않았다면
                stack[++top] = g->adj_list[temp->vertex]; //스택에 temp의 vertex를 넣는다.
                visited[temp->vertex] = TRUE;   //temp의 vertex를 방문했다고 표시한다.
                printf("%d ", temp->vertex);    //temp의 vertex를 출력한다.
                break;
            }
            temp = temp->next;  //temp를 다음 노드로 이동한다.
        }
        if(temp == NULL){   //temp가 NULL이라면
            top--;  //스택의 top을 감소시킨다.
        }
    }
    printf("\n");
}

void BFS(graph *g, int v){ //책에 나온 두번째 방법인 반복법을 이용한 너비 우선 탐색
    int visited[MAX_VERTEX_SIZE] = {0}; //방문한 정점을 저장하는 배열을 0으로 초기화한다.
    graphNode* queue[MAX_VERTEX_SIZE];  //큐를 생성한다.
    int front = 0, rear = 0;    //front와 rear를 0으로 초기화한다.
    queue[rear++] = g->adj_list[v]; //큐에 시작 정점을 넣는다.
    visited[v] = TRUE;  //시작 정점을 방문했다고 표시한다.
    printf("%d ", v);   //시작 정점을 출력한다.
    while(front < rear){    //front가 rear보다 작을때까지 반복
        graphNode* temp = queue[front++];   //temp에 큐의 front를 저장하고 front를 증가시킨다.
        while(temp != NULL){    //temp가 NULL이 아닐때까지 반복
            if(visited[temp->vertex] == FALSE){ //temp의 vertex를 방문하지 않았다면
                queue[rear++] = g->adj_list[temp->vertex]; //큐에 temp의 vertex를 넣는다.
                visited[temp->vertex] = TRUE;   //temp의 vertex를 방문했다고 표시한다.
                printf("%d ", temp->vertex);    //temp의 vertex를 출력한다.
            }
            temp = temp->next;  //temp를 다음 노드로 이동한다.
        }
    }
    printf("\n");
}

int main(){
    int v1, v2;
    char input;
    graph g;
    Init(&g);

    do{
        printf("----------------------------------------------------------------\n");
        printf("-------------------------Graph Searches-------------------------\n");
        printf("---------------- [Park younghyeon] [2021041019] ----------------\n");
        printf("Initialize Graph = z\n");
        printf("Insert Vertex = v Insert Edge = e\n");
        printf("Depth First Search = d Breath First Search = b\n");
        printf("Print Graph = p Quit = q\n");
        printf("----------------------------------------------------------------\n");
        printf("Enter command: ");
        scanf(" %c", &input);

        switch (input) {
        case 'z': // 그래프 초기화
            Init(&g);
            printf("Graph Initialized!!\n");
            break;
        case 'v': // 그래프에 정점 추가
            printf("Enter vertex to insert: ");
            scanf("%d", &v1);
            InsertVertex(&g, v1);
            break;
        case 'e': // 그래프에 간선 추가
            printf("Enter two vertices to create an edge (v1 v2): ");
            scanf("%d %d", &v1, &v2);
            InsertEdge(&g, v1, v2);
            break;
        case 'd': //깊이 우선 탐색
            printf("Enter starting vertex: ");
            scanf("%d", &v1);
            printf("Depth First Search: ");
            DFS(&g, v1);
            break;
        case 'b': //너비 우선 탐색
            printf("Enter starting vertex: ");
            scanf("%d", &v1);
            printf("Breadth First Search: ");
            BFS(&g,v1);
            break;
        case 'p': // 그래프 출력
            printGraph(&g);
            break;
        default:
            break;
        }

    } while(input != 'q');

    return 0;
}
