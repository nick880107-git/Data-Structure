#include <stdio.h> 
#include <stdlib.h> 

#define MAX 100

void in_to_post(char*, char*); 
int priority(char); 

int main(void) { 
    char infix[MAX] = {'\0'}; 
    char postfix[MAX]= {'\0'};    
    scanf("%s", infix); 
    in_to_post(infix, postfix);
    for(int i = 0; postfix[i] != '\0'; i++) {
        printf("%c", postfix[i]); 
    }

    return 0; 
} 

void in_to_post(char* infix, char* postfix) { 
    char stack[MAX] = {'\0'};
    int i=0, j=0, top=0;
    for(i = 0; infix[i] != '\0'; i++){
    	switch(infix[i]) { 
        case '+': case '-': case '*': case '/': 
            while(priority(stack[top]) >= priority(infix[i])) { 
                postfix[j++] = stack[top--];
            } 
            stack[++top] = infix[i]; 
            break; 
        case '(':               
            stack[++top] = infix[i]; 
            break; 
        case ')': 
            while(stack[top] != '(') { 
                postfix[j++] = stack[top--];
            } 
            top--;  
            break; 
        default:   
            postfix[j++] = infix[i];
		} 
    }
    while(top > 0) { 
        postfix[j++] = stack[top--];
    }
} 

int priority(char s) { 
    switch(s) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 
