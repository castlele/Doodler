#ifndef APPLICATION_H_
#define APPLICATION_H_

typedef enum AppState
{
    AppStateMain,
    AppStateGame,
} AppState;

void InitApplication();
void RunApplication();

#endif
