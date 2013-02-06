
/* EXP.C *********************************************************************

			Inference Mechanism Teaching Aid.
				Top level module

			    Written by Jack Hughes
			      Copmanthorpe Grange
				York. YO2 3TN

	  Mechanisms implemented are forward and depth first backward chaining

	  Related modules are :-
		  done  exp.c       this module, high level routines.
		  done  parse.c     rule base parser. (without any syntax checking)
		  done  r_base.c    definition of rule base + interface routines more validation
		  done  q_base.c         "      "  question base + "       "     necessary
		  done  d_base.c         "      "  data base  +    "       "
		  done  agenda.c         "      "  agenda     +    "       "
		  done  forward.c   forward chaining module and related functions
		  done  how_why.c   why routines only, how to be implemented later
		  done  question.c  question generation and asking module
		  done  error.c     error handling module
		  done  breadth.c   improved backward chainer, clips its search better
		  done  user_int.c  user interface module
		  done  data_bas.c  data base handling routines, not low level routines

	  Program not as yet stable enough to warrant a version number.

******************************************************************************/

#include "expert.h"   /* header containing all global parameters */

void main(int argc, char *argv[]);
void initialise_d_structures(void);
void garbage_collect(void);
void reset_agenda_and_database(void);
void generate_q_base(char filename[]);
int its_empty(char string[]);

/* program top level function */
void main(int argc, char *argv[])
{
	int choice;   /* used to store user input for the main menu */

	initialise_d_structures();  /* make sure all string are null and all flags are false */

	if (argc != 2) /* program name and rule base filename */
		handle_error(NO_FILE_SPECIFIED_ON_C_L); /* print error and exit */
	else
		parse_file(argv[1]); /* pass filename to be parsed */

	generate_q_base(argv[1]); /* place all question identifiers into q_base */
							  /* with their relevant values */
	while (TRUE)  /* loop until a valid answer is given */
		{
		main_menu();   /* print out the menu text */
		scanf("%d", &choice);
		switch(choice)
			{
			case 1:
				do_quest_menu();  /* menu to choose which questions to answer */
				break;
			case 2:
				garbage_collect();   /* reset all relevent flags */
				forward();           /* and forward chain */
				break;
			case 3:
				garbage_collect();
				get_and_check_goal();  /* get the goal and backward chain */
				break;
			case 4:
				print_rules();     /* print out the rule base */
				break;
			case 5:
				examine_d_base();  /* print out the data base */
				break;
			case 6:
				print_results();   /* print out inferred data */
				break;
			case 7:
				do_reset_menu();   /* reset menu ( for reseting data base and agenda) */
				break;
			case 8:
				exit(1);    /* exit the whole program */
				break;
			 } /* end of switch */
		}  /* end of while */
}  /* end of main */

void reset_agenda_and_database(void)
{
	reset_database();
	reset_agenda();
	garbage_collect();
}

/* initialise database and rule base */
/* not necessary when using dynamic allocation
   as these memory locations will not exist */
void initialise_d_structures(void)
{
	int i;
	register int j, z;

	/* Initialise rule base */
	for (i = 0; i < RULE_NUM; i++)
		{
		set_rb_fire_flag(i, FALSE);  /* reset fire flag */
		set_rb_try_flag(i, FALSE);   /* reset try flag */
		set_rb_live_flag(i, FALSE);  /* reset live flag */
		for (j = 0; j < MAX_COND; j++)
			{
			set_rb_cond_id(i, j, "");  /* reset condition id string */
			set_rb_condition_flag(i, j, FALSE);   /* reset condition flag */
			set_rb_cond_val(i, j, "");  /* reset condition value */
			}
		}

	/* Initialise data base */
	reset_database();
}

/* function to reset fire flag for each rule that has fired back to FALSE */
/* and remove all fired rules consequences from the data base             */
void garbage_collect(void)
{
	register int i, y;

	for (i = 0; i < RULE_NUM; i++)
		{
		if (get_rb_fire_flag(i))
			set_rb_fire_flag(i, FALSE); /* reset fired rules */
		if (get_rb_try_flag(i))
			set_rb_try_flag(i, FALSE);  /* reset tried rules */
		if (get_rb_live_flag(i))
			set_rb_live_flag(i, FALSE); /* reset live rule   */
		for (y = 0; y < MAX_COND; y++)
			{
			if (get_rb_condition_flag(i, y))
				set_rb_condition_flag(i, y, FALSE); /* reset tried conditions */
			}
		}

	for (i = 0; i < SIZE_OF_DB; i++)  /* delete fired consequences */
		if (!get_db_question_flag(i))
			reset_db_item(i);

	for (i = 0; i < MAX_QUESTIONS; i++) /* reset questions */
		if (get_qb_q_base_flag(i))
			set_qb_q_base_flag(i, FALSE);
}

/* Make question base, find all question identifiers and values and place */
/* into q_base */
/* All related functions in question.c */
void generate_q_base(char filename[])
{
	put_questions_into_q_base(); /* generate list of question identifiers quetion base */
	get_all_values();   /* place all values into question base */
	get_question_text(filename);  /* place question text into question base */
}

/* test to see if the given string is empty */
int its_empty(char string[])
{
	int c;

	if ((c = strlen(string)) == EMPTY)	/* it is assumed that if the first element is a */
		return TRUE;        /* null then the rest must be null */
	else		 /* a better way could be to use strlen ??? */
		return FALSE;
}
