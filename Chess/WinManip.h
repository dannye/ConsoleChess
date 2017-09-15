#include <Windows.h>

class WinManip {

public:
    const int FG_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    const int BG_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    const int FG_BLACK = 0;
    const int BG_BLACK = BACKGROUND_RED | BACKGROUND_GREEN;
    const int BG_RED = BACKGROUND_RED | BACKGROUND_INTENSITY;
    const int BG_GREEN = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    const int BG_BLUE = BACKGROUND_BLUE | BACKGROUND_INTENSITY;

private:
    HANDLE handle;

public:
    WinManip();
    void SetWindowSize(int height, int width);
    void SetCursorVisibility(bool show);
    void SetCursorPosition(int y, int x);
    void SetTextColor(int color);
    void SetScreenColor(int color);
    void SetFontSize(int sizeY);
};
