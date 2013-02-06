
/* BREADTH.C *****************************************************************

		      Breadth first backward chaining module.
   (it only checks to make sure current path isn't a complete waste of time)

			   Written by Jack Hughes

			   Completed 19 - 6 - 90

	 Should let the user know whether goal has been solved or not.

******************************************************************************/

#include "expert.h"

/* asks the user to enter the goal, then validates it before passing it to */
/* backward() */
void get_and_check_goal(void)
{
	char goal_id[ID_LENGTH], goal_value[VAL_LENGTH];

	printf("\n\tInput goal id : ");
	scanf("%s", goal_id);               /* get the identifier */
	printf("\n\tInput goal value : ");
	scanf("%s", goal_value);            /* get the value */
	if (!its_a_question(goal_id) &&            /* check validity of inputs */
	   (value_exists(goal_id, goal_value)))
		{
		push(goal_id, goal_value);      /* if they are valid, put values onto */
		backward();                     /* agenda and backward chain on that */
		}
	else
		{
		printf("\n\nInvalid goal");     /* else return to main menu */
		return;
		}
}

/* returns TRUE if value exists in any of the rule base consequences else FALSE */
int value_exists(char id[], char value[])
{
	int z, y;

	for (z = 0; z < RULE_NUM; z++)
		{
		for (y = 0; y < MAX_CONS; y++)
			{
			if ((!strcmp(id, get_rb_cons_id(z, y)) &&
			   (!strcmp(value, get_rb_cons_val(z, y)))))
				return TRUE;
			}
		}
	return FALSE;
}

/* recursive backward chainer, uses agenda to control recursing */
void backward(void)
{
	switch(db_holds_goal(get_id_from_agenda(), get_value_from_agenda()))
		{                /* does the data base hold current goal */
		int result;
		static int rule;
		case YES:
			pop();
			if (agenda_is_empty())   /* then either goal is satisfied or cannot */
				return;              /* prove goal */
			else
				{
				set_live_rule(rule, FALSE);  /* reset currently active rule */
				backward();                     /* and go around again */
				}
			break;
		case NO:
			result = find_rule(get_id_from_agenda(), get_value_from_agenda());
			if (result == FAIL)
				{
				if (its_a_question(get_id_from_agenda()))
					{
					question(get_id_from_agenda());  /* if goal is a question */
					backward();                      /* then ask it(if ot hasn't */
					}                                /* been asked before) */
				else
					{
					mark_rule_as_dead(rule, get_id_from_agenda(), get_value_from_agenda());
					set_live_rule(rule, FALSE);   /* ensure that no rules */
					pop();                           /* with unprovable conditions */
					if (agenda_is_empty())           /* are still active */
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
					fire(rule); /* if rule can be proved then fire it and */
					backward(); /* go around again */
					}
				else
					{
					put_cond_on_agenda(rule);  /* put next goal onto agenda */
					set_live_rule(rule, TRUE); /* set currently active rule */
					backward();
					}
				}
			break;
		case NOT_QUITE:
			mark_rule_as_dead(rule, get_id_from_agenda(), get_value_from_agenda());
			set_live_rule(rule, FALSE);  /* if carn't prove goal then remove */
			pop();                         /* from agenda and mark rules as inactive */
			if (agenda_is_empty())
				return;
			else
				backward();
			break;
		}
}

void set_live_rule(int rule, int flag)
{
	reset_live_rule();
	set_rb_live_flag(rule, flag);
}

void reset_live_rule(void)
{
	int i;

	for (i = 0; i < RULE_NUM; i++)
		if (get_rb_live_flag(i))
			set_rb_live_flag(i, FALSE);
}

/* set the try fag as active for given rule */
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

/* return TRUE if data base holds identifier and value */
/* return NOT_QUITE if data base only holds identifier */
/* return FALSE if data base holds neither */
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

/* find rule with given identifier and value as consequences and try to disprove */
/* it */
int find_rule(char id[], char value[])
{
	int c;

	if ((c = get_rule(id, value)) == FAIL)
		return FAIL;
	else
		{
		if (try_to_disprove_rule(c))
			{
			set_rb_try_flag(c, TRUE);
			find_rule(id, value);
			}
		else
			return c;
		}
}

/* return subscipt of rule with given identifier and value as consequences */
int get_rule(char id[], char value[])
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

/* compare rule conditions with data base and try to disprove that condition */
/* ie by finding an identifier with a different value in the data base */
int try_to_disprove_rule(int rule)
{
	int i, z;

	for (i = 0; i < MAX_COND; i++)
		{
		if (!its_empty(get_rb_cond_id(rule, i)))
			if ((z = db_holds_goal(get_rb_cond_id(rule, i), get_rb_cond_val(rule, i))) == NOT_QUITE)
				return TRUE;
		}
	return FALSE;
}

/* try to prove all conditions of a given rule to be true by comparing each */
/* condition to the data base */
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

/* place next condition onto the agenda, so that it can be used in backward() */
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
