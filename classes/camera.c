struct camera {
	struct tileMap *map;
	struct vec2 start;
	struct vec2 end;
};
struct camera new_camera(struct tileMap* map, struct vec2 start, struct vec2 end) {
	struct camera;
	camera.map = map;
	camera.start = start;
	camera.start = end;
	return tmp;
}
void read_camera(struct camera cam) {
	for (int i = 0; i < cam.end.y; i++) {
		for (int j = 0; j < cam.end.x; j++) {
			read_object(*get_last_object(new_vec2(j, i), map));
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

