#include "Header.h"

Game_end::Game_end() {
	exit_to_menu = Button(1, -3, -2, 3, -0.5, "  Exit to menu", 2);
	active = 1;
	winner = -1;
}

void Game_end::show_end() {

	renderStrokeFontString(-2.6, 4, 0.01, "Win : ", 0.007);
	if (winner == -1) {
		renderStrokeFontString(0.4, 4, 0.01, "Black", 0.007);
	}
	else {
		renderStrokeFontString(0.4, 4, 0.01, "White", 0.007);
	}
	exit_to_menu.show_button();
}

void Game_end::prov_buttons(int x, int y, int w, int h) {
	double xx = double(x);
	double yy = double(y);

	//std::cout << "   " << double(xx / w) << "  " << double(yy / h) << "\n";

	if (double(xx / w) >= 0.40117 && double(xx / w) <= 0.59809 && double(yy / h) >= 0.52864 && double(yy / h) <= 0.61588) { exit_to_menu.active = 1; }
	else { exit_to_menu.active = 0; }

}

void Game_end::pressure() {
	if (exit_to_menu.active == 1) {
		active = 0;
	}
}
