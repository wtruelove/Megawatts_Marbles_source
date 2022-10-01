/*
 *	[ESC] Interactive core library - header
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


#ifndef ESC_H
#define ESC_H


// -------- includes -------- //
#include "constants.h"
#include "includes.h"


// -------- function prototypes -------- //
sf::RenderWindow* getRenderWindowPtr(std::string);
sf::RenderWindow* playBrandAnimation(std::string);


// -------- class structures & interfaces -------- //


// ---- Assets ---- //

class Assets {
	/*
	 *	Class to load, store, and fetch game assets
	 */

	private:
		std::map<std::string, sf::Font*> font_map;
		std::map<std::string, sf::Texture*> texture_map;
		std::map<std::string, sf::SoundBuffer*> soundbuffer_map;
		std::map<std::string, sf::Sound*> sound_map;

	protected:
		//

	public:
		Assets();

		void loadFont(std::string, std::string);
		void loadTexture(std::string, std::string);
		void loadSoundBuffer(std::string, std::string);
		void loadSound(std::string, std::string);

		sf::Font* getFont(std::string);
		sf::Texture* getTexture(std::string);
		sf::SoundBuffer* getSoundBuffer(std::string);
		sf::Sound* getSound(std::string);

		~Assets();
};	// end Assets


// ---- MusicPlayer ---- //

class MusicPlayer {
	/*
	 *	Class to open and stream from a list of tracks
	 */

 	private:
		bool first_play_flag;
		bool render_flag;
		int render_alpha;
		int render_state;
		int render_frame;
		Assets* assets_ptr;
		std::map<std::string, sf::Music*>::iterator current_track;
		std::map<std::string, sf::Music*> track_map;
		sf::RenderWindow* window_ptr;

	protected:
		//

	public:
		MusicPlayer(Assets*, sf::RenderWindow*);

		void addTrack(std::string, std::string);
		void play(void);
		void pause(void);
		void stop(void);
		void nextTrack(void);
		void prevTrack(void);
		void printTrackInfo(void);
		void renderTrackInfo(void);
		sf::SoundSource::Status getStatus(void);

		~MusicPlayer();
};	// end MusicPlayer


// ---- TextBox ---- //

class TextBox{
	/*
	 *	Class to handle the drawing of JRPG-style text boxes
	 */

	private:
		bool text_flag;
		bool done_flag;
		int animation_state;
		int font_size;
		int x;
		int y;
		int text_ptr_vec_idx = 0;
		double height;
		double width;
		double target_height;
		double target_width;
		std::string feed_string;
		std::string font_key;

		Assets* assets_ptr;
		sf::RenderWindow* window_ptr;
		sf::Text enter_text;
		sf::Text left_text;
		sf::Text right_text;
		std::vector<sf::Text*> text_ptr_vec;

	protected:
		void reset(void);

	public:
		TextBox(Assets*, sf::RenderWindow*);

		void drawFrame(void);
		void makeBox(std::string, std::string, int, int, int, double, double);
		void handleEvents(int);
		bool isDone(void);

		~TextBox();
};	// end TextBox


#endif
