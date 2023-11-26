### Compiler Design Lab - 1

1. WAP that takes source program of C language via file handling and counts number of lines, number of words, number of characters, and number of keywords present in the source program and display them. 


### Compiler Design Lab - 2

1. Lex tool


### Compiler Design Lab - 3

1. Complete lexical analyser using lex tool. 

### Compiler Design Lab - 4
1. Design LL(1) parser for the following language 
- S -> AA
      A -> aA | b

Parse the following string ababa

- E -> TE’ 
      E’ -> +TE’ | NULL
      T -> FT’
      T’ -> *FT’ | NULL
      F -> (E) | id
Parse the following string id + id * id


### Compiler Design Lab - 5

Construct YACC parser for the following grammar
L -> E n
E -> E + T | T
T -> T * F | F
F -> ( E ) | a

For the same grammar write the s-attributed definition and find the value of expression “2+3*5”

### Compiler Design Lab - 6
Integration of lex and yacc

### Compiler Design Lab -7
Use YACC to generate a 3-address code for an expression



### Compiler Design Lab Endsem
Consider the following grammar

E -> E ‘\n’ {printf(E.val)}
E -> E % T {E.val = E.val % T.val}
	| T {E.val = T.val}
T -> F ^ T {T.val = F.val ^ T.val}
	| F {T.val = F.val}
F -> (E) {F.val = E.val}
	| Num {F.val = Num}

Write a YACC program to calculate the value of expression where Num is taken as an input from lex. 
