#define air new_object(new_vec3(0,0,0), '.', DEF, DEF, 0, init_string(3, "air"))
#include "headers.c"



int main() {
	srand(time(NULL)); //for random O_o

	struct tileMapLayer tmp = new_tile_map_layer(
		new_tile_map_data(air, 24, 24, 8));
	
	struct object o = item_to_object(grass);
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 24; j++) {
			if ( i * j > 48) {
				int a = rand() % 20;
				if (a == 19) {
					set_obj(new_vec3(i, j, 1), item_to_object(rock), &tmp);
				}
				if (a == 18) {
					set_obj(new_vec3(i, j, 1), item_to_object(wood_log), &tmp);
				}
				if (a == 17) {
					set_obj(new_vec3(i, j, 1), item_to_object(bery), &tmp);
				}
				set_obj(new_vec3(i, j, 0), o, &tmp);
			}
			else if (i * j < 24) {
				set_obj(new_vec3(i, j, 0), item_to_object(water), &tmp);
			}
			else {
				set_obj(new_vec3(i, j, 0), item_to_object(sand), &tmp);
			}
		}
	}
	struct object* a = set_obj(new_vec3(6,6,7), new_object(new_vec3(3,3,3), 'A', GREEN, PURPLE_BG, 0, init_string(6, "player")), &tmp);

	struct entity ts = new_entity(a, &tmp);
	
	struct inventory inv = new_inventory(10);
	set_item(&inv, wood_log, 1);
	set_item(&inv, wood_door, 2);
	set_item(&inv, wood_floor, 3);
	set_item(&inv, rock_floor, 4);
	set_item(&inv, rock_wall, 5);
	set_item(&inv, wood, 6);
	
	int ch = 0;
	while (true) {
		//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
			collect_block(new_vec2(ts.self->position.x, ts.self->position.y - 1), &inv, &tmp);
		}
		if (ch == 'q') { break; }
	}
	
	free_inventory(&inv);
	free_tile_map_data(&tmp.data);
	return 0;
}
