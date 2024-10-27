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
	if (search_id(new_pos, 1, tmp->self_map) == false) {
		if (new_pos.x >= 0 && new_pos.y >= 0 && new_pos.x < tmp->self_map->data.size.x && new_pos.y < tmp->self_map->data.size.y)
			tmp->self = move_obj(new_pos, *tmp->self, tmp->self_map);
		}
}
void move_entity_other_map(struct entity *tmp, struct vec2 new_pos, struct tileMapLayer* new_map) {
	if (search_id(new_pos, 1, new_map) == false) {
		if (new_map->index < tmp->self_map->index && get_obj(new_vec3(new_pos.x, new_pos.y, 0), new_map)->id == -1) {
			tmp->self = move_to_other_map(new_pos, *tmp->self, tmp->self_map, new_map);
			tmp->self_map = new_map;
		}
		else if (new_map->index > tmp->self_map->index && tmp->self->position.z == 0) {
			tmp->self = move_to_other_map(new_pos, *tmp->self, tmp->self_map, new_map);
			tmp->self_map = new_map;
		}
	}
}
struct player {
	struct entity ent;
	struct inventory inv;
};
void place_item(struct item *to_place, struct tileMapLayer *map, struct vec3 pos, int index) {
	if (search_id(new_vec2(pos.x, pos.y), 1, map) == false && search_id(new_vec2(pos.x, pos.y), 2, map) == false) {
		if (to_place->block_id != -1 && to_place->stack != 0) {
			to_place->stack -= 1;
			set_obj(pos, item_to_object(*to_place), map);
		}
		if (to_place->stack <= 0) {
			set_obj(pos, item_to_object(*to_place), map);
			*to_place = NULLITEM;
		}
	}
}
void collect_floor(struct vec2 pos, struct inventory* inv, struct tileMapLayer* map) {
	struct item itm;
	if (search_id(pos, 0, map) == true && search_id(pos, 1, map) == false && search_id(pos, 2, map) == false) {
		for (int i = 0; i < map->data.size.z; i++) {
			if (get_obj(new_vec3(pos.x, pos.y, i), map)->id == 0) {
				itm = object_to_item(*get_obj(new_vec3(pos.x, pos.y, i), map), 1);
				set_free_obj(new_vec3(pos.x, pos.y, i), air, map);
				break;
			}
		}
		for (int j = 0; j < inv->size; j++) {
			if (check_strings_equal(inv->arr[j].name, itm.name) == true) {
				itm.stack += inv->arr[j].stack;
				set_item(inv, itm, j);
				return;
			}
		}
		for (int j = 0; j < inv->size; j++) {
			if (inv->arr[j].icon == NULLITEM.icon) {
				set_item(inv, itm, j);
				return;
			}
		}
	}
}
void collect_block(struct vec2 pos, struct inventory* inv, struct tileMapLayer* map) {
	struct item itm;
	if (search_id(pos, 1, map) == true || search_id(pos, 2, map) == true) {
		for (int i = 0; i < map->data.size.z; i++) {
			if (get_obj(new_vec3(pos.x, pos.y, i), map)->id != -1 && get_obj(new_vec3(pos.x, pos.y, i), map)->id != 0) {
				itm = object_to_item(*get_obj(new_vec3(pos.x, pos.y, i), map), 1);
				set_free_obj(new_vec3(pos.x, pos.y, i), air, map);
				break;
			}
		}
		for (int j = 0; j < inv->size; j++) {
			if (check_strings_equal(inv->arr[j].name, itm.name) == true) {
				itm.stack += inv->arr[j].stack;
				set_item(inv, itm, j);
				return;
			}
		}
		for (int j = 0; j < inv->size; j++) {
			if (inv->arr[j].icon == NULLITEM.icon) {
				set_item(inv, itm, j);
				return;
			}
		}
	}
}
