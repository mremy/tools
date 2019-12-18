/* # SOF */
/* sol.h */

#ifndef __SOL_H
#define __SOL_H

/*
#ifndef DEBUG
#define DEBUG 20
#endif
*/

#include <arpa/inet.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CLEAR 0
#define SET 1

#define BUFS 65536

#define HEADER 4
#define CHUNK_SIZE 4
#define MAX_CHUNK_TYPE 32

/* Return the CRC of the bytes buf[0..len-1]. */
unsigned long crc(unsigned char *, int );

/* Convert binary to printable data */
void data_to_string( unsigned char *, unsigned char *, size_t );

/* Chercher 4 caractères ASCII consécutifs */
int search_4_chars( unsigned char *, size_t, size_t * );

#endif
/* # EOF */
