/* 			GROUP NO : 18
	NIKHIL DEVABHAKTUNI    	2017A7PS0032P
	YAGANTI SHIVA KRISHNA  	2017A7PS0045P
	SANKEERTH NALAM	       	2017A7PS0070P
	PAIDIPALLY HEMANTH RAO 	2017A7PS0159P 
						*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX 81       //defining max limit for a line
#define LEN 10

//global vars
int line_no;
char *stream;
int nxt_lex_ptr;
bool fileover,streamover,iserror;

//structs
struct tokenlexemepair{
	char* token;
	char* lexeme;
};

struct tokenlexemepair* hashtable[10];
int sizes[10];

//utility functions
int hashfun(char* lex){
	return (strlen(lex)%10);
}

void intialize_symbol_table(){
	char *res_lex[33]={"integer","real","boolean","of","array","start","end","declare","module","driver","program","record","tagged","union","get_value","print","use","with","parameters","true","false","takes","input","returns","AND","OR","for","in","switch","case","break","default","while"};
	char *res_tok[33]={"INTEGER","REAL","BOOLEAN","OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","RECORD","TAGGED","UNION","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR","IN","SWITCH","CASE","BREAK","DEFAULT","WHILE"};
	
	for(int i=0;i<33;i++){
		char tok[20]="TK_";
		int k = hashfun(res_lex[i]);
		struct tokenlexemepair* ptr=hashtable[k];
		
		ptr=realloc(ptr,(sizes[k]+1)*sizeof(struct tokenlexemepair));
		hashtable[k]=ptr;
		ptr[sizes[k]].lexeme=malloc(33*sizeof(char));
		strcpy(ptr[sizes[k]].lexeme,res_lex[i]);
		
		ptr[sizes[k]].token=malloc(sizeof(char)*20);
		strcpy(ptr[sizes[k]].token,strcat(tok,res_tok[i]));
	//ptr[sizes[k]].token="TK_ID";
	
	
		sizes[k]++;
	}
}
char* search_token(char* lex){
	char* a="TK_ID";
	
	int k = hashfun(lex);
	struct tokenlexemepair* ptr=hashtable[k];
	
	//int size=sizeof(hashtable[k])/sizeof(struct tokenlexemepair);
	//printf("%d\n",sizes[k]);
	for(int i=0;i<sizes[k];i++){
		
		if(strcmp(lex,ptr[i].lexeme)==0){
			
			return ptr[i].token;
		}
	}
	
	ptr=realloc(ptr,(sizes[k]+1)*sizeof(struct tokenlexemepair));
	hashtable[k]=ptr;
	ptr[sizes[k]].lexeme=malloc(33*sizeof(char));
	strcpy(ptr[sizes[k]].lexeme,lex);
	
	ptr[sizes[k]].token=malloc(sizeof(char)*10);
	strcpy(ptr[sizes[k]].token,a);
	//ptr[sizes[k]].token="TK_ID";
	
	
	sizes[k]++;
	return ptr[sizes[k]-1].token;
}

char* substr(int begin,int end){
	char* ret=malloc((end-begin+1)*sizeof(char));
	strcpy(ret,"");
	for(int i=begin;i<end;i++){
		ret[i-begin]=stream[i];
	}
	ret[end-begin+1]='\0';
	return ret;
}

//functions

FILE *getStream(FILE *fp){
	fileover=false;
	nxt_lex_ptr=0;
	char initial;
	stream=malloc(sizeof(char)*MAX);
	strcpy(stream,"");
	while(1){
		line_no++;
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
	iserror=false;
	streamover=false;
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
						case '\0':
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
				
			case 7 : c=stream[nxt_lex_ptr];
					  nxt_lex_ptr++;
					  switch(c){
						case '=':state=8;break;
						default : state=100;
					}
					break;
				
			case 8 : tk->token="TK_NE";
				 tk->lexeme=malloc(3*sizeof(char));
				 tk->lexeme="!=";
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
					//printf("jjjj%c\n",c);
				  nxt_lex_ptr++;
				  switch(c){
					case '*': state = 27;break;
					default:state = 13;
				  }
				  break;
			case 13 : tk->token="TK_MUL";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;
				
			case 14 : tk->token="TK_COMMENT";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
				
			case 27 : c = stream[nxt_lex_ptr];
				  nxt_lex_ptr++;
				  //printf("hhhh%c\n",c);
				  switch(c){
					case '*': state = 47;break;
					default:state = 27;
				  }
				  break;
			case 47 :  c = stream[nxt_lex_ptr];
				  nxt_lex_ptr++;
				  switch(c){
					case '*': state = 14;break;
					default:state = 27;
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
					//printf("infn%s %d %d\n",tk->lexeme,init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;
			case 46:streamover=true;return NULL;
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
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
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
			case 34:
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					strcpy(tk->token,search_token(tk->lexeme));
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
			case 20:/*tk->token="TK_DEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;*/
					c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '<':state=50;break;
						default:state=51;
					}
					break;
			case 50:tk->token="TK_DRIVERDEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 51:tk->token="TK_DEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
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
			case 16:/*tk->token="TK_ENDDEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;*/
					c=stream[nxt_lex_ptr];
					nxt_lex_ptr++;
					switch(c){
						case '>':state=48;break;
						default:state=49;
					}
					break;
			case 48:tk->token="TK_ENDDRIVERDEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 49:tk->token="TK_ENDDEF";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;
			case 17:tk->token="TK_GE";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					return tk;
			case 18:tk->token="TK_GT";
					tk->lexeme=substr(init_ptr,nxt_lex_ptr-1);
					nxt_lex_ptr--;
					return tk;
			case 25:c=stream[nxt_lex_ptr];
			        nxt_lex_ptr++;
			        switch(c){
			        	case '=':state=26;break;
			        	default:state=100;
			        }
				break;
			case 26:tk->token="TK_EQ";
					//tk->lexeme=malloc((nxt_lex_ptr-init_ptr)*sizeof(char));
					tk->lexeme=substr(init_ptr,nxt_lex_ptr);
					//printf("infn%s %d %d\n",tk->lexeme,init_ptr,nxt_lex_ptr-1);
					//nxt_lex_ptr--;
					return tk;
			case 100:printf("Line: %d Lexical Error :\n",line_no);
					iserror=true;
					//printf("%s\n",substr(init_ptr,nxt_lex_ptr))
					return NULL;
		}
	}
}

int main(){
	intialize_symbol_table();

	struct tokenlexemepair* ex;
	FILE* fp=fopen("test.txt","r");
	if(fp==NULL)printf("NULL file\n");

	while(1){
		fp=getStream(fp);
	
		while(1){
			ex=getNexttoken(stream);
			if(streamover==true) break;
			if(iserror==true)continue;
			printf("%s\t%s\t%d\n",ex->token,ex->lexeme,line_no);
		}
		if(fileover==true) break;
	}
}


