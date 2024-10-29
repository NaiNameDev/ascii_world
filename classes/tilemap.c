struct tileMapData {
	struct vec3 size;
	struct object *arr;
};
size_t vec3_to_size(struct vec3 pos, struct vec3 size) {
	return (size.x * size.y * pos.z) + (pos.x * size.y + pos.y); //god deamn я эту формулу ИСКАЛ СУКА 2 СРАНЫХ ДЛЯ СУКА
}
struct tileMapData new_tile_map_data(struct object obj, int x, int y, int z) {
	struct tileMapData tmp;
	tmp.size = new_vec3(x, y, z);
	tmp.arr = malloc((x * y * z) * sizeof(struct object));
	
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			for (int o = 0; o < z; o++) {
				obj.position = new_vec3(j, i, o);
				tmp.arr[vec3_to_size(new_vec3(j, i, o), new_vec3(x, y, z))] = obj;
			}
		}
	}
	return tmp;
}
struct tileMapData free_tile_map_data(struct tileMapData *data) {
	//for (int i = 0; i < data->size.x * data->size.y * data->size.z; i++) {
	//	free(&data->arr[i].name.arr);
	//}
	free(data->arr);
}

struct tileMapLayer {
	struct tileMapData data;
	int index;
};
struct tileMapLayer new_tile_map_layer(struct tileMapData data, int index) {
	struct tileMapLayer tmp;
	tmp.index = index;
	tmp.data = data;
	return tmp;
}
struct object* get_obj(struct vec3 pos, struct tileMapLayer* map) {
	return &map->data.arr[vec3_to_size(pos, map->data.size)];
}
struct object* set_obj(struct vec3 pos, struct object new_obj, struct tileMapLayer* map) {
	new_obj.position = pos;
	map->data.arr[vec3_to_size(pos, map->data.size)] = new_obj;
	return get_obj(pos, map);
}
void set_free_obj(struct vec3 pos, struct object new_obj, struct tileMapLayer* map) {
	new_obj.position = pos;
	map->data.arr[vec3_to_size(pos, map->data.size)] = new_obj;
}
struct object* get_last_object(struct vec2 pos, struct tileMapLayer *map) {
	struct object* tmp = &map->data.arr[vec3_to_size(new_vec3(pos.x, pos.y, 0), map->data.size)];
	
	for (int i = 0; i < map->data.size.z; i++) {
		if (get_obj(new_vec3(pos.x, pos.y, i), map)->id != -1) {
			tmp = get_obj(new_vec3(pos.x, pos.y, i), map);
		}
	}
	return tmp;
}
struct object* get_free_space(struct vec2 pos, struct tileMapLayer *map) {
	for (int i = 0; i < map->data.size.z; i++) {
		if (map->data.arr[vec3_to_size(new_vec3(pos.x, pos.y, i), map->data.size)].id == -1) {
			return &map->data.arr[vec3_to_size(new_vec3(pos.x, pos.y, i), map->data.size)];
		}
	}
}
struct object* move_obj(struct vec2 new_pos, struct object obj_to_move, struct tileMapLayer* map) {
	//map->data.arr[vec3_to_size(obj_to_move.position, map->data.size)] = air;
	struct vec3 pos = new_vec3(new_pos.x, new_pos.y, get_free_space(new_pos, map)->position.z);
	set_obj(obj_to_move.position, air, map);
	obj_to_move.position = pos;
	set_obj(pos, obj_to_move, map);
	return get_obj(pos, map);
}

struct object* move_to_other_map(struct vec2 new_pos, struct object obj_to_move, struct tileMapLayer* startmap, struct tileMapLayer* endmap) {
	//map->data.arr[vec3_to_size(obj_to_move.position, map->data.size)] = air;
	struct vec3 pos = new_vec3(new_pos.x, new_pos.y, get_free_space(new_pos, endmap)->position.z);
	set_obj(obj_to_move.position, air, startmap);
	obj_to_move.position = pos;
	set_obj(pos, obj_to_move, endmap);
	return get_obj(pos, endmap);
}

int search_id(struct vec2 pos, int id, struct tileMapLayer* map) {
	for (int i = 0; i < map->data.size.z; i++) {
		if (get_obj(new_vec3(pos.x, pos.y, i), map)->id == id) {
			return true;
		}
	}
	return false;
}

void read_map(struct tileMapLayer* map) {
	for (int i = 0; i < map->data.size.y; i++) {
		for (int j = 0; j < map->data.size.x; j++) {
			read_object(*get_last_object(new_vec2(j, i), map));
			printf(" "); //for debug
		}
		printf("\n");
	}
	printf("\n");
}
struct tileMap {
	struct tileMapLayer* arr;
	size_t layer_count;
};
struct tileMap new_tile_map(/*struct tileMapLayer paste_map*/ size_t layer_count, int size_x, int size_y) {
	struct tileMap tmp;
	tmp.layer_count = layer_count;
	
	tmp.arr = malloc(layer_count * sizeof(struct tileMapLayer));
	
	for (int i = 0; i < layer_count; i++) {
		tmp.arr[i] = new_tile_map_layer(new_tile_map_data(air, size_x, size_y, 8), i);
	}

	return tmp;
}
//char air_progress[2] = "#+."
void read_tile_map(struct tileMap* map, size_t start_z, struct vec2 start, struct vec2 end) {
	for (int i = start.y; i < end.y; i++) {
		for (int j = start.x; j < end.x; j++) {
			if (i >= 0 && j >= 0 && i < map->arr[0].data.size.y && j < map->arr[0].data.size.x ) {
				if (get_last_object(new_vec2(j, i), &map->arr[start_z])->id != -1) {
						read_object(*get_last_object(new_vec2(j, i), &map->arr[start_z]));
				}
				else if (start_z + 1 != map->layer_count) {
					if (get_last_object(new_vec2(j, i), &map->arr[start_z + 1])->id != -1) {
						switch (get_last_object(new_vec2(j, i), &map->arr[start_z + 1])->id) {
							case 0:
								printf("=");
								break;
							case 1:
								read_color(BLACK);
								read_color(WHITE_BG);
								printf("#");
								read_color(DEF);
								break;
							case 2:
								printf("+");
								break;
						}
					}
					else {
						printf(".");
					}
					//for (int j = 0; j < map->layer_count - start_index; j++) {
					//	if (*get_last_object(new_vec2(j, i), map)->index != -1) {
					//		printf(air_progress[j]);
					//	}
					//}
				}
				else {
					printf(".");
				}
				printf(" "); //for debug
			}
			else { printf("  "); }
		}
		printf("\n");
	}
	printf("\n");
}
