#define up new_vec2(0, 1)
#define down new_vec2(0, -1)
#define left new_vec2(-1, 0)
#define right new_vec2(1, 0)

struct entity {
	struct String name;
	struct object *self;
	struct tileMapLayer *self_map;
};
struct entity new_entity(struct String name, struct object *self, struct tileMapLayer *self_tilemap) {
	struct entity tmp;
	reinit(&tmp.name, name);
	tmp.self = self;
	tmp.self_map = self_tilemap;
	return tmp;
}
void move_entity(struct entity *tmp, struct vec3 new_pos) {
	if (get_obj(new_pos, tmp->self_map)->colide == 0) {
		tmp->self = move_obj(new_pos, *tmp->self, tmp->self_map);
	}
}

struct player {
	struct entity ent;
	struct inventory inv;
};
void place_item(struct item *to_place, struct tileMapLayer *map, struct vec3 pos) {
	if (to_place->is_block == 1) {
		set_obj(pos, item_to_object(*to_place), map);
	}
}
