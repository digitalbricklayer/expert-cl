
/* PARSE.C *******************************************************************

			Rule base parsing routines

			  Written by Gino Salvato

			   Completed 1 - 5 - 90

******************************************************************************/


#include "expert.h"

#define RE_INIT i = 0, j = 0, k = 0

/* local prototypes */
void manip_line(char label[], char id[], char val[], char line[]);
FILE *check_file(char filename[]);
char *reset(char str[]);
void invoke_load_cond(char id[], char val[]);
void invoke_load_cons(char id[], char val[]);
void load_either(char id[], char val[]);
void new_rule(void);

static int i = 0, j = 0, k = 0;
static int flag, cond, cons, L = 1, m = 0, n = 0;

/* Top level function for parsing a rule base and placing into rule base */
void parse_file(char filename[])
{
	char line[MAXLINE], temp[VAL_LENGTH], temp_id[ID_LENGTH];
	int ITTER = 0;
	FILE *ifp, *check_file();
	char temp_val[MAX], *reset();

	ifp = check_file(filename);
	while (fgets(line, MAXLINE, ifp) != NULL)
		{
		if (!strcmp(line, "\n"))
			new_rule();
		if (ITTER++ > 0)
			{
			strcpy(temp, reset(temp));
			strcpy(temp_id, reset(temp_id));
			strcpy(temp_val, reset(temp_val));
			RE_INIT;
			}
		manip_line(temp, temp_id, temp_val, line);
		}
	fclose(ifp);
}

/* check file exists */
FILE *check_file(char filename[])
{
	FILE *fopen(), *ifp;

	if ((ifp = fopen(filename, "r")) == NULL)
		handle_error(FILE_NOT_FOUND);
	return(ifp);
}

/* reset given array to null */
char *reset(char str[])
{
	int i = 0;

	for (i = 0; str[i] != NULL; i++)
		str[i] = NULL;
	return(str);
}

/* get line type, identifier and value */
void manip_line(char label[], char id[], char val[], char line [])
{
	if (line[j] == ' ')
		while (line[j] == ' ')
			j++;
	while (line[j] != '\n')
		{
		while (line[j] != ' ' && line[j] != '\n')
			label[k++] = line[j++];
		if (line[j] == ' ' || line[j] == '\n')
			while (line[j] == ' ')
				j++;
		k = 0;
		while (line[j] != ' ' && line[j] != '\n')
			id[k++] = line[j++];
		while (line[j] == ' ')
			j++;
		while (line[j] != '\n')
			val[i++] = line[j++];
		if (!strcmp(label, "if"))
			invoke_load_cond(id, val);
		else if (!strcmp(label, "then"))
			invoke_load_cons(id, val);
		else if (!strcmp(label, "and"))
			load_either(id, val);

		}
}

/* load condition into rule base via load_cond */
void invoke_load_cond(char id[], char val[])
{
	m++;
	set_rb_cond_id(--L, --m, id);
	set_rb_cond_val(L, m, val);
	cond++;
	set_rb_cond_num(L, cond);
	flag = TRUE;
	if (cond > MAX_COND)
		handle_error(TOO_MANY_CONDITIONS);
	L++;
	m++;
}

/* load consequence into rule base via load_cons */
void invoke_load_cons(char id[], char val[])
{
	n++;
	set_rb_cons_id(--L, --n, id);
	set_rb_cons_val(L, n, val);
	flag = FALSE;
	L++;
	n++;
}

/* decide if an and keyword is part of a condition or consequence */
void load_either(char id[], char val[])
{
	if (flag == TRUE)
		invoke_load_cond(id, val);
	else
		invoke_load_cons(id, val);
}

/* reset indexes for new rule */
void new_rule(void)
{
	L++;
	cond = 0;
	m = 0;
	n = 0;
}
