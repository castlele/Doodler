#include <raylib.h>
#include <stdbool.h>

#include "application.h"
#include "ui/game.h"
#include "ui/main.h"
#include "config.h"

typedef struct App
{
    AppState state;
    bool shouldClose;
} App;

App _app;

void InitScreen();
void Update(float dt);
void ListenApplicationEvents();
void Draw();

void StartGame();
void BackToMainMenu();
void ApplyConfig();

void InitApplication()
{
    _app = (App) {
        .state = AppStateMain,
        .shouldClose = false,
    };
}

void RunApplication()
{
    // TODO: Make window resizable
    //       https://www.reddit.com/r/raylib/comments/a19a67/resizable_window_questions/
    InitWindow(DEFAULT_SCREEN_W, DEFAULT_SCREEN_H, APP_NAME);
    ApplyConfig();

    InitScreen();

    float dt;

    while (!WindowShouldClose() && !_app.shouldClose) {
        dt = GetFrameTime();

        Update(dt);
        ListenApplicationEvents();

        BeginDrawing();
            ClearBackground(WHITE);

            Draw();
        EndDrawing();
    }

    CloseWindow();
}

// Private methods declarations

void InitScreen()
{
    switch (_app.state) {
        case AppStateGame:
            InitGameScreen(&BackToMainMenu);
            break;
        case AppStateMain:
            InitMainScreen(&StartGame);
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

void ListenApplicationEvents()
{
    if (IsKeyDown(KEY_Q) && IsKeyDown(KEY_LEFT_CONTROL)) {
        _app.shouldClose = true;
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

void StartGame()
{
    switch (_app.state) {
        case AppStateGame:
            break;
        case AppStateMain:
            DestroyMainScreen();
            break;
    }

    _app.state = AppStateGame;
    InitScreen();
}

void BackToMainMenu()
{
    switch (_app.state) {
        case AppStateGame:
            DestroyGameScreen();
            break;
        case AppStateMain:
            break;
    }

    _app.state = AppStateMain;
    InitScreen();
}

void ApplyConfig()
{
    // TODO: Make this value configurable
    // FIX: Why setting fps shouldn't be used?
    // https://bedroomcoders.co.uk/posts/218
    SetTargetFPS(60);
    SetExitKey(-1);
}
