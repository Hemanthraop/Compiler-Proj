#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//global vars
char *stream;

bool fileover;
//structs
struct tokenlexemepair{
	char* token;
	char* lexeme;
};

//functions

FILE *getStream(FILE *fp){
	char initial;
	stream=malloc(sizeof(char)*81);
	strcpy(stream,"");
	while(1){
		if(feof(fp)){fileover=true;return NULL;}
		initial = fgetc(fp);
		//printf("%c",initial);
		if(initial != '\n') break;
	}
	
	while(initial!='\n'&&!feof(fp)){
		strcat(stream,&initial);
		if(feof(fp)){fileover=true;return NULL;}
		initial=fgetc(fp);
	}
	return fp;
}

//getNexttoken()

int main(){
	FILE* fp=fopen("test.txt","r");
	if(fp==NULL)printf("NULL file\n");
	getStream(fp);
	printf("%s\n",stream);
	getStream(fp);
	printf("%s\n",stream);
}