/*
 *	main() for Megawatts & Marbles - The Energy Planning Game
 *
 *	[ESC] Interactive
 *
 *	Anthony Truelove MASc, P.Eng.
 *	Spencer Funk BEng, EIT
 *
 *	Copyright 2022 (C) - [ESC] Interactive
 *	See license terms for details
 *
 *	This defines main() for Megawatts & Marbles - The Energy Planning Game.
 *	Pretty simple.
 *
 *	ref: A. Moreira at al. (2013), SFML Game Development - Learn how to use
 *			SFML 2.0 to develop your own feature-packed game, Packt Publishing
 *			ISBN 978-1-84969-684-5
 *
 *		https://en.sfml-dev.org/documentation/2.5.1/
 *
 */


// -------- includes -------- //
#include "../header/constants.h"
#include "../header/includes.h"

#include "../header/ESC.h"
#include "../header/MM.h"


// -------- global variables -------- //
//          USE SPARINGLY!!!          //
bool fullscreen = false;
bool test_flag = false;


// -------- helper functions -------- //
void handleInputArgs(int argc, char** argv) {
	/*
	 *	Helper function to handle input arguments
	 */

	if (argc <= 1) {
		return;
	}

	std::string arg_str;
	for (int i = 0; i < argc; i++) {
		arg_str = std::string(argv[i]);
		if (
			arg_str.compare("--test") == 0 ||
			arg_str.compare("-t") == 0
		) {
			runTests();
			test_flag = true;
		}

		// else if ()

		// else {}
	}

	return;
}


// -------- main() -------- //
int main(int argc, char** argv)
{
	// handle input args
	try {
		handleInputArgs(argc, argv);
		if (test_flag) {
			return 0;
		}
	}
	catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return -1;
	}

	// init window pointer (used throughout)
	sf::RenderWindow* window_ptr;
	/* initialize random seed: */
  srand (time(NULL));

	// create and run game
	try {
		// play brand animation (also creates window and returns ptr to it)
		window_ptr = playBrandAnimation("Copyright 2022 (C) - [ESC] Interactive");

		// set window icon
		sf::Image window_icon;
		assert (window_icon.loadFromFile("assets/images/MM_256x116.png"));
		window_ptr->setIcon(
			window_icon.getSize().x,
			window_icon.getSize().y,
			window_icon.getPixelsPtr()
		);

		// set window title
		window_ptr->setTitle("Megawatts & Marbles - The Energy Planning Game");

		// render splash screen
		renderSplashScreen(window_ptr);

		// create Game object and run
		Game game(window_ptr);
		game.run();
	}
	catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		// window_ptr deleted within Game::~Game()
		return -1;
	}

	// window_ptr deleted within Game::~Game()
    return 0;
}
