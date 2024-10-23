#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils/color.c"
#include "utils/string.c"
#include "classes/vector.c"
#include "classes/object.c"
#include "classes/tilemap.c"
#include "classes/inventory.c"
#include "classes/entity.c"

#define air_obj new_object(new_vec3(0,0,0), '.', CYAN, DEF, 0, 0)

int main() {
	struct tileMapLayer tmp = new_tile_map_layer(
		new_tile_map_data(air_obj, 16, 16, 8));
	struct object* a = set_obj(new_vec3(3,3,1), new_object(new_vec3(3,3,3), 'A', RED, RED_BG, 0, 1), &tmp);
	struct object* it1 = set_obj(new_vec3(0,0,1), new_object(new_vec3(2,2,2), '#', RED, DEF, 0, 1), &tmp);
	struct object* it2 = set_obj(new_vec3(1,1,1), new_object(new_vec3(2,2,2), '@', CYAN, DEF, 0, 1), &tmp);

	struct entity ts = new_entity(init_string(3, "player"), a, &tmp);
	
	struct inventory inv = new_inventory(10);
	set_item(&inv, object_to_item(*it1, init_string(4, "itm1"), 1), 0);
	set_item(&inv, object_to_item(*it2, init_string(6, "lol xd"), 1), 1);

	int ch = 0;
	while (1) {
		read_map(tmp);
		read_inventory(inv);
		printf("%s\n", inv.arr[inv.chosen_slot].name.arr);
		scanf("%c", &ch);
		if (ch == '1') {
			inv.chosen_slot -= 1;
		}
		if (ch == '2') {
			inv.chosen_slot += 1;
		}
		if (ch == 'a') {
			move_entity(&ts, new_vec2(ts.self->position.x, ts.self->position.y - 1));
		}
		if (ch == 'd') {
			move_entity(&ts, new_vec2(ts.self->position.x, ts.self->position.y + 1));
		}
		if (ch == 's') {
			move_entity(&ts, new_vec2(ts.self->position.x + 1, ts.self->position.y));
		}
		if (ch == 'w') {
			move_entity(&ts, new_vec2(ts.self->position.x - 1, ts.self->position.y));
		}
		if (ch == 'e') {
			place_item(&inv.arr[inv.chosen_slot], &tmp, new_vec2(ts.self->position.x - 1, ts.self->position.y));
		}
		if (ch == 'x') {
			set_free_obj(new_vec2(ts.self->position.x - 1, ts.self->position.y), air_obj, &tmp);
		}
		if (ch == 'q') { break; }
	}
	
	free_tile_map_data(&tmp.data);
	return 0;
}
