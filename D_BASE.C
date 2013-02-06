
/* D_BASE.C ******************************************************************

			   Data base interface routines
			      Written by Jack Hughes

			       Completed 12 - 6 - 90

******************************************************************************/

#include "expert.h" /* contains all global definitions */


/* data base declaration */
static struct db_item d_base[SIZE_OF_DB];  /* struct is in expert.h */


/* set question flag */
int set_db_question_flag(int num, int flag)
/* set question flag and return TRUE else return FALSE */
{
	if (num > SIZE_OF_DB-1 || num < 0)
		return FALSE;
	else
		d_base[num]. question_flag = flag;
}

/* return question flag */
int get_db_question_flag(int num)
/* return value in num else return FALSE */
{
	if (num > SIZE_OF_DB-1 || num < 0)
		return FALSE;
	else
		return d_base[num]. question_flag;
}

/* set identifier */
int set_db_id(int num, char id[])
/* return TRUE if successful else return FALSE */
{
	if (num > SIZE_OF_DB-1 || num < 0)
		return FALSE;
	else
		strcpy(d_base[num]. single. id, id);
}

/* return identifier */
char *get_db_id(int num)
/* return id if successful else return FALSE */
{
	if (num > SIZE_OF_DB-1 || num < 0)
		return FALSE;
	else
		return d_base[num]. single. id;
}

/* set value */
int set_db_val(int num, char value[])
/* return TRUE if successful else return FALSE */
{
	if (num > SIZE_OF_DB-1 || num < 0)
		return FALSE;
	else
		strcpy(d_base[num]. single. val, value);
}

/* return value */
char *get_db_val(int num)
/* return value else return FALSE */
{
	if (num > SIZE_OF_DB-1 || num < 0)
		return FALSE;
	else
		return d_base[num]. single. val;
}
