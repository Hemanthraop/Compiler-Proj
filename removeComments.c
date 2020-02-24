/* 			GROUP NO : 18
	NIKHIL DEVABHAKTUNI    	2017A7PS0032P
	YAGANTI SHIVA KRISHNA  	2017A7PS0045P
	SANKEERTH NALAM	       	2017A7PS0070P
	PAIDIPALLY HEMANTH RAO 	2017A7PS0159P 
	HIMA SIVA KALYAN        2017A7PS0235P        */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void removeComments(char *testcaseFile,char *cleanFile){
	FILE *file1;
	FILE *file2;
	file1=fopen(testcaseFile,"r");
	file2=fopen(cleanFile,"w");
	char c;
	char * buff;
	int state=0;
	int buf_sz=1;
	int nl_cnt=0;
	buff=malloc(sizeof(char));
	buff[0]='\0';
	while(1){
		c=fgetc(file1);

		if(c==EOF){
			if(state==0){
				fputc('\n',file2);
				break;
			}
			if(state==1){
				fputc('*',file2);
				break;
			}
			if(state==2){
				fputc('*',file2);
				fputc('*',file2);
				fputs(buff,file2);
				break;
			}
			if(state==3){
				fputc('*',file2);
				fputc('*',file2);
				fputs(buff,file2);
				fputc('*',file2);
				break;
			}
		}
		switch(state){
			case 0://c=fgetc(file1);
					printf("in 0\n");
				   if(c=='*') state=1;
				   else{

				   		fputc(c,file2);
				   }
				   break;
			case 1://c=fgetc(file1);
					printf("in 1\n");
				   if(c=='*'){
				   		state=2;

				   } 
				   else{
				   		fputc('*',file2);
				   		fputc(c,file2);
				   		state=0;
				   }
				   break;
			case 2://c=fgetc(file1);
					printf("in 2\n");
				   if(c!='*'){
				   		printf("1\n");
				   		printf("%c\n",c);
				   		printf("%d\n",buf_sz);
				   		buff=(char *)realloc(buff,(1+buf_sz)*sizeof(char));
				   		printf("3\n");
				   		
				   		//strcat(buff,&c);
				   		if(c=='\n') nl_cnt++;
				   		buff[buf_sz-1]=c;
				   		buff[buf_sz]='\0';
				   		buf_sz++;
				   		printf("2\n");
				   }
				   else{
				   		state=3;
				   }
				   break;
			case 3://c=fgetc(file1);
				   printf("in 3\n");
				   if(c!='*'){
				   		state=2;
				   		fputc('*',file2);
				   		if(c=='\n') nl_cnt++;
				   		buff=realloc(buff,(1+buf_sz)*sizeof(char));
				   		buff[buf_sz-1]=c;
				   		buff[buf_sz]='\0';
				   		buf_sz++;
				   		//strcat(buff,&c);
				   }
				   else{
				   		state=0;
				   		buff[0]='\0';
				   		buf_sz=1;
				   		for(int i=0;i<nl_cnt;i++) fputc('\n',file2);
				   		nl_cnt=0;
				   }
				   break;
		}
	}
}

int main(){
	removeComments("f1","f2");
}
