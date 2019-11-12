#include <criterion/criterion.h>
#include "obj.h"

Test(obj_load, normal) {
	t_obj	o;

	cr_assert_eq(obj_load(&o, "./objects/42.obj"), 0);
}

Test(obj_load, file_missing) {
	t_obj	o;
	char	*missing_path = "does-not-exist.937130.c";

	cr_assert(obj_load(&o, missing_path) < 0);
}
