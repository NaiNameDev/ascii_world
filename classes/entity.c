struct entity {
	struct object *self;
	struct tileMapLayer *self_map;
};
struct entity new_entity(struct object *self, struct tileMapLayer *self_tilemap) {
	struct entity tmp;
	tmp.self = self;
	tmp.self_map = self_tilemap;
	return tmp;
}
void move_entity(struct entity *tmp, struct vec2 new_pos) {
	if (get_last_object(new_pos, tmp->self_map)->id == 0) {
		tmp->self = move_obj(new_pos, *tmp->self, tmp->self_map);
	}
}

struct player {
	struct entity ent;
	struct inventory inv;
};
void place_item(struct item *to_place, struct tileMapLayer *map, struct vec3 pos) {
	if (to_place->block_id != -1) {
		set_obj(pos, item_to_object(*to_place), map);
	}
}
