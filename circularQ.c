#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;//front�� rear ����
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);//cQ �޸��Ҵ� ����
int isEmpty(QueueType *cQ);//cQ�� ����ִ��� Ȯ��
int isFull(QueueType *cQ);//cQ�� ���� á���� Ȯ��
void enQueue(QueueType *cQ, element item);//cQ�� item�� �Է�
void deQueue(QueueType *cQ, element* item);//cQ�� item �� ����
void printQ(QueueType *cQ);//cQ ���
void debugQ(QueueType *cQ);//cQ �����
element getElement();


int main(void)
{
	QueueType *cQ = createQueue();//cQ�� ����
	element data;
	printf("[----- [���°�] [2019038059] -----]");

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
		case 'i': case 'I'://i �Ǵ�I �Է� ������
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D'://d �Ǵ�D �Է� ������
			deQueue(cQ,&data);
			break;
		case 'p': case 'P'://p �Ǵ�P �Է� ������
			printQ(cQ);
			break;
		case 'b': case 'B'://b �Ǵ�B �Է� ������
			debugQ(cQ);
			break;
		case 'q': case 'Q'://Q �Ǵ�q �Է� ������
            free(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()// ����ť ����� �Լ�
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ�� �޸𸮸� �Ҵ��Ѵ�
	cQ->front = 0;//front �ʱⰪ0
	cQ->rear = 0;//rear �ʱⰪ 0
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;//cQ�� �ƹ����� ������ ���� 1
    free(cQ);//cQ�޸� �Ҵ� ����
    return 1;
}

element getElement()
{
	element item;//item ����
	printf("Input element = ");
	scanf(" %c", &item);//item �� �Է�
	return item;//���� item
}


int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){//cQ�� front�� rear �� ������
		printf("Circular Queue is empty!");// cQ�� ����ִٰ� ���
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {//cQ�� front�� rear���� �ϳ�������Ų����MAX_QUEUE_SIZE�� ���� ������ ���� ������
		printf(" Circular Queue is full!");//cQ�� �������ִٶ�� ���
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)//����ť������ �����Է�
{
	if(isFull(cQ)) return;//����ť�� ���� �������� �׳� ����
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;//rear���� �ϳ�������Ų����MAX_QUEUE_SIZE�� ���� ������ ���� rear�ιٱ���
		cQ->queue[cQ->rear] = item;//������ �ٱ��� rear���� ������ item�� �ִ´�
	}
}

void deQueue(QueueType *cQ, element *item)//����ť������ ��������
{
	if(isEmpty(cQ)) return;//����ť�� ��������� �׳� ����
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;//front���� �ϳ�������Ų����MAX_QUEUE_SIZE�� ���� ������ ���� front�ιٱ���
		*item = cQ->queue[cQ->front] ;//
		return;
	}
}


void printQ(QueueType *cQ)//cQ ��� �Լ�
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//first�� front���� �ϳ�������Ų����MAX_QUEUE_SIZE�� ���� ������ ������ ����
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//last�� rear���� �ϳ�������Ų����MAX_QUEUE_SIZE�� ���� ������ ������ ����

	printf("Circular Queue : [");

	i = first;
	while(i != last){//first�� last�� �ٸ���
		printf("%3c", cQ->queue[i]);//cQ.queue[i]�� ���
		i = (i+1)%MAX_QUEUE_SIZE;//i���� �ϳ�������Ų����MAX_QUEUE_SIZE�� ���� ������ ���� i�� �Է�

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)//cq �����
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//i�� 0���� MAX_QUEUE_SIZE ������ ������Ű�鼭 �ݺ�
	{
		if(i == cQ->front) {//i�� cQ.front�� ������ ����
			printf("  [%d] = front\n", i);//i=front���
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//cQ.queue[i]�� �� ���

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front rear ���
}