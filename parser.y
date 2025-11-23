%{
/* --- DEFINITION SECTION --- */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

/* Symbol Table Structure */
struct Symbol {
    char* name;           /* Name of the set, e.g., "A" */
    UniversalSet* set;    /* The set itself */
};

/* Simple storage for variables */
struct Symbol symbol_table[100];
int symbol_count = 0;

/* Function to save or update a variable in the table */
void save_variable(char* name, UniversalSet* set) {
    /* 1. Check if variable already exists to update it */
    for(int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            /* Free old memory to prevent leaks */
            free_universal_set(symbol_table[i].set);
            free(symbol_table[i].set);

            /* Update with new set */
            symbol_table[i].set = set;
            return;
        }
    }

    /* 2. If not found, create a new one */
    if (symbol_count < 100) {
        symbol_table[symbol_count].name = strdup(name);
        symbol_table[symbol_count].set = set;
        symbol_count++;
    } else {
        printf("Error: Memory full! Too many variables.\n");
    }
}

/* Function to retrieve a variable from the table */
/* MOVED OUTSIDE of save_variable (Fixed C syntax error) */
UniversalSet* get_variable(char* name) {
    for(int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].set;
        }
    }
    printf("Error: Undefined variable %s\n", name);
    return NULL;
}

/* Prototypes required by Bison */
int yylex();
void yyerror(char * s) {
    printf("Error: %s\n", s);
}
%}

/* --- BISON DECLARATIONS --- */

%union {
    int num;
    char* name;
    struct UniversalSet* u_set;
}

/* Tokens with values */
%token <num> NUMBER
%token <name> VAR_NAME

/* Keywords and Special Symbols */
%token LET              /* Keyword "let" */
%token EOL              /* End of Line (Enter key) */

/* Brackets and punctuation */
/* Note: Assuming LSQUAREBRACE maps to '{' in lexer based on assignment example */
%token LROUNDBRACE      /* ( */
%token RROUNDBRACE      /* ) */
%token LSQUAREBRACE     /* { */
%token RSQUAREBRACE     /* } */
%token COMMA            /* , */
%token ASSIGN           /* = */

/* Operator Tokens */
%token OP_UNION         /* + */
%token OP_INTERSECTION  /* ^ */
%token OP_DIFFERENCE    /* - */
%token OP_CARTESIAN     /* x */
%token OP_EQUAL         /* == */
%token OP_NOTEQUAL      /* != */

/* Operations Priority */
/* Cartesian product has higher priority than Union/Difference */
%left OP_UNION OP_DIFFERENCE
%left OP_INTERSECTION
%left OP_CARTESIAN

/* Types for Non-Terminals */
%type <u_set> expression
%type <u_set> set_literal
%type <u_set> num_list

%%

/* --- GRAMMAR RULES --- */

/* 1. Main Program Loop */
/* This allows the calculator to accept multiple lines one after another */
program:
    | program line
;

line:
    EOL { /* Empty line, do nothing */ }
    | statement EOL {
        printf("> "); /* Print prompt for the next line */
    }
;

/* 2. Statements (Commands) */
statement:
    /* Assigning a variable: let A = ... */
    LET VAR_NAME ASSIGN expression {
        save_variable($2, $4);
        printf("Defined %s\n", $2);
        free($2); /* Free the name string copy */
    }

    /* Just an expression: A + B (Print the result) */
    | expression {
        if ($1 != NULL) {
            printf("= ");
            print_set($1); /* Call C function to print */
            printf("\n");

            /* The result is temporary, so we must free it */
            free_universal_set($1);
            free($1);
        }
    }

    /* Equality Test: A == B */
    | expression OP_EQUAL expression {
        bool result = is_equal($1, $3);
        if (result) printf("= true\n"); else printf("= false\n");

        /* Cleanup temporary sets */
        free_universal_set($1); free($1);
        free_universal_set($3); free($3);
    }

    /* Inequality Test: A != B */
    | expression OP_NOTEQUAL expression {
        bool result = is_equal($1, $3);
        if (!result) printf("= true\n"); else printf("= false\n");

        free_universal_set($1); free($1);
        free_universal_set($3); free($3);
    }
;

/* 3. Mathematical Expressions */
expression:
    /* Variable usage: A */
    VAR_NAME {
        $$ = get_variable($1);
        free($1);
    }
    /* Explicit set: {1, 2} */
    | set_literal {
        $$ = $1;
    }
    /* Operations */
    | expression OP_UNION expression        { $$ = ops_union($1, $3); }
    | expression OP_INTERSECTION expression { $$ = ops_intersection($1, $3); }
    | expression OP_DIFFERENCE expression   { $$ = ops_difference($1, $3); }
    | expression OP_CARTESIAN expression    { $$ = ops_cartesian_product($1, $3); }
;

/* 4. Set Construction Rules */
set_literal:
    LSQUAREBRACE num_list RSQUAREBRACE {
        $$ = $2; /* Pass the created set up */
    }
;

num_list:
    NUMBER {
        /* Start of list: create new set and add first number */
        $$ = malloc(sizeof(UniversalSet));
        init_universal_set($$, TYPE_INT_SET);
        add_int($$, $1);
    }
    | num_list COMMA NUMBER {
        /* Recursion: take existing set ($1) and add next number ($3) */
        $$ = $1;
        add_int($$, $3);
    }
;

%%