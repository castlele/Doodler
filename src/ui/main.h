#ifndef MAIN_H_
#define MAIN_H_

void InitMainScreen(void (*startGame)(void));
void DestroyMainScreen();

void UpdateMainScreen(float dt);
void DrawMainScreen();

#endif
