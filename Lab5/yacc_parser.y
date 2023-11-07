%{
    #include <stdio.h>
    yylex();
    yyerror();
%}

%%

L: E 'n' {printf("L -> E n\n");}
;

E: E '+' T {printf("E -> E + T\n");}
 | T {printf("E -> T\n");}
 ;

T: T '*' F {printf("T-> T*F\n");}
 | F {printf("T->F\n");}
 ;

F: '(' E ')' {printf("F -> (E)\n");}
| 'a' {printf("F -> a\n");}
 ;

%%

yylex(){
    return getchar();
}

yyerror(const char* s){
    printf("%s \n", s);
}

main(){
    yyparse();
    return 0;
}