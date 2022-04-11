
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10//���� �迭 ũ�⸦ 10���� ����
#define MAX_EXPRESSION_SIZE 20//�Է� �� �� ������ �迭 ũ�⸦ 20���� ����

/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 6,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 4,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];//���� ǥ���
char postfixExp[MAX_EXPRESSION_SIZE];//����ǥ���
char postfixStack[MAX_STACK_SIZE];//����ǥ��� ����
int evalStack[MAX_STACK_SIZE];//��� ����

int postfixStackTop = -1;//postfixStack �� ž�� �ʱⰪ�� -1 �� ����
int evalStackTop = -1;//evalstack�� ž�� �ʱⰪ�� -1 �� ����

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;
	printf("[----- [���°�] [2019038059] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command �Է�

		switch(command) {
		case 'i': case 'I'://i or I �Է� ������
			getInfix();
			break;
		case 'p': case 'P'://p or P �Է� ������
			toPostfix();
			break;
		case 'e': case 'E'://e or E �Է� ������
			evaluation();
			break;
		case 'd': case 'D'://d or D �Է� ������
			debug();
			break;
		case 'r': case 'R'://r or R �Է� ������
			reset();
			break;
		case 'q': case 'Q'://q or Q �Է� ������
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;// postfixStack�� top�� �ϳ� ������Ű��  ���ÿ� x�� ����
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1)//top�� =-1 �϶� �� ���ÿ� �ƹ����� ������
        return '\0';
    else {// ���ÿ� ���� ������
    	x = postfixStack[postfixStackTop--];//x�� postfixStack�� top�� �ִ� �� �� ���� ���� top�� -1 ���ش�
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;//  evalStack�� top�� �ϳ� ������Ű��  ���ÿ� x�� ����
}


int evalPop()
{
    if(evalStackTop == -1)//top�� =-1 �϶� �� ���ÿ� �ƹ����� ������
        return -1;
    else
        return evalStack[evalStackTop--];// evalStack�� top�� �ִ� �� �� ���� ���� top�� -1 ���ش�
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);//����ǥ����� ����� �Է�
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;// (�̸� lparen ����
	case ')' : return rparen;// )�̸� rparen ����
	case '+' : return plus;// +�̸� plus ����
	case '-' : return minus;// -�̸� minus ����
	case '/' : return divide;// /�̸� divide ����
	case '*' : return times;// *�̸� times ����
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);//���� �����ڸ� gettoken�Լ����� ���ϰ��� �޾���
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);//postfixExp�� �ƹ����� ������ c �Է�
	else
		strncat(postfixExp, c, 1);//postfixExp�� ���� ������ c�� �߰�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp; 
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)//���� ���ڰ� �����̸�
		{
			x = *exp;//x�� *exp �� �Է�
        	charCat(&x);//charcat �� ���Ͽ� x���� postfixExp�� �Է��ϰų� �߰�
		}
        else if(getPriority(*exp) == lparen) {//���� ���ڰ� ( �̸�

        	postfixPush(*exp);//postfixstack�� top�� ���� ���� ����
        }
        else if(getPriority(*exp) == rparen)//���� ���ڰ� ) �̸�
        {
        	while((x = postfixPop()) != '(') {//postfixstack�� �����߿� ( �� ���������� postfixpop����
        		charCat(&x);//charcat �� ���Ͽ� x���� postfixExp�� �Է��ϰų� �߰�
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))//������ ž �����ڰ� *exp ���� �켱������ �ְų� ������ ����
            {
            	x = postfixPop();//x�� postfix������ ���� pop�� �ִ°� �Է� 
            	charCat(&x);//charcat �� ���Ͽ� x���� postfixExp�� �Է��ϰų� �߰�
            }
            postfixPush(*exp);//postfixstack�� top�� ���� ���� ����
        }
        exp++;//exp�� 1���� ��Ŵ���ν� infixExp�� ���� ���ڷ� exp�� �ٲ�
	}

    while(postfixStackTop != -1)//postfixstack�� top -1�� �Ǳ������� �ݺ�
    {
    	x = postfixPop();//postfixstack���� ����pop�� �ִ� ���� x�� �Է�
    	charCat(&x);//charcat �� ���Ͽ� x���� postfixExp�� �Է��ϰų� �߰�
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);//infixExp ���
	printf("postExp =  %s\n", postfixExp);//postfixExp ���
	printf("eval result = %d\n", evalResult);//evalResult ���

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)//i�� 0���� MAX_STACK_SIZE �������� i�� ���� ��Ű�鼭 �ݺ�
		printf("%c  ", postfixStack[i]);//post���ÿ� �׿��ִ°� ���

	printf("\n");

}

void reset()//�ʱ�ȭ
{
	infixExp[0] = '\0';//infixExp�� �ʱ�ȭ
	postfixExp[0] = '\0';//postfixExp�� �ʱ�ȭ

	for(int i = 0; i < MAX_STACK_SIZE; i++)//postfixstack�� �ִ� ������ �ʱ�ȭ
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;//postfixstacktop�� -1�� �ʱ�ȭ
	evalStackTop = -1;//evalstacktop�� -1�� �ʱ�ȭ
	evalResult = 0;//evalResult�� 0���� �ʱ�ȭ
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);//postfixExp�� ���̸� lenght�� �Է�
	char symbol;
	evalStackTop = -1;//evalstack�� top�� -1�� ����

	for(i = 0; i < length; i++)//postfixexp�� ���̸�ŭ �ݺ�
	{
		symbol = postfixExp[i];//postfixexp[i]���� symbol�� �Է�
		if(getToken(symbol) == operand) {//symbol�� ���ڸ����
			evalPush(symbol - '0');//evalstack�� top�� symbol �Է�
		}
		else {//���ڰ� �ƴϸ�
			opr2 = evalPop();//evalstack�� ����top�� ���� opr2�� �Է�
			opr1 = evalPop();//evalstack�� ����top�� ���� opr1�� �Է�
			switch(symbol) {
			case '+': evalPush(opr1 + opr2); break;//symbol�� +�̸� opr1�̶� opr2�� ���Ѱ��� evalpush�� ���� evalstack�� top�ڸ��� �Է�
			case '-': evalPush(opr1 - opr2); break;//symbol�� -�̸� opr1�̶� opr2�� ���� evalpush�� ���� evalstack�� top�ڸ��� �Է�
			case '*': evalPush(opr1 * opr2); break;//symbol�� *�̸� opr1�̶� opr2�� *�� evalpush�� ���� evalstack�� top�ڸ��� �Է�
			case '/': evalPush(opr1 / opr2); break;//symbol�� /�̸� opr1�̶� opr2�� �������� evalpush�� ���� evalstack�� top�ڸ��� �Է�
			default: break;
			}
		}
	}
	evalResult = evalPop();//evalstack�� ����top�� �ִ°��� evalResult�� �Է�
}

