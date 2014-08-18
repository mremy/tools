#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
	long int strtol(const char *nptr, char **endptr, int base);
	char *strncpy(char *dest, const char *src, size_t n);
	 *getenv(const char *name);

RETURN VALUE
       The  strtol()  function  returns  the result of the conversion, unless the value would underflow or overflow.  If an
       underflow occurs, strtol() returns LONG_MIN.  If an overflow occurs, strtol()  returns  LONG_MAX.   In  both  cases,
       errno  is  set  to ERANGE.  Precisely the same holds for strtoll() (with LLONG_MIN and LLONG_MAX instead of LONG_MIN
       and LONG_MAX).

       The getenv() function returns a pointer to the value in the environment, or NULL if there is no match.

*/

#define	MAX_NUM	5

int main( int argc, char *argv[], char* argenv[] ) {

  char num[MAX_NUM];
	long index;
  long nbr=1;

	/* prepare destination string, to ensure correct end of C string */
	for( index=0; index<MAX_NUM; index++) {
		num[index] = '\0';
	}

  /* Get from command line, if given */
  if( argc == 2 ) {
#if DEBUG > 1
		(void)fprintf( stderr, "Process argv\n");
#endif
		/* Copy/truncate the input string */
	  strncpy( num, argv[1], MAX_NUM-1);
  }

  /* Get from environment, if defined  has priority */
  if( getenv( "NOPNUM" ) != NULL && strlen( getenv( "NOPNUM" ) ) < MAX_NUM ) {
#if DEBUG > 1
		(void)fprintf( stderr, "Process argenv\n");
#endif
    strncpy( num, getenv( "NOPNUM" ), MAX_NUM-1 );
  }

  if( strlen(num) > 0 ) {
#if DEBUG > 1
		(void)fprintf( stderr, "Convert num %ld\n", strlen(num) );
#endif
		/* Convert to a long */
		long result;
		/* Clear errno */
		errno = 0;
		result = strtol( num, NULL, 10 );
		if( ! errno ) {
			nbr = result;
		}

	} /* END if strlen */

#if DEBUG > 1
	(void)fprintf( stderr, "nbr:%ld\n", nbr );
#endif

	for( index=0; index<nbr; index++ ) {
		(void)fprintf( stdout, "%c", '\x90' );
	}

	return 0;
}
