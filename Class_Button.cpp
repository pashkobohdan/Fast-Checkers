#include "Header.h"


Button::Button() {}

Button::Button(int off_on, double x1, double y1, double x2, double y2, char *string, int length) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->length = length;
	this->off_on = off_on;

	take = 0;
	active = 0;

	text = string;
}

void Button::show_button() {

	if (off_on == 1) {

		glColor3d(0, 0, 0.5);

		if (length == 1) {
			renderStrokeFontString(x1, y1 + 0.3, 0.2, text, 0.005);
		}
		if (length == 2) {
			renderStrokeFontString(x1, y1 + 0.5, 0.2, text, 0.005);
		}


		if (take == 1) {
			glColor3d(0.74, 0.24, 1);
		}
		else {
			if (active == 1) {
				glColor3d(1, 0.6, 0);
			}
			else {
				glColor3d(1, 0.8, 0.5);
			}
		}


		glBegin(GL_QUADS);
		glVertex3d(x1, y1, 0.1);
		glVertex3d(x1, y2, 0.1);
		glVertex3d(x2, y2, 0.1);
		glVertex3d(x2, y1, 0.1);
		glEnd();
	}
}