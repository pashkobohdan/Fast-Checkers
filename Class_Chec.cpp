#include "Header.h"


Chec::Chec(int xx, int yy, int wb, int color) {
	active = 1;
	x = xx;
	y = yy;
	x_d = -5.6875 + (1.625*(x - 1));
	y_d = -5.6875 + (1.625*(y - 1));
	white_black = wb;
	need_of_turn = 0;
	this->color = color;
	active_sinn = 0;
	plus_z = 0;
}

void Chec::show() {

	float white_pieshka_dif[4] = { 1.2, 1.2, 1.2, 1.0 }, white_pieshka_amb[3] = { 0.5f, 0.5f, 0.5f }, white_pieshka_spec[3] = { 1.0f, 1.0f, 1.0f }, white_pieshka_shininess = 2.0f * 128;
	float black_pieshka_dif[4] = { 0.1, 0.1, 0.1, 1.0 }, black_pieshka_amb[3] = { 0.5f, 0.5f, 0.5f }, black_pieshka_spec[3] = { 1.0f, 1.0f, 1.0f }, black_pieshka_shininess = 2.0f * 128;
	float hod_pieshka_dif[4] = { 1.0, 1.0, 0.0, 1.0 }, hod_pieshka_amb[3] = { 0.5f, 0.5f, 0.5f }, hod_pieshka_spec[3] = { 1.0f, 1.0f, 1.0f }, hod_pieshka_shininess = 2.0f * 128;
	float take_pieshka_dif[4] = { 0, 0.902, 0, 1.0 }, take_pieshka_amb[3] = { 0.5f, 0.5f, 0.5f }, take_pieshka_spec[3] = { 1.0f, 1.0f, 1.0f }, take_pieshka_shininess = 2.0f * 128;
	float take_no_pieshka_dif[4] = { 0.8, 0.149, 0.149, 1.0 }, take_no_pieshka_amb[3] = { 0.5f, 0.5f, 0.5f }, take_no_pieshka_spec[3] = { 1.0f, 1.0f, 1.0f }, take_no_pieshka_shininess = 2.0f * 128;

	float white_pieshka1_dif[4] = { 0.75, 0.75, 0.75, 1.0 }, white_pieshka1_amb[3] = { 0.5f, 0.5f, 0.5f }, white_pieshka1_spec[3] = { 1.0f, 1.0f, 1.0f }, white_pieshka1_shininess = 2.0f * 128;
	float black_pieshka1_dif[4] = { 0.54, 0.27, 0.15, 1.0 }, black_pieshka1_amb[3] = { 0.5f, 0.5f, 0.5f }, black_pieshka1_spec[3] = { 1.0f, 1.0f, 1.0f }, black_pieshka1_shininess = 2.0f * 128;

	float white_pieshka2_dif[4] = { 0, 0.75, 1, 1.0 }, white_pieshka2_amb[3] = { 0.5f, 0.5f, 0.5f }, white_pieshka2_spec[3] = { 1.0f, 1.0f, 1.0f }, white_pieshka2_shininess = 2.0f * 128;
	float black_pieshka2_dif[4] = { 1, 0.07, 0.57, 1.0 }, black_pieshka2_amb[3] = { 0.5f, 0.5f, 0.5f }, black_pieshka2_spec[3] = { 1.0f, 1.0f, 1.0f }, black_pieshka2_shininess = 2.0f * 128;


	x_d = -5.6875 + (1.625*(x - 1)); y_d = -5.6875 + (1.625*(y - 1));
	if (active == 1) {
		glPushMatrix();

		if (take == 2) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, hod_pieshka_amb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, hod_pieshka_dif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, hod_pieshka_spec);
			glMaterialf(GL_FRONT, GL_SHININESS, hod_pieshka_shininess);
		}
		else {
			if (take == 1) {
				glMaterialfv(GL_FRONT, GL_AMBIENT, take_pieshka_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, take_pieshka_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, take_pieshka_spec);
				glMaterialf(GL_FRONT, GL_SHININESS, take_pieshka_shininess);
			}
			else {
				if (take == -1) {
					glMaterialfv(GL_FRONT, GL_AMBIENT, take_no_pieshka_amb);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, take_no_pieshka_dif);
					glMaterialfv(GL_FRONT, GL_SPECULAR, take_no_pieshka_spec);
					glMaterialf(GL_FRONT, GL_SHININESS, take_no_pieshka_shininess);
				}

				else {
					if (white_black == 1) {

						if (color == 1) {
							glMaterialfv(GL_FRONT, GL_AMBIENT, white_pieshka_amb);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, white_pieshka_dif);
							glMaterialfv(GL_FRONT, GL_SPECULAR, white_pieshka_spec);
							glMaterialf(GL_FRONT, GL_SHININESS, white_pieshka_shininess);
						}
						if (color == 2) {
							glMaterialfv(GL_FRONT, GL_AMBIENT, white_pieshka1_amb);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, white_pieshka1_dif);
							glMaterialfv(GL_FRONT, GL_SPECULAR, white_pieshka1_spec);
							glMaterialf(GL_FRONT, GL_SHININESS, white_pieshka1_shininess);
						}
						if (color == 3) {
							glMaterialfv(GL_FRONT, GL_AMBIENT, white_pieshka2_amb);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, white_pieshka2_dif);
							glMaterialfv(GL_FRONT, GL_SPECULAR, white_pieshka2_spec);
							glMaterialf(GL_FRONT, GL_SHININESS, white_pieshka2_shininess);
						}

					}
					if (white_black == -1) {
						if (color == 1) {
							glMaterialfv(GL_FRONT, GL_AMBIENT, black_pieshka_amb);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, black_pieshka_dif);
							glMaterialfv(GL_FRONT, GL_SPECULAR, black_pieshka_spec);
							glMaterialf(GL_FRONT, GL_SHININESS, black_pieshka_shininess);
						}
						if (color == 2) {
							glMaterialfv(GL_FRONT, GL_AMBIENT, black_pieshka1_amb);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, black_pieshka1_dif);
							glMaterialfv(GL_FRONT, GL_SPECULAR, black_pieshka1_spec);
							glMaterialf(GL_FRONT, GL_SHININESS, black_pieshka1_shininess);
						}
						if (color == 3) {
							glMaterialfv(GL_FRONT, GL_AMBIENT, black_pieshka2_amb);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, black_pieshka2_dif);
							glMaterialfv(GL_FRONT, GL_SPECULAR, black_pieshka2_spec);
							glMaterialf(GL_FRONT, GL_SHININESS, black_pieshka2_shininess);
						}
					}
				}

			}
		}
		glTranslated(x_d, y_d, 0.21 + plus_z);
		glutSolidTorus(0.2f, 0.6f, 40, 30);
		glBegin(GL_LINES);
		double yy = 0;
		double i = -0.6;
		while (i <= 0.6) {
			yy = sqrt(0.36 - (i*i));
			glVertex3f(i, yy, 0.2);
			glVertex3f(i, -yy, 0.2);
			i += 0.001;
		}
		glEnd();
		glTranslated(0.0, 0.0, 0.0);
		glPopMatrix();
	}
}
