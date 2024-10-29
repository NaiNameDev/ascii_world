#define air new_object(new_vec3(0,0,0), '#', DEF, DEF, -1, init_string(3, "air"))
#include "headers.c"


char asd[16] = ";;;;;,,,,,,,,,@$";

int main() {
	//crafts
	struct craftLevel hand_lvl = init_craft_level(0);
	
	struct craft wood_floor_c = init_craft(wood_floor, 0, hand_lvl);
	append_craft_element(&wood_floor_c, wood_log, 1);
	append_craft_level(wood_floor_c, &hand_lvl);

	struct craft door_c = init_craft(wood_door, 0, hand_lvl);
	append_craft_element(&door_c, wood_log, 4);
	append_craft_level(door_c, &hand_lvl);

	struct craft wood_c = init_craft(wood, 0, hand_lvl);
	append_craft_element(&wood_c, wood_log, 2);
	append_craft_level(wood_c, &hand_lvl);

	struct craft rock_wall_c = init_craft(rock_wall, 0, hand_lvl);
	append_craft_element(&rock_wall_c, rock, 3);
	append_craft_level(rock_wall_c, &hand_lvl);

	struct craft rock_floor_c = init_craft(rock_floor, 0, hand_lvl);
	append_craft_element(&rock_floor_c, rock, 2);
	append_craft_level(rock_floor_c, &hand_lvl);

	srand(time(NULL)); //for random O_o
	struct tileMap map = new_tile_map(3, 250, 250);
	
	struct object r = item_to_object(rock);
	struct object o = item_to_object(grass);
	for (int i = 0; i < 250; i++) {
		for (int j = 0; j < 250; j++) {
			if ( i * j > 48) {
				int a = rand() % 16;
				o.sym = asd[a];
				if (a == 1) {
					set_obj(new_vec3(i, j, 1), item_to_object(rock), &map.arr[0]);
				}
				if (a == 2) {
					set_obj(new_vec3(i, j, 1), item_to_object(wood_log), &map.arr[0]);
				}
				if (a == 3) {
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
			set_obj(new_vec3(i, j, 0), r, &map.arr[2]);
			set_obj(new_vec3(i, j, 0), r, &map.arr[1]);
		}
	}
	struct object* a = set_obj(new_vec3(240,240,7), new_object(new_vec3(3,3,3), 'A', GREEN, PURPLE_BG, 0, init_string(6, "player")), &map.arr[0]);

	struct entity ts = new_entity(a, &map.arr[0]);
	
	struct inventory inv = new_inventory(10);
	struct item asdd = wood_log;
	asdd.stack = 19;
	set_item(&inv, asdd, 0);
	
	//set_item(&inv, wood_door, 2);
	//set_item(&inv, wood_floor, 3);
	//set_item(&inv, rock_floor, 4);
	//set_item(&inv, rock_wall, 5);
	//set_item(&inv, wood, 6);
	
	int ch = 0;
	while (true) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("wasd - move, 1, 2 - change slot, e - place block, x - break block, c - break floor, z - break block on z - 1, ; - move down, ' - move up, q - QUIT\n");
		read_tile_map(&map, ts.self_map->index, plus_vec2(vec3_to_vec2(ts.self->position), new_vec2(-8,-8)), plus_vec2(vec3_to_vec2(ts.self->position), new_vec2(9,9)));
		print_vec3(ts.self->position);
		read_inventory(inv);
		scanf("%c", &ch);
		if (ch == ';') {
			if (ts.self_map->index + 1 <= 2) {
				move_entity_other_map(&ts, new_vec2(ts.self->position.x, ts.self->position.y), &map.arr[ts.self_map->index + 1]);
			}
		}
		if (ch == '\'') {
			if (ts.self_map->index - 1 >= 0) {
				move_entity_other_map(&ts, new_vec2(ts.self->position.x, ts.self->position.y), &map.arr[ts.self_map->index - 1]);
			}
		}

		if (ch == '1') {
			set_chosen_slot(inv.chosen_slot - 1, &inv);
		}
		if (ch == '2') {
			set_chosen_slot(inv.chosen_slot + 1, &inv);
		}
		if (ch == 'i') {
			int chi = 0;
			while(true) {
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				read_craft_level(hand_lvl);
				printf("chose craft (N)umber\n");
				printf("type eny symbol to exit\n");
				read_inventory(inv);
				if (scanf("%d", &chi) != 0) { }
				else { break; }
				craft_item(hand_lvl.belt[chi - 1], &inv);
			}
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
		if (ch == 'z') {
			if (ts.self_map->index + 1 != map.layer_count) {
				collect_block(new_vec2(ts.self->position.x, ts.self->position.y - 1), &inv, &map.arr[ts.self_map->index + 1]);
			}
		}
		if (ch == 'x') {
			collect_block(new_vec2(ts.self->position.x, ts.self->position.y - 1), &inv, ts.self_map);
		}
		if (ch == 'c') {
			collect_floor(new_vec2(ts.self->position.x, ts.self->position.y - 1), &inv, ts.self_map);
		}

		if (ch == 'q') { break; }
	}
	
	free_full_craft_level(&hand_lvl);
	free_inventory(&inv);
	free_tile_map_data(&map.arr[0].data);
	return 0;
}
