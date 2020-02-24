#include <time.h>

                clock_t    start_time, end_time;

                double total_CPU_time, total_CPU_time_in_seconds;

                start_time = clock();

               //copy pasted from lexer main
                intialize_symbol_table();

	              struct tokenlexemepair* ex;
	              FILE* fp=fopen("test","r");
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
                //lexer end

                //parser start

                //parser end

                end_time = clock();

                total_CPU_time  =  (double) (end_time - start_time);

                total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;

             // Print both total_CPU_time and total_CPU_time_in_seconds
