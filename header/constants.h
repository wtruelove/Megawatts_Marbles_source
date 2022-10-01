/*
 *	Constants definitions for Megawatts & Marbles - The Energy Planning Game
 *
 *	[ESC] Interactive
 *
 *	Anthony Truelove MASc, P.Eng.
 *	Spencer Funk BEng, EIT
 *
 *	Copyright 2022 (C) - [ESC] Interactive
 *	See license terms for details
 *
 *	This defines recurring constants referenced throughout the source and
 *	header files for the game.
 *
 */


#ifndef CONSTANTS_H
#define CONSTANTS_H


// numerical constants
#define FRAMES_PER_BLIT		5.0
#define	SECONDS_PER_FRAME	1.0 / 60.0
#define FRAMES_PER_SECOND	60.0

#define SCREEN_WIDTH		1280.0 //1024.0
#define SCREEN_HEIGHT		960.0  //768.0

#define GW_PER_TOKEN  1
#define TOTAL_TOKENS  36
//#define STORAGE_TOKENS_PER_GW  2
#define FISSION_TOKENS_PER_GW	2
#define PEAKER_TOKENS_PER_GW	2
#define STORAGE_TOKENS_PER_GW	3
#define STORAGE_GW_PER_INCREMENT 1
#define CAPACITY_PER_GEOTHERMAL_ROLL 3

#define MAX_FISSION_CAPACITY	999		// remove upper bounds, pricing to enforce
#define MAX_PEAKER_CAPACITY		999		// remove upper bounds, pricing to enforce

// SFML-specific constants

#define MARBLE_COLOUR_COAL				sf::Color(25, 4, 1, 255)
#define MARBLE_COLOUR_COMBINED			sf::Color(217, 88, 34, 255)
#define MARBLE_COLOUR_FISSION			sf::Color(0, 255, 0, 255)
#define MARBLE_COLOUR_GEOTHERMAL		sf::Color(196, 161, 26, 255)
#define MARBLE_COLOUR_GLASS				sf::Color(224, 242, 241, 32)
#define MARBLE_COLOUR_GLASS_MUSTER		sf::Color(224, 242, 241, 128)
#define MARBLE_COLOUR_HYDRO				sf::Color(0, 80, 255, 255)
#define MARBLE_COLOUR_PEAKER			sf::Color(255, 0, 0, 255)
#define MARBLE_COLOUR_SOLAR				sf::Color(255, 246, 115, 255)
#define MARBLE_COLOUR_STORAGE			sf::Color(75, 150, 75, 255)
#define MARBLE_COLOUR_TIDAL				sf::Color(6, 143, 252, 255)
#define MARBLE_COLOUR_WAVE				sf::Color(255, 0, 255, 255)
#define MARBLE_COLOUR_WIND				sf::Color(104, 194, 255, 255)

#define TEXT_BOX_BACK_COLOUR			sf::Color(0, 86, 255, 240)
#define TEXT_BOX_OUTLINE_COLOUR			sf::Color(128, 122, 138, 255)
#define TEXT_BOX_OUTLINE_THICKNESS		8.0

#define	SMOG_COLOUR						sf::Color(128, 100, 75, 255)


// string constants (for various text boxes)

#define TEXT_LOREM_IPSUM	"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Vitae aliquet nec ullamcorper sit amet risus nullam. Morbi non arcu risus quis. Metus vulputate eu scelerisque felis imperdiet. Accumsan lacus vel facilisis volutpat est velit egestas dui id. In dictum non consectetur a erat nam. Eu sem integer vitae justo. Egestas sed tempus urna et pharetra pharetra massa. Tellus elementum sagittis vitae et leo. Auctor augue mauris augue neque gravida in fermentum et. A scelerisque purus semper eget duis. Vel orci porta non pulvinar. Tincidunt tortor aliquam nulla facilisi cras fermentum. Est placerat in egestas erat. Ipsum faucibus vitae aliquet nec ullamcorper sit. Suspendisse ultrices gravida dictum fusce ut placerat orci nulla pellentesque. Et malesuada fames ac turpis egestas integer eget aliquet nibh. Commodo odio aenean sed adipiscing diam donec adipiscing tristique risus. Suspendisse interdum consectetur libero id faucibus. Volutpat maecenas volutpat blandit aliquam. Vitae ultricies leo integer malesuada nunc vel. Enim ut tellus elementum sagittis vitae et leo duis. Scelerisque varius morbi enim nunc faucibus a pellentesque sit amet. Ultricies leo integer malesuada nunc vel risus commodo. Nec ullamcorper sit amet risus nullam eget. Et molestie ac feugiat sed lectus. Molestie at elementum eu facilisis sed. Massa id neque aliquam vestibulum morbi blandit cursus. Enim neque volutpat ac tincidunt vitae semper quis lectus nulla. Et netus et malesuada fames ac turpis. Condimentum id venenatis a condimentum vitae sapien pellentesque habitant. Purus ut faucibus pulvinar elementum integer enim neque. Enim lobortis scelerisque fermentum dui faucibus in. Vel pharetra vel turpis nunc eget lorem dolor."

#define TEXT_MONTY_PYTHON	"ARTHUR: Whoa there!\n[clop clop clop]\nSOLDIER #1: Halt! Who goes there?\nARTHUR: It is I, Arthur, son of Uther Pendragon, from the castle of Camelot. King of the Britons, defeator of the Saxons, sovereign of all England!\nSOLDIER #1: Pull the other one!\nARTHUR: I am. And this my trusty servant Patsy. We have ridden the length and breadth of the land in search of knights who will join me in my court of Camelot. I must speak with your lord and master.\nSOLDIER #1: What, ridden on a horse?\nARTHUR: Yes!\nSOLDIER #1: You're using coconuts!\nARTHUR: What?\nSOLDIER #1: You've got two empty halves of coconut and you're bangin' 'em together.\nARTHUR: So? We have ridden since the snows of winter covered this land, through the kingdom of Mercea, through--\nSOLDIER #1: Where'd you get the coconut?\nARTHUR: We found them.\nSOLDIER #1: Found them? In Mercea? The coconut's tropical!\nARTHUR: What do you mean?\nSOLDIER #1: Well, this is a temperate zone.\nARTHUR: The swallow may fly south with the sun or the house martin or the plumber may seek warmer climes in winter yet these are not strangers to our land.\nSOLDIER #1: Are you suggesting coconuts migrate?\nARTHUR: Not at all, they could be carried.\nSOLDIER #1: What -- a swallow carrying a coconut?\nARTHUR: It could grip it by the husk!\nSOLDIER #1: It's not a question of where he grips it! It's a simple question of weight ratios! A five ounce bird could not carry a 1 pound coconut.\nARTHUR: Well, it doesn't matter. Will you go and tell your master that Arthur from the Court of Camelot is here.\nSOLDIER #1: Listen, in order to maintain air-speed velocity, a swallow needs to beat its wings 43 times every second, right?\nARTHUR: Please!\nSOLDIER #1: Am I right?\nARTHUR: I'm not interested!\nSOLDIER #2: It could be carried by an African swallow!\nSOLDIER #1: Oh, yeah, an African swallow maybe, but not a European swallow. That's my point.\nSOLDIER #2: Oh, yeah, I agree with that.\nARTHUR: Will you ask your master if he wants to join my court at Camelot?!\nSOLDIER #1: But then of course, uh, African swallows are non-migratory.\nSOLDIER #2: Oh, yeah.\nSOLDIER #1: So, they couldn't bring a coconut back anyway.\n[clop clop clop]\nSOLDIER #2: Wait a minute! Supposing two swallows carried it together?\nSOLDIER #1: No, they'd have to have it on a line.\nSOLDIER #2: Well, simple! They'd just use a strand of creeper!\nSOLDIER #1: What, held under the dorsal guiding feathers?\nSOLDIER #2: Well, why not?"

#define TEXT_COAL		"COAL PLANT\t(tokens/GW: 1)\n\n\tCoal plants burn coal to boil water into high pressure steam that spins a turbine. Changing the flow of water/steam too quickly (to generate more or less power) damages the equipment.\nCampfire analogy: Slow to heat up, and slow to cool down.\n\nRULES: Limited ramp rate, i.e. you cannot change by more than +/- 1 marble from hour to hour (after the first round).\n\nSCORING: -1 points per Coal marble dispatched."

#define TEXT_PEAKER		"PEAKER NATURAL GAS PLANT\t(tokens/GW: 2)\n\n\tPeaker natural gas plants are very similar to jet airplane engines (they don't use steam) and they can change their output quickly. However, they are expensive to build and operate.\n\nBBQ analogy: Quick to heat up, quick to cool down.\n\nRULES: There are no operational constraints for this plant, but they are expensive to build and operate.\n\nSCORING: -0.75 points per Peaker marble dispatched."

#define TEXT_WIND		"WIND TURBINE\t(tokens/GW: 1)\n\n\tWind turbines generate electricity based on how strong the wind blows, but you can't control the wind.\n\nRULES: Wind dependent. The wind resource will be procedurally generated every round, and it determines your output.\n\nBACKGROUND: Wind farms are often guaranteed priority access to the electricity market (\"feed in guarantee\"). That means as soon as the wind blows the system operator has agreed to purchase this electricity. This is usually done as an incentive to promote renewable energies."

#define TEXT_HYDRO		"HYDROPOWER PLANT\t(token/GW: 1)\n\n\tHydropower dams are filled with water when it rains and mostly when snow melts. Often dams are only filled in late winter and spring. The gathered water must last for the rest of the year.\n\nRULES:\n\nLimited reservoir: You only have a limited water supply each game, ration it!\n\nMinimum discharge: You can't run dry your river -- think of the fish! You must discharge (i.e. play) at least one marble each round."

#define TEXT_FISSION	"NUCLEAR FISSION PLANT\t(tokens/GW: 2)\n\n\tNuclear fission plants split a heavy, unstable nucleus into two lighter nuclei, thus releasing energy. Nuclear plants are thermal base load plants (they hardly ever change their output (until they are shut down)).\n\n\tNuclear fusion is the combining of nuclei to form a larger and heavier nucleus. This is currently not viable technology and therefore is not used in gameplay.\n\nRULES:\n\nNo ramping: You decide at the beginning of the game (i.e., in the first round) how many marbles your nuclear plant will produce. It will produce the same amount every hour during the game.\n\nExpensive: Fission plants are expensive to build and operate."

#define TEXT_COMBINED	"COMBINED CYCLE NATURAL GAS PLANT\t(tokens/GW: 1)\n\n\tCombined cycle natural gas plants are more efficient than Peaker natural gas plants but are not as flexible. They combine a gas turbine with a steam turbine. The steam part is slow to adapt to changing demand - similar to coal, but not quite as \"stiff\". \n\nRULES: Limited ramp rate, i.e. you cannot change by more than +/- 2 marbles from hour to hour (after the first round).\n\nSCORING: -0.5 points per Combined marble dispatched."

#define TEXT_SOLAR		"SOLAR PHOTOVOLTAIC PLANT\t(tokens/GW: 1)\n\n\tSolar photovoltaic (PV) power generates electricity based on the sunshine we get, and like wind you cannot control it.\n\nRULES: Sun dependent. The solar resource will be procedurally generated every round, and it determines your output. The resource available is affected by time of day, cloud cover, and smog.@BACKGROUND: Solar plants are often guaranteed priority access to the electricity market (\"feed in guarantee\"). That means as soon as the sun shines the system operator has agreed to purchase this electricity. This is usually done as an incentive to promote renewable energies."

#define TEXT_GEOTHERMAL	"GEOTHERMAL PLANT\t(tokens/GW: 1)\n\n\tGeothermal power plants generate electricity by spinning a steam turbine via water heated underground. These plants are notoriously risky to build because of uncertainty in drilling to find adequate resource.\n\nRULES:\n\nRisky drilling: Capacity is dependent on the success of drilled wells, which will be determined randomly at the beginning of each game.\n\nMinimum investment: You must invest into potential capacity in 3 token increments.\n\nLimited ramp rate: You cannot change by more than +/- 2 marbles from hour to hour (after the first round)."

#define TEXT_TIDAL		"TIDAL PLANT\t(tokens/GW: 1)\n\n\tTidal power plants generate electricity from the movement of the ocean tides, and like the winds you cannot control them.\n\nRULES: Tide dependent. The tidal resource will be procedurally generated every round, and it determines your output.\n\nBACKGROUND: Tidal plants are often guaranteed priority access to the electricity market (\"feed in guarantee\"). That means as soon as the tides flow the system operator has agreed to purchase this electricity. This is usually done as an incentive to promote renewable energies."

#define TEXT_WAVE		"WAVE PLANT\t(tokens/GW: 1)\n\n\tWave power plants generate electricity from the movement of the ocean surface (i.e., the waves), and like the winds you cannot control them.\n\nRULES: Sea state dependent. The wave resource will be procedurally generated every round, and it determines your output.\n\nBACKGROUND: Wave plants are often guaranteed priority access to the electricity market (\"feed in guarantee\"). That means as soon as the sea heaves the system operator has agreed to purchase this electricity. This is usually done as an incentive to promote renewable energies."

#define TEXT_STORAGE	"ENERGY STORAGE SYSTEM\t(tokens/GW: 3)\n\n\tStorage and Demand Response (a.k.a. load deferral) may be invested in using tokens.\n\n3 tokens = 1 GWh Storage + 1 GW Demand Response\n\nRULES:\n\nCharge / Discharge: Over generating? Store and discharge up to n GWh (i.e., up to built capacity) at any time throughout the day, subject to available room / charge. Available for use all day.\n\nLoad Deferral: Coming up short? Defer n GW of demand (i.e., up to built capacity) to a future turn. Only 1 use per game!\n\nExpensive: Energy storage systems are expensive to build and operate."

#define TEXT_TUTORIAL	"TUTORIAL\n\nWelcome to Megawatts & Marbles - The Energy Planning Game!\n\nNOTE: You can always bring up this tutorial text by pressing [T].\n\nNOTE: You can always bring up the key bindings text by pressing\n[B].\n\nPage right to work through the tutorial, or press [Enter] to skip.@\tThe intent of this game is to help you learn about grid design and energy planning. As such, you will be setting up power production infrastructure, and then managing it in each round\n(i.e., each hour of the game day).\n\n\tThe goal is to EXACTLY meet electricity demand in every round, while at the same time minimizing damage to the environment.@\tAt the bottom of the screen, you should see six boxes. These are the slots in which you can set up power plants. \n\n\tThe green box is the presently selected slot. You can cycle through the slots using [A] and [D]. Try it out!@\tTo cycle through the types of power plant that you can set up in each slot, press the [W] and [S] keys.\n\n\tNote that as you cycle through the plant types, the information for each plant will be displayed (replacing this tutorial text). You can always display the plant information again later by pressing [I]. Try cycling through the plants now, then press [T] to return to the tutorial once you are ready to proceed.\n\n\tOnce you have selected one or more plant types, press\n[Spacebar] to proceed to plant sizing.@\tIf you have reached the plant sizing phase, then you should see your capacity tokens displayed in the top right of the screen. These capacity tokens are the currency you use to build out your power production infrastructure.\n\n\tYou can add or remove tokens from each of your plants using the [W] and [S] keys. Try it out!\n\n\tOnce you have assigned all tokens, press [Spacebar] to proceed to the first round of play.@\tIf you have reached the first round of play, then you should see the energy demand displayed in the top right, your score in the top centre, and the hour of the game day in the top left.\n\n\tAt this point, you now have control of your plants' production, which you can increase and decrease using [W] and [S]. Note that each marble represents 1 GW of production for that round. Once you have mustered enough marbles to dispatch and meet the energy demand, press [Spacebar] to commit production and move to the next round. Try it out!@\tIf you have successfully committed your first dispatch of marbles, then you should have seen the points summary pop up and your score change. In this game, scoring in each round is as follows:\n\nEnergy Demand: If satisfied, points earned equal to the demand. If not, you lose points equal to the remaining, unmet demand.\n\nEmissions: Certain plant types have emissions associated with them. Emissions cause you to lose points as follows:\n\n\tCoal: -1 points per marble dispatched.\n\n\tPeaker: -0.75 points per marble dispatched.\n\n\tCombined Cycle: -0.5 points per marble dispatched.\n\nNote also that emissions will increase the smog in game, which has a negative impact on the solar resource available in each round.@Overproduction: If you produce too much energy and cannot store it, then you lose 1 point per GWh of excess.\n\nThe game ends once a full game day has been played through\n(i.e., 24 rounds).@Note that you can view your past energy demands and distributions using the energy overlay (by pressing [E]). In addition, you can view a forecast of the coming hour using the forecase overlay (by pressing [F]).@\tThat's it! As you play through, you will no doubt figure things out. Have fun!!\n\nNOTE: If at any time you want to quit a play session and start over, you can do so by pressing [P]. You can also quit the game by way of either [Esc], or clicking the (X) on the game window."

#define TEXT_KEYS		"KEY BINDINGS\n\n[A] and [D]: Cycle through plant slots.\n\n[W] and [S]: Cycle through plant types, assign tokens, muster marbles.\n\n[Spacebar]: Select, commit, etc.\n\n[T]: Tutorial.\n\n[B]: Key bindings.\n\n[I]: Plant information.\n\n[E]: Toggle energy overlay.\n\n[F]: Toggle forecast overlay.\n\n[L]: Perform load deferral.\n\n[P]: Quit and restart.@[Escape]: Exit game.\n\n[M]: Pause/resume music.\n\n[,]: Previous music track.\n\n[.]: Next music track."


#endif
