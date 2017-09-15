#include <stdio.h>
#include <conio.h>
#include "WinManip.h"

class Game {

private:
    struct Piece{
        int rank;
        int x, y;
        int color;
    };

    Piece white[16];
    Piece black[16];

    WinManip wm;

    bool player1;
    bool gameOver;
    int player1X;
    int player1Y;
    int player2X;
    int player2Y;

public:
    Game();
    void GameLoop();
    void PrintBoard();
    void InitBoard();
    void PrintPieces();
    void PrintPieceAt(int x, int y, bool holding, Piece held);
    void PrintCursorAt(int x, int y, bool holding, Piece held, int color);
    bool IsPieceAt(int x, int y);
    bool IsPieceAt(int x, int y, Piece team[]);
    bool IsPieceBetween(int x1, int y1, int x2, int y2);
    int PieceAt(int x, int y);
    void HighlightMoves(Piece player[], Piece opp[], int piece);
    void TakeTurn(Piece player[], Piece opp[], int &cursorX, int &cursorY, bool &player1);
    bool IsInCheck(Piece player[], Piece opp[]);
    bool IsInCheckMate(Piece player[], Piece opp[]);
    bool CanMove(Piece player[], Piece opp[], int piece, int x, int y);
    bool WillCauseCheck(Piece player[], Piece opp[], int piece, int x, int y);
};
