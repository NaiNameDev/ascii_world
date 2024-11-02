char asd[16] = ";;;;;,,,,,,,,,@$";

struct tileMap gen(int seed, struct vec2 size, int layer_count) {
	srand(seed);

	struct tileMap tmp = new_tile_map(layer_count, size.x, size.y);
	
	struct object r = item_to_object(rock);
	struct object o = item_to_object(grass);
	for (int i = 0; i < size.y; i++) {
		for (int j = 0; j < size.x; j++) {
			if ( i * j > 48) {
				int a = rand() % 16;
				o.sym = asd[a];
				if (a == 1) {
					set_obj(new_vec3(i, j, 1), item_to_object(rock), &tmp.arr[0]);
				}
				if (a == 2) {
					set_obj(new_vec3(i, j, 1), item_to_object(wood_log), &tmp.arr[0]);
				}
				if (a == 3) {
					set_obj(new_vec3(i, j, 1), item_to_object(bery), &tmp.arr[0]);
				}
				set_obj(new_vec3(i, j, 0), o, &tmp.arr[0]);
			}
			else if (i * j < 24) {
				set_obj(new_vec3(i, j, 0), item_to_object(water), &tmp.arr[0]);
			}
			else {
				set_obj(new_vec3(i, j, 0), item_to_object(sand), &tmp.arr[0]);
			}
			set_obj(new_vec3(i, j, 0), r, &tmp.arr[2]);
			set_obj(new_vec3(i, j, 0), r, &tmp.arr[1]);
		}
	}
	//save(seed, init_string(3, "asd"), &tmp.arr[0].data);
	//load();
	return tmp;
}
