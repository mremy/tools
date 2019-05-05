/*
** main.c main function
*/

#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_VERSION const char *argp_program_version = "rev 0.1";
#define PROGRAM_BUG_ADDRESS const char *argp_program_bug_address = "https://github.com/mremy/rev";
#define PROGRAM_DOC static char doc[] = "rev -- reverse a bits stream";

#define FERR(...) (void)fprintf( stderr, ##__VA_ARGS__ );

#define EXIT_FAILURE 1

PROGRAM_DOC

/*
** arguments parsing
*/

/* A description of the arguments we accept. */
static char args_doc[] = "";

/* The options we understand. */
static struct argp_option options[] = {
  {"verbose",    'v', 0,         0, "Produce verbose output" },
  {"quiet",      'q', 0,         0, "Don't produce any output" },
  {"silent",     's', 0,         OPTION_ALIAS },
  {"input",      'i', "SRC",     0, "Input from FILE instead of standard input" },
  {"output",     'o', "FILE",    0, "Output to FILE instead of standard output" },
  {"wordsize",   'w', "INTEGER", 0, "INTEGER size of the word to handle" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments {
  int quiet, verbose, wordsize;
  char * output;
  char * input;
};

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */

  struct arguments *arguments = state->input;
  unsigned int uitmp;

  switch (key) {
    case 'q': case 's':
      arguments->quiet = 1;
      break;
    case 'v':
      arguments->verbose = 1;
      break;
    case 'o':
      arguments->output = arg;
      break;
    case 'i':
      arguments->input = arg;
      break;
    case 'w':
      arguments->wordsize = atoi( arg );
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main( int argc, char *argv[] ) {

  int rc;
  error_t  rc1;
  FILE * fin, * fout;

  struct arguments arguments;
  /*
  ** Default values
  */
  arguments.quiet   = 0;
  arguments.verbose = 0;
  arguments.wordsize= 0;
  arguments.output  = "-";
  arguments.input   = "-";

  rc = 0;
  rc1 = argp_parse( &argp, argc, argv, 0, 0, &arguments );

  if( strncmp( arguments.input, "-", 1 ) == 0 ) {
    fin = stdin;
  } else {
    fin = fopen( arguments.input, "r" );
    if( fin == NULL ) {
      FERR( "ERR: fopen %s %d\n", arguments.input, errno );
      exit( EXIT_FAILURE );
    }
  }

  if( strncmp( arguments.output, "-", 1 ) == 0 ) {
    fout = stdout;
  } else {
    fout = fopen( arguments.output, "r" );
    if( fout == NULL ) {
      FERR( "ERR: fopen %s %d\n", arguments.output, errno );
      exit( EXIT_FAILURE );
    }
  }

  FERR( "%s\n%s\n%d\n", arguments.input, arguments.output, arguments.wordsize );

  fclose( fin );
  fclose( fout );
  return( rc );
}

/* EOF */
