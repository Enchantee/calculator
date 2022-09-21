#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef double Element;

Element data[MAX_STACK_SIZE];	//실제 스택 요소의 배열
int top;						//실제 스택의 top

//오류 상황을 처리하기 위한 함수. 메세지 출력후 프로그램 종료.
void error(char str[]) {
	printf("%s\n", str);
	exit(1);
}
//스택의 주요 연산: 고통
void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX_STACK_SIZE - 1; }
int size() { return top + 1; }

void push(Element e) {
	if (is_full())
		error("스택 포화 에러");
	data[++top] = e;
}
Element pop()
{
	if (is_empty())
		error("스택 공백 에러");
	return data[top--];
}
Element pick()
{
	if (is_empty())
		error("스택 공백 에러");
	return data[top];
}
int precedence(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

void infix_to_postfix(char expr[])
{
	int i = 0;
	char c, op;

	init_stack();
	while (expr[i] != '\0') {
		c = expr[i++];
		if (c >= '0' && c <= '9') {
			printf("%c ", c);
		}
		else if (c == '(')
			push(c);
		else if (c == ')') {
			while (is_empty() == 0) {
				op = pop();
				if (op == '(') break;
				else printf("%c ", op);
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (is_empty() == 0) {
				op = pick();
				if (precedence(c) <= precedence(op)) {
					printf("%c ", op);
					pop();
				}
				else break;
			}
			push(c);
		}
	}
	while (is_empty() == 0)
		printf("%c ", pop());
	printf("\n");
}

int main(void) {
	char expr[2][80] = { "8 / 2 - 3 + (3 * 2)", "1 / 2 * 4 * (1 / 4)" };

	printf("중위수식: %s ==> 후위수식:", expr[0]);
	infix_to_postfix(expr[0]);
	printf("중위수식: %s ==> 후위수식:", expr[1]);
	infix_to_postfix(expr[1]);


	int n = 4096;
	while (n > 0) {
		push(n % 2);
		n /= 2;
	}
	
	while (!is_empty())
	/- 	printf("%d", pop());
}