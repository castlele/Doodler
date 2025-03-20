#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#include "colors.h"
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

    bool isPaused;

    void (*backToMainScreen)(void);
} Game;

Game *_game;

void ListenGameEvents();

void InitGameScreen(void (*backToMainScreen)(void))
{
    _game = malloc(sizeof(Game));
    _game->player = CreatePlayer(GetScreenWidth() / 2, GetScreenHeight() / 2);
    _game->world = CreatePhysicsWorld(GRAVITY_X, GRAVITY_Y);
    _game->platformsFactory = CreatePlatformFactory();
    _game->isPaused = false;
    _game->backToMainScreen = backToMainScreen;

    SetPlatformColliders(&_game->platformsFactory, &_game->world);
    AddColliderToWorld(&_game->world, _game->player.collider);
    ResetPlatforms(&_game->platformsFactory);
}

void DestroyGameScreen()
{
    free(_game);
}

void UpdateGameScreen(float dt)
{
    if (!_game->isPaused) {
        UpdatePhysicsWorld(&_game->world, dt);
        UpdatePlatforms(&_game->platformsFactory);
        UpdatePlayer(&_game->player, dt);
        UpdateScore(_game->player.y, _game->player.width);
    }

    ListenGameEvents();
}

void ListenGameEvents()
{
    if (IsKeyPressed(KEY_R)) {
        ResetPlayerPos(&_game->player);
        ResetPlatforms(&_game->platformsFactory);
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        _game->isPaused = !_game->isPaused;
    }

    if (_game->isPaused) {
        // Handle pause buttons
    }
}

void DrawGameScreen()
{
    DrawPlatforms(&_game->platformsFactory);
    DrawPlayer(&_game->player);
    DrawScore();
    DrawPhysicsWorld(&_game->world);

    if (_game->isPaused) {
        DrawRectangle(
            0, 0,
            GetScreenWidth(), GetScreenHeight(),
            SHADOW_COLOR
        );
    }
}
