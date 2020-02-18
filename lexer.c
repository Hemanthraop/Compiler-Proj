#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX 81       //defining max limit for a line

//global vars
char *stream;
int nxt_lex_ptr;
bool fileover;

//structs
struct tokenlexemepair{
	char* token;
	char* lexeme;
};

//utility functions
char* substr(int begin,int end){
	char* ret=malloc((end-begin)*sizeof(char));
	strcpy(ret,"");
	for(int i=begin;i<end;i++){
		ret[i-begin]=stream[i];
	}
	return ret;
}

//functions

FILE *getStream(FILE *fp){
	nxt_lex_ptr=0;
	char initial;
	stream=malloc(sizeof(char)*MAX);
	strcpy(stream,"");
	while(1){
		
		initial = fgetc(fp);
		if(initial==EOF){fileover=true;return NULL;}
		//printf("%c",initial);
		if(initial != '\n') break;
	}
	
	while(initial!='\n'){
		strcat(stream,&initial);
		
		initial=fgetc(fp);
		if(initial==EOF){fileover=true;return NULL;}
	}
	return fp;
}

struct tokenlexemepair* getNexttoken(char* stream){
	char c;
	int init_ptr=nxt_lex_ptr;
	struct tokenlexemepair* tk;
	tk=malloc(sizeof(struct tokenlexemepair*));
	tk->token=malloc(sizeof(char)*20);
	int state=0;
	while(1){
		switch(state){
			case 0:	c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){

						case ';' : state = 1; break;
						case ',' : state = 2; break;
						case '[' : state = 3; break;  
						case ']' : state = 4; break;
						case '(' : state = 5; break;
						case ')' : state = 6; break;
						case '!' : state = 7; break;
						case '+' : state = 9; break;
						case '-' : state = 10; break;
						case '/' : state = 11; break;
						case '*' : state = 12; break;
						case '>' : state = 15; break;
						case '<' : state = 19; break;
						case '.' : state = 23; break;
						case '=' : state = 25; break;
						case ':' : state = 28; break;
						case ' ' : 
						case '\t':
						case '\n': state = 31; break;
						case 'a' ... 'z' : 
						case 'A' ... 'Z' :state = 33; break;
						case EOF : state = 46; break;   //eof?
						case '0' ... '9':state=35; break;
						default:state=100;
					}
					break;

			case 31:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case ' ':state=31;break;
						default:state=0;nxt_lex_ptr--;init_ptr=nxt_lex_ptr;
					}
					break;
			case 32:nxt_lex_ptr--;
					state=0;
					break;
			case 35:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '0' ... '9':break;
						case '.':state=37;
								 break;
						default:state=36;
					}
					break;
			case 36:tk->token="TK_NUM";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;
			case 37:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '0' ... '9':state=39;break;
						case '.':state=38;
								 break;
						default:state=100;
					}
					break;
			case 38:tk->token="TK_NUM";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-2);
					nxt_lex_ptr-=2;
					return tk;
			case 39:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '0' ... '9':state=39;break;
						case 'e':
						case 'E':state=40;
								 break;
						default:state=45;
					}
					break;
			case 40:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '0' ... '9':state=44;break;
						case '+':
						case '-':state=42;
								 break;
						default:state=41;
					}
					break;
			case 41:tk->token="TK_RNUM";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-2);
					nxt_lex_ptr-=2;
					return tk;
			case 42:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '0' ... '9':state=44;break;
						default:state=43;
					}
					break;
			case 43:tk->token="TK_RNUM";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-3);
					nxt_lex_ptr-=3;
					return tk;
			case 44:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '0' ... '9':break;
						default:state=45;
					}
					break;
			case 45:tk->token="TK_RNUM";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					printf("infn%s %d %d\n",tk->lexeme,init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;

		}
	}
}

int main(){
	FILE* fp=fopen("test.txt","r");
	if(fp==NULL)printf("NULL file\n");
	getStream(fp);
	printf("%s\n",stream);
	/*getStream(fp);
	printf("%s\n",stream);
	getStream(fp);
	printf("%s\n",stream);*/
	struct tokenlexemepair* ex=getNexttoken(stream);
	printf("%s\n%s\n",ex->lexeme,ex->token);
	free(ex);
	ex=getNexttoken(stream);
	printf("%s\n%s\n",ex->lexeme,ex->token);
}
