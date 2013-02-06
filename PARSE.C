
/* PARSE.C *******************************************************************

			Rule base parsing routines

			  Written by Jack Hughes

			   Completed ? - 11 - 90

******************************************************************************/


#include "expert.h"

#define IF  0
#define THEN	2
#define AND 1
#define NOT_RECOGNISED	-1
#define NUM_TOKEN   3
#define TOKEN_SIZE  10
#define MAX_WORD    80

FILE *check_file(char filename[]);
int get_token(FILE *fp);
void eat_invisibles(FILE *fp);
char *get_identifier(FILE *fp);
char *_get_value(FILE *fp);
int convert_token(char token[]);
char *get_word(FILE *fp);

/* Top level function for parsing a rule base and placing into rule base */
void parse_file(char filename[])
{
    FILE *fp; /* rule base file */
    int token; /* numeric representation of symbol */
    int count = 0; /* rule number currently being parsed */
    int cond_num = 0; /* number of conditions in current rule */
    int cons_num = 0; /* number of consequences in current rule */
    int token_flag = IF; /* does the token refer to a condition or consequence */
    char id[ID_LENGTH], val[VAL_LENGTH];

    fp = check_file(filename);
    while (TRUE)
	{
	/* eat_invisibles(fp); */
	token = get_token(fp); /* get the token and return the relevant type */
	switch (token)
	    {
	    case IF:
		cons_num = 0;
		/* eat_invisibles(fp); */
		strcpy(id, get_identifier(fp));
		/* eat_invisibles(fp); */
		strcpy(val, _get_value(fp));
		set_rb_cond_id(count, cond_num, id);
		set_rb_cond_val(count, cond_num, val);
		set_rb_cond_num(count, cond_num);
		token_flag = IF;
		cond_num++;
		break;
	    case AND:
		/* eat_invisibles(fp); */
		strcpy(id, get_identifier(fp));
		/* eat_invisibles(fp);	*/
		strcpy(val, _get_value(fp));
		if (token_flag == IF)
		    {
		    set_rb_cond_id(count, cond_num, id);
		    set_rb_cond_val(count, cond_num, val);
		    set_rb_cond_num(count, cond_num);
		    }
		else
		    {
		    set_rb_cons_id(count, cons_num, id);
		    set_rb_cons_val(count, cons_num, val);
		    }
		cond_num++;
		break;
	    case THEN:
		cond_num = 0;
		/* eat_invisibles(fp); */
		strcpy(id, get_identifier(fp));
		/* eat_invisibles(fp); */
		strcpy(val, _get_value(fp));
		set_rb_cons_id(count, cons_num, id);
		set_rb_cons_val(count, cons_num, val);
		token_flag = THEN;
		cons_num++;
		break;
	    default:
		handle_error(BAD_TOKEN);
		break;
	    }
	count++;
	}
    fclose(fp);
}

/* check file exists */
FILE *check_file(char filename[])
{
    FILE *ifp;

    if ((ifp = fopen(filename, "r")) == NULL)
	handle_error(FILE_NOT_FOUND);
    return(ifp);
}

/* return an integer representation of of a given token ( ie if then or and ) */
int get_token(FILE *fp)
{
    int char_count = 0, token_rep;
    char token[TOKEN_SIZE];

    strcpy(token, get_next_word(fp));
    token_rep = convert_token(token); /* convert the token into an integer to be used */
    return (token_rep); /* by the case statement in the main parse function */
}

/* return integer representation of given token */
int convert_token(char token[])
{
    static char token_types[NUM_TOKEN][LINE] =
    {
	    "if",
	    "and",
	    "then"
    };
    int i;

    for (i =  0; i < NUM_TOKEN; i++)  /* go through the tokens to find a match */
	if (!strcmp(token, token_types[i]))
	    return (i); /* when you find it return the subscript */
    return (NOT_RECOGNISED); /* if you don't find a token then return the not found code */
}

/* remove all non printables from given stream until a printable is reached */
void eat_invisibles(FILE *fp)
{
    int c;
    char ch;

    ch = getc(fp);
    while ((c = isalpha(ch)) == 0)
	ch = getc(fp);
}

/* get identifier from file and do validation */
char *get_identifier(FILE *fp)
{
    char identifier[ID_LENGTH], temp_id[MAX_WORD];
    int c; /* holds the number of elements in the id */

    strcpy(temp_id, get_next_word(fp));
    if ((c = strlen(temp_id)) <= ID_LENGTH - 1)
	{
	strcpy(identifier, temp_id);
	return (identifier);
	}
    else
	handle_error(IDENTIFIER_TOO_BIG);
}

/* get value from file and do validation */
char *_get_value(FILE *fp)
{
    char value[ID_LENGTH], temp_value[MAX_WORD];
    int c; /* holds the number of elements in the val */

    strcpy(temp_value, get_next_word(fp));
    if ((c = strlen(temp_value)) <= VAL_LENGTH - 1)
	{
	strcpy(value, temp_value);
	return (value);
	}
    else
	handle_error(VALUE_TOO_BIG);
}

/* returns the next word from the given stream assumes that eat_spaces */
/* has been used immediately before */
char *get_word(FILE *fp)
{
    char word[MAX_WORD], ch;
    int char_count = 0, c;

    ch = getc(fp);
    while ((c = isalpha(ch)) > 0) /* go to the end of the word placing the word */
	{
	word[char_count++] = ch; /* in token */
	ch = getc(fp);
	}
    return (word);
}
