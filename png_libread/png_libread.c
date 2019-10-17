/*
** png_libread - read a png file using libpng
*/

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <png.h>

#define PNG_BYTES_TO_CHECK 8
#define PNG_CHUNK_NAME_SIZE 4
#define NOT_PNG 0
#define ERROR 1

/*
** declarations
*/
static png_uint_32 user_chunk_data[4];

int our_unknown_chunk_handler( png_structp, png_unknown_chunkp );
int fprintc( FILE *, unsigned int );

/*
** functions
*/
int fprintc( FILE * out, unsigned int showchar ) {

  int rc;

  if( isalpha( showchar ) || isdigit( showchar ) ) {
    rc=fputc( showchar, out );
  } else {
    rc=fputc( '.', out );
  }
  return rc;

}

int our_unknown_chunk_handler( png_structp our_png_ptr, png_unknown_chunkp our_png_chunk_ptr ) {

  int i, rc;
  png_uint_32 *our_user_chunk_data_ptr;
  png_infop our_info_unknown_ptr;

  /*
  ** initialize
  */
  rc=1;

  (void)fprintf( stderr, "unknown chunk: %4s size: %d data:\n", our_png_chunk_ptr->name, our_png_chunk_ptr->size );
  for( i=0; i <  our_png_chunk_ptr->size ; i++ ) {
    fprintc( stderr, our_png_chunk_ptr->data[ i ] );
  }
  (void)fputc( '\n', stderr );
  /*
  **  < 0 error
  ** == 0 function not recognize header
  **  > 0 success
  */
  return rc;

}

int read_png_fd( FILE *fin, unsigned int sig_read ) {

  png_structp png_ptr;
  png_infop png_info_ptr;
  png_infop end_info_ptr;
  png_voidp user_chunk_ptr;

  user_chunk_ptr = (png_voidp)user_chunk_data;

  /*
  png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, (png_voidp)user_error_ptr,
   user_error_fn, user_warning_fn);
  */
  png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, (png_voidp)NULL,
   NULL, NULL);
  if( !png_ptr ) {
    return ERROR;
  }

  png_info_ptr = png_create_info_struct( png_ptr );
  if( !png_info_ptr ) {
    /*
    ** free already allocated structure
    */
    png_destroy_read_struct( &png_ptr, (png_infopp)NULL, (png_infopp)NULL );
    return ERROR;
  }

  end_info_ptr = png_create_info_struct( png_ptr );
  if( !end_info_ptr ) {
    /*
    ** free already allocated structure
    */
    png_destroy_read_struct( &png_ptr, &png_info_ptr, (png_infopp)NULL );
    return ERROR;
  }

  /*
  ** initialize our png structure
  */
  png_init_io( png_ptr, fin );

  /*
  ** skip the already checked png magic number
  */
  png_set_sig_bytes( png_ptr, PNG_BYTES_TO_CHECK );

  /*
  ** setup an unknown chunk handler
  */
  user_chunk_data[0] = 0;
  user_chunk_data[1] = 0;
  user_chunk_data[2] = 0;
  user_chunk_data[3] = 0;
  png_set_read_user_chunk_fn( png_ptr, user_chunk_ptr, our_unknown_chunk_handler );

  /*
  ** keep all unknown chunks
  */
  png_set_keep_unknown_chunks( png_ptr, PNG_HANDLE_CHUNK_ALWAYS, NULL, 0 );

  /*
  ** read the png file
  */
  png_read_png( png_ptr, png_info_ptr, 0, NULL );

  /*
  ** definition de la structure png_struct_def
  ** /usr/include/png.h ligne 1236
  ** avec: typedef struct png_struct_def png_struct
  */
  (void) fprintf( stderr, "img size: %d x %d \n", png_ptr->width, png_ptr->height );
  /*
  ** close, free and return
  */
  png_destroy_read_struct( &png_ptr, &png_info_ptr, &end_info_ptr );
  return 0;

}

/*
** main
*/
int main( void ) {

  int rc;
  FILE * fin;
  FILE * fout;
  char * fname;
  uint32_t * chunk_type;
  uint32_t * chunk_len;

  /*
  ** initialize
  */
  rc = 0;
  fname = "test.png";
  chunk_len = (uint32_t *)malloc( sizeof( uint32_t ) );
  if( chunk_len == NULL ) {
    exit( EXIT_FAILURE );
  } else {
    *chunk_len = 0;
  }

  chunk_type = (uint32_t *)malloc( sizeof( uint32_t ) );
  if( chunk_type == NULL ) {
    free( chunk_len );
    exit( EXIT_FAILURE );
  } else {
    *chunk_type = 0;
  }

  fin = fopen( fname, "rb" );
  if( fin == NULL ) {
    (void)fprintf( stderr, "ERR: fopen %s %d\n", fname, errno );
    exit( EXIT_FAILURE );
  }

  char buf[ PNG_BYTES_TO_CHECK ];
  if( fread( buf, 1, PNG_BYTES_TO_CHECK, fin ) != PNG_BYTES_TO_CHECK ) {
    fclose( fin );
    exit( EXIT_FAILURE );
  }

  uint32_t is_png;
  is_png = !png_sig_cmp( buf, 0, PNG_BYTES_TO_CHECK );
  if (!is_png) {
    return( NOT_PNG );
  }
  /*
  ** As we already checked the file header, we have to tell it to libpng
  ** with: png_set_sig_bytes( PNG_BYTES_TO_CHECK );
  ** after initializing the struture.
  */

  rc = read_png_fd( fin, PNG_BYTES_TO_CHECK );
  (void)fprintf( stderr, "read_png_fd: %d\n", rc );

END:
  free( chunk_len );
  free( chunk_type );
  fclose( fin );
  return rc;

}
/* EOF */
