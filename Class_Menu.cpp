#include "Header.h"

Menu::Menu() {
	change_angle = 0;

	active = 0;
	games = Button(1, -11, 4, -7, 5, "  Game", 1);
	setings = Button(1, -11, 2, -7, 3, "  Setings", 1);
	helps = Button(1, -11, 0, -7, 1, "  Help", 1);
	exid = Button(1, -11, -2, -7, -1, "  Exit", 1);

	cheker = Button(0, 2, 2.5, 7, 4, "  Checkers", 2);
	poddavki = Button(0, 2, 0.5, 7, 2, "  Poddavki", 2);
	four_four = Button(0, 2, -1.5, 7, 0, "   4x4", 2);

	down1 = Button(0, 0.5, -5, 2.5, -4, "File 1", 1);
	down2 = Button(0, 3.5, -5, 5.5, -4, "File 2", 1);
	down3 = Button(0, 6.5, -5, 8.5, -4, "File 3", 1);


	exit_yes = Button(0, -2, -4, 3, -2.5, "   Yes", 2);
	exit_no = Button(0, 4, -4, 9, -2.5, "    No", 2);

	rules1 = Button(0, -5, -6, -1, -5, " Checkers", 1);
	rules2 = Button(0, 0, -6, 4, -5, " Poddavki", 1);
	rules3 = Button(0, 5, -6, 9, -5, " Control", 1);
	rules1.take = 1;

	color_black = Button(0, 5, 3, 10, 4, " Black-White", 1);
	color_dark = Button(0, 5, 1, 10, 2, "  Brown-Grey", 1);
	color_blue = Button(0, 5, -1, 10, 0, "  Blue-Pink", 1);
	color_of_figure = 1;
	color_black.take = 1;


	fps_off = Button(0, 5, -4, 7, -3, " Off", 1);
	fps_on = Button(0, 8, -4, 10, -3, " On", 1);
	fps = 0;
	fps_off.take = 1;


	time_off = Button(0, 5, -6, 7, -5, " Off", 1);
	time_on = Button(0, 8, -6, 10, -5, " On", 1);
	time_off.take = 1;
	time = 0;


	vsync60 = Button(0, 5, -2.5, 7, -1.5, " 60", 1);
	vsync120 = Button(0, 8, -2.5, 10, -1.5, " 120", 1);
	vsync120.take = 1;;
	vsync = 8;
}

void Menu::show_menu() {
	glColor3d(0.3, 0.9, 0.6);


	glBegin(GL_QUADS);
	glVertex3d(-30, -30, 0);
	glVertex3d(-30, 30, 0);
	glVertex3d(30, 30, 0);
	glVertex3d(30, -30, 0);
	glEnd();


	glColor3d(1, 0, 0);

	if (games.take == 1) {
		cheker.off_on = 1;
		poddavki.off_on = 1;
		four_four.off_on = 1;

		down1.off_on = 1;
		down2.off_on = 1;
		down3.off_on = 1;

		glColor3d(0.4, 0, 0);
		renderStrokeFontString(2, 5.5, 0.2, "  Game", 0.006);

		cheker.show_button();
		poddavki.show_button();
		//four_four.show_button();

		glColor3d(0.4, 0, 0);
		renderStrokeFontString(2.5, -3.6, 0.2, "Loading", 0.006);
		down1.show_button();
		down2.show_button();
		down3.show_button();

	}
	else {
		cheker.off_on = 0;
		poddavki.off_on = 0;
		four_four.off_on = 0;

		down1.off_on = 0;
		down2.off_on = 0;
		down3.off_on = 0;
	}


	if (helps.take == 1) {                            ////// helps menu !!!
		rules1.off_on = 1;
		rules2.off_on = 1;
		rules3.off_on = 1;
		glColor3d(0.4, 0, 0);
		renderStrokeFontString(0, 5.5, 0.2, "Game rules", 0.006);

		rules1.show_button();
		if (rules1.take == 1) {
			glColor3d(0.4, 0.4, 0);
			renderStrokeFontString(-4.5, 3, 0.2, "To win destroy all opponent's pieces or ", 0.006);
			renderStrokeFontString(-4.5, 1.6, 0.2, "  reaching the end of the board.", 0.006);
			renderStrokeFontString(-4.5, 0, 0.2, "Allowed to move in diagonal directions ", 0.006);
			renderStrokeFontString(-4.5, -1.4, 0.2, "  to the enemy.", 0.006);
		}
		rules2.show_button();
		if (rules2.take == 1) {
			glColor3d(0.4, 0.4, 0);
			renderStrokeFontString(-4.5, 2, 0.2, "Lose to win by the rules of checkers.", 0.006);
		}
		rules3.show_button();
		if (rules3.take == 1) {
			glColor3d(0.4, 0.4, 0);
			renderStrokeFontString(-4.5, 2, 0.2, "To select a new figure press a, w, d, s.", 0.006);
			renderStrokeFontString(-4.5, 0, 0.2, "Press q to move left.", 0.006);
			renderStrokeFontString(-4.5, -2, 0.2, "Press e to move right.", 0.006);
		}
	}
	else {
		rules1.off_on = 0;
		rules2.off_on = 0;
		rules3.off_on = 0;
	}



	if (exid.take == 1) {                              /////  exit menu !!!
		exit_yes.off_on = 1;
		exit_no.off_on = 1;

		glColor3d(0.4, 0, 0);
		renderStrokeFontString(1.5, 5.5, 0.2, "  Exit", 0.006);
		glColor3d(0, 0.4, 0);
		renderStrokeFontString(0, 2, 0.2, "You want to exit ?", 0.006);

		exit_yes.show_button();
		exit_no.show_button();
	}
	else {
		exit_yes.off_on = 0;
		exit_no.off_on = 0;
	}

	if (setings.take == 1) {							/////  setings menu !!!
		glColor3d(0.4, 0, 0);
		renderStrokeFontString(1.5, 5.5, 0.2, "Setings", 0.006);
		glColor3d(0, 0.4, 0);
		renderStrokeFontString(-4.5, 1.5, 0.2, "Choose the color", 0.006);
		renderStrokeFontString(-4.5, 0, 0.2, "of figures", 0.006);
		renderStrokeFontString(2, -3.8, 0.2, "FPS", 0.006);
		renderStrokeFontString(1.8, -5.8, 0.2, "Time", 0.006);
		renderStrokeFontString(1.8, -2.3, 0.2, "VSync", 0.006);

		fps_off.off_on = 1;
		fps_on.off_on = 1;
		color_black.off_on = 1;
		color_blue.off_on = 1;
		color_dark.off_on = 1;
		time_off.off_on = 1;
		time_on.off_on = 1;
		vsync60.off_on = 1;
		vsync120.off_on = 1;

		color_black.show_button();
		color_blue.show_button();
		color_dark.show_button();
		fps_off.show_button();
		fps_on.show_button();
		time_off.show_button();
		time_on.show_button();
		vsync60.show_button();
		vsync120.show_button();
	}
	else {
		color_black.off_on = 0;
		color_blue.off_on = 0;
		color_dark.off_on = 0;
		fps_off.off_on = 0;
		fps_on.off_on = 0;
		time_off.off_on = 0;
		time_on.off_on = 0;
		vsync60.off_on = 0;
		vsync120.off_on = 0;
	}

	games.show_button();
	setings.show_button();
	helps.show_button();
	exid.show_button();


	glColor3d(0.5, 0, 0);
	glLineWidth(2.0f);
	renderStrokeFontString(-3, -7.9, 0.2, "Fast-Checkers", 0.007);
}

void Menu::prov_buttons(int x, int y, int w, int h) {
	double xx = double(x);
	double yy = double(y);

	//std::cout << games.active << "   " << setings.active << "   " << helps.active << "   " << exid.active << "   \n";


	//	std::cout<<"   "<< double(xx / w) <<  "  "  << double(yy / h) << "\n";
	if (active == 1) {
		if (double(xx / w) >= 0.11706 && double(xx / w) <= 0.26793 && double(yy / h) >= 0.19401 && double(yy / h) <= 0.25781) { games.active = 1; }
		else { games.active = 0; }

		if (double(xx / w) >= 0.12152 && double(xx / w) <= 0.2657 && double(yy / h) >= 0.31901 && double(yy / h) <= 0.38151) { setings.active = 1; }
		else { setings.active = 0; }

		if (double(xx / w) >= 0.12298 && double(xx / w) <= 0.26647 && double(yy / h) >= 0.44140 && double(yy / h) <= 0.5) { helps.active = 1; }
		else { helps.active = 0; }

		if (double(xx / w) >= 0.12225 && double(xx / w) <= 0.26720 && double(yy / h) >= 0.55989 && double(yy / h) <= 0.61979) { exid.active = 1; }
		else { exid.active = 0; }

		if (games.take == 1) {
			if (double(xx / w) >= 0.56442 && double(xx / w) <= 0.73352 && double(yy / h) >= 0.26302 && double(yy / h) <= 0.35546) { cheker.active = 1; }
			else { cheker.active = 0; }

			if (double(xx / w) >= 0.56515 && double(xx / w) <= 0.73352 && double(yy / h) >= 0.38281 && double(yy / h) <= 0.47135) { poddavki.active = 1; }
			else { poddavki.active = 0; }

			if (double(xx / w) >= 0.56442 && double(xx / w) <= 0.73279 && double(yy / h) >= 0.49869 && double(yy / h) <= 0.58984) { four_four.active = 1; }
			else { four_four.active = 0; }

			if (double(xx / w) >= 0.51610 && double(xx / w) <= 0.58272 && double(yy / h) >= 0.73437 && double(yy / h) <= 0.79687) { down1.active = 1; }
			else { down1.active = 0; }

			if (double(xx / w) >= 0.61566 && double(xx / w) <= 0.68374 && double(yy / h) >= 0.73567 && double(yy / h) <= 0.79687) { down2.active = 1; }
			else { down2.active = 0; }

			if (double(xx / w) >= 0.71815 && double(xx / w) <= 0.78989 && double(yy / h) >= 0.73828 && double(yy / h) <= 0.80338) { down3.active = 1; }
			else { down3.active = 0; }
		}
		else {

			if (exid.take == 1) {
				if (double(xx / w) >= 0.43411 && double(xx / w) <= 0.59882 && double(yy / h) >= 0.64583 && double(yy / h) <= 0.73697) { exit_yes.active = 1; }
				else { exit_yes.active = 0; }

				if (double(xx / w) >= 0.63177 && double(xx / w) <= 0.80527 && double(yy / h) >= 0.64843 && double(yy / h) <= 0.73838) { exit_no.active = 1; }
				else { exit_no.active = 0; }
			}
			else {

				if (helps.take == 1) {
					if (double(xx / w) >= 0.33016 && double(xx / w) <= 0.46632 && double(yy / h) >= 0.79557 && double(yy / h) <= 0.85807) { rules1.active = 1; }
					else { rules1.active = 0; }

					if (double(xx / w) >= 0.49926 && double(xx / w) <= 0.63396 && double(yy / h) >= 0.79557 && double(yy / h) <= 0.85677) { rules2.active = 1; }
					else { rules2.active = 0; }

					if (double(xx / w) >= 0.66764 && double(xx / w) <= 0.81039 && double(yy / h) >= 0.80078 && double(yy / h) <= 0.86588) { rules3.active = 1; }
					else { rules3.active = 0; }
				}
				else {

					if (setings.take == 1) {
						if (double(xx / w) >= 0.66617 && double(xx / w) <= 0.84333 && double(yy / h) >= 0.26041 && double(yy / h) <= 0.32161) { color_black.active = 1; }
						else { color_black.active = 0; }

						if (double(xx / w) >= 0.66398 && double(xx / w) <= 0.83966 && double(yy / h) >= 0.37890 && double(yy / h) <= 0.44270) { color_dark.active = 1; }
						else { color_dark.active = 0; }

						if (double(xx / w) >= 0.66398 && double(xx / w) <= 0.84041 && double(yy / h) >= 0.49869 && double(yy / h) <= 0.56119) { color_blue.active = 1; }
						else { color_blue.active = 0; }

						if (double(xx / w) >= 0.66544 && double(xx / w) <= 0.73499 && double(yy / h) >= 0.67708 && double(yy / h) <= 0.73828) { fps_off.active = 1; }
						else { fps_off.active = 0; }

						if (double(xx / w) >= 0.76866 && double(xx / w) <= 0.84260 && double(yy / h) >= 0.68099 && double(yy / h) <= 0.74349) { fps_on.active = 1; }
						else { fps_on.active = 0; }

						if (double(xx / w) >= 0.66764 && double(xx / w) <= 0.73792 && double(yy / h) >= 0.79817 && double(yy / h) <= 0.86197) { time_off.active = 1; }
						else { time_off.active = 0; }

						if (double(xx / w) >= 0.77306 && double(xx / w) <= 0.84699 && double(yy / h) >= 0.80468 && double(yy / h) <= 0.87109) { time_on.active = 1; }
						else { time_on.active = 0; }

						if (double(xx / w) >= 0.66471 && double(xx / w) <= 0.73352 && double(yy / h) >= 0.58854 && double(yy / h) <= 0.64843) { vsync60.active = 1; }
						else { vsync60.active = 0; }

						if (double(xx / w) >= 0.76720 && double(xx / w) <= 0.84041 && double(yy / h) >= 0.58984 && double(yy / h) <= 0.65104) { vsync120.active = 1; }
						else { vsync120.active = 0; }
					}
				}
			}
		}
	}
}

void Menu::pressure() {

	if (games.active == 1) { games.take = 1; setings.take = 0; helps.take = 0; exid.take = 0; }
	else {
		if (setings.active == 1) { games.take = 0; setings.take = 1; helps.take = 0; exid.take = 0; }
		else {
			if (helps.active == 1) { games.take = 0; setings.take = 0; helps.take = 1; exid.take = 0; }
			else {
				if (exid.active == 1) { games.take = 0; setings.take = 0; helps.take = 0; exid.take = 1; }
			}
		}
	}

	if (exid.take == 1) {                                           // exit
		if (exit_yes.active == 1) { exit(0); }   // .yes
		if (exit_no.active == 1) { exid.take = 0; } // .no
	}
	else {

		if (helps.take == 1) {                                           //  helps 
			if (rules1.active == 1) {
				rules1.take = 1;
				rules2.take = 0;
				rules3.take = 0;
			}
			else {
				if (rules2.active == 1) {
					rules1.take = 0;
					rules2.take = 1;
					rules3.take = 0;
				}
				else {
					if (rules3.active == 1) {
						rules1.take = 0;
						rules2.take = 0;
						rules3.take = 1;
					}
				}
			}
		}
		else {


			if (setings.take == 1) {                                        // setings 
				if (color_black.active == 1) {   // .color
					color_of_figure = 1;
					color_black.take = 1;
					color_blue.take = 0;
					color_dark.take = 0;
				}
				else {
					if (color_blue.active == 1) {
						color_of_figure = 3;
						color_black.take = 0;
						color_blue.take = 1;
						color_dark.take = 0;
					}
					else {
						if (color_dark.active == 1) {
							color_of_figure = 2;
							color_black.take = 0;
							color_blue.take = 0;
							color_dark.take = 1;
						}
					}
				}

				if (fps_off.active == 1) {      // .fps
					fps = 0;
					fps_off.take = 1;
					fps_on.take = 0;
				}
				else {
					if (fps_on.active == 1) {
						fps = 1;
						fps_off.take = 0;
						fps_on.take = 1;
					}
				}


				if (time_off.active == 1) {     // .time
					time = 0;
					time_off.take = 1;
					time_on.take = 0;
				}
				else {
					if (time_on.active == 1) {
						time = 1;
						time_off.take = 0;
						time_on.take = 1;
					}
				}


				if (vsync60.active == 1) {        // .vsync
					vsync = 17;
					vsync60.take = 1;
					vsync120.take = 0;
				}
				else {
					if (vsync120.active == 1) {
						vsync = 8;
						vsync60.take = 0;
						vsync120.take = 1;
					}
				}
			}
			else {
				if (games.take == 1) {                                    // games
					if (cheker.active == 1) {         // .checker
						change_angle = 1;
						active = 0;
						type = 1;
					}

					if (poddavki.active == 1) {         // .checker
						change_angle = 1;
						active = 0;
						type = 2;
					}
				}
			}

		}
	}
}