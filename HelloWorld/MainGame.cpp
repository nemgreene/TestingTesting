#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Maths.h"
#include "SpriteManager.h"
#include "Utilities.h"
#include "HandleInputs.h"
#include "Gun.h"


int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;
Vec2 vPlayerPos(DISPLAY_WIDTH/2, DISPLAY_HEIGHT / 2);



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

Gun primaryGun = Gun::Gun(TYPE_BULLET_PRIMARY, "laser_2", &spriteManager);



// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();

	int iPlayer = Play::CreateGameObject(TYPE_PLAYER, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 50, "fry");
	int iGunPrimary = Play::CreateGameObject(TYPE_GUN_PRIMARY, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 50, "lava_gun");
	int iRobit = Play::CreateGameObject(TYPE_ENEMY, { 350, 350 }, 50, "robit");

	std::vector<std::map<int, std::string>> vInitializeSpriteMap = {
		{},                                  //Background    0
		{},                                  //Bullets       1
		{{iRobit, "robit_running_down_6"}} , //Enemies       2
		{},                                  //enemies guns  3
		{{iPlayer, "fry_ruinning_down_6"} }, //Char          4
		{{iGunPrimary, "lava_gun_1"}},       //Guns          5
		{}									 //foreground    6
	};
	spriteManager.initializeSprites(vInitializeSpriteMap);

}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cOrange );
	//get mouse position
	Vec2 vMousePos = Play::GetMousePos();
	//calculate aim vector
	Vec2 vAimVec = utilHandleCursorDirection( vPlayerPos, vMousePos);

	//catch user inputs
	handleInputs(vPlayerPos, vAimVec, &primaryGun);

	//tick all sprites
	spriteManager.tickSprites(vMousePos, vAimVec.rad());

	//tick all bullets
	primaryGun.moveBullets();

	//cleanup
	utilJanitor();
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

