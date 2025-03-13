#include <raylib.h>
#include <stdio.h>

#include "application.h"
#include "ui/game.h"
#include "ui/main.h"
#include "config.h"

typedef struct App
{
    AppState state;
} App;

App _app;

void InitScreen();
void Update(float dt);
void Draw();

void ApplyConfig();

void InitApplication()
{
    _app = (App) {
        .state = AppStateMain,
    };
}

void RunApplication()
{
    ApplyConfig();

    // TODO: Make window resizable
    //       https://www.reddit.com/r/raylib/comments/a19a67/resizable_window_questions/
    InitWindow(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H, APP_NAME);

    InitScreen();

    float dt;

    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        Update(dt);

        BeginDrawing();
            ClearBackground(WHITE);

            Draw();
        EndDrawing();
    }

    CloseWindow();
}

void ChangeApplicationState(AppState newState)
{
}

// Private methods declarations

void InitScreen()
{
    switch (_app.state) {
        case AppStateGame:
            InitGameScreen();
            break;
        case AppStateMain:
            InitMainScreen();
            break;
    }
}

void Update(float dt)
{
    switch (_app.state) {
        case AppStateGame:
            UpdateGameScreen(dt);
            break;
        case AppStateMain:
            UpdateMainScreen(dt);
            break;
    }
}

void Draw()
{
    switch (_app.state) {
        case AppStateGame:
            DrawGameScreen();
            break;
        case AppStateMain:
            DrawMainScreen();
            break;
    }
}

void ApplyConfig()
{
    // TODO: Make this value configurable
    // FIX: Why setting fps shouldn't be used?
    // https://bedroomcoders.co.uk/posts/218
    SetTargetFPS(60);
}
