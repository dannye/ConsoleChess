#include "WinManip.h"

WinManip::WinManip() {
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void WinManip::SetWindowSize(int width, int height)
{
    SMALL_RECT window;
    window.Top = 0;
    window.Left = 0;
    window.Bottom = height - 1;
    window.Right = width - 1;
    SetConsoleWindowInfo(handle, TRUE, &window);
    COORD buffer = { (SHORT)width, (SHORT)height };
    SetConsoleScreenBufferSize(handle, buffer);
}

void WinManip::SetCursorVisibility(bool show)
{
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(handle, &cursor);
    cursor.bVisible = show;
    SetConsoleCursorInfo(handle, &cursor);
}

void WinManip::SetCursorPosition(int x, int y)
{
    COORD cursor = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(handle, cursor);
}

void WinManip::SetTextColor(int color)
{
    SetConsoleTextAttribute(handle, color);
}

void WinManip::SetScreenColor(int color)
{
    COORD coord = { 0,0 };
    DWORD dwWritten;
    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color, 10 * 11, coord, &dwWritten);
}

void WinManip::SetFontSize(int size)
{
    CONSOLE_FONT_INFOEX font = { 0 };
    font.cbSize = sizeof(font);
    font.dwFontSize.Y = size;
    font.FontWeight = FW_NORMAL;
    wcscpy_s(font.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(handle, false, &font);
}
