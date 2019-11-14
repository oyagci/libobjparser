#include <obj.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include <errno.h>
#include <assert.h>

void ft_dlstpush(t_dlist **lstp, t_dlist *elem)
{
	t_dlist	*lst;
	t_dlist	*d;

	lst = *lstp;
	if (lst)
	{
		d = lst;
		while (d && d->next && d->next != lst)
			d = d->next;
		elem->next = lst;
		elem->prev = d;
		d->next = elem;
		lst->prev = elem;
	}
	else
	{
		*lstp = elem;
		elem->next = 0;
		elem->prev = 0;
	}
}

int	obj_load(t_obj *obj, char const *const filename)
{
	int			fd;
	struct stat	st;
	char		*content;

	memset(obj, 0, sizeof(*obj));

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		return (-1);
	}
	if (-1 == fstat(fd, &st)) {
		perror("fstat");
		close(fd);
		return (-1);
	}
	if (!obj) {
		perror("malloc");
		return (-1);
	}
	content = malloc(sizeof(*content) * (st.st_size + 1));
	if (!content) {
		perror("malloc");
		close(fd);
		free(obj);
		return (-1);
	}
	read(fd, content, st.st_size);
	content[st.st_size] = '\0';
	obj->data = content;
	close(fd);
	return (0);
}

enum e_obj_tok	obj_kind(char const *const stok)
{
	struct { char *str; enum e_obj_tok tok; } tokens[] = {
		{ "v", OBJ_VERTEX },
		{ "vt", OBJ_TEXTURE },
		{ "vn", OBJ_NORMAL },
		{ "f", OBJ_FACE },
	};
	size_t	i = 0;

	while (i < sizeof(tokens) / sizeof(*tokens)) {
		if (!strcmp(stok, tokens[i].str)) {
			return (tokens[i].tok);
		}
		i += 1;
	}
	return (OBJ_NONE);
}

int	obj_add_vertice(t_obj *obj, char const **v)
{
	char const *sx = v[0];
	char const *sy = v[1];
	char const *sz = v[2];
	char const *sw = v[3];

	if (sx == 0 || sy == 0 || sz == 0) {
		// Invalid token. Missing x y or z component
		return (-1);
	}

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	// Read values
	sscanf(sx, "%f", &x);
	sscanf(sy, "%f", &y);
	sscanf(sz, "%f", &z);
	if (sw != 0) { sscanf(sw, "%f", &w); }

	t_list		*elem = ft_lstnew(NULL, 0);
	t_vertex	*vert = malloc(sizeof(t_vertex));

	vert->x = x;
	vert->y = y;
	vert->z = z;
	vert->w = w;

	fprintf(stderr, "V { x: %.2f, y: %.2f, z: %.2f, w: %.2f }\n",
		x, y, z, w);

	elem->content = v;
	ft_lstpush(&obj->vertices, elem);

	return (0);
}

int	obj_add_face(t_obj *obj, const char **fs)
{
	t_face	*face;
	size_t	nverts;
	size_t	i;

	nverts = 0;
	while (fs[nverts] != 0) {
		nverts++;
	}

	face = malloc(sizeof(*face));
	face->indices = 0;

	i = 0;
	while (i < nverts) {
		t_dlist	*elem = ft_dlstnew(NULL, 0);
		t_face_indices *indices = malloc(sizeof(*indices));

		elem->content = indices;

		size_t j = 0;

		// TODO: Refactor the stuff bellow. It's obviously bad.
		//
		ft_dlstpush(&face->indices, elem);

		// Parse digit
		indices->vert = ft_atoi(fs[i]);

		// Go to next digit
		while (fs[i][j] != '\0' && fs[i][j] != '/')
			j += 1;
		if (fs[i][j] == '/') {
			j += 1;
		}
		else {
			i += 1;
			continue ;
		}

		// Parse digit
		indices->text = ft_atoi(fs[i]);

		// Go to next digit
		while (fs[i][j] != '\0' && fs[i][j] != '/')
			j += 1;
		if (fs[i][j] == '/') {
			j += 1;
		}
		else {
			i += 1;
			continue ;
		}

		// Parse digit
		indices->norm = ft_atoi(fs[i]);
		fprintf(stderr, "!\n");

		i += 1;
	}

	t_dlist *l = face->indices;
	if (l) {
		fprintf(stderr, "F {\n");
		do {
			t_face_indices *indices = l->content;

			fprintf(stderr, "  { vert: %ld, norm: %ld, text: %ld }\n",
				indices->vert, indices->norm, indices->text);
			l = l->next;
		} while (l != face->indices);
		fprintf(stderr, "}\n");
	}

	return (0);
}

int	obj_parse(t_obj *obj)
{
	size_t	j;
	char	**lines;
	char	**line;

	lines = ft_strsplit(obj->data, '\n');
	j = 0;
	while (lines[j] != 0) {
		line = ft_strsplit(lines[j], ' ');

		switch (obj_kind(line[0])) {
			case OBJ_VERTEX:
				obj_add_vertice(obj, (const char **)(line + 1));
				break ;
			case OBJ_FACE:
				obj_add_face(obj, (const char **)(line + 1));
				break ;
			default:
				break ;
		}
		j += 1;
	}
	return (0);
}

int	obj_triangulate(t_obj *obj)
{
	t_dlist *ears = NULL;
	return (0);
}
