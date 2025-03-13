#ifndef GAME_H_
#define GAME_H_

#define GRAVITY_X 0
#define GRAVITY_Y 800

void InitGameScreen();
void DestroyGameScreen();

void UpdateGameScreen(float dt);
void DrawGameScreen();

#endif
