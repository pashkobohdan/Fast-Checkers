#include "Header.h"


Game::Game() {
	loading_active = 1;
	menu_active = 0;
	pause_active = 0;
	angleY = 0;
	first_loading = 1;
	type_of_game = 1;
	game_active = 0;
	first_end = 1;
	game1 = Game_checker(menu.color_of_figure);

	r_time = clock();
	frames = 0;
	r_fps = 0;
	f[10];
}

void Game::show_game() {
	if (loading.active == 1) {
		loading.show_loading();
	}
	else {
		if (first_loading == 1) {
			menu_active = 1;
			menu.active = 1;
			first_loading = 0;
			loading_active = 0;
		}

		if (menu.active == 1) {
			menu.show_menu();
		}
		else {
			if (menu.change_angle == 1) {
				menu.change_angle = 0;
				moving_of_camera = 1;
				counter_moving = 30;
				moving_x_white = (-180 - angleX) / 30; moving_y_white = (-150 - angleY) / 30;
				moving_x_black = (-angleX) / 30; moving_y_black = (-30 - angleY) / 30;
				menu_active = 0;
				game_active = 1;
				game1 = Game_checker(menu.color_of_figure);
				game1.type_of_games = menu.type;
			}
			if (moving_of_camera == 1) {
				moving_camera();
			}

			if (pause.active == 1) {
				pause.show_pause();
			}
			else {

				if (game1.game_end == 0) {
					//std::cout << "sdvfsdf  ";

					game1.show_games();
				}
				else {
					if (game1.game_end == 1) {
						game1.show_games();
					}
					if (game1.end_exit == 1) {
						menu.active = 1;
						game_active = 0;
						menu_active = 1;
						game1.initi();
						menu.change_angle = 1;
						menu.cheker.active = 0;
					}
				}
			}



		}
	}
}

void Game::moving_camera() {
	if (game1.game_end < 1) {
		if (game1.turn == 1) {

			angleX += moving_x_white;
			angleY += moving_y_white;
			counter_moving--;
			if (counter_moving == 0) { moving_of_camera = 0; }
		}
		else {
			angleX += moving_x_black;
			angleY += moving_y_black;
			counter_moving--;
			if (counter_moving == 0) { moving_of_camera = 0; }
		}
	}
	else {
		if (first_end > 0) {
			first_end = 0;
			angleY = 0;
			angleX = 0;
		}
	}
}

void Game::record_data(int n) {
	std::ofstream f;

	switch (n) {
	case 1:f.open("save\\text1.ftr", std::ios::out);  break;
	case 2:f.open("save\\text2.ftr", std::ios::out); break;
	case 3:f.open("save\\text3.ftr", std::ios::out);  break;
	}

	if (f.is_open()) {
		//PlaySound(TEXT("music\\ok_save.wav"), NULL, SND_FILENAME);

		f << type_of_game << " ";
		f << game1.turn << " ";
		for (int i = 0; i < 24; i++) {
			f << game1.f[i].x << " " << game1.f[i].y << " " << game1.f[i].active << " " << game1.f[i].white_black << " ";
		}
		f << game1.gamer1_point << " ";
		f << game1.gamer2_point << " ";
		f << game1.figure_work;

		f.close();
	}
}

void Game::read_data(int n) {
	game1.color = menu.color_of_figure;
	game1.initi();
	std::ifstream fin;

	switch (n) {
	case 1:fin.open("save\\text1.ftr"); break;
	case 2:fin.open("save\\text2.ftr"); break;
	case 3:fin.open("save\\text3.ftr"); break;
	}

	if (fin.is_open()) {
		int x;
		fin >> x;
		game1.type_of_games = x;

		fin >> x;
		game1.turn = x;

		for (int i = 0; i < 24; i++) {
			fin >> x;
			game1.f[i].x = x;

			fin >> x;
			game1.f[i].y = x;

			fin >> x;
			game1.f[i].active = x;

			fin >> x;
			game1.f[i].white_black = x;

			game1.f[i].take = 0;
		}

		fin >> x;
		game1.gamer1_point = x;

		fin >> x;
		game1.gamer2_point = x;

		fin >> x;
		game1.figure_work = x;
		game1.f[game1.figure_work].take = game1.ability_turn(game1.figure_work);
		game1.xx = game1.f[game1.figure_work].x;
		game1.yy = game1.f[game1.figure_work].y;

		fin.close();
		game1.color = menu.color_of_figure;

	}
	else {

	}
}

void Game::fps_time_game() {
	char f[10];
	glColor3d(0, 0, 0.5);
	char *c;
	if (menu.fps == 1) {
		sprintf(f, "%d", r_fps);
		renderText("fps : ", -14.5, -8);
		renderText(f);
	}
	if (menu.time == 1) {
		renderText("min : ", 11, -8);
		sprintf(f, "%d", int(r_time / 60000));
		renderText(f);
		renderText("   sec : ");
		sprintf(f, "%d", int((r_time / 1000) % 60));
		renderText(f);
	}

	game1.output_points();
}

void Game::on_paint()
{

	GLfloat light_ambient[4] = { 0.0f, 0.0f, 0.0f, 1.0f }, light_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f }, light_specular[4] = { 0.6, 0.6f, 0.6, 1.0f }, light_position[4] = { 0.6f, 0.6f, 1.2f, 0.0f };

	glViewport(0, 0, width, height);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glClearColor(0.3, 0.9, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (GLfloat)width / height, 1, 100);// задаємо усічений конус видимості

	glMatrixMode(GL_MODELVIEW);// включаємо режим роботи з видовою матрицею
	glLoadIdentity();

	glTranslatef(0, 0, distZ);  // камера з початку координат зсувається на distZ, 


	if (game_active == 1) {
		fps_time_game();
	}

	glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // потім повертається по осі Oy
	glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // потім повертається по осі Ox

	glEnable(GL_DEPTH_TEST);  // включаємо буфер глибини

							  ////////////////////////////////////////    Loading !!!

	if (loading_active == 1 || menu_active == 1 || game1.game_end == 1 || pause.active == 1) {
		show_game();
	}

	frames++;
	if (clock() - r_time >= 1000) {
		r_fps = frames;
		r_time = clock();
		frames = 0;
	}

	if (menu.active == 1) {
		if (menu.time == 1) {
			glColor3d(0, 0, 0.5);
			glLineWidth(1.5f);

			renderStrokeFontString(10, -7, 0.2, "min ", 0.004);
			sprintf(f, "%d", int(r_time / 60000));
			renderStrokeFontString(11, -7, 0.2, f, 0.005);

			renderStrokeFontString(12, -7, 0.2, "sec ", 0.004);
			sprintf(f, "%d", int((r_time / 1000) % 60));
			renderStrokeFontString(13, -7, 0.2, f, 0.005);
		}

		if (menu.fps == 1) {
			sprintf(f, "%d", r_fps);
			glColor3d(0, 0, 0.5);
			glLineWidth(1.5f);
			renderStrokeFontString(-13, -7, 0.2, f, 0.005);
		}
	}


	////////////////////////////////////////


	glEnable(GL_LIGHTING);   // включаємо режим для установки освітлення
	glEnable(GL_LIGHT0);     // додаємо джерело світла № 0 (їх може бути до 8), зараз він світить з "очей"

							 ////





	if (menu.active == 0 && loading_active == 0 && game1.game_end == 0 && pause.active == 0) {


		show_game();

	}


	////

	glDisable(GL_LIGHT0);// вимкнемо все, що включили
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glFlush();
	glutSwapBuffers(); // перемикання буферів
}

void Game::on_keyboard(unsigned char key, int x, int y) //обробка події від клавіатури
{
	//std::cout << int(key) << "\n";
	switch (key) {

	case 27:if (menu_active == 1 && menu.active == 1) { menu.exid.take = 1; menu.games.take = 0; menu.setings.take = 0; menu.helps.take = 0; menu.rules1.take = 0; menu.rules2.take = 0; menu.rules3.take = 0; }
			if (game_active == 1 && menu.active == 0) { menu_active = 0; game_active = 0; menu.active = 0; pause.active = 1; angleX = 0; angleY = 0; }
			break;
	case 97: if (game1.turn == -1)game1.selection_left();   else { game1.selection_right(); } break;
	case 119:if (game1.turn == -1)game1.selection_up();     else { game1.selection_down(); } break;
	case 100:if (game1.turn == -1)game1.selection_right();  else { game1.selection_left(); } break;
	case 115:if (game1.turn == -1)game1.selection_down();   else { game1.selection_up(); }   break;

	case 244:if (game1.turn == -1)game1.selection_left();   else { game1.selection_right(); }break;
	case 246:if (game1.turn == -1)game1.selection_up();     else { game1.selection_down(); } break;
	case 226:if (game1.turn == -1)game1.selection_right();  else { game1.selection_left(); } break;
	case 251:if (game1.turn == -1)game1.selection_down();   else { game1.selection_up(); }   break;

	case 52:angleX += 3;
		while (angleX >= 360) { angleX -= 360; }
		while (angleY >= 360) { angleY -= 360; }
		while (angleX <= -360) { angleX += 360; }
		while (angleY <= -360) { angleY += 360; }break;

	case 54:angleX -= 3;
		while (angleX >= 360) { angleX -= 360; }
		while (angleY >= 360) { angleY -= 360; }
		while (angleX <= -360) { angleX += 360; }
		while (angleY <= -360) { angleY += 360; }break;

	case 56:if (angleX >= 90 && angleX <= 270)angleY -= 3; else angleY += 3;  break;
	case 50:if (angleX >= 90 && angleX <= 270)angleY += 3; else angleY -= 3; break;

	case 113: if ((game1.ability_turn(game1.figure_work) == 1) || (game1.ability_turn(game1.figure_work) == 2)) {
		game1.turn_of_gamers(-1);
		moving_of_camera = 1;
		counter_moving = 30;
		moving_x_white = (-180 - angleX) / 30; moving_y_white = (-150 - angleY) / 30;
		moving_x_black = (-angleX) / 30; moving_y_black = (-30 - angleY) / 30;
	}
			  break;
	case 101: if ((game1.ability_turn(game1.figure_work) == 1) || (game1.ability_turn(game1.figure_work) == 2)) {
		game1.turn_of_gamers(1);
		moving_of_camera = 1;
		counter_moving = 30;
		moving_x_white = (-180 - angleX) / 30; moving_y_white = (-150 - angleY) / 30;
		moving_x_black = (-angleX) / 30; moving_y_black = (-30 - angleY) / 30;
	}
			  break;

	case 233:if ((game1.ability_turn(game1.figure_work) == 1) || (game1.ability_turn(game1.figure_work) == 2)) {
		game1.turn_of_gamers(-1);
		moving_of_camera = 1;
		counter_moving = 30;
		moving_x_white = (-180 - angleX) / 30; moving_y_white = (-150 - angleY) / 30;
		moving_x_black = (-angleX) / 30; moving_y_black = (-30 - angleY) / 30;
	}
			 break;

	case 243: if ((game1.ability_turn(game1.figure_work) == 1) || (game1.ability_turn(game1.figure_work) == 2)) {
		game1.turn_of_gamers(1);
		moving_of_camera = 1;
		counter_moving = 30;
		moving_x_white = (-180 - angleX) / 30; moving_y_white = (-150 - angleY) / 30;
		moving_x_black = (-angleX) / 30; moving_y_black = (-30 - angleY) / 30;
	}
			  break;

	case 32:if (game_active == 1) {
		if (game1.turn == -1) {
			angleX = 0;
			angleY = -30;
		}
		else {
			angleX = -180;
			angleY = -150;
		}
	}break;

	}
}

void Game::on_motion(int x, int y)
{
	//	std::cout << angleX<<"    "<<g.angleY<<"\n";

	if (loading_active < 1 && menu.active<1 && game1.game_end<1 && pause.active<1) {
		switch (button) {
		case 0:
			angleX += x - mouseX;
			angleY += y - mouseY;
			while (angleX >= 360) { angleX -= 360; }
			while (angleY >= 360) { angleY -= 360; }
			while (angleX <= -360) { angleX += 360; }
			while (angleY <= -360) { angleY += 360; }
			mouseX = x;
			mouseY = y;

			break;
		}
	}
	else {
		if (menu_active == 1 || game1.game_end == 1 || pause.active == 1) {
			angleX = -(10.0*x - 5.0*width) / width;
			angleY = -(10.0 * y - 5.0 * height) / height;

		}
	}

}

void Game::on_mouse(int _button, int state, int x, int y)
{
	if (state == 1) {
		kn = 0;
		button = -1;
		return;
	}
	else {
		switch (button = _button) {
		case 0: mouseX = x; mouseY = y; if (menu_active == 1) { menu.pressure(); } if (game1.game_end == 1) { game1.end.pressure(); }
				if (menu.active == 1 && menu.games.take == 1) {
					if (menu.down1.active == 1 || menu.down2.active == 1 || menu.down3.active == 1) {
						menu.active = 0;
						menu_active = 0;
						game_active = 1;
						moving_of_camera = 1;
						counter_moving = 30;
						moving_x_white = (-180 - angleX) / 30; moving_y_white = (-150 - angleY) / 30;
						moving_x_black = (-angleX) / 30; moving_y_black = (-30 - angleY) / 30;

						if (menu.down1.active == 1) {
							read_data(1);
						}
						else {
							if (menu.down2.active == 1) {
								read_data(2);
							}
							else {
								if (menu.down3.active == 1) {
									read_data(3);
								}
							}
						}
					}
				}

				if (pause.active == 1) {
					if (pause.file1.active == 1) {
						record_data(1);
					}
					else {
						if (pause.file2.active == 1) { record_data(2); }
						else {
							if (pause.file3.active == 1) { record_data(3); }
						}
					}

					if (pause.exit_to_menu.active == 1) {
						menu_active = 1;
						menu.active = 1;
						pause.active = 0;
						game_active = 1;
					}

					if (pause.resume.active == 1) {
						pause.active = 0;
						game_active = 1;

						moving_of_camera = 1;
						counter_moving = 30;
						moving_x_white = (-180 - angleX) / 30; moving_y_white = (-150 - angleY) / 30;
						moving_x_black = (-angleX) / 30; moving_y_black = (-30 - angleY) / 30;
					}

				}

				break;
		}
	}

}

void Game::on_mouse_passive(int x, int y) {

	if (menu_active == 1) {
		angleX = -(10.0*x - 5.0*width) / width;
		angleY = -(10.0 * y - 5.0 * height) / height;
		this->menu.prov_buttons(x, y, width, height);
	}
	else {
		if (game1.game_end == 1) {
			angleX = -(10.0*x - 5.0*width) / width;
			angleY = -(10.0 * y - 5.0 * height) / height;
			this->game1.end.prov_buttons(x, y, width, height);
		}
		else {
			if (pause.active == 1) {
				angleX = -(10.0*x - 5.0*width) / width;
				angleY = -(10.0 * y - 5.0 * height) / height;
				this->pause.prov_buttons(x, y, width, height);
			}
		}
	}
	//std::cout << width << "   " << height << "\n";

}

void Game::on_size(int w, int h)
{
	width = w;
	height = h;
	if (height == 0) height = 1;
}

