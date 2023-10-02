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

//each gun class should have its own method to update its own bullets, encapsulating custom bullet behavior in each gun//
//long term memory efficiency may infom if keeping a single list of all bullets in memory is more efficient, or having each gun track its own bullet
//void GunsShouldUpdateTheirBullets() {
//	charObject.primaryGun.updateBullets();
//	charObject.secondaryGun.updateBullets();
//};

void HandleEnemyMovement();
// random movement pattern
// VV
//a* pathfinding, raytracing

#pragma endregion


SpriteManager spriteManager = SpriteManager();
Gun primaryGun = Gun::Gun(TYPE_BULLET_PRIMARY, "laser_2");



// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();

	int iPlayer = Play::CreateGameObject(TYPE_PLAYER, { vPlayerPos.GetX(), vPlayerPos.GetY() }, 50, "fry");
	int iGunPrimary = Play::CreateGameObject(TYPE_GUN_PRIMARY, { 100, 200 }, 50, "lava_gun");
	int iRobit = Play::CreateGameObject(TYPE_ENEMY, { 350, 350 }, 50, "robit");



	std::map<int, std::string> mCharLevel = { {iPlayer, "fry_ruinning_down_6"}, {iGunPrimary, "lava_gun_1"}, {iRobit, "robit_running_down_6"} };



	std::vector<std::map<int, std::string>> vInitializeSpriteMap = { mCharLevel };

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

	//utilDebugString()
	utilDebugString( "X: " + std::to_string(vAimVec.GetX()) , 100, 100);
	utilDebugString( "Y: " + std::to_string(vAimVec.GetY()) , 100, 125);


	spriteManager.tickSprites(vMousePos, vAimVec.rad());

	handleInputs(vPlayerPos, vAimVec, &primaryGun);

	primaryGun.moveBullets();

	//
	utilJanitor();
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}


//aim bullet at mouse
//GameObject& obj_bullet = Play::GetGameObjectByType(TYPE_BULLET);
// 
//obj_bullet.rotation = vAimVec.rad();

//Play::SetSprite(obj_bullet, "laser_2", 0.5);
//Play::UpdateGameObject(obj_bullet);
//Play::DrawObjectRotated(obj_bullet);	
//
/*GameObject& player = Play::GetGameObjectByType(TYPE_PLAYER);

Play::SetSprite(player, "fry_ruinning_down_6", 0.2f);
Play::UpdateGameObject(player);
Play::DrawObjectRotated(player);*/

