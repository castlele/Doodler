#ifndef PLATFORM_H_
#define PLATFORM_H_

typedef struct Platform
{
    int x;
    int y;
} Platform;

int GetPlatformWidth();
int GetPlatformHeight();

Platform CreatePlatform(int x, int y);
void UpdatePlatform(Platform *p);
void DrawPlatform(Platform *p);

#endif
