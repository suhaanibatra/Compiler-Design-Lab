%%
[0-9] {printf("Digit\n");}
[0-9]+ {printf("Number\n");}
^[-+]?[0-9]*[.][0-9]+$ {printf("Real number\n");}
%%


int main(){
    yylex();
    return 0;
}
