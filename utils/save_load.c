struct save_unit {
	//struct String dir_path;
	size_t layer_count;
};

void save_layer_data(struct String file_name, struct String path, struct tileMapData *to_save) {
	string_append(&path, init_string(file_name.size, file_name.arr));
	//char_array_append(&path, 5, ".save");

	//printf("%s\n", path.arr);

	FILE* file = fopen(path.arr, "wb");
	if (!file) { printf("SAVE OPEN ERROR!"); exit(1); }

	int true_size = to_save->size.x * to_save->size.y * to_save->size.z;
	fwrite(&to_save->size, sizeof(struct vec3), 1, file);

	for (int i = 0; i < true_size; i++) {
		size_t now_size = ((sizeof(struct object) - sizeof(struct String)) + (to_save->arr[i].name.size * (sizeof(to_save->arr[i].name.arr))));
		fwrite(&now_size, sizeof(size_t), 1, file);
		fwrite(&to_save->arr[i], now_size, 1, file);
	}
	fclose(file);

	printf("layer successfully saved as %s\n", path.arr);
}

struct tileMapData load_layer_data(struct String path_to_file) {
	//char_array_append(&path_to_file, 5, ".save");
	//printf("%s\n", path_to_file.arr);

	FILE* file = fopen(path_to_file.arr, "rb");
	if (!file) { printf("LOAD OPEN ERROR!"); exit(1); }
	
	struct vec3 vec_size;
	fread(&vec_size, sizeof(struct vec3), 1, file);	
	
	int true_size = vec_size.x * vec_size.y * vec_size.z;
	struct tileMapData data = new_tile_map_data(air, vec_size.x, vec_size.y, vec_size.z);
	
	for (int i = 0; i < true_size; i++) {
		size_t now_size;
		fread(&now_size, sizeof(size_t), 1, file);
		fread(&data.arr[i], now_size, 1, file);
	}
	fclose(file);

	printf("layer successfully loaded from %s\n", path_to_file.arr);

	return data;
}

void save_world(struct tileMap *map, struct String dir_name) {
	
	struct String path;
	init_var_string(8, "./saves/", &path);
	mkdir(path.arr, 0777);

	if (dir_name.arr[dir_name.size - 1] != '/') {
		char_append(&dir_name, '/');
	}
	string_append(&path, dir_name);
	mkdir(path.arr, 0777);
	
	struct save_unit unit;
	unit.layer_count = map->layer_count;
	//unit.path = init_string(path.size, path.arr);

	printf("open dir %s\n", path.arr);

	struct String info_name;

	reinit_string(&info_name, path);
	char_array_append(&info_name, 6, "info.i");
	FILE* info = fopen(info_name.arr, "wb");

	fwrite(&unit, sizeof(size_t), 1, info);
	//fwrite(&unit, sizeof(path.size) * sizeof(path.arr), 1, info);

	//free_string(&info_name);

	char_array_append(&path, 7, "levels/");
	mkdir(path.arr, 0777);
	//printf("%s\n", path.arr);
	struct String name = init_string(1, "a");
	for (int i = 0; i < map->layer_count; i++) {
		save_layer_data(init_string(name.size, name.arr), init_string(path.size, path.arr), &map->arr[i].data);
		char_append(&name, 'a');
	}
	fclose(info);
}

struct tileMap load_world(struct String path_to_dir) {
	if (path_to_dir.arr[path_to_dir.size - 1] != '/') {
		char_append(&path_to_dir, '/');
	}

	struct String info_path = init_string(8, "./saves/");
	string_append(&info_path, path_to_dir);
	string_append(&info_path, init_string(6, "info.i"));

	printf("opening info.i in %s\n", info_path.arr);

	FILE* info_file = fopen(info_path.arr, "rb+");
	if (!info_file) {
		printf("ERROR: CANT FIND \"info.i\" FILE!");
		return new_tile_map(1, 0, 0);
	}

	struct save_unit unit;

	fread(&unit.layer_count, sizeof(size_t), 1, info_file);

	struct tileMap map = new_tile_map(unit.layer_count, 0, 0);
	struct String name = init_string(8, "./saves/");
	string_append(&name, path_to_dir);
	char_array_append(&name, 8, "levels/a");

	for (int i = 0; i < unit.layer_count; i++) {
		map.arr[i].data = load_layer_data(name);
		char_append(&name, 'a');
	}

	fclose(info_file);
	return map;
}








