#include	<stdio.h>
#include	<stdlib.h>

#include	"pixel.h"
#include	"boxes.h"

void print_pixel(FILE *flux, void *pp) {
	struct pixel * ptmp;
	ptmp = (struct pixel *)pp;
	fprintf(flux, "Pixel (%d, %d)\n",(*ptmp).i, (*ptmp).j);
	return;
}

int main(int argc, char *argv[]) {
	int rc;
	struct box *pixelbox;
	struct pixel pix1, pix2;
	pix1.i = 1; pix1.j = 1;
	pix2.i = 2; pix2.j = 2;
	rc = EXIT_SUCCESS;

	/* Réserver mémoire pour pixelbox */
	pixelbox = (struct box *)box_init(sizeof(struct pixel), 2, &print_pixel);

	/* 
	** Les essais
	*/

	/* Afficher les informations de la boite */
	box_info(stdout, pixelbox);

	/* Afficher des pixels, directement, puis par le pointeur sur la fonction de la boite */
	//print_pixel(&pix1);
	//pixelbox->print(&pix2);

	/* Insérer un point dans la boite */
	box_put(pixelbox, &pix1);
	pix1.j = 3;

	/* Test plus long, tant que ça fonctionne */
	while( box_put(pixelbox, &pix1) == BOX_SUCCESS ) {
		pix1.j = rand();
	}

	printf("La boite contient %d elements\n", box_size(pixelbox));

	/* Afficher de nouveau les informations de la boite */
	box_info(stdout, pixelbox);

	/* Afficher le contenu de la boite */
	//box_display(stdout, pixelbox);

	goto FIN; /* to avoid a warning at compile time */

FIN:
	box_release(pixelbox);
	return rc;
}
/* EOF */
