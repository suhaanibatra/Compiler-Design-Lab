//definitions
%{
int COMMENT = 0;
int cnt = 0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%

{identifier}[-+*/%] {if (!COMMENT) printf("\n%s is an expression");}
#.*                      {printf("%s PREPROCESSOR DIRECTIVE\n", yytext);}
auto|
break|
case|
char|
const|
continue|
default|
do|
double|
else|
enum|
extern|
float|
for|
goto|
if|
int|
long|
register|
return|
short|
signed|
sizeof|
static|
struct|
switch|
typedef|
union|
unsigned|
void|
volatile|
while {printf("%s is a KEYWORD\n", yytext);}
"/*" {COMMENT = 1;}
"*/ {COMMENT = 0; cnt++;}

{identifier}\( {if (!COMMENT) printf("\nFUNCTION\n%s", yytext);}
\{ {if (!COMMENT) printf("\nBLOCK BEGINS\n");}
\} {if (!COMMENT) printf("\nBLOCK ENDS\n");}
{identifier}(\[[0-9]*\])? {if (!COMMENT) printf("\n%s is IDENTIFIER\n", yytext);}
\".*\" {printf("%s is a STRING\n", yytext);}
[0-9]+ {printf("%s is NUMBER\n", yytext);}

printf\(.+?\); { if (!COMMENT) printf("\n%s is a PRINTF STATEMENT", yytext); }

"="|
"+"|
"-"|
"*"|
"/"|
">"|
"<"|
"<="|
">="|
"=="|
"!="|
"&&"|
"||"|
"|"|
"&"|
"!" {printf("%s is OPERATOR\n", yytext);}

%%

int main(){
    yylex();
    return 0;
}

