#include <stdio.h>

#include "utils/color.c"
#include "classes/vector.c"
#include "classes/object.c"
#include "classes/tilemap.c"

int main() {
	struct tileMapLayer tmp = new_tile_map_layer(new_tile_map_data('#'));
	struct object* a = set_obj(new_vec2(3,3), new_object(new_vec2(3,3), 'A', RED, RED_BG), &tmp);
	
	int ch = 0;
	while (1 < 2) {
		scanf("%d", &ch);
		if (ch == 1) {
			a = move_obj(new_vec2(a->position.x, a->position.y - 1), *a, &tmp);
		}
		if (ch == 2) {
			a = move_obj(new_vec2(a->position.x, a->position.y + 1), *a, &tmp);
		}
		if (ch == 3) {
			a = move_obj(new_vec2(a->position.x + 1, a->position.y), *a, &tmp);
		}
		if (ch == 4) {
			a = move_obj(new_vec2(a->position.x - 1, a->position.y), *a, &tmp);
		}
		if (ch == 0) { break; }
		read(tmp);
	}

	return 0;
}
