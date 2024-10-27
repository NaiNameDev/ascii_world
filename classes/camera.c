struct camera {
	struct vec2 position;
	struct vec2 local_start;
	struct vec2 local_end;
};/*
struct camera new_camera(struct vec2) {
	struct camera;
	camera.map = map;
	camera.start = start;
	camera.start = end;
	return tmp;
}
void read_camera(struct tileMap* map, struct camera cam) {
	read_tile_map(map, cam.start, cam.end);
}

