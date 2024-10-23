struct tileMapData {
	struct vec3 size;
	struct object *arr;
};
size_t vec3_to_size(struct vec3 p) {
	return p.x * p.y * p.z + p.y * p.z;
}
struct tileMapData new_tile_map_data(struct object obj, int x, int y, int z) {
	struct tileMapData tmp;
	tmp.size = new_vec3(x, y, z);
	tmp.arr = malloc((x * y * z) * sizeof(struct object));
	
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			obj.position = new_vec3(i, j, 0);
			tmp.arr[i * y * z + j * z] = obj;
		}
	}
	return tmp;
}
struct tileMapData free_tile_map_data(struct tileMapData *data) {
	free(data->arr);
}

struct tileMapLayer {
	struct tileMapData data;
};
struct tileMapLayer new_tile_map_layer(struct tileMapData data) {
	struct tileMapLayer tmp;
	tmp.data = data;
	return tmp;
}
struct object* get_obj(struct vec3 pos, struct tileMapLayer* map) {
	struct object* tmp = &map->data.arr[pos.x * map->data.size.y + pos.y];
	return tmp;
}
struct object* set_obj(struct vec3 pos, struct object new_obj, struct tileMapLayer* map) {
	new_obj.position = pos;
	map->data.arr[pos.x * map->data.size.y + pos.y] = new_obj;
	return get_obj(pos, map);
}
void set_free_obj(struct vec3 pos, struct object new_obj, struct tileMapLayer* map) {
	new_obj.position = pos;
	map->data.arr[pos.x * map->data.size.y + pos.y] = new_obj;
}
struct object* move_obj(struct vec2 new_pos, struct object obj_to_move, struct tileMapLayer* map) {
	map->data.arr[obj_to_move.position.x * obj_to_move.position.y * obj_to_move.position.z + obj_to_move.position.y * obj_to_move.position.z];
	struct vec3 last = get_last_object(new_pos , &map);
	map->data.arr[new_pos.x * new_pos.y * last.z + new_pos.y * last.z] = obj_to_move;
	return get_obj(new_vec3(new_pos.x, new_pos.y, last.z), map);
}
struct vec3 get_last_object(struct vec2 pos, struct tileMapLayer *map) {
	for (int i = 0; i < map->data.size.z; i++) {
		if (map->data.arr[pos.x * pos.y * i + pos.y * i].sym != '.') {
			return new_vec3(pos.x, pos.y, pos.x * pos.y * i + pos.y + i);
		}
	}
}

/* NOT WORKS!!! meybe be fixd when i need it xd
void resize_tile_map_layer(struct tileMapLayer *map, char sym, int x, int y) {
	int start_point = map->data.size.x * map->data.size.y;
	map->data.size = new_vec3(x, y);
	map->data.arr = realloc(map->data.arr, (x * y) * sizeof(struct object));
	
	for (int i = 0; i < y - (y - start_point); i++) {
		for (int j = 0; j < x - (x - start_point); j++) {
			struct object a = new_object(new_vec3(i,j), sym, GREEN, DEF);
			map->data.arr[(i * y + j) + start_point] = a;
		}
	}
}
*/
void read_map(struct tileMapLayer map) {
	//struct String str = init_string(0, "");

	for (int i = 0; i < map.data.size.y; i++) {
		for (int j = 0; j < map.data.size.x; j++) {
			//char_array_append(&str, 5, map.data.arr[i][j][0].color_bg);
			//char_array_append(&str, 5, map.data.arr[i][j][0].color);
			//char_append(&str, map.data.arr[i][j][0].sym);
			//char_array_append(&str, 5, DEF);
			//struct object *tmp = &map.data.arr[i * map.data.size.y + j];
			//printf("%s%s%c%s ", tmp->color_bg, tmp->color, tmp->sym, DEF);
			read_object(map.data.arr[i * map.data.size.y * map.data.size.z + j * map.data.size.z]);
			printf(" "); //for debug
		}
		printf("\n");
		//char_append(&str, '\n');
	}
	printf("\n");
	//printf("\r%s\r", str.arr);
	//free_string(&str);
}
