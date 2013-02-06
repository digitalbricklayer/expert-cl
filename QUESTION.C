
/* QUESTION.C ****************************************************************


			Question handling routines

			  Written by Jack Hughes

   All functions involved in producing q_base and producing question are here

			  Modularised 12 - 6 - 90

******************************************************************************/

#include "expert.h"
#include <graph.h>


/* top level function for backward chaining rule */
void question(char identifier[])
{
	int a;
	char debug[ID_LENGTH];

	for (a = 0; a < MAX_QUESTIONS; a++)
		{
		strcpy(debug, get_qb_id(a));
		if (!strcmp(debug, identifier))
			{
			do_question_backward(a);
			break;
			}
		}
}

/* top level function for forward chaining rule */
void do_question_forward(int choice)
{
	int id, q, ctr;

	do
		{
		_clearscreen(_GCLEARSCREEN);
		if (!its_empty(get_qb_text(choice)))
			printf("%s\n\n", get_qb_text(choice));
		else
			printf("\t%s\n\n", get_qb_id(choice));
		ctr = 0;
		for (q = 0; q < MAX_VALUES; q++)
			{
			if (!its_empty(get_qb_value(choice, q)))
				{
				printf("\t\t%d) %s\n", q+1, get_qb_value(choice, q));
				ctr++;
				}
			}
		printf("\n\n\tEnter your selection : ");
		scanf("%d", &id);
		}
	while (id <= 0 || id > ctr);
	destroy_previous_value(get_qb_id(choice));
	load_db(TRUE, get_qb_id(choice), get_qb_value(choice, --id));
	set_qb_q_base_flag(choice, TRUE);
	do_quest_menu();
}

/* write question text and question values to the screen and do validationon input */
void do_question_backward(int choice)
{
	int id, q, ctr;

	if (!get_qb_q_base_flag(choice))
		{
		do
			{
			_clearscreen(_GCLEARSCREEN);
			if (!its_empty(get_qb_text(choice)))
				printf("%s\n\n", get_qb_text(choice));
			else
				printf("\t%s\n\n", get_qb_id(choice));
			ctr = 0;
			for (q = 0; q < MAX_VALUES; q++)
				{
				if (!its_empty(get_qb_value(choice, q)))
					{
					printf("\t\t%d) %s\n", q+1, get_qb_value(choice, q));
					ctr++;
					}
				}
			printf("\t\t%d) Why\n", ctr+1);
			printf("\n\n\tEnter your selection : ");
			scanf("%d", &id);
			}
		while (id <= 0 || id > ctr+1);
		if (id == ctr+1)
			{
			do_explanation();
			do_question_backward(choice);
			}
		else
			{
			destroy_previous_value(get_qb_id(choice));
			load_db(TRUE, get_qb_id(choice), get_qb_value(choice, --id));
			set_qb_q_base_flag(choice, TRUE);
			}
		}
}

/* find identifiers which are questions and place in the question list (base) */
void put_questions_into_q_base(void)
{
	register int p, z;

	for (p = 0; p < RULE_NUM; p++)
		{
		for (z = 0; z < MAX_COND; z++)
			{
			if (!its_empty(get_rb_cond_id(p, z)))
				{
				if ((its_a_question(get_rb_cond_id(p, z))) &&
				   (!id_on_q_base(get_rb_cond_id(p, z))))
					add_id_to_q_base(get_rb_cond_id(p, z));
				}
			}
		}
}

/* is the identifier supplied as an argument already in the question base */
int id_on_q_base(char identifier[])
{
	register int p;

	for (p = 0; p < MAX_QUESTIONS; p++)
		if (!strcmp(get_qb_id(p), identifier))
			return TRUE;

	return FALSE;
}

/* is the identifier a question */
int its_a_question(char identifier[])
{
	register int p, z;

	for (p = 0; p < RULE_NUM; p++)
		{
		for (z = 0; z < MAX_CONS; z++)
			if (!strcmp(get_rb_cons_id(p, z), identifier))
				return FALSE;
		}
	return TRUE;
}

/* place identifier into the question base */
void add_id_to_q_base(char identifier[])
{
	register int p;

	for (p = 0; p < MAX_QUESTIONS; p++)
		if (its_empty(get_qb_id(p)))
			{
			set_qb_id(p, identifier);
			return;
			}
	handle_error(NO_SPACE_ON_Q_B);
}

/* go through the list of question identifiers, find their associated value */
void get_all_values(void)
{
	register int z;

	for (z = 0; z < MAX_QUESTIONS; z++)
		{
		load_values(get_qb_id(z));
		copy_temp_struct(get_qb_id(z));
		reset_temp();
		}
}

/* given an identifier load its values from the rule base, place in temp */
void load_values(char identifier[])
{
	register int z, y;

	for (z = 0; z < RULE_NUM; z++)
		for (y = 0; y < MAX_COND; y++)
			if (!strcmp(get_rb_cond_id(z, y), identifier))
				put_into_temp(get_rb_cond_val(z, y));
}

/* put value into temp for storage */
void put_into_temp(char value[])
{
	register int z;

	for (z = 0; z < MAX_VALUES; z++)
		{
		if (!strcmp(get_temp_value(z), value))
			return;
		else
			if (its_empty(get_temp_value(z)))
				{
				set_temp_value(z, value);
				return;
				}
		}
}

/* copy temp into question list */
void copy_temp_struct(char identifier[])
{
	int subscript;

	subscript = find_subscript_of_id_slot(identifier);
	copy_temp(subscript);
}

/* find the subscript of the argument identifier, return to calling function */
int find_subscript_of_id_slot(char identifier[])
{
	register int z;

	for (z = 0; z < MAX_QUESTIONS; z++)
		if (!strcmp(get_qb_id(z), identifier))
			return z;
}

/* low level function for copying temp into (subscript)th element of q_base */
void copy_temp(int subscript)
{
	register int s;

	for (s = 0; s < MAX_VALUES; s++)
		set_qb_value(subscript, s, get_temp_value(s));
}

/* reset temp storage area */
void reset_temp(void)
{
	register int p, j;

	for (p = 0; p < MAX_VALUES; p++)
		set_temp_value(p, "");
}

/* load queston text (if there is any) into the question base */
void get_question_text(char filename[])
{
	FILE *fp;

	filename = strip_postfix(filename);
	if ((fp = fopen(filename, "r")) == NULL)
		return; /* if question text hasn't been defined then do nothing */
	else
		load_text(fp); /* else load it */
}

/* place .QES postfix onto filename and return it */
char *strip_postfix(char filename[])
{
	int z = 0;

	while (filename[z] != '.') /* get to the full stop and stop */
		z++;
	z++;
	filename[z] = 'q';    /* and replace with .QES postfix */
	z++;
	filename[z] = 'e';
	z++;
	filename[z] = 's';
	return filename;
}

/* return next word form file */
char *get_next_word(FILE *fp)
{
	char line[80], ch;

	fscanf(fp, "%s", line);
	if ((ch = getc(fp)) == EOF)
	    {
	    printf("Got to the end of file\n");
	    exit(1);
	    }
	else
	    return line;
}

/* load question text from filename.QES */
void load_text(FILE *fp)
{
	int sub;
	char id[80], line[LINE];

	while (TRUE)
		{
		strcpy(id, get_next_word(fp));
		if (!strcmp(id, "end_of_file"))
			break;
		else
			{
			sub = find_sub(id);
			strcpy(line, get_next_line(fp));
			set_qb_text(sub, line);
			}
		}
	fclose(fp);
}

/* return subscript of given identifier in the question base */
int find_sub(char id[])
{
	int z;

	for (z = 0; z < MAX_QUESTIONS; z++)
		if (!strcmp(id, get_qb_id(z)))
			return z;
}

/* return line of text form file */
char *get_next_line(FILE *fp)
{
	char line[LINE];

	fgets(line, LINE, fp);
	strip_carriage_return(line);
	return line;
}

/* strip out the carriage return from the given string */
void strip_carriage_return(char line[])
{
	int i;

	for (i = 0; i < LINE; i++)
		if (line[i] == '\n')
			line[i] = NULL;
}
