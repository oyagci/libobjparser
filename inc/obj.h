#ifndef OBJ_H
# define OBJ_H

# include <string.h>
# include "libft.h"

enum			e_obj_tok
{
	OBJ_NONE = 0,
	OBJ_VERTEX,
	OBJ_TEXTURE,
	OBJ_NORMAL,
	OBJ_FACE,
};

typedef struct	s_obj
{
	char			*data;
	struct s_list	*vertices;
	struct s_list	*faces;
}				t_obj;

typedef struct	s_vertex {
	float	x;
	float	y;
	float	z;
	float	w;
}				t_vertex;

typedef struct	s_face_indices {
	size_t	vert;
	size_t	text;
	size_t	norm;
}				t_face_indices;

typedef struct	s_face {
	t_dlist *indices;
}				t_face;

int		obj_load(t_obj *obj, char const *const filename);
int		obj_parse(t_obj *obj);

#endif
