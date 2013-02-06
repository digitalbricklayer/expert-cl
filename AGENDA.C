
/* AGENDA.C ******************************************************************

			 Agenda interface routines

			  Written by Jack Hughes

			   Completed 12 - 6 - 90

******************************************************************************/

#include "expert.h"

static struct stck stack[STACK_SIZE];
static struct stck *tos = stack, *pl = stack;

/* test to see if the agenda is empty */
int agenda_is_empty(void)
{
	if (pl == tos)
		return TRUE;
	else
		return FALSE;
}

/* remove top item from the agenda */
void pop(void)
{
	if (pl == tos)
		return;
	pl--;
	*(pl + 1);
}

/* put given item onto top of the agenda */
void push(char id[], char val[])
{
	pl++;
	if (pl == (tos + STACK_SIZE))
		handle_error(NO_MORE_STACK_SPACE);
	strcpy(pl -> id, id);
	strcpy(pl -> val, val);
}

/* return value of identifier from the top of the stack */
char *get_id_from_agenda(void)
{
	return pl -> id;
}

/* return value of the value from the top of the stack */
char *get_value_from_agenda(void)
{
	return pl -> val;
}

/* reset stack pointer and remove all data from the stack */
void reset_agenda(void)
{
	int z, q;

	for (q = 0; q < STACK_SIZE; q++)
		{
		for (z = 0; z < ID_LENGTH; z++)
			stack[q]. id[z] = NULL;
		for (z = 0; z < VAL_LENGTH; z++)
			stack[q]. val[z] = NULL;
		}
	tos = stack;
	pl = stack;
}
