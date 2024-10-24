struct object {
	struct vec3 position;
	char sym;
	struct String name;
	char color[5];
	char color_bg[5];
	int id;
};
struct object new_object(struct vec3 pos, char sym, char color[5], char color_bg[5], int id, struct String name) {
	struct object tmp;
	tmp.position = pos;
	tmp.sym = sym;
	reinit(&tmp.name, name);
	set_color(tmp.color, color);
	set_color(tmp.color_bg, color_bg);
	tmp.id = id;
	return tmp;
}
void free_object(struct object *obj) {
	free(&obj->name.arr);
}

void read_object(struct object obj) {
	read_color(obj.color_bg);
	read_color(obj.color);
	printf("%c", obj.sym);
	read_color(DEF);
}

//id table
//
// -1: item
//
// 0: air
// 1: block
