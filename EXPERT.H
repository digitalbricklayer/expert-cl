/* global definitions for expert system shell */

#include <stdio.h>
#include <string.h>

#define TRUE        1
#define FALSE       0

#define RULE_NUM    85	  /* max number of rules in the rule base   */
#define ID_LENGTH   50	  /* identifier length */
#define VAL_LENGTH  50	  /* value length      */

#define MAX_COND    3	  /* maximum number of conditions per rule  */
#define MAX_CONS    1	  /* maximum number of conclusions per rule */

#define SIZE_OF_DB  40	  /* size of data base */

#define MAXLINE     80
#define MAX         20

#define FAIL        -1
#define NULLED      -1

#define MAX_VALUES  5
#define MAX_QUESTIONS   50

#define STACK_SIZE  15
#define NOT_QUITE   -1
#define NO  0
#define YES 1
#define LINE    80
#define EMPTY	0

/* Error message definitions */
#define FILE_NOT_FOUND      0
#define NO_FILE_SPECIFIED_ON_C_L    1
#define TOO_MANY_RULES      2
#define TOO_MANY_CONDITIONS     3
#define TOO_MANY_CONSEQUENCES   4
#define NO_SPACE_ON_D_B     5
#define NO_SPACE_ON_Q_B     6
#define NO_MORE_STACK_SPACE 7
#define BAD_TOKEN   8
#define VALUE_TOO_BIG	9
#define IDENTIFIER_TOO_BIG  10

struct value
{
	char value[VAL_LENGTH];
};

struct id
{
	char id[ID_LENGTH];
	struct value value_list[MAX_VALUES];
	char text[LINE];
	int q_base_flag;
};

struct stck
{
	char id[ID_LENGTH];
	char val[VAL_LENGTH];
};

struct db_item
{
	int question_flag;
	struct stck single;
};

struct sgle
{
	char id[ID_LENGTH];
	char val[VAL_LENGTH];
	int condition_flag;
};

struct rule
{
	int cond_num;
	int fire_flag;
	struct sgle cond[MAX_COND];
	struct sgle cons[MAX_CONS];
	int try_flag;
	int live_flag;
};

/************************* global prototypes ****************************/
/************************************************************************/
void garbage_collect(void);
void reset_agenda_and_database(void);
int its_empty(char string[]);
char *get_id_from_agenda(void);
char *get_value_form_agenda(void);
void push(char id[], char val[]);
void pop(void);
int agenda_is_empty(void);
void reset_agenda(void);
void get_and_check_goal(void);
int set_db_question_flag(int num, int flag);
int get_db_question_flag(int num);
int set_db_id(int num, char id[]);
char *get_db_id(int num);
int set_db_val(int num, char val[]);
char *get_db_val(int num);
void reset_database(void);
void fire(int i);
void handle_error(int error_num);
void forward(void);
int find_db_num(void);
void do_explanation(void); /* top level function for WHY */
void parse_file(char filename[]);
int set_qb_id(int question_num, char id[]);
char *get_qb_id(int question_num);
int set_qb_text(int question_num, char text[]);
char *get_qb_text(int question_num);
int set_qb_q_base_flag(int question_num, int flag);
int get_qb_q_base_flag(int question_flag);
int set_qb_value(int question_num, int value_num, char value[]);
char *get_qb_value(int question_num, int value_num);
int set_temp_value(int value_num, char value[]);
char *get_temp_value(int value_num);
void do_question_forward(int choice);
void do_question_backward(int choice);
void put_questions_into_q_base(void);
int id_on_q_base(char identifier[]);
int its_a_question(char identifier[]);
void add_id_to_q_base(char identifier[]);
void get_all_values(void);
void load_values(char identifier[]);
void put_into_temp(char value[]);
void copy_temp_struct(char identifier[]);
int find_subscript_of_id_slot(char identifier[]);
void copy_temp(int subscript);
void reset_temp(void);
void get_question_text(char filename[]);
char *strip_postfix(char filename[]);
char *get_next_word(FILE *fp);
void load_text(FILE *fp);
int find_sub(char id[]);
char *get_next_line(FILE *fp);
void strip_carriage_return(char line[]);
int set_rb_cond_num(int rule_num, int num);
int get_rb_cond_num(int rule_num);
int set_rb_fire_flag(int rule_num, int flag);
int get_rb_fire_flag(int rule_num);
int set_rb_cond_id(int rule_num, int cond_num, char id[]);
char *get_rb_cond_id(int rule_num, int cond_num);
int set_rb_cond_val(int rule_num, int cond_num, char val[]);
char *get_rb_cond_val(int rule_num, int cond_num);
int set_rb_cons_id(int rule_num, int cons_num, char id[]);
char *get_rb_cons_id(int rule_num, int cons_num);
int set_rb_cons_val(int rule_num, int cons_num, char val[]);
char *get_rb_cons_val(int rule_num, int cons_num);
int set_rb_condition_flag(int rule_num, int cond_num, int flag);
int get_rb_condition_flag(int rule_num, int cond_num);
int set_rb_try_flag(int rule_num, int flag);
int get_rb_try_flag(int rule_num);
int set_rb_live_flag(int rule_num, int flag);
int get_rb_live_flag(int rule_num);
void do_reset_menu(void);
void main_menu(void);
void do_quest_menu(void);
void print_rules(void);
void show_rule_without_status(int num);
char *get_value(char string[]);
void examine_d_base(void);
void print_results(void);
void print_cons(int i);
int value_exists(char id[], char value[]);
void set_dead_rule(int rule);
void mark_rule_as_dead(int rule, char id[], char value[]);
int db_holds_goal(char id[], char value[]);
int find_rule(char id[], char value[]);
int prove_rule(int rule);
void put_cond_on_agenda(int rule);
int get_rule(char id[], char value[]);
int try_to_disprove_rule(int rule);
int value_exist(char id[], char value[]);
void mark_rule_as_dead(int rule, char id[], char value[]);
int db_holds_goal(char id[], char value[]);
int find_rule(char id[], char value[]);
int prove_rule(int rule);
void put_cond_on_agenda(int rule);
void backward(void);
void set_live_rule(int rule, int flag);
void reset_live_rule(void);
void reset_db_item(int i);
char *get_value_from_agenda(void);
void destroy_previous_value(char string[]);
void load_db(int flag, char string1[], char string2[]);
