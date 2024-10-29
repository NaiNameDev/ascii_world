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
int vec2_equal(struct vec2 first, struct vec2 second) {
	if (first.x == second.x && first.y == second.y) {
		return true;
	}
	else {
		return false;
	}
}

struct vec2 plus_vec2(struct vec2 a, struct vec2 b) {
	return new_vec2(a.x + b.x, a.y + b.y);
}

void print_vec2(struct vec2 tmp) {
	printf("Vec2(%d, %d)\n", tmp.x, tmp.y);
}

struct vec2 vec3_to_vec2(struct vec3 pos) {
	return new_vec2(pos.x, pos.y);
}
struct vec3 vec2_to_vec3(struct vec2 pos, int z) {
	return new_vec3(pos.x, pos.y, z);
}
