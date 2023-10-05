#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#pragma once
#include "Gun.h"
#include "Play.h"
#include "Enemy.h"
#include "Maths.h"
#include "Utilities.h"
#include "HandleInputs.h"
#include "SpriteManager.h"
#include "EnemyController.h"

//#include "Pawn.h"


int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;
Vec2 vPlayerPos(DISPLAY_WIDTH/2, DISPLAY_HEIGHT / 2);
bool INIT = true;


#pragma region NeedsWork

//Detect map collisions one way or another to make sure nobody walks/flies through walls
void utilBuildMap();

//Handle user commands
void HandleInputs() {
	//Once the sprite has been drawn 
	//Is user moving
	//Is the user shooting, do they have ammo
	//Is user dodging, can they dodge, where are they dodging
	//reload, handle perfect reload
};


void HandleEnemyMovement();
// random movement pattern
// VV
//a* pathfinding, raytracing

#pragma endregion


SpriteManager spriteManager = SpriteManager();

EnemyController enemyController = EnemyController(&spriteManager);
Gun primaryGun;



// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();


	int iPlayer = Play::CreateGameObject(TYPE_PLAYER, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 50, "fry");

	std::vector<std::map<int, std::string>> vInitializeSpriteMap = {
	{},                                  //Background    0
	{},                                  //Bullets       1
	{} ,								 //Enemies       2
	{},                                  //enemies guns  3
	{{iPlayer, "fry_ruinning_down_6"} }, //Char          4
	{},       //Guns          5
	{}									 //foreground    6
	};

	spriteManager.initializeSprites(vInitializeSpriteMap);
	
	primaryGun = Gun(TYPE_BULLET_PRIMARY, "laser_2", &spriteManager);

	EnemySchema robitSchema = { primaryGun, "robit_running_down" };
	std::map<int, EnemySchema> enemyGenerationSchema = { {1, robitSchema} };
	
	enemyController.spawnEnemies(enemyGenerationSchema);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cOrange );



	////get mouse position
	Vec2 vMousePos = Play::GetMousePos();
	////calculate aim vector
	Vec2 vAimVec = utilHandleCursorDirection( vPlayerPos, vMousePos);

	////catch user inputs
	handleInputs(vPlayerPos, vAimVec, &primaryGun);

	//tick all sprites
	spriteManager.tickSprites(vMousePos, vAimVec.rad(), elapsedTime);

	//tick all bullets

	//cleanup
	utilJanitor();

	//after all enemies/bullets have been destroyed, bring in next round of enemy 
	enemyController.moveEnemies();


	primaryGun.moveBullets(&enemyController._enemies);

	//display
	Play::PresentDrawingBuffer();
	//dismount
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

