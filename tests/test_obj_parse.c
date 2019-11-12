#include <criterion/criterion.h>
#include "obj.h"

Test(obj_parse, parse_42) {
	t_obj o;

	cr_assert(0 == obj_load(&o, "objects/42.obj"), "Could not load object");
	cr_assert(obj_parse(&o) == 0);
}
