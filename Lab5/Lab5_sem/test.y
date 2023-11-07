%{
#include <stdio.h>
#include <math.h>
yylex();
yyerror(const char *s);
int yylval;
%}

%token NUM 

%%

L: E '\n' {printf("%d\n", $1);}
;

E: E '+' T {$$ = $1 + $3;}
 | T {$$ = $1;}
 ;

T: T '*' F {$$ = $1 * $3;}
 | F {$$ = $1;}
 ;

F: '(' E ')' {$$ = $2;}
 | NUM 
 ;


%%

yylex(){
    char c = getchar();

    if (c >= '0' && c <= '9') {  // If the input is a number
        yylval = c - '0';
        return NUM;
    }

    return c;  // If the input is an operator or parentheses
}

yyerror(const char *s){
    printf ("Parsing error---- %s\n", s);
}

int main(){
    yyparse();
    return 0;
}