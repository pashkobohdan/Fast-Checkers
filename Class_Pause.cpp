#include "Header.h"

Pause::Pause() {
	file1 = Button(1, -2, 3, 2, 4, "  File 1", 1);
	file2 = Button(1, -2, 1, 2, 2, "  File 2", 1);
	file3 = Button(1, -2, -1, 2, 0, "  File 3", 1);
	exit_to_menu = Button(1, -4, -5, -1, -3.5, "  Exit", 2);
	resume = Button(1, 1, -5, 4, -3.5, " Resume", 2);
	active = 0;
}

void Pause::show_pause() {
	if (active == 1) {
		glColor3d(0.4, 0, 0);
		renderStrokeFontString(-1.8, 5, 0.01, "Save in : ", 0.006);

		file1.show_button();
		file2.show_button();
		file3.show_button();
		exit_to_menu.show_button();
		resume.show_button();
	}
}

void Pause::prov_buttons(int x, int y, int w, int h) {
	double xx = double(x);
	double yy = double(y);

	//std::cout << "   " << double(xx / w) << "  " << double(yy / h) << "\n";

	if (double(xx / w) >= 0.423265 && double(xx / w) <= 0.56515 && double(yy / h) >= 0.26692 && double(yy / h) <= 0.32557) { file1.active = 1; }
	else { file1.active = 0; }

	if (double(xx / w) >= 0.43338 && double(xx / w) <= 0.56515 && double(yy / h) >= 0.38281 && double(yy / h) <= 0.44140) { file2.active = 1; }
	else { file2.active = 0; }

	if (double(xx / w) >= 0.43338 && double(xx / w) <= 0.56442 && double(yy / h) >= 0.49869 && double(yy / h) <= 0.55589) { file3.active = 1; }
	else { file3.active = 0; }

	if (double(xx / w) >= 0.3653 && double(xx / w) <= 0.46705 && double(yy / h) >= 0.70442 && double(yy / h) <= 0.79557) { exit_to_menu.active = 1; }
	else { exit_to_menu.active = 0; }

	if (double(xx / w) >= 0.53147 && double(xx / w) <= 0.63250 && double(yy / h) >= 0.70442 && double(yy / h) <= 0.79557) { resume.active = 1; }
	else { resume.active = 0; }

}
