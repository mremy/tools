
/*
** Macros
*/
#define BOX_TYPE_LINEAR 1<<0
#define BOX_TYPE_LIST 1<<1

#define	BOX_SIZE_INITIAL	10240
#define	BOX_SIZE_INCREMENT	10240

#define	BOX_SUCCESS	0
#define	BOX_ERROR_REALLOC	1

/*
** Structures
*/
struct box {
	unsigned	int	index;
	unsigned	int	maxindex;
	unsigned	int	eltsize;
	unsigned	int	type;
	void	(*print)(void *);
	//struct pixel	*ptr;
	 void	*ptr;
};

/*
** Fonctions
*/
void	info_box(struct box *);
void	*init_box(unsigned int, unsigned int, void (*)());
void	*new_box(unsigned int, unsigned int, unsigned int, void (*)());
void	release_box(struct box *);
void	display_box(struct box *);
int	put_box(struct box *, void *);

/*
** EOF
*/
