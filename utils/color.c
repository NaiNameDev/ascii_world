char DEF[6] = "\x1b[0m";

char BLACK[6] = "\x1b[30m";
char RED[6] = "\x1b[31m";
char GREEN[6] = "\x1b[32m";
char YELLOW[6] = "\x1b[33m";
char BLUE[6] = "\x1b[34m";
char PURPLE[6] = "\x1b[35m";
char CYAN[6] = "\x1b[36m";
char WHITE[6] = "\x1b[37m";

char BLACK_BG[6] = "\x1b[40m";
char RED_BG[6] = "\x1b[41m";
char GREEN_BG[6] = "\x1b[42m";
char YELLOW_BG[6] = "\x1b[43m";
char BLUE_BG[6] = "\x1b[44m";
char PURPLE_BG[6] = "\x1b[45m";
char CYAN_BG[6] = "\x1b[46m";
char WHITE_BG[6] = "\x1b[47m";

void set_color(char string[5], char color[6]) {
	for (int i = 0; i < 5; i++) {
		string[i] = color[i];
	}
}
