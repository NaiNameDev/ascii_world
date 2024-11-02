#define true 1
#define false 0

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#include "utils/color.c"
#include "utils/string.c"
#include "utils/vector.c"
#include "classes/object.c"
#include "classes/tilemap.c"
#include "classes/inventory.c"
#include "classes/entity.c"
#include "utils/save_load.c"

#include "game_settings/items.c"
#include "game_settings/generator.c"
#include "game_settings/ui.c"

char air_sym = '#';
