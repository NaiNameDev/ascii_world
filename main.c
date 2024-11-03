#define air new_object(new_vec3(0,0,0), '#', DEF, DEF, -1, init_string(4, "air "))
#include "headers.c"

void start_loop() {
	main_loop(hand_lvl, workbanch_lvl);
}

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
	
	main_menu();

	//struct tileMap a = gen(time(NULL),new_vec2(10, 10), 3);

	free_full_craft_level(&hand_lvl);
	free_full_craft_level(&workbanch_lvl);
	return 0;
}
