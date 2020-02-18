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
	char* ret=malloc((end-begin+1)*sizeof(char));
	strcpy(ret,"");
	for(int i=begin;i<end;i++){
		ret[i-begin]=stream[i];
	}
	r[end-begin+1]='\0';
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
				
			case 1 : tk->token="TK_SEMICOLON";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme=";";
				 return tk;
				
			case 2 : tk->token="TK_COMMA";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme=",";
				 return tk;
				
			case 3 : tk->token="TK_SQBO";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme="[";
				 return tk;
				
			case 4 : tk->token="TK_SQBC";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme="]";
				 return tk;
				
			case 5 : tk->token="TK_BO";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme="(";
				 return tk;
				
			case 6 : tk->token="TK_BC";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme=")";
				 return tk;
				
			case 7 : c=stream[next_lex_ptr];
					  next_lex_ptr++;
					  switch(c){
						case '=':state=8;break;
						default : state=100;
					}
					break;
				
			case 8 : tk->token="TK_NE";
				 tk->lexeme=malloc(3*sizeof(char));
				 tk->lexeme='!=';
				 return tk;
				
			case 9 : tk->token="TK_PLUS";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme="+";
				 return tk;
				
			case 10 : tk->token="TK_MINUS";
				 tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme="-";
				 return tk;
				
			case 11 : tk->token="TK_DIV";
				  tk->lexeme=malloc(2*sizeof(char));
				 tk->lexeme="/";
				 return tk;
				
			case 12 : c = stream[nxt_lex_ptr];
				  nxt_lex_ptr++;
				  switch(c){
					case '*': state = 27;break;
					default:state = 13;
				  }
				
			case 13 : tk->token="TK_NUM";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;
				
			case 14 : tk->token="TK_NUM";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
				
			case 27 : c = stream[nxt_lex_ptr];
				  nxt_lex_ptr++;
				  switch(c){
					case '*': state = 47;break;
					default:state = 27;nxt_ptr--;init_ptr = nxt_lex_ptr;
				  }
				
			case 47 :  c = stream[nxt_lex_ptr];
				  nxt_lex_ptr++;
				  switch(c){
					case '*': state = 14;break;
					default:state = 27;nxt_ptr--;init_ptr = nxt_lex_ptr;
				  }
				
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
			
			case 28:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '=':state=29;
									break;
						default:state=30;
					}
					break;
			case 29:tk->token="TK_ASSIGNOP";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			
			case 30:tk->token="TK_COLON";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 33:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case 'a'...'z':
						case 'A'...'Z':
						case '0'...'9':
						case '_':
								 break;
						default:state=34;
					}
					break;
			case 34:tk->token=search_token();
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;
            
			case 23:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '.':state=24;break;
						default:state=100;
					}
					break;
			case 24:tk->token="TK_RANGEOP";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 19:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '<':state=20;break;
						case '=':state=21;break;
						default:state=22;
					}
					break;
			case 20:tk->token="TK_DEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 21:tk->token="TK_LE";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 22:tk->token="TK_LT";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;

			case 15:c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '>':state=16;break;
						case '=':state=17;break;
						default:state=18;
					}
					break;
			case 16:tk->token="TK_ENDDEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 17:tk->token="TK_GE";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 18:tk->token="TK_GT";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
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
