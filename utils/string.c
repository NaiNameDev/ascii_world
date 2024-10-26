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

void char_append(struct String *str, char charstr) {
	str->size += 1;
	(*str).arr = realloc(str->arr, str->size * sizeof(char));
	(*str).arr[str->size - 1] = charstr;
}

void char_array_append(struct String *str, size_t size, char* charstr) {
	size_t start_point = str->size;
	str->size += size;

	(*str).arr = realloc(str->arr, str->size * sizeof(char));
	for (int i = 0; i < size; i++) {
		(*str).arr[i + start_point] = charstr[i];
	}
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
int check_strings_equal(struct String to_ch, struct String target) {
	if (to_ch.size != target.size) {
		return false;
	}
	for (int i = 0; i < to_ch.size; i++) {
		if (to_ch.arr[i] != target.arr[i]) {
			return false;
		}
	}
	return true;
}
void free_string(struct String *str) {
	free(str->arr);
}
