/* # SOF */
/* file: data_to_string.c */

void data_to_string(char *dst,  char *data, size_t length ) {
	size_t index;
	for( index=0; index < length; index++ ) {
		if( isprint(data[index]) ) sprintf( dst+index, "%c",data[index]);
		else sprintf( dst+index, ".");
	}
	sprintf( dst+index, "%c", '\0' );
	return;
}

/* # vim : filetype=c ts=4 : */
/* # EOF */
