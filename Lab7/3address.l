%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex();
void yyerror(const char *);
extern int yylval;
extern char iden[20];
%}

%%

[0-9]+ {yylval= atoi(yytext); return digit;}
[a-zA-Z]+ {strcpy(iden, yytext); yylval = 1; return id;}
[ \t] {;}
\n return 0;
. return yytext[0];

%%

int yywrap(){
    return 1;
}
