#define NULLITEM new_item('.', DEF, DEF, init_string(0,""), 0, 0)

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

struct craft {
	struct item crafting_item;
	
};
