
#include <bur/plctypes.h>
#include <math.h>

#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "Global.h"
#include "ExtraMath.h"
#include "PhyShapes.h"

#include "Board.h"

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

Sim sim;

void _INIT ProgramInit(void)
{

	sim.setup();

	sim.ball->velocity.x = 0; //40000/40;
	//ball->velocity.y = 20500;
	sim.ball->velocity.y = -0; //-20000/40;
	
	sim.ball->position = Vec2(5330, 0);

	sim.red[0].velocity = Vec2(0, 0);
	sim.blu[0].velocity = Vec2(0, 0);
	
	//red[0].position.y = 0;

}

void resetBall(int x, int y){
	sim.ball->position = Vec2(x, y);
	sim.ball->velocity = Vec2(0, 0);
}

void newBall(){
	sim.ball->position = Vec2(6050, 3300);
	sim.ball->velocity = Vec2(-400 + (rand() % 800) , -2000);
}

void _CYCLIC ProgramCyclic(void)
{
	
	//Button hadling
	if(hmi.sim.simResetBall.pushed){
		hmi.sim.simResetBall.pushed = false;
		resetBall(hmi.sim.xball, hmi.sim.yball);
	}
	if(hmi.sim.simNewBall.pushed){
		hmi.sim.simNewBall.pushed = false;
		hmi.sim.simNewBallAck = true;
		newBall();
	}
	
	//Simulation handling
	
	if(camera.mode == 2){
		sim.ball->move();
	
	
		if(sim.ball->position.x < 0){
			resetBall(boardwidth/2, 0);
			sensor.isGoal[0] = true;
		}
		else if(sim.ball->position.x > boardwidth){
			resetBall(boardwidth/2, 0);
			sensor.isGoal[1] = true;
		}

		if(cycle_counter % fps_divider == 0){
			camera.ball[2].X = (int)(ballx = sim.ball->position.x);
			camera.ball[2].Y = (int)(bally = sim.ball->position.y);
			camera.ball[2].newdata = true;
		}
		cycle_counter++;	
	
	
		for (int i = 0; i < 4; i++) {
			//red[i].position.y = (float) motion.status.real.pos.lin[i];
			sim.red[i].position.y = (float) motion.status.lin[i].pos;
			sim.red[i].velocity.y = (float) motion.status.lin[i].vel;
		
			sim.red[i].angle = (float) motion.status.rot[i].pos;
			sim.red[i].angular_velocity = (float) motion.status.rot[i].vel;
			sim.red[i].move();
		
			sim.blu[i].movePos( (float) sensor.human.pos[i] );
			sim.blu[i].moveAng( (float) (1 - sensor.human.block[i]) * 900);
		
			//redd[i] = red[i].position.y;
			//bluu[i] = blu[i].position.y;
		
			//redangle[i] = red[i].angle;
			//bluangle[i] = blu[i].angle;
		}
		
		sim.collide();
	
		//ballvx = ball->velocity.x;
		//ballvy = ball->velocity.y;

	
		//ballspeed = sqrt(ball->velocity.lengthSquared());
	
	
	}
	

}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}
