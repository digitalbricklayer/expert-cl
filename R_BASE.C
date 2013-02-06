
/* R_BASE.C ******************************************************************

		   Rule base interface routines

		      Written by Jack Hughes

		       Completed 16 - 6 - 90

	Convert r_base into an array of pointers to the rule structure
******************************************************************************/

#include "expert.h"

static struct rule r_base[RULE_NUM];	/* rule base */

int set_rb_cond_num(int rule_num, int num)
{
	if (rule_num > RULE_NUM)
	    handle_error(TOO_MANY_RULES);
	else
	    r_base[rule_num]. cond_num = num;
}

int get_rb_cond_num(int rule_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. cond_num;
}

int set_rb_fire_flag(int rule_num, int flag)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
		return FALSE;
	else
		r_base[rule_num]. fire_flag = flag;
}

int get_rb_fire_flag(int rule_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. fire_flag;
}

int set_rb_cond_id(int rule_num, int cond_num, char id[])
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    strcpy(r_base[rule_num]. cond[cond_num]. id, id);
}

char *get_rb_cond_id(int rule_num, int cond_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. cond[cond_num]. id;
}

int set_rb_cond_val(int rule_num, int cond_num, char val[])
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    strcpy(r_base[rule_num]. cond[cond_num]. val, val);
}

char *get_rb_cond_val(int rule_num, int cond_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. cond[cond_num]. val;
}

int set_rb_cons_id(int rule_num, int cons_num, char id[])
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    {
	    strcpy(r_base[rule_num]. cons[cons_num]. id, id);
	    return TRUE;
	    }
}

char *get_rb_cons_id(int rule_num, int cons_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. cons[cons_num]. id;
}

int set_rb_cons_val(int rule_num, int cons_num, char val[])
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    {
	    strcpy(r_base[rule_num]. cons[cons_num]. val, val);
	    return TRUE;
	    }
}

char *get_rb_cons_val(int rule_num, int cons_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. cons[cons_num]. val;
}
int set_rb_condition_flag(int rule_num, int cond_num, int flag)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    r_base[rule_num]. cond[cond_num]. condition_flag = flag;
}

int get_rb_condition_flag(int rule_num, int cond_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. cond[cond_num]. condition_flag;
}

int set_rb_try_flag(int rule_num, int flag)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    r_base[rule_num]. try_flag = flag;
}

int get_rb_try_flag(int rule_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. try_flag;
}

int set_rb_live_flag(int rule_num, int flag)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    r_base[rule_num]. live_flag = flag;
}

int get_rb_live_flag(int rule_num)
{
	if (rule_num > RULE_NUM-1 || rule_num < 0)
	    return FALSE;
	else
	    return r_base[rule_num]. live_flag;
}
