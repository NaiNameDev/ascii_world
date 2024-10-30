#define air new_object(new_vec3(0,0,0), '#', DEF, DEF, -1, init_string(3, "air"))
#include "headers.c"

#define up new_vec2(0, 1)
#define right new_vec2(1, 0)

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

	struct craft workbanch_c = init_craft(workbanch, 0, hand_lvl);
	append_craft_element(&workbanch_c, wood_log, 10);
	append_craft_level(workbanch_c, &hand_lvl);

	struct craft wood_c = init_craft(wood, 0, hand_lvl);
	append_craft_element(&wood_c, wood_log, 2);
	append_craft_level(wood_c, &hand_lvl);

	struct craft rock_wall_c = init_craft(rock_wall, 0, hand_lvl);
	append_craft_element(&rock_wall_c, rock, 3);
	append_craft_level(rock_wall_c, &hand_lvl);

	struct craft rock_floor_c = init_craft(rock_floor, 0, hand_lvl);
	append_craft_element(&rock_floor_c, rock, 2);
	append_craft_level(rock_floor_c, &hand_lvl);



	//wrokbanch crafts
	struct craftLevel workbanch_lvl = init_craft_level(0);

	struct craft glass_c = init_craft(glass, 0, workbanch_lvl);
	append_craft_element(&glass_c, rock, 2);
	append_craft_level(glass_c, &workbanch_lvl);

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
	struct vec2 dir = up;

	int ch = 0;
	while (true) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("wasd - move, (1, 2) - change slot, e - place block, x - break block, c - break floor, z - break block on z - 1, ; - move down, ' - move up, f - change direction, i - inventory mod, Q - QUIT\n");
		read_tile_map(&map, ts.self_map->index, plus_vec2(vec3_to_vec2(ts.self->position), new_vec2(-8,-8)), plus_vec2(vec3_to_vec2(ts.self->position), new_vec2(9,9)));
		if (vec2_equal(up, dir) == true) {
			printf("\\/\n");
		}
		else if (vec2_equal(right, dir) == true) {
			printf(">\n");
		}
		else if (dir.x == -up.x && dir.y == -up.y) {
			printf("/\\\n");
		}
		else if (dir.x == -right.x && dir.y == -right.y) {
			printf("<\n");
		}
		print_vec3(ts.self->position);
		read_inventory(inv);
		scanf("%c", &ch);
		if (ch == 'f') {
			if (vec2_equal(up, dir) == true) {
				dir = right;
			}
			else if (vec2_equal(right, dir) == true) {
				dir.x = -up.x;
				dir.y = -up.y;
			}
			else if (dir.x == -up.x && dir.y == -up.y) {
				dir.x = -right.x;
				dir.y = -right.y;
			}
			else if (dir.x == -right.x && dir.y == -right.y) {
				dir = up;
			}
		}
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
			struct String toeq = init_string(9, "workbanch");
			if (check_strings_equal(get_last_object(plus_vec2(new_vec2(ts.self->position.x, ts.self->position.y), dir), ts.self_map)->name, toeq) == false) {
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
			else {
				while(true) {
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
					read_craft_level(workbanch_lvl);
					printf("chose craft (N)umber\n");
					printf("type eny symbol to exit\n");
					read_inventory(inv);
					if (scanf("%d", &chi) != 0) { }
					else { break; }
					craft_item(workbanch_lvl.belt[chi - 1], &inv);
				}
			}
			free_string(&toeq);
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
			place_item(&inv.arr[inv.chosen_slot], ts.self_map, get_free_space(plus_vec2(new_vec2(ts.self->position.x, ts.self->position.y), dir), ts.self_map)->position, inv.chosen_slot);
		}
		if (ch == 'z') {
			if (ts.self_map->index + 1 != map.layer_count && get_obj(vec2_to_vec3(plus_vec2(new_vec2(ts.self->position.x, ts.self->position.y), dir), 0), ts.self_map)->id == -1) {
				collect_block(plus_vec2(new_vec2(ts.self->position.x, ts.self->position.y), dir), &inv, &map.arr[ts.self_map->index + 1]);
			}
		}
		if (ch == 'x') {
			collect_block(plus_vec2(new_vec2(ts.self->position.x, ts.self->position.y), dir), &inv, ts.self_map);
		}
		if (ch == 'c') {
			collect_floor(plus_vec2(new_vec2(ts.self->position.x, ts.self->position.y), dir), &inv, ts.self_map);
		}

		if (ch == 'Q') { break; }
	}
	
	free_full_craft_level(&hand_lvl);
	free_inventory(&inv);
	free_tile_map_data(&map.arr[0].data);
	return 0;
}
