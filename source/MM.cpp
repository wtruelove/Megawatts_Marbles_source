/*
 *	Implementation file for Megawatts & Marbles - The Energy Planning Game
 *
 *	[ESC] Interactive
 *
 *	Anthony Truelove MASc, P.Eng.
 *	Spencer Funk BEng, EIT
 *
 *	Copyright 2022 (C) - [ESC] Interactive
 *	See license terms for details
 *
 *	Implementation for Megawatts & Marbles.
 *
 *	ref: A. Moreira at al. (2013), SFML Game Development - Learn how to use
 *			SFML 2.0 to develop your own feature-packed game, Packt Publishing
 *			ISBN 978-1-84969-684-5
 *
 *		https://en.sfml-dev.org/documentation/2.5.1/
 *
 */


// -------- includes -------- //
#include "../header/includes.h"

#include "../header/ESC.h"
#include "../header/MM.h"


// -------- function implementations -------- //
void runTests(void) {
	/*
	 *	Runs the test suite for Megawatts & Marbles - The Energy Planning Game
	 */

	std::cout << "Running tests ... " << std::endl;

	try {
		// 1. testing plant animations
		{
			sf::RenderWindow* window_ptr = getRenderWindowPtr("Test 1");
			Game game(window_ptr);
			game.test1();
		}


		// 2. [...]
		{}
	}
	catch (...) {
		std::cerr << "\n*** A test has failed! ***\n" << std::endl;
		throw;
	}

	std::cout << "\n*** All tests have passed! ***\n" << std::endl;

	return;
}	// end runTests()


void renderSplashScreen(sf::RenderWindow* window_ptr) {
	/*
	 *	Renders the splash screen for Megawatts & Marbles - The Energy Planning Game
	 */

	// init
	bool animation_finished = false;
	int frame = 0;
	int alpha = 0;
	int animation_state = 0;
	sf::Clock clock;
	sf::Event event;
	sf::Time time_elapsed = sf::Time::Zero;

	// load assets
	sf::Texture MM_txtr;
	MM_txtr.setSmooth(true);
	assert (MM_txtr.loadFromFile("assets/images/MM_256x116.png"));
	sf::Sprite MM_sprite(MM_txtr);
	MM_sprite.setPosition(
		(SCREEN_WIDTH - 256) / 2,
		16
	);

	sf::Texture IESVic_txtr;
	IESVic_txtr.setSmooth(true);
	assert (IESVic_txtr.loadFromFile("assets/images/IESVic_512x88.png"));
	sf::Sprite IESVic_sprite(IESVic_txtr);
	IESVic_sprite.setPosition(
		16,
		SCREEN_HEIGHT - 104
	);

	sf::Texture SFML_txtr;
	SFML_txtr.setSmooth(true);
	assert (SFML_txtr.loadFromFile("assets/ESC_brand/SFML_256x128.png"));
	sf::Sprite SFML_sprite(SFML_txtr);
	SFML_sprite.setPosition(
		SCREEN_WIDTH - 272,
		SCREEN_HEIGHT - 144
	);

	// define legal info
	std::string legal_str;
	for (int i = 0; i < 14; i++) {
		legal_str += "\t";
	}
	legal_str += "  Megawatts & Marbles - The Energy Planning Game\n\n";
	/*
	for (int i = 0; i < 15; i++) {
		legal_str += "\t";
	}
	legal_str += "*** DEMO VERSION - FOR PLAY TESTING ONLY ***\n";
	*/
	for (int i = 0; i < 25; i++) {
		legal_str += "\t";
	}
	legal_str += "Version 1.0\n";
	for (int i = 0; i < 12; i++) {
		legal_str += "\t";
	}
	legal_str += "  You can send feedback to megawattsmarbles@gmail.com\n\n\n";
	legal_str += "Copyright 2022 (C) - [ESC] Interactive:  CC BY-NC-SA 4.0  (see: https://creativecommons.org/licenses/by-nc-sa/4.0/)\n\n\n";
	legal_str += "You are free to:\n\n";
    legal_str += "\tShare -- copy and redistribute the material in any medium or format\n\n";
    legal_str += "\tAdapt -- remix, transform, and build upon the material\n\n\n";
    legal_str += "Under the following terms:\n\n";
    legal_str += "\tAttribution -- You must give appropriate credit, provide a link to the license, and indicate if changes were made.\n\tYou may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.\n\n";
    legal_str += "\tNonCommercial -- You may not use the material for commercial purposes.\n\n";
    legal_str += "\tShareAlike -- If you remix, transform, or build upon the material, you must distribute your contributions under\n\tthe same license as the original.\n\n";
    legal_str += "\tNo additional restrictions -- You may not apply legal terms or technological measures that legally restrict others\n\tfrom doing anything the license permits.\n\n\n";
	for (int i = 0; i < 8; i++) {
		legal_str += "\t";
	}
    legal_str += "CONTINUED USE OF THIS SOFTWARE CONSTITUTES ACCEPTANCE OF THESE TERMS.";

	sf::Font font;
	assert (font.loadFromFile("assets/ESC_brand/OpenSans-Bold.ttf"));
	sf::Text legal_text(legal_str, font, 16);
	int text_width = ceil(1.02 * legal_text.getLocalBounds().width);
	int text_height = ceil(1.02 * legal_text.getLocalBounds().height);
	legal_text.setPosition(
		(SCREEN_WIDTH - text_width) / 2,
		1.15 * ((SCREEN_HEIGHT - text_height) / 2)
	);

	// loop over animation
	while (window_ptr->isOpen()) {
		// update time elapsed
		time_elapsed = clock.getElapsedTime();

		// skip on any key press or "close window" signal
		while (window_ptr->pollEvent(event)) {
			switch (event.type) {
	   			case (sf::Event::Closed):	// receive "close window" signal
	   				animation_finished = true;
	   				break;

	   			case (sf::Event::KeyPressed):	// key is pressed
	   				animation_finished = true;
	   				break;

	   			default:
	   				// do nothing!
	   				break;
   			}
		}

		// if "clock tick" ...
		if (
			!animation_finished &&
			time_elapsed.asSeconds() >= (frame + 1) * SECONDS_PER_FRAME
		) {
			// clear back buffer
			window_ptr->clear();

			// state dependent drawing
			switch (animation_state) {
				case (0):	// fade in
					MM_sprite.setColor(
						sf::Color(255, 255, 255, alpha)
					);
					IESVic_sprite.setColor(
						sf::Color(255, 255, 255, alpha)
					);
					SFML_sprite.setColor(
						sf::Color(255, 255, 255, alpha)
					);
					legal_text.setFillColor(
						sf::Color(255, 255, 255, alpha)
					);
					alpha += 3;
					if (alpha >= 255) {
						alpha = 255;
						animation_state++;
					}
					break;

				case (1):	// pause
					frame++;
					if (frame >= 10 * FRAMES_PER_SECOND) {
						animation_state++;
					}
					break;

				case (2):	// fade out
					MM_sprite.setColor(
						sf::Color(255, 255, 255, alpha)
					);
					IESVic_sprite.setColor(
						sf::Color(255, 255, 255, alpha)
					);
					SFML_sprite.setColor(
						sf::Color(255, 255, 255, alpha)
					);
					legal_text.setFillColor(
						sf::Color(255, 255, 255, alpha)
					);
					alpha -= 3;
					if (alpha <= 0) {
						alpha = 0;
						animation_state++;
					}
					break;

				default:	// finish
					animation_finished = true;
					break;
			}

			// constant drawing
			window_ptr->draw(MM_sprite);
			window_ptr->draw(IESVic_sprite);
			window_ptr->draw(SFML_sprite);
			window_ptr->draw(legal_text);

			// blit back buffer to front buffer
			window_ptr->display();

			// increment frame
			frame++;
		}

		// check for breaking condition
		if (animation_finished) {
			break;
		}
	}

	// clear and flip
	window_ptr->clear();
	window_ptr->display();

	return;
}	// end renderLegalInfo()


// -------- class implementations -------- //


// ---- Marble ---- //
Marble::Marble(
	double position_x,
	double position_y,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr,
	sf::Color shader_colour,
	bool charge
) {
	/*
	 *	Constructor for Marble class
	 */

	this->charge = charge;
	this->height = 32;
	this->frame = 0;
	this->glow_frame = 0;
	this->tile = 0;
	this->width = 32;
 	this->texture_key = "marble";
	this->shader_colour = shader_colour;

	if (this->charge) {
		this->scale = 0.04;
		this->target_x = position_x;
		this->target_y = position_y;
		this->position_x = SCREEN_WIDTH / 2;
		this->position_y = SCREEN_HEIGHT / 2;
	}
	else {
		this->scale = 1;
		this->position_x = position_x;
	 	this->position_y = position_y;
		this->target_x = SCREEN_WIDTH / 2;
		this->target_y = SCREEN_HEIGHT / 2;
	}
	this->init_dist = sqrt(
		pow(this->position_x - this->target_x, 2) +
		pow(this->position_y - this->target_y, 2)
	);

 	this->window_ptr = window_ptr;

 	this->assets_ptr = assets_ptr;

	// stream out and return
    //std::cout << "Marble object created at " << this << "." << std::endl;
  	return;
}	// end Marble::Marble()


bool Marble::isFinished(void) {
	/*
	 *	Method to check if marble has vanished (and hence can be destroyed)
	 */

	double dist_2_target = sqrt(
		pow(this->position_x - this->target_x, 2) +
		pow(this->position_y - this->target_y, 2)
	);
	if (dist_2_target <= 4 || this->scale <= 0.03) {
		return true;
	}
	else {
		return false;
	}
}	// end Marble::isFinished()


void Marble::drawFrame(void) {
	/*
	 *	Method to draw Marble frame
	 */

	// init
	sf::CircleShape glass;
	glass.setRadius(this->width / 2);
	glass.setFillColor(MARBLE_COLOUR_GLASS);
	glass.setOrigin(this->width / 2, this->height / 2);

	sf::Sprite sprite(
 		*(this->assets_ptr->getTexture(this->texture_key)),
 		sf::IntRect(
			0,
			this->tile * this->height,
			this->width,
			this->height
		)
 	);
	sprite.setOrigin(this->width / 2, this->height / 2);

	// transformations
 	sprite.setPosition(
		this->position_x,
		this->position_y
	);
	double split = fabs(cos((1.5 * M_PI * this->glow_frame) / FRAMES_PER_SECOND));
	sprite.setColor(
		sf::Color(
			split * this->shader_colour.r + (1 - split) * 255,
			split * this->shader_colour.g + (1 - split) * 255,
			split * this->shader_colour.b + (1 - split) * 255,
			255
		)
	);
	sf::Vector2f scale = sprite.getScale();
	sprite.setScale(
		scale.x * this->scale * (1 + split),
		scale.y * this->scale * (1 + split)
	);

	glass.setPosition(
		this->position_x,
		this->position_y
	);
	scale = glass.getScale();
	glass.setScale(scale.x * this->scale, scale.y * this->scale);

	// update scale (based on distance to target)
	double dist_2_target = sqrt(
		pow(this->position_x - this->target_x, 2) +
		pow(this->position_y - this->target_y, 2)
	);
	if (this->charge) {
		this->scale = 1 - dist_2_target / this->init_dist + 0.04;
	}
	else {
		this->scale = dist_2_target / this->init_dist;
	}

	// update position
	double delta_x = this->target_x - this->position_x;
	double delta_y = this->target_y - this->position_y;
	double denom = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	this->position_x += 12 * this->scale * (delta_x / denom);
	this->position_y += 12 * this->scale * (delta_y / denom);

	// draw
	this->window_ptr->draw(glass);
	this->window_ptr->draw(sprite);

	// increment frame and tile, return
	if (this->frame >= 0.005 * FRAMES_PER_SECOND) {
		if (this->charge) {
			this->tile--;
			if (this->tile < 0) {
				this->tile = 18;
			}
		}
		else {
			this->tile++;
			if (this->tile >= 19) {
				this->tile = 0;
			}
		}
		this->frame = 0;
	}
	else {
		this->frame++;
	}
	this->glow_frame++;
	return;
}	// end Marble::drawFrame()


Marble::~Marble(void) {
	/*
	 *	Destructor for Marble class
	 */

	// stream out and return
	//std::cout << "Marble object at " << this << " destroyed." << std::endl;
	return;
}	// end Marble::~Marble()


// ---- Emissions Hierarchy ---- //


// ---- Particle ---- //
Particle::Particle(
	double position_x,
	double position_y,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) {
	/*
	 *	Constructor for Particle class
	 */

	this->height = 8;
	this->width = 8;
	this->alpha = 255;
	this->angle = 0;
	this->position_x = position_x;
	this->position_y = position_y;
	this->scale = 1;
	this->texture_key = "emissions";

	this->window_ptr = window_ptr;

	this->assets_ptr = assets_ptr;

	// stream out and return
    //std::cout << "Particle object created at " << this << "." << std::endl;
  	return;
}	// end Particle::Particle()


bool Particle::isFinished(void) {
	/*
	 *	Method to check if particle has vanished (and hence can be destroyed)
	 */

	if (this->alpha <= 0) {
		return true;
	}
	else {
		return false;
	}
}	// end Particle::isFinished()


void Particle::drawFrame(double wind_speed_ratio) {
	/*
	 *	Method to draw particle frame
	 */

	// init
 	sf::Sprite sprite(
 		*(this->assets_ptr->getTexture(this->texture_key)),
 		sf::IntRect(
			0,
			this->sprite_idx * this->height,
			this->width,
			this->height
		)
 	);
	sprite.setOrigin(this->width / 2, this->height / 2);

 	// transformations
 	sprite.setPosition(
		this->position_x,
		this->position_y
	);
	sprite.setColor(sf::Color(255, 255, 255, this->alpha));
	sprite.setRotation(this->angle);
	sf::Vector2f scale = sprite.getScale();
	sprite.setScale(scale.x * this->scale, scale.y * this->scale);

	// update position, alpha, angle, and scale
	this->position_x += 2 * wind_speed_ratio;
	this->position_y -= 1;
	this->alpha -= 1.5;
	if (this->alpha < 0) {
		this->alpha = 0;
	}
	this->angle += 5 * wind_speed_ratio;
	this->scale += 0.02;

 	// draw and return
 	this->window_ptr->draw(sprite);
 	return;
}	// end of Particle::drawFrame()


Particle::~Particle(void) {
	/*
	 *	Destructor for Particle class
	 */

	// stream out and return
  	//std::cout << "Particle object at " << this << " destroyed." << std::endl;
  	return;
}	// end Particle::~Particle()


// ---- Particle <-- Steam ---- //

Steam::Steam(
	double position_x,
	double position_y,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Particle(
	position_x,
	position_y,
	window_ptr,
	assets_ptr
) {
	/*
	 *	Constructor for Steam class
	 */

	this->sprite_idx = 0;

	// stream out and return
  	//std::cout << "\tSteam object created at " << this << ".\n" << std::endl;
  	return;
}	// end Steam::Steam()


Steam::~Steam(void) {
	/*
	 *	Destructor for Steam class
	 */

	// stream out and return
  	//std::cout << "\tSteam object at " << this << " destroyed.\n" << std::endl;
  	return;
}	// end Steam::~Steam()


// ---- Particle <-- Smoke ---- //

Smoke::Smoke(
	double position_x,
	double position_y,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Particle(
	position_x,
	position_y,
	window_ptr,
	assets_ptr
) {
	/*
	 *	Constructor for Smoke class
	 */

	this->sprite_idx = 1;

	// stream out and return
  	//std::cout << "\tSmoke object created at " << this << ".\n" << std::endl;
  	return;
}	// end Smoke::Smoke()


Smoke::~Smoke(void) {
	/*
	 *	Destructor for Smoke class
	 */

	// stream out and return
  	//std::cout << "\tSmoke object at " << this << " destroyed.\n" << std::endl;
  	return;
}	// end Smoke::~Smoke()


// ---- Sky Disk ---- //

SkyDisk::SkyDisk(sf::RenderWindow* window_ptr, Assets* assets_ptr)
{
	/*
	 *	Constructor for Sky Disk
	 */

	this->angle = 180;
	this->window_ptr = window_ptr;
	this->assets_ptr = assets_ptr;

	// stream out and return
 	std::cout << "SkyDisk object created at " << this << "." << std::endl;
 	return;
}	// end SkyDisk::SkyDisk()


void SkyDisk::buildSprites(void) {
	/*
	 *	Method to build sprites (to finish construction once assets available!)
	 */

	// day sprite
	this->day_sprite.setTexture(*(this->assets_ptr->getTexture("sky disk")));
	this->day_sprite.setTextureRect(sf::IntRect(0, 0, 960, 960));
	this->day_sprite.setOrigin(960 / 2, 960 / 2);
	sf::Vector2f scale = this->day_sprite.getScale();
	this->day_sprite.setScale(scale.x * 2 * sqrt(2), scale.y * 2 * sqrt(2));
	this->day_sprite.setPosition(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT
	);
	this->day_sprite.setRotation(this->angle);

	// night sprite
	this->night_sprite.setTexture(*(this->assets_ptr->getTexture("sky disk")));
	this->night_sprite.setTextureRect(sf::IntRect(0, 960, 960, 960));
	this->night_sprite.setOrigin(960 / 2, 960 / 2);
	scale = this->night_sprite.getScale();
	this->night_sprite.setScale(scale.x * 2 * sqrt(2), scale.y * 2 * sqrt(2));
	this->night_sprite.setPosition(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT
	);
	this->night_sprite.setRotation(this->angle);

	return;
}	// end of SkyDisk::buildSprite()


double SkyDisk::getAlphaVar(void) {
	/*
	 *	Method to compute alpha_var (for dawn/dusk transitions)
	 */

	double alpha_var = 0;
	int angle = (int)(this->angle) % 360;

	if (angle >= 60 && angle <= 120) {
		alpha_var = (1.0 / 60.0) * angle - 1.0;
	}
	else if (angle >= 240 && angle <= 300) {
		alpha_var = (-1.0 / 60.0) * angle + 5.0;
	}
	else if (angle > 120 && angle < 240) {
		alpha_var = 1;
	}

	return alpha_var;
}	// end SkyDisk::getAlphaVar()


void SkyDisk::drawFrame(double hour_of_day) {
	/*
	 *	Method to draw frame of Sky Disk
	 */

	// angle as function of hour of day
	this->angle = (360.0 / 24.0) * hour_of_day + 180.0;
	this->day_sprite.setRotation(this->angle);
	this->night_sprite.setRotation(this->angle);

	// alpha as function of angle
	double alpha_var = this->getAlphaVar();
	double night_alpha = 255 * alpha_var;
	double day_alpha = 255 * (1 - alpha_var);
	this->day_sprite.setColor(sf::Color(255, 255, 255, day_alpha));
	this->night_sprite.setColor(sf::Color(255, 255, 255, night_alpha));

	// backing rectangle (for reddish dawn/dusk transitions)
	sf::RectangleShape backing_rect(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	backing_rect.setFillColor(sf::Color(255, 64, 0, 255));
	this->window_ptr->draw(backing_rect);

	// draw day/night skies
	this->window_ptr->draw(this->day_sprite);
	this->window_ptr->draw(this->night_sprite);

	return;
}	// end of SkyDisk::drawFrame()


SkyDisk::~SkyDisk(void) {
	/*
	 *	Destructor for Sky Disk
	 */

	// stream out and return
 	std::cout << "SkyDisk object at " << this << " destroyed." << std::endl;
 	return;
}	// end of SkyDisk::~SkyDisk()


// ---- OvercastClouds ---- //

OvercastClouds::OvercastClouds(sf::RenderWindow* window_ptr, Assets* assets_ptr) {
	/*
	 *	Constructor for OvercastClouds class
	 */

	this->window_ptr = window_ptr;
	this->assets_ptr = assets_ptr;

	// stream out and return
 	std::cout << "OvercastClouds object created at " << this << "." << std::endl;
 	return;
}	// end of OvercastClouds::OvercastClouds()


sf::Color OvercastClouds::getShading(
	double cloud_cover_ratio,
	double hour_of_day
) {
	/*
	 *	Method to get shading based on hour of day
	 */

	sf::Color colour(255, 255, 255, 255 * cloud_cover_ratio);
	double scalar = 1;
	double angle = (360.0 / 24.0) * hour_of_day + 180.0;
	int angle_int = (int)(angle) % 360;

	if (angle_int >= 60 && angle_int <= 120) {
		scalar = (-1.0 / 120.0) * angle_int + (3.0 / 2.0);
	}
	else if (angle_int >= 240 && angle_int <= 300) {
		scalar = (1.0 / 120.0) * angle_int - (3.0 / 2.0);
	}
	else if (angle_int > 120 && angle_int < 240) {
		scalar = 0.5;
	}
	//std::cout << scalar << std::endl;

	colour.r = scalar * 255;
	colour.g = scalar * 255;
	colour.b = scalar * 255;
	return colour;
}	// end OvercastClouds::getShading()


void OvercastClouds::buildSprites(void) {
	/*
	 *	Method to build sprites (to finish construction once assets available!)
	 */

	// overcast sky sprite
	this->overcast_sky_sprite.setTexture(*(this->assets_ptr->getTexture("overcast")));
	sf::Vector2f scale = this->overcast_sky_sprite.getScale();
	this->overcast_sky_sprite.setScale(scale.x * 2, scale.y * 2);

	// cloud sprites (fill list with random clouds in random places)
	int rand_frame = 0;
	int size_scalar = 3;
	double rand_pos_x = 0;
	double rand_pos_y = 0;
	for (int i = 0; i < 64; i++) {
		sf::Sprite* cloud_sprite_ptr = new sf::Sprite(
			*(this->assets_ptr->getTexture("clouds"))
		);
		scale = cloud_sprite_ptr->getScale();
		cloud_sprite_ptr->setScale(scale.x * size_scalar, scale.y * size_scalar);

		rand_frame = round(5 * ((double)rand() / RAND_MAX));
		cloud_sprite_ptr->setTextureRect(sf::IntRect(0, rand_frame * 32, 64, 32));

		rand_pos_x = SCREEN_WIDTH * ((double)rand() / RAND_MAX) -
			size_scalar * 64;
		rand_pos_y = (SCREEN_HEIGHT / 2) * ((double)rand() / RAND_MAX) -
			size_scalar * 32;
		cloud_sprite_ptr->setPosition(
			rand_pos_x,
			rand_pos_y
		);

		this->cloud_sprite_ptr_list.push_back(cloud_sprite_ptr);
	}


	return;
}	// end OvercastClouds::buildSprites()


void OvercastClouds::drawFrame(
	double wind_speed_ratio,
	double cloud_cover_ratio,
	double hour_of_day
) {
	/*
	 *	Method to draw frame of OvercastClouds
	 */

	// shading as a function of hour of day
	sf::Color shading = this->getShading(cloud_cover_ratio, hour_of_day);
	this->overcast_sky_sprite.setColor(shading);
	for (
 		auto itr = this->cloud_sprite_ptr_list.begin();
 		itr != this->cloud_sprite_ptr_list.end();
 		itr++
 	) {
 		(*itr)->setColor(shading);
 	}

	// overcast sky
	this->window_ptr->draw(this->overcast_sky_sprite);

	// clouds

	if (wind_speed_ratio > 0) {
		// remove finished clouds
		auto itr = this->cloud_sprite_ptr_list.begin();
		sf::Vector2f cloud_posn;
		while (itr != this->cloud_sprite_ptr_list.end()) {
			cloud_posn = (*itr)->getPosition();
			if (cloud_posn.x >= SCREEN_WIDTH + 64) {
				delete *itr;
				itr = this->cloud_sprite_ptr_list.erase(itr);
			}
			else {
				itr++;
			}
		}

		// update cloud positions
		for (
	 		auto itr = this->cloud_sprite_ptr_list.begin();
	 		itr != this->cloud_sprite_ptr_list.end();
	 		itr++
	 	) {
			cloud_posn = (*itr)->getPosition();
			(*itr)->setPosition(
				cloud_posn.x + wind_speed_ratio,
				cloud_posn.y
			);
		}

		// add new clouds
		int rand_frame = 0;
		int size_scalar = 3;
		double rand_pos_x = 0;
		double rand_pos_y = 0;
		sf::Vector2f scale;
		while (this->cloud_sprite_ptr_list.size() < 64) {
			sf::Sprite* cloud_sprite_ptr = new sf::Sprite(
				*(this->assets_ptr->getTexture("clouds"))
			);
			scale = cloud_sprite_ptr->getScale();
			cloud_sprite_ptr->setScale(scale.x * size_scalar, scale.y * size_scalar);

			rand_frame = round(5 * ((double)rand() / RAND_MAX));
			cloud_sprite_ptr->setTextureRect(sf::IntRect(0, rand_frame * 32, 64, 32));

			rand_pos_x = -1 * size_scalar * 64;
			rand_pos_y = (SCREEN_HEIGHT / 2) * ((double)rand() / RAND_MAX) -
				size_scalar * 32;
			cloud_sprite_ptr->setPosition(
				rand_pos_x,
				rand_pos_y
			);

			this->cloud_sprite_ptr_list.push_back(cloud_sprite_ptr);
		}
	}

	// draw clouds
	for (
 		auto itr = this->cloud_sprite_ptr_list.begin();
 		itr != this->cloud_sprite_ptr_list.end();
 		itr++
 	) {
		this->window_ptr->draw(*(*itr));
	}

	return;
}	// end OvercastClouds::drawFrame();


OvercastClouds::~OvercastClouds(void) {
	/*
	 *	Destructor for OvercastClouds class
	 */

	// clean up clouds
	for (
 		auto itr = this->cloud_sprite_ptr_list.begin();
 		itr != this->cloud_sprite_ptr_list.end();
 		itr++
 	) {
 		delete (*itr);
 	}
	this->cloud_sprite_ptr_list.clear();

	// stream out and return
	std::cout << "OvercastClouds object at " << this << " destroyed." << std::endl;
	return;
}	// end OvercastClouds::~OvercastClouds()


// ---- Foreground (and Plinko City) ---- //

Foreground::Foreground(sf::RenderWindow* window_ptr, Assets* assets_ptr) {
	/*
	 *	Constructor for Foreground
	 */

	this->window_ptr = window_ptr;
	this->assets_ptr = assets_ptr;

	// stream out and return
 	std::cout << "Foreground object created at " << this << "." << std::endl;
 	return;
}	// end of Foreground::Foreground()


void Foreground::buildSprites(void) {
	/*
	 *	Method to build sprites (to finish construction once assets available!)
	 */

	// terrain sprite
	this->terrain_sprite.setTexture(*(this->assets_ptr->getTexture("foreground")));
	this->terrain_sprite.setTextureRect(sf::IntRect(0, 0, 640, 480));
	sf::Vector2f scale = this->terrain_sprite.getScale();
	this->terrain_sprite.setScale(scale.x * 2, scale.y * 2);

	// city (powered) sprite
	this->city_powered_sprite.setTexture(*(this->assets_ptr->getTexture("foreground")));
	this->city_powered_sprite.setTextureRect(sf::IntRect(0, 480, 640, 480));
	scale = this->city_powered_sprite.getScale();
	this->city_powered_sprite.setScale(scale.x * 2, scale.y * 2);

	// city (unpowered) sprite
	this->city_unpowered_sprite.setTexture(*(this->assets_ptr->getTexture("foreground")));
	this->city_unpowered_sprite.setTextureRect(sf::IntRect(0, 960, 640, 480));
	scale = this->city_unpowered_sprite.getScale();
	this->city_unpowered_sprite.setScale(scale.x * 2, scale.y * 2);

	return;
}	// end Foreground::buildSprites()


sf::Color Foreground::getShading(double hour_of_day) {
	/*
	 *	Method to get shading based on hour of day
	 */

	sf::Color colour(255, 255, 255, 255);
	double scalar = 1;
	double angle = (360.0 / 24.0) * hour_of_day + 180.0;
	int angle_int = (int)(angle) % 360;

	if (angle_int >= 60 && angle_int <= 120) {
		scalar = (-1.0 / 120.0) * angle_int + (3.0 / 2.0);
	}
	else if (angle_int >= 240 && angle_int <= 300) {
		scalar = (1.0 / 120.0) * angle_int - (3.0 / 2.0);
	}
	else if (angle_int > 120 && angle_int < 240) {
		scalar = 0.5;
	}
	//std::cout << scalar << std::endl;

	colour.r = scalar * 255;
	colour.g = 0.8 * scalar * 255;
	colour.b = 0.8 * scalar * 255;
	return colour;
}	// end Foreground::getShading()


void Foreground::drawFrame(bool powered_flag, double hour_of_day) {
	/*
	 *	Method to draw frame of Foreground
	 */

	// shading as function of hour of day
	sf::Color shading = this->getShading(hour_of_day);
	this->terrain_sprite.setColor(shading);
	this->city_unpowered_sprite.setColor(shading);

	// terrain
	this->window_ptr->draw(this->terrain_sprite);

	// city
	if (powered_flag) {
		this->window_ptr->draw(this->city_powered_sprite);
	}
	else {
		this->window_ptr->draw(this->city_unpowered_sprite);
	}

	return;
}	// end Foreground::drawFrame();


Foreground::~Foreground(void) {
	/*
	 *	Destructor for Foreground
	 */

	// stream out and return
	std::cout << "Foreground object at " << this << " destroyed." << std::endl;
	return;
}	// end Foreground::~Foreground()


// ---- WindSock ---- //

WindSock::WindSock(sf::RenderWindow* window_ptr, Assets* assets_ptr) {
	/*
	 *	Constructor for WindSock class
	 */

	this->frame = 0;
	this->window_ptr = window_ptr;
	this->assets_ptr = assets_ptr;

	// stream out and return
 	std::cout << "WindSock object created at " << this << "." << std::endl;
 	return;
}	// end of WindSock::WindSock()


sf::Color WindSock::getShading(double hour_of_day) {
	/*
	 *	Method to get shading based on hour of day
	 */

	sf::Color colour(255, 255, 255, 255);
	double scalar = 1;
	double angle = (360.0 / 24.0) * hour_of_day + 180.0;
	int angle_int = (int)(angle) % 360;

	if (angle_int >= 60 && angle_int <= 120) {
		scalar = (-1.0 / 120.0) * angle_int + (3.0 / 2.0);
	}
	else if (angle_int >= 240 && angle_int <= 300) {
		scalar = (1.0 / 120.0) * angle_int - (3.0 / 2.0);
	}
	else if (angle_int > 120 && angle_int < 240) {
		scalar = 0.5;
	}
	//std::cout << scalar << std::endl;

	colour.r = scalar * 255;
	colour.g = 0.8 * scalar * 255;
	colour.b = 0.8 * scalar * 255;
	return colour;
}	// end WindSock::getShading()


void WindSock::buildSprites(void) {
	/*
	 *	Method to build sprites (to finish construction once assets available!)
	 */

	this->sock_sprite.setTexture(*(this->assets_ptr->getTexture("wind sock")));
	this->sock_sprite.setTextureRect(sf::IntRect(0, 64, 48, 64));
	this->sock_sprite.setOrigin(31, 6);
	this->sock_sprite.setPosition(
		SCREEN_WIDTH / 2 + 72,
		SCREEN_HEIGHT - 128 - 39
	);

	this->tower_sprite.setTexture(*(this->assets_ptr->getTexture("wind sock")));
	this->tower_sprite.setTextureRect(sf::IntRect(0, 0, 48, 64));
	this->tower_sprite.setPosition(
		SCREEN_WIDTH / 2 + 43,
		SCREEN_HEIGHT - 128 - 45
	);

	return;
}	// end of WindSock::buildSprites()


void WindSock::drawFrame(double wind_speed_ratio, double hour_of_day) {
	/*
	 *	Method to draw frame of WindSock
	 */

	// shading
	sf::Color shading = this->getShading(hour_of_day);

	// sock
	this->sock_sprite.setColor(shading);
	if (wind_speed_ratio <= 0) {
		this->sock_sprite.setRotation(90);
	}
	else if (this->frame % int(FRAMES_PER_SECOND / 12) == 0) {
		double sock_amp = ((double)rand() / RAND_MAX) * 6;
		double sock_angle = 0;
		if (wind_speed_ratio >= 1) {
			sock_angle = sock_amp * sin(this->frame);
		}
		else {
			sock_angle = 90 * (1 - wind_speed_ratio) + sock_amp * sin(this->frame);
		}
		this->sock_sprite.setRotation(sock_angle);
	}
	this->window_ptr->draw(this->sock_sprite);

	// tower
	this->tower_sprite.setColor(shading);
	this->window_ptr->draw(this->tower_sprite);

	this->frame++;
	return;
}	// end of WindSock::drawFrame()


WindSock::~WindSock(void) {
	/*
	 *	Destructor for WindSock class
	 */

	// stream out and return
 	std::cout << "WindSock object at " << this << " destroyed." << std::endl;
 	return;
}	// end of WindSock::~WindSock()

// ---- Plant Hierarchy ---- //


// ---- Plant ---- //

Plant::Plant(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) {
	/*
	 *	Constructor for Plant class
	 */

	this->running_flag = false;
	this->has_run = false;
	this->pulse_flag = false;
	this->draw_tokens = true;
	this->draw_charge = true;
	this->draw_price = true;
	this->frame = 0;
	this->muster_frame = 0;
	this->line_frame = 0;
	this->price_per_GW = 1;
	this->pulse_frame = 0;
	this->height = 128;
	this->last_production_GWh = 0;
	this->marble_counter = 0;
	this->marble_frame = 0;
	this->marble_iters = 0;
	this->marbles_committed = 0;
	this->n_blits = 0;
	this->n_sprites = 0;
	this->sprite_idx = 1;
	this->width = 128;
	//this->capacity_GW = GW_PER_TOKEN;
	this->capacity_GW = 0;
	this->position_x = position_x;
	this->position_y = position_y;
	this->prod_GW = 0;
	this->scale = scale;
	this->texture_key = "null";
	this->marble_colour = sf::Color(255, 255, 255, 255);
	this->window_ptr = window_ptr;
	this->assets_ptr = assets_ptr;

	// stream out and return
 	std::cout << "Plant object created at " << this << "." << std::endl;
 	return;
}	// end Plant::Plant()


void Plant::clearMarbles() {
	/*
	 *	Method to clear marble_ptr_list
	 */

	auto itr_marble = this->marble_ptr_list.begin();
  	while (itr_marble != this->marble_ptr_list.end()) {
  		delete *itr_marble;
  		itr_marble = this->marble_ptr_list.erase(itr_marble);
  	}
  	this->marble_ptr_list.clear();

	this->pulse_flag = false;

	return;
}	// end Plant::clearMarbles()


bool Plant::isRunning(void) {
	/*
	 *	Getter for running_flag	attribute
	 */

	return this->running_flag;
}	// end Plant::isRunning()


bool Plant::marblesFinished(void) {
	/*
	 *	Method to check if all marbles have finished animating
	 */

	return this->marble_ptr_list.empty();
}	// end Plant::marblesFinished()


int Plant::getMusteredMarbles(void) {
	/*
	 *	Getter for marble_counter attribute
	 */

	return this->marble_counter;
}	// end Plant::getMusteredMarbles()


int Plant::getPositionX(void) {
	/*
	 *	Getter for position_x attribute
	 */

	return this->position_x;
}	// end Plant::getPositionX()


int Plant::getPositionY(void) {
	/*
	 *	Getter for position_y attribute
	 */

	return this->position_y;
}	// end Plant::getPositionY()


int Plant::getTextureIndex(void) {
		if(this->texture_key == "coal"){
			return 0;
		}
		else if(this->texture_key == "combined"){
			return 1;
		}
		else if(this->texture_key == "fission"){
			return 2;
		}
		else if(this->texture_key == "geothermal"){
			return 3;
		}
		else if(this->texture_key == "hydro"){
			return 4;
		}
		else if(this->texture_key == "peaker"){
			return 5;
		}
		else if(this->texture_key == "solar"){
			return 6;
		}
		else if(this->texture_key == "storage"){
			return 7;
		}
		else if(this->texture_key == "tidal selection" || this->texture_key == "tidal"){
			return 8;
		}
		else if(this->texture_key == "wave selection" || this->texture_key == "wave"){
			return 9;
		}
		else if(this->texture_key == "wind selection" || this->texture_key == "wind"){
			return 10;
		}
		else{
			return -1;
		}
}// end Plant::getTextureIndex()


int Plant::getMarblesCommitted(int i) {
	/*
	 *	Getter for marbles_committed attribute.
	 */

	return this->marbles_committed_vector.at(i);
}	// end Plant::getMarblesCommitted()


double Plant::getCapacityGW(void) {
	return this->capacity_GW;
}	//end Plant::getCapacityGW()


int Plant::getPrice(void) {
	/*
	 *	Getter for price_per_GW attribute
	 */

	return this->price_per_GW;
}	// end Plant::getPrice()


sf::Color Plant::getMarbleColour(void) {
	/*
	 *	Getter for marble_colour attribute
	 */

	return this->marble_colour;
}	// end Plant::getMarbleColour()


void Plant::setPowerCapacity(double capacity_GW) {
	/*
	 *	Method to set capacity_GW attribute of Plant
	 */

	this->capacity_GW = capacity_GW;

	return;
}	// end Plant::setCapacity()


void Plant::setRunning(bool running_flag) {
	/*
	 *	Setter for running_flag attribute
	 */

	this->running_flag = running_flag;
	return;
}	// end of Plant::setRunning()


void Plant::setPositionX(int position_x) {
	/*
	 *	Setter for position_x attribute
	 */

	this->position_x = position_x;
	return;
}	// end Plant::setPositionX()


void Plant::setPositionY(int position_y) {
	/*
	 *	Setter for position_y attribute
	 */

	this->position_y = position_y;
	return;
}	// end Plant::setPositionY()


void Plant::setPlantTexture(int plant_num) {
	/*
	*	Sets temporary texture during plant selection
	*/

	switch (plant_num) {
		case (-2):
			this->texture_key = "blank";
			break;
		case (-1):
			this->texture_key = "null";
			break;
		case (0):
			this->texture_key = "coal";
			break;
		case (1):
			this->texture_key = "combined";
			break;
		case (2):
			this->texture_key = "fission";
			break;
		case (3):
			this->texture_key = "geothermal";
			break;
		case (4):
			this->texture_key = "hydro";
			break;
		case (5):
			this->texture_key = "peaker";
			break;
		case (6):
			this->texture_key = "solar";
			break;
		case (7):
			this->texture_key = "storage";
			break;
		case (8):
			this->texture_key = "tidal selection";
			break;
		case (9):
			this->texture_key = "wave selection";
			break;
		case (10):
			this->texture_key = "wind selection";
			break;
	}// end switch(plant_num)
}// end Plant::setPlantTexture()


void Plant::setHasRun(bool has_run) {
	/*
	 *	Setter for has_run attribute
	 */

	this->has_run = has_run;
	return;
}	// end Plant::setHasRun()


void Plant::setPulseFlag(bool pulse_flag) {
	/*
	 *	Setter for pulse_flag attribute
	 */

	this->pulse_flag = pulse_flag;
	return;
}	// end Plant::setPulseFlag()


void Plant::setDrawTokens(bool draw_tokens) {
	/*
	 *	Setter for draw_tokens attribute
	 */

	this->draw_tokens = draw_tokens;
	return;
}	// end Plant::setDrawTokens()


void Plant::setDrawCharge(bool draw_charge) {
	/*
	 *	Setter for draw_charge attribute
	 */

	this->draw_charge = draw_charge;
	return;
}	// end of Plant::drawCharge()


void Plant::setDrawPrice(bool draw_price) {
	/*
	 *	Setter for draw_price attribute
	 */

	this->draw_price = draw_price;
	return;
}	// end of Plant::drawPrice()


void Plant::setPrice(int price_per_GW) {
	/*
	 *	Setter for price_per_GW attribute
	 */

	this->price_per_GW = price_per_GW;

	return;
}	// end of Plant::setPrice()


/*
// ----------------------------------- I think this is an antiquated function
bool Plant::hasTextureKey(void){
	if(this->texture_key == "null"){
		return false;
	}
	else{
		return true;
	}
} // end Plant::hasTextureKey()
*/


void Plant::incMarbles(void) {
	/*
	 *	Method to increment marble_counter attribute
	 */

	if (this->marble_counter >= this->capacity_GW) {
		return;
	}
	else {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	return;
}	// end Plant::incMarbles()


void Plant::decMarbles(void) {
	/*
	 *	Method to decrement marble_counter attribute
	 */

	if (this->marble_counter <= 0) {
		return;
	}
	else {
		delete this->marble_sprite_ptr_list.back();
		this->marble_sprite_ptr_list.pop_back();
		this->marble_counter--;
	}

	return;
}	// end Plant::decMarbles()


void Plant::commitMarbles(void) {
	/*
	 *	Method to commit marble_counter (discharge), for rendering
	 */

	if (this->marble_counter == 0) {
		this->running_flag = false;
	}
	else {
		this->running_flag = true;
		this->has_run = true;
	}

	this->marbles_committed = 0;
	for (int i = 0; i < this->marble_counter; i++) {
		this->marble_ptr_list.push_back(
			new Marble(
				this->position_x,
				this->position_y - this->height / 2,
				this->window_ptr,
				this->assets_ptr,
				this->marble_colour,
				false
			)
		);
		this->marbles_committed++;
	}
	this->marbles_committed_vector.push_back(this->marbles_committed);

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
		delete *itr_marble_sprite;
		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
	}
	this->marble_sprite_ptr_list.clear();
	this->marble_counter = 0;

	return;
}	// end Plant::commitMarbles()


void Plant::drawTokens(void) {
	/*
	 *	Method to draw tokens invested into plant
	 */

	sf::Sprite token_sprite(*(this->assets_ptr->getTexture("capacity token")));

	int n_tokens = this->capacity_GW / GW_PER_TOKEN;
	// if storage need to count differently
	if (this->getTextureIndex() == 7) {
		n_tokens = this->capacity_GW * STORAGE_TOKENS_PER_GW;
	}
	double token_spacing = 0;
	if (n_tokens > 1) {
		token_spacing = (this->width - 32) / (n_tokens - 1);
	}
	double token_dx = 0;
	for (int i = 0; i < n_tokens; i++) {
		token_sprite.setPosition(
			this->position_x - this->width / 2 + token_dx,
			this->position_y + 8
		);
		this->window_ptr->draw(token_sprite);
		token_dx += token_spacing;
	}

	return;
}	// end Plant::drawTokens()


void Plant::drawCapacity(void) {
	/*
	 *	Method to draw plant capacity
	 */

	 // skip for null plants
 	if (this->getTextureIndex() <= -1) {
 		return;
 	}

	// assemble sprite
	sf::Sprite power_cap_sprite(*(this->assets_ptr->getTexture("power capacity")));
	double power_cap_width = power_cap_sprite.getLocalBounds().width;
	double power_cap_height = power_cap_sprite.getLocalBounds().height;
	power_cap_sprite.setOrigin(power_cap_width / 2, power_cap_height / 2);
	power_cap_sprite.setPosition(
		this->position_x - power_cap_width / 2 - 4,
		this->position_y + power_cap_height
	);

	// assemble text
	std::string power_cap_str;
	if (this->getTextureIndex() == 7) {	// Storage
		power_cap_str = ": " + std::to_string(int(this->capacity_GW)) + " GWh";
	}
	else {
		power_cap_str = ": " + std::to_string(int(this->capacity_GW)) + " GW";
	}
	sf::Text power_cap_txt(
		power_cap_str,
		*(this->assets_ptr->getFont("bold")),
		16
	);
	double cap_txt_width = power_cap_txt.getLocalBounds().width;
	double cap_txt_height = power_cap_txt.getLocalBounds().height;
	power_cap_txt.setOrigin(0, cap_txt_height / 2);
	power_cap_txt.setPosition(
		this->position_x,
		this->position_y + power_cap_height - 10
	);

	// render
	this->window_ptr->draw(power_cap_sprite);
	this->window_ptr->draw(power_cap_txt);

	return;
}	// end Plant::drawCapacity()


void Plant::drawPrice(void) {
	/*
	 *	Method to draw plant price per GW
	 */

	// skip for null plants
	if (this->getTextureIndex() <= -1) {
		return;
	}

	// assemble sprite
	sf::Sprite price_sprite(*(this->assets_ptr->getTexture("price per GW")));
	double price_sprite_width = price_sprite.getLocalBounds().width;
	double price_sprite_height = price_sprite.getLocalBounds().height;
	price_sprite.setOrigin(price_sprite_width / 2, price_sprite_height / 2);
	price_sprite.setPosition(
		this->position_x - price_sprite_width / 2 - 4,
		this->position_y - this->height - price_sprite_height
	);

	// assemble text
	std::string price_str = ": " + std::to_string(int(this->price_per_GW));
	sf::Text price_txt(
		price_str,
		*(this->assets_ptr->getFont("bold")),
		16
	);
	double price_txt_width = price_txt.getLocalBounds().width;
	double price_txt_height = price_txt.getLocalBounds().height;
	price_txt.setOrigin(0, price_txt_height / 2);
	price_txt.setPosition(
		this->position_x,
		this->position_y - this->height - price_sprite_height - 8
	);

	// assemble backing rect
	sf::RectangleShape backing_rect(
		sf::Vector2f(
			1.3 * (price_sprite_width + price_txt_width),
			1.15 * price_sprite_height
		)
	);
	backing_rect.setFillColor(sf::Color(0, 0, 0, 200));
	backing_rect.setOrigin(0, backing_rect.getLocalBounds().height / 2);
	backing_rect.setPosition(
		this->position_x - price_sprite_width - 8,
		this->position_y - this->height - price_sprite_height - 2
	);

	// render
	this->window_ptr->draw(backing_rect);
	this->window_ptr->draw(price_sprite);
	this->window_ptr->draw(price_txt);

	return;
}	// end Plant::drawPrice()


void Plant::drawMarbles(void) {
	/*
	 *	Method to render marbles (if any)
	 */

	// if no marbles, reset and return
	if (this->marble_ptr_list.empty()) {
		this->marble_frame = 0;
		this->marble_iters = 0;
		this->pulse_flag = false;
		return;
	}

	// remove finished marbles
	auto itr = this->marble_ptr_list.begin();
	while (itr != this->marble_ptr_list.end()) {
		if ((*itr)->isFinished()) {
			delete *itr;
			itr = this->marble_ptr_list.erase(itr);
		}
		else {
			itr++;
		}
	}

	// draw power line
	double line_alpha = 42 * fabs(cos((2.5 * M_PI * this->line_frame) / FRAMES_PER_SECOND));
	sf::Vertex line[2] = {
		sf::Vertex(
			sf::Vector2f(
				this->position_x,
				this->position_y - this->height / 2
			),
			sf::Color(162, 238, 242, line_alpha)
		),
		sf::Vertex(
			sf::Vector2f(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2
			),
			sf::Color(162, 238, 242, line_alpha)
		)
	};
	this->window_ptr->draw(line, 2, sf::Lines);

	// draw marbles (with space between, so can see)
	int n_iters = 0;
	for (
		auto itr = this->marble_ptr_list.begin();
		itr != this->marble_ptr_list.end();
		itr++
	) {
		(*itr)->drawFrame();

		if (n_iters >= this->marble_iters) {
			break;
		}
		else {
			n_iters++;
		}
	}

	// update marble_frames and marble_iters, return
	if (this->marble_frame >= FRAMES_PER_SECOND / 10) {
		this->marble_frame = 0;
		this->marble_iters++;
	}
	else {
		this->marble_frame++;
	}
	this->line_frame++;
	return;
}	// end Plant::drawMarbles()


void Plant::drawMusteredMarbles(void) {
	/*
	 *	Method to draw mustered marbles orbiting plant
	 */

	if (this->marble_counter == 0) {
		return;
	}

	sf::Text marble_counter_text(
		std::to_string(this->marble_counter),
		*(this->assets_ptr->getFont("bold")),
		24
	);
	//marble_counter_text.setFillColor(this->marble_colour);
	marble_counter_text.setFillColor(sf::Color(0, 0, 0, 255));
	marble_counter_text.setOrigin(
		marble_counter_text.getLocalBounds().width / 2,
		marble_counter_text.getLocalBounds().height / 2
	);
	marble_counter_text.setPosition(
		this->position_x,
		this->position_y - this->height - 35 - 6 * sin(
			(2 * M_PI * this->muster_frame) / (3 * FRAMES_PER_SECOND)
		)
	);

	sf::CircleShape counter_back;
	double counter_radius = 0.666 * sqrt(
		pow(marble_counter_text.getLocalBounds().width, 2) +
		pow(marble_counter_text.getLocalBounds().height, 2)
	);
	counter_back.setRadius(counter_radius);
	counter_back.setFillColor(MARBLE_COLOUR_GLASS_MUSTER);
	counter_back.setOrigin(counter_radius, counter_radius);
	counter_back.setPosition(
		marble_counter_text.getPosition().x,
		marble_counter_text.getPosition().y + 0.5 * counter_radius
	);

	double d_phase = 0;
	if (this->marble_counter > 1) {
		d_phase = (2 * M_PI) / this->marble_counter;
	}
	double pos_x = 0;
	double pos_y = 0;
	double phase = 0;
	for (
		auto itr = this->marble_sprite_ptr_list.begin();
		itr != this->marble_sprite_ptr_list.end();
		itr++
	) {
		sf::CircleShape glass;
		glass.setRadius(16);
		glass.setFillColor(
			sf::Color(
				MARBLE_COLOUR_GLASS_MUSTER.r,
				MARBLE_COLOUR_GLASS_MUSTER.g,
				MARBLE_COLOUR_GLASS_MUSTER.b,
				255 * (
					1 + cos((1.5 * M_PI * this->muster_frame) / FRAMES_PER_SECOND)
				) / 2
			)
		);
		glass.setOrigin(16, 16);

		pos_x = this->position_x + 45 * cos(
			(2 * M_PI * this->muster_frame) / (3 * FRAMES_PER_SECOND) + phase
		);
		pos_y = this->position_y - this->height / 2 + 45 * sin(
			(2 * M_PI * this->muster_frame) / (3 * FRAMES_PER_SECOND) + phase
		);
		(*itr)->setPosition(
			pos_x,
			pos_y
		);
		glass.setPosition(
			pos_x,
			pos_y
		);
		phase += d_phase;

		(*itr)->setColor(
			sf::Color(
				this->marble_colour.r,
				this->marble_colour.g,
				this->marble_colour.b,
				255 * (
					1 + cos((1.5 * M_PI * this->muster_frame) / FRAMES_PER_SECOND)
				) / 2
			)
		);

		this->window_ptr->draw(glass);
		this->window_ptr->draw(*(*itr));
	}

	this->window_ptr->draw(counter_back);
	this->window_ptr->draw(marble_counter_text);
	this->muster_frame++;
	return;
}	// end Plant::drawMusteredMarbles()


void Plant::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Plant object
	 */

	// change texture key if selected and a blank plant
	if (selected) {
		if (this->texture_key == "null") {
			this->texture_key = "null green";
		}
	}
	else{
		if (this->texture_key == "null green") {
				this->texture_key = "null";
		}
	}

	// init
	sf::Sprite sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
		);

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		sprite.setColor(color);
	}

	// state-dependent blitting
	if (this->running_flag) {
		sprite.setTextureRect(
			sf::IntRect(
				0,
				this->sprite_idx * this->height,
				this->width,
				this->height
			)
		);

		if (this->frame >= FRAMES_PER_BLIT) {
			this->sprite_idx++;
			this->frame = 0;
			if (this->sprite_idx > this->n_sprites - 1) {
				this->sprite_idx = 1;
			}
		}
	}

	// transformations
	sprite.setOrigin(this->width / 2,this->height);
	sprite.setPosition(
		this->position_x,
		this->position_y
	);
	if (this->pulse_flag) {
		double pulse = 1 + 0.05 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);
		sf::Vector2f scale = sprite.getScale();
		sprite.setScale(pulse * scale.x, pulse * scale.y);
		this->pulse_frame++;
	}

	// draw plant
	this->window_ptr->draw(sprite);

	// draw tokens invested into plant
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}

	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}

	// draw mustered marbles
	if (play_phase) {
		this->drawMusteredMarbles();
	}

	this->frame++;
	return;
}	// end Plant::drawFrame()


Plant::~Plant(void) {
	/*
	 *	Destructor for Plant class
	 */

	// delete marbles
	auto itr_marble = this->marble_ptr_list.begin();
 	while (itr_marble != this->marble_ptr_list.end()) {
 		delete *itr_marble;
 		itr_marble = this->marble_ptr_list.erase(itr_marble);
 	}
 	this->marble_ptr_list.clear();

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
 	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
 		delete *itr_marble_sprite;
 		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
 	}
 	this->marble_sprite_ptr_list.clear();

	// delete particles
 	auto itr_steam = this->steam_ptr_list.begin();
 	while (itr_steam != this->steam_ptr_list.end()) {
 		delete *itr_steam;
 		itr_steam = this->steam_ptr_list.erase(itr_steam);
 	}
 	this->steam_ptr_list.clear();

 	auto itr_smoke = this->smoke_ptr_list.begin();
 	while (itr_smoke != this->smoke_ptr_list.end()) {
 		delete *itr_smoke;
 		itr_smoke = this->smoke_ptr_list.erase(itr_smoke);
 	}
 	this->smoke_ptr_list.clear();

	// stream out and return
 	std::cout << "Plant object at " << this << " destroyed." << std::endl;
 	return;
}	// end Plant::~Plant()


// ---- Plant <-- Coal ---- //

Coal::Coal(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Coal class
	 */

	this->height = 128;
 	this->n_sprites = 9;
 	this->width = 128;
	this->texture_key = "coal";
	this->marble_colour = MARBLE_COLOUR_COAL;

	// stream out and return
 	std::cout << "\tCoal object created at " << this << ".\n" << std::endl;
 	return;
}	// end Coal::Coal()


void Coal::drawSteam(double wind_speed_ratio) {
	/*
	 *	Method to draw steam particles
	 */

	// remove finished particles
	auto itr = this->steam_ptr_list.begin();
	while (itr != this->steam_ptr_list.end()) {
		if ((*itr)->isFinished()) {
			delete *itr;
			itr = this->steam_ptr_list.erase(itr);
		}
		else {
			itr++;
		}
	}

	// spawn new particles
	if (this->running_flag) {
		double rand_pos_x = 51 * ((double)rand() / RAND_MAX);
		double pos_y = 32;
		this->steam_ptr_list.push_back(
			new Steam(
				this->position_x + rand_pos_x - this->width / 2,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);
	}

	// draw particles
	for (
		auto itr = this->steam_ptr_list.begin();
		itr != this->steam_ptr_list.end();
		itr++
	) {
		(*itr)->drawFrame(wind_speed_ratio);
	}

	return;
}	// end Coal::drawSteam()


void Coal::drawSmoke(double wind_speed_ratio) {
	/*
	 *	Method to draw smoke particles
	 */

	// remove finished particles
	auto itr = this->smoke_ptr_list.begin();
	while (itr != this->smoke_ptr_list.end()) {
		if ((*itr)->isFinished()) {
			delete *itr;
			itr = this->smoke_ptr_list.erase(itr);
		}
		else {
			itr++;
		}
	}

	// spawn new particles
	if (this->running_flag) {
		double rand_pos_x_1 = 40 + 6 * ((double)rand() / RAND_MAX);
		double rand_pos_x_2 = 40 + 6 * ((double)rand() / RAND_MAX) + 17;
		double rand_pos_x_3 = 40 + 6 * ((double)rand() / RAND_MAX) + 34;
		double pos_y = 22;
		this->smoke_ptr_list.push_back(
			new Smoke(
				this->position_x + rand_pos_x_1 - this->width / 2,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);
		this->smoke_ptr_list.push_back(
			new Smoke(
				this->position_x + rand_pos_x_2 - this->width / 2,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);
		this->smoke_ptr_list.push_back(
			new Smoke(
				this->position_x + rand_pos_x_3 - this->width / 2,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);
	}

	// draw particles
	for (
		auto itr = this->smoke_ptr_list.begin();
		itr != this->smoke_ptr_list.end();
		itr++
	) {
		(*itr)->drawFrame(wind_speed_ratio);
	}

	return;
}	// end Coal::drawSmoke()


void Coal::incMarbles(void) {
	/*
	 *	Method to increment marble_counter attribute
	 */

	if (this->marble_counter >= this->capacity_GW) {
		return;
	}
	else if (
		this->has_run &&
		this->marble_counter >= this->last_production_GWh + 1
	) {
		return;
	}
	else {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	return;
}	// end Coal::incMarbles()


void Coal::decMarbles(void) {
	/*
	 *	Method to decrement marble_counter attribute
	 */

	if (this->marble_counter <= 0) {
		return;
	}
	else if (
		this->has_run &&
		this->marble_counter <= this->last_production_GWh - 1
	) {
		return;
	}
	else {
		delete this->marble_sprite_ptr_list.back();
		this->marble_sprite_ptr_list.pop_back();
		this->marble_counter--;
	}

	return;
}	// end Coal::decMarbles()


void Coal::commitMarbles(void) {
	/*
	 *	Method to commit marble_counter (discharge), for rendering
	 */

	if (this->marble_counter == 0) {
		this->running_flag = false;
	}
	else {
		this->running_flag = true;
		this->has_run = true;
	}

	this->marbles_committed = 0;
	for (int i = 0; i < this->marble_counter; i++) {
		this->marble_ptr_list.push_back(
			new Marble(
				this->position_x,
				this->position_y - this->height / 2,
				this->window_ptr,
				this->assets_ptr,
				this->marble_colour,
				false
			)
		);
		this->marbles_committed++;
	}
	this->marbles_committed_vector.push_back(this->marbles_committed);

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
		delete *itr_marble_sprite;
		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
	}
	this->marble_sprite_ptr_list.clear();
	this->last_production_GWh = this->marble_counter;

	if (this->has_run) {
		for (int i = 0; i < this->last_production_GWh; i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
		}
	}

	return;
}	// end Coal::commitMarbles()


Coal::~Coal(void) {
	/*
	 *	Destructor for Coal class
	 */

	// stream out and return
 	std::cout << "\tCoal object at " << this << " destroyed." << std::endl;
 	return;
}	// end Coal::~Coal()


// ---- Plant <-- Combined ---- //

Combined::Combined(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Combined class
	 */

	this->height = 128;
 	this->n_sprites = 9;
 	this->width = 128;
	this->texture_key = "combined";
	this->marble_colour = MARBLE_COLOUR_COMBINED;

	// stream out and return
 	std::cout << "\tCombined object created at " << this << ".\n" << std::endl;
 	return;
}	// end Combined::Combined()


void Combined::drawSteam(double wind_speed_ratio) {
	/*
	 *	Method to draw steam particles
	 */

	// remove finished particles
	auto itr = this->steam_ptr_list.begin();
	while (itr != this->steam_ptr_list.end()) {
		if ((*itr)->isFinished()) {
			delete *itr;
			itr = this->steam_ptr_list.erase(itr);
		}
		else {
			itr++;
		}
	}

	// spawn new particles
	if (this->running_flag) {
		double rand_pos_x = 51 * ((double)rand() / RAND_MAX);
		double pos_y = 32;
		this->steam_ptr_list.push_back(
			new Steam(
				this->position_x + rand_pos_x - this->width / 2,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);
	}

	// draw particles
	for (
		auto itr = this->steam_ptr_list.begin();
		itr != this->steam_ptr_list.end();
		itr++
	) {
		(*itr)->drawFrame(wind_speed_ratio);
	}

	return;
}	// end Combined::drawSteam()


void Combined::drawSmoke(double wind_speed_ratio) {
	/*
	 *	Method to draw smoke particles
	 */
	// remove finished particles
	auto itr = this->smoke_ptr_list.begin();
	while (itr != this->smoke_ptr_list.end()) {
		if ((*itr)->isFinished()) {
			delete *itr;
			itr = this->smoke_ptr_list.erase(itr);
		}
		else {
			itr++;
		}
	}

	// spawn new particles
	if (this->running_flag) {
		double rand_pos_x = 98 + 19 * ((double)rand() / RAND_MAX);
		double pos_y = 22;
		this->smoke_ptr_list.push_back(
			new Smoke(
				this->position_x + rand_pos_x - this->width /2 ,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);
	}

	// draw particles
	for (
		auto itr = this->smoke_ptr_list.begin();
		itr != this->smoke_ptr_list.end();
		itr++
	) {
		(*itr)->drawFrame(wind_speed_ratio);
	}

	return;
}	// end Combined::drawSmoke()


void Combined::incMarbles(void) {
	/*
	 *	Method to increment marble_counter attribute
	 */

	if (this->marble_counter >= this->capacity_GW) {
		return;
	}
	else if (
		this->has_run &&
		this->marble_counter >= this->last_production_GWh + 2
	) {
		return;
	}
	else {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	return;
}	// end Combined::incMarbles()


void Combined::decMarbles(void) {
	/*
	 *	Method to decrement marble_counter attribute
	 */

	if (this->marble_counter <= 0) {
		return;
	}
	else if (
		this->has_run &&
		this->marble_counter <= this->last_production_GWh - 2
	) {
		return;
	}
	else {
		delete this->marble_sprite_ptr_list.back();
		this->marble_sprite_ptr_list.pop_back();
		this->marble_counter--;
	}

	return;
}	// end Combined::decMarbles()


void Combined::commitMarbles(void) {
	/*
	 *	Method to commit marble_counter (discharge), for rendering
	 */

	if (this->marble_counter == 0) {
		this->running_flag = false;
	}
	else {
		this->running_flag = true;
		this->has_run = true;
	}

	this->marbles_committed = 0;
	for (int i = 0; i < this->marble_counter; i++) {
		this->marble_ptr_list.push_back(
			new Marble(
				this->position_x,
				this->position_y - this->height / 2,
				this->window_ptr,
				this->assets_ptr,
				this->marble_colour,
				false
			)
		);
		this->marbles_committed++;
	}
	this->marbles_committed_vector.push_back(this->marbles_committed);

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
		delete *itr_marble_sprite;
		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
	}
	this->marble_sprite_ptr_list.clear();
	this->last_production_GWh = this->marble_counter;

	if (this->has_run) {
		for (int i = 0; i < this->last_production_GWh; i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
		}
	}

	return;
}	// end Combined::commitMarbles()


Combined::~Combined(void) {
	/*
	 *	Destructor for Combined class
	 */

	// stream out and return
 	std::cout << "\tCombined object at " << this << " destroyed." << std::endl;
 	return;
}	// end Combined::~Combined()


// ---- Plant <-- Fission ---- //

Fission::Fission(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Fission class
	 */

	this->height = 128;
 	this->n_sprites = 9;
 	this->width = 128;
	this->texture_key = "fission";
	this->marble_colour = MARBLE_COLOUR_FISSION;
	this->price_per_GW = FISSION_TOKENS_PER_GW;

	// stream out and return
 	std::cout << "\tFission object created at " << this << ".\n" << std::endl;
 	return;
}	// end Fission::Fission()


void Fission::drawSteam(double wind_speed_ratio) {
	/*
	 *	Method to draw steam particles
	 */

	// remove finished particles
	auto itr = this->steam_ptr_list.begin();
	while (itr != this->steam_ptr_list.end()) {
		if ((*itr)->isFinished()) {
			delete *itr;
			itr = this->steam_ptr_list.erase(itr);
		}
		else {
			itr++;
		}
	}

	// spawn new particles
	if (this->running_flag) {
		double rand_pos_x = 51 * ((double)rand() / RAND_MAX);
		double pos_y = 32;
		this->steam_ptr_list.push_back(
			new Steam(
				this->position_x + rand_pos_x - this->width / 2,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);
	}

	// draw particles
	for (
		auto itr = this->steam_ptr_list.begin();
		itr != this->steam_ptr_list.end();
		itr++
	) {
		(*itr)->drawFrame(wind_speed_ratio);
	}

	return;
}	// end Fission::drawSteam()


void Fission::incMarbles(void) {
	/*
	 *	Method to increment marble_counter attribute
	 */

	if (this->marble_counter >= this->capacity_GW) {
		return;
	}
	else if (this->has_run) {
		return;
	}
	else {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	return;
}	// end Fission::incMarbles()


void Fission::decMarbles(void) {
	/*
	 *	Method to decrement marble_counter attribute
	 */

	if (this->marble_counter <= 0) {
		return;
	}
	else if (this->has_run) {
		return;
	}
	else {
		delete this->marble_sprite_ptr_list.back();
		this->marble_sprite_ptr_list.pop_back();
		this->marble_counter--;
	}

	return;
}	// end Fission::decMarbles()


void Fission::commitMarbles(void) {
	/*
	 *	Method to commit marble_counter (discharge), for rendering
	 */

	if (this->marble_counter == 0) {
		this->running_flag = false;
	}
	else {
		this->running_flag = true;
		this->has_run = true;
	}

	this->marbles_committed = 0;
	for (int i = 0; i < this->marble_counter; i++) {
		this->marble_ptr_list.push_back(
			new Marble(
				this->position_x,
				this->position_y - this->height / 2,
				this->window_ptr,
				this->assets_ptr,
				this->marble_colour,
				false
			)
		);
		this->marbles_committed++;
	}
	this->marbles_committed_vector.push_back(this->marbles_committed);

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
		delete *itr_marble_sprite;
		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
	}
	this->marble_sprite_ptr_list.clear();
	this->last_production_GWh = this->marble_counter;

	if (this->has_run) {
		for (int i = 0; i < this->last_production_GWh; i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
		}
	}

	return;
}	// end Fission::commitMarbles()


Fission::~Fission(void) {
	/*
	 *	Destructor for Fission class
	 */

	// stream out and return
 	std::cout << "\tFission object at " << this << " destroyed." << std::endl;
 	return;
}	// end Fission::~Fission()


// ---- Plant <-- Geothermal ---- //

Geothermal::Geothermal(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Fission class
	 */

	this->height = 128;
 	this->n_sprites = 9;
 	this->width = 128;
	this->texture_key = "geothermal";
	this->marble_colour = MARBLE_COLOUR_GEOTHERMAL;

	// stream out and return
 	std::cout << "\tGeothermal object created at " << this << ".\n" << std::endl;
 	return;
}	// end Geothermal::Geothermal()


void Geothermal::drawSteam(double wind_speed_ratio) {
	/*
	 *	Method to draw steam particles
	 */

	// remove finished particles
	auto itr = this->steam_ptr_list.begin();
	while (itr != this->steam_ptr_list.end()) {
		if ((*itr)->isFinished()) {
			delete *itr;
			itr = this->steam_ptr_list.erase(itr);
		}
		else {
			itr++;
		}
	}

	// spawn new particles
	if (this->running_flag) {
		double rand_pos_x = 51 * ((double)rand() / RAND_MAX);
		double pos_y = 32;
		this->steam_ptr_list.push_back(
			new Steam(
				this->position_x + rand_pos_x - this->width / 2,
				this->position_y + pos_y - this->height,
				this->window_ptr,
				this->assets_ptr
			)
		);

		if ((double)rand() / RAND_MAX >= 0.9) {
			rand_pos_x = 96 + 32 * ((double)rand() / RAND_MAX);
			pos_y = 124;
			this->steam_ptr_list.push_back(
				new Steam(
					this->position_x + rand_pos_x - this->width / 2,
					this->position_y + pos_y - this->height,
					this->window_ptr,
					this->assets_ptr
				)
			);
		}
	}
	else {
		if ((double)rand() / RAND_MAX >= 0.9) {
			double rand_pos_x = 96 + 32 * ((double)rand() / RAND_MAX);
			double pos_y = 124;
			this->steam_ptr_list.push_back(
				new Steam(
					this->position_x + rand_pos_x - this->width / 2,
					this->position_y + pos_y - this->height,
					this->window_ptr,
					this->assets_ptr
				)
			);
		}
	}

	// draw particles
	for (
		auto itr = this->steam_ptr_list.begin();
		itr != this->steam_ptr_list.end();
		itr++
	) {
		(*itr)->drawFrame(wind_speed_ratio);
	}

	return;
}	// end Geothermal::drawSteam()


void Geothermal::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Geothermal object
	 */

	// change texture key if selected and a blank plant
	if (selected) {
		if (this->texture_key == "null") {
			this->texture_key = "null green";
		}
	}
	else{
		if (this->texture_key == "null green") {
				this->texture_key = "null";
		}
	}

	// init
	sf::Sprite sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
		);

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		sprite.setColor(color);
	}

	// state-dependent blitting
	if (this->running_flag) {
		sprite.setTextureRect(
			sf::IntRect(
				0,
				this->sprite_idx * this->height,
				this->width,
				this->height
			)
		);

		if (this->frame >= FRAMES_PER_BLIT) {
			this->sprite_idx++;
			this->frame = 0;
			if (this->sprite_idx > this->n_sprites - 1) {
				this->sprite_idx = 1;
			}
		}
	}

	// transformations
	sprite.setOrigin(this->width / 2,this->height);
	sprite.setPosition(
		this->position_x,
		this->position_y
	);
	if (this->pulse_flag) {
		double pulse = 1 + 0.05 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);
		sf::Vector2f scale = sprite.getScale();
		sprite.setScale(pulse * scale.x, pulse * scale.y);
		this->pulse_frame++;
	}

	// draw plant
	this->window_ptr->draw(sprite);

	// draw tokens invested into plant
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}

	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}

	// draw mustered marbles
	if (play_phase) {
		this->drawMusteredMarbles();
	}

	// draw drill txt
	/*
	if (!this->drill_txt_ptr_list.empty()) {
		for (
			auto itr_txt = this->drill_txt_ptr_list.begin();
			itr_txt != this->drill_txt_ptr_list.end();
			itr_txt++
		) {
			// update state
			sf::Vector2f posn = (**itr_txt).getPosition();
			(**itr_txt).setPosition(posn.x, posn.y - 2);

			// draw
			this->window_ptr->draw((**itr_txt));

			// clear finished
		}
	}
	*/
	int alpha = 0;
	int pos_y = 0;
	sf::Vector2f posn;
	sf::Color txt_colour;
	auto itr_txt = this->drill_txt_ptr_list.begin();
	while (itr_txt != this->drill_txt_ptr_list.end()) {
		// update state
		posn = (*itr_txt)->getPosition();
		pos_y = posn.y - 2;
		if (pos_y < this->position_y - 190) {
			pos_y = this->position_y - 190;
		}
		(*itr_txt)->setPosition(posn.x, pos_y);

		txt_colour = (*itr_txt)->getFillColor();
		alpha = txt_colour.a - 2;
		if (alpha < 0) {
			alpha = 0;
		}
		(*itr_txt)->setFillColor(
			sf::Color(
				txt_colour.r,
				txt_colour.g,
				txt_colour.b,
				alpha
			)
		);

		// draw
		this->window_ptr->draw(**itr_txt);

		// increment, clearing finished elements
		if (txt_colour.a <= 0) {
			delete *itr_txt;
	 		itr_txt = this->drill_txt_ptr_list.erase(itr_txt);
		}
		else {
			itr_txt++;
		}
	}

	this->frame++;
	return;
}	// end Plant::drawFrame()


void Geothermal::incMarbles(void) {
	/*
	 *	Method to increment marble_counter attribute
	 */

	if (this->marble_counter >= this->capacity_GW) {
		return;
	}
	else if (
		this->has_run &&
		this->marble_counter >= this->last_production_GWh + 2
	) {
		return;
	}
	else {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	return;
}	// end Geothermal::incMarbles()


void Geothermal::decMarbles(void) {
	/*
	 *	Method to decrement marble_counter attribute
	 */

	if (this->marble_counter <= 0) {
		return;
	}
	else if (
		this->has_run &&
		this->marble_counter <= this->last_production_GWh - 2
	) {
		return;
	}
	else {
		delete this->marble_sprite_ptr_list.back();
		this->marble_sprite_ptr_list.pop_back();
		this->marble_counter--;
	}

	return;
}	// end Geothermal::decMarbles()


void Geothermal::commitMarbles(void) {
	/*
	 *	Method to commit marble_counter (discharge), for rendering
	 */

	if (this->marble_counter == 0) {
		this->running_flag = false;
	}
	else {
		this->running_flag = true;
		this->has_run = true;
	}

	this->marbles_committed = 0;
	for (int i = 0; i < this->marble_counter; i++) {
		this->marble_ptr_list.push_back(
			new Marble(
				this->position_x,
				this->position_y - this->height / 2,
				this->window_ptr,
				this->assets_ptr,
				this->marble_colour,
				false
			)
		);
		this->marbles_committed++;
	}
	this->marbles_committed_vector.push_back(this->marbles_committed);

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
		delete *itr_marble_sprite;
		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
	}
	this->marble_sprite_ptr_list.clear();
	this->last_production_GWh = this->marble_counter;

	if (this->has_run) {
		for (int i = 0; i < this->last_production_GWh; i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
		}
	}

	return;
}	// end Geothermal::commitMarbles()


void Geothermal::drillSuccess(bool success) {
	/*
	 *	Method to populate drill_txt_ptr_list attribute
	 */

	if (success) {
		sf::Text* drill_txt_ptr = new sf::Text(
			"SUCCESS! (+1 GW)",
			*(this->assets_ptr->getFont("bold")),
			16
		);
		drill_txt_ptr->setOrigin(
			drill_txt_ptr->getLocalBounds().width / 2,
			drill_txt_ptr->getLocalBounds().height / 2
		);
		drill_txt_ptr->setPosition(
			this->position_x,
			this->position_y - 140
		);
		drill_txt_ptr->setFillColor(sf::Color(0, 255, 0, 255));
		this->drill_txt_ptr_list.push_back(drill_txt_ptr);

		this->assets_ptr->getSound("transition complete")->play();
	}
	else {
		sf::Text* drill_txt_ptr = new sf::Text(
			"FAILURE! (+0 GW)",
			*(this->assets_ptr->getFont("bold")),
			16
		);
		drill_txt_ptr->setOrigin(
			drill_txt_ptr->getLocalBounds().width / 2,
			drill_txt_ptr->getLocalBounds().height / 2
		);
		drill_txt_ptr->setPosition(
			this->position_x,
			this->position_y - 140
		);
		drill_txt_ptr->setFillColor(sf::Color(255, 0, 0, 255));
		this->drill_txt_ptr_list.push_back(drill_txt_ptr);

		this->assets_ptr->getSound("buzzer")->play();
	}

	return;
}	// end Geothermal::drillSuccess()


Geothermal::~Geothermal(void) {
	/*
	 *	Destructor for Geothermal class
	 */

	// delete drill texts
	auto itr_txt = this->drill_txt_ptr_list.begin();
 	while (itr_txt != this->drill_txt_ptr_list.end()) {
 		delete *itr_txt;
 		itr_txt = this->drill_txt_ptr_list.erase(itr_txt);
 	}
 	this->drill_txt_ptr_list.clear();

	// stream out and return
 	std::cout << "\tGeothermal object at " << this << " destroyed." << std::endl;
 	return;
}	// end Geothermal::~Geothermal()


// ---- Plant <-- Hydro ---- //

Hydro::Hydro(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Peaker class
	 */

	this->height = 128;
 	this->n_sprites = 5;
 	this->width = 128;
	this->capacity_GWh = 0;
	this->charge_GWh = 0;
	this->texture_key = "hydro";
	this->marble_colour = MARBLE_COLOUR_HYDRO;

	sf::Sprite* marble_sprite = new sf::Sprite(
		*(this->assets_ptr->getTexture("marble"))
	);
	marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
	marble_sprite->setColor(this->marble_colour);
	marble_sprite->setOrigin(16, 16);
	this->marble_sprite_ptr_list.push_back(marble_sprite);
	this->marble_counter++;

	// stream out and return
 	std::cout << "\tHydro object created at " << this << ".\n" << std::endl;
 	return;
}	// end Hydro::Hydro()


void Hydro::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Hydro object
	 */

	// init
	sf::Sprite sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);
	sf::RectangleShape charge_rect(
		sf::Vector2f(45, 74 * this->charge_GWh / this->capacity_GWh)
	);
	sf::Text charge_text(
		std::to_string(int(round(this->charge_GWh))),
		*(this->assets_ptr->getFont("bold")),
		18
	);

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		sprite.setColor(color);
	}

	// state-dependent blitting
	if (this->running_flag) {
		sprite.setTextureRect(
			sf::IntRect(
				0,
				this->sprite_idx * this->height,
				this->width,
				this->height
			)
		);

		/*
		if (this->frame >= (1 + this->n_blits) * FRAMES_PER_BLIT) {
			this->n_blits++;
			this->sprite_idx++;
			if (this->sprite_idx > this->n_sprites - 1) {
				this->sprite_idx = 1;
			}
		}
		*/

		if (this->frame >= FRAMES_PER_BLIT) {
			this->sprite_idx++;
			this->frame = 0;
			if (this->sprite_idx > this->n_sprites - 1) {
				this->sprite_idx = 1;
			}
		}
	}

	// transformations
	sprite.setOrigin(this->width / 2, this->height);
	sprite.setPosition(
		this->position_x,
		this->position_y
	);
	charge_rect.setOrigin(
		45 / 2,
		74 * this->charge_GWh / this->capacity_GWh
	);
	charge_rect.setPosition(
		this->position_x + 36,
		this->position_y - 25
	);
	charge_rect.setFillColor(sf::Color(0, 80, 255, 255));

	charge_text.setOrigin(
		charge_text.getLocalBounds().width / 2,
		charge_text.getLocalBounds().height / 2
	);
	charge_text.setPosition(
		this->position_x + 36,
		this->position_y - 1.4 * charge_text.getLocalBounds().height
	);
	int red = int(round(255 * (1 - this->charge_GWh / this->capacity_GWh)));
	int green = int(round(255 * (this->charge_GWh / this->capacity_GWh)));
	charge_text.setFillColor(
		sf::Color(red, green, 0, 255)
	);

	// pulsing
	if (this->pulse_flag) {
		double pulse = 1 + 0.05 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);

		sf::Vector2f scale = sprite.getScale();
		double sprite_scale_x = scale.x;
		double sprite_scale_y = scale.y;
		sprite.setScale(
			pulse * sprite_scale_x,
			pulse * sprite_scale_y
		);

		scale = charge_rect.getScale();
		charge_rect.setScale(
			pulse * scale.x / sprite_scale_x,
			pulse * scale.y / sprite_scale_y
		);

		scale = charge_text.getScale();
		charge_text.setScale(
			pulse * scale.x / sprite_scale_x,
			pulse * scale.y / sprite_scale_y
		);

		this->pulse_frame++;
	}

	// draw and return
	this->window_ptr->draw(charge_rect);
	this->window_ptr->draw(sprite);
	if (this->draw_charge) {
		this->window_ptr->draw(charge_text);
	}
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}
	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}
	if (play_phase) {
		this->drawMusteredMarbles();
	}
	this->frame++;
	return;
}	// end Hydro::drawFrame()


void Hydro::setEnergyCapacity(double capacity_GWh) {
	/*
	 *	Method to set capacity_GWh attribute of Hydro object
	 */

	this->capacity_GWh = capacity_GWh;
	this->charge_GWh = capacity_GWh;

	return;
}	// end Hydro::setCapacity()


void Hydro::setCharge(double charge_GWh) {
	/*
	 *	Method to set charge_GWh attribute of Hydro object
	 */

	if (charge_GWh < 0) {
		this->charge_GWh = 0;
	}

	this->charge_GWh = charge_GWh;
	if (this->charge_GWh > this->capacity_GWh) {
		this->charge_GWh = this->capacity_GWh;
	}

	return;
}	// end Hydro::setCharge()


double Hydro::getStorageGWh(){
	return this->capacity_GWh;
} // end Hydro::getStorageGWh()


double Hydro::getChargeGWh(){
	return this->charge_GWh;
} // end Hydro::getChargeGWh()


void Hydro::incMarbles(void) {
	/*
	 *	Method to increment marble_counter attribute
	 */

	if (
		this->marble_counter >= this->capacity_GW ||
		this->marble_counter >= this->charge_GWh
	) {
		return;
	}
	else {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	return;
}	// end Hydro::incMarbles()


void Hydro::decMarbles(void) {
	/*
	 *	Method to decrement marble_counter attribute
	 */

	if (this->marble_counter <= 1) {
		return;
	}
	else {
		delete this->marble_sprite_ptr_list.back();
		this->marble_sprite_ptr_list.pop_back();
		this->marble_counter--;
	}

	return;
}	// end Hydro::decMarbles()


void Hydro::commitMarbles(void) {
	/*
	 *	Method to commit marble_counter (discharge), for rendering
	 */

	if (this->marble_counter == 0) {
		this->running_flag = false;
	}
	else {
		this->running_flag = true;
		this->has_run = true;
	}

	this->marbles_committed = 0;
	for (int i = 0; i < this->marble_counter; i++) {
		this->marble_ptr_list.push_back(
			new Marble(
				this->position_x,
				this->position_y - this->height / 2,
				this->window_ptr,
				this->assets_ptr,
				this->marble_colour,
				false
			)
		);
		this->charge_GWh--;
		this->marbles_committed++;
	}
	this->marbles_committed_vector.push_back(this->marbles_committed);

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
		delete *itr_marble_sprite;
		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
	}
	this->marble_sprite_ptr_list.clear();
	this->marble_counter = 0;

	if (this->charge_GWh > 0) {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	if (this->charge_GWh <= 0) {
		this->running_flag = false;
	}

	return;
}	// end Hydro::commitMarbles()


Hydro::~Hydro(void) {
	/*
	 *	Destructor for Hydro class
	 */

	// stream out and return
 	std::cout << "\tHydro object at " << this << " destroyed." << std::endl;
 	return;
}	// end Hydro::~Hydro()


// ---- Plant <-- Peaker ---- //

Peaker::Peaker(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Peaker class
	 */

	this->height = 128;
 	this->n_sprites = 7;
 	this->width = 128;
	this->texture_key = "peaker";
	this->marble_colour = MARBLE_COLOUR_PEAKER;
	this->price_per_GW = PEAKER_TOKENS_PER_GW;

	// stream out and return
 	std::cout << "\tPeaker object created at " << this << ".\n" << std::endl;
 	return;
}	// end Peaker::Peaker()


void Peaker::drawSmoke(double wind_speed_ratio) {
	/*
	 *	Method to draw smoke particles
	 */

 	// remove finished particles
 	auto itr = this->smoke_ptr_list.begin();
 	while (itr != this->smoke_ptr_list.end()) {
 		if ((*itr)->isFinished()) {
 			delete *itr;
 			itr = this->smoke_ptr_list.erase(itr);
 		}
 		else {
 			itr++;
 		}
 	}

 	// spawn new particles
 	if (this->running_flag) {
 		double rand_pos_x = 98 + 19 * ((double)rand() / RAND_MAX);
 		double pos_y = 22;
 		this->smoke_ptr_list.push_back(
 			new Smoke(
 				this->position_x + rand_pos_x - this->width / 2,
 				this->position_y + pos_y - this->height,
 				this->window_ptr,
 				this->assets_ptr
 			)
 		);
 	}

 	// draw particles
 	for (
 		auto itr = this->smoke_ptr_list.begin();
 		itr != this->smoke_ptr_list.end();
 		itr++
 	) {
 		(*itr)->drawFrame(wind_speed_ratio);
 	}

 	return;
}	// end Peaker::drawSmoke()


Peaker::~Peaker(void) {
	/*
	 *	Destructor for Peaker class
	 */

	// stream out and return
 	std::cout << "\tPeaker object at " << this << " destroyed." << std::endl;
 	return;
}	// end Peaker::~Peaker()


// ---- Plant <-- Solar ---- //

Solar::Solar(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Solar class
	 */

	this->height = 128;
 	this->n_sprites = 1;
 	this->width = 128;
	this->texture_key = "solar";
	this->marble_colour = MARBLE_COLOUR_SOLAR;

	// stream out and return
 	std::cout << "\tSolar object created at " << this << ".\n" << std::endl;
 	return;
}	// end Solar::Solar()


void Solar::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Solar object
	 */

	// init
	sf::Sprite sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);
	sf::RectangleShape output_rect(
		sf::Vector2f(19, 65 * this->prod_GW / this->capacity_GW)
	);

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		sprite.setColor(color);
	}

	// transformations
	sprite.setOrigin(this->width / 2, this->height);
	sprite.setPosition(
		this->position_x,
		this->position_y
	);
	output_rect.setOrigin(
		19 / 2,
		65 * this->prod_GW / this->capacity_GW
	);
	output_rect.setPosition(
		this->position_x + 47,
		this->position_y - 6
	);
	int red = int(round(255 * (1 - this->prod_GW / this->capacity_GW)));
	int green = int(round(255 * (this->prod_GW / this->capacity_GW)));
	output_rect.setFillColor(sf::Color(red, green, 0, 255));

	// pulsing
	if (this->pulse_flag) {
		double pulse = 1 + 0.05 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);

		sf::Vector2f scale = sprite.getScale();
		double sprite_scale_x = scale.x;
		double sprite_scale_y = scale.y;
		sprite.setScale(
			pulse * sprite_scale_x,
			pulse * sprite_scale_y
		);

		scale = output_rect.getScale();
		output_rect.setScale(
			pulse * scale.x / sprite_scale_x,
			pulse * scale.y / sprite_scale_y
		);

		this->pulse_frame++;
	}

	// draw and return
	this->window_ptr->draw(output_rect);
	this->window_ptr->draw(sprite);
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}
	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}
	if (play_phase) {
		this->drawMusteredMarbles();
	}
	this->frame++;
	return;
}	// end Solar::drawFrame()


double Solar::getProduction(double solar_res_kWm2) {
	/*
	 *	Method to compute and return solar production.
	 */

	if (solar_res_kWm2 <= 0) {
		solar_res_kWm2 = 0;
	}

	double prod_GW = this->capacity_GW * solar_res_kWm2;
	if (prod_GW > this->capacity_GW) {
		prod_GW = this->capacity_GW;
	}

	this->prod_GW = prod_GW;

	if (this->marble_counter < 128) {
		for (int i = 0; i < round(prod_GW); i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
			this->marble_counter++;
		}
	}

	this->prod_GW = round(prod_GW);
	if (this->prod_GW > 0) {
		this->running_flag = true;
	}
	else {
		this->running_flag = false;
	}
	return prod_GW;
}	// end Solar::getProduction()


Solar::~Solar(void) {
	/*
	 *	Destructor for Solar class
	 */

	// stream out and return
 	std::cout << "\tSolar object at " << this << " destroyed." << std::endl;
 	return;
}	// end Solar::~Solar()


// ---- Plant <-- Storage ---- //

Storage::Storage(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Solar class
	 */

	this->height = 128;
 	this->n_sprites = 1;
 	this->width = 128;
	this->capacity_GWh = 0;
	this->charge_GWh = 0;
	this->texture_key = "storage";
	this->marble_colour = MARBLE_COLOUR_STORAGE;
	this->price_per_GW = STORAGE_TOKENS_PER_GW;

	// stream out and return
 	std::cout << "\tStorage object created at " << this << ".\n" << std::endl;
 	return;
}	// end Storage::Storage()


void Storage::incMarbles(void) {
	/*
	 *	Method to increment marble_counter attribute
	 */

	if (
		this->marble_counter >= this->capacity_GW ||
		this->marble_counter >= this->charge_GWh
	) {
		return;
	}
	else {
		sf::Sprite* marble_sprite = new sf::Sprite(
			*(this->assets_ptr->getTexture("marble"))
		);
		marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
		marble_sprite->setColor(this->marble_colour);
		marble_sprite->setOrigin(16, 16);
		this->marble_sprite_ptr_list.push_back(marble_sprite);
		this->marble_counter++;
	}

	return;
}	// end Storage::incMarbles()


void Storage::commitMarbles(void) {
	/*
	 *	Method to commit marble_counter (discharge), for rendering
	 */

	if (this->marble_counter == 0) {
		this->running_flag = false;
	}
	else {
		this->running_flag = true;
		this->has_run = true;
	}

	this->marbles_committed = 0;
	for (int i = 0; i < this->marble_counter; i++) {
		this->marble_ptr_list.push_back(
			new Marble(
				this->position_x,
				this->position_y - this->height / 2,
				this->window_ptr,
				this->assets_ptr,
				this->marble_colour,
				false
			)
		);
		this->charge_GWh -= 1;
		this->marbles_committed++;
	}
	this->marbles_committed_vector.push_back(this->marbles_committed);

	auto itr_marble_sprite = this->marble_sprite_ptr_list.begin();
	while (itr_marble_sprite != this->marble_sprite_ptr_list.end()) {
		delete *itr_marble_sprite;
		itr_marble_sprite = this->marble_sprite_ptr_list.erase(itr_marble_sprite);
	}
	this->marble_sprite_ptr_list.clear();
	this->marble_counter = 0;

	return;
}	// end Storage::commitMarbles()


int Storage::commitCharge(int n_marbles) {
	/*
	 *	Method to commit n marbles (charge), for rendering
	 */

	int space_GWh = this->capacity_GWh - this->charge_GWh;

	if (space_GWh <= 0) {
		return n_marbles;
	}

	int accepted_GWh = 0;
	int limit = 0;
	if (n_marbles > space_GWh) {
		limit = space_GWh;
	}
	else {
		limit = n_marbles;
	}
	for (int i = 0; i < limit; i++) {
 		this->marble_ptr_list.push_back(
 			new Marble(
 				this->position_x,
 				this->position_y - this->height / 2,
 				this->window_ptr,
 				this->assets_ptr,
 				this->marble_colour,
 				true
 			)
 		);
		accepted_GWh++;
		this->charge_GWh += 1;
 	}

	return n_marbles - accepted_GWh;
}	// end Storage::commitCharge()


void Storage::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Storage object
	 */

	// init
	sf::Sprite sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);
	sf::Text charge_text(
		std::to_string(int(round(this->charge_GWh))),
		*(this->assets_ptr->getFont("bold")),
		18
	);

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		sprite.setColor(color);
	}

	// transformations
	sprite.setOrigin(this->width / 2, this->height);
	sprite.setPosition(
		this->position_x,
		this->position_y
	);
	charge_text.setPosition(
		this->position_x + 54 +
			((18 - charge_text.getLocalBounds().width) / 2) - this->width / 2,
		this->position_y + 94 +
			((18 - charge_text.getLocalBounds().height) / 2) - this->height
	);
	int red = int(round(255 * (1 - this->charge_GWh / this->capacity_GWh)));
	int green = int(round(255 * (this->charge_GWh / this->capacity_GWh)));
	charge_text.setFillColor(
		sf::Color(red, green, 0, 255)
	);

	// pulsing
	if (this->pulse_flag) {
		double pulse = 1 + 0.05 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);

		sf::Vector2f scale = sprite.getScale();
		double sprite_scale_x = scale.x;
		double sprite_scale_y = scale.y;
		sprite.setScale(
			pulse * sprite_scale_x,
			pulse * sprite_scale_y
		);

		scale = charge_text.getScale();
		charge_text.setScale(
			pulse * scale.x / sprite_scale_x,
			pulse * scale.y / sprite_scale_y
		);

		this->pulse_frame++;
	}

	// draw and return
	this->window_ptr->draw(sprite);
	if (this->draw_charge) {
		this->window_ptr->draw(charge_text);
	}
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}
	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}
	if (play_phase) {
		this->drawMusteredMarbles();
	}
	this->frame++;
	return;
}	// end Storage::drawFrame()


void Storage::setEnergyCapacity(double capacity_GWh) {
	/*
	 *	Method to set capacity_GWh attribute of Storage object
	 */

	this->capacity_GWh = capacity_GWh;
	// ----------------------------------------------------------------------------
	// was this casuing the issue Anthony had with initilizing storage?
	this->charge_GWh = 0;

	return;
}	// end Storage::setCapacity()


void Storage::setCharge(double charge_GWh) {
	/*
	 *	Method to set charge_GWh attribute of Storage object
	 */

	if (charge_GWh < 0) {
		this->charge_GWh = 0;
	}

	this->charge_GWh = charge_GWh;
	if (this->charge_GWh > this->capacity_GWh) {
		this->charge_GWh = this->capacity_GWh;
	}

	return;
}	// end Storage::setCharge()


double Storage::getStorageGWh(){
	return this->capacity_GWh;
} // end Storage::getStorageGWh()


double Storage::getChargeGWh(){
	return this->charge_GWh;
} // end Storage::getChargeGWh()


Storage::~Storage(void) {
	/*
	 *	Destructor for Storage class
	 */

	// stream out and return
 	std::cout << "\tStorage object at " << this << " destroyed." << std::endl;
 	return;
}	// end Storage::~Storage()


// ---- Plant <-- Tidal ---- //

Tidal::Tidal(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Tidal class
	 */

	this->height = 128;
 	this->width = 128;
	this->angle = 0;
	this->design_speed_ms = 0.47;
	this->texture_key = "tidal";
	this->marble_colour = MARBLE_COLOUR_TIDAL;

	// stream out and return
 	std::cout << "\tTidal object created at " << this << ".\n" << std::endl;
 	return;
}	// end Tidal::Tidal()


void Tidal::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Tidal object
	 */

	// init
	sf::Sprite body_sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);
	std::vector<sf::Sprite> blade_sprite_vec;
	for (int i = 0; i < 3; i++) {
		blade_sprite_vec.push_back(
			sf::Sprite(
				*(this->assets_ptr->getTexture(this->texture_key)),
				sf::IntRect(0, this->height, this->width, this->height)
			)
		);
		blade_sprite_vec[i].setOrigin(64, 96);
	}
	sf::RectangleShape water_rect(sf::Vector2f(128, 128));

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		body_sprite.setColor(color);
		for (int i = 0; i < 3; i++) {
			blade_sprite_vec[i].setColor(color);
		}
	}

	// transformations
	body_sprite.setOrigin(this->width / 2, this->height);
	body_sprite.setPosition(
		this->position_x,
		this->position_y - 8 + 5 * sin((double)this->frame / 128)
	);
	for (int i = 0; i < blade_sprite_vec.size(); i++) {
		blade_sprite_vec[i].setOrigin(64, 96);
		blade_sprite_vec[i].setPosition(
			this->position_x,
			this->position_y - 40 + 5 * sin((double)this->frame / 128)
		);
		blade_sprite_vec[i].setRotation(this->angle + i * 120);
	}
	water_rect.setOrigin(this->width / 2, this->height);
	water_rect.setPosition(
		this->position_x,
		this->position_y
	);

	// pulsing
	if (this->pulse_flag) {
		double pulse = 1 + 0.05 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);

		sf::Vector2f scale = body_sprite.getScale();
		double sprite_scale_x = scale.x;
		double sprite_scale_y = scale.y;
		body_sprite.setScale(
			pulse * sprite_scale_x,
			pulse * sprite_scale_y
		);

		for (int i = 0; i < blade_sprite_vec.size(); i++) {
			scale = blade_sprite_vec[i].getScale();
			blade_sprite_vec[i].setScale(
				pulse * scale.x,
				pulse * scale.y
			);
			blade_sprite_vec[i].setPosition(
				this->position_x,
				this->position_y - 40 + 5 * sin((double)this->frame / 128) -
				2 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND)
			);
		}

		this->pulse_frame++;
	}

	// update angle
	this->angle += 2 * (this->prod_GW / this->capacity_GW);

	// draw, increment frame, and return
	water_rect.setFillColor(
		sf::Color(0, 80, 255, 255)
	);
	this->window_ptr->draw(water_rect);
	this->window_ptr->draw(body_sprite);
	for (int i = 0; i < blade_sprite_vec.size(); i++) {
		this->window_ptr->draw(blade_sprite_vec[i]);
	}
	water_rect.setFillColor(
		sf::Color(0, 80, 255, 100)
	);
	this->window_ptr->draw(water_rect);
	if (this->prod_GW > 0) {
		this->frame++;
	}
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}
	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}
	if (play_phase) {
		this->drawMusteredMarbles();
	}
	this->frame++;
	return;
}	// end Tidal::drawFrame()


double Tidal::getProduction(double tidal_res_ms) {
	/*
	 *	Method to compute and return tidal production.
	 */

	if (tidal_res_ms <= 0) {
		tidal_res_ms = 0;
	}

	// compute production based on derived dimensionless performance
	double prod = 0;
	double prod_GW = 0;
	if (tidal_res_ms > 0) {
		double turb_speed = (tidal_res_ms - this->design_speed_ms) /
			this->design_speed_ms;

		// look-up on dimensionless performance curve, get dimensionless production [ ]
		 if (turb_speed < -0.71 || turb_speed > 0.65) {
			 prod = 0;
		 } else if (turb_speed >= -0.71 && turb_speed <= 0) {
			 prod = 1.69215 * exp(1.25909 * turb_speed) - 0.69215;
		 } else {
			 prod = 1;
		 }
	}
	prod_GW = this->capacity_GW * prod;

	if (this->marble_counter < 128) {
		for (int i = 0; i < round(prod_GW); i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
			this->marble_counter++;
		}
	}

	this->prod_GW = round(prod_GW);
	if (this->prod_GW > 0) {
		this->running_flag = true;
	}
	else {
		this->running_flag = false;
	}
	return prod_GW;
}	// end Tidal::getProduction()


double Tidal::getDesignSpeed(void) {
	/*
	 *	Getter for design_speed_ms attribute
	 */

	return this->design_speed_ms;
}	// end Tidal::getDesignSpeed()


Tidal::~Tidal(void) {
	/*
	 *	Destructor for Tidal class
	 */

	// stream out and return
 	std::cout << "\tTidal object at " << this << " destroyed." << std::endl;
 	return;
}	// end Tidal::~Tidal()


// ---- Plant <-- Wave ---- //

Wave::Wave(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Wave class
	 */

	this->height = 128;
 	this->width = 128;
	this->design_period_s = 8.5;	// specific to Robertson et al (2021) model
	this->wave_res_m = 0;
	this->wave_res_s = 0;
	this->texture_key = "wave";
	this->marble_colour = MARBLE_COLOUR_WAVE;

	// stream out and return
 	std::cout << "\tWave object created at " << this << ".\n" << std::endl;
 	return;
}	// end Wave::Wave()


void Wave::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Wave object
	 */

	// init
	if (this->wave_res_s < 5.75) {
		this->wave_res_s = 5.75;
	}
	double amp = 1.05 * (this->wave_res_m / 2);
	if (this->running_flag && amp <= 0.75) {
		amp = 0.75;
	}
	double trig_arg = (2 * M_PI * this->frame * SECONDS_PER_FRAME) /
		this->wave_res_s;
	sf::Sprite WEC_arm(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(
			0,
			0,
			this->width,
			this->height)
	);
	WEC_arm.setOrigin(64, 64);
	sf::Sprite WEC_spar(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(
			0,
			this->height,
			this->width,
			this->height)
	);
	WEC_spar.setOrigin(64, 64);
	sf::Sprite WEC_float(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(
			0,
			2 * this->height,
			this->width,
			this->height)
	);
	WEC_float.setOrigin(64, 64);
	sf::RectangleShape wave_column;

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		WEC_arm.setColor(color);
		WEC_spar.setColor(color);
		WEC_float.setColor(color);
	}

	// transformations
	// ASSUMPTION: float tracks free surface
	double float_y = amp * sin(trig_arg);
	WEC_arm.setPosition(
		this->position_x,
		this->position_y + float_y - 78
	);
	WEC_float.setPosition(
		this->position_x,
		this->position_y + float_y - 78
	);

	// ASSUMPTION: spar follows float according to simple harmonic motion
	// from particular solution to linear mass-spring-damper ODE
	// ASSUMPTION: system is critically damped (zeta = 1)
	double spar_y = (
		(
			(2 * amp * this->wave_res_s) /
			(
				pow(M_PI * this->wave_res_s, 4) +
				2 * pow(M_PI, 4) * pow(
					this->wave_res_s * this->design_period_s, 2
				) +
				pow(M_PI * this->design_period_s, 4)
			)
		) *
		(
			((pow(M_PI, 4) * this->wave_res_s) / 2) *
			(
				pow(this->wave_res_s, 2) +
				3 * pow(this->design_period_s, 2)
			) *
			sin(trig_arg) -
			(
				pow(M_PI, 4) * pow(this->design_period_s, 3)
			) *
			cos(trig_arg)
		)
	);
	if (fabs(spar_y) < 0.5) {
		spar_y = 0;
	}

	// enforce end-stops
	if (float_y - spar_y > 9) {
		float_y = spar_y + 9;
	}
	else if (spar_y - float_y > 25) {
		float_y = spar_y - 25;
	}
	WEC_spar.setPosition(
		this->position_x,
		this->position_y + spar_y - 78
	);
	wave_column.setSize(
		sf::Vector2f(
			this->width,
			71 - float_y
		)
	);
	wave_column.setOrigin(
		wave_column.getLocalBounds().width / 2,
		wave_column.getLocalBounds().height
	);
	wave_column.setPosition(
		this->position_x,
		this->position_y
	);

	// pulsing
	if (this->pulse_flag) {
		double pulse = 1 + 0.05 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);

		sf::Vector2f scale = WEC_spar.getScale();
		double sprite_scale_x = scale.x;
		double sprite_scale_y = scale.y;
		WEC_spar.setScale(
			pulse * sprite_scale_x,
			pulse * sprite_scale_y
		);

		scale = WEC_arm.getScale();
		WEC_arm.setScale(
			pulse * scale.x,
			pulse * scale.y
		);

		scale = WEC_float.getScale();
		WEC_float.setScale(
			pulse * scale.x,
			pulse * scale.y
		);

		this->pulse_frame++;
	}

	// draw, increment frame, and return
	wave_column.setFillColor(
		sf::Color(0, 80, 255, 255)
	);
	this->window_ptr->draw(wave_column);
	this->window_ptr->draw(WEC_arm);
	this->window_ptr->draw(WEC_spar);
	this->window_ptr->draw(WEC_float);
	wave_column.setFillColor(
		sf::Color(0, 80, 255, 100)
	);
	this->window_ptr->draw(wave_column);
	if (this->wave_res_m > 0) {
		this->frame++;
	}
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}
	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}
	if (play_phase) {
		this->drawMusteredMarbles();
	}
	this->frame++;
	return;

}	// end Wave::drawFrame()


double Wave::getProduction(double wave_res_s) {
	/*
	 *	Method to compute and return wave production.
	 */

	if (wave_res_s <= 0) {
		wave_res_s = 0;
	}
	this->wave_res_s = wave_res_s;

	// compute production based on *very* simplified dimensionless performance
	// from the model of Robertson et al (2021)
	// ASSUMPTION: H_s = c * T_e^2, with random c < 0.2184 (deep-water breaking condition)
	double prod_GW = 0;
	double prod = 0;

	// generate wave_res_m from Rayleigh distribution
	double sigma = 0.028;	// Rayleigh scale parameter (mode of dist)
	double roll = (double)rand() / RAND_MAX;
	if (roll == 1) {
		roll = 0.999999;
	}
	double scalar = sigma * sqrt(2 * log(1 / (1 - roll)));
	double wave_res_m = scalar * pow(this->wave_res_s, 2);
	if (wave_res_m > 0.2184 * pow(this->wave_res_s, 2)) {
		wave_res_m = 0.2 * pow(this->wave_res_s, 2);
	}
	this->wave_res_m = wave_res_m;

	if (wave_res_m > 0) {
		prod = 0.289 * wave_res_m -
			0.00111 * pow(wave_res_m, 2) * wave_res_s -
			0.0169 * wave_res_s;
		if (prod <= 0) {
			prod = 0;
		} else if (prod >= 1) {
			prod = 1;
		}
	}
	prod_GW = this->capacity_GW * prod;

	if (this->marble_counter < 128) {
		for (int i = 0; i < round(prod_GW); i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
			this->marble_counter++;
		}
	}

	this->prod_GW = round(prod_GW);
	if (this->prod_GW > 0) {
		this->running_flag = true;
	}
	else {
		this->running_flag = false;
	}
	return prod_GW;
}	// end Wave::getProduction()


double Wave::getDesignPeriod(void) {
	/*
	 *	Getter for design_period_s attribute
	 */

	return this->design_period_s;
}	// end Wave::getDesignPeriod();


Wave::~Wave(void) {
	/*
	 *	Destructor for Wave class
	 */

	// stream out and return
 	std::cout << "\tWave object at " << this << " destroyed." << std::endl;
 	return;
}	// end Wave::~Wave()


// ---- Plant <-- Wind ---- //

Wind::Wind(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) :
Plant(
	position_x,
	position_y,
	scale,
	window_ptr,
	assets_ptr
)
{
	/*
	 *	Constructor for Wind class
	 */

	this->height = 128;
 	this->width = 128;
	this->angle = 0;
	this->design_speed_ms = 0.47;
	this->texture_key = "wind";
	this->marble_colour = MARBLE_COLOUR_WIND;

	// stream out and return
 	std::cout << "\tWind object created at " << this << ".\n" << std::endl;
 	return;
}	// end Wind::Wind()


void Wind::drawFrame(bool selected, bool play_phase) {
	/*
	 *	Method to draw frame of Wind object
	 */

	// init
	sf::Sprite body_sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);
	std::vector<sf::Sprite> blade_sprite_vec;
	for (int i = 0; i < 3; i++) {
		blade_sprite_vec.push_back(
			sf::Sprite(
				*(this->assets_ptr->getTexture(this->texture_key)),
				sf::IntRect(0, this->height, this->width, this->height)
			)
		);
		blade_sprite_vec[i].setOrigin(64, 53);
	}

	//modify sprite to have green shading to indicate being selected
	if (selected) {
		sf::Color color(127,255,127,255);
		body_sprite.setColor(color);
		for (int i = 0; i < 3; i++) {
			blade_sprite_vec[i].setColor(color);
		}
	}

	// transformations
	body_sprite.setOrigin(this->width / 2, this->height);
	body_sprite.setPosition(
		this->position_x,
		this->position_y
	);
	for (int i = 0; i < blade_sprite_vec.size(); i++) {
		blade_sprite_vec[i].setOrigin(64, 53);
		blade_sprite_vec[i].setPosition(
			this->position_x,
			this->position_y - 75
		);
		blade_sprite_vec[i].setRotation(this->angle + i * 120);
	}

	// pulsing
	if (this->pulse_flag) {
		double pulse = 1 + 0.1 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND);

		sf::Vector2f scale = body_sprite.getScale();
		double sprite_scale_x = scale.x;
		double sprite_scale_y = scale.y;
		body_sprite.setScale(
			pulse * sprite_scale_x,
			pulse * sprite_scale_y
		);

		for (int i = 0; i < blade_sprite_vec.size(); i++) {
			scale = blade_sprite_vec[i].getScale();
			blade_sprite_vec[i].setScale(
				pulse * scale.x,
				pulse * scale.y
			);
			blade_sprite_vec[i].setPosition(
				this->position_x,
				this->position_y - 75 -
				6 * cos((2 * M_PI * this->pulse_frame) / FRAMES_PER_SECOND)
			);
		}

		this->pulse_frame++;
	}

	// update angle
	this->angle += 6 * (this->prod_GW / this->capacity_GW);

	// draw and return
	this->window_ptr->draw(body_sprite);
	for (int i = 0; i < blade_sprite_vec.size(); i++) {
		this->window_ptr->draw(blade_sprite_vec[i]);
	}
	if (this->draw_tokens) {
		//this->drawTokens();
		this->drawCapacity();
	}
	// draw price
	if (this->draw_price) {
		this->drawPrice();
	}
	if (play_phase) {
		this->drawMusteredMarbles();
	}
	this->frame++;
	return;
}	// end Wind::drawFrame()


double Wind::getProduction(double wind_res_ms) {
	/*
	 *	Method to compute and return wind production.
	 */

	if (wind_res_ms <= 0) {
		wind_res_ms = 0;
	}

	// compute production based on derived dimensionless performance
	double prod = 0;
	double prod_GW = 0;
	if (wind_res_ms > 0) {
		double turb_speed = (wind_res_ms - this->design_speed_ms) /
			this->design_speed_ms;

		// look-up on dimensionless performance curve, get dimensionless production [ ]
		if (turb_speed < -0.76 || turb_speed > 0.68) {
			prod = 0;
		} else if (turb_speed >= -0.76 && turb_speed <= 0) {
			prod = 1.03273 * exp(-5.97588 * pow(turb_speed, 2)) -
				0.03273;
		} else {
			prod = 0.16154 * exp(-9.30254 * pow(turb_speed, 2)) +
				0.83846;
		}
	}
	if (prod > 1) {
		prod = 1;
	}
	prod_GW = this->capacity_GW * prod;

	if (this->marble_counter < 128) {
		for (int i = 0; i < round(prod_GW); i++) {
			sf::Sprite* marble_sprite = new sf::Sprite(
				*(this->assets_ptr->getTexture("marble"))
			);
			marble_sprite->setTextureRect(sf::IntRect(0, 9 * 32, 32, 32));
			marble_sprite->setColor(this->marble_colour);
			marble_sprite->setOrigin(16, 16);
			this->marble_sprite_ptr_list.push_back(marble_sprite);
			this->marble_counter++;
		}
	}

	this->prod_GW = round(prod_GW);
	if (this->prod_GW > 0) {
		this->running_flag = true;
	}
	else {
		this->running_flag = false;
	}
	return prod_GW;
}	// end Wind::getProduction()


double Wind::getDesignSpeed(void) {
	/*
	 *	Getter for design_speed_ms attribute
	 */

	return this->design_speed_ms;
}	// end Wind::getDesignSpeed()


Wind::~Wind(void) {
	/*
	 *	Destructor for Wind class
	 */

	// stream out and return
 	std::cout << "\tWind object at " << this << " destroyed." << std::endl;
 	return;
}	// end Wind::~Wind()


// ---- PhaseManager ---- //

PhaseManager::PhaseManager()
{
	/*
	 *	Constructor for PhaseManager class
	 *
	 *	phases:
	 *	0 = menu -> choice of choosing gens/random/presets like AB, BC, etc.
	 *	1 = active game environment
	 *	2 = choose generators window
	 *	3 = set amount of capacity for each generator
	 */

	 //this->phase = 0;
	 this->phase = 2;
 	 this->index = 0;
	 this->max_index = 5;
	 this->max_plant_num = 10; // this is hardcoded, not sure how to count types of plants
	 this->plant_num = -1;
	 this->capacity = GW_PER_TOKEN;
	 this->capacity_tokens = TOTAL_TOKENS;
	 this->quitting_round = false;
	 this->quitting_game = false;
	 this->geothermal_present = {false, false, false, false, false, false};

	 // stream out and return
 	std::cout << "\nPhaseManager object created at " << this << "." << std::endl;
 	return;
 }	// end PhaseManager::PhaseManager()


void PhaseManager::reset(){
	this->setQuittingRound(false);
	//this->setPhase(0);
	this->setPhase(2);
	this->setIndex(0);
	this->setPlantNum(-1);
	this->setCapacity(GW_PER_TOKEN);
	this->setCapacityTokens(TOTAL_TOKENS);
	this->plant_taboo_list.clear();

	return;
}	// end PhaseManager::reset


int PhaseManager::getPhase(){
	return this->phase;
}	// end PhaseManager::getPhase()


int PhaseManager::getIndex(){
	return this->index;
}	// end PhaseManager::getIndex()


int PhaseManager::getPlantNum(){
	return this->plant_num;
}	// end PhaseManager::getPlantNum()


int PhaseManager::getCapacity(){
	return this->capacity;
}	// end PhaseManager::getCapacity()


bool PhaseManager::getQuittingRound(){
	return this->quitting_round;
}	// end PhaseManager::getQuittingRound()


bool PhaseManager::getQuittingGame(){
	return this->quitting_game;
}	// end PhaseManager::getQuittingGame()


int PhaseManager::getCapacityTokens(){
	return this->capacity_tokens;
}	// end PhaseManager::getCapacityTokens()


bool PhaseManager::getGeothermalPresent(int index){
	//std::cout << index << "\t" << this->geothermal_present.at(index) << std::endl;
	return this->geothermal_present.at(index);
}	// end PhaseManager::getGeothermalPresent()


void PhaseManager::setPhase(int new_phase){
	this->phase = new_phase;
	return;
}	// end PhaseManager::setPhase(int)


void PhaseManager::setIndex(int new_index){
	this->index = new_index;
	return;
}	// end PhaseManager::setIndex(int)


void PhaseManager::setPlantNum(int new_plant_num){
	this->plant_num = new_plant_num;
	return;
}	// end PhaseManager::setPlantNum()


void PhaseManager::setCapacity(int new_capacity){
	this->capacity = new_capacity;
	return;
}	// end PhaseManager::setCapacity()


void PhaseManager::setQuittingRound(bool new_quitting){
	this->quitting_round = new_quitting;
	return;
}	// end PhaseManager::setQuittingRound(bool)


void PhaseManager::setQuittingGame(bool new_quitting){
	this->quitting_game = new_quitting;
	return;
}	// end PhaseManager::setQuittingGame(bool)


void PhaseManager::setCapacityTokens(int new_capacity_tokens){
	this->capacity_tokens = new_capacity_tokens;
	return;
}	// end PhaseManager::setCapacityTokens()


void PhaseManager::setGeothermalPresent(int index, bool value){
	this->geothermal_present[index] = value;
	return;
}	// end PhaseManager::getGeothermalPresent()


void PhaseManager::nextValidIndex(std::vector<Plant*>* plant_ptr_vec){
	// determine which points in vector are valid
	std::vector <bool> is_index_valid;
	for (int i = 0; i < plant_ptr_vec->size(); i++) {
		if (plant_ptr_vec->at(i)->getTextureIndex() == -1){
			is_index_valid.push_back(false);
		}
		else{
			is_index_valid.push_back(true);
		}
	}

	// find next valid index and set index to that
	for (int i = 0; i < plant_ptr_vec->size(); i++) {
		int temp_index = this->index + i + 1;
		if (temp_index > this->max_index){
			temp_index -= (max_index + 1);
		}
		if (is_index_valid[temp_index]) {
			this->setIndex(temp_index);
			//std::cout << "Index:\t" << this->getIndex() << std::endl;
			break;
		}
	}

	return;
}	// end PhaseManager::nextValidIndex()


void PhaseManager::prevValidIndex(std::vector<Plant*>* plant_ptr_vec){
	// determine which points in vector are valid
	std::vector <bool> is_index_valid;
	for (int i = 0; i < plant_ptr_vec->size(); i++) {
		if (plant_ptr_vec->at(i)->getTextureIndex() == -1){
			is_index_valid.push_back(false);
		}
		else{
			is_index_valid.push_back(true);
		}
	}

	// find previous valid index and set index to that
	for (int i = 0; i < plant_ptr_vec->size(); i++) {
		int temp_index = this->index - i - 1;
		if (temp_index < 0){
			temp_index += (max_index + 1);
		}
		if (is_index_valid[temp_index]) {
			this->setIndex(temp_index);
			//std::cout << "Index:\t" << this->getIndex() << std::endl;
			break;
		}
	}

	return;
}	// end PhaseManager::prevValidIndex()


void PhaseManager::incIndex(std::vector<Plant*> plant_ptr_vec){
	/*
	 *	Method to increment index, then build plant_taboo_list
	 */

	// increment index
	this->index ++;
	//this->resetPlantNum();
	//this->resetCapacity();

	// handle wrap around
	if(this->index > this->max_index){
		this->index = 0;
	}

	// clear and re-build plant taboo list
	this->plant_taboo_list.clear();
	int texture_idx = 0;
	for (int i = 0; i < plant_ptr_vec.size(); i++) {
		// skip current position
		if (i == this->index) {
			continue;
		}

		// push back non-null texture indices
		texture_idx = plant_ptr_vec[i]->getTextureIndex();
		if (texture_idx >= 0) {
			this->plant_taboo_list.push_back(texture_idx);
		}
	}

	// print plant taboo list
	/*
	if (!this->plant_taboo_list.empty()) {
		std::cout << "plant_taboo_list = {";
		for (int i = 0; i < this->plant_taboo_list.size(); i++) {
			std::cout << this->plant_taboo_list[i] << "\t";
		}
		std::cout << "}" << std::endl;
	}
	*/

	return;
}	// end PhaseManager::incIndex()


void PhaseManager::incPlantNum(){
	/*
	 *	Method to increment Plant number during plant class selection
	 */

	// if plant taboo list empty, increment and return as before
	if (this->plant_taboo_list.empty()) {
		// increment plant_num
		this->plant_num++;

		// handle wrap around
		if(this->plant_num > this->max_plant_num){
			this->plant_num = -1;
		}

		return;
	}

	// find next non-taboo plant num
	bool taboo_flag = true;
	while (taboo_flag) {
		// increment plant_num
		this->plant_num++;

		// handle wrap around
		if(this->plant_num > this->max_plant_num){
			this->plant_num = -1;
		}

		// check plant num against taboo list
		taboo_flag = false;
		for (int i = 0; i < this->plant_taboo_list.size(); i++) {
			// if in taboo list, loop while again
			if (this->plant_num == this->plant_taboo_list[i]) {
				taboo_flag = true;
				break;
			}
		}
	}

	return;
}	// end PhaseManager::incPlantNum()


void PhaseManager::incCapacity(int GW_to_increase_by){
	if (this->capacity_tokens > 0) {
		this->capacity += GW_to_increase_by;
		this->decCapacityTokens();
	}
	else{
		std::cout << "capacity tokens less than or equal to 0" << std::endl;
	}

	return;
}	// end PhaseManager::incCapacity()


void PhaseManager::incCapacityTokens(){
	this->capacity_tokens ++;
	return;
}	// end PhaseManager::incCapacityTokens()


void PhaseManager::decIndex(std::vector<Plant*> plant_ptr_vec){
	/*
	 *	Method to decrement index, then build plant_taboo_list
	 */

	// decrement index
	this->index --;
	//this->resetPlantNum();
	//this->resetCapacity();

	// handle wrap around
	if(this->index < 0){
		this->index = this->max_index;
	}

	// clear and re-build plant taboo list
	this->plant_taboo_list.clear();
	int texture_idx = 0;
	for (int i = 0; i < plant_ptr_vec.size(); i++) {
		// skip current position
		if (i == this->index) {
			continue;
		}

		// push back non-null texture indices
		texture_idx = plant_ptr_vec[i]->getTextureIndex();
		if (texture_idx >= 0) {
			this->plant_taboo_list.push_back(texture_idx);
		}
	}

	// print plant taboo list
	/*
	if (!this->plant_taboo_list.empty()) {
		std::cout << "plant_taboo_list = {";
		for (int i = 0; i < this->plant_taboo_list.size(); i++) {
			std::cout << this->plant_taboo_list[i] << "\t";
		}
		std::cout << "}" << std::endl;
	}
	*/

	return;
}	// end PhaseManager::decIndex()


void PhaseManager::decPlantNum(){
	/*
	 *	Method to decrement Plant number during plant class selection
	 */

	// if plant taboo list empty, decrement and return as before
	if (this->plant_taboo_list.empty()) {
		// decrement plant_num
		this->plant_num--;

		// handle wrap around
		if(this->plant_num < -1){
			this->plant_num = this->max_plant_num;
		}

		return;
	}

	// find next non-taboo plant num
	bool taboo_flag = true;
	while (taboo_flag) {
		// decrement plant_num
		this->plant_num--;

		// handle wrap around
		if(this->plant_num < -1){
			this->plant_num = this->max_plant_num;
		}

		// check plant num against taboo list
		taboo_flag = false;
		for (int i = 0; i < this->plant_taboo_list.size(); i++) {
			// if in taboo list, loop while again
			if (this->plant_num == this->plant_taboo_list[i]) {
				taboo_flag = true;
				break;
			}
		}
	}

	return;
}	// end PhaseManager::decPlantNum()


void PhaseManager::decCapacity(int GW_to_decrease_by){
	if (this->capacity > GW_to_decrease_by) {
		this->capacity -= GW_to_decrease_by;
		this->incCapacityTokens();
	}

	return;
}	// end PhaseManager::decCapacity()


void PhaseManager::decCapacityTokens(){
	this->capacity_tokens --;
	return;
}	// end PhaseManager::decCapacityTokens()


int PhaseManager::hydroStorageTable(int GW_capacity){
	std::vector<int> capacities = {16, 29, 40, 49, 56, 63, 70, 77, 84, 91, 98, 104, 110, 116, 122, 128, 134, 140};
	if (GW_capacity > capacities.size()) {
		return capacities.back();
	}
	else{
		return capacities[capacity-1];
	}
}	// end PhaseManager::hydroStorageTable(int)


PhaseManager::~PhaseManager(void) {
 	/*
 	 *	Destructor for PhaseManager class
 	 */

 	// stream out and return
 	std::cout << "PhaseManager object at " << this << " destroyed.\n" << std::endl;
 	return;
}	// end PhaseManager::~PhaseManager()


// ---- PictorialTutorial ---- //

PictorialTutorial::PictorialTutorial(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr
) {
	/*
	*	Constructor for PictorialTutorial class
	*/
	this->show_wasd_instructions_ws = true;
	this->show_wasd_instructions_ad = true;
	this->show_spacebar_instructions = false;

	this->w_presses_during_game = 0;

	this->frame = 0;
	this->heights = {256, 128};
	this->n_sprites = {9, 9};
	this->sprite_idx = {0, 0};
	this->widths = {256, 512};
	this->position_x = position_x;
	this->position_y = position_y;
	this->rel_pos_x = {0, -128};
	this->rel_pos_y = {0, 200};
	std::vector<double> temp_scales (2, scale);
	this->scales = temp_scales;
	this->texture_keys = {"wasd", "spacebar"};

	this->ws_indices = {0, 1, 2, 3, 4, 3, 2, 1, 0};
	this->ad_indices = {0, 5, 6, 7, 8, 7, 6, 5, 0};
	this->spacebar_indices = {0, 1, 2, 3, 4, 3, 2, 1, 0};

	this->window_ptr = window_ptr;
	this->assets_ptr = assets_ptr;

	// stream out and return
	std::cout << "\nPictorialTutorial object created at " << this << "." << std::endl;
	return;
}	// end PictorialTutorial::PictorialTutorial()


void PictorialTutorial::reset(){
	 this->show_wasd_instructions_ws = true;
     this->show_wasd_instructions_ad = true;
	 this->show_spacebar_instructions = false;
	 this->w_presses_during_game = 0;
} // end PictorialTutorial::reset()


void PictorialTutorial::drawFrame(int phase) {
	/*
	*	Method to draw frame highlighting PictorialTutorial object
	*/

	sf::Text info_txt(
		"CONTROLS",
		*(this->assets_ptr->getFont("bold")),
		20
	);

	for (int i = 0; i < texture_keys.size(); i++) {

		// init
		sf::Sprite sprite(
			*(this->assets_ptr->getTexture(this->texture_keys[i])),
			sf::IntRect(0, 0, this->widths[i], this->heights[i])
		);

		// draw ad highlighting
		if (this->show_wasd_instructions_ad && this->texture_keys[i] == "wasd") {
			sprite.setTextureRect(
				sf::IntRect(
					0,
					this->ad_indices[this->sprite_idx[i]] * this->heights[i],
					this->widths[i],
					this->heights[i]
				)
			);
			if (this->frame >= FRAMES_PER_BLIT) {
				this->sprite_idx[i]++;
				this->frame = 0;
				if (this->sprite_idx[i] > this->n_sprites[i] - 1) {
					this->sprite_idx[i] = 0;
				}
			}
			// set text
			info_txt.setString("MOVE LEFT AND RIGHT");
		}

		// draw ws highlighting
		else if (this->show_wasd_instructions_ws && this->texture_keys[i] == "wasd") {
			sprite.setTextureRect(
				sf::IntRect(
					0,
					this->ws_indices[this->sprite_idx[i]] * this->heights[i],
					this->widths[i],
					this->heights[i]
				)
			);
			if (this->frame >= FRAMES_PER_BLIT) {
				this->sprite_idx[i]++;
				this->frame = 0;
				if (this->sprite_idx[i] > this->n_sprites[i] - 1) {
					this->sprite_idx[i] = 0;
				}
			}

			// set text
			switch (phase) {
				case 1:
				info_txt.setString("CHANGE POWER TO BE SENT");
				break;

				case 2:
				info_txt.setString("CHANGE POWER PLANT TYPE");
				break;

				case 3:
				info_txt.setString("CHANGE POWER PLANT CAPACITY");
				break;
			}

		}
		// draw wasd
		else if (this->sprite_idx[i] != 0 && this->texture_keys[i] == "wasd") {
			this->sprite_idx[i] = 0;
			sprite.setTextureRect(
				sf::IntRect(
					0,
					this->sprite_idx[i] * this->heights[i],
					this->widths[i],
					this->heights[i]
				)
			);
		}
		// draw spacebar
		else if (this->show_spacebar_instructions && this->texture_keys[i] == "spacebar") {
			sprite.setTextureRect(
				sf::IntRect(
					0,
					this->spacebar_indices[this->sprite_idx[i]] * this->heights[i],
					this->widths[i],
					this->heights[i]
				)
			);
			if (this->frame >= FRAMES_PER_BLIT) {
				this->sprite_idx[i]++;
				this->frame = 0;
				if (this->sprite_idx[i] > this->n_sprites[i] - 1) {
					this->sprite_idx[i] = 0;
				}
			}

			// set text
			switch (phase) {
				case 1:
				info_txt.setString("SEND POWER TO CITY");
				break;

				case 2:
				info_txt.setString("PROCEED TO SETTING PLANT CAPACITIES");
				break;

				case 3:
				info_txt.setString("PROCEED TO GAME");
				break;
			}
		}

		// transformations
		sprite.setPosition(
			this->position_x + this->rel_pos_x[i],
			this->position_y + this->rel_pos_y[i]
		);

		// draw sprite
		if (this->texture_keys[i] != "spacebar" || this->show_spacebar_instructions) {
			this->window_ptr->draw(sprite);
		}

	}// end for each sprite

	// draw descriptive text
	info_txt.setOrigin(
		info_txt.getLocalBounds().width / 2,
		info_txt.getLocalBounds().height / 2
	);
	info_txt.setPosition(
		this->position_x + this->widths[0] / 2,
		this->position_y + this->heights[0] * 0.8
	);

	this->window_ptr->draw(info_txt);

	this->frame++;
	return;
}	// end PictorialTutorial::drawFrame()


void PictorialTutorial::update(PhaseManager* phase_manager, std::vector<Plant*>* plant_ptr_vec){
	switch (phase_manager->getPhase()) {
		case 2:
			{
				bool all_plants_selected = true;
				for (int i = 0; i < plant_ptr_vec->size(); i++) {
					if (plant_ptr_vec->at(i)->getTextureIndex() == -1) {
						all_plants_selected = false;
					}
				}
				if (all_plants_selected) {
					this->show_spacebar_instructions = true;
				}
			}
			break;

		case 3:
			if (phase_manager->getCapacityTokens() == 0) {
				this->show_spacebar_instructions = true;
			}
	}
}// end PictorialTutorial::update()


PictorialTutorial::~PictorialTutorial(void) {
 /*
	*	Destructor for PictorialTutorial class
	*/

 // stream out and return
 std::cout << "PictorialTutorial object at " << this << " destroyed.\n" << std::endl;
 return;
}	// end PictorialTutorial::~PictorialTutorial()



// ---- DiceRoll ---- //

DiceRoll::DiceRoll(
	int position_x,
	int position_y,
	double scale,
	sf::RenderWindow* window_ptr,
	Assets* assets_ptr)
{
	/*
	*	Constructor for DiceRoll class
	*/
	this->dice_num = 1;
	this->roll_num = 0;
	this->rolling_dice = true;
	this->rolls_left = {0, 0, 0, 0, 0, 0};
	this->geothermal_rolls = {0, 0, 0};

	this->spacebar_frame_idx = 0;
	this->spacebar_frame_vec = {0, 1, 2, 3, 4, 3, 2, 1, 0};

	this->frame = 0;
	this->height = 32;
	this->n_sprites = 6;
	this->sprite_idx = 1;
	this->width = 32;
	this->position_x = position_x;
	this->position_y = position_y;
	this->scale = scale;
	this->texture_key = "dice";

	this->window_ptr = window_ptr;
	this->assets_ptr = assets_ptr;

	// stream out and return
	std::cout << "\nDiceRoll object created at " << this << "." << std::endl;
	return;
}	// end DiceRoll::DiceRoll()


void DiceRoll::reset(){
	this->dice_num = 1;
	this->roll_num = 0;
	this->rolling_dice = true;
	this->rolls_left = {0, 0, 0, 0, 0, 0};
	this->geothermal_rolls = {0, 0, 0};

	this->spacebar_frame_idx = 0;
	this->spacebar_frame_vec = {0, 1, 2, 3, 4, 3, 2, 1, 0};

	this->frame = 0;
	this->height = 32;
	this->n_sprites = 6;
	this->sprite_idx = 1;
	this->width = 32;
	this->position_x = position_x;
	this->position_y = position_y;
	this->scale = scale;
	this->texture_key = "dice";

	/*
	this->setRollingDice(true);
	this->resetGeothermalRolls();
	for (int i = 0; i < this->rolls_left.size(); i++) {
		this->rolls_left.at(i) = 0;
	}
	*/
} // end DiceRoll::reset()


void DiceRoll::resetGeothermalRolls(){
	for (int i = 0; i < this->geothermal_rolls.size(); i++) {
		this->geothermal_rolls[i] = 0;
	}
	return;
}	// end DiceRoll::resetGeothermalRolls


bool DiceRoll::getRollingDice(){
	return this->rolling_dice;
}	// end DiceRoll::getRollingDice()


int DiceRoll::getDiceNum(){
	return this->dice_num;
} // end DiceRoll::getDiceNum


int DiceRoll::getRollsLeft(int i){
	return this->rolls_left.at(i);
} // end DiceRoll::getRollsLeft


int DiceRoll::getGeothermalCapacity(){
	/*
	for (int i = 0; i < this->geothermal_rolls.size(); i++) {
		if (this->geothermal_rolls[i] == 0) {
			std::cout << "Geothermal rolls value is 0 when it should be between 1 and 6" << std::endl;
			return 0;
		}
	}
	*/

	int ret_val = 0;
	/*
	//first roll

	if (this->geothermal_rolls[0] <= 3) {
		ret_val++;
		//second roll
		if (geothermal_rolls[1] <= 4) {
			ret_val++;
			//third roll
			if (geothermal_rolls[2] <= 5) {
				ret_val++;
			}
			//third roll
			else{
				// nothing
			}
		}
		//second roll
		else{
			//third roll
			if (geothermal_rolls[2] <= 3) {
				ret_val++;
			}
			//third roll
			else{
				// nothing
			}
		}
	}
	//first roll
	else{
		//second roll
		if (geothermal_rolls[1] <= 2) {
			ret_val++;
			//third roll
			if (geothermal_rolls[2] <= 3) {
				ret_val++;
			}
			//third roll
			else{
				// nothing
			}
		}
		//second roll
		else{
			//third roll
			if (geothermal_rolls[2] <= 1) {
				ret_val++;
			}
			//third roll
			else{
				// nothing
			}
		}
	}
	*/

//std::cout << "roll num in getGeothermalCapacity:\t" << this->roll_num << std::endl;

	switch (this->roll_num) {
		case 0:
			if (this->geothermal_rolls[0] <= 3) {
				ret_val++;
			}
			break;

		case 1:
		//first roll
		if (this->geothermal_rolls[0] <= 3) {
			//second roll
			if (geothermal_rolls[1] <= 4) {
				ret_val++;
			}
		}
		//first roll
		else{
			//second roll
			if (geothermal_rolls[1] <= 2) {
				ret_val++;
			}
		}
			break;

		case 2:
		//first roll
		if (this->geothermal_rolls[0] <= 3) {
			//second roll
			if (geothermal_rolls[1] <= 4) {
				//third roll
				if (geothermal_rolls[2] <= 5) {
					ret_val++;
				}
			}
			//second roll
			else{
				//third roll
				if (geothermal_rolls[2] <= 3) {
					ret_val++;
				}
			}
		}
		//first roll
		else{
			//second roll
			if (geothermal_rolls[1] <= 2) {
				//third roll
				if (geothermal_rolls[2] <= 3) {
					ret_val++;
				}
			}
			//second roll
			else{
				//third roll
				if (geothermal_rolls[2] <= 1) {
					ret_val++;
				}
				//third roll
			}
		}
			break;
	}
	std::cout << "Adding:\t" << ret_val << std::endl;
	return ret_val;
} // end DiceRoll::getGeothermalCapacity


void DiceRoll::setRollingDice(bool rolling_dice_input){
	this->rolling_dice = rolling_dice_input;
	if (rolling_dice_input) {
			this->roll_num++;
			if (this->roll_num > 2) {
				this->roll_num = 0;
				this->resetGeothermalRolls();
			}
	}
	//std::cout << "roll num in setRollingDice:\t\t" << this->roll_num << std::endl;
}	// end DiceRoll::setRollingDice()


void DiceRoll::setRollsLeft(int i, int rolls_left_input){
	this->rolls_left.at(i) = rolls_left_input;
}	// end DiceRoll::setRollsLeft()


bool DiceRoll::setGeothermalRolls(){
	for (int i = 0; i < this->geothermal_rolls.size(); i++) {
		if (this->geothermal_rolls[i] == 0) {
			this->geothermal_rolls[i] = this->dice_num;
			break;
		}
	} // end DiceRoll::setGeothermalRolls()

	// display info
	std::cout << "roll values:\t";
	for (int i = 0; i < this->geothermal_rolls.size(); i++) {
		std::cout << this->geothermal_rolls[i] << "\t";
	}
	std::cout << std::endl;

	// if have completed two rolls already
	//std::cout << "roll num in setGeothermalRolls:\t\t" << this->roll_num << std::endl;
	if (this->roll_num >= 2) {
		return true;
	}
	else{
		return false;
	}

}	// end PhaseManager::setGeothermalRolls()


void DiceRoll::randDiceNum(){
	 // make value from 1-6 but not same as previous number to make animation smooth
	 int temp =  rand() % 6 + 1;
	 while (temp == this->dice_num) {
		 temp =  rand() % 6 + 1;
	 }
	this->dice_num = temp;
	//std::cout << this->dice_num << std::endl;
} // end DiceRoll::randDiceNum


void DiceRoll::drawFrame(bool new_num) {
	/*
	*	Method to draw frame of DiceRoll object
	*/

	sf::Text info_txt(
		"",
		*(this->assets_ptr->getFont("bold")),
		20
	);

	sf::Text info_txt_l(
		"",
		*(this->assets_ptr->getFont("bold")),
		20
	);

	sf::Text info_txt_r(
		"",
		*(this->assets_ptr->getFont("bold")),
		20
	);

	sf::Text spacebar_txt(
		"",
		*(this->assets_ptr->getFont("bold")),
		20
	);


	// init
	sf::Sprite sprite(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);

	sf::Sprite sprite1(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);

	sf::Sprite sprite2(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);

	sf::Sprite sprite3(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);

	sf::Sprite sprite4(
		*(this->assets_ptr->getTexture(this->texture_key)),
		sf::IntRect(0, 0, this->width, this->height)
	);

	sf::Sprite spacebar_sprite(
		*(this->assets_ptr->getTexture("spacebar"))
	);
	int rolls_left_sum = 0;
	for (int i = 0; i < this->rolls_left.size(); i++) {
		rolls_left_sum += this->rolls_left[i];
	}
	if (new_num) {
		spacebar_txt.setString("STOP DRILLING (STOP DICE)");
	}
	else if (rolls_left_sum <= 0) {	// this logic only works when limited to a single instance of each class of Plant!
		spacebar_txt.setString("FINISH");
	}
	else {
		spacebar_txt.setString("START DRILLING (ROLL DICE)");
	}
	spacebar_sprite.setTextureRect(
		sf::IntRect(
			0,
			128 * this->spacebar_frame_vec[this->spacebar_frame_idx],
			512,
			128
		)
	);
	spacebar_sprite.setPosition(
		0.70 * SCREEN_WIDTH - 128,
		0.03 * SCREEN_HEIGHT + 200
	);
	spacebar_txt.setOrigin(
		spacebar_txt.getLocalBounds().width / 2.0,
		spacebar_txt.getLocalBounds().height / 2.0
	);
	spacebar_txt.setPosition(
		0.70 * SCREEN_WIDTH + 128,
		0.03 * SCREEN_HEIGHT + 205
	);

	std::vector<sf::Sprite*> static_sprites = {&sprite1, &sprite2, &sprite3, &sprite4};

	// draw dice
	sprite.setTextureRect(
		sf::IntRect(
			0,
			(sprite_idx - 1) * this->height,
			this->width,
			this->height
		)
	);

	// set text
	info_txt.setString("");


	// transformations
	sprite.setScale(this->scale, this->scale);

	sprite.setPosition(
		this->position_x - this->width*this->scale/2,
		this->position_y - this->height*this->scale/2
	);

	// draw sprite
	this->window_ptr->draw(sprite);

	// draw descriptive text
	info_txt.setOrigin(
		info_txt.getLocalBounds().width / 2,
		info_txt.getLocalBounds().height / 2
	);
	info_txt.setPosition(
		this->position_x + this->width / 2,
		this->position_y + this->height * 0.8
	);

	this->window_ptr->draw(info_txt);

	// draw static_sprites
	for (int i = 0; i < static_sprites.size(); i++) {
		// need logic here to set sprite_idx
		int static_sprites_idx = 1;
		switch (i) {
			case 0:
				static_sprites_idx = 1;
				break;
			case 1:
				switch (this->roll_num) {
					case 0:
						static_sprites_idx = 3;
						break;
					case 1:
						if (this->geothermal_rolls[0] <= 3) {
							static_sprites_idx = 4;
						}
						else{
							static_sprites_idx = 2;
						}
						break;
					case 2:
						if (this->geothermal_rolls[0] <= 3) {
							if (this->geothermal_rolls[1] <= 4) {
								static_sprites_idx = 5;
							}
							else{
								static_sprites_idx = 3;
							}
						}
						else{
							if (this->geothermal_rolls[1] <= 2) {
								static_sprites_idx = 3;
							}
							else{
								static_sprites_idx = 1;
							}
						}
						break;
				}
				break;
			case 2:
				switch (this->roll_num) {
					case 0:
						static_sprites_idx = 4;
						break;
					case 1:
					if (this->geothermal_rolls[0] <= 3) {
						static_sprites_idx = 5;
					}
					else{
						static_sprites_idx = 3;
					}
						break;
					case 2:
						if (this->geothermal_rolls[0] <= 3) {
							if (this->geothermal_rolls[1] <= 4) {
								static_sprites_idx = 6;
							}
							else{
								static_sprites_idx = 4;
							}
						}
						else{
							if (this->geothermal_rolls[1] <= 2) {
								static_sprites_idx = 4;
							}
							else{
								static_sprites_idx = 2;
							}
						}
						break;
				}
				break;
			case 3:
				static_sprites_idx = 6;
				break;
}

		// draw dice
		static_sprites[i]->setTextureRect(
			sf::IntRect(
				0,
				(static_sprites_idx - 1) * this->height,
				this->width,
				this->height
			)
		);

		// transformations
		static_sprites[i]->setScale(this->scale, this->scale);

		int static_sprite_position = i;
		if (i > 1) {
			static_sprite_position++;
		}

		static_sprites[i]->setPosition(
			this->position_x + this->width*this->scale*1.5*(static_sprite_position - 2) - this->width*this->scale/2,
			this->position_y + this->height*this->scale*2 - this->height*this->scale/2
		);

		// draw sprite
		this->window_ptr->draw(*static_sprites.at(i));

	}

	// set text
	info_txt_l.setString("                                       -                          \n\n                         SUCCESS: +1 GW");
	info_txt_r.setString("                                       -                          \n\n                         FAILURE: +0 GW");

	// draw descriptive text

	info_txt_l.setOrigin(
		info_txt_l.getLocalBounds().width / 2,
		info_txt_l.getLocalBounds().height / 2
	);

	info_txt_r.setOrigin(
		info_txt_r.getLocalBounds().width / 2,
		info_txt_r.getLocalBounds().height / 2
	);

	info_txt_l.setPosition(
		this->position_x - this->width*this->scale*2.25 - this->width*this->scale/2,
		this->position_y + this->height*this->scale*2.8 - this->height*this->scale/2
	);

	info_txt_r.setPosition(
		this->position_x + this->width*this->scale*2.25 - this->width*this->scale/2,
		this->position_y + this->height*this->scale*2.8 - this->height*this->scale/2
	);

	this->window_ptr->draw(info_txt_l);
	this->window_ptr->draw(info_txt_r);

	// draw spacebar instructions
	this->window_ptr->draw(spacebar_sprite);
	this->window_ptr->draw(spacebar_txt);


	// handle frame events
	if (this->frame >= FRAMES_PER_BLIT) {
		this->spacebar_frame_idx++;
		if (this->spacebar_frame_idx >= this->spacebar_frame_vec.size()) {
			this->spacebar_frame_idx = 0;
		}

		if (new_num) {
			this->randDiceNum();
		}

		this->sprite_idx = this->dice_num;

		this->frame = 0;
	}
	this->frame++;

	return;
}	// end DiceRoll::drawFrame()


DiceRoll::~DiceRoll(void) {
 /*
	*	Destructor for DiceRoll class
	*/

 // stream out and return
 std::cout << "DiceRoll object at " << this << " destroyed.\n" << std::endl;
 return;
}	// end DiceRoll::~DiceRoll()



// ---- Game ---- //

Game::Game(sf::RenderWindow* window_ptr) :
key_vec(sf::Keyboard::KeyCount, false),
assets(),
phase_manager(),
pictorial_tutorial(0.70*SCREEN_WIDTH, 0.03*SCREEN_HEIGHT, 1, window_ptr, &(this->assets)),
dice_roll(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 2, window_ptr, &(this->assets)),
overcast_clouds(window_ptr, &(this->assets)),
foreground(window_ptr, &(this->assets)),
music_player(&(this->assets), window_ptr),
sky_disk(window_ptr, &(this->assets)),
text_box(&(this->assets), window_ptr),
wind_sock(window_ptr, &(this->assets))
{
	/*
	 *	Constructor for Game class
	 */

	// init attributes
	this->draw_frame_rate = false;
	this->music_paused = false;
	this->powered_flag = true;
	this->draw_energy_overlay = false;
	this->draw_forecast_overlay = false;
	this->can_defer_load = true;
	this->frame = 0;
	this->rolls_rem_corr = 0;
	this->coal_marbles = 0;
	this->combined_marbles = 0;
	this->peaker_marbles = 0;
	this->current_energy_demand_GWh = 0;
	this->excess_dispatch_GWh = 0;
	this->dt_s = 0;
	this->frame_time_s = 0;
	this->hour_of_day = 0;
	this->next_hour_of_day = 0;
	this->time_since_run_s = 0;
	this->cloud_cover_ratio = 0;
	this->next_cloud_cover_ratio = 0;
	this->wind_speed_ratio = 0;
	this->next_wind_speed_ratio = 0;
	this->smog_ratio = 0;
	this->next_smog_ratio = 0;
	this->wave_res_s = 0;
	this->next_wave_res_s = 0;
	this->score = 0;
	this->fade_alpha = 255;
	this->points_str = "";

	this->forecast_map["demand GWh"] = 0;
	this->forecast_map["solar forecast GWh"] = 0;
	this->forecast_map["solar forecast error GWh"] = 0;
	this->forecast_map["tidal forecast GWh"] = 0;
	this->forecast_map["tidal forecast error GWh"] = 0;
	this->forecast_map["wave forecast GWh"] = 0;
	this->forecast_map["wave forecast error GWh"] = 0;
	this->forecast_map["wind forecast GWh"] = 0;
	this->forecast_map["wind forecast error GWh"] = 0;

	this->window_ptr = window_ptr;

	sf::RectangleShape black_rect(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	black_rect.setFillColor(sf::Color(0, 0, 0, 255));
	this->window_ptr->draw(black_rect);
	this->window_ptr->display();

	this->energy_demand_GWh_vec = {
		13, 13, 13, 15, 16, 18,
		19, 20, 20, 20, 19, 18,
		18, 18, 19, 21, 22, 21,
		20, 18, 17, 15, 14
	};

	this->tidal_idx_offset = round(23 * (double)rand() / RAND_MAX);
	this->tidal_res_ms_vec = {
		0.125, 0.279, 0.265, 0.106, 0.076, 0.221,
		0.645, 0.918, 1,     0.913, 0.744, 0.487,
		0.104, 0.323, 0.621, 0.670, 0.621, 0.483,
		0.157, 0.181, 0.497, 0.609, 0.565
	};

	// ---- load assets ---- //

	// sf::Font
	{
		this->assets.loadFont("assets/font/Roboto-Thin.ttf", "teletype");
		this->assets.loadFont("assets/font/OpenSans-Bold.ttf", "bold");
	}

	sf::Text loading_text(
		"Loading ...",
		*(this->assets.getFont("bold")),
		32
	);
	loading_text.setOrigin(
		loading_text.getLocalBounds().width / 2,
		loading_text.getLocalBounds().height / 2
	);
	loading_text.setPosition(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2
	);
	this->window_ptr->draw(loading_text);
	this->window_ptr->display();

	// sf::Texture
	{
		// in-play assets
		this->assets.loadTexture("assets/sheets/capacity_token_32x32_1fr.png", "capacity token");
		this->assets.loadTexture("assets/sheets/clock_32x32_3fr.png", "clock");
		this->assets.loadTexture("assets/sheets/clouds_64x32_6fr.png", "clouds");
		this->assets.loadTexture("assets/sheets/coal_128x128_9fr.png", "coal");
		this->assets.loadTexture("assets/sheets/combined_128x128_9fr.png", "combined");
		this->assets.loadTexture("assets/sheets/emissions_8x8_2fr.png", "emissions");
		this->assets.loadTexture("assets/sheets/energy_demand_32x32_1fr.png", "energy demand");
		this->assets.loadTexture("assets/sheets/fission_128x128_9fr.png", "fission");
		this->assets.loadTexture("assets/sheets/foreground_640x480_3fr.png", "foreground");
		this->assets.loadTexture("assets/sheets/geothermal_128x128_9fr.png", "geothermal");
		this->assets.loadTexture("assets/sheets/hydro_128x128_5fr.png", "hydro");
		this->assets.loadTexture("assets/sheets/marble_32x32_19fr.png", "marble");
		this->assets.loadTexture("assets/images/MM_256x116.png", "MM logo");
		this->assets.loadTexture("assets/sheets/overcast_640x480_1fr.png", "overcast");
		this->assets.loadTexture("assets/sheets/peaker_128x128_7fr.png", "peaker");
		this->assets.loadTexture("assets/sheets/power_cap_32x32_1fr.png", "power capacity");
		this->assets.loadTexture("assets/sheets/price_per_GW_32x32_1fr.png", "price per GW");
		this->assets.loadTexture("assets/sheets/skydisk_960x960_2fr.png", "sky disk");
		this->assets.loadTexture("assets/sheets/solar_128x128_1fr.png", "solar");
		this->assets.loadTexture("assets/sheets/storage_128x128_1fr.png", "storage");
		this->assets.loadTexture("assets/sheets/tidal_128x128_2fr.png", "tidal");
		this->assets.loadTexture("assets/sheets/wave_128x128_3fr.png", "wave");
		this->assets.loadTexture("assets/sheets/wind_128x128_2fr.png", "wind");
		this->assets.loadTexture("assets/sheets/wind_sock_48x64_2fr.png", "wind sock");
		this->assets.loadTexture("assets/sheets/wasd_256x256_9fr.png", "wasd");
		this->assets.loadTexture("assets/sheets/spacebar_512x128_5fr.png", "spacebar");
		this->assets.loadTexture("assets/sheets/dice_32x32_6fr.png", "dice");

		// selection assets
		this->assets.loadTexture("assets/sheets/blank_128x128_1fr.png", "blank");
		this->assets.loadTexture("assets/sheets/null_128x128_1fr.png", "null");
		this->assets.loadTexture("assets/sheets/null_green_128x128_1fr.png", "null green");
		this->assets.loadTexture("assets/sheets/tidal_128x128_1fr.png", "tidal selection");
		this->assets.loadTexture("assets/sheets/wave_128x128_1fr.png", "wave selection");
		this->assets.loadTexture("assets/sheets/wind_128x128_1fr.png", "wind selection");
	}

	// sf::Sound
	{
		this->assets.loadSound(
			"assets/audio/samples/mixkit-electronics-power-up-2602.ogg",
			"powering up"
		);

		this->assets.loadSound(
			"assets/audio/samples/power-down.ogg",
			"powering down"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-quick-lock-sound-2854.ogg",
			"A D key"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-computer-digital-lock-2859.ogg",
			"S key"
		);

		this->assets.loadSound(
			"assets/audio/samples/W-key.ogg",
			"W key"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-magical-coin-win-1936.ogg",
			"capacity token"
		);

		this->assets.loadSound(
			"assets/audio/samples/token-return.ogg",
			"token return"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-synthetic-power-bass-transition-2296.ogg",
			"dispatch"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-arcade-retro-changing-tab-206.ogg",
			"P key"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-positive-notification-951.ogg",
			"transition complete"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-melodic-clock-strike-1057.ogg",
			"clock chime"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-single-book-paging-1101.ogg",
			"page right"
		);

		this->assets.loadSound(
			"assets/audio/samples/page-left.ogg",
			"page left"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-quick-paper-crumple-sound-2996.ogg",
			"paper crumple"
		);

		this->assets.loadSound(
			"assets/audio/samples/mixkit-apartment-buzzer-bell-press-932.ogg",
			"buzzer"
		);
	}

	// sf::Music
	{
		this->music_player.addTrack(
			"assets/audio/tracks/Background_electronic_modern_music.ogg",
			"A:  Alexander Blu - Background Electronic Modern Music (CC BY 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Cinematic_electronic_track.ogg",
			"B:  Alexander Blu - Cinematic Electronic Track (CC BY-NC 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Deep_ambient_electronic_music.ogg",
			"C:  Alexander Blu - Deep Ambient Electronic Music (CC BY 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Downtempo_chill_out_track.ogg",
			"D:  Alexander Blu - Downtempo Chill Out Track (CC BY-NC 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Downtempo_electronic_music.ogg",
			"E:  Alexander Blu - Downtempo Electronic Music (CC BY-NC 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Electronic_house_downtempo_music.ogg",
			"F:  Alexander Blu - Electronic House Downtempo Music (CC BY-NC 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Electronic_modern_music.ogg",
			"G:  Alexander Blu - Modern Electronic Music (CC BY-NC 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Electro_session_ambient_electronic_lounge_music.ogg",
			"H:  Alexander Blu - Ambient Electronic Lounge Music Electro Session (CC BY-NC 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Hi_tech_electronic_background_music.ogg",
			"I:  Alexander Blu - Hi Tech Electronic Background Music (CC BY-NC 4.0)"
		);
		this->music_player.addTrack(
			"assets/audio/tracks/Soft_techno_music.ogg",
			"J:  Alexander Blu - Techno Soft Music (CC BY-NC 4.0)"
		);
	}

	// ---- end load assets ---- //

	// build sprites
	this->overcast_clouds.buildSprites();
	this->foreground.buildSprites();
	this->sky_disk.buildSprites();
	this->wind_sock.buildSprites();

	sf::Vector2f scale;
	double scalar = 1.5;

	this->capacity_token_sprite.setTexture(*(this->assets.getTexture("capacity token")));
	this->capacity_token_sprite.setOrigin(16, 16);
	scale = this->capacity_token_sprite.getScale();
	this->capacity_token_sprite.setScale(scalar * scale.x, scalar * scale.y);

	this->energy_demand_sprite.setTexture(*(this->assets.getTexture("energy demand")));
	this->energy_demand_sprite.setOrigin(16, 16);
	scale = this->energy_demand_sprite.getScale();
	this->energy_demand_sprite.setScale(scalar * scale.x, scalar * scale.y);

	this->clock_face_sprite.setTexture(*(this->assets.getTexture("clock")));
	this->clock_face_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	this->clock_face_sprite.setOrigin(16, 16);
	scale = this->clock_face_sprite.getScale();
	this->clock_face_sprite.setScale(scalar * scale.x, scalar * scale.y);

	this->clock_minute_sprite.setTexture(*(this->assets.getTexture("clock")));
	this->clock_minute_sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
	this->clock_minute_sprite.setOrigin(16, 16);
	scale = this->clock_minute_sprite.getScale();
	this->clock_minute_sprite.setScale(scalar * scale.x, scalar * scale.y);

	this->clock_hour_sprite.setTexture(*(this->assets.getTexture("clock")));
	this->clock_hour_sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
	this->clock_hour_sprite.setOrigin(16, 16);
	scale = this->clock_hour_sprite.getScale();
	this->clock_hour_sprite.setScale(scalar * scale.x, scalar * scale.y);

	// init plant_ptr_vec with 6x base class (as "null plant")
	this->initPlants();

	// stream out and return
	std::cout << "\nGame object created at " << this << "." << std::endl;
	return;
}	// end Game::Game()


void Game::renderTitle(void) {
	/*
	 *	Method to play title
	 */

	// init
	bool animation_finished = false;
	int animation_state = 0;
	double black_rect_alpha = 255;
	double scalar = 1;
	double hour_of_day = 1;
	double wind_speed_ratio = 0.4;
	double cloud_cover_ratio = 0.25;

	sf::Event event;

	sf::Vector2f scale;

	sf::RectangleShape black_rect(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	black_rect.setFillColor(sf::Color(0, 0, 0, black_rect_alpha));

	sf::Sprite MM_logo(*(this->assets.getTexture("MM logo")));
	MM_logo.setOrigin(
		MM_logo.getLocalBounds().width / 2,
		MM_logo.getLocalBounds().height / 2
	);
	MM_logo.setPosition(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2
	);

	sf::Text blink_instructions(
		"Press any key to play",
		*(this->assets.getFont("bold")),
		32
	);
	blink_instructions.setOrigin(
		blink_instructions.getLocalBounds().width / 2,
		blink_instructions.getLocalBounds().height / 2
	);
	blink_instructions.setPosition(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2 + 45
	);

	Plant* plant = new Fission(0, 0, 1, this->window_ptr, &(this->assets));
	plant->setPowerCapacity(3);
	plant->setDrawTokens(false);
	plant->setRunning(true);
	plant->setDrawPrice(false);
	this->pushPlant(0, plant);

	plant = new Combined(0, 0, 1, this->window_ptr, &(this->assets));
	plant->setPowerCapacity(3);
	plant->setDrawTokens(false);
	plant->setRunning(true);
	plant->setDrawPrice(false);
	this->pushPlant(1, plant);

	plant = new Peaker(0, 0, 1, this->window_ptr, &(this->assets));
	plant->setPowerCapacity(3);
	plant->setDrawTokens(false);
	plant->setRunning(true);
	plant->setDrawPrice(false);
	this->pushPlant(2, plant);

	plant = new Solar(0, 0, 1, this->window_ptr, &(this->assets));
	plant->setPowerCapacity(3);
	plant->setDrawTokens(false);
	double solar_res_kWm2 = 0;
	if (hour_of_day > 5.5 && hour_of_day < 17.5) {
		if (hour_of_day <= 10) {
			solar_res_kWm2 = (2.0 / 9.0) * hour_of_day - (11.0 / 9.0);
		}
		else if (hour_of_day >= 14) {
			solar_res_kWm2 = (-2.0 / 7.0) * hour_of_day + 5.0;
		}
		else {
			solar_res_kWm2 = 1;
		}
		solar_res_kWm2 *= (1 - cloud_cover_ratio);
	}
	plant->getProduction(solar_res_kWm2);
	plant->setDrawPrice(false);
	this->pushPlant(3, plant);

	plant = new Wind(0, 0, 1, this->window_ptr, &(this->assets));
	plant->setPowerCapacity(3);
	plant->setDrawTokens(false);
	plant->getProduction(wind_speed_ratio);
	plant->setDrawPrice(false);
	this->pushPlant(4, plant);

	plant = new Hydro(0, 0, 1, this->window_ptr, &(this->assets));
	plant->setPowerCapacity(3);
	plant->setDrawTokens(false);
	plant->setDrawCharge(false);
	plant->setEnergyCapacity(100);
	plant->setCharge(100);
	plant->setRunning(true);
	plant->setDrawPrice(false);
	this->pushPlant(5, plant);

	// animation (blocking while loop)
	while (this->window_ptr->isOpen() && !animation_finished) {
		// mark time
		this->time_since_run_s = this->clock.getElapsedTime().asSeconds();

		// if clock tick
		if (
			this->time_since_run_s >= (this->frame + 1) * SECONDS_PER_FRAME
		) {
			// state dependent animation
			switch (animation_state) {
				case (0):	// fade in
					this->window_ptr->clear();
					this->window_ptr->draw(MM_logo);

					if (black_rect_alpha == 0 && this->frame >= 3 * FRAMES_PER_SECOND) {
						animation_state++;
						black_rect_alpha = 255;
					}

					this->window_ptr->draw(black_rect);
					black_rect_alpha -= 2;
					if (black_rect_alpha <= 0) {
						black_rect_alpha = 0;
					}
					black_rect.setFillColor(
						sf::Color(0, 0, 0, black_rect_alpha)
					);

					break;

				case (1):	// slide logo, fade in game display
					this->window_ptr->clear();

					if (MM_logo.getPosition().y > 64) {
						// slide
						MM_logo.setPosition(
							SCREEN_WIDTH / 2,
							MM_logo.getPosition().y - 2
						);
					}

					if (
						MM_logo.getPosition().y <= 64 &&
						black_rect_alpha == 0 &&
						hour_of_day >= 5.5
					) {
						animation_state++;
					}

					//	sky disk
					this->sky_disk.drawFrame(hour_of_day);

					//	overcast and clouds
					this->overcast_clouds.drawFrame(
						wind_speed_ratio,
						cloud_cover_ratio,
						hour_of_day
					);

					// foreground + Plinko City
					this->foreground.drawFrame(true, hour_of_day);

					// wind sock
					this->wind_sock.drawFrame(wind_speed_ratio, hour_of_day);

					// draw objects
					for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
						//this->plant_ptr_vec[i]->drawMarbles();
						this->plant_ptr_vec[i]->drawSteam(wind_speed_ratio);
						this->plant_ptr_vec[i]->drawSmoke(wind_speed_ratio);
						this->plant_ptr_vec[i]->drawFrame(false, false);
					}

					this->window_ptr->draw(black_rect);
					black_rect_alpha -= 2;
					if (black_rect_alpha <= 0) {
						black_rect_alpha = 0;
					}
					black_rect.setFillColor(
						sf::Color(0, 0, 0, black_rect_alpha)
					);

					this->window_ptr->draw(MM_logo);

					break;

				case (2):	// blink instructions
					this->window_ptr->clear();

					//	sky disk
					this->sky_disk.drawFrame(hour_of_day);

					//	overcast and clouds
					this->overcast_clouds.drawFrame(
						wind_speed_ratio,
						cloud_cover_ratio,
						hour_of_day
					);

					// foreground + Plinko City
					this->foreground.drawFrame(true, hour_of_day);

					// wind sock
					this->wind_sock.drawFrame(wind_speed_ratio, hour_of_day);

					// draw objects
					for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
						//this->plant_ptr_vec[i]->drawMarbles();
						this->plant_ptr_vec[i]->drawSteam(wind_speed_ratio);
						this->plant_ptr_vec[i]->drawSmoke(wind_speed_ratio);
						this->plant_ptr_vec[i]->drawFrame(false, false);
					}

					if (
						this->frame % int(FRAMES_PER_SECOND) <
						FRAMES_PER_SECOND / 2
					) {
						this->window_ptr->draw(blink_instructions);
					}

					this->window_ptr->draw(MM_logo);

					break;

				case (3):	// fade out
					this->window_ptr->clear();

					if (black_rect_alpha == 255) {
						animation_state++;
					}

					//	sky disk
					this->sky_disk.drawFrame(hour_of_day);

					//	overcast and clouds
					this->overcast_clouds.drawFrame(
						wind_speed_ratio,
						cloud_cover_ratio,
						hour_of_day
					);

					// foreground + Plinko City
					this->foreground.drawFrame(true, hour_of_day);

					// wind sock
					this->wind_sock.drawFrame(wind_speed_ratio, hour_of_day);

					// draw objects
					for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
						//this->plant_ptr_vec[i]->drawMarbles();
						this->plant_ptr_vec[i]->drawSteam(wind_speed_ratio);
						this->plant_ptr_vec[i]->drawSmoke(wind_speed_ratio);
						this->plant_ptr_vec[i]->drawFrame(false, false);
					}

					if (
						this->frame % int(FRAMES_PER_SECOND) <
						FRAMES_PER_SECOND / 2
					) {
						this->window_ptr->draw(blink_instructions);
					}

					this->window_ptr->draw(MM_logo);

					this->window_ptr->draw(black_rect);
					black_rect_alpha += 2;
					if (black_rect_alpha >= 255) {
						black_rect_alpha = 255;
					}
					black_rect.setFillColor(
						sf::Color(0, 0, 0, black_rect_alpha)
					);

					break;

				default:
					animation_finished = true;
					break;
			}

			// handle events
			while (this->window_ptr->pollEvent(event)) {
				switch (event.type) {
					case (sf::Event::Closed):	// receive "close window" signal
						this->window_ptr->close();
						break;

					case (sf::Event::KeyPressed):	// key is pressed
						if (animation_state < 2) {
							animation_state = 2;
							black_rect_alpha = 0;
							MM_logo.setPosition(
								SCREEN_WIDTH / 2,
								64
							);
						}
						else {
							animation_state = 3;
						}
						break;

					default:
						// do nothing!
						break;
				}
			}

			// flip display, increment frame, increment hour_of_day
			this->window_ptr->display();
			this->frame++;
			hour_of_day += 0.5 / FRAMES_PER_SECOND;

			// update solar production
			if (hour_of_day > 5.5 && hour_of_day < 17.5) {
				if (hour_of_day <= 10) {
					solar_res_kWm2 = (2.0 / 9.0) * hour_of_day - (11.0 / 9.0);
				}
				else if (hour_of_day >= 14) {
					solar_res_kWm2 = (-2.0 / 7.0) * hour_of_day + 5.0;
				}
				else {
					solar_res_kWm2 = 1;
				}
				solar_res_kWm2 *= (1 - cloud_cover_ratio);
			}
			this->plant_ptr_vec[3]->getProduction(solar_res_kWm2);
		}
	}

	this->clearPlants();
	this->initPlants();
	return;
}	// end Game::playTitle()


void Game::handleEvents(void) {
	/*
	 *	Method to handle events (usually user inputs)
	 */

	sf::Event event;

	// while there is an event left to handle ...
	while (this->window_ptr->pollEvent(event))
	{
		switch (event.type) {
			case (sf::Event::Closed):	// receive "close window" signal
				this->window_ptr->close();
				break;

			case (sf::Event::KeyPressed):	// key is pressed
				handleKeys(event.key.code, true);
				this->text_box.handleEvents(event.key.code);
				break;

			case (sf::Event::KeyReleased):	// key is released
				handleKeys(event.key.code, false);
				break;

			default:
				// do nothing!
				break;
		}
	}

	// if music finished, move to next track and play
	sf::SoundSource::Status music_status = this->music_player.getStatus();
	if (music_status == sf::SoundSource::Status::Stopped) {
		this->music_player.nextTrack();
		this->music_player.play();
	}

	return;
}	// end Game::handleEvents()


void Game::handleKeys(sf::Keyboard::Key key, bool key_press) {
	/*
	 *	Method to handle user key presses
	 */

	if (key_press) {	// handle key presses
		this->key_vec[key] = true;

		// if at game over screen then return to main menu for any key press
		// add saving high scores with plant info and name------------------------------------------
		if (this->phase_manager.getPhase() == 5) {
			this->reset();
		}

		// single keys
		switch (key) {
			// close window
			case (sf::Keyboard::Escape):
				// -------------------------------------------------------------------------------------
				// feels weird that you can play more of the game while this prompt is up, consider revising
				// cancel quitting the round (felt intuitive)
				/*
				 *	Copied over to handler in Game::transition() as well =P
				 */
				if (this->phase_manager.getQuittingRound()) {
					this->phase_manager.setQuittingRound(false);
					this->assets.getSound("P key")->play();
				}
				else{
					// toggle quitting the game
					if (this->phase_manager.getQuittingGame()) {
						this->phase_manager.setQuittingGame(false);
						this->assets.getSound("P key")->play();
					}
					else{
						this->phase_manager.setQuittingGame(true);
						// also disable quitting round overlay
						this->phase_manager.setQuittingRound(false);
						this->assets.getSound("P key")->play();
					}
				}
				break;

			// toggle frame rate overlay
			case (sf::Keyboard::F1):
				if (this->draw_frame_rate) {
					this->draw_frame_rate = false;
				}
				else {
					this->draw_frame_rate = true;
				}
				break;

			// toggle energy overlay
			case (sf::Keyboard::E):
				if (this->draw_energy_overlay) {
					this->draw_energy_overlay = false;
				}
				else {
					this->draw_energy_overlay = true;
					if (this->draw_forecast_overlay) {
						this->draw_forecast_overlay = false;
					}
				}

				this->assets.getSound("A D key")->play();
				break;

			// toggle forecast overlay
			case (sf::Keyboard::F):
				if (this->draw_forecast_overlay) {
					this->draw_forecast_overlay = false;
				}
				else {
					this->draw_forecast_overlay = true;
					if (this->draw_energy_overlay) {
						this->draw_energy_overlay = false;
					}
				}

				this->assets.getSound("A D key")->play();
				break;

			// toggle music (play/pause)
			case (sf::Keyboard::M):
				if (this->powered_flag) {
					if (this->music_paused) {
						this->music_player.play();
						this->music_paused = false;
					}
					else {
						this->music_player.pause();
						this->music_paused = true;
					}
				}
				break;

			// move to next music track
			case (sf::Keyboard::Period):
				if (this->powered_flag && !this->music_paused) {
					this->music_player.nextTrack();
					this->music_player.play();
				}
				break;

			// move to previous music track
			case (sf::Keyboard::Comma):
				if (this->powered_flag && !this->music_paused) {
					this->music_player.prevTrack();
					this->music_player.play();
				}
				break;

			// display plant information
			case (sf::Keyboard::I):
				{
					int texture_key = this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex();
					std::string feed_str = "";
					switch (texture_key) {
						case (0):	// Coal
							feed_str = TEXT_COAL;
							break;

						case (1):	// Combined
							feed_str = TEXT_COMBINED;
							break;

						case (2):	// Fission
							feed_str = TEXT_FISSION;
							break;

						case (3):	// Geothermal
							feed_str = TEXT_GEOTHERMAL;
							break;

						case (4):	// Hydro
							feed_str = TEXT_HYDRO;
							break;

						case (5):	// Peaker
							feed_str = TEXT_PEAKER;
							break;

						case (6):	// Solar
							feed_str = TEXT_SOLAR;
							break;

						case (7):	// Storage
							feed_str = TEXT_STORAGE;
							break;

						case (8):	// Tidal
							feed_str = TEXT_TIDAL;
							break;

						case (9):	// Wave
							feed_str = TEXT_WAVE;
							break;

						case (10):	// Wind
							feed_str = TEXT_WIND;
							break;

						default:
							// do nothing!
							break;
					}

					if (!feed_str.empty()) {
						this->text_box.makeBox(
							std::string(feed_str),
							"bold",
							0.02 * SCREEN_HEIGHT,
							SCREEN_WIDTH / 8,
							SCREEN_HEIGHT / 8,
							SCREEN_WIDTH / 2,
							SCREEN_HEIGHT / 3
						);
					}
				}
				break;

			// display tutorial information
			case (sf::Keyboard::T):
				if (this->phase_manager.getPhase() > 0) {
					this->text_box.makeBox(
						std::string(TEXT_TUTORIAL),
						"bold",
						0.02 * SCREEN_HEIGHT,
						SCREEN_WIDTH / 8,
						SCREEN_HEIGHT / 8,
						SCREEN_WIDTH / 2,
						SCREEN_HEIGHT / 3
					);
				}
				break;

			// display key bindings
			case (sf::Keyboard::B):
				if (this->phase_manager.getPhase() > 0) {
					this->text_box.makeBox(
						std::string(TEXT_KEYS),
						"bold",
						0.02 * SCREEN_HEIGHT,
						SCREEN_WIDTH / 8,
						SCREEN_HEIGHT / 8,
						SCREEN_WIDTH / 2,
						SCREEN_HEIGHT / 3
					);
				}
				break;

			// commit and transition
			case (sf::Keyboard::Space):
				//different functionality depending on phases
				switch(this->phase_manager.getPhase()) {

					case (0): // at menu
						// display tutorial
						this->text_box.makeBox(
							std::string(TEXT_TUTORIAL),
							"bold",
							0.02 * SCREEN_HEIGHT,
							SCREEN_WIDTH / 8,
							SCREEN_HEIGHT / 8,
							SCREEN_WIDTH / 2,
							SCREEN_HEIGHT / 3
						);

						// go to selecting generators
						this->phase_manager.setPhase(2);

						//reset pictorial_tutorial
						this->pictorial_tutorial.reset();

						this->assets.getSound("P key")->play();
						break;

					case (1): // during game
						{
							// clear spacebar tutorial
							this->pictorial_tutorial.show_spacebar_instructions = false;

							// reset marbles (for emissions)
							this->coal_marbles = 0;
							this->combined_marbles = 0;
							this->peaker_marbles = 0;

							// determine total dispatch, update score, update smog
							int total_dispatch_GWh = 0;
							double smog_ratio = this->smog_ratio;
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								int texture_key = this->plant_ptr_vec[i]->getTextureIndex();
								if (texture_key < 0) {
									continue;
								}

								total_dispatch_GWh +=
									this->plant_ptr_vec[i]->getMusteredMarbles();

								if (
									this->plant_ptr_vec[i]->getMusteredMarbles() > 0
								) {
									this->plant_ptr_vec[i]->setPulseFlag(true);
								}

								switch (texture_key) {
									case (0):	// Coal
										this->coal_marbles += this->plant_ptr_vec[i]->getMusteredMarbles();
										this->score -= this->plant_ptr_vec[i]->getMusteredMarbles();
										smog_ratio += 0.001 * this->plant_ptr_vec[i]->getMusteredMarbles();
										break;
									case (1):	// Combined
										this->combined_marbles += this->plant_ptr_vec[i]->getMusteredMarbles();
										this->score -= 0.5 * this->plant_ptr_vec[i]->getMusteredMarbles();
										smog_ratio += 0.0005 * this->plant_ptr_vec[i]->getMusteredMarbles();
										break;
									case (5):	// Peaker
										this->peaker_marbles += this->plant_ptr_vec[i]->getMusteredMarbles();
										this->score -= 0.75 * this->plant_ptr_vec[i]->getMusteredMarbles();
										smog_ratio += 0.00075 * this->plant_ptr_vec[i]->getMusteredMarbles();
										break;
									default:
										// do nothing!
										break;
								}
							}
							if (total_dispatch_GWh >= this->current_energy_demand_GWh) {
								this->score += this->current_energy_demand_GWh;
							}
							else {
								this->score += total_dispatch_GWh -
									this->current_energy_demand_GWh;
							}
							if (total_dispatch_GWh > 0) {
								this->assets.getSound("dispatch")->play();
							}
							if (smog_ratio > 1) {
								smog_ratio = 1;
							}
							this->next_smog_ratio = smog_ratio;

							// commit marbles
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								int texture_key = this->plant_ptr_vec[i]->getTextureIndex();
								if (texture_key < 0) {
									continue;
								}
								this->plant_ptr_vec[i]->commitMarbles();
							}

							// lock in ramping rate constraints (after first round)
							if (this->hour_of_day == 0) {
								for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
									this->plant_ptr_vec[i]->setHasRun(true);
								}
							}

							// update city power state
							if (
								this->powered_flag &&
								total_dispatch_GWh < this->current_energy_demand_GWh
							) {
								this->powered_flag = false;

								this->music_player.pause();
								this->assets.getSound("powering down")->play();
							}
							else if (
								!this->powered_flag &&
								total_dispatch_GWh >= this->current_energy_demand_GWh
							) {
								this->powered_flag = true;

								this->music_player.play();
								this->assets.getSound("powering up")->play();
							}

							// determine storage charging (from any available excess)
							int excess_dispatch_GWh = 0;
							if (total_dispatch_GWh > this->current_energy_demand_GWh) {
								excess_dispatch_GWh = total_dispatch_GWh -
									this->current_energy_demand_GWh;
							}
							if (excess_dispatch_GWh > 0) {
								for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
									if (excess_dispatch_GWh <= 0) {
										break;
									}
									int texture_key = this->plant_ptr_vec[i]->getTextureIndex();
									if (texture_key == 7) {
										double excess_before_GWh = excess_dispatch_GWh;
										excess_dispatch_GWh =
											this->plant_ptr_vec[i]->commitCharge(excess_dispatch_GWh);
										if (excess_before_GWh - excess_dispatch_GWh > 0) {
											this->plant_ptr_vec[i]->setPulseFlag(true);
										}
									}
								}
							}

							// penalize any remaining excess
							// this is a new rule in this implementation ----------------------------------------
							if (excess_dispatch_GWh > 0) {
								this->score -= excess_dispatch_GWh;
							}
							this->excess_dispatch_GWh = excess_dispatch_GWh;

							// prepare points string
							double total_points = 0;
							this->points_str = "";
							if (total_dispatch_GWh >= this->current_energy_demand_GWh) {
								this->points_str += "Satisfied demand of ";
								this->points_str += std::to_string(this->current_energy_demand_GWh);
								this->points_str += " GWh!\n";
								for (int i = 0; i < 25; i++) {
									this->points_str += "\t";
								}
								this->points_str += "Points: +";
								this->points_str += std::to_string(this->current_energy_demand_GWh);
								total_points += this->current_energy_demand_GWh;
								this->points_str += "\n";
							}
							else {
								this->points_str += "Unmet demand of ";
								this->points_str += std::to_string(
									this->current_energy_demand_GWh - total_dispatch_GWh
								);
								this->points_str += " GWh!\n";
								for (int i = 0; i < 25; i++) {
									this->points_str += "\t";
								}
								this->points_str += "Points: ";
								this->points_str += std::to_string(
									total_dispatch_GWh - this->current_energy_demand_GWh
								);
								total_points += total_dispatch_GWh -
									this->current_energy_demand_GWh;
								this->points_str += "\n";
							}
							if (this->coal_marbles > 0) {
								this->points_str += "Coal dispatch of ";
								this->points_str += std::to_string(this->coal_marbles);
								this->points_str += " GWh.\n";
								for (int i = 0; i < 25; i++) {
									this->points_str += "\t";
								}
								this->points_str += "Points: -";
								this->points_str += std::to_string(this->coal_marbles);
								total_points -= this->coal_marbles;
								this->points_str += "\n";
							}
							if (this->combined_marbles > 0) {
								this->points_str += "Combined Cycle dispatch of ";
								this->points_str += std::to_string(this->combined_marbles);
								total_points -= 0.5 * this->combined_marbles;
								this->points_str += " GWh.\n";
								for (int i = 0; i < 25; i++) {
									this->points_str += "\t";
								}
								this->points_str += "Points: -";
								if (0.5 * this->combined_marbles == int(0.5 * this->combined_marbles)) {
									this->points_str += std::to_string(int(0.5 * this->combined_marbles));
								}
								else {
									this->points_str += std::to_string(0.5 * this->combined_marbles);
									while (this->points_str.back() == '0') {
										this->points_str.pop_back();
										if (this->points_str.back() == '.') {
											this->points_str.pop_back();
											break;
										}
									}
								}
								this->points_str += "\n";
							}
							if (this->peaker_marbles > 0) {
								this->points_str += "Peaker dispatch of ";
								this->points_str += std::to_string(this->peaker_marbles);
								total_points -= 0.75 * this->peaker_marbles;
								this->points_str += " GWh.\n";
								for (int i = 0; i < 25; i++) {
									this->points_str += "\t";
								}
								this->points_str += "Points: -";
								if (0.75 * this->peaker_marbles == int(0.75 * this->peaker_marbles)) {
									this->points_str += std::to_string(int(0.75 * this->peaker_marbles));
								}
								else {
									this->points_str += std::to_string(0.75 * this->peaker_marbles);
									while (this->points_str.back() == '0') {
										this->points_str.pop_back();
										if (this->points_str.back() == '.') {
											this->points_str.pop_back();
											break;
										}
									}
								}
								this->points_str += "\n";
							}
							if (this->excess_dispatch_GWh > 0) {
								this->points_str += std::to_string(this->excess_dispatch_GWh);
								total_points -= this->excess_dispatch_GWh;
								this->points_str += " GWh of excess production could not be stored!\n";
								for (int i = 0; i < 25; i++) {
									this->points_str += "\t";
								}
								this->points_str += "Points: -";
								if (this->excess_dispatch_GWh == int(this->excess_dispatch_GWh)) {
									this->points_str += std::to_string(int(this->excess_dispatch_GWh));
								}
								else {
									this->points_str += std::to_string(this->excess_dispatch_GWh);
									while (this->points_str.back() == '0') {
										this->points_str.pop_back();
										if (this->points_str.back() == '.') {
											this->points_str.pop_back();
											break;
										}
									}
								}
								this->points_str += "\n";
							}
							this->points_str += "\nTOTAL THIS HOUR\n";
							for (int i = 0; i < 25; i++) {
								this->points_str += "\t";
							}
							this->points_str += "Points: ";
							if (total_points > 0) {
								this->points_str += "+";
							}
							if (total_points == int(total_points)) {
								this->points_str += std::to_string(int(total_points));
							}
							else {
								this->points_str += std::to_string(total_points);
								while (this->points_str.back() == '0') {
									this->points_str.pop_back();
									if (this->points_str.back() == '.') {
										this->points_str.pop_back();
										break;
									}
								}
							}
							this->points_str += "\n";

							// determine next weather states
							this->next_wind_speed_ratio = this->generateWindRatio();
							this->next_cloud_cover_ratio = this->generateCloudRatio();
							this->next_wave_res_s = this->generateWaveResource();

							// set next hour
							this->next_hour_of_day = this->hour_of_day + 1;

							// loop transition
							// blocks until finished
							while (this->transition()) {}

							// reset points_str
							this->points_str = "";

							// clear marbles, lines, pulsing plants
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								this->plant_ptr_vec[i]->clearMarbles();
							}

							// compute renewable production
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								if (	// Solar
									this->plant_ptr_vec[i]->getTextureIndex() == 6
								) {
									this->plant_ptr_vec[i]->getProduction(
										this->generateSolarResource()
									);
								}
								else if (	// Tidal
									this->plant_ptr_vec[i]->getTextureIndex() == 8
								) {
									double tidal_res_ms =
										this->tidal_res_ms_vec[
											(int(this->hour_of_day) +
											this->tidal_idx_offset) % 23
										];

									tidal_res_ms *= 1 + (0.1 * ((double)rand() / RAND_MAX) - 0.05);
									if (tidal_res_ms < 0) {
										tidal_res_ms = 0;
									}
									else if (tidal_res_ms > 1) {
										tidal_res_ms = 1;
									}

									this->plant_ptr_vec[i]->getProduction(tidal_res_ms);
								}
								else if (	// Wave
									this->plant_ptr_vec[i]->getTextureIndex() == 9
								) {
									this->plant_ptr_vec[i]->getProduction(
										this->wave_res_s
									);
								}
								else if (	// Wind
									this->plant_ptr_vec[i]->getTextureIndex() == 10
								) {
									this->plant_ptr_vec[i]->getProduction(
										this->wind_speed_ratio
									);
								}
							}

							// get next demand
							if (this->hour_of_day < 23) {
								this->current_energy_demand_GWh =
									this->energy_demand_GWh_vec[int(this->hour_of_day)] +
									int(4 * ((double)rand() / RAND_MAX)) - 2;
							}
							else {
								this->current_energy_demand_GWh =
									this->energy_demand_GWh_vec[0] +
									int(4 * ((double)rand() / RAND_MAX)) - 2;
							}
							this->actual_energy_demand_GWh_vec.push_back(
								this->current_energy_demand_GWh
							);

							// update forecast
							this->getForecast();

							this->assets.getSound("transition complete")->play();
						}
						break;

					case (2): // when selecting plants
						{
							// go to selecting capacities
							bool plants_selected = false;
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								if (this->plant_ptr_vec[i]->getTextureIndex() != -1) {
									plants_selected = true;
									break;
								}
							}

							if (plants_selected) {
								//reset pictorial_tutorial - but not ad, same function
								this->pictorial_tutorial.show_wasd_instructions_ws = true;
								this->pictorial_tutorial.show_spacebar_instructions = false;
								this->phase_manager.setPhase(3);
								this->phase_manager.setIndex(0);
								if (this->plant_ptr_vec[0]->getTextureIndex() == -1) {
									this->phase_manager.nextValidIndex(&this->plant_ptr_vec);
								}

								// create correct plant objects
								for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
									int texture_key = this->plant_ptr_vec[i]->getTextureIndex();
									switch (texture_key) {
										case (0):
											{
												Plant* plant = new Coal(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (1):
											{
												Plant* plant = new Combined(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (2):
											{
												Plant* plant = new Fission(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (3):
											{
												Plant* plant = new Geothermal(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (4):
											{
												Plant* plant = new Hydro(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												plant->setEnergyCapacity(this->phase_manager.hydroStorageTable(GW_PER_TOKEN));
												plant->setCharge(this->phase_manager.hydroStorageTable(GW_PER_TOKEN));//this should equal energy capacity
												this->pushPlant(i, plant);
											}
											break;
										case (5):
											{
												Plant* plant = new Peaker(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (6):
											{
												Plant* plant = new Solar(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (7):
											{
												Plant* plant = new Storage(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												plant->setEnergyCapacity(STORAGE_GW_PER_INCREMENT);
												plant->setCharge(0);//this should start at 0
												this->pushPlant(i, plant);
											}
											break;
										case (8):
											{
												Plant* plant = new Tidal(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (9):
											{
												Plant* plant = new Wave(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										case (10):
											{
												Plant* plant = new Wind(0, 0, 1, this->window_ptr, &(this->assets));
												plant->setRunning(true);
												this->pushPlant(i, plant);
											}
											break;
										default:
											// plant was set to null
											this->plant_ptr_vec[i]->setPlantTexture(-2);
											break;
									} // end switch(texture_key)

									// if regular plant
									//if (texture_key != -1) { //
									if (texture_key >= 0) {
										this->phase_manager.decCapacityTokens();

										// if storage
										if (texture_key == 7) {
											// reduce capacity tokens extra times depending on storage tokens per GW
											for (size_t i = 0; i < STORAGE_TOKENS_PER_GW-1; i++) {
												this->phase_manager.decCapacityTokens();
											}
											this->plant_ptr_vec[i]->setPowerCapacity(STORAGE_GW_PER_INCREMENT);
										}
										// if geothermal, have to reduce by amount of tokens assigned to it
										else if (texture_key == 3) {
											for (size_t i = 0; i < CAPACITY_PER_GEOTHERMAL_ROLL/GW_PER_TOKEN-1; i++) {
												this->phase_manager.decCapacityTokens();
											}
											this->plant_ptr_vec[i]->setPowerCapacity(CAPACITY_PER_GEOTHERMAL_ROLL);
										}
										// if fission have to reduce tokens based on fission tokesn per GW
										else if (texture_key == 2){
											for (size_t i = 0; i < FISSION_TOKENS_PER_GW-1; i++) {
												this->phase_manager.decCapacityTokens();
											}
											this->plant_ptr_vec[i]->setPowerCapacity(GW_PER_TOKEN);
										}
										// if peaker have to reduce tokens based on peaker tokesn per GW
										else if (texture_key == 5){
											for (size_t i = 0; i < PEAKER_TOKENS_PER_GW-1; i++) {
												this->phase_manager.decCapacityTokens();
											}
											this->plant_ptr_vec[i]->setPowerCapacity(GW_PER_TOKEN);
										}
										// every other plant
										else {
											this->plant_ptr_vec[i]->setPowerCapacity(GW_PER_TOKEN);
										}
									}// end if regular plant

									//set capacity in phase_manager depending on first plant
									this->phase_manager.setCapacity(
										this->plant_ptr_vec[this->phase_manager.getIndex()]
										->getCapacityGW());

									std::cout << "PLANT " << i << " CAP: " <<
										this->plant_ptr_vec[i]->getCapacityGW() <<
										" GW" << std::endl;
								}

								// reset text box
								this->text_box.makeBox(
									"",
									"bold",
									0.02 * SCREEN_HEIGHT,
									SCREEN_WIDTH / 8,
									SCREEN_HEIGHT / 8,
									SCREEN_WIDTH / 2,
									SCREEN_HEIGHT / 3
								);
							}

							//this->plantInfo(this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex());

						}
						this->assets.getSound("P key")->play();
						break;

					case (3): // when selecting capacities
						// start the game

						// need to have some kind of check for if enough capacity applied
						if (this->phase_manager.getCapacityTokens() == 0) {
							//reset pictorial_tutorial - but not ad, same function
							this->pictorial_tutorial.show_wasd_instructions_ws = true;
							this->pictorial_tutorial.show_spacebar_instructions = false;

							// init all plants (other than hydro) as off
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								if (	// Hydro
									this->plant_ptr_vec[i]->getTextureIndex() != 4
								) {
									this->plant_ptr_vec[i]->setRunning(false);
								}

							}

							// find out if need to roll for geothermal and set phase accordingly
							{
								bool geothermal_in_plant_ptr_vec = false;
								for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
									if(this->plant_ptr_vec[i]->getTextureIndex() == 3){
										this->phase_manager.setGeothermalPresent(i,true);
										this->dice_roll.setRollsLeft(i,
											this->plant_ptr_vec[i]->getCapacityGW()/CAPACITY_PER_GEOTHERMAL_ROLL);
											this->plant_ptr_vec[i]->setPowerCapacity(0);
										geothermal_in_plant_ptr_vec = true;
									}
								}// end for loop

								if (geothermal_in_plant_ptr_vec){
									this->phase_manager.setPhase(4);
								} else {
									this->phase_manager.setPhase(1);
								}

							}

							this->phase_manager.setIndex(0);

							if (this->plant_ptr_vec[0]->getTextureIndex() == -1) {
								this->phase_manager.nextValidIndex(&this->plant_ptr_vec);
							}

							// compute initial renewable production
							this->wind_speed_ratio = (double)rand() / RAND_MAX;
							this->cloud_cover_ratio = (double)rand() / RAND_MAX;
							this->wave_res_s =
								(15 - 5.75) * ((double)rand() / RAND_MAX) - 5.75;
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								if (	// Solar
									this->plant_ptr_vec[i]->getTextureIndex() == 6
								) {
									this->plant_ptr_vec[i]->getProduction(
										this->generateSolarResource()
									);
								}
								else if (	// Tidal
									this->plant_ptr_vec[i]->getTextureIndex() == 8
								) {
									double tidal_res_ms =
										this->tidal_res_ms_vec[
											(int(this->hour_of_day) +
											this->tidal_idx_offset) % 23
										];

									tidal_res_ms *= 1 + (0.1 * ((double)rand() / RAND_MAX) - 0.05);
									if (tidal_res_ms < 0) {
										tidal_res_ms = 0;
									}
									else if (tidal_res_ms > 1) {
										tidal_res_ms = 1;
									}

									this->plant_ptr_vec[i]->getProduction(tidal_res_ms);

								}
								else if (	// Wave
									this->plant_ptr_vec[i]->getTextureIndex() == 9
								) {
									this->plant_ptr_vec[i]->getProduction(
										this->wave_res_s
									);
								}
								else if (	// Wind
									this->plant_ptr_vec[i]->getTextureIndex() == 10
								) {
									this->plant_ptr_vec[i]->getProduction(
										this->wind_speed_ratio
									);
								}
							}

							// set initial demand
							this->current_energy_demand_GWh =
								this->energy_demand_GWh_vec[int(this->hour_of_day)] +
								int(4 * ((double)rand() / RAND_MAX)) - 2;
							this->actual_energy_demand_GWh_vec.push_back(
								this->current_energy_demand_GWh
							);

							// I think this fix is unnecessary
							// fix broken storage energy capacity init  >=(
							// ---------------------------------------------------------------------------
							/*
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								if (this->plant_ptr_vec[i]->getTextureIndex() == 4) {
									this->plant_ptr_vec[i]
										->setEnergyCapacity(
											this->phase_manager.hydroStorageTable(
												this->plant_ptr_vec[i]->getCapacityGW()
											)
										);
								}
								else if (this->plant_ptr_vec[i]->getTextureIndex() == 7) {
									this->plant_ptr_vec[i]->setEnergyCapacity(
										this->plant_ptr_vec[i]->getCapacityGW()
									);
								}
							}
							*/

							// make initial forecast
							this->getForecast();

							// set draw_price
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								this->plant_ptr_vec[i]->setDrawPrice(false);
							}
						}
						this->assets.getSound("P key")->play();
						break;

					case (4):// run rolls for geothermal if in play
						{
							// want to show a dice rolling on the screen, proably need to roll
							// dice and wait until roll done to do next and so on, need a
							// variable that says to start roll and one when roll is done.
							// Maybe a counter stating how many rolls left or a vector linking
							// to each geothermal plant?
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								if (this->phase_manager.getGeothermalPresent(i)) {
									// if rolling dice stop them and save result
									if (this->dice_roll.getRollingDice()) {
										this->dice_roll.setRollingDice(false);

										// store roll in vector and set up plant if vector is full
										if(this->dice_roll.setGeothermalRolls()){
											this->plant_ptr_vec[i]->setPowerCapacity(
												this->plant_ptr_vec[i]->getCapacityGW()
												+ this->dice_roll.getGeothermalCapacity());

												//this->dice_roll.resetGeothermalRolls();

												this->dice_roll.setRollsLeft(i,this->dice_roll.getRollsLeft(i) - 1);
												std::cout << "rolls left: " << this->dice_roll.getRollsLeft(i) << std::endl;
												/*
												if (this->dice_roll.getRollsLeft(i) <= 0) {
													// only do this below if have rolled for each token
													this->phase_manager.setGeothermalPresent(i,false);
													std::cout << "Geothermal in slot: " << i << " has capacity: "
														<< this->plant_ptr_vec[i]->getCapacityGW() << std::endl;
												}
												*/
										}
										else{
											this->plant_ptr_vec[i]->setPowerCapacity(
												this->plant_ptr_vec[i]->getCapacityGW()
												+ this->dice_roll.getGeothermalCapacity());
										}

										if (this->dice_roll.getGeothermalCapacity() > 0) {
											//std::cout << "SUCCESS" << std::endl;
											this->plant_ptr_vec[i]->drillSuccess(true);
										}
										else {
											//std::cout << "FAILURE" << std::endl;
											this->plant_ptr_vec[i]->drillSuccess(false);
										}

										this->rolls_rem_corr = (this->rolls_rem_corr + 1) % 3;
									} // end if rolling dice
									// start rolling dice again
									else{

										this->dice_roll.setRollingDice(true);

										if (this->dice_roll.getRollsLeft(i) <= 0) {
											// only do this below if have rolled for each token
											this->phase_manager.setGeothermalPresent(i,false);
											std::cout << "Geothermal in slot: " << i << " has capacity: "
												<< this->plant_ptr_vec[i]->getCapacityGW() << std::endl;
										}

									}
									// only run for first geothermal left to roll for - ie if there are two gwothermal plants roll for one at a time
									break;
								}
							} // end for loop

							bool geothermal_left_to_roll_for = false;
							for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
								if (this->phase_manager.getGeothermalPresent(i)) {
									geothermal_left_to_roll_for = true;
								}
							} // end for loop
							if (!geothermal_left_to_roll_for) {
								this->phase_manager.setPhase(1);
							}
						}
						break;
				}

				break;

			// toggle menu/quitting game and returning to menu
			case (sf::Keyboard::P):
				if (this->phase_manager.getPhase() == 1) {
					// if not already being prompted to quit the game
					if (!this->phase_manager.getQuittingGame()) {
						this->phase_manager.setQuittingRound(true);
						this->assets.getSound("P key")->play();
					}
				}
				break;

			// say yes to some onscreen prompt
			case (sf::Keyboard::Y):
				if (this->phase_manager.getQuittingRound()) {
					// quit round and restart
					this->reset();
				}

				if (this->phase_manager.getQuittingGame()) {
					// quit game and close window
					this->window_ptr->close();
				}
				break;

			// say no to some onscreen prompt
			case (sf::Keyboard::N):
				if (this->phase_manager.getQuittingRound()) {
					// cancel quitting round and return to game
					// (do not change phase)
					this->phase_manager.setQuittingRound(false);
				}

				if (this->phase_manager.getQuittingGame()) {
					// cancel quitting game and return to game
					// (do not change phase)
					this->phase_manager.setQuittingGame(false);
				}
				break;

			// move left
			case (sf::Keyboard::A):
				this->pictorial_tutorial.show_wasd_instructions_ad = false;
				switch(this->phase_manager.getPhase()) {

					case (1):
						// playing the game
						this->phase_manager.prevValidIndex(&this->plant_ptr_vec);
						// set marbles to previous marbles value

						this->assets.getSound("A D key")->play();
						break;

					case (2):
						// selecting generators
						this->phase_manager.decIndex(this->plant_ptr_vec);
						// set plant_num to previous plant
						this->phase_manager.setPlantNum(
							this->plant_ptr_vec[this->phase_manager.getIndex()]
							->getTextureIndex());

						//this->plantInfo(this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex());

						this->assets.getSound("A D key")->play();
						break;

					case (3):
						// selecting capacities
						this->phase_manager.prevValidIndex(&this->plant_ptr_vec);
						// set capacity to previous capacity
						this->phase_manager.setCapacity(
							this->plant_ptr_vec[this->phase_manager.getIndex()]
							->getCapacityGW());

						//this->plantInfo(this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex());

						this->assets.getSound("A D key")->play();
						break;

					default:
						// do nothing!
						break;
				}
				break;

			// move right
			case (sf::Keyboard::D):
				this->pictorial_tutorial.show_wasd_instructions_ad = false;
				switch(this->phase_manager.getPhase()) {

					case (1):
						// playing the game
						this->phase_manager.nextValidIndex(&this->plant_ptr_vec);
						// set marbles to next marbles value

						this->assets.getSound("A D key")->play();
						break;

					case (2):
						// selecting generators
						this->phase_manager.incIndex(this->plant_ptr_vec);
						// set plant_num to next plant
						this->phase_manager.setPlantNum(
							this->plant_ptr_vec[this->phase_manager.getIndex()]
							->getTextureIndex());

						//this->plantInfo(this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex());

						this->assets.getSound("A D key")->play();
						break;

					case (3):
						// selecting capacities
						this->phase_manager.nextValidIndex(&this->plant_ptr_vec);
						// set capacity to next capacity
						this->phase_manager.setCapacity(
							this->plant_ptr_vec[this->phase_manager.getIndex()]
							->getCapacityGW());

						//this->plantInfo(this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex());

						this->assets.getSound("A D key")->play();
						break;

					default:
						// do nothing!
						break;
				}
				break;

			// move up
			case (sf::Keyboard::W):
				// manage pictorial tutorial
				this->pictorial_tutorial.show_wasd_instructions_ws = false;
				switch(this->phase_manager.getPhase()) {

					case (1):
						{
							// update pictorial_tutorial to show spacebar
							this->pictorial_tutorial.w_presses_during_game ++;
							if (this->pictorial_tutorial.w_presses_during_game == 1) {
								this->pictorial_tutorial.show_spacebar_instructions = true;
							}
							// store last
							int last_marbles = this->plant_ptr_vec[this->phase_manager.getIndex()]->
								getMusteredMarbles();

							// call increaseMarbles()
							this->plant_ptr_vec[this->phase_manager.getIndex()]->
								incMarbles();

							// if change, play sound
							if (
								last_marbles !=
								this->plant_ptr_vec[this->phase_manager.getIndex()]->
									getMusteredMarbles()
							) {
								this->assets.getSound("W key")->play();
							}
						}
						break;

					case (2):
						// select next generator
						this->phase_manager.incPlantNum();
						this->plant_ptr_vec[this->phase_manager.getIndex()]
						->setPlantTexture(this->phase_manager.getPlantNum());

						// update price
						{
							int texture_idx = this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex();
							switch (texture_idx) {
								case (2):	// Fission
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(FISSION_TOKENS_PER_GW);
									break;

								case (5):	// Peaker
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(PEAKER_TOKENS_PER_GW);
									break;

								case (7):	// Storage
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(STORAGE_TOKENS_PER_GW);
									break;

								default:	// all other plants
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(1);
									break;
							}
						}

						if (
							this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex() >= 0
						) {
							this->plantInfo(this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex());
						}
						else {
							this->text_box.makeBox(
								"",
								"bold",
								0.02 * SCREEN_HEIGHT,
								SCREEN_WIDTH / 8,
								SCREEN_HEIGHT / 8,
								SCREEN_WIDTH / 2,
								SCREEN_HEIGHT / 3
							);
						}

						this->assets.getSound("A D key")->play();
						break;

					case (3):
						// setting capacities
						{
							int texture_key = this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex();
							int last_tokens = 0;
							int next_tokens = 0;
							switch (texture_key) {
								case (-1):
									// null plant - do nothing
									std::cout << "null plant" << std::endl;
									break;

								case (2):
									// fission - cannot exceed 9 GW capacity
									// give a bit of leeway in case of floating point error in the future
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									if (this->phase_manager.getCapacity() < MAX_FISSION_CAPACITY - 0.1) {
										if (this->phase_manager.getCapacityTokens() >= FISSION_TOKENS_PER_GW) {
											// decrease tokens by appropriate amount minus 1 (the last one happens during incCapacity() call)
											for (size_t i = 0; i < FISSION_TOKENS_PER_GW-1; i++) {
												this->phase_manager.decCapacityTokens();
											}
											this->phase_manager.incCapacity(GW_PER_TOKEN);
											this->plant_ptr_vec[this->phase_manager.getIndex()]
												->setPowerCapacity(this->phase_manager.getCapacity());
										}
									}

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									break;

								// special case for geothermal, need to make big investment to search for power
								case (3):
									// storage set capacity_GWh and charge_GWh based on capacity
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									// if we have enough tokens to add capacity
									if (this->phase_manager.getCapacityTokens() >= CAPACITY_PER_GEOTHERMAL_ROLL/GW_PER_TOKEN) {
										// decrease tokens by appropriate amount minus 1 (the last one happens during incCapacity() call)
										for (size_t i = 0; i < CAPACITY_PER_GEOTHERMAL_ROLL/GW_PER_TOKEN-1; i++) {
											this->phase_manager.decCapacityTokens();
										}

										this->phase_manager.incCapacity(CAPACITY_PER_GEOTHERMAL_ROLL);
										this->plant_ptr_vec[this->phase_manager.getIndex()]
											->setPowerCapacity(this->phase_manager.getCapacity());
									}

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									break;

								case (4):
									// hydro - set capacity_GWh and charge_GWh based on table
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									this->phase_manager.incCapacity(GW_PER_TOKEN);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());

									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setEnergyCapacity(this->phase_manager.hydroStorageTable(this->phase_manager.getCapacity()));
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setCharge(this->phase_manager.hydroStorageTable(this->phase_manager.getCapacity()));//this should equal energy capacity

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									break;

								case (5):
									// peaker - cannot exceed 9 GW capacity
									// give a bit of leeway in case of floating point error in the future
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									if (this->phase_manager.getCapacity() < MAX_PEAKER_CAPACITY - 0.1) {
										if (this->phase_manager.getCapacityTokens() >= PEAKER_TOKENS_PER_GW) {
											// decrease tokens by appropriate amount minus 1 (the last one happens during incCapacity() call)
											for (size_t i = 0; i < PEAKER_TOKENS_PER_GW-1; i++) {
												this->phase_manager.decCapacityTokens();
											}
											this->phase_manager.incCapacity(GW_PER_TOKEN);
											this->plant_ptr_vec[this->phase_manager.getIndex()]
												->setPowerCapacity(this->phase_manager.getCapacity());
										}
									}

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									break;

									// special case for this, should use more tokens, also need to do same for geothermal
								case (7):
									// storage set capacity_GWh and charge_GWh based on capacity
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() * STORAGE_TOKENS_PER_GW;

										// if we have enough tokens to add capacity
										if (this->phase_manager.getCapacityTokens() >= STORAGE_TOKENS_PER_GW) {
											// decrease tokens by appropriate amount minus 1 (the last one happens during incCapacity() call)
											for (size_t i = 0; i < STORAGE_TOKENS_PER_GW-1; i++) {
												this->phase_manager.decCapacityTokens();
											}

											this->phase_manager.incCapacity(STORAGE_GW_PER_INCREMENT);
											this->plant_ptr_vec[this->phase_manager.getIndex()]
												->setPowerCapacity(this->phase_manager.getCapacity());
											this->plant_ptr_vec[this->phase_manager.getIndex()]
												->setEnergyCapacity(this->phase_manager.getCapacity());

										}

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() * STORAGE_TOKENS_PER_GW;

									break;

								default:
									// all other plants
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									this->phase_manager.incCapacity(GW_PER_TOKEN);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									break;
							} // end switch(texture_key)

							// if change, play sound
							if (last_tokens != next_tokens) {
								this->assets.getSound("capacity token")->play();
							}
						}

						break;

					default:
						// do nothing!
						break;
				}
				break;

			// move down
			case (sf::Keyboard::S):
				this->pictorial_tutorial.show_wasd_instructions_ws = false;
				switch(this->phase_manager.getPhase()) {

					case (1):
						{
							// store last
							int last_marbles = this->plant_ptr_vec[this->phase_manager.getIndex()]->
								getMusteredMarbles();

							// call decreaseMarbles()
							this->plant_ptr_vec[this->phase_manager.getIndex()]->
								decMarbles();

							// if change, play sound
							if (
								last_marbles !=
								this->plant_ptr_vec[this->phase_manager.getIndex()]->
									getMusteredMarbles()
							) {
								this->assets.getSound("S key")->play();
							}
						}
						break;

					case (2):
						// select previous generator
						this->phase_manager.decPlantNum();
						this->plant_ptr_vec[this->phase_manager.getIndex()]
							->setPlantTexture(this->phase_manager.getPlantNum());

						// update price
						{
							int texture_idx = this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex();
							switch (texture_idx) {
								case (2):	// Fission
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(FISSION_TOKENS_PER_GW);
									break;

								case (5):	// Peaker
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(PEAKER_TOKENS_PER_GW);
									break;

								case (7):	// Storage
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(STORAGE_TOKENS_PER_GW);
									break;

								default:	// all other plants
									this->plant_ptr_vec[this->phase_manager.getIndex()]->setPrice(1);
									break;
							}
						}

						if (
							this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex() >= 0
						) {
							this->plantInfo(this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex());
						}
						else {
							this->text_box.makeBox(
								"",
								"bold",
								0.02 * SCREEN_HEIGHT,
								SCREEN_WIDTH / 8,
								SCREEN_HEIGHT / 8,
								SCREEN_WIDTH / 2,
								SCREEN_HEIGHT / 3
							);
						}

						this->assets.getSound("A D key")->play();
						break;

					case (3):
						// call decreaseCapactiy()
						// setting capacities
						{
							int texture_key = this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex();
							int last_tokens = 0;
							int next_tokens = 0;
							switch (texture_key) {
								case (-1):
									// null plant - do nothing
									std::cout << "null plant" << std::endl;
									break;

								case (2):
										last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									this->phase_manager.decCapacity(GW_PER_TOKEN);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									if (next_tokens != last_tokens) {
										// increase tokens by appropriate amount minus 1 (the first one happens during decCapacity() call)
										for (size_t i = 0; i < FISSION_TOKENS_PER_GW-1; i++) {
											this->phase_manager.incCapacityTokens();
										}
									}

									break;

								// special case for geothermal, need to make big investment to search for power
								case (3):
										last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									this->phase_manager.decCapacity(CAPACITY_PER_GEOTHERMAL_ROLL);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									if (next_tokens != last_tokens) {
										// increase tokens by appropriate amount minus 1 (the first one happens during decCapacity() call)
										for (size_t i = 0; i < CAPACITY_PER_GEOTHERMAL_ROLL/GW_PER_TOKEN-1; i++) {
											this->phase_manager.incCapacityTokens();
										}
									}

									break;

								case (4):
									// hydro - set capacity_GWh and charge_GWh based on table
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									this->phase_manager.decCapacity(GW_PER_TOKEN);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setEnergyCapacity(this->phase_manager.hydroStorageTable(this->phase_manager.getCapacity()));
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setCharge(this->phase_manager.hydroStorageTable(this->phase_manager.getCapacity()));//this should equal energy capacity

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									break;

								case (5):
									// peaker - cannot exceed 9 GW capacity
									// need to check all plants that are peaker gas
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									this->phase_manager.decCapacity(GW_PER_TOKEN);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

										if (next_tokens != last_tokens) {
											// increase tokens by appropriate amount minus 1 (the first one happens during decCapacity() call)
											for (size_t i = 0; i < PEAKER_TOKENS_PER_GW-1; i++) {
												this->phase_manager.incCapacityTokens();
											}
										}

									break;

								case (7):
									// storage set capacity_GWh and charge_GWh based on capacity
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() * STORAGE_TOKENS_PER_GW;

									this->phase_manager.decCapacity(STORAGE_GW_PER_INCREMENT);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setEnergyCapacity(this->phase_manager.getCapacity());

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() * STORAGE_TOKENS_PER_GW;

										if (next_tokens != last_tokens) {
											// increase tokens by appropriate amount minus 1 (the first one happens during decCapacity() call)
											for (size_t i = 0; i < STORAGE_TOKENS_PER_GW-1; i++) {
												this->phase_manager.incCapacityTokens();
											}
										}
									break;

								default:
									// all other plants
									last_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									this->phase_manager.decCapacity(GW_PER_TOKEN);
									this->plant_ptr_vec[this->phase_manager.getIndex()]
										->setPowerCapacity(this->phase_manager.getCapacity());

									next_tokens = this->plant_ptr_vec[this->phase_manager.getIndex()]->
										getCapacityGW() / GW_PER_TOKEN;

									break;
							} // end switch(texture_key)

							// if change, play sound
							if (last_tokens != next_tokens) {
								this->assets.getSound("token return")->play();
							}
						}
						break;

					default:
						// do nothing!
						break;
				}
				break;


			// defer load
			case (sf::Keyboard::L):
				if (this->can_defer_load) {
					this->can_defer_load = false;
					this->deferLoad();
				}
				break;

			default:
				// do nothing!
				break;
		}
	}

	else {	// handle key releases
		this->key_vec[key] = false;
	}

	// keep pictorial_tutorial updated
	this->pictorial_tutorial.update(&this->phase_manager, &this->plant_ptr_vec);

	return;
}	// end Game::handleKeys()


void Game::renderOverlays(void) {
	/*
	 *	Helper function to handle the rendering of overlays
	 */

	// game overlay

	// playing the actual game == 1
	// selecting generators == 2
	// selecting capacities == 3

	double rgb = 0;

	// selection overlay
	if (this->phase_manager.getPhase() == 2) {
		sf::Text select_instructions_txt(
			"SELECT PLANT TYPES",
			*(this->assets.getFont("bold")),
			32
		);
		select_instructions_txt.setOrigin(
			select_instructions_txt.getLocalBounds().width / 2,
			select_instructions_txt.getLocalBounds().height / 2
		);
		select_instructions_txt.setPosition(
			SCREEN_WIDTH / 2,
			2 * SCREEN_HEIGHT / 3
		);

		this->window_ptr->draw(select_instructions_txt);
	}

	// capacity tokens overlay
	if (this->phase_manager.getPhase() == 3) {
		if (this->hour_of_day <= 5.5 || this->hour_of_day >= 17.5) {
			rgb = 255;
		}

		int n_tokens = this->phase_manager.getCapacityTokens();
		std::string tokens_str = " : " + std::to_string(n_tokens);
		sf::Text tokens_txt(
			tokens_str,
			*(this->assets.getFont("bold")),
			32
		);

		tokens_txt.setFillColor(sf::Color(rgb, rgb, rgb, 255));
		sf::Rect tokens_txt_rect = tokens_txt.getLocalBounds();
		double tokens_txt_h = tokens_txt_rect.height;
		double tokens_txt_w = tokens_txt_rect.width;
		tokens_txt.setOrigin(tokens_txt_w, 0);
		tokens_txt.setPosition(
			SCREEN_WIDTH - 32,
			tokens_txt_h - 2
		);
		this->window_ptr->draw(tokens_txt);

		this->capacity_token_sprite.setRotation(this->frame);
		this->capacity_token_sprite.setPosition(
			tokens_txt.getPosition().x - tokens_txt_w - 24,
			19 + tokens_txt_h + 6 * sin((2 * M_PI * this->frame) / FRAMES_PER_SECOND)
		);
		this->window_ptr->draw(this->capacity_token_sprite);

		sf::Text tokens_instructions_txt(
			"SET PLANT CAPACITIES",
			*(this->assets.getFont("bold")),
			32
		);
		tokens_instructions_txt.setOrigin(
			tokens_instructions_txt.getLocalBounds().width / 2,
			tokens_instructions_txt.getLocalBounds().height / 2
		);
		tokens_instructions_txt.setPosition(
			SCREEN_WIDTH / 2,
			2 * SCREEN_HEIGHT / 3
		);
		this->window_ptr->draw(tokens_instructions_txt);
	}

	// energy demand, score, and clock overlays
	if (this->phase_manager.getPhase() == 1) {
		if (this->hour_of_day <= 5.5 || this->hour_of_day >= 17.5) {
			rgb = 255;
		}

		// energy demand overlay
		int energy_demand = this->current_energy_demand_GWh;
		std::string energy_demand_str = " : " + std::to_string(energy_demand) + " GWh";
		sf::Text energy_demand_txt(
			energy_demand_str,
			*(this->assets.getFont("bold")),
			32
		);
		energy_demand_txt.setFillColor(sf::Color(rgb, rgb, rgb, 255));
		sf::Rect energy_demand_txt_rect = energy_demand_txt.getLocalBounds();
		double energy_demand_txt_h = energy_demand_txt_rect.height;
		double energy_demand_txt_w = energy_demand_txt_rect.width;
		energy_demand_txt.setOrigin(energy_demand_txt_w, 0);
		energy_demand_txt.setPosition(
			SCREEN_WIDTH - 32,
			energy_demand_txt_h - 15
		);
		this->window_ptr->draw(energy_demand_txt);

		this->energy_demand_sprite.setPosition(
			SCREEN_WIDTH - energy_demand_txt_w - 48,
			8 + energy_demand_txt_h + 6 * sin((2 * M_PI * this->frame) / FRAMES_PER_SECOND)
		);
		this->window_ptr->draw(this->energy_demand_sprite);

		// score overlay
		std::string score_str = "Score: " + std::to_string(this->score);
		while (score_str.back() == '0') {
			score_str.pop_back();
			if (score_str.back() == '.') {
				score_str.pop_back();
				break;
			}
		}
		sf::Text score_txt(
			score_str,
			*(this->assets.getFont("bold")),
			30
		);
		score_txt.setFillColor(sf::Color(rgb, rgb, rgb, 255));
		sf::Rect score_txt_rect = energy_demand_txt.getLocalBounds();
		double score_txt_h = energy_demand_txt_rect.height;
		double score_txt_w = energy_demand_txt_rect.width;
		score_txt.setOrigin(score_txt_w / 2, score_txt_h / 2);
		score_txt.setPosition(
			SCREEN_WIDTH / 2,
			score_txt_h - 5
		);
		this->window_ptr->draw(score_txt);

		// clock overlay
		int hour = int(this->hour_of_day);
		int min = int((this->hour_of_day - int(hour_of_day)) * 60);
		std::string time_str = "";
		if (hour < 10) {
			time_str += "0" + std::to_string(hour);
		}
		else {
			time_str += std::to_string(hour);
		}
		time_str += ":";
		if (min < 10) {
			time_str += "0" + std::to_string(min);
		}
		else {
			time_str += std::to_string(min);
		}
		sf::Text time_txt(
			time_str,
			*(this->assets.getFont("bold")),
			32
		);

		time_txt.setFillColor(sf::Color(rgb, rgb, rgb, 255));
		sf::Rect time_txt_rect = time_txt.getLocalBounds();
		double time_txt_h = ceil(time_txt_rect.height);
		double time_txt_w = ceil(time_txt_rect.width);

		this->clock_face_sprite.setPosition(26, 26);
		time_txt.setPosition(
			this->clock_face_sprite.getPosition().x + 28,
			5
		);
		this->window_ptr->draw(time_txt);
		this->window_ptr->draw(this->clock_face_sprite);

		this->clock_minute_sprite.setPosition(26, 26);
		this->clock_minute_sprite.setRotation(6 * min);
		this->window_ptr->draw(this->clock_minute_sprite);

		this->clock_hour_sprite.setPosition(26, 26);
		this->clock_hour_sprite.setRotation(30 * this->hour_of_day);
		this->window_ptr->draw(this->clock_hour_sprite);
	}

	// dice roll overlay
	if (this->phase_manager.getPhase() == 4) {
		// if dice are still rolling get a new dice number
		if (this->dice_roll.getRollingDice()) {
			this->dice_roll.drawFrame(true);
		}
		else {
			this->dice_roll.drawFrame(false);
		}

		// draw remaining rolls
		for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
			if (this->phase_manager.getGeothermalPresent(i)) {
				int num_rolls_rem = 3 * this->dice_roll.getRollsLeft(i) -
					this->rolls_rem_corr;
				sf::Text rolls_txt(
					"WELLS REMAINING: " + std::to_string(num_rolls_rem),
					*(this->assets.getFont("bold")),
					16
				);
				rolls_txt.setOrigin(
					rolls_txt.getLocalBounds().width / 2,
					rolls_txt.getLocalBounds().height / 2
				);
				rolls_txt.setPosition(
					this->plant_ptr_vec[i]->getPositionX(),
					this->plant_ptr_vec[i]->getPositionY() - 140
				);
				this->window_ptr->draw(rolls_txt);
			}
		}
	}

	// points text overlay
	if (!this->points_str.empty()) {
		sf::Text points_text(
			this->points_str,
			*(this->assets.getFont("bold")),
			14
		);
		points_text.setOrigin(points_text.getLocalBounds().width / 2, 0);
		points_text.setPosition(
			SCREEN_WIDTH / 2,
		 	60 + 4 * (1 + cos((M_PI * this->frame) / FRAMES_PER_SECOND)) / 2
		);

		sf::RectangleShape backing_rect;
		backing_rect.setFillColor(TEXT_BOX_BACK_COLOUR);
		backing_rect.setOutlineColor(TEXT_BOX_OUTLINE_COLOUR);
		backing_rect.setOutlineThickness(TEXT_BOX_OUTLINE_THICKNESS);
		backing_rect.setSize(
			sf::Vector2f(
				1.05 * points_text.getLocalBounds().width,
				1.1 * points_text.getLocalBounds().height
			)
		);
		backing_rect.setOrigin(backing_rect.getLocalBounds().width / 2, 0);
		backing_rect.setPosition(
			SCREEN_WIDTH / 2 + 8,
			60 + 4 * (1 + cos((M_PI * this->frame) / FRAMES_PER_SECOND)) / 2 - 8
		);

		this->window_ptr->draw(backing_rect);
		this->window_ptr->draw(points_text);
	}

	// smog overlay (rect, general "smoginess")
	sf::RectangleShape smog_rect;
	smog_rect.setFillColor(
		sf::Color(
			SMOG_COLOUR.r,
			SMOG_COLOUR.g,
			SMOG_COLOUR.b,
			this->smog_ratio * 200
		)
	);
	smog_rect.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	this->window_ptr->draw(smog_rect);

	// forecast overlay
	if (this->draw_forecast_overlay && this->phase_manager.getPhase() == 1) {
		sf::RectangleShape backing_rect(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		backing_rect.setFillColor(sf::Color(0, 0, 0, 200));
		this->window_ptr->draw(backing_rect);

		// draw title
		sf::Text title_txt(
			"Forecast Overlay",
			*(this->assets.getFont("bold")),
			24
		);
		title_txt.setOrigin(
			title_txt.getLocalBounds().width / 2,
			title_txt.getLocalBounds().height / 2
		);
		title_txt.setPosition(
			SCREEN_WIDTH / 2,
			70
		);
		this->window_ptr->draw(title_txt);

		// demand forecast
		sf::Sprite energy_demand_sprite(
			*(this->assets.getTexture("energy demand"))
		);
		energy_demand_sprite.setOrigin(
			energy_demand_sprite.getLocalBounds().width,
			energy_demand_sprite.getLocalBounds().height / 2
		);
		energy_demand_sprite.setPosition(
			SCREEN_WIDTH / 5,
			SCREEN_HEIGHT / 5
		);
		energy_demand_sprite.scale(2, 2);
		this->window_ptr->draw(energy_demand_sprite);

		std::string energy_demand_str = " : ";
		energy_demand_str += std::to_string(this->forecast_map["demand GWh"]);
		energy_demand_str += " +/- 2 GWh";
		sf::Text energy_demand_txt(
			energy_demand_str,
			*(this->assets.getFont("bold")),
			24
		);
		energy_demand_txt.setOrigin(
			0,
			energy_demand_txt.getLocalBounds().height / 2
		);
		energy_demand_txt.setPosition(
			SCREEN_WIDTH / 5,
			SCREEN_HEIGHT / 5 - 6
		);
		this->window_ptr->draw(energy_demand_txt);


		// renewable production forecast
		int n_renewables = 0;
		double renewable_scalar = 0.75;
		int forecast_GWh = 0;
		int forecast_error_GWh = 0;
		std::vector<double> forecast_return_vec = {0, 0};
		std::string renewable_str;
		sf::Sprite renewable_sprite;
		sf::Text renewable_txt;
		renewable_txt.setFont(*(this->assets.getFont("bold")));
		renewable_txt.setCharacterSize(24);
		for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
			int texture_key = this->plant_ptr_vec[i]->getTextureIndex();
			switch (texture_key) {
				case (6):	// Solar
					n_renewables++;
					renewable_sprite.setTexture(
						*(this->assets.getTexture("solar"))
					);
					renewable_sprite.setOrigin(
						renewable_sprite.getLocalBounds().width,
						renewable_sprite.getLocalBounds().height / 2
					);
					renewable_sprite.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_sprite);

					forecast_GWh = round(forecast_return_vec[0]);
					forecast_error_GWh = round(forecast_return_vec[1]);
					renewable_str = " : ";
					renewable_str += std::to_string(
						this->forecast_map["solar forecast GWh"]
					);
					renewable_str += " +/- ";
					renewable_str += std::to_string(
						this->forecast_map["solar forecast error GWh"]
					);
					renewable_str += " GWh";
					renewable_txt.setString(renewable_str);
					renewable_txt.setOrigin(
						0,
						renewable_txt.getLocalBounds().height / 2
					);
					renewable_txt.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_txt);

					break;

				case (8):	// Tidal
					n_renewables++;
					renewable_sprite.setTexture(
						*(this->assets.getTexture("tidal selection"))
					);
					renewable_sprite.setOrigin(
						renewable_sprite.getLocalBounds().width,
						renewable_sprite.getLocalBounds().height / 2
					);
					renewable_sprite.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_sprite);

					forecast_GWh = round(forecast_return_vec[0]);
					forecast_error_GWh = round(forecast_return_vec[1]);
					renewable_str = " : ";
					renewable_str += std::to_string(
						this->forecast_map["tidal forecast GWh"]
					);
					renewable_str += " +/- ";
					renewable_str += std::to_string(
						this->forecast_map["tidal forecast error GWh"]
					);
					renewable_str += " GWh";
					renewable_txt.setString(renewable_str);
					renewable_txt.setOrigin(
						0,
						renewable_txt.getLocalBounds().height / 2
					);
					renewable_txt.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_txt);

					break;

				case (9):	// Wave
					n_renewables++;
					renewable_sprite.setTexture(
						*(this->assets.getTexture("wave selection"))
					);
					renewable_sprite.setOrigin(
						renewable_sprite.getLocalBounds().width,
						renewable_sprite.getLocalBounds().height / 2
					);
					renewable_sprite.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_sprite);

					forecast_GWh = round(forecast_return_vec[0]);
					forecast_error_GWh = round(forecast_return_vec[1]);
					renewable_str = " : ";
					renewable_str += std::to_string(
						this->forecast_map["wave forecast GWh"]
					);
					renewable_str += " +/- ";
					renewable_str += std::to_string(
						this->forecast_map["wave forecast error GWh"]
					);
					renewable_str += " GWh";
					renewable_txt.setString(renewable_str);
					renewable_txt.setOrigin(
						0,
						renewable_txt.getLocalBounds().height / 2
					);
					renewable_txt.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_txt);

					break;

				case (10):	// Wind
					n_renewables++;
					renewable_sprite.setTexture(
						*(this->assets.getTexture("wind selection"))
					);
					renewable_sprite.setOrigin(
						renewable_sprite.getLocalBounds().width,
						renewable_sprite.getLocalBounds().height / 2
					);
					renewable_sprite.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_sprite);

					forecast_GWh = round(forecast_return_vec[0]);
					forecast_error_GWh = round(forecast_return_vec[1]);
					renewable_str = " : ";
					renewable_str += std::to_string(
						this->forecast_map["wind forecast GWh"]
					);
					renewable_str += " +/- ";
					renewable_str += std::to_string(
						this->forecast_map["wind forecast error GWh"]
					);
					renewable_str += " GWh";
					renewable_txt.setString(renewable_str);
					renewable_txt.setOrigin(
						0,
						renewable_txt.getLocalBounds().height / 2
					);
					renewable_txt.setPosition(
						SCREEN_WIDTH / 5 + 30,
						SCREEN_HEIGHT / 5 + n_renewables * (
							renewable_sprite.getLocalBounds().height
						)
					);
					this->window_ptr->draw(renewable_txt);

					break;

				default:
					// do nothing!
					break;
			}
		}
	}

	// energy overlay
	if (
		this->draw_energy_overlay &&
		(
			this->phase_manager.getPhase() == 1 ||
			this->phase_manager.getPhase() == 5
		)
	) {
		sf::RectangleShape backing_rect(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		backing_rect.setFillColor(sf::Color(0, 0, 0, 200));
		this->window_ptr->draw(backing_rect);

		double pixels_per_GWh = round((0.75 * SCREEN_HEIGHT) / 25);
		double pixels_per_hour = round((0.75 * SCREEN_WIDTH) / 25);
		double origin_x = 0.125 * SCREEN_WIDTH;
		double max_x = 0.875 * SCREEN_WIDTH;
		double origin_y = 0.875 * SCREEN_HEIGHT;
		double min_y = 0.125 * SCREEN_HEIGHT - 5;

		// draw vertical axis
		sf::Vertex vert_vertex_array[2] = {
			sf::Vertex(sf::Vector2f(origin_x, origin_y)),
			sf::Vertex(sf::Vector2f(origin_x, min_y))
		};
		this->window_ptr->draw(vert_vertex_array, 2, sf::Lines);
		for (int i = 0; i < 26; i++) {
			sf::Text y_tick(
				std::to_string(i),
				*(this->assets.getFont("teletype")),
				16
			);
			y_tick.setOrigin(
				y_tick.getLocalBounds().width / 2,
				y_tick.getLocalBounds().height / 2
			);
			y_tick.setPosition(
				0.105 * SCREEN_WIDTH,
				origin_y - i * pixels_per_GWh - 5
			);
			this->window_ptr->draw(y_tick);

			sf::Vertex grid_array[2] = {
				sf::Vertex(
					sf::Vector2f(origin_x, origin_y - i * pixels_per_GWh),
					sf::Color(128, 128, 128, 150)
				),
				sf::Vertex(
					sf::Vector2f(max_x, origin_y - i * pixels_per_GWh),
					sf::Color(128, 128, 128, 150)
				)
			};
			this->window_ptr->draw(grid_array, 2, sf::Lines);
		}
		sf::Text vert_label(
			"Energy [GWh]",
			*(this->assets.getFont("teletype")),
			24
		);
		vert_label.setOrigin(
			vert_label.getLocalBounds().width / 2,
			vert_label.getLocalBounds().height / 2
		);
		vert_label.setPosition(
			0.075 * SCREEN_WIDTH,
			0.5 * (origin_y + min_y)
		);
		vert_label.setRotation(-90);
		this->window_ptr->draw(vert_label);

		// draw horizontal axis
		sf::Vertex horiz_vertex_array[2] = {
			sf::Vertex(sf::Vector2f(origin_x, origin_y)),
			sf::Vertex(sf::Vector2f(max_x, origin_y))
		};
		this->window_ptr->draw(horiz_vertex_array, 2, sf::Lines);
		for (int i = 0; i <= this->hour_of_day; i++) {
			if (i >= 24) {
				break;
			}
			sf::Text x_tick(
				std::to_string(i),
				*(this->assets.getFont("teletype")),
				16
			);
			x_tick.setOrigin(x_tick.getLocalBounds().width / 2, 0);
			x_tick.setPosition(
				origin_x + (i + 0.5) * pixels_per_hour,
				0.885 * SCREEN_HEIGHT
			);
			this->window_ptr->draw(x_tick);
		}
		sf::Text horiz_label(
			"Hour of Day [\t]",
			*(this->assets.getFont("teletype")),
			24
		);
		horiz_label.setOrigin(
			horiz_label.getLocalBounds().width / 2,
			horiz_label.getLocalBounds().height / 2
		);
		horiz_label.setPosition(
			0.5 * (origin_x + max_x),
			0.925 * SCREEN_HEIGHT
		);
		this->window_ptr->draw(horiz_label);

		// draw dispatch columns
		int dispatch_cumul_sum = 0;
		for (int i = 0; i < this->hour_of_day; i++) {
			if (i >= 24) {
				break;
			}
			for (int j = 0; j < this->plant_ptr_vec.size(); j++) {
				if (this->plant_ptr_vec[j]->getTextureIndex() < 0) {
					continue;
				}
				sf::RectangleShape disp_rect(
					sf::Vector2f(
						0.8 * pixels_per_hour,
						pixels_per_GWh * this->plant_ptr_vec[j]->getMarblesCommitted(i)
					)
				);
				disp_rect.setOrigin(
					disp_rect.getLocalBounds().width / 2,
					disp_rect.getLocalBounds().height
				);
				disp_rect.setPosition(
					origin_x + (i + 0.5) * pixels_per_hour,
					origin_y - pixels_per_GWh * dispatch_cumul_sum - 1
				);
				disp_rect.setFillColor(
					this->plant_ptr_vec[j]->getMarbleColour()
				);
				dispatch_cumul_sum +=
					this->plant_ptr_vec[j]->getMarblesCommitted(i);
				this->window_ptr->draw(disp_rect);
			}
			dispatch_cumul_sum = 0;
		}

		// draw actual demands
		for (int i = 0; i <= this->hour_of_day; i++) {
			if (i >= 24) {
				break;
			}
			sf::RectangleShape demand_rect(
				sf::Vector2f(
					pixels_per_hour / 4,
					pixels_per_GWh * this->actual_energy_demand_GWh_vec[i]
				)
			);
			demand_rect.setOrigin(
				demand_rect.getLocalBounds().width / 2,
				demand_rect.getLocalBounds().height
			);
			demand_rect.setPosition(
				origin_x + (i + 0.5) * pixels_per_hour,
				origin_y - 1
			);
			this->window_ptr->draw(demand_rect);
		}

		// draw legend
		sf::Text legend_txt(
			"Legend",
			*(this->assets.getFont("teletype")),
			20
		);
		legend_txt.setOrigin(0, legend_txt.getLocalBounds().height / 2);
		legend_txt.setPosition(0.895 * SCREEN_WIDTH, min_y);
		double legend_txt_h = legend_txt.getLocalBounds().height;
		this->window_ptr->draw(legend_txt);

		sf::RectangleShape demand_rect(sf::Vector2f(16, 16));
		demand_rect.setOrigin(0, demand_rect.getLocalBounds().height / 2);
		demand_rect.setPosition(
			0.895 * SCREEN_WIDTH,
			min_y + legend_txt_h + 25
		);
		this->window_ptr->draw(demand_rect);

		sf::Text demand_txt(
			"Demand",
			*(this->assets.getFont("teletype")),
			16
		);
		demand_txt.setOrigin(0, demand_txt.getLocalBounds().height / 2);
		demand_txt.setPosition(
			0.895 * SCREEN_WIDTH + 25,
			min_y + legend_txt_h + 25 - 2
		);
		this->window_ptr->draw(demand_txt);

		for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
			if (this->plant_ptr_vec[i]->getTextureIndex() < 0) {
				continue;
			}
			sf::RectangleShape plant_rect(sf::Vector2f(16, 16));
			plant_rect.setOrigin(0, plant_rect.getLocalBounds().height / 2);
			plant_rect.setPosition(
				0.895 * SCREEN_WIDTH,
				min_y + legend_txt_h + 25 * (i + 2)
			);
			plant_rect.setFillColor(
				this->plant_ptr_vec[i]->getMarbleColour()
			);
			this->window_ptr->draw(plant_rect);

			sf::Text plant_txt(
				"plant",
				*(this->assets.getFont("teletype")),
				16
			);
			plant_txt.setOrigin(0, plant_txt.getLocalBounds().height / 2);
			plant_txt.setPosition(
				0.895 * SCREEN_WIDTH + 25,
				min_y + legend_txt_h + 25 * (i + 2) - 2
			);

			int texture_index = this->plant_ptr_vec[i]->getTextureIndex();
			switch (texture_index) {
				case (0):	// Coal
					plant_txt.setString("Coal");
					break;

				case (1):	// Combined
					plant_txt.setString("Combined");
					break;

				case (2):	// Fission
					plant_txt.setString("Fission");
					break;

				case (3):	// Geothermal
					plant_txt.setString("Geothermal");
					break;

				case (4):	// Hydro
					plant_txt.setString("Hydro");
					break;

				case (5):	// Peaker
					plant_txt.setString("Peaker");
					break;

				case (6):	// Solar
					plant_txt.setString("Solar");
					break;

				case (7):	// Storage
					plant_txt.setString("Storage");
					break;

				case (8):	// Tidal
					plant_txt.setString("Tidal");
					break;

				case (9):	// Wave
					plant_txt.setString("Wave");
					break;

				case (10):	// Wind
					plant_txt.setString("Wind");
					break;

				default:
					// do nothing!
					break;
			}

			this->window_ptr->draw(plant_txt);
		}

		// draw title
		sf::Text title_txt(
			"Energy Overlay",
			*(this->assets.getFont("bold")),
			24
		);
		title_txt.setOrigin(
			title_txt.getLocalBounds().width / 2,
			title_txt.getLocalBounds().height / 2
		);
		title_txt.setPosition(
			SCREEN_WIDTH / 2,
			70
		);
		this->window_ptr->draw(title_txt);
	}

	// game over overlay
	if (this->phase_manager.getPhase() == 5) {
		// init rectangle
		sf::RectangleShape background_rect;
		background_rect.setFillColor(sf::Color(64, 64, 64, 230));

		// set text font, size, and string
		sf::Text game_over_text;
		sf::Text score_text;
		sf::Text message_text;
		game_over_text.setFont(*(this->assets.getFont("teletype")));
		game_over_text.setCharacterSize(32);
		score_text.setFont(*(this->assets.getFont("teletype")));
		score_text.setCharacterSize(32);
		message_text.setFont(*(this->assets.getFont("teletype")));
		message_text.setCharacterSize(32);

		std::string score_str = "Score: " + std::to_string(this->score);
		while (score_str.back() == '0') {
			score_str.pop_back();
			if (score_str.back() == '.') {
				score_str.pop_back();
				break;
			}
		}
		game_over_text.setString("Game Over");
		score_text.setString(score_str);
		message_text.setString("Press any key to restart.");

		// place game over text
		int text_width = ceil(1.01 * game_over_text.getLocalBounds().width);
		int text_height = ceil(1.01 * game_over_text.getLocalBounds().height) + 4;
		game_over_text.setPosition(
			(SCREEN_WIDTH - text_width) / 2,
			(SCREEN_HEIGHT - text_height) / 2 + text_height
		);

		// place score text
		text_width = ceil(1.01 * score_text.getLocalBounds().width);
		score_text.setPosition(
			(SCREEN_WIDTH - text_width) / 2,
			(SCREEN_HEIGHT - text_height) / 2 + text_height * 3
		);

		// place message text
		text_width = ceil(1.01 * message_text.getLocalBounds().width);
		message_text.setPosition(
			(SCREEN_WIDTH - text_width) / 2,
			(SCREEN_HEIGHT - text_height) / 2 + text_height * 5
		);

		// size rectangle
		sf::Vector2f size_vec(text_width + 4, text_height * 6 - 10);
		background_rect.setSize(size_vec);
		background_rect.setPosition(
			(SCREEN_WIDTH - text_width) / 2 - 2,
			(SCREEN_HEIGHT - text_height) / 2 + text_height
		);

		// draw
		this->window_ptr->draw(background_rect);
		this->window_ptr->draw(game_over_text);
		this->window_ptr->draw(score_text);
		this->window_ptr->draw(message_text);
	}

	// text box overlay
	this->text_box.drawFrame();

	// frame rate overlay
	if (this->draw_frame_rate) {
		// init rectangle
		sf::RectangleShape background_rect;
		background_rect.setFillColor(sf::Color(64, 64, 64, 192));

		// set text font and size
		sf::Text frame_text;
		frame_text.setFont(*(this->assets.getFont("teletype")));
		frame_text.setCharacterSize(12);

		// set text string
		std::stringstream ss;

		ss << "  Frame:                  " <<
			this->frame <<
			"\n  Time Elapsed:      " << std::setprecision(4) <<
			this->time_since_run_s <<
	      " s\n  FPS (avg.):            " << std::setprecision(4) <<
		  	double(this->frame) / this->time_since_run_s <<
			"\n  Frame Time (dt):  " << std::setprecision(4) <<
			this->dt_s <<
		  " s\n";

		std::string frame_str = ss.str();
		frame_text.setString(frame_str);

		// size rectangle
		sf::Vector2f size_vec(
			ceil(1.05 * frame_text.getLocalBounds().width),
			60
		);
		background_rect.setSize(size_vec);

		// draw
		this->window_ptr->draw(background_rect);
		this->window_ptr->draw(frame_text);
	}

	// track overlay
	this->music_player.renderTrackInfo();

	// music paused overlay
	if (this->music_paused) {
		// init rectangle
		sf::RectangleShape background_rect;
		background_rect.setFillColor(sf::Color(64, 64, 64, 192));

		// set text font, size, and string
		sf::Text music_paused_text;
		music_paused_text.setFont(*(this->assets.getFont("teletype")));
		music_paused_text.setCharacterSize(16);
		music_paused_text.setString("MUSIC PAUSED");
		int text_width = ceil(1.01 * music_paused_text.getLocalBounds().width);
		int text_height = ceil(1.01 * music_paused_text.getLocalBounds().height) + 4;
		music_paused_text.setPosition(
			(SCREEN_WIDTH - text_width) / 2,
			SCREEN_HEIGHT - text_height - 8
		);

		// size rectangle
		sf::Vector2f size_vec(text_width + 4, text_height + 2);
		background_rect.setSize(size_vec);
		background_rect.setPosition(
			(SCREEN_WIDTH - text_width) / 2 - 2,
			SCREEN_HEIGHT - text_height - 8
		);

		// draw
		this->window_ptr->draw(background_rect);
		this->window_ptr->draw(music_paused_text);
	}

	// quit round overlay
	if (this->phase_manager.getQuittingRound()){
		// init rectangle
		sf::RectangleShape background_rect;
		background_rect.setFillColor(sf::Color(64, 64, 64, 192));

		// set text font, size, and string
		sf::Text quit_game_text;
		quit_game_text.setFont(*(this->assets.getFont("teletype")));
		quit_game_text.setCharacterSize(32);
		quit_game_text.setString("Are you sure you want to quit and restart? (Y/N)");
		int text_width = ceil(1.01 * quit_game_text.getLocalBounds().width);
		int text_height = ceil(1.01 * quit_game_text.getLocalBounds().height) + 4;
		quit_game_text.setPosition(
			(SCREEN_WIDTH - text_width) / 2,
			(SCREEN_HEIGHT - text_height) / 2 + 30
		);

		// size rectangle
		sf::Vector2f size_vec(text_width + 4, text_height + 2);
		background_rect.setSize(size_vec);
		background_rect.setPosition(
			(SCREEN_WIDTH - text_width) / 2 - 2,
			(SCREEN_HEIGHT - text_height) / 2 + 30
		);

		// draw
		this->window_ptr->draw(background_rect);
		this->window_ptr->draw(quit_game_text);
	}

	// quit game overlay
	if (this->phase_manager.getQuittingGame()){
		// init rectangle
		sf::RectangleShape background_rect;
		background_rect.setFillColor(sf::Color(64, 64, 64, 192));

		// set text font, size, and string
		sf::Text quit_game_text;
		quit_game_text.setFont(*(this->assets.getFont("teletype")));
		quit_game_text.setCharacterSize(32);
		quit_game_text.setString("Are you sure you want to quit and close the game? (Y/N)");
		int text_width = ceil(1.01 * quit_game_text.getLocalBounds().width);
		int text_height = ceil(1.01 * quit_game_text.getLocalBounds().height) + 4;
		quit_game_text.setPosition(
			(SCREEN_WIDTH - text_width) / 2,
			(SCREEN_HEIGHT - text_height) / 2 + 30
		);

		// size rectangle
		sf::Vector2f size_vec(text_width + 4, text_height + 2);
		background_rect.setSize(size_vec);
		background_rect.setPosition(
			(SCREEN_WIDTH - text_width) / 2 - 2,
			(SCREEN_HEIGHT - text_height) / 2 + 30
		);

		// draw
		this->window_ptr->draw(background_rect);
		this->window_ptr->draw(quit_game_text);
	}

	// wasd overlays
	if (this->phase_manager.getPhase() == 2) {
		this->pictorial_tutorial.drawFrame(this->phase_manager.getPhase());
	}
	// selecting capacities
	if (this->phase_manager.getPhase() == 3) {
		this->pictorial_tutorial.drawFrame(this->phase_manager.getPhase());
	}
	// playing game
	if (this->phase_manager.getPhase() == 1
			&& (this->pictorial_tutorial.show_wasd_instructions_ad
					|| this->pictorial_tutorial.show_wasd_instructions_ws
					|| this->pictorial_tutorial.show_spacebar_instructions)) {
		this->pictorial_tutorial.drawFrame(this->phase_manager.getPhase());
	}

	return;
}	// end Game::renderOverlays()


void Game::render(void) {
	/*
	 *	Method to render the game to the screen
	 */

	// clear back buffer
	this->window_ptr->clear();

	// draw backgrounds

	//	1. sky disk
	this->sky_disk.drawFrame(this->hour_of_day);

	//	2. overcast and clouds
	this->overcast_clouds.drawFrame(
		this->wind_speed_ratio,
		this->cloud_cover_ratio,
		this->hour_of_day
	);

	//	3. smog dome (circ, behind city)
	sf::CircleShape smog_circ;
	smog_circ.setFillColor(
		sf::Color(
			SMOG_COLOUR.r,
			SMOG_COLOUR.g,
			SMOG_COLOUR.b,
			this->smog_ratio * 200
		)
	);
	double radius = 1.1 * SCREEN_HEIGHT / 3;
	smog_circ.setRadius(radius);
	smog_circ.setOrigin(radius, radius);
	smog_circ.setPosition(
		sf::Vector2f(
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2
		)
	);
	this->window_ptr->draw(smog_circ);

	//	4. foreground + Plinko City
	this->foreground.drawFrame(this->powered_flag, this->hour_of_day);

	//	5. wind sock
	this->wind_sock.drawFrame(this->wind_speed_ratio, this->hour_of_day);

	// draw objects if not at main menu
	if (this->phase_manager.getPhase() != 0) {
		//std::cout << this->plant_ptr_vec.size() << std::endl;
		for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
			this->plant_ptr_vec[i]->drawMarbles();
			this->plant_ptr_vec[i]->drawSteam(this->wind_speed_ratio);
			this->plant_ptr_vec[i]->drawSmoke(this->wind_speed_ratio);
			this->plant_ptr_vec[i]->drawFrame(
				i == this->phase_manager.getIndex(),
				this->phase_manager.getPhase() == 1
			);

			if (
				this->can_defer_load &&
				this->plant_ptr_vec[i]->getTextureIndex() == 7 &&	// Storage
				this->phase_manager.getPhase() == 1
			) {
				sf::Text load_defer_txt(
					"[L]: DEFER LOAD",
					*(this->assets.getFont("bold")),
					16
				);
				load_defer_txt.setOrigin(
					load_defer_txt.getLocalBounds().width / 2,
					load_defer_txt.getLocalBounds().height / 2
				);
				load_defer_txt.setPosition(
					this->plant_ptr_vec[i]->getPositionX(),
					this->plant_ptr_vec[i]->getPositionY() - 128
				);
				this->window_ptr->draw(load_defer_txt);
			}
		}
	}

	// switch between phases
	switch(this->phase_manager.getPhase()){
		// playing the actual game
		case (1):


			break;// end of case 1: actual game

		// selecting generators
		case (2):
			/* TESTING */
				/*
				std::cout << "Index:\t"
				<< this->phase_manager.getIndex()
				<< "\tPlant:\t"
				<< this->phase_manager.getPlantNum()
				<< std::endl;
				*/
			/* END TESTING */

			/*
				for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
					this->plant_ptr_vec[i]->drawSteam(this->wind_speed_ratio);
					this->plant_ptr_vec[i]->drawSmoke(this->wind_speed_ratio);
					this->plant_ptr_vec[i]->drawFrame(i == this->phase_manager.getIndex());
				}
				*/
			break;// end of case 2: selecting generators

		// selecting capacities
		case (3):
			/* TESTING */
		//	/*
				if (this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex() == 4
							|| this->plant_ptr_vec[this->phase_manager.getIndex()]->getTextureIndex() == 7) {
								std::cout << "Index:\t"
								<< this->phase_manager.getIndex()
								<< "\tCapacity:\t"
								<< this->phase_manager.getCapacity() << "\t"
								<< this->plant_ptr_vec[this->phase_manager.getIndex()]->getCapacityGW()
								<< "\tStorage:\t"
								<< this->plant_ptr_vec[this->phase_manager.getIndex()]->getStorageGWh()
								<< "\tCharge:\t"
								<< this->plant_ptr_vec[this->phase_manager.getIndex()]->getChargeGWh()
								<< "\tTokens:\t"
								<< this->phase_manager.getCapacityTokens()
								<< std::endl;
				}else{
					std::cout << "Index:\t"
					<< this->phase_manager.getIndex()
					<< "\tCapacity:\t"
					<< this->phase_manager.getCapacity() << "\t"
					<< this->plant_ptr_vec[this->phase_manager.getIndex()]->getCapacityGW()
					<< "\tTokens:\t"
					<< this->phase_manager.getCapacityTokens()
					<< std::endl;
				}
		//	*/
			/* END TESTING */

			/*
			for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
				this->plant_ptr_vec[i]->drawSteam(this->wind_speed_ratio);
				this->plant_ptr_vec[i]->drawSmoke(this->wind_speed_ratio);
				this->plant_ptr_vec[i]->drawFrame(i == this->phase_manager.getIndex());
			}
			*/
			break;// end of case 3: selecting capacities

		case (4):
			/* TESTING */
			/*
				std::cout << "geothermal bool values:\t"
				<< this->phase_manager.getGeothermalPresent(0)
				<< "\t" << this->phase_manager.getGeothermalPresent(1)
				<< "\t" << this->phase_manager.getGeothermalPresent(2)
				<< "\t" << this->phase_manager.getGeothermalPresent(3)
				<< std::endl;
			*/
			/* END TESTING */

			break; // end of case 4: rolling for geothermal

		case (5): // game over screen
			// does nothing for now
			break; // end of case 5: game over

		// menu
		default:
			// probably just call drawMenu or something for final product
			// init rectangle
			sf::RectangleShape background_rect;
			background_rect.setFillColor(sf::Color(64, 64, 64, 230));

			// set text font, size, and string
			sf::Text menu_text;
			menu_text.setFont(*(this->assets.getFont("teletype")));
			menu_text.setCharacterSize(32);
			menu_text.setString("You are at the menu.\nPress Spacebar to play.");
			int text_width = ceil(1.01 * menu_text.getLocalBounds().width);
			int text_height = ceil(1.01 * menu_text.getLocalBounds().height) + 4;
			menu_text.setPosition(
				(SCREEN_WIDTH - text_width) / 2,
				(SCREEN_HEIGHT - text_height) / 2 + 26
			);

			// size rectangle
			sf::Vector2f size_vec(text_width + 4, text_height + 2);
			background_rect.setSize(size_vec);
			background_rect.setPosition(
				(SCREEN_WIDTH - text_width) / 2 - 2,
				(SCREEN_HEIGHT - text_height) / 2 + 32
			);

			// draw
			this->window_ptr->draw(background_rect);
			this->window_ptr->draw(menu_text);

	} //end switch phase

	if (this->fade_alpha > 0) {
		sf::RectangleShape black_rect(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		black_rect.setFillColor(
			sf::Color(0, 0, 0, this->fade_alpha)
		);

		this->window_ptr->draw(black_rect);

		this->fade_alpha -= 2;
		if (this->fade_alpha <= 0) {
			this->fade_alpha = 0;

			// init tutorial
			// display tutorial
			this->text_box.makeBox(
				std::string(TEXT_TUTORIAL),
				"bold",
				0.02 * SCREEN_HEIGHT,
				SCREEN_WIDTH / 8,
				SCREEN_HEIGHT / 8,
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 3
			);

			//reset pictorial_tutorial
			this->pictorial_tutorial.reset();
		}
	}
	else {
		// draw overlays
		this->renderOverlays();
	}

	// blit back buffer to front buffer
	this->window_ptr->display();

	return;
}	// end Game::render()


void Game::initPlants() {
	std::vector<int> position_x_vec = {
		32 + 64,
		32 + 128 + 32 + 64,
		32 + 128 + 32 + 128 + 32 + 64,
		int(SCREEN_WIDTH) - 32 - 128 - 32 - 128 - 32 - 64,
		int(SCREEN_WIDTH) - 32 - 128 - 32 - 64,
		int(SCREEN_WIDTH) - 32 - 64
	};
	for (int i = 0; i < position_x_vec.size(); i++) {
		this->plant_ptr_vec.push_back(
			new Plant(
				position_x_vec[i],	// position_x
				SCREEN_HEIGHT - 64,	// position_y
				1,
				this->window_ptr,
				&(this->assets)
			)
		);
	}
} // end Game::initPlants()


void Game::clearPlants(void) {
	/*
	 *	Method to clear plant_ptr_vec
	 */

	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
 		delete this->plant_ptr_vec[i];
 	}
 	this->plant_ptr_vec.clear();

	return;
}	// end Game::clearPlants()


void Game::run(void) {
	/*
	 *	Method to run instance of Game
	 */

	// stream out seconds per frame
	std::cout << "Running game (frames per second: " <<
		FRAMES_PER_SECOND << ") ...\n" << std::endl;

	// start music_player
	this->music_player.play();

	// render title screen (blocks until complete)
	this->renderTitle();

	// while window is open (i.e., game is alive) ...
	while (this->window_ptr->isOpen()) {
		// update time elapsed since run()
		this->time_since_run_s = this->clock.getElapsedTime().asSeconds();

		// if "clock tick" ...
		if (
			this->time_since_run_s >= (this->frame + 1) * SECONDS_PER_FRAME
		) {
			// compute dt, update frame time
			this->dt_s = this->time_since_run_s - this->frame_time_s;
			this->frame_time_s = this->time_since_run_s;

			// handle events, update, transitions, and render
			if (this->fade_alpha == 0) {
				this->handleEvents();
			}
			this->update();
			this->render();

			// increment frame count
			this->frame++;
		}
	}

	return;
}	// end Game::run()


void Game::setHourDay(double hour_of_day) {
	/*
	 *	Setter for hour_of_day attribute
	 */

	this->hour_of_day = hour_of_day;
	return;
}	// end Game::setHourDay()


void Game::setPoweredFlag(bool powered_flag) {
	/*
	 *	Setter for powered_flag attribute
	 */

	this->powered_flag = powered_flag;
	return;
}	// end Game::setPoweredFlag()


void Game::pushPlant(int i, Plant* plant_ptr) {
	/*
	 *	Method to push Plant object into position i of plant_ptr_vec attribute
	 */

	// bounds enforcement on i
	if (i < 0) {
		i == 0;
	}
	else if (i >= this->plant_ptr_vec.size()) {
		i = this->plant_ptr_vec.size() - 1;
	}

	// create Plant
	plant_ptr->setPositionX(this->plant_ptr_vec[i]->getPositionX());
	plant_ptr->setPositionY(this->plant_ptr_vec[i]->getPositionY());

	// clear position
	try {
		delete this->plant_ptr_vec[i];
	}
	catch (...) {
		// do nothing!
	}

	// push into plant_ptr_vec
	this->plant_ptr_vec[i] = plant_ptr;

	return;
}	// end Game::pushPlant()


bool Game::transition(void) {
	/*
	 *	Method to handle smooth transitions between time steps (or rounds)
	 */

	// set return flag
	bool ret_flag = false;

	// while not clock tick, wait
	while (this->time_since_run_s < (this->frame + 1) * SECONDS_PER_FRAME) {
		this->time_since_run_s = this->clock.getElapsedTime().asSeconds();
	}

	// check if rolling marbles finished
	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
		int texture_key = this->plant_ptr_vec[i]->getTextureIndex();

		if (texture_key < 0) {
			continue;
		}

		if (!this->plant_ptr_vec[i]->marblesFinished()) {
			ret_flag = true;
			break;
		}
	}

	// advance time
	if (this->hour_of_day < this->next_hour_of_day) {
		this->hour_of_day += 0.3 * SECONDS_PER_FRAME;
		ret_flag = true;
	}
	else if (this->hour_of_day >= this->next_hour_of_day) {
		this->hour_of_day = this->next_hour_of_day;
	}
	/*
	if (this->hour_of_day >= 24) {
		this->assets.getSound("clock chime")->play();
		this->phase_manager.setPhase(5);
		this->draw_energy_overlay = true;
	}
	*/

	// advance wind speed ratio
	double d_wind = this->next_wind_speed_ratio - this->wind_speed_ratio;
	if (fabs(d_wind) > 1e-6) {
		/*
		std::cout << this->wind_speed_ratio << " : " <<
			this->next_wind_speed_ratio << std::endl;
		*/
		if (d_wind > 0.005) {
			this->wind_speed_ratio += 0.005;
		}
		else if (d_wind < -0.005) {
			this->wind_speed_ratio -= 0.005;
		}
		else {
			this->wind_speed_ratio += d_wind;
		}
		ret_flag = true;
	}

	// advance cloud cover ratio
	double d_clouds = this->next_cloud_cover_ratio - this->cloud_cover_ratio;
	if (fabs(d_clouds) > 1e-6) {
		/*
		std::cout << this->cloud_cover_ratio << " : " <<
			this->next_cloud_cover_ratio << std::endl;
		*/
		if (d_clouds > 0.005) {
			this->cloud_cover_ratio += 0.005;
		}
		else if (d_clouds < -0.005) {
			this->cloud_cover_ratio -= 0.005;
		}
		else {
			this->cloud_cover_ratio += d_clouds;
		}
		ret_flag = true;
	}

	// advance sea state (waves)
	if (this->wave_res_s != this->next_wave_res_s) {
		this->wave_res_s = this->next_wave_res_s;
	}

	// advance smog ratio
	double d_smog = this->next_smog_ratio - this->smog_ratio;
	if (fabs(d_smog) > 1e-6) {
		/*
		std::cout << this->smog_ratio << " : " <<
			this->next_smog_ratio << std::endl;
		*/
		if (d_smog > 0.005) {
			this->smog_ratio += 0.005;
		}
		else if (d_smog < -0.005) {
			this->smog_ratio -= 0.005;
		}
		else {
			this->smog_ratio += d_smog;
		}
		ret_flag = true;
	}

	// handle select closing events, update, and render
	sf::Event event;
	while (this->window_ptr->pollEvent(event))
	{
		switch (event.type) {
			case (sf::Event::Closed):	// receive "close window" signal
				this->window_ptr->close();
				ret_flag = false;
				break;

			case (sf::Event::KeyPressed):	// key is pressed
				if (event.key.code == sf::Keyboard::Escape) {
					//this->window_ptr->close();
					if (this->phase_manager.getQuittingRound()) {
						this->phase_manager.setQuittingRound(false);
						this->assets.getSound("P key")->play();
					}
					else{
						// toggle quitting the game
						if (this->phase_manager.getQuittingGame()) {
							this->phase_manager.setQuittingGame(false);
							this->assets.getSound("P key")->play();
						}
						else{
							this->phase_manager.setQuittingGame(true);
							// also disable quitting round overlay
							this->phase_manager.setQuittingRound(false);
							this->assets.getSound("P key")->play();
						}
					}
					ret_flag = false;
				}
				else if (event.key.code == sf::Keyboard::Space) {	// skip
					this->hour_of_day = this->next_hour_of_day;
					this->wind_speed_ratio = this->next_wind_speed_ratio;
					this->cloud_cover_ratio = this->next_cloud_cover_ratio;
					this->smog_ratio = this->next_smog_ratio;

					ret_flag = false;
				}
				break;

			default:
				// do nothing!
				break;
		}
	}

	// render
	this->render();
	this->frame++;

	// reset phase manager index, check time value
	if (!ret_flag) {
		this->phase_manager.setIndex(0);
		if (this->hour_of_day >= 24) {
			this->assets.getSound("clock chime")->play();
			this->phase_manager.setPhase(5);
			this->draw_energy_overlay = true;
		}
	}

	return ret_flag;
}	// end Game::transition()


void Game::update(void) {
	/*
	 *	Method to update the game state
	 */

	 /*

	// WASD movement
	if (key_vec[sf::Keyboard::W]) {
		std::cout << "W" << std::endl;
	}
	if (key_vec[sf::Keyboard::A]) {
		std::cout << "A" << std::endl;
	}
	if (key_vec[sf::Keyboard::S]) {
		std::cout << "S" << std::endl;
	}
	if (key_vec[sf::Keyboard::D]) {
		std::cout << "D" << std::endl;
	}

	*/

	return;
}	// end Game::update()


void Game::plantInfo(int index){
	std::string feed_str = "";
	switch (index) {
		case (0):	// Coal
			feed_str = TEXT_COAL;
			break;

		case (1):	// Combined
			feed_str = TEXT_COMBINED;
			break;

		case (2):	// Fission
			feed_str = TEXT_FISSION;
			break;

		case (3):	// Geothermal
			feed_str = TEXT_GEOTHERMAL;
			break;

		case (4):	// Hydro
			feed_str = TEXT_HYDRO;
			break;

		case (5):	// Peaker
			feed_str = TEXT_PEAKER;
			break;

		case (6):	// Solar
			feed_str = TEXT_SOLAR;
			break;

		case (7):	// Storage
			feed_str = TEXT_STORAGE;
			break;

		case (8):	// Tidal
			feed_str = TEXT_TIDAL;
			break;

		case (9):	// Wave
			feed_str = TEXT_WAVE;
			break;

		case (10):	// Wind
			feed_str = TEXT_WIND;
			break;

		default:
			// do nothing!
			break;
	}

	if (!feed_str.empty()) {
		this->text_box.makeBox(
			std::string(feed_str),
			"bold",
			0.02 * SCREEN_HEIGHT,
			SCREEN_WIDTH / 8,
			SCREEN_HEIGHT / 8,
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 3
		);
	}
} // end Game::plantInfo(int)


void Game::reset(void){
	this->phase_manager.reset();
	this->pictorial_tutorial.reset();
	this->dice_roll.reset();
	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
		this->phase_manager.setGeothermalPresent(i,false);
	}

	/*
	// for this part, just copy/paste the attribute block from the Game constructor
	this->setHourDay(0);
	this->next_hour_of_day = 0;
	*/
	this->powered_flag = true;
	this->draw_energy_overlay = false;
	this->draw_forecast_overlay = false;
	this->can_defer_load = true;
	this->current_energy_demand_GWh = 0;
	this->excess_dispatch_GWh = 0;
	this->coal_marbles = 0;
	this->rolls_rem_corr = 0;
	this->combined_marbles = 0;
	this->peaker_marbles = 0;
	this->hour_of_day = 0;
	this->next_hour_of_day = 0;
	this->cloud_cover_ratio = 0;
	this->next_cloud_cover_ratio = 0;
	this->wind_speed_ratio = 0;
	this->next_wind_speed_ratio = 0;
	this->smog_ratio = 0;
	this->next_smog_ratio = 0;
	this->wave_res_s = 0;
	this->next_wave_res_s = 0;
	this->score = 0;
	this->tidal_idx_offset = round(23 * (double)rand() / RAND_MAX);
	this->points_str = "";

	this->forecast_map["demand GWh"] = 0;
	this->forecast_map["solar forecast GWh"] = 0;
	this->forecast_map["solar forecast error GWh"] = 0;
	this->forecast_map["tidal forecast GWh"] = 0;
	this->forecast_map["tidal forecast error GWh"] = 0;
	this->forecast_map["wave forecast GWh"] = 0;
	this->forecast_map["wave forecast error GWh"] = 0;
	this->forecast_map["wind forecast GWh"] = 0;
	this->forecast_map["wind forecast error GWh"] = 0;

	this->energy_demand_GWh_vec = {
		13, 13, 13, 15, 16, 18,
		19, 20, 20, 20, 19, 18,
		18, 18, 19, 21, 22, 21,
		20, 18, 17, 15, 14
	};

	this->actual_energy_demand_GWh_vec.clear();

	this->clearPlants();
	this->initPlants();

	sf::SoundSource::Status music_status = this->music_player.getStatus();
	if (music_status == sf::SoundSource::Status::Paused) {
		this->music_player.play();
	}
	else if (music_status == sf::SoundSource::Status::Stopped) {
		this->music_player.nextTrack();
		this->music_player.play();
	}
} // end Game::reset


void Game::deferLoad(void) {
	/*
	 *	Method to defer load (blocks main thread!)
	 */

	// make sure Storage is actually built
	bool skip_flag = true;
	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
		if (
			this->plant_ptr_vec[i]->getTextureIndex() == 7	// Storage
		) {
			skip_flag = false;
			break;
		}
	}
	if (skip_flag) {
		return;
	}

	// init local varibles
	double min_deferral_hour = this->hour_of_day + 1;
	double target_deferral_hour = min_deferral_hour;
	double min_deferral_load_GW = 1;
	double max_deferral_load_GW = min_deferral_load_GW;
	double target_deferral_load_GW = min_deferral_load_GW;

	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
		if (
			this->plant_ptr_vec[i]->getTextureIndex() == 7	// Storage
		) {
			max_deferral_load_GW = this->plant_ptr_vec[i]->getCapacityGW();
		}
	}
	if (max_deferral_load_GW > this->current_energy_demand_GWh) {
		max_deferral_load_GW = this->current_energy_demand_GWh;
	}

	std::string defer_str = "";
	sf::Text defer_txt(
		defer_str,
		*(this->assets.getFont("bold")),
		0.02 * SCREEN_HEIGHT
	);

	sf::RectangleShape backing_rect;

	// blocking while loop
	bool defer_finished = false;
	sf::Event event;
	while (!defer_finished) {
		// handle events
		while (this->window_ptr->pollEvent(event)) {
			switch (event.type) {
				case (sf::Event::Closed):	// receive "close window" signal
					defer_finished = true;
					this->window_ptr->close();
					break;

				case (sf::Event::KeyPressed):	// key is pressed
					switch (event.key.code) {
						case (sf::Keyboard::Escape):
							// cancel deferral
							this->can_defer_load = true;
							defer_finished = true;
							break;

						case (sf::Keyboard::W):
							// increment load to defer
							target_deferral_load_GW += 1;
							if (
								target_deferral_load_GW > max_deferral_load_GW
							) {
								target_deferral_load_GW = max_deferral_load_GW;
							}
							break;

						case (sf::Keyboard::A):
							// decrement time to defer to
							target_deferral_hour -= 1;
							if (
								target_deferral_hour < min_deferral_hour
							) {
								target_deferral_hour = min_deferral_hour;
							}
							break;

						case (sf::Keyboard::S):
							// decrement load to defer
							target_deferral_load_GW -= 1;
							if (
								target_deferral_load_GW < min_deferral_load_GW
							) {
								target_deferral_load_GW = min_deferral_load_GW;
							}
							break;

						case (sf::Keyboard::D):
							// increment time to defer to
							target_deferral_hour += 1;
							if (
								target_deferral_hour > 23
							) {
								target_deferral_hour = 23;
							}
							break;

						case (sf::Keyboard::Space):
							// commit deferral
							this->current_energy_demand_GWh -= int(round(target_deferral_load_GW));
							this->actual_energy_demand_GWh_vec[int(this->hour_of_day)] = this->current_energy_demand_GWh;
							this->energy_demand_GWh_vec[int(target_deferral_hour)] += int(round(target_deferral_load_GW));
							this->getForecast();
							defer_finished = true;
							break;

						default:
							// do nothing!
							break;
					}
					break;

				default:
					// do nothing!
					break;
			}
		}

		// update clock, render
		this->time_since_run_s = this->clock.getElapsedTime().asSeconds();

		// if "clock tick" ...
		if (
			this->time_since_run_s >= (this->frame + 1) * SECONDS_PER_FRAME
		) {
			// compute dt, update frame time
			this->dt_s = this->time_since_run_s - this->frame_time_s;
			this->frame_time_s = this->time_since_run_s;

			// clear window
			this->window_ptr->clear();

			// render layers

			//	1. sky disk
			this->sky_disk.drawFrame(this->hour_of_day);

			//	2. overcast and clouds
			this->overcast_clouds.drawFrame(
				this->wind_speed_ratio,
				this->cloud_cover_ratio,
				this->hour_of_day
			);

			//	3. smog dome (circ, behind city)
			sf::CircleShape smog_circ;
			smog_circ.setFillColor(
				sf::Color(
					SMOG_COLOUR.r,
					SMOG_COLOUR.g,
					SMOG_COLOUR.b,
					this->smog_ratio * 200
				)
			);
			double radius = 1.1 * SCREEN_HEIGHT / 3;
			smog_circ.setRadius(radius);
			smog_circ.setOrigin(radius, radius);
			smog_circ.setPosition(
				sf::Vector2f(
					SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2
				)
			);
			this->window_ptr->draw(smog_circ);

			//	4. foreground + Plinko City
			this->foreground.drawFrame(this->powered_flag, this->hour_of_day);

			//	5. wind sock
			this->wind_sock.drawFrame(this->wind_speed_ratio, this->hour_of_day);

			//	6. plant ojects
			for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
				this->plant_ptr_vec[i]->drawMarbles();
				this->plant_ptr_vec[i]->drawSteam(this->wind_speed_ratio);
				this->plant_ptr_vec[i]->drawSmoke(this->wind_speed_ratio);
				this->plant_ptr_vec[i]->drawFrame(
					i == this->phase_manager.getIndex(),
					this->phase_manager.getPhase() == 1
				);
			}

			//	7. backing_rect and defer_txt
			defer_str = "LOAD DEFERRAL\n\n";
			defer_str += "Deferring: " +
				std::to_string(int(target_deferral_load_GW)) + " GW\n";
			if (target_deferral_hour < 10) {
				defer_str += "Deferring to: 0" +
					std::to_string(int(target_deferral_hour)) + ":00\n\n";
			}
			else {
				defer_str += "Deferring to: " +
					std::to_string(int(target_deferral_hour)) + ":00\n\n";
			}
			defer_str += "[W] / [S]: change load deferred\n";
			defer_str += "[A] / [D]: change time deferred to\n";
			defer_str += "[Spacebar]: accept\n";
			defer_str += "[ESC]: cancel";

			defer_txt.setString(defer_str);
			defer_txt.setOrigin(
				defer_txt.getLocalBounds().width / 2,
				defer_txt.getLocalBounds().height / 2
			);
			defer_txt.setPosition(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2
			);

			backing_rect.setFillColor(TEXT_BOX_BACK_COLOUR);
			backing_rect.setOutlineColor(TEXT_BOX_OUTLINE_COLOUR);
			backing_rect.setOutlineThickness(TEXT_BOX_OUTLINE_THICKNESS);
			backing_rect.setSize(
				sf::Vector2f(
					1.05 * defer_txt.getLocalBounds().width,
					1.1 * defer_txt.getLocalBounds().height
				)
			);
			backing_rect.setOrigin(
				backing_rect.getLocalBounds().width / 2,
				backing_rect.getLocalBounds().height / 2
			);
			backing_rect.setPosition(
				SCREEN_WIDTH / 2 + 8,
				SCREEN_HEIGHT / 2 + 16
			);

			this->window_ptr->draw(backing_rect);
			this->window_ptr->draw(defer_txt);

			//	8. overlays
			this->renderOverlays();

			// flip
			this->window_ptr->display();

			// increment frame count
			this->frame++;
		}
	}

	return;
}	// end Game::deferLoad()


double Game::generateWindRatio(void) {
	/*
	 *	Method to generate wind ratio (simple Markov process)
	 */

	double inc_prob = 1 - this->wind_speed_ratio;
	double roll = (double)rand() / RAND_MAX;
	double wind_speed_ratio = 0;

	if (roll <= inc_prob) {
		wind_speed_ratio = this->wind_speed_ratio + 0.5 * (double)rand() / RAND_MAX;
	}
	else {
		wind_speed_ratio = this->wind_speed_ratio - 0.5 * (double)rand() / RAND_MAX;
	}

	if (wind_speed_ratio > 1) {
		wind_speed_ratio = 1;
	}
	else if (wind_speed_ratio < 0) {
		wind_speed_ratio = 0;
	}

	return wind_speed_ratio;
}	// end Game::generateWindRatio()


double Game::generateCloudRatio(void) {
	/*
	 *	Method to generate cloud ratio (simple Markov process)
	 */

	double inc_prob = 1 - this->cloud_cover_ratio;
	double roll = (double)rand() / RAND_MAX;
	double cloud_cover_ratio = 0;

	if (roll <= inc_prob) {
		cloud_cover_ratio = this->cloud_cover_ratio + 0.5 * (double)rand() / RAND_MAX;
	}
	else {
		cloud_cover_ratio = this->cloud_cover_ratio - 0.5 * (double)rand() / RAND_MAX;
	}

	if (cloud_cover_ratio > 1) {
		cloud_cover_ratio = 1;
	}
	else if (cloud_cover_ratio < 0) {
		cloud_cover_ratio = 0;
	}

	return cloud_cover_ratio;
}	// end Game::generateCloudRatio()


double Game::generateSolarResource(void) {
	/*
	 *	Method to generate solar resource
	 *	(product of cloud cover and time of day)
	 */

	double solar_res_kWm2 = 0;

	if (this->hour_of_day > 5.5 && this->hour_of_day < 17.5) {
		if (this->hour_of_day <= 10) {
			solar_res_kWm2 = (2.0 / 9.0) * this->hour_of_day - (11.0 / 9.0);
		}
		else if (this->hour_of_day >= 14) {
			solar_res_kWm2 = (-2.0 / 7.0) * this->hour_of_day + 5.0;
		}
		else {
			solar_res_kWm2 = 1;
		}
		solar_res_kWm2 *= (1 - this->cloud_cover_ratio) * (1 - this->smog_ratio);
	}

	return solar_res_kWm2;
}	// end Game::generateSolarResource()


double Game::generateWaveResource(void) {
	/*
	 *	Method to generate wave energy period (simple Markov process)
	 */

	double norm_res = (this->wave_res_s - 5.75) / (15 - 5.75);
	double inc_prob = 1 - norm_res;
	double next_norm_res = 0;
	double next_res = 0;

	double roll = (double)rand() / RAND_MAX;
	if (roll <= inc_prob) {
		next_norm_res = norm_res + 0.1 * (double)rand() / RAND_MAX;
	}
	else {
		next_norm_res = norm_res - 0.1 * (double)rand() / RAND_MAX;
	}

	if (next_norm_res > 1) {
		next_norm_res = 1;
	}
	else if (next_norm_res < 0) {
		next_norm_res = 0;
	}
	next_res = (15 - 5.75) * next_norm_res + 5.75;

	return next_res;
}	// end Game::generateWaveResource()


void Game::getForecast(void) {
	/*
	 *	Method to get forecast values for renewables (simple Monte Carlo)
	 */

	 this->forecast_map["demand GWh"] = this->energy_demand_GWh_vec[
 		(int(this->hour_of_day) + 1) % 23
 	];

	int texture_key = 0;
	int n_trials = 1024;
	double mean_prod_GWh = 0;
	double max_abs_error_GWh = 0;
	std::vector<double> forecast_GWh_vec (n_trials, 0);
	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
		texture_key = this->plant_ptr_vec[i]->getTextureIndex();

		switch (texture_key) {
			case (6):	// Solar
				mean_prod_GWh = 0;
				max_abs_error_GWh = 0;
				{
					// init
					double cloud_cover_ratio = 0;
					double solar_res_kWm2 = 0;
					double solar_prod_GWh = 0;

					// Monte Carlo
					for (int j = 0; j < n_trials; j++) {
						// roll cloud cover ratio
						cloud_cover_ratio = this->generateCloudRatio();

						// compute solar resource
						if (this->hour_of_day > 5.5 && this->hour_of_day < 17.5) {
							if (this->hour_of_day <= 10) {
								solar_res_kWm2 = (2.0 / 9.0) * this->hour_of_day - (11.0 / 9.0);
							}
							else if (this->hour_of_day >= 14) {
								solar_res_kWm2 = (-2.0 / 7.0) * this->hour_of_day + 5.0;
							}
							else {
								solar_res_kWm2 = 1;
							}
							solar_res_kWm2 *= (1 - cloud_cover_ratio) * (1 - this->smog_ratio);
						}

						// compute solar production
						solar_prod_GWh = this->plant_ptr_vec[i]->getCapacityGW() *
							solar_res_kWm2;
						if (solar_prod_GWh > this->plant_ptr_vec[i]->getCapacityGW()) {
							solar_prod_GWh = this->plant_ptr_vec[i]->getCapacityGW();
						}

						// update mean_prod_GWh
						mean_prod_GWh += solar_prod_GWh;

						// write to forecast_GWh_vec
						forecast_GWh_vec[j] = solar_prod_GWh;
					}

					// compute mean_prod_GWh
					mean_prod_GWh = mean_prod_GWh / double(n_trials);

					// compute max_abs_error_GWh
					for (int j = 0; j < n_trials; j++) {
						if (
							abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							) > max_abs_error_GWh
						) {
							max_abs_error_GWh = abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							);
						}
					}

					// write to forecast_map
					mean_prod_GWh = round(mean_prod_GWh);
					max_abs_error_GWh = ceil(max_abs_error_GWh);
					if (max_abs_error_GWh > mean_prod_GWh) {
						max_abs_error_GWh = mean_prod_GWh;
					}
					this->forecast_map["solar forecast GWh"] = mean_prod_GWh;
					this->forecast_map["solar forecast error GWh"] = max_abs_error_GWh;
				}
				break;

			case (8):	// Tidal
				mean_prod_GWh = 0;
				max_abs_error_GWh = 0;
				{
					// init
					double tidal_res_ms = 0;
					double design_speed_ms = this->plant_ptr_vec[i]->getDesignSpeed();
					double turb_speed = 0;
					double tidal_prod = 0;
					double tidal_prod_GWh = 0;

					// Monte Carlo
					for (int j = 0; j < n_trials; j++) {
						// roll tidal res
						tidal_res_ms = this->tidal_res_ms_vec[
							(
								int(this->hour_of_day) + 1 +
								this->tidal_idx_offset
							) % 23
						];
						tidal_res_ms *= 1 + (0.1 * ((double)rand() / RAND_MAX) - 0.05);
						if (tidal_res_ms < 0) {
							tidal_res_ms = 0;
						}
						else if (tidal_res_ms > 1) {
							tidal_res_ms = 1;
						}

						// compute tidal production
						if (tidal_res_ms > 0) {
							turb_speed = (tidal_res_ms - design_speed_ms) /
								design_speed_ms;

							// look-up on dimensionless performance curve, get dimensionless production [ ]
							 if (turb_speed < -0.71 || turb_speed > 0.65) {
								 tidal_prod = 0;
							 } else if (turb_speed >= -0.71 && turb_speed <= 0) {
								 tidal_prod = 1.69215 * exp(1.25909 * turb_speed) - 0.69215;
							 } else {
								 tidal_prod = 1;
							 }
						}
						else {
							tidal_prod = 0;
						}
						tidal_prod_GWh = this->plant_ptr_vec[i]->getCapacityGW() * tidal_prod;

						// update mean_prod_GWh
						mean_prod_GWh += tidal_prod_GWh;

						// write to forecast_GWh_vec
						forecast_GWh_vec[j] = tidal_prod_GWh;
					}

					// compute mean_prod_GWh
					mean_prod_GWh = mean_prod_GWh / double(n_trials);

					// compute max_abs_error_GWh
					for (int j = 0; j < n_trials; j++) {
						if (
							abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							) > max_abs_error_GWh
						) {
							max_abs_error_GWh = abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							);
						}
					}

					// write to forecast_map
					mean_prod_GWh = round(mean_prod_GWh);
					max_abs_error_GWh = ceil(max_abs_error_GWh);
					if (max_abs_error_GWh > mean_prod_GWh) {
						max_abs_error_GWh = mean_prod_GWh;
					}
					this->forecast_map["tidal forecast GWh"] = mean_prod_GWh;
					this->forecast_map["tidal forecast error GWh"] = max_abs_error_GWh;
				}
				break;

			case (9):	// Wave
				mean_prod_GWh = 0;
				max_abs_error_GWh = 0;
				{
					// init
					double wave_res_s = 0;
					double wave_res_m = 0;
					double design_period_s = this->plant_ptr_vec[i]->getDesignPeriod();
					double wave_prod = 0;
					double wave_prod_GWh = 0;
					double sigma = 0.028;	// Rayleigh scale parameter (mode of dist)
					double roll = 0;
					double scalar = 0;

					// Monte Carlo
					for (int j = 0; j < n_trials; j++) {
						// roll wave resource
						wave_res_s = this->generateWaveResource();

						// wave production
						// generate wave_res_m from Rayleigh distribution
						roll = (double)rand() / RAND_MAX;
						if (roll == 1) {
							roll = 0.999999;
						}
						scalar = sigma * sqrt(2 * log(1 / (1 - roll)));
						wave_res_m = scalar * pow(wave_res_s, 2);
						if (wave_res_m > 0.2184 * pow(wave_res_s, 2)) {
							wave_res_m = 0.2 * pow(wave_res_s, 2);
						}

						if (wave_res_m > 0) {
							wave_prod = 0.289 * wave_res_m -
								0.00111 * pow(wave_res_m, 2) * wave_res_s -
								0.0169 * wave_res_s;
							if (wave_prod <= 0) {
								wave_prod = 0;
							}
							else if (wave_prod >= 1) {
								wave_prod = 1;
							}
						}
						else {
							wave_prod = 0;
						}
						wave_prod_GWh = this->plant_ptr_vec[i]->getCapacityGW() * wave_prod;

						// update mean_prod_GWh
						mean_prod_GWh += wave_prod_GWh;

						// write to forecast_GWh_vec
						forecast_GWh_vec[j] = wave_prod_GWh;
					}

					// compute mean_prod_GWh
					mean_prod_GWh = mean_prod_GWh / double(n_trials);

					// compute max_abs_error_GWh
					for (int j = 0; j < n_trials; j++) {
						if (
							abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							) > max_abs_error_GWh
						) {
							max_abs_error_GWh = abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							);
						}
					}

					// write to forecast_map
					mean_prod_GWh = round(mean_prod_GWh);
					max_abs_error_GWh = ceil(max_abs_error_GWh);
					if (max_abs_error_GWh > mean_prod_GWh) {
						max_abs_error_GWh = mean_prod_GWh;
					}
					this->forecast_map["wave forecast GWh"] = mean_prod_GWh;
					this->forecast_map["wave forecast error GWh"] = max_abs_error_GWh;
				}
				break;

			case (10):	// Wind
				mean_prod_GWh = 0;
				max_abs_error_GWh = 0;
				{
					// init
					double wind_speed_ratio = 0;
					double design_speed_ms = this->plant_ptr_vec[i]->getDesignSpeed();
					double turb_speed = 0;
					double wind_prod = 0;
					double wind_prod_GWh = 0;

					// Monte Carlo
					for (int j = 0; j < n_trials; j++) {
						// roll wind speed ratio
						wind_speed_ratio = this->generateWindRatio();

						// compute wind production
						if (wind_speed_ratio > 0) {
							turb_speed = (wind_speed_ratio - design_speed_ms) /
								design_speed_ms;

							// look-up on dimensionless performance curve, get dimensionless production [ ]
							if (turb_speed < -0.76 || turb_speed > 0.68) {
								wind_prod = 0;
							} else if (turb_speed >= -0.76 && turb_speed <= 0) {
								wind_prod = 1.03273 * exp(-5.97588 * pow(turb_speed, 2)) -
									0.03273;
							} else {
								wind_prod = 0.16154 * exp(-9.30254 * pow(turb_speed, 2)) +
									0.83846;
							}
						}
						else {
							wind_prod = 0;
						}
						if (wind_prod > 1) {
							wind_prod = 1;
						}
						wind_prod_GWh = this->plant_ptr_vec[i]->getCapacityGW() * wind_prod;

						// update mean_prod_GWh
						mean_prod_GWh += wind_prod_GWh;

						// write to forecast_GWh_vec
						forecast_GWh_vec[j] = wind_prod_GWh;
					}

					// compute mean_prod_GWh
					mean_prod_GWh = mean_prod_GWh / double(n_trials);

					// compute max_abs_error_GWh
					for (int j = 0; j < n_trials; j++) {
						if (
							abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							) > max_abs_error_GWh
						) {
							max_abs_error_GWh = abs(
								forecast_GWh_vec[j] - mean_prod_GWh
							);
						}
					}

					// write to forecast_map
					mean_prod_GWh = round(mean_prod_GWh);
					max_abs_error_GWh = ceil(max_abs_error_GWh);
					if (max_abs_error_GWh > mean_prod_GWh) {
						max_abs_error_GWh = mean_prod_GWh;
					}
					this->forecast_map["wind forecast GWh"] = mean_prod_GWh;
					this->forecast_map["wind forecast error GWh"] = max_abs_error_GWh;
				}
				break;

			default:
				// do nothing!
				break;
		}
	}

	return;
}	// end Game::getForecast()


void Game::test1(void) {
	/*
	 *	Method to test animations
	 */

	// add Plants to plant_ptr_vec
	/*
	this->clearPlants();

	Plant* test_coal = new Coal(0, 0, 1, this->window_ptr, &(this->assets));
	test_coal->setPositionX(32);
	test_coal->setPositionY(SCREEN_HEIGHT - 128 - 32);
	test_coal->setRunning(true);
	this->plant_ptr_vec.push_back(test_coal);

	Plant* test_combined = new Combined(0, 0, 1, this->window_ptr, &(this->assets));
	test_combined->setPositionX(32 + 256);
	test_combined->setPositionY(SCREEN_HEIGHT - 128 - 32);
	test_combined->setRunning(true);
	this->plant_ptr_vec.push_back(test_combined);

	Plant* test_fission = new Fission(0, 0, 1, this->window_ptr, &(this->assets));
	test_fission->setPositionX(32 + 2 * 256);
	test_fission->setPositionY(SCREEN_HEIGHT - 128 - 32);
	test_fission->setRunning(true);
	this->plant_ptr_vec.push_back(test_fission);

	Plant* test_geothermal = new Geothermal(0, 0, 1, this->window_ptr, &(this->assets));
	test_geothermal->setPositionX(32 + 3 * 256);
	test_geothermal->setPositionY(SCREEN_HEIGHT - 128 - 32);
	test_geothermal->setRunning(true);
	this->plant_ptr_vec.push_back(test_geothermal);

	Plant* test_peaker = new Peaker(0, 0, 1, this->window_ptr, &(this->assets));
	test_peaker->setPositionX(32 + 4 * 256);
	test_peaker->setPositionY(SCREEN_HEIGHT - 128 - 32);
	test_peaker->setRunning(true);
	this->plant_ptr_vec.push_back(test_peaker);

	Plant* test_hydro = new Hydro(0, 0, 1, this->window_ptr, &(this->assets));
	test_hydro->setPositionX(32);
	test_hydro->setPositionY(SCREEN_HEIGHT - 128 - 64 - 256);
	test_hydro->setEnergyCapacity(100);
	test_hydro->setCharge(100);
	test_hydro->setRunning(true);
	this->plant_ptr_vec.push_back(test_hydro);

	Plant* test_solar = new Solar(0, 0, 1, this->window_ptr, &(this->assets));
	test_solar->setPositionX(32 + 256);
	test_solar->setPositionY(SCREEN_HEIGHT - 128 - 64 - 256);
	test_solar->setPowerCapacity(5);
	test_solar->getProduction(0.5);
	this->plant_ptr_vec.push_back(test_solar);

	Plant* test_storage = new Storage(0, 0, 1, this->window_ptr, &(this->assets));
	test_storage->setPositionX(32 + 2 * 256);
	test_storage->setPositionY(SCREEN_HEIGHT - 128 - 64 - 256);
	test_storage->setEnergyCapacity(5);
	test_storage->setCharge(3);
	this->plant_ptr_vec.push_back(test_storage);

	Plant* test_tidal = new Tidal(0, 0, 1, this->window_ptr, &(this->assets));
	test_tidal->setPositionX(32 + 3 * 256);
	test_tidal->setPositionY(SCREEN_HEIGHT - 128 - 64 - 256);
	test_tidal->setPowerCapacity(5);
	test_tidal->getProduction(2);
	this->plant_ptr_vec.push_back(test_tidal);

	Plant* test_wind = new Wind(0, 0, 1, this->window_ptr, &(this->assets));
	test_wind->setPositionX(32 + 4 * 256);
	test_wind->setPositionY(SCREEN_HEIGHT - 128 - 64 - 256);
	test_wind->setPowerCapacity(5);
	test_wind->getProduction(7.5);
	this->plant_ptr_vec.push_back(test_wind);

	Plant* test_wave = new Wave(0, 0, 1, this->window_ptr, &(this->assets));
	test_wave->setPositionX(32);
	test_wave->setPositionY(SCREEN_HEIGHT - 128 - 64 - 512);
	test_wave->setPowerCapacity(5);
	test_wave->getProduction(8.5);
	this->plant_ptr_vec.push_back(test_wave);
	*/
	/*
	Plant* test_combined = new Combined(0, 0, 1, this->window_ptr, &(this->assets));
	test_combined->setRunning(true);
	this->pushPlant(0, test_combined);

	Plant* test_wind = new Wind(0, 0, 1, this->window_ptr, &(this->assets));
	test_wind->setPowerCapacity(5);
	test_wind->getProduction(7.5);
	this->pushPlant(1, test_wind);

	Plant* test_solar = new Solar(0, 0, 1, this->window_ptr, &(this->assets));
	test_solar->setPowerCapacity(5);
	test_solar->getProduction(0.5);
	this->pushPlant(2, test_solar);

	Plant* test_hydro = new Hydro(0, 0, 1, this->window_ptr, &(this->assets));
	test_hydro->setEnergyCapacity(100);
	test_hydro->setCharge(100);
	test_hydro->setRunning(true);
	this->pushPlant(3, test_hydro);
	*/
	///*
	//Plant* test_plant = new Coal(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Combined(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Fission(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Geothermal(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Hydro(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Peaker(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Solar(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Storage(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Tidal(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Wave(0, 0, 1, this->window_ptr, &(this->assets));
	//Plant* test_plant = new Wind(0, 0, 1, this->window_ptr, &(this->assets));

	Plant* test_coal = new Coal(0, 0, 1, this->window_ptr, &(this->assets));
	test_coal->setRunning(true);
	this->pushPlant(0, test_coal);

	Plant* test_fission = new Fission(0, 0, 1, this->window_ptr, &(this->assets));
	test_fission->setRunning(true);
	this->pushPlant(1, test_fission);

	Plant* test_storage = new Storage(0, 0, 1, this->window_ptr, &(this->assets));
	test_storage->setRunning(true);
	this->pushPlant(2, test_storage);

	Plant* test_combined = new Combined(0, 0, 1, this->window_ptr, &(this->assets));
	test_combined->setRunning(true);
	this->pushPlant(3, test_combined);

	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
		this->plant_ptr_vec[i]->setPowerCapacity(6);
		for (int j = 0; j < 6; j++) {
			this->plant_ptr_vec[i]->incMarbles();
		}
		//this->plant_ptr_vec[i]->commitMarbles(6);
		//this->plant_ptr_vec[i]->commitCharge(4);
		/*
		for (int j = 0; j < 3; j++) {
			this->plant_ptr_vec[i]->decMarbles();
		}
		*/
	}
	//*/

	// start music_player
	this->music_player.play();
	this->music_player.pause();
	this->music_paused = true;

	// ---- TESTING ---- //

	this->powered_flag = true;
	this->wind_speed_ratio = 0.5;
	this->cloud_cover_ratio = 0.5;

	bool test_flag_1 = false;
	bool test_flag_2 = false;

	// ---- END TESTING ---- //

	// while window is open (i.e., game is alive) ...
	int text_idx = 0;
	while (this->window_ptr->isOpen()) {
		// update time elapsed since run()
		this->time_since_run_s = this->clock.getElapsedTime().asSeconds();

		// if "clock tick" ...
		if (
			this->time_since_run_s >= (this->frame + 1) * SECONDS_PER_FRAME
		) {
			// compute dt, update frame time
			this->dt_s = this->time_since_run_s - this->frame_time_s;
			this->frame_time_s = this->time_since_run_s;

			// handle events, update, and render
			handleEvents();
			update();
			render();

			// ---- TESTING ---- //
			this->hour_of_day += 0.5 / FRAMES_PER_SECOND;
			if (this->hour_of_day >= 24) {
				this->hour_of_day = 0;
			}
			//std::cout << this->hour_of_day << std::endl;
			///*
			// ------------------------------------------------------------------------------------------------------------------------------
			// text box code
			//
			/*
			if (this->text_box.isDone()) {
				switch (text_idx) {
					case (0):
						this->text_box.makeBox(
							std::string(TEXT_COAL),
							"bold",
							0.02 * SCREEN_HEIGHT,
							SCREEN_WIDTH / 8,
							SCREEN_HEIGHT / 8,
							SCREEN_WIDTH / 2,
							SCREEN_HEIGHT / 3
						);
						break;

					default:
						// do nothing!
						break;
				}
				text_idx++;
			}
			*/
			//*/

			if (!test_flag_1 && fabs(this->time_since_run_s - 5) <= 1e-6) {
				for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
					this->plant_ptr_vec[i]->commitMarbles();
				}
				test_flag_1 = true;
			}

			if (!test_flag_2 && fabs(this->time_since_run_s - 10) <= 1e-6) {
				for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
					this->plant_ptr_vec[i]->commitCharge(3);
				}
				test_flag_2 = true;
			}

			// ---- END TESTING ---- //

			// increment frame count
			this->frame++;
		}
	}

	return;
}	// end Game::test1()


Game::~Game(void) {
	/*
	 *	Destructor for Game class
	 */

	// clean up plant_ptr_vec
	for (int i = 0; i < this->plant_ptr_vec.size(); i++) {
		delete this->plant_ptr_vec[i];
	}
	this->plant_ptr_vec.clear();

	// clean up RenderWindow (last!)
	this->window_ptr->clear();
	this->window_ptr->display();
	this->window_ptr->close();
	delete window_ptr;
	std::cout << "\nsf::RenderWindow object at " << this->window_ptr <<
		" destroyed." << std::endl;

	// stream out and return
	std::cout << "Game object at " << this << " destroyed.\n" << std::endl;
	return;
}	// end Game::~Game()
