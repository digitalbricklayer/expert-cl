
/* ERROR.C *******************************************************************

			  Error handling routines

			   Written by Jack Hughes

			   Completed 17 - 6 - 90

******************************************************************************/

#include "expert.h"

#define NUM_ERRORS  9
#define NUM_MISS_DEMEANORS  2

/* array containing all misdemeanor errors, will be used with the rule parser */
static char miss_demeanors[NUM_MISS_DEMEANORS][LINE] =
{
	"",
	"",
};

/* take the error number and print out relevant message and exit */
void handle_error(int error_num)
{
    /* array containing all fatal error messages */
    static char fatal_errors[NUM_ERRORS][LINE] =
	{
	    "FATAL ERROR : File not found",
	    "FATAL ERROR : No file specified on command line",
	    "FATAL ERROR : No more space on rule base",
	    "FATAL ERROR : Too many conditions",
	    "FATAL ERROR : Too many consequences",
	    "FATAL ERROR : No more space on data base",
	    "FATAL ERROR : No more space on question base",
	    "FATAL ERROR : No more space on agenda",
	    "FATAL ERROR : Bad token"
	};

    switch(error_num)
	{
	case FILE_NOT_FOUND:
	    printf("%s\n", fatal_errors[FILE_NOT_FOUND]);
	    exit(-1);
	    break;
	case NO_FILE_SPECIFIED_ON_C_L:
	    printf("%s\n", fatal_errors[NO_FILE_SPECIFIED_ON_C_L]);
	    exit(-1);
	    break;
	case TOO_MANY_RULES:
	    printf("%s\n", fatal_errors[TOO_MANY_RULES]);
	    exit(-1);
	    break;
	case TOO_MANY_CONDITIONS:
	    printf("%s\n", fatal_errors[TOO_MANY_CONDITIONS]);
	    exit(-1);
	    break;
	case TOO_MANY_CONSEQUENCES:
	    printf("%s\n", fatal_errors[TOO_MANY_CONSEQUENCES]);
	    exit(-1);
	    break;
	case NO_SPACE_ON_D_B:
	    printf("%s\n", fatal_errors[NO_SPACE_ON_D_B]);
	    exit(-1);
	    break;
	case NO_SPACE_ON_Q_B:
	    printf("%s\n", fatal_errors[NO_SPACE_ON_Q_B]);
	    exit(-1);
	    break;
	case NO_MORE_STACK_SPACE:
	    printf("%s\n", fatal_errors[NO_MORE_STACK_SPACE]);
	    exit(-1);
	    break;
	}
}
