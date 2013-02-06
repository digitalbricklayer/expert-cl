
/* FORWARD.C *****************************************************************

			Forward chaining module (unstructured)

				Written by Jack Hughes

				Modularized 12 - 6 - 90

******************************************************************************/

#include "expert.h"

void compare_db_items(int i);

/* Forward chain to find solution to all rules, forward chaining is not directed in any way */
void forward(void)
{
	register int i;

	for (i = 0; i < RULE_NUM; i++) /* go through each rule to find a match */
		{
		if (!get_rb_fire_flag(i)) /* if rule has already been fired */
			 compare_db_items(i);
		else
			i++;      /* then skip rule */
		}
}

/* Take a rule and try to match it's conditions to the data base */
void compare_db_items(int i)
{
	register int z, y;      /* z is each condition of a rule */
	int count = 0;          /* y is each data base item      */
	int fail_flag = TRUE;   /* has the condition failed      */

	for (z = 0; z < get_rb_cond_num(i); z++) /* take a condition from rule i */
		{
		if (fail_flag == FALSE)
			break;
		for (y = 0; y < find_db_num(); y++) /* and try to match it up to the items on the data base */
			if ((!strcmp(get_rb_cond_id(i, z), get_db_id(y)) &&
			   (!strcmp(get_rb_cond_val(i, z), get_db_val(y)))))
				{
				count++; /* if you do find a match add one to the number of matches found in this rule */
				fail_flag = TRUE;     /* do not bomb out, please */
				break;
				}
			else
				fail_flag = FALSE;

		if (count == get_rb_cond_num(i))
			{
			fire(i);   /* so fire it and */
			forward(); /* go back to the beginning of the rule base */
			break;
			}
		}
}

/* return the number of items in the data base, used in forward chaining */
int find_db_num(void)
{
	int number = 0, z;

	for (z = 0; z < SIZE_OF_DB; z++)
		if (!its_empty(get_db_id(z)))
			number++;
	return number;
}
