%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Adding the file for tokens from Bison/Parser.*/
#include "parser.tab.h"

void yyerror(char *s);
%}

/* Ending after the file is read (no waiting for the new file ) */
%option noyywrap

%%

    /* Ignoring spaces and tab symbols */
[ \t\r]+    { }

    /* End of Line */
\n          { return EOL; }

    /* Key words */
"let"       { return LET; }
"quit"      { return EXIT; }
"exit"      { return EXIT; }
"IF"        { return IF; }
"DO"        { return DO; }
"ELSE"      { return ELSE; }
"help"      { return HELP; }


    /* Comparison operators */
"=="        { return OP_EQUAL; }
"!="        { return OP_NOTEQUAL; }
"="         { return ASSIGN; }

    /* Math operators */
"+"         { return OP_UNION; }
"^"         { return OP_INTERSECTION; }
"-"         { return OP_DIFFERENCE; }
"x"         { return OP_CARTESIAN; }

    /* Brackets and commas */
"{"         { return LSQUAREBRACE; }
"}"         { return RSQUAREBRACE; }
"("         { return LROUNDBRACE; }
")"         { return RROUNDBRACE; }
","         { return COMMA; }

    /* Numbers */
[0-9]+      {
    yylval.num = atoi(yytext); /* saving to yylval.num */
    return NUMBER;
}

    /* 8. Sets names  */
[a-zA-Z][a-zA-Z0-9]* {
    yylval.name = strdup(yytext); /* saving to yylval.name */
    return VAR_NAME;
}

    /* 9. for the rest of the symbols we throw an error */
.           { printf("Unknown character: %s\n", yytext); }

%%