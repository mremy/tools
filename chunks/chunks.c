/* # SOF */
/* file: chunks.c */

#include "chunks.h"

#define DEBUG 30

char printable( char c ) {
	if( isprint(c) ) { return c; }
	else { return '.'; }
}

int search_4_chars( char * strsrc, size_t strlength, size_t * found ) {
	size_t index;
	int rc;
	index = 4;
	rc = -1;
	*found = 0;
	#if DEBUG>10
	fprintf( stderr, " Search start at %p with length %zu\n", strsrc, strlength );
	#endif
	while( (index+4<strlength) && (rc<0) ) {
		if( isalpha(strsrc[index]) && \
		(isalpha(strsrc[index+1])) && \
		(isalpha(strsrc[index+2])) && \
		(isalpha(strsrc[index+3])) ) {
			rc = 0;
			*found = index - 4 ;
			#if DEBUG>10
			fprintf( stderr, " >%c%c%c%c<\n", strsrc[index],strsrc[index+1],strsrc[index+2],strsrc[index+3] );
			#endif
		} /* if */
		index += 1;
		#if DEBUG>10
		fprintf( stderr, "index: %zu %c\n", index, printable(strsrc[index]) );
		#endif

	} /* while */
	#if DEBUG>10
	fprintf( stderr, " found at index: %zu\n", *found );
	#endif
	return rc;
}

int get_chunk_tab_num( char * name, const char ** tab, uint32_t * num ) {
	int rc;
	rc = 1;
	for( size_t idx=0; idx<MAX_CHUNK_TYPE; idx++ ) {
		#if DEBUG>10
		fprintf( stderr, "  get_chunk_tab_num: idx %zu\n", idx );
		#endif
		if( strcmp( name, tab[idx] )==0 ) {
			*num = idx;
			rc = 0;
			break;
		} /* if */
	} /* for */
	return rc;
}

int main( int argc, char ** argv, char ** argenv ) {

    /* standart descriptors */
    FILE * OUT;
    FILE * ERR;
    OUT = stdout;
	ERR = stderr;

	/* manage options with getopt */
	char * file_name = NULL;
	int c;

	opterr = 0;
	while((c=getopt(argc, argv, "f:")) != -1 ) {
		switch(c) {
			case 'f':
				file_name = optarg;
				break;
		} /* switch */
	} /* while */

	/* Check if a filename is provided */
	if( file_name == NULL ) {
		fprintf( ERR, "Missing file name\n" );
		return EXIT_FAILURE;
	}

	fprintf( ERR, "File name: %s\n", file_name );

	/* chunks */
	char chunk_file_name[1024];
	const char *chunk_name[MAX_CHUNK_TYPE];
	chunk_name[__COUNTER__] = "NULL";
	chunk_name[__COUNTER__] = "IHDR";
	chunk_name[__COUNTER__] = "PLTE";
	chunk_name[__COUNTER__] = "IDAT";
	chunk_name[__COUNTER__] = "IEND";
	chunk_name[__COUNTER__] = "sRGB";
	chunk_name[__COUNTER__] = "gAMA";
	chunk_name[__COUNTER__] = "pHYs";
	chunk_name[__COUNTER__] = "tEXt";

	uint32_t chunk_nbr[MAX_CHUNK_TYPE];

	/* */
	char data[BUFS];
	char chunk_found[5];
	chunk_found[4] = '\0';
	size_t remaining_bytes;
	size_t chunk_index;
	size_t current_index;
	//void * chunk_start;
	uint32_t chunk_size;
	uint32_t chunk_tab_num;
	//uint32_t chunk_crc;
	int rc1;

    /* read file */
    FILE * fh;

	/* Initialisation */
	for( size_t index=0; index<MAX_CHUNK_TYPE; index++ ) {
		chunk_nbr[index] = 0;
	}
	current_index = 0;

    fh = fopen( file_name, "rb");
    if( ! fh ) {
        fprintf( ERR, "Unable to open file %s !\n", file_name );
        return EXIT_FAILURE;
    }

	/* Read the file */
	/* FIXME: doesn't work if a chunk is cross read */
	/* a la recherche de chunk potentiel, ie 4 lettres de suite */
    while( feof(fh)==0 ) {
        remaining_bytes = fread( data, 1, BUFS*sizeof(uint8_t), fh);
		#if DEBUG>20
		fprintf( ERR, "Bytes read: %zu\n", remaining_bytes );
		#endif
		while( remaining_bytes >=12 ) {
			chunk_found[0] = '.';
			chunk_found[1] = '.';
			chunk_found[2] = '.';
			chunk_found[3] = '.';
			chunk_found[4] = '\0';
			chunk_size = 0;
			/* Search for chunk */
			#if DEBUG>10
			fprintf( ERR, "  Call chunk_index with: %p , %lu\n", data+current_index, remaining_bytes );
			#endif
			rc1 = search_4_chars( data+current_index, remaining_bytes, &chunk_index );
			#if DEBUG>10
			fprintf( ERR, "  Return chunk_index : %lu\n", chunk_index );
			#endif
			if( rc1==0 ) {
				/* get chunk size */
				chunk_size = htonl( (uint32_t)*(uint32_t *)(data+current_index+chunk_index) );
				#if DEBUG>10
				fprintf( ERR, "Chunk_size %d\n", chunk_size);
				#endif
				/* get chunk name */
				chunk_found[0] = data[current_index+chunk_index+4];
				chunk_found[1] = data[current_index+chunk_index+5];
				chunk_found[2] = data[current_index+chunk_index+6];
				chunk_found[3] = data[current_index+chunk_index+7];
				/* get chunk data, if any */
				/* get crc */
				fprintf( OUT, "Chunk %s of size %x (%d) found at index %zu\n", \
					chunk_found, \
					chunk_size, \
					chunk_size, \
					chunk_index );
				current_index = current_index + chunk_index + chunk_size + 12;
				remaining_bytes = remaining_bytes - 12 - chunk_size - chunk_index;
				#if DEBUG>10
				fprintf( ERR, " current_index %zu  chunk found %s\n", current_index, chunk_found );
				#endif
				/* get index */
				chunk_tab_num = 0;
				get_chunk_tab_num( chunk_found, chunk_name, &chunk_tab_num );
				//sprintf( chunk_file_name, "%s_chunk_%s_%d.bin", file_name, chunk_found, chunk_nbr[chunk_tab_num] );
			} /* if chunk found */
			else {
				remaining_bytes=-1;
			}
		} /* while remaining_bytes */
    } /* while */

    fclose(fh);

    return EXIT_SUCCESS;
}

/* IEND crc ae 42  60 82 */

/* # vim : filetype=c ts=4 : */
/* # EOF */
