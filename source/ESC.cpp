/*
 *	[ESC] Interactive core library - implementation
 *
 *	[ESC] Interactive
 *
 *	Anthony Truelove MASc, P.Eng.
 *	Spencer Funk BEng, EIT
 *
 *	Copyright 2022 (C) - [ESC] Interactive
 *	See license terms for details
 *
 *	This defines core [ESC] Interactive functionality, as a wrapper to various
 *	elements of SFML.
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


// -------- function implementations -------- //
sf::RenderWindow* getRenderWindowPtr(std::string title_str) {
	/*
	 *	Method to create a RenderWindow and return pointer to
	 */

	// get dektop display settings
	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
 	int DESKTOP_WIDTH = video_mode.width;
 	int DESKTOP_HEIGHT = video_mode.height;
	double width_ratio = DESKTOP_WIDTH / SCREEN_WIDTH;
	double height_ratio = DESKTOP_HEIGHT / SCREEN_HEIGHT;
	double min_ratio = width_ratio;
	if (height_ratio < width_ratio) {
		min_ratio = height_ratio;
	}

	// create RenderWindow, scale if DESKTOP_() < SCREEN_()
	sf::RenderWindow* window_ptr;
	sf::ContextSettings context_settings(0, 0, 0);	// third arg is anti-aliasing param {0, 2, 4, 8}
	if (min_ratio < 1) {
		window_ptr = new sf::RenderWindow(
	 		sf::VideoMode(min_ratio * SCREEN_WIDTH, min_ratio * SCREEN_HEIGHT),
	 		title_str,
	 		sf::Style::Default,
			context_settings
	 	);

		sf::View view;
		view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
		//view.zoom(1);
		window_ptr->setView(view);
	}
	else {
		window_ptr = new sf::RenderWindow(
	 		sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
	 		title_str,
	 		sf::Style::Default,
			context_settings
	 	);
	}

	// centre RenderWindow on screen
 	window_ptr->setVerticalSyncEnabled(true);
	double window_width = window_ptr->getSize().x;
	if (DESKTOP_WIDTH > window_width) {
		window_ptr->setPosition(
	 		sf::Vector2(
	 			int(round((DESKTOP_WIDTH - window_width) / 2.0)),
	 			0
	 		)
	 	);
	}

	std::cout << "sf::RenderWindow object created at " << window_ptr << ".\n" <<
		std::endl;

	return window_ptr;
}	// end getRenderWindowPtr()


sf::RenderWindow* playBrandAnimation(std::string input_str) {
	/*
	 *	Handles playing the [ESC] Interactive brand animation
	 */

	std::cout << input_str << std::endl << std::endl;

	// init
	bool animation_finished = false;
	bool sound_flag = false;
	int alpha = 255;
	int animation_state = 0;
	int frame = 0;
	int press_frame = 0;
	int pause_frame = 0;
	int red = 0;
	int green = 0;
	int blue = 0;
	int dcolour = 32;
	int advance_sum = 0;

	sf::Clock clock;
	sf::Event event;
	sf::Time time_elapsed = sf::Time::Zero;
	sf::RectangleShape rectangle(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	sf::RenderWindow* window_ptr = getRenderWindowPtr(
		"[ESC] Interactive - thanks for playing! =)"
	);

	// load brand assets
	sf::Font font;
	assert (font.loadFromFile("assets/ESC_brand/OpenSans-Bold.ttf"));
	sf::Text input_text(input_str, font, 16);
	input_text.setPosition(
		int(round(SCREEN_WIDTH - 16 - input_text.getLocalBounds().width)),
		int(round(SCREEN_HEIGHT - 16 - input_text.getLocalBounds().height))
	);

	sf::Texture ESC_large_txtr;
	ESC_large_txtr.setSmooth(true);
	assert (ESC_large_txtr.loadFromFile("assets/ESC_brand/ESC_key_109x90.png"));
	sf::Sprite ESC_large_sprite(ESC_large_txtr);

	sf::Texture ESC_small_txtr;
	ESC_small_txtr.setSmooth(true);
	assert (ESC_small_txtr.loadFromFile("assets/ESC_brand/ESC_key_98x81.png"));
	sf::Sprite ESC_small_sprite(ESC_small_txtr);

	sf::SoundBuffer key_press_buffer;
	assert (key_press_buffer.loadFromFile("assets/ESC_brand/key_press.ogg"));
	sf::Sound key_press_sound(key_press_buffer);

	// set window icon
	sf::Image window_icon;
	assert (window_icon.loadFromFile("assets/ESC_brand/ESC_key_109x90.png"));
	window_ptr->setIcon(
		window_icon.getSize().x,
		window_icon.getSize().y,
		window_icon.getPixelsPtr()
	);

	// define char_vec and text_ptr_vec
	int text_size = 75;
	std::vector<char> char_vec = {
		'I', 'N', 'T', 'E', 'R', 'A', 'C', 'T', 'I', 'V', 'E'
	};
	std::vector<std::vector<int>> colour_vec = {
		{0, 0, 0},
		{-120, 0, 0},
		{-240, 0, 0},
		{-360, 0, 0},
		{-480, 0, 0},
		{-600, 0, 0},
		{-720, 0, 0},
		{-840, 0, 0},
		{-960, 0, 0},
		{-1080, 0, 0},
		{-1200, 0, 0},
	};
	std::vector<int> colour_switch_vec (char_vec.size(), 0);
	std::vector<bool> colour_done_vec (char_vec.size(), false);
	std::vector<sf::Text> text_ptr_vec;

	// compute brand size
	int brand_width = 109;
	int brand_height = 90 + 15 + 75;
	for (int i = 1; i < char_vec.size(); i++) {
		brand_width += 4 +
			font.getGlyph(char_vec[i - 1], text_size, false).advance;
	}
	//std::cout << brand_width << " , " << brand_height << std::endl;

	// position brand
	int dx = int(round(0.80 * (SCREEN_WIDTH - brand_width) / 2.0));
	int dy = int(round(0.90 * (SCREEN_HEIGHT - brand_height) / 2.0));
	//std::cout << dx << " , " << dy << std::endl;
	ESC_large_sprite.setPosition(dx, dy);
	ESC_small_sprite.setPosition(dx + 5.5, dy + 4.5);

	for (int i = 0; i < char_vec.size(); i++) {
		text_ptr_vec.push_back(sf::Text(char_vec[i], font, text_size));
		if (i > 0) {
			text_ptr_vec[i].setPosition(
				text_ptr_vec[i - 1].getPosition().x + 4 +
				font.getGlyph(char_vec[i - 1], text_size, false).advance,
				dy + 15 + 75
			);
		}
		else {
			text_ptr_vec[i].setPosition(dx + 109, dy + 15 + 75);
		}
	}

	// cycle display a few times
	for (int i = 0; i < int(round(1 / SECONDS_PER_FRAME)); i++) {
		window_ptr->clear();
		window_ptr->display();
	}

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
					// draw large [ESC]
					window_ptr->draw(ESC_large_sprite);

					// draw fading rectangle
					rectangle.setFillColor(sf::Color(0, 0, 0, alpha));
					window_ptr->draw(rectangle);

					// update alpha
					alpha -= 2;
					if (alpha <= 0) {
						alpha = 0;
					}

					// conditionally increment animation_state
					if (time_elapsed.asSeconds() >= 2.25) {
						animation_state++;
					}
					break;

				case (1):	// key press, sound
					// draw small [ESC]
					window_ptr->draw(ESC_small_sprite);

					// play key press sound
					if (!sound_flag) {
						key_press_sound.play();
						sound_flag = true;
					}

					// increment press_frame
					press_frame++;

					// conditionally increment animation_state
					if (press_frame >= 6) {
						animation_state++;
					}
					break;

				case (2):	// key up, colour wave
					// draw large [ESC]
					window_ptr->draw(ESC_large_sprite);

					// colour wave
					for (int i = 0; i < text_ptr_vec.size(); i++) {
						if (!colour_done_vec[i]) {
							red = colour_vec[i][0];
							green = colour_vec[i][1];
							blue = colour_vec[i][2];

							if (red < 0) {
								red = 0;
							}

							text_ptr_vec[i].setFillColor(
								sf::Color(red, green, blue, 255)
							);

							switch (colour_switch_vec[i]) {
								case (0):	// red++
									colour_vec[i][0] += dcolour;
									if (colour_vec[i][0] >= 255) {
										colour_vec[i][0] = 255;
										colour_switch_vec[i]++;
									}
									break;

								case (1):	// red--, green++
									colour_vec[i][0] -= dcolour;
									colour_vec[i][1] += dcolour;
									if (
										colour_vec[i][0] <= 0 ||
										colour_vec[i][1] >= 255
									) {
										colour_vec[i][0] = 0;
										colour_vec[i][1] = 255;
										colour_switch_vec[i]++;
									}
									break;

								case (2):	// green--, blue++
									colour_vec[i][1] -= dcolour;
									colour_vec[i][2] += dcolour;
									if (
										colour_vec[i][1] <= 0 ||
										colour_vec[i][2] >= 255
									) {
										colour_vec[i][1] = 0;
										colour_vec[i][2] = 255;
										colour_switch_vec[i]++;
									}
									break;

								case (3):	// blue++
									colour_vec[i][1] += dcolour;
									if (colour_vec[i][1] >= 255) {
										colour_vec[i][1] = 255;
										colour_switch_vec[i]++;
									}
									break;

								case (4):	// red++
									colour_vec[i][0] += dcolour;
									if (colour_vec[i][0] >= 255) {
										colour_vec[i][0] = 255;
										colour_switch_vec[i]++;
									}
									break;

								default:	// done
									colour_done_vec[i] = true;
									advance_sum++;
									break;
							}
						}
						window_ptr->draw(text_ptr_vec[i]);
					}

					// update alpha
					alpha += 3;
					if (alpha >= 255) {
						alpha = 255;
					}

					// draw input_text
					input_text.setFillColor(
						sf::Color(255, 255, 255, alpha)
					);
					window_ptr->draw(input_text);

					// conditionally increment animation_state
					if (advance_sum >= 11) {
						animation_state++;
						alpha = 0;
					}
					break;

				case (3):	// pause
					// draw large [ESC]
					window_ptr->draw(ESC_large_sprite);

					// draw text
					for (int i = 0; i < text_ptr_vec.size(); i++) {
						window_ptr->draw(text_ptr_vec[i]);
					}

					// draw input_text
					window_ptr->draw(input_text);

					// conditionally increment animation_state
					if (time_elapsed.asSeconds() >= 5.5) {
						animation_state++;
					}
					break;

				case (4):	// fade out
					// draw large [ESC]
					window_ptr->draw(ESC_large_sprite);

					// draw text
					for (int i = 0; i < text_ptr_vec.size(); i++) {
						window_ptr->draw(text_ptr_vec[i]);
					}

					// draw input_text
					window_ptr->draw(input_text);

					// draw fading rectangle
					rectangle.setFillColor(sf::Color(0, 0, 0, alpha));
					window_ptr->draw(rectangle);

					// update alpha
					alpha += 2;

					// conditionally increment animation_state
					if (alpha >= 255) {
						alpha = 255;
						animation_state++;
					}
					break;

				default:	// animation finished
					animation_finished = true;
					break;
			}

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

	return window_ptr;
}	// end playBrandAnimation()


// -------- class implementations -------- //


// ---- Assets ---- //

Assets::Assets() {
	/*
	 *	Constructor for Assets class
	 */

	//

	// stream out and return
	std::cout << "Assets object created at " << this << "." << std::endl;
	return;
}	// end Assets::Assets()


void Assets::loadFont(std::string path_2_font, std::string asset_key) {
	/*
	 *	Method to load font and add to font_map
	 */

	sf::Font* font = new sf::Font();

	if (!font->loadFromFile(path_2_font))
	{
		std::stringstream error_ss;
		error_ss << "EXCEPTION: Assets::loadFont(): Cannot load font at \"" <<
			path_2_font << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	if (this->font_map.count(asset_key) > 0) {
		std::cout << "WARNING: Assets::loadFont(): Asset key \"" << asset_key <<
			"\" already in use. Asset will be overwritten!" << std::endl;
		delete this->font_map[asset_key];
	}

	this->font_map[asset_key] = font;
	std::cout << "\tsf::Font asset \"" << asset_key << "\" loaded at " <<
		font << "." << std::endl;

	return;
}	// end Assets::loadFont()


void Assets::loadTexture(std::string path_2_texture, std::string asset_key) {
	/*
	 *	Method to load texture and add to texture_map
	 */

	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(path_2_texture))
	{
		std::stringstream error_ss;
		error_ss << "EXCEPTION: Assets::loadTexture(): Cannot load texture at \"" <<
			path_2_texture << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	if (this->texture_map.count(asset_key) > 0) {
		std::cout << "WARNING: Assets::loadTexture(): Asset key \"" << asset_key <<
			"\" already in use. Asset will be overwritten!" << std::endl;
		delete this->texture_map[asset_key];
	}

	this->texture_map[asset_key] = texture;
	std::cout << "\tsf::Texture asset \"" << asset_key << "\" loaded at " <<
		texture << "." << std::endl;

	return;
}	// end Assets::loadTexture()


void Assets::loadSoundBuffer(std::string path_2_soundbuffer, std::string asset_key) {
	/*
	 *	Method to load sound buffer and add to soundbuffer_map
	 */

	sf::SoundBuffer* soundbuffer = new sf::SoundBuffer();

	if (!soundbuffer->loadFromFile(path_2_soundbuffer))
	{
		std::stringstream error_ss;
		error_ss << "EXCEPTION: Assets::loadSoundBuffer(): Cannot load sound buffer at \"" <<
			path_2_soundbuffer << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	if (this->soundbuffer_map.count(asset_key) > 0) {
		std::cout << "WARNING: Assets::loadSoundBuffer(): Asset key \"" << asset_key <<
			"\" already in use. Asset will be overwritten!" << std::endl;
		delete this->soundbuffer_map[asset_key];
	}

	this->soundbuffer_map[asset_key] = soundbuffer;
	std::cout << "\tsf::SoundBuffer asset \"" << asset_key << "\" loaded at " <<
		soundbuffer << "." << std::endl;

	return;
}	// end Assets::loadSoundBuffer()


void Assets::loadSound(std::string path_2_sound, std::string asset_key) {
	/*
	 *	Method to load sound and add to sound_map
	 */

	// create associated sf::SoundBuffer
	this->loadSoundBuffer(path_2_sound, asset_key);

	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*(this->soundbuffer_map[asset_key]));

	if (this->sound_map.count(asset_key) > 0) {
		std::cout << "WARNING: Assets::loadSound(): Asset key \"" << asset_key <<
			"\" already in use. Asset will be overwritten!" << std::endl;
		delete this->sound_map[asset_key];
	}

	this->sound_map[asset_key] = sound;
	std::cout << "\tsf::Sound asset \"" << asset_key << "\" loaded at " <<
		sound << "." << std::endl;

	return;
}	// end Assets::loadSound()


sf::Font* Assets::getFont(std::string asset_key) {
	/*
	 *	Method to get font from font_map
	 */

	if (this->font_map.count(asset_key) <= 0) {
		std::stringstream error_ss;
		error_ss << "EXCEPTION: Assets::getFont(): Cannot get font " <<
			"with asset key \"" << asset_key << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	return this->font_map[asset_key];
}	// end Assets::getFont()


sf::Texture* Assets::getTexture(std::string asset_key) {
	/*
	 *	Method to get texture from texture_map
	 *	be sure to dereference if you need const Texture&
	 */

	if (this->texture_map.count(asset_key) <= 0) {
		std::stringstream error_ss;
		error_ss << "EXCEPTION: Assets::getTexture(): Cannot get texture " <<
			"with asset key \"" << asset_key << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	return this->texture_map[asset_key];
}	// end Assets::getTexture()


sf::SoundBuffer* Assets::getSoundBuffer(std::string asset_key) {
	/*
	 *	Method to get SoundBuffer from soundbuffer_map
	 */

	if (this->soundbuffer_map.count(asset_key) <= 0) {
		std::stringstream error_ss;
		error_ss << "EXCEPTION: Assets::getSoundBuffer(): Cannot get sound buffer " <<
			"with asset key \"" << asset_key << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	return this->soundbuffer_map[asset_key];
}	// end Assets::getSoundBuffer()


sf::Sound* Assets::getSound(std::string asset_key) {
	/*
	 *	Method to get Sound from sound_map
	 */

	if (this->sound_map.count(asset_key) <= 0) {
		std::stringstream error_ss;
		error_ss << "EXCEPTION: Assets::getSound(): Cannot get sound buffer " <<
			"with asset key \"" << asset_key << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	return this->sound_map[asset_key];
}	// end Assets::getSound()


Assets::~Assets() {
	/*
	 *	Destructor for Assets class
	 */

	// clean up fonts
	for (
		auto itr = this->font_map.begin();
		itr != this->font_map.end();
		itr++
	) {
		delete itr->second;
		std::cout << "\tsf::Font asset \"" << itr->first << "\" at " <<
			itr->second << " destroyed." << std::endl;
	}
	this->font_map.clear();

	// clean up textures
	for (
		auto itr = this->texture_map.begin();
		itr != this->texture_map.end();
		itr++
	) {
		delete itr->second;
		std::cout << "\tsf::Texture asset \"" << itr->first << "\" at " <<
			itr->second << " destroyed." << std::endl;
	}
	this->texture_map.clear();

	// clean up sound buffers
	for (
		auto itr = this->soundbuffer_map.begin();
		itr != this->soundbuffer_map.end();
		itr++
	) {
		delete itr->second;
		std::cout << "\tsf::SoundBuffer asset \"" << itr->first << "\" at " <<
			itr->second << " destroyed." << std::endl;
	}
	this->soundbuffer_map.clear();

	// clean up sounds
	for (
		auto itr = this->sound_map.begin();
		itr != this->sound_map.end();
		itr++
	) {
		delete itr->second;
		std::cout << "\tsf::Sound asset \"" << itr->first << "\" at " <<
			itr->second << " destroyed." << std::endl;
	}
	this->sound_map.clear();

	// stream out and return
	std::cout << "Assets object at " << this << " destroyed." << std::endl;
	return;
}	// end Assets::~Assets()


// ---- MusicPlayer ---- //

MusicPlayer::MusicPlayer(Assets* assets_ptr, sf::RenderWindow* window_ptr) {
	/*
	 *	Constructor for MusicPlayer class
	 */

	this->first_play_flag = true;
	this->render_flag = false;
	this->render_alpha = 0;
	this->render_state = 0;
	this->render_frame = 0;
	this->assets_ptr = assets_ptr;
	this->window_ptr = window_ptr;

	// stream out and return
	std::cout << "MusicPlayer object created at " << this << "." << std::endl;
	return;
}	// end MusicPlayer::MusicPlayer()


void MusicPlayer::addTrack(std::string path_2_track, std::string track_key) {
	/*
	 *	Method to "add track" to track_map
	 */

	sf::Music* music = new sf::Music();

	if (!music->openFromFile(path_2_track))
	{
		std::stringstream error_ss;
		error_ss << "EXCEPTION: MusicPlayer::addTrack(): Cannot add track at \"" <<
			path_2_track << "\".";
	    throw std::runtime_error(error_ss.str());
	}

	if (this->track_map.count(track_key) > 0) {
		std::cout << "WARNING: MusicPlayer::addTrack(): Track key \"" <<
			track_key << "\" already in use. Track will be overwritten!" <<
			std::endl;
		delete this->track_map[track_key];
	}

	this->track_map[track_key] = music;
	this->current_track = this->track_map.begin();
	std::cout << "\tTrack (sf::Music) \"" << track_key << "\" added at " <<
		music << "." << std::endl;

	return;
}	// end MusicPlayer::openTrack()


void MusicPlayer::play(void) {
	/*
	 *	Method to play current track
	 */

	// play (resume) current track
	this->current_track->second->play();

	// print track info (if first play)
	if (this->first_play_flag) {
		this->printTrackInfo();
		this->first_play_flag = false;
	}

	return;
}	// end MusicPlayer::play()


void MusicPlayer::pause(void) {
	/*
	 *	Method to pause current track
	 */

	// pause current track
	this->current_track->second->pause();
	return;
}	// end MusicPlayer::pause()


void MusicPlayer::stop(void) {
	/*
	 *	Method to stop current track
	 */

	// stop current track
	this->current_track->second->stop();
	return;
}	// end MusicPlayer::stop()


void MusicPlayer::nextTrack(void) {
	/*
	 *	Method to stop current track and move to next track
	 */

	this->current_track->second->stop();

	this->current_track++;
	if (this->current_track == this->track_map.end()) {
		this->current_track = this->track_map.begin();
	}
	this->printTrackInfo();

	return;
}	// end MusicPlayer::nextTrack()


void MusicPlayer::prevTrack(void) {
	/*
	 *	Method to stop current track and move to previous track
	 */

	this->current_track->second->stop();

	if (this->current_track == this->track_map.begin()) {
		this->current_track = this->track_map.end();
	}
	this->current_track--;
	this->printTrackInfo();

	return;
}	// end MusicPlayer::prevTrack()


void MusicPlayer::printTrackInfo(void) {
	/*
	 *	Method to print track info.
	 */

	if (!this->render_flag) {
		this->render_flag = true;
	}
	else {
		this->render_alpha = 0;
		this->render_state = 0;
		this->render_frame = 0;
	}

	return;
}	// end MusicPlayer::printTrackInfo()


void MusicPlayer::renderTrackInfo(void) {
	/*
	 *	Method to render track info to window.
	 */

	if (this->render_flag) {
		// init rectangles
		int background_alpha;
		int text_alpha;
		sf::RectangleShape background_rect;
		switch (this->render_state) {
			case (0):	// fade in
				background_alpha = this->render_alpha;
				text_alpha = this->render_alpha;
				if (background_alpha > 192) {
					background_alpha = 192;
				}
				this->render_alpha += 3;

				if (this->render_alpha >= 255) {
					this->render_alpha = 255;
					this->render_state++;
				}
				break;

			case (1):	// pause
				background_alpha = 192;
				text_alpha = 255;
				this->render_frame++;
				if (this->render_frame >= 2 * FRAMES_PER_SECOND) {
					this->render_state++;
				}
				break;

			default:	// fade out
				background_alpha = this->render_alpha;
				text_alpha = this->render_alpha;
				if (background_alpha > 192) {
					background_alpha = 192;
				}
				else if (background_alpha <= 0) {
					background_alpha = 0;
				}
				if (text_alpha <= 0) {
					text_alpha = 0;
				}
				this->render_alpha -= 3;

				if (this->render_alpha <= 0) {
					this->render_alpha = 0;
					this->render_state = 0;
					this->render_frame = 0;
					this->render_flag = false;
				}
				break;
		}
		background_rect.setFillColor(sf::Color(64, 64, 64, background_alpha));


		// set text font, size, and string
		sf::Text track_text;
		track_text.setFont(*(this->assets_ptr->getFont("teletype")));
		track_text.setCharacterSize(16);
		track_text.setString(this->current_track->first);
		track_text.setFillColor(
			sf::Color(255, 255, 255, text_alpha)
		);
		int text_width = ceil(1.01 * track_text.getLocalBounds().width);
		int text_height = ceil(1.01 * track_text.getLocalBounds().height) + 4;
		track_text.setPosition(
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
		this->window_ptr->draw(track_text);
	}

	return;
}	// end MusicPlayer::renderTrackInfo()


sf::SoundSource::Status MusicPlayer::getStatus(void) {
	/*
	 *	Method to get status of current track
	 */

	return this->current_track->second->getStatus();
}	// end MusicPlayer::getStatus()


MusicPlayer::~MusicPlayer() {
	/*
	 *	Destructor for MusicPlayer class
	 */

	// clean up tracks
	for (
		auto itr = this->track_map.begin();
		itr != this->track_map.end();
		itr++
	) {
		itr->second->stop();
		delete itr->second;
		std::cout << "\tTrack (sf::Music) \"" << itr->first << "\" at " <<
			itr->second << " destroyed." << std::endl;
	}
	this->track_map.clear();

	// stream out and return
	std::cout << "MusicPlayer object at " << this << " destroyed." << std::endl;
	return;
}	// end MusicPlayer::~MusicPlayer()


// ---- TextBox ---- //

TextBox::TextBox(
	Assets* assets_ptr,
	sf::RenderWindow* window_ptr
) {
	/*
	 *	Constructor for TextBox class
	 */

	this->done_flag = true;
	this->text_flag = false;
	this->animation_state = -1;
 	this->font_size = 0;
 	this->height = 0;
 	this->width = 0;
	this->target_height = 0;
	this->target_width = 0;
 	this->x = 0;
 	this->y = 0;
	this->text_ptr_vec_idx = 0;
 	this->feed_string = "";
 	this->font_key = "";

	this->assets_ptr = assets_ptr;
	this->window_ptr = window_ptr;

	// stream out and return
	std::cout << "TextBox object created at " << this << "." << std::endl;
	return;
}	// end TextBox::TextBox()


void TextBox::reset(void) {
	/*
	 *	Method to reset text box and ready for next call to makeBox()
	 */

	this->done_flag = true;
	this->text_flag = false;
 	this->animation_state = -1;
  	this->font_size = 0;
  	this->height = 0;
  	this->width = 0;
 	this->target_height = 0;
 	this->target_width = 0;
  	this->x = 0;
  	this->y = 0;
	this->text_ptr_vec_idx = 0;
  	this->feed_string = "";
  	this->font_key = "";

	for (
		auto itr = this->text_ptr_vec.begin();
		itr != this->text_ptr_vec.end();
		itr++
	) {
		delete (*itr);
	}
	this->text_ptr_vec.clear();

	return;
}	// end TextBox::reset()


void TextBox::drawFrame(void) {
	/*
	 *	Method to handle drawing of text box frame
	 */

	if (this->feed_string.empty()) {
		return;
	}

	// init backing rect
	sf::RectangleShape back_rect;
	back_rect.setFillColor(TEXT_BOX_BACK_COLOUR);
	back_rect.setPosition(this->x, this->y);
	back_rect.setOutlineColor(TEXT_BOX_OUTLINE_COLOUR);
	back_rect.setOutlineThickness(TEXT_BOX_OUTLINE_THICKNESS);

	// animation switch statement
	switch (this->animation_state) {
		case (0):	// draw expanding box
			back_rect.setSize(sf::Vector2f(this->width, this->height));

			if (this->width < this->target_width) {
				this->width += 4 * (SECONDS_PER_FRAME) * this->target_width;
			}
			if (this->width >= this->target_width) {
				this->width = this->target_width;
			}

			if (this->height < this->target_height) {
				this->height += 4 * (SECONDS_PER_FRAME) * this->target_height;
			}
			if (this->height >= this->target_height) {
				this->height = this->target_height;
			}

			if (
				this->width == this->target_width &&
				this->height == this->target_height
			) {
				this->text_flag = true;
			}

			break;

		default:
			// do nothing!
			break;
	}

	if (!this->font_key.empty()) {
		// assemble left text
		if (this->text_ptr_vec_idx > 0) {
			this->left_text.setString("Page Left: [<--]");
			this->left_text.setFont(
				*(this->assets_ptr->getFont(this->font_key))
			);
			this->left_text.setCharacterSize(0.015 * SCREEN_HEIGHT);
			double left_width = this->left_text.getLocalBounds().width;
			double left_height = this->left_text.getLocalBounds().height;
			this->left_text.setOrigin(0, left_height / 2);
			this->left_text.setPosition(
				this->x + TEXT_BOX_OUTLINE_THICKNESS,
				this->y + this->target_height - TEXT_BOX_OUTLINE_THICKNESS -
					0.5 * left_height
			);
		}
		else {
			this->left_text.setString("");
		}

		// assemble right text
		if (this->text_ptr_vec_idx < this->text_ptr_vec.size() - 1) {	// right
			this->right_text.setString("Page Right: [-->]");
			this->right_text.setFont(
				*(this->assets_ptr->getFont(this->font_key))
			);
			this->right_text.setCharacterSize(0.015 * SCREEN_HEIGHT);
			double right_width = this->right_text.getLocalBounds().width;
			double right_height = this->right_text.getLocalBounds().height;
			this->right_text.setOrigin(right_width, right_height / 2);
			this->right_text.setPosition(
				this->x + this->target_width - TEXT_BOX_OUTLINE_THICKNESS,
				this->y + this->target_height - TEXT_BOX_OUTLINE_THICKNESS -
					0.5 * right_height
			);
		}
		else {
			this->right_text.setString("");
		}
	}

	// draw
	this->window_ptr->draw(back_rect);
	if (this->text_flag) {
		this->window_ptr->draw(*(this->text_ptr_vec[this->text_ptr_vec_idx]));
		this->window_ptr->draw(this->enter_text);
		this->window_ptr->draw(this->left_text);
		this->window_ptr->draw(this->right_text);
	}

	return;
}	// end TextBox::drawFrame()


void TextBox::makeBox(
	std::string feed_string,
	std::string font_key,
	int font_size,
	int x,
	int y,
	double target_width,
	double target_height
) {
	/*
	 *	Method to make text box (sequence) with given string, font params, and
	 *	size params appear on the screen
	 */

	// reset
	this->reset();

	// if non-empty feed string, play sound
	if (!feed_string.empty()) {
		this->assets_ptr->getSound("page right")->play();
	}

	// set attributes
	this->animation_state = 0;
	this->font_size = font_size;
  	this->target_height = target_height;
  	this->target_width = target_width;
  	this->x = x;
  	this->y = y;
  	this->feed_string = feed_string;
  	this->font_key = font_key;

	// assemble enter text
	this->enter_text.setString("Close: [Enter]");
	this->enter_text.setFont(
		*(this->assets_ptr->getFont(this->font_key))
	);
	this->enter_text.setCharacterSize(0.015 * SCREEN_HEIGHT);
	double enter_width = this->enter_text.getLocalBounds().width;
	double enter_height = this->enter_text.getLocalBounds().height;
	this->enter_text.setOrigin(enter_width / 2, enter_height / 2);
	this->enter_text.setPosition(
		this->x + this->target_width / 2 + TEXT_BOX_OUTLINE_THICKNESS,
		this->y + this->target_height - TEXT_BOX_OUTLINE_THICKNESS -
			0.5 * enter_height
	);

	// populate text_ptr_vec
	int feed_idx = 0;
	double line_width = this->target_width - 2 * TEXT_BOX_OUTLINE_THICKNESS;
	double field_height = this->target_height - 2 * TEXT_BOX_OUTLINE_THICKNESS -
		enter_height;
	while (feed_idx < this->feed_string.size()) {
		// assemble field
		std::string field_str = "";
		while (
			feed_idx < this->feed_string.size() &&
			sf::Text(
				field_str,
				*(this->assets_ptr->getFont(this->font_key)),
				this->font_size
			).getLocalBounds().height < field_height
		) {
			// assemble line
			std::string line_str = "";
			bool break_flag = false;
			bool page_flag = false;
			while (
				feed_idx < this->feed_string.size() &&
				sf::Text(
					line_str,
					*(this->assets_ptr->getFont(this->font_key)),
					this->font_size
				).getLocalBounds().width < line_width
			) {
				line_str += this->feed_string[feed_idx];
				feed_idx++;

				if (line_str.back() == '\n') {
					field_str += line_str;
					line_str = "";
					break_flag = true;
					break;
				}
				else if (line_str.back() == '@') {
					line_str.pop_back();
					field_str += line_str;
					line_str = "";
					page_flag = true;
					break;
				}
			}

			if (page_flag) {
				break;
			}
			else if (!break_flag) {
				// trim line back
				while (std::isalnum(line_str.back())) {
					line_str.pop_back();
					feed_idx--;
				}

				// append to field_str
				field_str += line_str + "\n";
			}
		}

		// push field onto text_ptr_vec
		sf::Text* push_text = new sf::Text(
			field_str,
			*(this->assets_ptr->getFont(this->font_key)),
			this->font_size
		);
		push_text->setPosition(
			this->x + TEXT_BOX_OUTLINE_THICKNESS,
			this->y + TEXT_BOX_OUTLINE_THICKNESS
		);

		this->text_ptr_vec.push_back(push_text);
		//std::cout << this->text_ptr_vec.size() << std::endl;
	}

	return;
}	// end of TextBox::makeBox()


void TextBox::handleEvents(int key_code) {
	/*
	 *	Method to handle events, namely distinct key presses
	 */

	if (!this->text_ptr_vec.empty()) {
		switch (key_code) {
			case (sf::Keyboard::Enter):	// close
				this->makeBox(
					"",
					this->font_key,
					this->font_size,
					this->x,
					this->y,
					this->target_width,
					this->target_height
				);
				this->assets_ptr->getSound("paper crumple")->play();
				break;

			case (sf::Keyboard::Right):	// page right
				if (this->text_ptr_vec_idx < this->text_ptr_vec.size() - 1) {
					this->text_ptr_vec_idx++;
					this->height = 0;
				 	this->width = 0;
					this->animation_state = 0;
					this->text_flag = false;
					this->assets_ptr->getSound("page right")->play();
				}
				break;

			case (sf::Keyboard::Left):	// page left
				if (this->text_ptr_vec_idx > 0) {
					this->text_ptr_vec_idx--;
					this->height = 0;
				 	this->width = 0;
					this->animation_state = 0;
					this->text_flag = false;
					this->assets_ptr->getSound("page left")->play();
				}
				break;

			default:
				// do nothing!
				break;
		}
	}

	return;
}	// end TextBox::handleEvents()


bool TextBox::isDone(void) {
	/*
	 *	Getter for done_flag attribute
	 */

	return this->done_flag;
}	// end TextBox::isDone()


TextBox::~TextBox() {
	/*
	 *	Destructor for TextBox class
	 */

	for (
 		auto itr = this->text_ptr_vec.begin();
 		itr != this->text_ptr_vec.end();
 		itr++
 	) {
 		delete (*itr);
 	}
 	this->text_ptr_vec.clear();

	// stream out and return
	std::cout << "TextBox object at " << this << " destroyed." << std::endl;
	return;
}	// end TextBox::~TextBox()
