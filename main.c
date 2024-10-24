#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define air new_object(new_vec3(0,0,0), '.', DEF, DEF, 0, init_string(3, "air"))
#define water new_object(new_vec3(0,0,0), '~', CYAN, CYAN, 0, init_string(5, "water"))
#define grass new_object(new_vec3(0,0,0), '@', GREEN, GREEN, 0, init_string(5, "grass"))
#define wood new_object(new_vec3(0,0,0), 'O', YELLOW, YELLOW, 1, init_string(4, "wood"))
#define rock new_object(new_vec3(0,0,0), 'r', DEF, DEF, 1, init_string(4, "rock"))
#define wood_door new_object(new_vec3(0,0,0), 'D', YELLOW_BG, DEF, 0, init_string(4, "door"))

char grass_syms[] = ";,@,,,,,,,,,,][}{\"%";
char air_sym = '.';

#include "utils/color.c"
#include "utils/string.c"
#include "classes/vector.c"
#include "classes/object.c"
#include "classes/tilemap.c"
#include "classes/inventory.c"
#include "classes/entity.c"

int main() {
	srand(time(NULL)); //for random O_o

	struct tileMapLayer tmp = new_tile_map_layer(
		new_tile_map_data(air, 24, 24, 8));
	
	struct object o = grass;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 24; j++) {
			if ( i * j > 24) {
				o.sym = grass_syms[rand() % 19];
				set_obj(new_vec3(i, j, 0), o, &tmp);
			}
			else {
				set_obj(new_vec3(i, j, 0), water, &tmp);
			}
		}
	}

	struct object* a = set_obj(new_vec3(6,6,7), new_object(new_vec3(3,3,3), 'A', RED, RED, 0, init_string(6, "player")), &tmp);
	
	print_vec3(get_free_space(new_vec2(3,5), &tmp)->position);

	struct entity ts = new_entity(a, &tmp);
	
	struct inventory inv = new_inventory(10);
	set_item(&inv, object_to_item(wood, 45), 1);
	set_item(&inv, object_to_item(wood_door, 5), 2);
	set_item(&inv, object_to_item(grass, 2), 0);
	
	int ch = 0;
	while (1) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		read_map(&tmp);
		read_inventory(inv);
		scanf("%c", &ch);
		if (ch == '1') {
			set_chosen_slot(inv.chosen_slot - 1, &inv);
		}
		if (ch == '2') {
			set_chosen_slot(inv.chosen_slot + 1, &inv);
		}
		if (ch == 'a') {
			move_entity(&ts, new_vec2(ts.self->position.x - 1, ts.self->position.y));
		}
		if (ch == 'd') {
			move_entity(&ts, new_vec2(ts.self->position.x + 1, ts.self->position.y));
		}
		if (ch == 's') {
			move_entity(&ts, new_vec2(ts.self->position.x, ts.self->position.y + 1));
		}
		if (ch == 'w') {
			move_entity(&ts, new_vec2(ts.self->position.x, ts.self->position.y - 1));
		}
		if (ch == 'e') {
			place_item(&inv.arr[inv.chosen_slot], &tmp, get_free_space(new_vec2(ts.self->position.x, ts.self->position.y - 1), &tmp)->position, inv.chosen_slot);
		}
		if (ch == 'x') {
			set_free_obj(get_last_object(new_vec2(ts.self->position.x, ts.self->position.y - 1), &tmp)->position, air, &tmp);
		}
		if (ch == 'q') { break; }
	}
	
	free_inventory(&inv);
	free_tile_map_data(&tmp.data);
	return 0;
}
