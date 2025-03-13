#include <stdlib.h>
#include <raylib.h>

#include "main.h"

#define BUTTONS_W 100
#define BUTTONS_H 50

typedef struct MenuState
{
    Rectangle startButtonRect;
    Rectangle quitButtonRect;

    void (*startGameCallback)(void);
} MenusState;

MenusState *_menu;

void ListenMenuEvents();

void InitMainScreen(void (*startGame)(void))
{
    _menu = malloc(sizeof(MenusState));
    _menu->startGameCallback = startGame;

    int w = GetScreenWidth();
    int h = GetScreenHeight();

    int x = (w - BUTTONS_W) / 2;
    int startButtonY = (h - BUTTONS_H) / 2;
    int padding = 20;
    int quitButtonY = startButtonY + BUTTONS_H + padding;

    _menu->startButtonRect = (Rectangle) { x, startButtonY, BUTTONS_W, BUTTONS_H, };
    _menu->quitButtonRect = (Rectangle) { x, quitButtonY, BUTTONS_W, BUTTONS_H, };
}

void DestroyMainScreen()
{
    free(_menu);
}

void UpdateMainScreen(float dt)
{
    ListenMenuEvents();
}

void DrawMainScreen()
{
    DrawRectangle(
        _menu->startButtonRect.x,
        _menu->startButtonRect.y,
        _menu->startButtonRect.width,
        _menu->startButtonRect.height,
        BLUE
    );
    DrawRectangle(
        _menu->quitButtonRect.x,
        _menu->quitButtonRect.y,
        _menu->quitButtonRect.width,
        _menu->quitButtonRect.height,
        RED
    );
}

// Private definitions

void ListenMenuEvents()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();

        if (CheckCollisionPointRec(pos, _menu->startButtonRect)) {
            _menu->startGameCallback();
        } else if (CheckCollisionPointRec(pos, _menu->quitButtonRect)) {
            CloseWindow();
        }
    }
}
