struct vec3 {
	int x;
	int y;
	int z;
};
struct vec3 new_vec3(int x, int y, int z) {
	struct vec3 tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
};

void print_vec3(struct vec3 tmp) {
	printf("Vec3(%d, %d, %d)\n", tmp.x, tmp.y, tmp.z);
}



struct vec2 {
	int x;
	int y;
};
struct vec2 new_vec2(int x, int y) {
	struct vec2 tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
};

struct vec2 plus_vec2(struct vec2 a, struct vec2 b) {
	return new_vec2(a.x + b.x, a.y + b.y);
}

void print_vec2(struct vec2 tmp) {
	printf("Vec2(%d, %d)\n", tmp.x, tmp.y);
}

struct vec2 vec3_to_vec2(struct vec3 pos) {
	return new_vec2(pos.x, pos.y);
}
