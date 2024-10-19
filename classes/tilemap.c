size_t WORLD_X = 9;
size_t WORLD_Y = 9;

struct tileMapData {
	struct vec2 size;
	struct object arr[9][18][32];
};
struct tileMapData new_tile_map_data(char sym) {
	struct tileMapData tmp;
	tmp.size = new_vec2(WORLD_X, WORLD_Y);
	
	for (int i = 0; i < sizeof(tmp.arr) / sizeof(tmp.arr[0]); i++) {
		for (int j = 0; j < sizeof(tmp.arr[i]) / sizeof(tmp.arr[i][0]); j++) {
			struct object a = new_object(new_vec2(i,j), sym, GREEN, GREEN_BG);
			tmp.arr[i][j][0] = a;
		}
	}

	return tmp;
}

struct tileMapLayer {
	struct tileMapData data;
};
struct tileMapLayer new_tile_map_layer(struct tileMapData data) {
	struct tileMapLayer tmp;
	tmp.data = data;
	return tmp;
}
struct object* get_obj(struct vec2 pos, struct tileMapLayer* map) {
	struct object* tmp = &map->data.arr[pos.x][pos.y][0];
	return tmp;
}
struct object* set_obj(struct vec2 pos, struct object new_obj, struct tileMapLayer* map) {
	new_obj.position = pos;
	map->data.arr[pos.x][pos.y][0] = new_obj;
	return get_obj(pos, map);
}
struct object* move_obj(struct vec2 new_pos, struct object obj_to_move, struct tileMapLayer* map) {
	map->data.arr[obj_to_move.position.x][obj_to_move.position.y][0] = map->data.arr[new_pos.x][new_pos.y][0];
	obj_to_move.position = new_pos;
	map->data.arr[new_pos.x][new_pos.y][0] = obj_to_move;
	return get_obj(new_pos, map);
}

void read(struct tileMapLayer map) {
	char tmp[(size_t) (map.data.size.x * map.data.size.y)];
	
	for (int i = 0; i < sizeof(map.data.arr) / sizeof(map.data.arr[0]); i++) {
		for (int j = 0; j < sizeof(map.data.arr[i]) / sizeof(map.data.arr[i][0]); j++) {
			printf("%s%s%c%s",map.data.arr[i][j][0].color_bg, map.data.arr[i][j][0].color, map.data.arr[i][j][0].sym, DEF);
			//printf(" "); //for debug
		}
		printf("\n");
	}
	printf("\n");
}
