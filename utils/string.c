struct String {
	size_t size;
	char *arr;
};

struct String init_string(size_t size, char* charstr) {
	struct String tmp;
	tmp.arr = (char*) malloc(size * sizeof(char));
	tmp.size = size;

	for (int i = 0; i < size; i++) {
		tmp.arr[i] = charstr[i];
	}

	return tmp;
}

void append(struct String *str, struct String to_add) {
	size_t start_point = str->size;
	str->size += to_add.size;

	(*str).arr = realloc(str->arr, str->size * sizeof(char));
	for (int i = 0; i < to_add.size; i++) {
		(*str).arr[i + start_point] = to_add.arr[i];
	}
}

void reinit(struct String *str, struct String new) {
	str->size = new.size;

	(*str).arr = malloc(str->size * sizeof(char));
	for (int i = 0; i < new.size; i++) {
		(*str).arr[i] = new.arr[i];
	}
}
void free_string(struct String *str) {
	free(str->arr);
}
