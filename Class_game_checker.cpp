#include "Header.h"

Game_checker::Game_checker(int color) {
	this->color = color;
	initi();
}

void Game_checker::initi() {
	int figure_pos[8][8] = {
		{ -1, 0, -1, 0, -1, 0, -1, 0 },
		{ 0, -1, 0, -1, 0, -1, 0, -1 },
		{ -1, 0, -1, 0, -1, 0, -1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0, 1, 0, 1 } };

	int fc = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (figure_pos[j][i] == 1) { f[fc] = Chec(i + 1, j + 1, 1, color); fc++; }
			if (figure_pos[j][i] == -1) { f[fc] = Chec(i + 1, j + 1, -1, color); fc++; }
		}
	}

	for (int i = 0; i < 24; i++) {
		f[i].take = 0;
		f[i].active = 1;
	}

	delete_figure = -1;
	turn = -1;
	vector_turn = 0;


	gamer1_point = 0;
	gamer2_point = 0;
	game_end = 0;
	gamer_win = -1;
	end_exit = 0;
	end.active = 1;
	end.winner = -1;

	selection_new_figure();
	f[figure_work].take = ability_turn(figure_work);

	sinn = 0;
}

void Game_checker::show_board() {

	float white_doska_dif[4] = { 0.9, 0.9, 0.9, 1.0 }, white_doska_amb[3] = { 0.5f, 0.5f, 0.5f }, white_doska_spec[3] = { 1.0f, 1.0f, 1.0f }, white_doska_shininess = 0.5f * 128;
	float black_doska_dif[4] = { 0.54, 0.27, 0.074, 1.0 }, black_doska_amb[3] = { 0.5f, 0.5f, 0.5f }, black_doska_spec[3] = { 1.0f, 1.0f, 1.0f }, black_doska_shininess = 1.0f * 128;
	float black_pieshka_dif[4] = { 0.1, 0.1, 0.1, 1.0 }, black_pieshka_amb[3] = { 0.5f, 0.5f, 0.5f }, black_pieshka_spec[3] = { 1.0f, 1.0f, 1.0f }, black_pieshka_shininess = 2.0f * 128;


	glPushMatrix();

	glBegin(GL_QUADS);

	glMaterialfv(GL_FRONT, GL_AMBIENT, black_pieshka_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black_pieshka_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black_pieshka_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, black_pieshka_shininess);

	glVertex3f(-6.5, -6.5, 0);  glVertex3f(-6.5, 6.5, 0);  glVertex3f(-6.5, 6.5, -1);  glVertex3f(-6.5, -6.5, -1);
	glVertex3f(-6.5, -6.5, 0);  glVertex3f(6.5, -6.5, 0); glVertex3f(6.5, -6.5, -1); glVertex3f(-6.5, -6.5, -1);
	glVertex3f(-6.5, 6.5, 0); glVertex3f(6.5, 6.5, 0); glVertex3f(6.5, 6.5, -1); glVertex3f(-6.5, 6.5, -1);
	glVertex3f(6.5, 6.5, 0); glVertex3f(6.5, -6.5, 0); glVertex3f(6.5, -6.5, -1); glVertex3f(6.5, 6.5, -1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, black_pieshka_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black_pieshka_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black_pieshka_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, black_pieshka_shininess);

	glVertex3f(-6.5, -6.5, -1); glVertex3f(-6.5, 6.5, -1); glVertex3f(6.5, 6.5, -1); glVertex3f(6.5, -6.5, -1);

	float x = -6.5, y = -6.5;
	for (int i = 0; i < 8; i++) {
		for (int q = 0; q < 8; q++) {
			if ((i + q) % 2 == 0) {
				glMaterialfv(GL_FRONT, GL_AMBIENT, black_doska_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, black_doska_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, black_doska_spec);
				glMaterialf(GL_FRONT, GL_SHININESS, black_doska_shininess);
				glPushMatrix();
				glVertex3f(x, y, 0);  glVertex3f(x, y + 1.625, 0);  glVertex3f(x + 1.625, y + 1.625, 0);  glVertex3f(x + 1.625, y, 0);
				glPopMatrix();
			}
			else {
				glMaterialfv(GL_FRONT, GL_AMBIENT, white_doska_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, white_doska_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, white_doska_spec);
				glMaterialf(GL_FRONT, GL_SHININESS, white_doska_shininess);
				glPushMatrix();
				glVertex3f(x, y, 0);  glVertex3f(x, y + 1.625, 0);  glVertex3f(x + 1.625, y + 1.625, 0);  glVertex3f(x + 1.625, y, 0);
				glPopMatrix();
			} x += 1.625;
		} y += 1.625; x = -6.5;
	}
	glEnd();

	glPopMatrix();
}

void Game_checker::show_games() {
	sinn += 0.5;
	if (sinn >= 360) { sinn -= 360; }
	if (game_end == 0) {
		show_board();
		for (int i = 0; i < 24; i++) {
			if (i == figure_work) { f[i].plus_z = sin(sinn / 3.14159) / 3.0 + 0.2; }
			else { f[i].plus_z = 0; }
			f[i].show();
		}
	}
	else {
		if (end.active == 1) {
			end.show_end();
		}
		else {
			end_exit = 1;
		}
	}


}

int Game_checker::figure_in_coordinate(int x, int y) {
	for (int i = 0; i < 24; i++) {
		if (f[i].active == 1 && f[i].x == x && f[i].y == y) { return i; }
	}
	return -1;
}
int Game_checker::availability_figure(int x, int y) {
	for (int q = 0; q < 24; q++) {
		if ((f[q].x == x) && (f[q].y == y) && (f[q].active == 1)) { return f[q].white_black; break; }
	}
	return 0;
}
int Game_checker::need_turn(int i) {
	x_hod = -1;
	y_hod = -1;
	delete_figure = -1;
	vector_turn = 0;
	if (f[i].white_black == -1) {
		if (f[i].y >= 7) { return 0; }
		else {
			if (f[i].x <= 2) {
				if (availability_figure(f[i].x + 1, f[i].y + 1) == (-1)*f[i].white_black && availability_figure(f[i].x + 2, f[i].y + 2) == 0) {
					delete_figure = figure_in_coordinate(f[i].x + 1, f[i].y + 1);
					x_hod = f[i].x + 2;
					y_hod = f[i].y + 2;
					vector_turn = 1;
					return 1;
				}
			}
			else {
				if (f[i].x >= 7) {
					if (availability_figure(f[i].x - 1, f[i].y + 1) == (-1)*f[i].white_black && availability_figure(f[i].x - 2, f[i].y + 2) == 0) {
						delete_figure = figure_in_coordinate(f[i].x - 1, f[i].y + 1);
						x_hod = f[i].x - 2;
						y_hod = f[i].y + 2;
						vector_turn = -1;
						return 1;
					}
				}
				else {
					if (availability_figure(f[i].x - 1, f[i].y + 1) == (-1)*f[i].white_black && availability_figure(f[i].x - 2, f[i].y + 2) == 0) {
						delete_figure = figure_in_coordinate(f[i].x - 1, f[i].y + 1);
						x_hod = f[i].x - 2;
						y_hod = f[i].y + 2;
						vector_turn = -1;
						return 1;
					}
					if (availability_figure(f[i].x + 1, f[i].y + 1) == (-1)*f[i].white_black && availability_figure(f[i].x + 2, f[i].y + 2) == 0) {
						delete_figure = figure_in_coordinate(f[i].x + 1, f[i].y + 1);
						x_hod = f[i].x + 2;
						y_hod = f[i].y + 2;
						vector_turn = 1;
						return 1;
					}
					return 0;
				}
			}
		}
	}



	else {
		if (f[i].y <= 2) { return 0; }
		else {
			if (f[i].x <= 2) {
				if (availability_figure(f[i].x + 1, f[i].y - 1) == (-1)*f[i].white_black && availability_figure(f[i].x + 2, f[i].y - 2) == 0) {
					delete_figure = figure_in_coordinate(f[i].x + 1, f[i].y - 1);
					x_hod = f[i].x + 2;
					y_hod = f[i].y - 2;
					vector_turn = 1;
					return 1;
				}
			}
			else {
				if (f[i].x >= 7) {
					if (availability_figure(f[i].x - 1, f[i].y - 1) == (-1)*f[i].white_black && availability_figure(f[i].x - 2, f[i].y - 2) == 0) {
						delete_figure = figure_in_coordinate(f[i].x - 1, f[i].y - 1);
						x_hod = f[i].x - 2;
						y_hod = f[i].y - 2;
						vector_turn = -1;
						return 1;
					}
				}
				else {
					if (availability_figure(f[i].x - 1, f[i].y - 1) == (-1)*f[i].white_black && availability_figure(f[i].x - 2, f[i].y - 2) == 0) {
						delete_figure = figure_in_coordinate(f[i].x - 1, f[i].y - 1);
						x_hod = f[i].x - 2;
						y_hod = f[i].y - 2;
						vector_turn = -1;
						return 1;
					}
					if (availability_figure(f[i].x + 1, f[i].y - 1) == (-1)*f[i].white_black && availability_figure(f[i].x + 2, f[i].y - 2) == 0) {
						delete_figure = figure_in_coordinate(f[i].x + 1, f[i].y - 1);
						x_hod = f[i].x + 2;
						y_hod = f[i].y - 2;
						vector_turn = 1;
						return 1;
					}
					return 0;
				}
			}
		}
	}
}
int Game_checker::ability_turn(int i) {


	if (need_turn(i) == 1) { return 2; }


	if ((turn == -1) && (f[i].y >= 8)) { return -1; }
	if ((turn == 1) && (f[i].y <= 1)) { return -1; }



	if (f[i].x == 1) {
		for (int j = 0; j < 24; j++) {
			if ((f[i].x + 1 == f[j].x) && (f[i].y - turn == f[j].y) && (f[i].active == 1) && (f[j].active == 1)) { return -1; }
		}
		return 1;
	}


	if (f[i].x == 8) {
		for (int j = 0; j < 24; j++) {

			if ((f[i].x - 1 == f[j].x) && (f[i].y - turn == f[j].y) && (f[i].active == 1) && (f[j].active == 1)) { return -1; }
		}
		return 1;
	}

	int res = 0;
	for (int j = 0; j < 24; j++) {

		if (((f[i].x + 1 == f[j].x) || (f[i].x - 1 == f[j].x)) && ((f[i].y - turn == f[j].y) && (f[i].active == 1) && (f[j].active == 1))) { res++; }
	}
	if (res == 2) { return -1; }
	else { return 1; }
}

void Game_checker::selection_new_figure() {
	int w = 0;

	for (int i = 0; i < 24; i++) {
		f[i].take = 0;
	}

	for (int i_x = 1; i_x < 9; i_x++) {
		for (int i_y = 1; i_y < 9; i_y++) {
			for (int q = 0; q < 24; q++) {

				if ((f[q].x == i_x) && (f[q].y == i_y) && (f[q].white_black == turn) && (f[q].active == 1))
				{
					f[q].take = ability_turn(q);
					xx = f[q].x;
					yy = f[q].y;
					figure_work = q;
					w++;
					break;

				}
			}
			if (w == 1) { break; }
		}
		if (w == 1) { break; }
	}
}

void Game_checker::selection_left() {

	int wyh = 0;

	for (int i = 0; i < 24; i++) {
		f[i].take = 0;
	}

	while (wyh == 0) {
		xx--;
		if (xx == 0) { yy--; xx = 8; }
		if (yy == 0) { yy = 8; }
		for (int i = 0; i < 24; i++) {
			if ((f[i].x == xx) && (f[i].y == yy) && (f[i].white_black == turn) && (f[i].active == 1)) {
				f[i].take = ability_turn(i);
				wyh++;
				figure_work = i;
				break;
			}
		}
	}
}
void Game_checker::selection_up() {
	int wyh = 0;

	for (int i = 0; i < 24; i++) {
		f[i].take = 0;
	}

	while (wyh == 0) {
		yy++;
		if (yy == 9) { yy = 1; xx++; }
		if (xx == 9) { xx = 1; }
		for (int i = 0; i < 24; i++) {
			if ((f[i].x == xx) && (f[i].y == yy) && (f[i].white_black == turn) && (f[i].active == 1)) {
				f[i].take = ability_turn(i);
				figure_work = i;
				wyh++;
				break;
			}
		}
	}
}
void Game_checker::selection_right() {
	int wyh = 0;

	for (int i = 0; i < 24; i++) {
		f[i].take = 0;
	}

	while (wyh == 0) {
		xx++;
		if (xx == 9) { yy++; xx = 1; }
		if (yy == 9) { yy = 1; }
		for (int i = 0; i <24; i++) {
			if ((f[i].x == xx) && (f[i].y == yy) && (f[i].white_black == turn) && (f[i].active == 1)) {
				figure_work = i;
				f[i].take = ability_turn(i);
				wyh++;
				break;
			}
		}
	}
}
void Game_checker::selection_down() {
	int wyh = 0;
	for (int i = 0; i < 24; i++) {
		f[i].take = 0;
	}
	while (wyh == 0) {
		yy--;
		if (yy == 0) { yy = 8; xx--; }
		if (xx == 0) { xx = 8; }
		for (int i = 0; i < 24; i++) {
			if ((f[i].x == xx) && (f[i].y == yy) && (f[i].white_black == turn) && (f[i].active == 1)) {
				figure_work = i;
				f[i].take = ability_turn(i);
				wyh++;
				break;
			}
		}
	}
}

void Game_checker::turn_of_gamers(int left_right) {
	int yspeh_hoda = 0;

	for (int i = 0; i < 24; i++) {
		f[i].need_of_turn = need_turn(i);
	}

	if (ability_turn(figure_work) == 2) {

		if (vector_turn == turn *(-left_right)) {

			f[delete_figure].active = 0;
			if (f[delete_figure].white_black == -1) { gamer2_point++; }
			else { gamer1_point++; }
			f[figure_work].x = x_hod;
			f[figure_work].y = y_hod;
			if (need_turn(figure_work) == 0) { yspeh_hoda += 1; }


		}

	}

	else {
		if (ability_turn(figure_work) == 1) {
			if (f[figure_work].x == 1) {
				f[figure_work].x = 2;
				f[figure_work].y -= turn;
				yspeh_hoda++;
			}
			else {
				if (f[figure_work].x == 8) {
					f[figure_work].x = 7;
					f[figure_work].y -= turn;
					yspeh_hoda++;
				}
				else {
					if (left_right == -1) {
						int wyhid = 0;
						for (int i = 0; i < 24; i++) {
							if ((f[figure_work].x + turn == f[i].x) && (f[figure_work].y - turn == f[i].y) && (f[i].active == 1)) { wyhid++; break; }
						}
						if (wyhid == 0) {
							f[figure_work].x += turn;
							f[figure_work].y -= turn;
							yspeh_hoda++;
						}
					}

					else {
						int wyhid = 0;
						for (int i = 0; i < 24; i++) {
							if ((f[figure_work].x - turn == f[i].x) && (f[figure_work].y - turn == f[i].y) && (f[i].active == 1)) { wyhid++; break; }
						}
						if (wyhid == 0) {
							f[figure_work].x -= turn;
							f[figure_work].y -= turn;
							yspeh_hoda++;
						}
					}
				}
			}
		}



	}


	if (yspeh_hoda > 0) {

		for (int i = 0; i < 24; i++) {
			if (f[i].active == 1 && need_turn(i) == 1 && f[i].white_black == turn && i != figure_work && f[i].need_of_turn == 1) { f[i].active = 0; if (f[i].white_black == -1) { gamer2_point++; } else { gamer1_point++; }break; }
		}
		//std::cout << "\n\n\nyes    "<<turn << "\n";
		turn *= -1;

		//	std::cout << "yes2    " << turn << "\n";



		if (type_of_games == 1) {
			if (gamer1_point > 11) { game_end = 1; gamer_win = 1; end.winner = -1; }
			if (gamer2_point > 11) { game_end = 1; gamer_win = -1; end.winner = 1; }

			for (int i = 0; i < 24; i++) {
				if (f[i].white_black == -1 && f[i].y == 8 && f[i].active == 1) { game_end = 1; gamer_win = -1; end.winner = -1; }
				if (f[i].white_black == 1 && f[i].y == 1 && f[i].active == 1) { game_end = 1; gamer_win = 1; end.winner = 1; }
			}
		}
		else {
			if (gamer1_point > 11) { game_end = 1; gamer_win = -1; end.winner = 1; }
			if (gamer2_point > 11) { game_end = 1; gamer_win = 1; end.winner = -1; }

			for (int i = 0; i < 24; i++) {
				if (f[i].white_black == -1 && f[i].y == 8 && f[i].active == 1) { game_end = 1; gamer_win = 1; end.winner = 1; }
				if (f[i].white_black == 1 && f[i].y == 1 && f[i].active == 1) { game_end = 1; gamer_win = -1; end.winner = -1; }
			}
		}




		f[figure_work].take = ability_turn(figure_work);
		selection_new_figure();
	}
}

void Game_checker::output_points() {
	if (game_end == 0) {
		char f[4];
		char *c;



		if (color == 1) {
			renderText("White : ", -14.5, 8);
		}
		else {
			if (color == 2) {
				renderText("Dark : ", -14.5, 8);
			}
			else {
				if (color == 3) {
					renderText("Blue : ", -14.5, 8);
				}
			}
		}
		sprintf(f, "%d", gamer2_point);
		renderText(f);
		renderText("   ", 12, 8);

		if (color == 1) {
			renderText("Black : ");
		}
		else {
			if (color == 2) {
				renderText("Brown : ");
			}
			else {
				renderText("Pink : ");
			}
		}

		sprintf(f, "%d", gamer1_point);
		renderText(f);

		renderText("Type : ", -2, 8);



		if (type_of_games == 1) {
			renderText("Checker");
		}
		else {
			renderText("Poddavki");
		}
	}
}


