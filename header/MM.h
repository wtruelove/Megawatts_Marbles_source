/*
 *	Header file for Megawatts & Marbles - The Energy Planning Game
 *
 *	[ESC] Interactive

 *	Anthony Truelove MASc, P.Eng.
 *	Spencer Funk BEng, EIT
 *
 *	Copyright 2022 (C) - [ESC] Interactive
 *	See license terms for details
 *
 *	Interface for Megawatts & Marbles.
 *
 *	ref: A. Moreira at al. (2013), SFML Game Development - Learn how to use
 *			SFML 2.0 to develop your own feature-packed game, Packt Publishing
 *			ISBN 978-1-84969-684-5
 *
 *		https://en.sfml-dev.org/documentation/2.5.1/
 *
 */


#ifndef MM_H
#define MM_H


// -------- includes -------- //
#include "constants.h"
#include "includes.h"

#include "ESC.h"


// -------- function prototypes -------- //
void runTests(void);
void renderSplashScreen(sf::RenderWindow*);


// -------- class structures & interfaces -------- //


// ---- Marble ---- //

class Marble {
	private:
		bool charge;
		int frame;
		int glow_frame;
		int height;
		int tile;
		int width;
		double init_dist;
		double position_x;
		double position_y;
		double scale;
		double target_x;
		double target_y;
		std::string texture_key;

		sf::Color shader_colour;
		sf::RenderWindow* window_ptr;

		Assets* assets_ptr;

	protected:
		//

	public:
		Marble(double, double, sf::RenderWindow*, Assets*, sf::Color, bool);

		bool isFinished(void);
		void drawFrame(void);

		~Marble(void);

};	// end Marble


// ---- Emissions Hierarchy ---- //


// ---- Particle ---- //

class Particle {
	private:
		//

	protected:
		int height;
		int sprite_idx;
		int width;
		double alpha;
		double angle;
		double position_x;
		double position_y;
		double scale;
		std::string texture_key;

		sf::RenderWindow* window_ptr;

		Assets* assets_ptr;

	public:
		Particle(double, double, sf::RenderWindow*, Assets*);

		bool isFinished(void);
		void drawFrame(double wind_speed_ratio);

		virtual ~Particle(void);

};	// end Particle


// ---- Particle <-- Steam ---- //

class Steam : public Particle {
	private:
		//

	protected:
		//

	public:
		Steam(double, double, sf::RenderWindow*, Assets*);

		~Steam(void);

};	// end Steam


// ----  Particle <-- Smoke ---- //

class Smoke : public Particle {
	private:
		//

	protected:
		//

	public:
		Smoke(double, double, sf::RenderWindow*, Assets*);

		~Smoke(void);

};	// end Smoke


// ---- Sky Disk ---- //

class SkyDisk {
	private:
		double angle;

		sf::RenderWindow* window_ptr;
		sf::Sprite day_sprite;
		sf::Sprite night_sprite;

		Assets* assets_ptr;

		double getAlphaVar(void);

	protected:
		//

	public:
		SkyDisk(sf::RenderWindow*, Assets*);

		void buildSprites(void);
		void drawFrame(double);

		~SkyDisk(void);

};	// end SkyDisk


// ---- OvercastClouds ---- //

class OvercastClouds {
	private:
		sf::RenderWindow* window_ptr;
		sf::Sprite overcast_sky_sprite;
		std::list<sf::Sprite*> cloud_sprite_ptr_list;

		Assets* assets_ptr;

		sf::Color getShading(double, double);

	protected:
		//

	public:
		OvercastClouds(sf::RenderWindow*, Assets*);

		void buildSprites(void);
		void drawFrame(double, double, double);

		~OvercastClouds(void);
};	// end OvercastClouds


// ---- Foreground (and Plinko City) ---- //

class Foreground {
	private:
		sf::RenderWindow* window_ptr;
		sf::Sprite terrain_sprite;
		sf::Sprite city_powered_sprite;
		sf::Sprite city_unpowered_sprite;

		Assets* assets_ptr;

		sf::Color getShading(double);

	protected:
		//

	public:
		Foreground(sf::RenderWindow*, Assets*);

		void buildSprites(void);
		void drawFrame(bool, double);

		~Foreground(void);

};	// end Foreground


// ---- Wind Sock ---- //

class WindSock {
	private:
		int frame;

		sf::RenderWindow* window_ptr;
		sf::Sprite sock_sprite;
		sf::Sprite tower_sprite;

		Assets* assets_ptr;

	protected:
		//

	public:
		WindSock(sf::RenderWindow*, Assets*);

		sf::Color getShading(double);
		void buildSprites(void);
		void drawFrame(double, double);

		~WindSock(void);
};	// end WindSock


// ---- Plant Hierarchy ---- //


// ---- Plant ---- //

class Plant {
	/*
	 *	Base class for hierarchy of plants (game objects)
	 */

	private:
		//

	protected:
		bool running_flag;
		bool has_run;
		bool pulse_flag;
		bool draw_tokens;
		bool draw_charge;
		bool draw_price;
		int frame;
		int muster_frame;
		int line_frame;
		int price_per_GW;
		int pulse_frame;
		int height;
		int last_production_GWh;
		int marble_counter;
		int marble_frame;
		int marble_iters;
		int marbles_committed;
		int n_blits;
		int n_sprites;
		int sprite_idx;
		int width;
		double capacity_GW;
		double position_x;
		double position_y;
		double prod_GW;
		double scale;
		std::string texture_key;
		std::vector<int> marbles_committed_vector;

		sf::Color marble_colour;
		sf::RenderWindow* window_ptr;

		Assets* assets_ptr;
		std::list<Steam*> steam_ptr_list;
		std::list<Smoke*> smoke_ptr_list;
		std::list<Marble*> marble_ptr_list;
		std::list<sf::Sprite*> marble_sprite_ptr_list;

	public:
		Plant(int, int, double, sf::RenderWindow*, Assets*);

		void clearMarbles(void);
		bool isRunning(void);
		bool marblesFinished(void);
		int getMusteredMarbles(void);
		int getPositionX(void);
		int getPositionY(void);
		int getTextureIndex(void);
		int getMarblesCommitted(int);
		double getCapacityGW(void);
		int getPrice(void);

		sf::Color getMarbleColour(void);

		virtual void incMarbles(void);
		virtual void decMarbles(void);
		virtual void commitMarbles(void);
		virtual int commitCharge(int) {return 0;}

		void setRunning(bool);
		void setPositionX(int);
		void setPositionY(int);
		void setPlantTexture(int);
		void setHasRun(bool);
		void setPulseFlag(bool);
		void setDrawTokens(bool);
		void setDrawCharge(bool);
		void setDrawPrice(bool);
		void setPrice(int);

		bool hasTextureKey(void);

		void drawTokens(void);
		void drawCapacity(void);
		void drawPrice(void);
		virtual void drawMarbles(void);
		virtual void drawMusteredMarbles(void);
		virtual void drawSteam(double) {return;}
		virtual void drawSmoke(double) {return;}
		virtual void drawFrame(bool, bool);
		virtual double getProduction(double) {return 0;}
		virtual void setEnergyCapacity(double) {return;}
		virtual void setPowerCapacity(double);
		virtual void setCharge(double) {return;}
		virtual double getStorageGWh(void) {return 0;}
		virtual double getChargeGWh(void) {return 0;}
		virtual double getDesignSpeed(void) {return 0;}
		virtual double getDesignPeriod(void) {return 0;}
		virtual void drillSuccess(bool) {return;}

		virtual ~Plant(void);

};	// end Plant


// ---- Plant <-- Coal ---- //

class Coal : public Plant {
	private:
		//

	protected:
		//

	public:
		Coal(int, int, double, sf::RenderWindow*, Assets*);

		void drawSteam(double);
		void drawSmoke(double);

		void incMarbles(void);
		void decMarbles(void);
		void commitMarbles(void);

		~Coal(void);

};	// end Coal


// ---- Plant <-- Combined ---- //

class Combined : public Plant {
	private:
		//

	protected:
		//

	public:
		Combined(int, int, double, sf::RenderWindow*, Assets*);

		void drawSteam(double);
		void drawSmoke(double);

		void incMarbles(void);
		void decMarbles(void);
		void commitMarbles(void);

		~Combined(void);

};	// end Combined


// ---- Plant <-- Fission ---- //

class Fission : public Plant {
	private:
		//

	protected:
		//

	public:
		Fission(int, int, double, sf::RenderWindow*, Assets*);

		void drawSteam(double);

		void incMarbles(void);
		void decMarbles(void);
		void commitMarbles(void);

		~Fission(void);

};	// end Fission


// ---- Plant <-- Geothermal ---- //

class Geothermal : public Plant {
	private:
		std::list<sf::Text*> drill_txt_ptr_list;

	protected:
		//

	public:
		Geothermal(int, int, double, sf::RenderWindow*, Assets*);

		void drawSteam(double);
		void drawFrame(bool, bool);

		void incMarbles(void);
		void decMarbles(void);
		void commitMarbles(void);

		void drillSuccess(bool);

		~Geothermal(void);

};	// end Geothermal


// ---- Plant <-- Hydro ---- //

class Hydro : public Plant {
	private:
		//

	protected:
		double capacity_GWh;
		double charge_GWh;

	public:
		Hydro(int, int, double, sf::RenderWindow*, Assets*);

		void drawFrame(bool, bool);
		void setEnergyCapacity(double);
		void setCharge(double);

		double getStorageGWh(void);
		double getChargeGWh(void);

		void incMarbles(void);
		void decMarbles(void);
		void commitMarbles(void);

		~Hydro(void);

};	// end Hydro


// ---- Plant <-- Peaker ---- //

class Peaker : public Plant {
	private:
		//

	protected:
		//

	public:
		Peaker(int, int, double, sf::RenderWindow*, Assets*);

		void drawSmoke(double);

		~Peaker(void);

};	// end Peaker


// ---- Plant <-- Solar ---- //

class Solar : public Plant {
	private:
		//

	protected:
		//

	public:
		Solar(int, int, double, sf::RenderWindow*, Assets*);

		void incMarbles(void) {return;}
		void decMarbles(void) {return;}

		void drawFrame(bool, bool);
		double getProduction(double);

		~Solar(void);

};	// end Solar


// ---- Plant <-- Storage ---- //

class Storage : public Plant {
	private:
		//

	protected:
		double capacity_GWh;
		double charge_GWh;

	public:
		Storage(int, int, double, sf::RenderWindow*, Assets*);

		void incMarbles(void);
		void commitMarbles(void);
		int commitCharge(int);

		void drawFrame(bool, bool);
		void setEnergyCapacity(double);
		void setCharge(double);

		double getStorageGWh(void);
		double getChargeGWh(void);

		~Storage(void);

};	// end Storage


// ---- Plant <-- Tidal ---- //

class Tidal : public Plant {
	private:
		//

	protected:
		double angle;
		double design_speed_ms;

	public:
		Tidal(int, int, double, sf::RenderWindow*, Assets*);

		void incMarbles(void) {return;}
		void decMarbles(void) {return;}

		void drawFrame(bool, bool);
		double getProduction(double);
		double getDesignSpeed(void);

		~Tidal(void);

};	// end Tidal


// ---- Plant <-- Wave ---- //

class Wave : public Plant {
	private:
		//

	protected:
		double design_period_s;
		double wave_res_m;
		double wave_res_s;

	public:
		Wave(int, int, double, sf::RenderWindow*, Assets*);

		void incMarbles(void) {return;}
		void decMarbles(void) {return;}

		void drawFrame(bool, bool);
		double getProduction(double);
		double getDesignPeriod(void);

		~Wave(void);

};	// end Wave


// ---- Plant <-- Wind ---- //

class Wind : public Plant {
	private:
		//

	protected:
		double angle;
		double design_speed_ms;

	public:
		Wind(int, int, double, sf::RenderWindow*, Assets*);

		void incMarbles(void) {return;}
		void decMarbles(void) {return;}

		void drawFrame(bool, bool);
		double getProduction(double);
		double getDesignSpeed(void);

		~Wind(void);

};	// end Wind


class PhaseManager {
	/*
	 *	Class to manage different phases of the game
	 */

 private:
	 int phase;
	 int index;
	 int max_index;
	 int plant_num;
	 int max_plant_num; // this is hardcoded, not sure how to count types of plants
	 int capacity;
	 int capacity_tokens;
	 bool quitting_round;
	 bool quitting_game;
	 std::vector <bool> geothermal_present;
	 std::vector<int> plant_taboo_list;

 protected:
	 //

 public:
	 PhaseManager(void);

	 void reset(void);

	 int getPhase(void);
	 int getIndex(void);
	 int getPlantNum(void);
	 int getCapacity(void);
	 bool getQuittingRound(void);
	 bool getQuittingGame(void);
	 int getCapacityTokens(void);
	 bool getGeothermalPresent(int);

	 void setPhase(int);
	 void setIndex(int);
	 void setPlantNum(int);
	 void setCapacity(int);
	 void setQuittingRound(bool);
	 void setQuittingGame(bool);
	 void setCapacityTokens(int);
	 void setGeothermalPresent(int, bool);

	 void nextValidIndex(std::vector<Plant*>*);
	 void prevValidIndex(std::vector<Plant*>*);

	 void incIndex(std::vector<Plant*>);
	 void incPlantNum(void);
	 void incCapacity(int);
	 void incCapacityTokens(void);

	 void decIndex(std::vector<Plant*>);
	 void decPlantNum(void);
	 void decCapacity(int);
	 void decCapacityTokens(void);

	 int hydroStorageTable(int);

	 ~PhaseManager(void);

}; // end PhaseManager


class PictorialTutorial {
	/*
	 *	Class to manage sprites showing how to play the game
	 */

 private:

 protected:
	 int frame;
	 std::vector<int> heights;
	 std::vector<int> n_sprites;
	 std::vector<int> sprite_idx;
	 std::vector<int> widths;
	 double position_x;
	 double position_y;
	 std::vector<double> rel_pos_x;
	 std::vector<double> rel_pos_y;
	 std::vector<double> scales;
	 std::vector<std::string> texture_keys;
	 std::vector<int> ws_indices;
	 std::vector<int> ad_indices;
	 std::vector<int> spacebar_indices;

	 sf::RenderWindow* window_ptr;

	 Assets* assets_ptr;

 public:

 	 bool show_wasd_instructions_ws;
 	 bool show_wasd_instructions_ad;
	 bool show_spacebar_instructions;

 	 int w_presses_during_game;

	 PictorialTutorial(int, int, double, sf::RenderWindow*, Assets*);

	 void reset(void);

	 void drawFrame(int);

	 void update(PhaseManager*, std::vector<Plant*>*);

	 ~PictorialTutorial(void);

}; // end PictorialTutorial


class DiceRoll {
	/*
	 *	Class to manage sprites for dice rolls
	 */

 private:
	 int dice_num;
	 int roll_num;
	 bool rolling_dice;
	 std::vector<int> rolls_left;
 	 std::vector<int> geothermal_rolls;

	 int spacebar_frame_idx;
 	 std::vector<int> spacebar_frame_vec;

 protected:
	 int frame;
	 int height;
	 int n_sprites;
	 int sprite_idx;
	 int width;
	 double position_x;
	 double position_y;
	 double scale;
	 std::string texture_key;

	 sf::RenderWindow* window_ptr;

	 Assets* assets_ptr;

 public:

	 DiceRoll(int, int, double, sf::RenderWindow*, Assets*);

	 void reset(void);
 	 void resetGeothermalRolls(void);

	 bool getRollingDice(void);
	 int getDiceNum(void);
	 int getRollsLeft(int);
 	 int getGeothermalCapacity(void);

	 void setRollingDice(bool);
	 void setRollsLeft(int, int);
	 bool setGeothermalRolls(void);

 	 void randDiceNum(void);

	 void drawFrame(bool);

	 ~DiceRoll(void);

}; // end DiceRoll


// ---- Game ---- //

class Game {
	/*
	 *	Class to contain game attributes and methods
	 */

	private:
		bool draw_frame_rate;
		bool music_paused;
		bool powered_flag;
		bool draw_energy_overlay;
		bool draw_forecast_overlay;
		bool can_defer_load;
		int frame;
		int current_energy_demand_GWh;
		int tidal_idx_offset;
		int coal_marbles;
		int combined_marbles;
		int peaker_marbles;
		int excess_dispatch_GWh;
		int rolls_rem_corr;
		double cloud_cover_ratio;
		double next_cloud_cover_ratio;
		double dt_s;
		double frame_time_s;
		double hour_of_day;
		double next_hour_of_day;
		double time_since_run_s;
		double wind_speed_ratio;
		double next_wind_speed_ratio;
		double smog_ratio;
		double next_smog_ratio;
		double wave_res_s;
		double next_wave_res_s;
		double score;
		double fade_alpha;
		std::vector<bool> key_vec;
		std::vector<int> energy_demand_GWh_vec;
		std::vector<int> actual_energy_demand_GWh_vec;
		std::vector<double> tidal_res_ms_vec;
		std::string points_str;
		std::map<std::string, int> forecast_map;

		sf::Clock clock;
		sf::RenderWindow* window_ptr;
		sf::Sprite capacity_token_sprite;
		sf::Sprite energy_demand_sprite;
		sf::Sprite clock_face_sprite;
		sf::Sprite clock_hour_sprite;
		sf::Sprite clock_minute_sprite;

		Assets assets;
		OvercastClouds overcast_clouds;
		Foreground foreground;
		MusicPlayer music_player;
		PhaseManager phase_manager;
		PictorialTutorial pictorial_tutorial;
		DiceRoll dice_roll;
		std::vector<Plant*> plant_ptr_vec;
		SkyDisk sky_disk;
		TextBox text_box;
		WindSock wind_sock;

		void renderTitle(void);
		void handleEvents(void);
		void handleKeys(sf::Keyboard::Key, bool);
		void renderOverlays(void);
		void render(void);
		void setHourDay(double);
		void setPoweredFlag(bool);
		void pushPlant(int, Plant*);
		bool transition(void);
		void update(void);
		void plantInfo(int);
		void reset(void);
		void deferLoad(void);

		double generateWindRatio(void);
		double generateCloudRatio(void);
		double generateSolarResource(void);
		double generateTidalResource(void);
		double generateWaveResource(void);

		void getForecast(void);

	protected:
		//

	public:
		Game(sf::RenderWindow*);

		void initPlants(void);
		void clearPlants(void);
		void run(void);

		void test1(void);

		~Game(void);

};	// end Game


#endif
