#include "Header.h"

Loading::Loading() {
	progress_loading = 0;
	active = 1;
	x = -10;
}

void Loading::show_loading() {
	if (active == 1) {
		if (progress_loading > 1250) {
			active = 0;
		}
		else {
			progress_loading += 10;
			x += 0.16;
			glColor3d(0, 0.3, 0.9);

			glBegin(GL_QUADS);
			glVertex3d(-10, -6, 0);
			glVertex3d(-10, -5.3, 0);
			glVertex3d(x, -5.3, 0);
			glVertex3d(x, -6, 0);
			glEnd();

			glColor3d(1, 0.4, 0);
			glLineWidth(3.0f);
			renderStrokeFontString(-22, -1, -20, "Fast-Checkers", 0.05);
		}
	}
}