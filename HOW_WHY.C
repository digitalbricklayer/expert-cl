
/* HOW_WHY.C *****************************************************************

			     How and why module

		   Functions to reply to how and why requests
			 How not currently implemented

			    Written by Jack Hughes

			    Modularized 12 - 6 - 90

******************************************************************************/

#include "expert.h"

void show_rule(int num);
char *return_status(char id[], char val[]);
int find_rule_cond(char id[], char val[]);

/* top level rule for WHY explanation */
void do_explanation(void)
{
	int num;
	char c;

	printf("\n\n\tAm trying to prove that %s is %s\n\tin order to prove rule %d, as shown below\n\n",
				get_id_from_agenda(), get_value_from_agenda(),
				num = find_rule_cond(get_id_from_agenda(), get_value_from_agenda()));
	show_rule(num);
	printf("\n\t============= Press any key to continue=============");
	c = getch();
}

/* write given rule to screen */
void show_rule(int num)
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
			printf("%s %s %s\n", get_rb_cond_id(num, i), get_rb_cond_val(num, i),
					   return_status(get_rb_cond_id(num, i), get_rb_cond_val(num, i)));
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
}

/* return string containing status of identifier on the data base */
char *return_status(char id[], char val[])
{
	int z;

	for (z = 0; z < SIZE_OF_DB; z++)
		{
		if (!strcmp(id, get_db_id(z)) &&
		   (!strcmp(val, get_db_val(z))))
			return "[TRUE]";
		else
			if (!strcmp(id, get_db_id(z)))
				return "[FALSE]";
		}
	return "[ ? ]";
}

/* find the currently active rule */
int find_rule_cond(char id[], char val[])
{
	int z;

	for (z = 0; z < RULE_NUM; z++)
		if (get_rb_live_flag(z))
			return z;
}
