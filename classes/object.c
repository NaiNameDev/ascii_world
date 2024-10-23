struct object {
	struct vec3 position;
	char sym;
	char color[5];
	char color_bg[5];
	int id;
	int colide; // 1 - colide, 0 - not colide
};
struct object new_object(struct vec3 pos, char sym, char color[5], char color_bg[5], int id, int colide) {
	struct object tmp;
	tmp.position = pos;
	tmp.sym = sym;
	set_color(tmp.color, color);
	set_color(tmp.color_bg, color_bg);
	tmp.id = id;
	tmp.colide = colide;
	return tmp;
}

void read_object(struct object obj) {
	read_color(obj.color_bg);
	read_color(obj.color);
	printf("%c", obj.sym);
	read_color(DEF);
}

//id table
//
// 0: air
// 1: test block
