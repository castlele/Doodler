#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "score.h"

int _score = 0;
int _level = 1;

int GetScore()
{
    return _score;
}

void UpdateScore(int currentY, int playerH)
{
    int pos = currentY + playerH / 2;

    if (pos > GetScreenHeight()) {
        _level = 1;
        _score = 0;
        return;
    }

    if (pos < 0) {
        _level++;
    }

    _score = fmax(
        (GetScreenHeight() - currentY) * _level,
        _score
    );
}

void DrawScore()
{
    char scoreMessage[64];
    sprintf(scoreMessage, "SCORE: %d", _score);

    DrawText(scoreMessage, GetScreenWidth() / 2, 0, 32, BLACK);
}
