
/* BACKWARD.C *****************************************************************

					 Depth first backward chaining module

						   Written by Jack Hughes

						   Modularized 12 - 6 - 90

						 Is now completely out of date
			(bug in the WHY explanation which is fixed in breadth.c)

******************************************************************************/

#include "expert.h"

int value_exist(char id[], char value[]);
void mark_rule_as_dead(int rule, char id[], char value[]);
int db_holds_goal(char id[], char value[]);
int find_rule(char id[], char value[]);
int prove_rule(int rule);
void put_cond_on_agenda(int rule);

void get_and_check_goal(void)
{
	char goal_id[ID_LENGTH], goal_value[VAL_LENGTH];

	printf("\n\tInput goal id : ");
	scanf("%s", goal_id);
	printf("\n\tInput goal value : ");
	scanf("%s", goal_value);
	if (!its_a_question(goal_id) &&
	   (value_exists(goal_id, goal_value)))
		{
		push(goal_id, goal_value);
		backward();
		}
	else
		{
		printf("\n\nInvalid goal");
		return;
		}
}

int value_exists(char id[], char value[])
{
	int z, y;

	for (z = 0; z < RULE_NUM; z++)
		{
		for (y = 0; y < MAX_CONS; y++)
			{
			if (!strcmp(id, get_rb_cons_id(z, y)) &&
			   (!strcmp(value, get_rb_cons_val(z, y))))
				return TRUE;
			}
		}
	return FALSE;
}

void backward(void)
{
	switch(db_holds_goal(get_id_from_agenda(), get_value_from_agenda()))
		{
		int result;
		static int rule;
		case YES:
			pop();
			if (agenda_is_empty())
				return;
			else
				{
				set_rb_live_flag(rule, FALSE);
				backward();
				}
			break;
		case NO:
			result = find_rule(get_id_from_agenda(), get_value_from_agenda());
			if (result == FAIL)
				{
				if (its_a_question(get_id_from_agenda()))
					{
					question(get_id_from_agenda());
					backward();
					}
				else
					{
					mark_rule_as_dead(rule, get_id_from_agenda(), get_value_from_agenda());
					set_rb_live_flag(rule, FALSE);
					pop();
					if (agenda_is_empty())
						return;
					else
						backward();
					}
				}
			else
				{
				rule = result;
				if (prove_rule(rule))
					{
					fire(rule);
					backward();
					}
				else
					{
					put_cond_on_agenda(rule);
					set_rb_live_flag(rule, TRUE);
					backward();
					}
				}
			break;
		case NOT_QUITE:
			mark_rule_as_dead(rule, get_id_from_agenda(), get_value_from_agenda());
			set_rb_live_flag(rule, TRUE);
			pop();
			if (agenda_is_empty())
				return;
			else
				backward();
			break;
		}
}

void mark_rule_as_dead(int rule, char id[], char value[])
{
	int t, z;

	set_rb_try_flag(rule, TRUE);

	for (t = 0; t < RULE_NUM; t++)
		{
		for (z = 0; z < MAX_COND; z++)
			{
			if (!strcmp(id, get_rb_cond_id(t, z)) &&
			   (!strcmp(value, get_rb_cond_val(t, z))))
				set_rb_try_flag(t, TRUE);
			}
		}
}

int db_holds_goal(char id[], char value[])
{
	int i;

	for (i = 0; i < SIZE_OF_DB; i++)
		{
		if (!strcmp(id, get_db_id(i)) &&
		   (!strcmp(value, get_db_val(i))))
			return YES;
		else
			if (!strcmp(id, get_db_id(i)))
				return NOT_QUITE;
		}
	return NO;
}

int find_rule(char id[], char value[])
{
	int z, q;

	for (z = 0; z < RULE_NUM; z++)
		{
		if (!get_rb_try_flag(z))
			{
			for (q = 0; q < MAX_CONS; q++)
				{
				if (!strcmp(id, get_rb_cons_id(z, q)) &&
				   (!strcmp(value, get_rb_cons_val(z, q))))
					return z;
				}
			}
		}
	return FAIL;
}

int prove_rule(int rule)
{
	int t, z, count = 0;

	for (t = 0; t < MAX_COND; t++)
		{
		if (!its_empty(get_rb_cond_id(rule, t)))
			{
			for (z = 0; z < SIZE_OF_DB; z++)
				{
				if (!strcmp(get_rb_cond_id(rule, t), get_db_id(z)) &&
				   (!strcmp(get_rb_cond_val(rule, t), get_db_val(z))))
					count++;
				}
			}
		}
	if (count == get_rb_cond_num(rule))
		return TRUE;
	else
		return FALSE;
}

void put_cond_on_agenda(int rule)
{
	int z;

	for (z = 0; z < MAX_COND; z++)
		{
		if (!get_rb_condition_flag(rule, z))
			{
			if (!its_empty(get_rb_cond_id(rule, z)))
				{
				push(get_rb_cond_id(rule, z), get_rb_cond_val(rule, z));
				set_rb_condition_flag(rule, z, TRUE);
				return;
				}
			}
		}
}

