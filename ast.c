#include "parser.c"

struct astnode{
	struct astnode* Children[50];
	int no_of_children;
	char lex[21];
	int no;
	struct astnode* next;
	/*astnode(){
		no_of_children=0;
		next=NULL;
	}*/
};

void reduce_program(struct node* root,struct astnode* ast){
	
	if((root->Children[0])->no_of_children!=1){
		ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
		if(ast->no_of_children!=0)
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_mDs(root->Children[0],ast->Children[ast->no_of_children-1]);	
	}
	if((root->Children[1])->no_of_children!=1){
		ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
		if(ast->no_of_children!=0)
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_other_modules(root->Children[1],ast->Children[ast->no_of_children-1]);
	}

		ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
		if(ast->no_of_children!=0)
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_driver_module(root->Children[2],ast->Children[ast->no_of_children-1]);

	if((root->Children[3])->no_of_children!=1){
		ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
		if(ast->no_of_children!=0)
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_other_modules(root->Children[3],ast->Children[ast->no_of_children-1]);
	}
}

void reduce_mDs(struct node* root,struct astnode* ast){
	//make_astnode( ast,(((root->Children)[0])->Children[2])->lex ,"TK_ID" );
	ast->no=root->no;
	ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
	if(ast->no_of_children!=0)
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	strcpy( ast->Children[ast->no_of_children]->lex , (((root->Children)[0])->Children[2])->lex);
	ast->no_of_children++;
	ast->Children[ast->no_of_children-1]->no=111;
	if(strcmp(((root->Children[1])->Children[0])->lex,"")==0){
		return;
	}
	else{
		reduce_mDs(root->Children[1],ast);
	}
}

void reduce_other_modules(struct node* root,struct astnode* ast){
	if(root->no_of_children==1) return;
	
	ast->no=root->no;
	ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
	if(ast->no_of_children!=0)
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children++;

	reduce_module(root->Children[0],ast->Children[no_of_children-1]);
	reduce_other_modules(root->Children[1],ast);
}

void reduce_expr(struct node* root,struct astnode* ast){

	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->Children[0]->next=NULL;
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

	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->Children[0]->next=NULL;
	reduce_anyterm(root->Children[0],ast->Children[0]);
	ast->no_of_children++;

	if(((root->Children[1])->Children[0])->no==114){
		//reduce_anyterm(((root->Children[1])->Children[0]),ast->Children[0]);
	}
	else{

		ast->no_of_children++;
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[0]->next=ast->Children[1];
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
		ast->Children[0]=calloc(sizeof(struct astnode));

		reduce_anyterm((root->Children[1]),ast->Children[0]);
		//copy Lop into ast somehow
		ast->no=(root->Children[2]->Children[0]->Children[0])->no;
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[0]->next=ast->Children[1];
		reduce_N7(root->Children[2],ast->Children[1]);
	}
}

void reduce_anyterm(struct node* root,struct astnode* ast){
	if((root->Children[0])->no==56){
		ast->no=((root->Children[0])->Children[0])->no;
	}
	else{
		ast->no_of_children++;
		ast->Children[0]=calloc(sizeof(struct astnode));
		reduce_arith_expr(root->Children[0],ast->Children[0]);
		if(root->Children[1]->Children[0]->no==114){

		}
		else{
			
			ast->Children[1]=calloc(sizeof(struct astnode));
			ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
			ast->no_of_children++;
			reduce_N8(root->Children[1],ast->Children[1]);
		}
	}
}

void reduce_N8(struct node* root,struct astnode* ast){
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->no_of_children++;
	reduce_rel_op(root->Children[0],ast->Children[0]);
	ast->Children[1]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children++;
	reduce_arith_expr(root->Children[1],ast->Children[1]);
}

void reduce_rel_op(struct node* root,struct astnode* ast){
	ast->no=(root->Children[0])->no;
}

void reduce_arith_expr(struct node* root,struct astnode* ast){

	ast->Children[0]=calloc(sizeof(struct astnode));
	reduce_term(root->Children[0],ast->Children[0]);
	ast->no_of_children++;

	if(((root->Children[1])->Children[0])->no==114){
		//reduce_anyterm(((root->Children[1])->Children[0]),ast->Children[0]);
	}
	else{
		
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
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
		ast->Children[0]=calloc(sizeof(struct astnode));

		reduce_term((root->Children[1]),ast->Children[0]);
		//copy Lop into ast somehow
		ast->no=(root->Children[2]->Children[0]->Children[0])->no;
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_A1(root->Children[2],ast->Children[1]);
	}
}

void reduce_term(struct node* root,struct astnode* ast){

	ast->Children[0]=calloc(sizeof(struct astnode));
	reduce_factor(root->Children[0],ast->Children[0]);
	ast->no_of_children++;

	if(((root->Children[1])->Children[0])->no==114){
		//reduce_anyterm(((root->Children[1])->Children[0]),ast->Children[0]);
	}
	else{
		
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
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
		ast->Children[0]=calloc(sizeof(struct astnode));

		reduce_factor((root->Children[1]),ast->Children[0]);
		//copy op2 into ast somehow
		ast->no=(root->Children[2]->Children[0]->Children[0])->no;
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
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

void reduce_var_id_num(struct node* root,struct astnode* ast){
	if(root->no_of_children==1){
		strcpy(ast->lex,(root->Children[0])->lex);
		ast->no=((root->Children[0])->no);
	}
	else{
**********************************************
	}
}

void reduce_U(struct node* root,struct astnode* ast){
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->no_of_children++;
	reduce_op1(root->Children[0],ast->Children[0]);
	ast->Children[1]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children+++;
	reduce_new_NT(root->Children[1],ast->Children[1]);
}

void reduce_new_NT(struct node* root,struct astnode* ast){
	if(root->no_of_children==1)
	reduce_var_id_num(root->Children[0],ast);
	
}

void reduce_stmts(struct node* root,struct astnode* ast){

	if(root->no_of_children==1){
		return;
	}
	//if(ast->no_of_children==0){
	ast->no= 17 ;
	ast->Children[no_of_children]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children++;
	reduce_stmt(root->Children[0],ast->Children[no_of_children-1]);
	reduce_stmts(root->Children[1],ast);
	//}
}

void reduce_stmt(struct node* root,struct astnode* ast){
	if((root->Children[0])->no==19)
		reduce_io_stmt(root->Children[0],ast);
	if((root->Children[0])->no==20)
		reduce_single_stmt(root->Children[0],ast);
	if((root->Children[0])->no==46)
		reduce_declare_stmt(root->Children[0],ast);
	if((root->Children[0])->no==47)
		reduce_cond_stmt(root->Children[0],ast);
	if((root->Children[0])->no==52)
		reduce_iter_stmt(root->Children[0],ast);
}

void reduce_io_stmt(struct node* root,struct astnode* ast){
	if((root->Children[0])->no==68){
		ast->Children[0]=calloc(sizeof(struct astnode));
		ast->no_of_children++;
		(ast->Children[0])->no=68;
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		strcpy((ast->Children[1])->lex,(root->Children[2])->lex);
		(ast->Children[1])->no= 111 ;
	}
	if((root->Children[0])->no==69){
		ast->Children[0]=calloc(sizeof(struct astnode));
		ast->no_of_children++;
		(ast->Children[0])->no=69;
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_var(root->Children[2],ast->Children[1]);
		//(ast->Children[1])->no=  ;
	}
}

void simple_stmt(struct node* root,struct astnode* ast){
	if((root->Children[0])->no==21)
		reduce_assign_stmt(root->Children[0],ast);
	if((root->Children[0])->no==26)
		reduce_module_reuse_stmt(root->Children[0],ast);
}


void reduce_assign_stmt(struct node* root,struct astnode* ast){
	ast->no=105;//should we write lexeme??
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->no_of_children++;
	ast->Children[0]->no=111;
	strcpy((ast->Children[0])->lex,(root->Children[0])->lex);
	reduce_which_stmt(root->Children[1],ast);
}

void reduce_which_stmt(struct node* root,struct astnode* ast){
	if(root->Children[0]->no==23)
		reduce_Lvalueid_stmt(root->Children[0],ast);
	else 
		reduce_Lvaluearr_stmt(root->Children[0],ast);
}

void reduce_Lvalueid_stmt(struct node* root,struct astnode* ast){
	ast->Children[1]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children++;
	reduce_expr(root->Children[1],ast->Children[1]);
}

void reduce_Lvaluearr_stmt(struct node* root,struct astnode* ast){
	//have a doubt so i didnt implement
	// ast->Children[ast->no_of_children++]=calloc(sizeof(struct astnode));
	// ast->Children[ast->no_of_children-1]->no=106;

	ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children++;
	reduce_index(root->Children[1],ast->Children[ast->no_of_children-1]);

	// ast->Children[ast->no_of_children++]=calloc(sizeof(struct astnode));
	// ast->Children[ast->no_of_children-1]->no=107;
	
	reduce_expr(root->Children[4],ast->Children[2]);	

}

void reduce_index(struct node* root,struct astnode* ast){
	strcpy(ast->lex,root->Children[0]->lex);
	ast->no=root->Children[0]->no;
}

void reduce_module_reuse_stmt(struct node* root,struct astnode* ast){
	if((root->Children[0]->Children[0])!=114){
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->Children[1]=calloc(sizeof(struct astnode));
	ast->Children[2]=calloc(sizeof(struct astnode));
	ast->no_of_children=3;
	ast->Children[0]->next=ast->Children[1];
	ast->Children[1]->next=ast->Children[2];
	reduce_optional(root->Children[0],ast->Children[0]);
	reduce_id(root->Children[3],ast->Children[1]);
	reduce_id_list(root->Children[6],ast->Children[2]);
	ast->no=105;
	}
	else{
		ast->Children[0]=calloc(sizeof(struct astnode));
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->no_of_children=2;
		ast->Children[0]->next=ast->Children[1];
		reduce_id(root->Children[3],ast->Children[0]);
		reduce_id_list(root->Children[6],ast->Children[1]);
		ast->no=115;
	}

}
void reduce_optional(struct node* root,struct astnode* ast){
	reduce_id_list(root->Children[1],ast);
}

void reduce_id_list(struct node* root,struct astnode* ast){
	if(root->no_of_children==1){
		ast->Children[no_of_children]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_id(root->Children[0],ast->Children[ast->no_of_children-1]);
	}
	else{
		ast->Children[no_of_children]=calloc(sizeof(struct astnode));
		ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
		ast->no_of_children++;
		reduce_id(root->Children[0],ast->Children[ast->no_of_children-1]);
		reduce_id_list(root->Children[2],ast);
	}
}

void reduce_declare_stmt(struct node* root,struct astnode* ast){
	ast->no=root->no;
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->Children[1]=calloc(sizeof(struct astnode));
	ast->no_of_children=2;
	(ast->Children[0])->next=ast->Children[1];
	reduce_id_list(root->Children[1],ast->Children[0]);
	reduce_data_type(root->Children[3],ast->Children[1]);
}

void reduce_conditional_stmt(struct node* root,struct astnode* ast){
	ast->no=root->no;
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->Children[1]=calloc(sizeof(struct astnode));
	ast->Children[2]=calloc(sizeof(struct astnode));
	ast->no_of_children=3;
	(ast->Children[0])->next=ast->Children[1];
	(ast->Children[1])->next=ast->Children[2];
	reduce_id(root->Children[2],ast->Children[0]);
	reduce_case_stmt(root->Children[5],ast->Children[1]);
	reduce_default(root->Children[6],ast->Children[2]);
}

//please look into default into datatype

void reduce_case_stmt(struct node* root,struct astnode* ast){
	ast->no=root->no;
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->no_of_children=1;
	struct astnode* child=ast->Children[0];
	child->Children[0]=calloc(sizeof(struct astnode));

	child->no_of_children=1;
	child->no=50;
	reduce_value(root->Children[1],child);
	reduce_stmts(root->Children[3],child->Children[0]);
	reduce_case_stmt_dash(root->Children[6],ast);
}

void reduce_case_stmt_dash(struct node* root,struct astnode* ast){
	if(root->no_of_children==0) return;

	ast->Children[no_of_children]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children++;

	struct astnode* child=ast->Children[ast->no_of_children-1];
	child->Children[0]=calloc(sizeof(struct astnode));

	child->no_of_children=1;
	child->no=50;
	reduce_value(root->Children[1],child);
	reduce_stmts(root->Children[3],child->Children[0]);
	reduce_case_stmt_dash(root->Children[6],ast);

}

void reduce_iter_stmt(struct node* root,struct astnode* ast){
	if(root->no_of_children==7){
		//while
		ast->Children[0]=calloc(sizeof(struct astnode));
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->no_of_children=2;
		(ast->Children[0])->next=ast->Children[1];
		ast->no=86;
		reduce_arithorBool_expr(root->Children[2],ast->Children[0]);
		reduce_stmts(root->Children[5],ast->Children[1]);
	}
	else{
		//for
		ast->no=80;
		ast->Children[0]=calloc(sizeof(struct astnode));
		ast->Children[1]=calloc(sizeof(struct astnode));
		ast->Children[2]=calloc(sizeof(struct astnode));
		ast->no_of_children=3;
		(ast->Children[0])->next=ast->Children[1];
		(ast->Children[1])->next=ast->Children[2];
		reduce_id(root->Children[2],ast->Children[0]);
		reduce_range(root->Children[4],ast->Children[1]);
		reduce_stmts(root->Children[7],ast->Children[2]);
	}
}

void reduce_id(struct node* root,struct astnode* ast){
	strcpy(ast->lex,root->lex);
	ast->no=111;
}

void reduce_input_plist(struct node* root,struct astnode* ast){
	ast->no=root->no;
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->no_of_children=1;
	struct astnode* child=ast->Children[0];
	child->Children[0]=calloc(sizeof(struct astnode));

	child->no_of_children=1;
	//child->no=root->Children[2]->no;
	reduce_id(root->Children[0],ast->Children[0]);
	reduce_data_type(root->Children[2],child->Children[0]);
	reduce_input_plist_dash(root->Children[3],ast);
}

void reduce_input_plist_dash(struct node* root,struct astnode* ast){
	if(root->no_of_children==0) return;
	ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children+=1;

	struct astnode* child=ast->Children[no_of_children-1];
	child->Children[0]=calloc(sizeof(struct astnode));

	child->no_of_children=1;
	//child->no=root->Children[2]->no;
	
	reduce_id(root->Children[1],child);
	reduce_data_type(root->Children[3],child->Children[0]);
	reduce_input_plist_dash(root->Children[4],ast);
}
void reduce_output_plist(struct node* root,struct astnode* ast){
	ast->no=root->no;
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->no_of_children=1;
	struct astnode* child=ast->Children[0];
	child->Children[0]=calloc(sizeof(struct astnode));

	child->no_of_children=1;
	//child->no=root->Children[2]->no;
	reduce_id(root->Children[0],ast->Children[0]);
	reduce_type(root->Children[2],child->Children[0]);
	reduce_input_plist_dash(root->Children[3],ast);
}
void reduce_output_plist_dash(struct node* root,struct astnode* ast){
	if(root->no_of_children==0) return;
	ast->Children[ast->no_of_children]=calloc(sizeof(struct astnode));
	ast->Children[ast->no_of_children-1]->next=ast->Children[ast->no_of_children];
	ast->no_of_children+=1;

	struct astnode* child=ast->Children[no_of_children-1];
	child->Children[0]=calloc(sizeof(struct astnode));

	child->no_of_children=1;
	//child->no=root->Children[2]->no;
	
	reduce_id(root->Children[1],child);
	reduce_type(root->Children[3],child->Children[0]);
	reduce_input_plist_dash(root->Children[4],ast);	
}

void reduce_data_type(struct node* root,struct astnode* ast){
	if(root->no_of_children==1){
		ast->no=root->Children[0]->no;
	}
	else{
		reduce_type(root->Children[5],ast);
		ast->Children[0]=calloc(sizeof(struct astnode));
		ast->no_of_children=1;
		reduce_range(root->Children[2],ast->Children[0])
	}
}

void reduce_type(struct node* root,struct astnode* ast){
	ast->no=root->no;
}

void reduce_range(struct node* root,struct astnode* ast){
	ast->Children[0]=calloc(sizeof(struct astnode));
	ast->Children[1]=calloc(sizeof(struct astnode));
	ast->Children[0]->next=ast->Children[1];
	ast->no_of_children=2;
	reduce_num(root->Children[0],ast->Children[0]);
	reduce_num(root->Children[2],ast->Children[1]);
}

void reduce_(struct node* root,struct astnode* ast)

void reduce_output_plist_dash(struct node* root,struct astnode* ast)
