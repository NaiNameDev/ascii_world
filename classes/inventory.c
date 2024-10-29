#define NULLITEM new_item('.', DEF, DEF, init_string(0,""), 0, -1)

struct item {
	char icon;
	char icon_color[5];
	char icon_color_bg[5];
	
	struct String name;
	
	int stack;
	int block_id;
};
struct item new_item(char icon, char color[5], char color_bg[5], struct String name, int stack, int block_id) {
	struct item tmp;
	tmp.icon = icon;
	set_color(tmp.icon_color, color);
	set_color(tmp.icon_color_bg, color_bg);
	reinit(&tmp.name, name);
	tmp.stack = stack;
	tmp.block_id = block_id;
	
	return tmp;
}
struct item object_to_item(struct object obj, int stack) {
	return new_item(obj.sym, obj.color, obj.color_bg, obj.name, stack, obj.id);
}
struct object item_to_object(struct item itm) {
	return new_object(new_vec3(0,0,0), itm.icon, itm.icon_color, itm.icon_color_bg, itm.block_id, itm.name);
}

void read_item(struct item itm) {
	read_color(itm.icon_color_bg);
	read_color(itm.icon_color);
	printf("%c", itm.icon);
	read_color(DEF);
}

void free_item(struct item *tmp) {
	free(tmp->name.arr);
}

struct inventory {
	size_t size;
	int chosen_slot;
	struct item *arr;
};
struct inventory new_inventory(size_t size) {
	struct inventory tmp;
	tmp.size = size;
	tmp.chosen_slot = 0;
	tmp.arr = malloc(size * sizeof(struct item));

	for (int i = 0; i < size; i++) {
		tmp.arr[i] = NULLITEM;
	}
	return tmp;
}
void set_chosen_slot(int index, struct inventory* inv) {
	if (index >= 0 && index < inv->size) {
		inv->chosen_slot = index;
	}
}
void free_inventory(struct inventory *tmp) {
	for (int i = 0; i < tmp->size; i++) {
		free_item(&tmp->arr[i]);
	}
	free(tmp->arr);
}
void read_inventory(struct inventory tmp) {
	for (int i = 0; i < tmp.size; i++) {
		if ( i == tmp.chosen_slot ) {
			read_color(WHITE_BG);
			read_color(BLACK);
			printf(" %c %s", tmp.arr[i].icon, DEF);
		}
		else {
			read_item(tmp.arr[i]);
		}
	}
	printf("\n");
	printf("%s X", tmp.arr[tmp.chosen_slot].name.arr);
	printf("%d\n", tmp.arr[tmp.chosen_slot].stack);
}
void set_item(struct inventory *tmp, struct item to_add, size_t index) {
	free_item(&tmp->arr[index]);
	tmp->arr[index] = to_add;
}
void sub_item(struct inventory *tmp, int index, int to_sub) {
	if (tmp->arr[index].stack - to_sub > 0) {
		tmp->arr[index].stack -= to_sub;
	}
	else {
		//free_item(&tmp->arr[index]);
		tmp->arr[index] = NULLITEM;
	}
}

void add_item(struct inventory *tmp, struct item to_add) {
	for (int i = 0; i < tmp->size; i++) {
		if (check_strings_equal(tmp->arr[i].name, to_add.name) == true) {
			tmp->arr[i].stack += to_add.stack;
			return;
		}
	}
	for (int i = 0; i < tmp->size; i++) {
		if (tmp->arr[i].icon == NULLITEM.icon) {
			free_item(&tmp->arr[i]);
			tmp->arr[i] = to_add;
			return;
		}
	}
}

struct craft;
struct craftLevel {
	struct craft* belt;
	size_t size;
};

struct craft {
	struct item crafting_item;
	struct item* craft_elements;
	int size;
	struct craftLevel* level;
};

struct craftLevel init_craft_level(size_t start_size) {
	struct craftLevel tmp;
	tmp.belt = malloc(start_size * sizeof(struct craft*));
	tmp.size = start_size;
	return tmp;
}
void append_craft_level(struct craft crf, struct craftLevel* lvl) {
	lvl->size += 1;
	lvl->belt = realloc(lvl->belt, lvl->size * sizeof(struct craft));
	lvl->belt[lvl->size - 1] = crf;
}

struct craft init_craft(struct item itm, size_t size, struct craftLevel lvl) {
	struct craft tmp;
	tmp.crafting_item = itm;
	tmp.size = size;
	
	tmp.craft_elements = malloc(size * sizeof(struct item));
	return tmp;
}
void append_craft_element(struct craft* crf, struct item itm, int count) {
	crf->size += 1;
	itm.stack = count;
	crf->craft_elements = realloc(crf->craft_elements, crf->size * sizeof(struct item));
	crf->craft_elements[crf->size - 1] = itm;
}

void craft_item(struct craft crf, struct inventory* inv) {
	int count = 0;
	
	for (int i = 0; i < crf.size; i++) {
		for (int j = 0; j < inv->size; j++) {
			if (check_strings_equal(inv->arr[j].name, crf.craft_elements[i].name) == true) {
				if (inv->arr[j].stack >= crf.craft_elements[i].stack) {
					count++;
				}
			}
		}
	}
	printf("%d", count);
	if (count == crf.size) {
		for (int i = 0; i < crf.size; i++) {
			for (int j = 0; j < inv->size; j++) {
				if (check_strings_equal(inv->arr[j].name, crf.craft_elements[i].name) == true) {
					if (inv->arr[j].stack >= crf.craft_elements[i].stack) {
						sub_item(inv, j, crf.craft_elements[i].stack);
						add_item(inv, crf.crafting_item);
					}
				}
			}
		}
	}
}

void read_craft_level(struct craftLevel lvl) {
	for (int i = 0; i < lvl.size; i++) {
		printf("N%d %s:\n", i + 1, lvl.belt[i].crafting_item.name.arr);
		for (int j = 0; j < lvl.belt[i].size; j++) {
			printf("    %d. %s X%d\n", j + 1, lvl.belt[i].craft_elements[j].name.arr, lvl.belt[i].craft_elements[j].stack);
		}
		printf("\n");
	}
}
void free_craft(struct craft* crf) {
	free(crf->craft_elements);
}
void free_craft_level(struct craftLevel* lvl) {
	free(lvl->belt);
}
void free_full_craft_level(struct craftLevel* lvl) {
	for (int i = 0; i < lvl->size; i++) {
		free_craft(&lvl->belt[i]);
	}
	free(lvl->belt);
}
