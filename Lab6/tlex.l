%{ 
# include<stdlib.h>
# include"y.tab.h"
void yyerror(char *);
%}

%%
[0-9]+  { yylval = atoi(yytext);
	return INT;	
	}
[+\n*()]    {return *yytext;}
[ \t];
.    yyerror("Invalid input\n");
%%

int yywrap(){
return 1;
}
