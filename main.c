#define air new_object(new_vec3(0,0,0), '.', DEF, DEF, 0, init_string(3, "air"))
#include "headers.c"



int main() {
	srand(time(NULL)); //for random O_o
	struct tileMap map = new_tile_map(3);

	struct object o = item_to_object(grass);
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 24; j++) {
			if ( i * j > 48) {
				int a = rand() % 20;
				if (a == 19) {
					set_obj(new_vec3(i, j, 1), item_to_object(rock), &map.arr[0]);
				}
				if (a == 18) {
					set_obj(new_vec3(i, j, 1), item_to_object(wood_log), &map.arr[0]);
				}
				if (a == 17) {
					set_obj(new_vec3(i, j, 1), item_to_object(bery), &map.arr[0]);
				}
				set_obj(new_vec3(i, j, 0), o, &map.arr[0]);
			}
			else if (i * j < 24) {
				set_obj(new_vec3(i, j, 0), item_to_object(water), &map.arr[0]);
			}
			else {
				set_obj(new_vec3(i, j, 0), item_to_object(sand), &map.arr[0]);
			}
		}
	}
	struct object* a = set_obj(new_vec3(6,6,7), new_object(new_vec3(3,3,3), 'A', GREEN, PURPLE_BG, 0, init_string(6, "player")), &map.arr[0]);

	struct entity ts = new_entity(a, &map.arr[0]);
	
	struct inventory inv = new_inventory(10);
	set_item(&inv, wood_log, 1);
	set_item(&inv, wood_door, 2);
	set_item(&inv, wood_floor, 3);
	set_item(&inv, rock_floor, 4);
	set_item(&inv, rock_wall, 5);
	set_item(&inv, wood, 6);
	
	int ch = 0;
	while (true) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		read_map(ts.self_map);
		read_inventory(inv);
		scanf("%c", &ch);
		if (ch == '+') {
			if (&map.arr[ts.self_map->index + 1] >= 0) {
				move_entity_other_map(&ts, new_vec2(ts.self->position.x, ts.self->position.y), &map.arr[ts.self_map->index + 1]);
			}
		}
		if (ch == '-') {
			if (&map.arr[ts.self_map->index - 1] >= 0) {
				move_entity_other_map(&ts, new_vec2(ts.self->position.x, ts.self->position.y), &map.arr[ts.self_map->index - 1]);
			}
		}
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
			place_item(&inv.arr[inv.chosen_slot], ts.self_map, get_free_space(new_vec2(ts.self->position.x, ts.self->position.y - 1), &map.arr[0])->position, inv.chosen_slot);
		}
		if (ch == 'x') {
			collect_block(new_vec2(ts.self->position.x, ts.self->position.y - 1), &inv, ts.self_map);
		}
		if (ch == 'q') { break; }
	}
	
	free_inventory(&inv);
	free_tile_map_data(&map.arr[0].data);
	return 0;
}
