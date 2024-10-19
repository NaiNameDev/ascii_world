struct object {
	struct vec2 position;
	char sym;
	char color[5];
	char color_bg[5];
};
struct object new_object(struct vec2 pos, char sym, char color[5], char color_bg[5]) {
	struct object tmp;
	tmp.position = pos;
	tmp.sym = sym;
	set_color(tmp.color, color);
	set_color(tmp.color_bg, color_bg);
	return tmp;
}
