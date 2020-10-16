#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TERMS 100
typedef struct{
	double coef; //係數 
	int expo;  //指數 
} polynomial;

polynomial terms[MAX_TERMS];
int starta, finisha, startb, finishb, startd, finishd; //定義多項式a,b,d的開始及結束位置 
int avail = 0;  //索引值 
int read();
int compare(int i,int j);
void attach(double coef,int expo);
void add();
void print();



int main(void){
	starta=0;

	finisha=read();
	startb=finisha+1;

	finishb=read();
	startd=avail;
	add();
	print();
	return 0;
}

int read(){
	char input[100];
	scanf("%s",input);
	int i,finish;
	int j=0;
	char buffer[10];
	double weight=1;
	int isExpo=0;
	for(i=0;input[i]!='\0';i++){
		if(input[i]!='^'){
			//是運算符號or未知數時 
			if(input[i]=='x'){
				double coef=atof(buffer);
				if(coef==0)
					coef=1.0;
				terms[avail].coef=coef*weight;
				memset(buffer,'\0',sizeof(buffer));
				j=0;
				isExpo=1;
			}
			else if(input[i]=='+'){
				weight=1.0;
				if(isExpo){
					int expo=atoi(buffer);
					if(isExpo && expo==0)
						expo=1;
					terms[avail].expo=expo;
					memset(buffer,'\0',sizeof(buffer));
					j=0;
					avail++;
					isExpo=0;
				}
				
			}
			else if(input[i]=='-'){
				weight=-1;
				if(isExpo){
					int expo=atoi(buffer);
					if(expo==0)
						expo=1;
					terms[avail].expo=expo;
					memset(buffer,'\0',sizeof(buffer));
					j=0;
					avail++;
					isExpo=0;
				}
			}
			//數字or值 
			else{
				buffer[j]=input[i];
				j++;
			}
		}
	}
	//處理還在buffer中的值 
	if(isExpo==1){
		int expo=atoi(buffer);
		if(expo==0)
			expo=1;
		terms[avail].expo=expo;
		memset(buffer,'\0',sizeof(buffer));
	}
	else{
		double coef=atof(buffer);
		terms[avail].coef=coef*weight;
		terms[avail].expo=0;
		memset(buffer,'\0',sizeof(buffer));
	}
	
	finish=avail++;
	return finish;
}



void add(){
	int t_starta = starta;
	int t_finisha = finisha;
	int t_startb = startb;
	int t_finishb = finishb;
	double coef; 
	while(t_starta<=t_finisha && t_startb<=t_finishb){
		switch(compare(terms[t_starta].expo,terms[t_startb].expo)){
			case -1:
				attach(terms[t_startb].coef,terms[t_startb].expo);
				t_startb++;
				break;
			case 0:
				coef=terms[t_starta].coef+terms[t_startb].coef;
				if(coef!=0)
					attach(coef,terms[t_starta].expo);
				t_starta++;
				t_startb++;
				break;
			case 1:
				attach(terms[t_starta].coef,terms[t_starta].expo);
				t_starta++;
		}
	}
	for(;t_starta<=t_finisha;t_starta++){
		attach(terms[t_starta].coef,terms[t_starta].expo);
	}
	for(;t_startb<=t_finishb;t_startb++){
		attach(terms[t_startb].coef,terms[t_startb].expo);
	}
	finishd=avail-1; 
}
void attach(double coef,int expo){
	if(avail>=MAX_TERMS){
		printf("超出空間");
	}
	else{
		terms[avail].coef=coef;
		terms[avail].expo=expo;
		avail++;
	}
	
}
int compare(int i,int j){
	int result;
	if(i<j){
		result=-1;
	}
	else if(i==j){
		result=0;
	}
	else if(i>j){
		result=1;
	}
	return result;
}

void print(){
	int i;
	int isPrint=0;
	for(i=startd;i<=finishd;i++){
		if(i>startd && terms[i].coef>0){
			printf("+");
			isPrint=1;
		}
		if(terms[i].expo!=0){
			if(terms[i].coef!=1 && terms[i].coef!=-1)
				printf("%gx^%d",terms[i].coef,terms[i].expo);
			else if(terms[i].coef==-1)
				printf("-x^%d",terms[i].expo);
			else
				printf("x^%d",terms[i].expo);
			isPrint=1;
		}
				
		else{
			printf("%g",terms[i].coef);
			isPrint=1;
		}
	}
	if(isPrint==0){
		printf("0");
	}
//	printf("\n");
//	for(i=0;i<=finishd;i++){
//		printf("%d:coef=%g,expo=%d\n",i,terms[i].coef,terms[i].expo);
//	}
}
