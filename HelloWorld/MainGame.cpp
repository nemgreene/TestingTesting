#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Maths.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

Vec2 PlayerPos(240,160);


//Detect map collisions one way or another to make sure nobody walks/flies through walls
void UtilBuildMap();


// Accepts 2 position vectors, and calculates the rotation from vec1 to vec 2
// Math implemented below
int UtilHandleCursorDirection(Vec2 vec1, Vec2 vec2) {
	//returns degrees to rotate sprites and vector to send bullet along
};

//Abstraction to handle drawing all sprites
//will likely need to handle a hierarchy/order/z-index to draw foregroud/background
void HandleSprites(int aimRotation)
{
	//Sprites have to be draw in a dynamic order
	//when a character is facind down, gun is draw on top
	//when a char is facing up, gun is drawn below
	//some bg elements need to be drawn on top of the characters, as they should be able to walk behind them
	//we need to be able to restrucutre the hierarchy of sprites dynamically frame by frame
	//how do we build this?

	//Could have a predefined number of layers ie : [bg, utility, gun, character, utility, foreground]
	//that is constructed at the start of the game
	//then can be updated by calling UpdateSprites()

	//ie on game start   [bg, utility, gun, character, utility, foreground]
	//during runtime upateSprites(charcater: -1, gun :1)
	//output             [bg, utility, character, gun, utility, foreground]
	// 
	// 
	//adidtionally we could have a global offest that all positions reference in here that is incremented as the character moves to mimic camera follow
};

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
void GunsShouldUpdateTheirBullets() {
	charObject.primaryGun.updateBullets();
	charObject.secondaryGun.updateBullets();
};

void HandleEnemyMovement();
// random movement pattern
// VV
//a* pathfinding, raytracing




enum GameObjectType
{
	TYPE_PLAYER,
	TYPE_ENEMY,
	TYPE_BULLET,
};

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();


	//Play::CreateGameObject(TYPE_PLAYER, { PlayerPos.GetX(),PlayerPos.GetY() }, 50, "phillip");
	Play::CreateGameObject(TYPE_BULLET, { PlayerPos.GetX(),PlayerPos.GetY() }, 50, "laser");
	//Play::CreateGameObject(TYPE_ENEMY, { 320, 360 }, 50, "bullet_sprite" );
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cOrange );
	Vec2 MousePos = Play::GetMousePos();
	Vec2 MouseDir = MousePos - PlayerPos;
	float MouseDirMag = MouseDir.mag(MouseDir);

	Vec2 MouseUnitVec{MouseDir.GetX()/MouseDirMag, MouseDir.GetY() / MouseDirMag };

	// Printing out the mouse direction
	std::string DirectionXString = std::to_string(MouseUnitVec.GetX());
	std::string DirectionYString = std::to_string(MouseUnitVec.GetY());
	std::string DirectionString = "x = " + DirectionXString + ", y =" + DirectionYString;
	const char* PS = DirectionString.c_str();
	Play::DrawDebugText({ 150,50 }, PS);
	// finished printing



	//Play::DrawBackground();
	//GameObject& obj_player = Play::GetGameObjectByType(TYPE_PLAYER);
	GameObject& obj_bullet = Play::GetGameObjectByType(TYPE_BULLET);
	obj_bullet.rotation = MouseUnitVec.rad(MouseUnitVec);
	//Play::SetSprite(obj_player, "phillip_idle_6", 0.16666f);
	Play::SetSprite(obj_bullet, "laser_2", 0.5);
	//Play::UpdateGameObject(obj_player);
	Play::UpdateGameObject(obj_bullet);
	//Play::DrawObjectRotated(obj_player);
	Play::DrawObjectRotated(obj_bullet);

	//Play::DrawObject(obj_player);

	/*GameObject& obj_enemy = Play::GetGameObjectByType(TYPE_ENEMY);
	Play::SetSprite(obj_enemy, "bullet_sprite", 0);
	Play::UpdateGameObject(obj_enemy);
	Play::DrawObject(obj_enemy);*/

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

