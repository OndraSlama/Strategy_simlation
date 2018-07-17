#ifndef GLOBAL_H_
#define GLOBAL_H_


//Simulation
const int FPS = 250; //SFML
const int simulationFPS = 500; //CHANGEABLE
const float TIMESTEP = 1 / (float)simulationFPS;

//SFML Window
const int HALFWIDTH = 650;
const int HALFHEIGHT = 400;


//Board
const float boardwidth = 12100;
const float boardheight = 3515 * 2;
//const float interval = boardwidth / 9;

const float goalsize = 2150; //width of goal
const float slopesize = 400; //CHANGEABLE //width of slope around borders
const float slopeacc = 5000; //CHANGEABLE //acceleration of ball on slope - need to calculate


							 //Ball
const float ballradius = 350 / 2;
const float ballacc = 200; //CHANGEABLE //acceleration (deceleration) of ball due to friction - need to calculate

const float default_ballx = boardwidth / 2;
const float default_bally = 0;

const float bounce_ratio = 0.7; //CHANGEABLE //speed reduction on contact with player


								//Players
const float boxwidth = 120;
const float boxheight = 210;

const float playerheight = 500;

//Scaling for SFML
const float scale = 10;
const float WCORRECTION = HALFWIDTH - boardwidth / scale / 2;

#endif // !GLOBAL_H_