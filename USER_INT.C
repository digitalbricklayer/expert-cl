
/* USER_INT.C ****************************************************************

			   User Interface Module

			   Written by Jack Hughes

			   Modularized 15 - 6 - 90

******************************************************************************/

#include <graph.h>
#include "expert.h"


/* display options for the reset menu and do validation on the input */
void do_reset_menu(void)
{
	int choice;

	_clearscreen(_GCLEARSCREEN);
	printf("\tReset options\n\n");
	printf("\t\t1) Reset database and agenda\n");
	printf("\t\t2) Reset agenda\n");
	printf("\t\t3) Reset database\n");
	printf("\t\t4) Return to main menu\n\n");
	printf("\tEnter an option : ");
	scanf("%d", &choice);

	switch(choice)
		{
		case 1:
			reset_agenda_and_database();
			break;
		case 2:
			reset_agenda();
			break;
		case 3:
			reset_database();
			break;
		case 4:
			return;
		}
}

/* print out the options for the main menu */
void main_menu(void)
{
	_clearscreen(_GCLEARSCREEN);
	printf("\tMain Menu\n\n\n");
	printf("\t\t1) Questions\n");
	printf("\t\t2) Forward chain\n");
	printf("\t\t3) Backward chain\n");
	printf("\t\t4) Examine rule base\n");
	printf("\t\t5) Examine data base\n");
	printf("\t\t6) Examine inferred data\n");
	printf("\t\t7) Reset options\n");
	printf("\t\t8) Quit\n\n");
	printf("\tEnter your choice : ");
}

/* do list of questions for forward chaining */
void do_quest_menu(void)
{
	int choice, q, ctr;

	do
		{
		ctr = 0;
		_clearscreen(_GCLEARSCREEN);
		printf("\tQuestion Menu\n\n\n");
		for (q = 0; q < MAX_QUESTIONS; q++)
			{
			if (!its_empty(get_qb_id(q)))
				{
				printf("\t\t%d) %s   current value is %s\n",
					  q+1, get_qb_id(q), get_value(get_qb_id(q)));
				ctr++;
				}
			}
		printf("\t\t%d) Return to main menu\n\n", ctr+1);
		printf("\tSelect a question : ");
		scanf("%d", &choice);
		}
	while (choice <= 0 || choice > ctr+1);
	if (choice == ctr+1)
		return; /* return to main question menu */
	else
		do_question_forward(--choice); /* otherwise ask the question */
}

/* print out rule base */
void print_rules(void)
{
	register int i;
	char c;

	for (i = 0; i < RULE_NUM; i++)
		 show_rule_without_status(i);
	printf("\n\t========== Press any key to continue=============");
	c = getch();
}

/* print out given rule */
void show_rule_without_status(int num)
{
	int i;

	for (i = 0; i < MAX_COND; i++)
		{
		if (!its_empty(get_rb_cond_id(num, i)))
			{
			if (i == 0)
				printf("\t\tIf ");
			else
				printf("\t\t And ");
			printf("%s %s\n", get_rb_cond_id(num, i), get_rb_cond_val(num, i));
			}
		}
	for (i = 0; i < MAX_CONS; i++)
		{
		if (!its_empty(get_rb_cons_id(num, i)))
			{
			if (i == 0)
				printf("\t\tThen ");
			else
				printf("\t\t And ");
			printf("%s %s\n", get_rb_cons_id(num, i), get_rb_cons_val(num, i));
			}
		}
	printf("\n");
}

/* return pointer to value held in the data base */
char *get_value(char string[])
{
	register int i;

	for (i = 0; i < SIZE_OF_DB; i++)
		if (!strcmp(get_db_id(i), string))  /* if a match is found */
			return (get_db_val(i));

	return ("not known");
}

/* print out the data base */
void examine_d_base(void)
{
	register int i;
	char c;

	_clearscreen(_GCLEARSCREEN);
	for (i = 0; i < SIZE_OF_DB; i++)
		{
		if (!its_empty(get_db_id(i)))
			{
			printf("data base item %d ", i+1);
			printf("%s %s", get_db_id(i), get_db_val(i));
			if (get_db_question_flag(i))
				printf("     User supplied\n");
			else
				printf("     Inferred data\n");
			}
		}
	printf("\n\t============Press a key to continue================");
	c = getch();
}

/* Print consequences of all fired rules */
void print_results(void)
{
	register int i;
	char c;

	_clearscreen(_GCLEARSCREEN);
	for (i = 0; i < RULE_NUM; i++)
		if (get_rb_fire_flag(i))
			print_cons(i);
	printf("\n\t============Press a key to continue===============");
	c = getch();
}

/* Print consequences of single rule */
void print_cons(int i)
{
	register int z;

	for (z = 0; z < MAX_CONS; z++)
		if (!its_empty(get_rb_cons_id(i, z)))
			printf("%s %s\n", get_rb_cons_id(i, z), get_rb_cons_val(i, z));
}
