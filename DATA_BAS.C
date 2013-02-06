
/* DATA_BAS.C ****************************************************************

			   Data base handling routines

			      Written by Jack Hughes

			       Completed 12 - 6 - 90

******************************************************************************/

#include "expert.h"

int find_space_on_db(void);

/* reset database value and all relevent flags */
void reset_database(void)
{
	int z;

	for (z = 0; z < SIZE_OF_DB; z++)
		{
		set_db_question_flag(z, FALSE);
		set_db_id(z, "");
		set_db_val(z, "");
		}
}

/* Place all non NULL consequences from the rule to be fired on the data base at db_num + 1 */
void fire(int i)
{
	register int z;

	set_rb_fire_flag(i, TRUE);
	for (z = 0; z < MAX_CONS; z++)
		if (!its_empty(get_rb_cons_id(i, z)))
			load_db(FALSE, get_rb_cons_id(i, z), get_rb_cons_val(i, z));
}
/* go through data base and find a blank spot, return the subscipt to load_db */
int find_space_on_db(void)
{
	int c;

	for (c = 0; c < SIZE_OF_DB; c++)
		if (its_empty(get_db_id(c)))
			return(c);

	return(FAIL);
}

/* find a space for data base item, and put it there */
void load_db(int flag, char string1[], char string2[])
{
	register int c;


	if ((c = find_space_on_db()) == FAIL)
		handle_error(NO_SPACE_ON_D_B);
	else
		{
		set_db_id(c, string1);
		set_db_val(c, string2);
		if (flag == TRUE)  /* then it is a question */
			set_db_question_flag(c, TRUE);
		else               /* got to be inferred    */
			set_db_question_flag(c, FALSE);
		}
}

/* function to remove a single occurence of an identifier from a data base */
void destroy_previous_value(char string[])
{
	register int z;

	for (z = 0; z < SIZE_OF_DB; z++)
		if (!strcmp(get_db_id(z), string))
			reset_db_item(z); /* found match, now get rid of it */
}

/* reset data base item i to NULL */
void reset_db_item(int i)
{
	set_db_id(i, "");       /* reset identifier */
	set_db_val(i, "");      /* reset value      */
	set_db_question_flag(i, NULLED); /* reset question flag */
}
