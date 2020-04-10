#include "parser.c"

struct astnode{
	struct astnode* Children[50];
	int no_of_children=0;
	char lex[21];
};

void reduce_mDs(struct node* root,struct astnode* ast){
	//make_astnode( ast,(((root->Children)[0])->Children[2])->lex ,"TK_ID" );
	ast->Children[ast->no_of_children]=malloc(sizeof(struct astnode));

	strcpy( ast->Children[ast->no_of_children]->lex , (((root->Children)[0])->Children[2])->lex);
	ast->no_of_children++;
	if(strcmp(((root->Children[1])->Children[0])->lex,"")==0){
		return;
	}
	else{
		reduce_mDs(root,ast);
	}
}
void reduce_expr(struct node* root,struct astnode* ast){

	ast->Children[0]=malloc(sizeof(struct astnode));
	if((root->Children[0])->no==35){
		ast->no_of_children=1;
		reduce_arithorBool_expr(root->Children[0],ast->Children[0]);
	}
	if((root->Children[0])->no==31){
		ast->no_of_children=1;
		reduce_U(root->Children[0],ast->Children[0]);
	}
}

void reduce_arithorBool_expr(struct node* root,struct astnode* ast){

	reduce_anyterm(root->Children[0],ast->Children[0]->Children[0]);

	
}