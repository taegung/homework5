
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10//스택 배열 크기를 10으로 정의
#define MAX_EXPRESSION_SIZE 20//입력 값 을 저장할 배열 크기를 20으로 정의

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 6,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 4,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];//중위 표기법
char postfixExp[MAX_EXPRESSION_SIZE];//후위표기법
char postfixStack[MAX_STACK_SIZE];//후위표기법 스택
int evalStack[MAX_STACK_SIZE];//결과 스택

int postfixStackTop = -1;//postfixStack 의 탑의 초기값을 -1 로 설정
int evalStackTop = -1;//evalstack의 탑의 초기값을 -1 로 설정

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
	printf("[----- [윤태경] [2019038059] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command 입력

		switch(command) {
		case 'i': case 'I'://i or I 입력 했을때
			getInfix();
			break;
		case 'p': case 'P'://p or P 입력 했을때
			toPostfix();
			break;
		case 'e': case 'E'://e or E 입력 했을떄
			evaluation();
			break;
		case 'd': case 'D'://d or D 입력 했을때
			debug();
			break;
		case 'r': case 'R'://r or R 입력 했을떄
			reset();
			break;
		case 'q': case 'Q'://q or Q 입력 했을때
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
    postfixStack[++postfixStackTop] = x;// postfixStack의 top을 하나 증가시키고  스택에 x를 대입
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1)//top이 =-1 일때 즉 스택에 아무값도 없을떄
        return '\0';
    else {// 스택에 값이 있을때
    	x = postfixStack[postfixStackTop--];//x에 postfixStack의 top에 있는 값 을 대입 한후 top을 -1 해준다
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;//  evalStack의 top을 하나 증가시키고  스택에 x를 대입
}


int evalPop()
{
    if(evalStackTop == -1)//top이 =-1 일때 즉 스택에 아무값도 없을떄
        return -1;
    else
        return evalStack[evalStackTop--];// evalStack의 top에 있는 값 을 리턴 한후 top을 -1 해준다
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);//중위표기법인 연산식 입력
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;// (이면 lparen 리턴
	case ')' : return rparen;// )이면 rparen 리턴
	case '+' : return plus;// +이면 plus 리턴
	case '-' : return minus;// -이면 minus 리턴
	case '/' : return divide;// /이면 divide 리턴
	case '*' : return times;// *이면 times 리턴
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);//받은 연산자를 gettoken함수에서 리턴값을 받아줌
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);//postfixExp에 아무값도 없으면 c 입력
	else
		strncat(postfixExp, c, 1);//postfixExp에 값이 있으면 c를 추가
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp; 
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)//받은 문자가 숫자이면
		{
			x = *exp;//x에 *exp 값 입력
        	charCat(&x);//charcat 을 통하여 x값을 postfixExp에 입력하거나 추가
		}
        else if(getPriority(*exp) == lparen) {//받은 문자가 ( 이면

        	postfixPush(*exp);//postfixstack의 top에 받은 문자 저장
        }
        else if(getPriority(*exp) == rparen)//받은 문자가 ) 이면
        {
        	while((x = postfixPop()) != '(') {//postfixstack의 값들중에 ( 을 만날때까지 postfixpop을함
        		charCat(&x);//charcat 을 통하여 x값을 postfixExp에 입력하거나 추가
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))//스택의 탑 연산자가 *exp 보다 우선순위에 있거나 같으면 실행
            {
            	x = postfixPop();//x는 postfix스택의 현재 pop에 있는값 입력 
            	charCat(&x);//charcat 을 통하여 x값을 postfixExp에 입력하거나 추가
            }
            postfixPush(*exp);//postfixstack의 top에 받은 문자 저장
        }
        exp++;//exp를 1증가 시킴으로써 infixExp의 다음 문자로 exp가 바뀜
	}

    while(postfixStackTop != -1)//postfixstack의 top -1이 되기전까지 반복
    {
    	x = postfixPop();//postfixstack에서 현재pop에 있는 값을 x에 입력
    	charCat(&x);//charcat 을 통하여 x값을 postfixExp에 입력하거나 추가
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);//infixExp 출력
	printf("postExp =  %s\n", postfixExp);//postfixExp 출력
	printf("eval result = %d\n", evalResult);//evalResult 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)//i를 0부터 MAX_STACK_SIZE 이전까지 i를 증가 시키면서 반복
		printf("%c  ", postfixStack[i]);//post스택에 쌓여있는값 출력

	printf("\n");

}

void reset()//초기화
{
	infixExp[0] = '\0';//infixExp을 초기화
	postfixExp[0] = '\0';//postfixExp을 초기화

	for(int i = 0; i < MAX_STACK_SIZE; i++)//postfixstack에 있는 값들을 초기화
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;//postfixstacktop을 -1로 초기화
	evalStackTop = -1;//evalstacktop을 -1로 초기화
	evalResult = 0;//evalResult을 0으로 초기화
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);//postfixExp의 길이를 lenght에 입력
	char symbol;
	evalStackTop = -1;//evalstack의 top을 -1로 설정

	for(i = 0; i < length; i++)//postfixexp의 길이만큼 반복
	{
		symbol = postfixExp[i];//postfixexp[i]값을 symbol에 입력
		if(getToken(symbol) == operand) {//symbol이 숫자면실행
			evalPush(symbol - '0');//evalstack의 top에 symbol 입력
		}
		else {//숫자가 아니면
			opr2 = evalPop();//evalstack의 현재top의 값을 opr2에 입력
			opr1 = evalPop();//evalstack의 현재top의 값을 opr1에 입력
			switch(symbol) {
			case '+': evalPush(opr1 + opr2); break;//symbol이 +이면 opr1이랑 opr2를 더한값을 evalpush를 통해 evalstack의 top자리에 입력
			case '-': evalPush(opr1 - opr2); break;//symbol이 -이면 opr1이랑 opr2를 뺀을 evalpush를 통해 evalstack의 top자리에 입력
			case '*': evalPush(opr1 * opr2); break;//symbol이 *이면 opr1이랑 opr2를 *을 evalpush를 통해 evalstack의 top자리에 입력
			case '/': evalPush(opr1 / opr2); break;//symbol이 /이면 opr1이랑 opr2를 나눈값을 evalpush를 통해 evalstack의 top자리에 입력
			default: break;
			}
		}
	}
	evalResult = evalPop();//evalstack의 현재top에 있는값을 evalResult에 입력
}

