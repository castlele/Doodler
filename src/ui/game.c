#include <raylib.h>

#include "game.h"
#include "physics/world.h"
#include "platforms.h"
#include "player.h"
#include "score.h"

typedef struct Game
{
    PhysicsWorld world;
    PlatformsFactory platformsFactory;
    Player player;
} Game;

Game _game;

void ListenGameEvents();

void InitGameScreen()
{
    _game = (Game) {
        .player = CreatePlayer(GetScreenWidth() / 2, GetScreenHeight() / 2),
        .world = CreatePhysicsWorld(GRAVITY_X, GRAVITY_Y),
        .platformsFactory = CreatePlatformFactory(),
    };

    SetPlatformColliders(&_game.platformsFactory, &_game.world);
    AddColliderToWorld(&_game.world, _game.player.collider);
}

void DestroyGameScreen()
{
}

void UpdateGameScreen(float dt)
{
    UpdatePhysicsWorld(&_game.world, dt);
    UpdatePlatforms(&_game.platformsFactory);
    UpdatePlayer(&_game.player, dt);
    UpdateScore(_game.player.y, _game.player.width);

    ListenGameEvents();
}

void ListenGameEvents()
{
    if (IsKeyPressed(KEY_R)) {
        ResetPlayerPos(&_game.player);
        ResetPlatforms(&_game.platformsFactory);
    }
}

void DrawGameScreen()
{
    DrawPlatforms(&_game.platformsFactory);
    DrawPlayer(&_game.player);
    DrawScore();
    DrawPhysicsWorld(&_game.world);
}
