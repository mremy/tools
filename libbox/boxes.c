/*
** Implémentation des fonctions
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>

#include	"boxes.h"

void *init_box(unsigned int myeltsize, unsigned int nombre_initial, void (*fct_print)(void *)) {
  new_box(myeltsize, nombre_initial, BOX_TYPE_LINEAR, fct_print);
}

void *new_box(unsigned int myeltsize, unsigned int nombre_initial, unsigned int box_type, void (*fct_print)(void *)) {
	struct box *pbox;
	if( (myeltsize <= 0) || (nombre_initial <= 0) ) {
		return NULL;
	}
	//if(nombre_initial < BOX_SIZE_INITIAL) {
		//nombre_initial = BOX_SIZE_INITIAL;
	//}
	if( (pbox = (struct box *)calloc(1, sizeof(struct box))) == NULL ) {
		fprintf(stderr, "[init_box] calloc box error\n");
		return NULL;
	}
	pbox->index = 0;
  pbox->type = box_type;
	pbox->maxindex = nombre_initial-1;
	pbox->eltsize = myeltsize;
	pbox->print = fct_print;
	if( (pbox->ptr = (void *)calloc(nombre_initial, myeltsize)) == NULL ) {
		fprintf(stderr, "[init_box] calloc box->ptr error\n");
		free(pbox);
		return NULL;
	}
	return pbox;
}

int	put_box(struct box *pbox, void * pdata) {
//*(pbox->ptr+pbox->index*pbox->eltsize) = *pdata;
	if(pbox->index == pbox->maxindex ) {
		void *ptmp;
		if( ( ptmp = realloc( pbox->ptr, pbox->eltsize*(pbox->maxindex+1+BOX_SIZE_INCREMENT)) ) == NULL ) {
			return BOX_ERROR_REALLOC;
		}
		pbox->ptr = ptmp;
		pbox->maxindex += BOX_SIZE_INCREMENT;
		fprintf(stderr, "Size: %8x\r", pbox->maxindex);
		//sleep(1);
	}
	memcpy(pbox->ptr+pbox->index*pbox->eltsize, pdata, pbox->eltsize);
	(pbox->index)++;
	return BOX_SUCCESS;
}

void	extend_box(struct box *pbox) {
	return;
}

void	release_box(struct box *pbox) {
	fprintf(stderr, "[free] pbox->ptr\n");
	free(pbox->ptr);
	fprintf(stderr, "[free] pbox\n");
	free(pbox);
	return;
}

void	info_box(struct box *pbox) {
	fprintf(stdout, "struct box %p\n", pbox);
	fprintf(stdout, "\tindex %d\n", pbox->index);
	fprintf(stdout, "\tmaxindex %d\n", pbox->maxindex);
	fprintf(stdout, "\teltsize %d\n", pbox->eltsize);
	fprintf(stdout, "\tprint %p\n", pbox->print);
	fprintf(stdout, "\tptr %p\n", pbox->ptr);
	return;
}

void display_box(struct box *pbox) {
	unsigned int i;
	while( i < pbox->index ) {
		pbox->print(pbox->ptr + i*pbox->eltsize);
		i++;
	}
return;
}

/* EOF */
