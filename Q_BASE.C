
/* Q_BASE.C ******************************************************************

			   Question Base interface routines

				Written by Jack Hughes

				 Completed 12 - 6 - 90

******************************************************************************/

#include "expert.h"
#define MAX_QUESTIONS    50

static struct id q_base[MAX_QUESTIONS];
static struct value temp[MAX_VALUES];


int set_qb_id(int question_num, char id[])
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		strcpy(q_base[question_num]. id, id);
}

char *get_qb_id(int question_num)
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		return q_base[question_num]. id;
}

int set_qb_text(int question_num, char text[])
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		strcpy(q_base[question_num]. text, text);
}

char *get_qb_text(int question_num)
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		return q_base[question_num]. text;
}

int set_qb_q_base_flag(int question_num, int flag)
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		q_base[question_num]. q_base_flag = flag;
}

int get_qb_q_base_flag(int question_num)
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		return q_base[question_num]. q_base_flag;
}

int set_qb_value(int question_num, int value_num, char value[])
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		if (value_num > MAX_VALUES-1 || value_num < 0)
			return FALSE;
		else
			strcpy(q_base[question_num]. value_list[value_num]. value, value);
}

char *get_qb_value(int question_num, int value_num)
{
	if (question_num > MAX_QUESTIONS-1 || question_num < 0)
		return FALSE;
	else
		if (value_num > MAX_VALUES-1 || value_num < 0)
			return FALSE;
		else
			return q_base[question_num]. value_list[value_num]. value;
}

int set_temp_value(int value_num, char value[])
{
	if (value_num > MAX_QUESTIONS-1 || value_num < 0)
		return FALSE;
	else
		strcpy(temp[value_num]. value, value);
}

char *get_temp_value(int value_num)
{
	if (value_num > MAX_QUESTIONS-1 || value_num < 0)
		return FALSE;
	else
		return temp[value_num]. value;
}
