%{
    #include <stdio.h>
%}

%token INT
%%
L:E '\n' {printf("%d\n", $1);}
 |
 ;
E:E '+' T {$$ = $1 + $3;}
 | T {$$ = $1;}
 ;
T: T '*' F {$$ = $1 * $3;}
 | F {$$ = $1;}

F: '(' E ')' {$$ = $2;}
 | INT
 ;
%%

void yyerror(char *s){
    printf("%s\n", s);
}

main(){
    yyparse();
    return 0;
}