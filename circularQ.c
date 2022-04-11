#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;//front와 rear 정의
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);//cQ 메모리할당 해제
int isEmpty(QueueType *cQ);//cQ가 비어있는지 확인
int isFull(QueueType *cQ);//cQ가 가득 찼는지 확인
void enQueue(QueueType *cQ, element item);//cQ에 item값 입력
void deQueue(QueueType *cQ, element* item);//cQ의 item 값 삭제
void printQ(QueueType *cQ);//cQ 출력
void debugQ(QueueType *cQ);//cQ 디버그
element getElement();


int main(void)
{
	QueueType *cQ = createQueue();//cQ를 만듬
	element data;
	printf("[----- [윤태경] [2019038059] -----]");

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I'://i 또는I 입력 했을때
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D'://d 또는D 입력 했을때
			deQueue(cQ,&data);
			break;
		case 'p': case 'P'://p 또는P 입력 했을때
			printQ(cQ);
			break;
		case 'b': case 'B'://b 또는B 입력 했을때
			debugQ(cQ);
			break;
		case 'q': case 'Q'://Q 또는q 입력 했을때
            free(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()// 원형큐 만드는 함수
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ에 메모리를 할당한다
	cQ->front = 0;//front 초기값0
	cQ->rear = 0;//rear 초기값 0
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;//cQ에 아무값이 없으면 리턴 1
    free(cQ);//cQ메모리 할당 해제
    return 1;
}

element getElement()
{
	element item;//item 정의
	printf("Input element = ");
	scanf(" %c", &item);//item 값 입력
	return item;//리턴 item
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){//cQ의 front와 rear 가 같으면
		printf("Circular Queue is empty!");// cQ는 비어있다고 출력
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {//cQ의 front와 rear값을 하나증가시킨다음MAX_QUEUE_SIZE로 나눈 나머지 값이 같으면
		printf(" Circular Queue is full!");//cQ는 가득차있다라고 출력
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)//원형큐에서의 원소입력
{
	if(isFull(cQ)) return;//원형큐가 가득 차있으면 그냥 리턴
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;//rear값을 하나증가시킨다음MAX_QUEUE_SIZE로 나눈 나머지 값을 rear로바까줌
		cQ->queue[cQ->rear] = item;//위에서 바까준 rear값의 공간에 item을 넣는다
	}
}

void deQueue(QueueType *cQ, element *item)//원형큐에서의 원소제거
{
	if(isEmpty(cQ)) return;//원형큐가 비어있으면 그냥 리턴
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;//front값을 하나증가시킨다음MAX_QUEUE_SIZE로 나눈 나머지 값을 front로바까줌
		*item = cQ->queue[cQ->front] ;//
		return;
	}
}


void printQ(QueueType *cQ)//cQ 출력 함수
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//first를 front값을 하나증가시킨다음MAX_QUEUE_SIZE로 나눈 나머지 값으로 정의
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//last를 rear값을 하나증가시킨다음MAX_QUEUE_SIZE로 나눈 나머지 값으로 정의

	printf("Circular Queue : [");

	i = first;
	while(i != last){//first랑 last가 다르면
		printf("%3c", cQ->queue[i]);//cQ.queue[i]를 출력
		i = (i+1)%MAX_QUEUE_SIZE;//i값을 하나증가시킨다음MAX_QUEUE_SIZE로 나눈 나머지 값을 i에 입력

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)//cq 디버그
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//i를 0부터 MAX_QUEUE_SIZE 전까지 증가시키면서 반복
	{
		if(i == cQ->front) {//i가 cQ.front와 같으면 실행
			printf("  [%d] = front\n", i);//i=front출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//cQ.queue[i]의 값 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front rear 출력
}