#define up new_vec2(0, 1)
#define right new_vec2(1, 0)

void craft_loop(struct craftLevel lvl, struct inventory inv) {
	int chi = 0;
	while(true) {
		printw("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		read_craft_level(lvl);
		printf("chose craft (N)umber\n");
		printf("type eny symbol to exit\n");
		read_inventory(inv);
		if (scanf("%d", &chi) != 0) { }
		else { break; }
		if (chi - 1 < lvl.size) {
			craft_item(lvl.belt[chi - 1], &inv);
		}
	}
}

	

void main_loop(struct craftLevel hand_lvl, struct craftLevel workbanch_lvl) {
	struct tileMap map = gen(time(NULL), new_vec2(30, 30), 3);
	//map.arr[0] = load();
	//read_map(&map.arr[0]);
	//save_world(&map, init_string(3, "def/"));
	//map = load_world(init_string(12, "./saves/def/"));
	//read_map(&map.arr[0]);

	struct object* a = set_obj(new_vec3(5,5,7), new_object(new_vec3(3,3,3), 'P', GREEN, PURPLE_BG, 0, init_string(6, "player")), &map.arr[0]);
	struct entity player = new_entity(a, &map.arr[0]);
	struct inventory inv = new_inventory(10);
	struct vec2 dir = up;
	
	//init cusrses

	int ch = 0;
	while (true) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("wasd - move, (1, 2) - change slot, e - place block, x - break block, c - break floor, z - break block on z - 1, ; - move down, ' - move up, f - change direction, i - inventory mod, S - save, L - load, Q - QUIT\n\n");	
		print_vec3(player.self->position);
		read_tile_map(&map, player.self_map->index, plus_vec2(vec3_to_vec2(player.self->position), new_vec2(-8,-8)), plus_vec2(vec3_to_vec2(player.self->position), new_vec2(9,9)));
		if (vec2_equal(up, dir) == true) {
			printf("∇\n");
		}
		else if (vec2_equal(right, dir) == true) {
			printf(">\n");
		}
		else if (dir.x == -up.x && dir.y == -up.y) {
			printf("Δ\n");
		}
		else if (dir.x == -right.x && dir.y == -right.y) {
			printf("<\n");
		}
		read_inventory(inv);

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
		if (ch == 'S') {
			char chi[25];
			printf("\nsave file name(max 25): ");
			scanf("%24[^\n]", chi);
			printf("\nSAVING...\n");
			save_world(&map, init_string(strlen(chi), chi));
			//break;
		}
		if (ch == 'L') {
			char chi[25];
			printf("\nsave file name: ");
			scanf("%24[^\n]", chi);
			printf("\nLOADING...\n");
			map = load_world(init_string(strlen(chi), chi));
			for (int i = 0; i < map.arr[0].data.size.y * map.arr[0].data.size.z * map.arr[0].data.size.x; i++) {
				if (map.arr[0].data.arr[i].sym == 'P') {
					a = &map.arr[0].data.arr[i];
					player.self = &map.arr[0].data.arr[i];
					player.self_map = &map.arr[0];
				}
			}
		}
		if (ch == ';') {
			if (player.self_map->index + 1 <= 2) {
				move_entity_other_map(&player, new_vec2(player.self->position.x, player.self->position.y), &map.arr[player.self_map->index + 1]);
			}
		}
		if (ch == '\'') {
			if (player.self_map->index - 1 >= 0) {
				move_entity_other_map(&player, new_vec2(player.self->position.x, player.self->position.y), &map.arr[player.self_map->index - 1]);
			}
		}

		if (ch == '1') {
			set_chosen_slot(inv.chosen_slot - 1, &inv);
		}
		if (ch == '2') {
			set_chosen_slot(inv.chosen_slot + 1, &inv);
		}
		if (ch == 'i') {
			struct String toeq = init_string(9, "workbanch");
			if (check_strings_equal(get_last_object(plus_vec2(new_vec2(player.self->position.x, player.self->position.y), dir), player.self_map)->name, toeq) == false) {
				craft_loop(hand_lvl, inv);
			}
			else {
				craft_loop(workbanch_lvl, inv);
			}
			free_string(&toeq);
		}

		if (ch == 'a') {
			move_entity(&player, new_vec2(player.self->position.x - 1, player.self->position.y));
		}
		if (ch == 'd') {
			move_entity(&player, new_vec2(player.self->position.x + 1, player.self->position.y));
		}
		if (ch == 's') {
			move_entity(&player, new_vec2(player.self->position.x, player.self->position.y + 1));
		}
		if (ch == 'w') {
			move_entity(&player, new_vec2(player.self->position.x, player.self->position.y - 1));
		}

		if (ch == 'e') {
			place_item(&inv.arr[inv.chosen_slot], player.self_map, get_free_space(plus_vec2(new_vec2(player.self->position.x, player.self->position.y), dir), player.self_map)->position, inv.chosen_slot);
		}
		if (ch == 'z') {
			if (player.self_map->index + 1 != map.layer_count && get_obj(vec2_to_vec3(plus_vec2(new_vec2(player.self->position.x, player.self->position.y), dir), 0), player.self_map)->id == -1) {
				collect_block(plus_vec2(new_vec2(player.self->position.x, player.self->position.y), dir), &inv, &map.arr[player.self_map->index + 1]);
			}
		}
		if (ch == 'x') {
			collect_block(plus_vec2(new_vec2(player.self->position.x, player.self->position.y), dir), &inv, player.self_map);
		}
		if (ch == 'c') {
			collect_floor(plus_vec2(new_vec2(player.self->position.x, player.self->position.y), dir), &inv, player.self_map);
		}

		usleep(50000);
		initscr();
		curs_set(0);
		keypad(stdscr, TRUE);
		nodelay(stdscr, TRUE);
		nonl();
		cbreak();
		noecho();

		ch = getch();
		
		endwin();

		if (ch == 'Q') { break; }
	}
	free_inventory(&inv);
	free_tile_map_data(&map.arr[0].data);
	free_tile_map_data(&map.arr[1].data);
	free_tile_map_data(&map.arr[2].data);
	endwin();	
}

void main_menu();

void multi_menu() {
	
}

void solo_menu() {
	start_loop;
	return;

	int chi = 0;
	clear();

	nodelay(stdscr, FALSE);
	curs_set(1);
	int h,w;
	getmaxyx(stdscr, h, w);	

	move(h / 2, w / 2 - 19);
	printw("type seed(leave empty for random seed)");

	move(h / 2 + 1, w / 2);

	while (1) {
		chi = getch();
		if (chi == 0) {
			break;
		}
		if (chi == 'Q') {
			clear();
			main_menu();
			break;
		}
		if (chi == KEY_BACKSPACE) {
			
		}
		if (chi) {
			addch(chi | A_UNDERLINE);
		}
	}
}

void main_menu() {
	initscr();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();	

	int h, w;
	getmaxyx(stdscr, h, w);	

	if (h < 20 || w < 40) {
		printf("to small console window please resize wondow and restart the game!");
		return;
	}
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_RED);	

	printw("by NaiName");

	int chi = 0;
	char hello[] = "WELCOME TO ASCII WORLD!";
	char solo[] = "1 - play singleplayer";
	char multi[] = "2 - play multiplayer";
	char quit[] = "Q - quit";

	//attron(COLOR_PAIR(1));
	move(h / 2, w / 2 -  strlen(hello) / 2);
	printw(hello);
	move(h / 2 + 2, w / 2 - strlen(solo) / 2);
	printw(solo);
	move(h / 2 + 3, w / 2 - strlen(multi) / 2);
	printw(multi);
	move(h / 2 + 4, w / 2 - strlen(quit) / 2);
	printw(quit);

	while(1) {
		chi = getch();
		if (chi == 'Q') {
			break;
		}
		if (chi == '1') {
			solo_menu();
			break;
		}
		if (chi == '2') {
			multi_menu();
		}
	}

	endwin();
}
