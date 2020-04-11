#include "parser.c"

struct astnode{
	struct astnode* Children[50];
	int no_of_children=0;
	char lex[21];
	int no;
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

	ast->Children[0]=malloc(sizeof(struct astnode));
	reduce_anyterm(root->Children[0],ast->Children[0]);
	ast->no_of_children++;

	if(((root->Children[1])->Children[0])->no==114){
		//reduce_anyterm(((root->Children[1])->Children[0]),ast->Children[0]);
	}
	else{
		ast->no_of_children++;
		ast->Children[1]=malloc(sizeof(struct astnode));

		//copy Lop into ast somehow
		ast->no=(root->Children[1]->Children[0]->Children[0])->no;
		reduce_N7(root->Children[1],ast->Children[1]);
	}
}

void reduce_N7(struct node* root,struct astnode* ast){
	if(((root->Children[2])->Children[0])->no==114){
		reduce_anyterm((root->Children[1]),ast);
	}
	else{
		ast->no_of_children++;
		ast->Children[0]=malloc(sizeof(struct astnode));

		reduce_anyterm((root->Children[1]),ast->Children[0]);
		//copy Lop into ast somehow
		ast->no=(root->Children[2]->Children[0]->Children[0])->no;
		ast->Children[1]=malloc(sizeof(struct astnode));
		reduce_N7(root->Children[2],ast->Children[1]);
	}
}

void reduce_anyterm(struct node* root,struct astnode* ast){
	if((root->Children[0])->no==56){
		ast->no=((root->Children[0])->Children[0])->no;
	}
	else{
		ast->no_of_children++;
		ast->Children[0]=malloc(sizeof(struct astnode));
		reduce_arith_expr(root->Children[0],ast->Children[0]);
		if(root->Children[1]->Children[0]->no==114){

		}
		else{
			ast->no_of_children++;
			ast->Children[1]=malloc(sizeof(struct astnode));
			reduce_N8(root->Children[1],ast->Children[1]);
		}
	}
}

void reduce_N8(struct node* root,struct astnode* ast){
	ast->Children[0]=malloc(sizeof(struct astnode));
	ast->no_of_children++;
	reduce_rel_op(root->Children[0],ast->Children[0]);
	ast->Children[1]=malloc(sizeof(struct astnode));
	ast->no_of_children++;
	reduce_arith_expr(root->Children[1],ast->Children[1]);
}

void reduce_rel_op(struct node* root,struct astnode* ast){
	ast->no=(root->Children[0])->no;
}

void reduce_arith_expr(struct node* root,struct astnode* ast){

	ast->Children[0]=malloc(sizeof(struct astnode));
	reduce_term(root->Children[0],ast->Children[0]);
	ast->no_of_children++;

	if(((root->Children[1])->Children[0])->no==114){
		//reduce_anyterm(((root->Children[1])->Children[0]),ast->Children[0]);
	}
	else{
		ast->no_of_children++;
		ast->Children[1]=malloc(sizeof(struct astnode));

		//copy Lop into ast somehow
		ast->no=(root->Children[1]->Children[0]->Children[0])->no;
		reduce_A1(root->Children[1],ast->Children[1]);
	}
}

void reduce_A1(struct node* root,struct astnode* ast){
	if(((root->Children[2])->Children[0])->no==114){
		reduce_term((root->Children[1]),ast);
	}
	else{
		ast->no_of_children++;
		ast->Children[0]=malloc(sizeof(struct astnode));

		reduce_term((root->Children[1]),ast->Children[0]);
		//copy Lop into ast somehow
		ast->no=(root->Children[2]->Children[0]->Children[0])->no;
		ast->Children[1]=malloc(sizeof(struct astnode));
		reduce_A1(root->Children[2],ast->Children[1]);
	}
}

void reduce_term(struct node* root,struct astnode* ast){

	ast->Children[0]=malloc(sizeof(struct astnode));
	reduce_factor(root->Children[0],ast->Children[0]);
	ast->no_of_children++;

	if(((root->Children[1])->Children[0])->no==114){
		//reduce_anyterm(((root->Children[1])->Children[0]),ast->Children[0]);
	}
	else{
		ast->no_of_children++;
		ast->Children[1]=malloc(sizeof(struct astnode));

		//copy op2 into ast somehow
		ast->no=(root->Children[1]->Children[0]->Children[0])->no;
		reduce_A2(root->Children[1],ast->Children[1]);
	}
}

void reduce_A2(struct node* root,struct astnode* ast){
	if(((root->Children[2])->Children[0])->no==114){
		reduce_factor((root->Children[1]),ast);
	}
	else{
		ast->no_of_children++;
		ast->Children[0]=malloc(sizeof(struct astnode));

		reduce_factor((root->Children[1]),ast->Children[0]);
		//copy op2 into ast somehow
		ast->no=(root->Children[2]->Children[0]->Children[0])->no;
		ast->Children[1]=malloc(sizeof(struct astnode));
		reduce_A2(root->Children[2],ast->Children[1]);
	}
}

void reduce_factor(struct node* root,struct astnode* ast){
	if(root->no_of_children==3)
		reduce_arith_expr(root->Children[1],ast);
	if(root->no_of_children==1){
		reduce_var_id_num(root->Children[0],ast);
	}
}

void reduce_
