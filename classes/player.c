struct Item {
	char icon;
	char icon_color[5];
	char icon_color_bg[5];
	
	struct String name;
	
	int stack;
}

struct Item new_item(char icon, char color[5], char color_bg[5], name[20], int stack) {
	struct Item tmp;
	
	
	return tmp;
}

struct Inventory {
	struct Item arr[10];
};
