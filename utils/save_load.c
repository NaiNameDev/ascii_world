struct save_unit {
	struct String folder_path;
	struct String* layer_files_paths;
	struct String* entity_files_paths;
}

void save_layer_data(struct String file_name, struct tileMapData *to_save) {
	struct String path = init_string(8, "./saves/");
	
	mkdir(path.arr, 0777);
	append(&path, file_name);
	char_array_append(&path, 5, ".save");

	FILE* file = fopen(path.arr, "wb");
	if (!file) { printf("SAVE OPEN ERROR!"); exit(1); }

	int true_size = to_save->size.x * to_save->size.y * to_save->size.z;
	
	for (int i = 0; i < true_size; i++) {
		size_t now_size = ((sizeof(struct object) - sizeof(struct String)) + (to_save->arr[i].name.size * (sizeof(to_save->arr[i].name.arr))));
		fwrite(&now_size, sizeof(size_t), 1, file);
		fwrite(&to_save->arr[i], now_size, 1, file);
	}

	fclose(file);
	free_string(&file_name);
	free_string(&path);
}

void load_layer_data() {
	FILE* file = fopen("./saves/asd.save", "rb");
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
	//return NULL;
}
