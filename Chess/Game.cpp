#include "Game.h"

using namespace std;

Game::Game() {
    wm.SetWindowSize(10, 11);
    wm.SetFontSize(72);
    wm.SetCursorVisibility(false);
    wm.SetScreenColor(wm.FG_BLACK);
    white[0].color = wm.FG_WHITE;
    black[0].color = wm.FG_BLACK;
    player1 = true;
    gameOver = false;
    player1X = 4;
    player1Y = 7;
    player2X = 4;
    player2Y = 0;
    InitBoard();
    PrintBoard();
    PrintPieces();
}

void Game::GameLoop() {
    while (!gameOver) {
        if (player1) {
            TakeTurn(white, black, player1X, player1Y, player1);
        }
        else {
            TakeTurn(black, white, player2X, player2Y, player1);
        }
        wm.SetCursorPosition(0, 10);
        wm.SetTextColor(wm.FG_WHITE);
        if (IsInCheck(white, black) || IsInCheck(black, white)) {
            fputs("CHECK", stdout);
            if (IsInCheckMate(white, black) || IsInCheckMate(black, white)) {
                gameOver = true;
            }
        }
        else {
            fputs("     ", stdout);
        }
    }
    fputs("MATE", stdout);
    _getch();
}

void Game::PrintBoard() {
    int cursorY = 0;
    wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
    wm.SetCursorPosition(0, cursorY);
    putchar(201);
    for (int i = 0; i < 8; ++i) {
        putchar(205);
    }
    putchar(187);
    wm.SetCursorPosition(0, ++cursorY);
    for (int i = 0; i < 4; ++i) {
        wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
        putchar(186);
        for (int j = 0; j < 4; ++j) {
            wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
            putchar(' ');
            wm.SetTextColor(wm.FG_BLACK | wm.BG_BLACK);
            putchar(' ');
        }
        wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
        putchar(186);
        wm.SetCursorPosition(0, ++cursorY);
        wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
        putchar(186);
        for (int j = 0; j < 4; ++j) {
            wm.SetTextColor(wm.FG_BLACK | wm.BG_BLACK);
            putchar(' ');
            wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
            putchar(' ');
        }
        wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
        putchar(186);
        wm.SetCursorPosition(0, ++cursorY);
    }
    putchar(200);
    for (int i = 0; i < 8; ++i) {
        putchar(205);
    }
    putchar(188);
}

void Game::InitBoard() {
    for (int pawn = 0; pawn < 8; ++pawn) {
        white[pawn].rank = 'P';
        white[pawn].x = pawn;
        white[pawn].y = 6;
        black[pawn].rank = 'P';
        black[pawn].x = pawn;
        black[pawn].y = 1;
    }
    white[8].rank = 'R';
    white[8].x = 0;
    white[8].y = 7;
    white[9].rank = 'R';
    white[9].x = 7;
    white[9].y = 7;
    black[8].rank = 'R';
    black[8].x = 0;
    black[8].y = 0;
    black[9].rank = 'R';
    black[9].x = 7;
    black[9].y = 0;
    white[10].rank = 'N';
    white[10].x = 1;
    white[10].y = 7;
    white[11].rank = 'N';
    white[11].x = 6;
    white[11].y = 7;
    black[10].rank = 'N';
    black[10].x = 1;
    black[10].y = 0;
    black[11].rank = 'N';
    black[11].x = 6;
    black[11].y = 0;
    white[12].rank = 'B';
    white[12].x = 2;
    white[12].y = 7;
    white[13].rank = 'B';
    white[13].x = 5;
    white[13].y = 7;
    black[12].rank = 'B';
    black[12].x = 2;
    black[12].y = 0;
    black[13].rank = 'B';
    black[13].x = 5;
    black[13].y = 0;
    white[14].rank = 'Q';
    white[14].x = 3;
    white[14].y = 7;
    black[14].rank = 'Q';
    black[14].x = 3;
    black[14].y = 0;
    white[15].rank = 'K';
    white[15].x = 4;
    white[15].y = 7;
    black[15].rank = 'K';
    black[15].x = 4;
    black[15].y = 0;
}

void Game::PrintPieces() {
    for (int i = 0; i < 16; ++i) {
        if (white[i].y % 2 == white[i].x % 2) {
            wm.SetTextColor(wm.FG_WHITE | wm.BG_WHITE);
        }
        else {
            wm.SetTextColor(wm.FG_WHITE | wm.BG_BLACK);
        }
        if (!(white[i].x == -1 && white[i].y == -1)) {
            wm.SetCursorPosition(white[i].x + 1, white[i].y + 1);
            putchar(white[i].rank);
        }
    }
    for (int i = 0; i < 16; ++i) {
        if (black[i].y % 2 == black[i].x % 2) {
            wm.SetTextColor(wm.FG_BLACK | wm.BG_WHITE);
        }
        else {
            wm.SetTextColor(wm.FG_BLACK | wm.BG_BLACK);
        }
        if (!(black[i].x == -1 && black[i].y == -1)) {
            wm.SetCursorPosition(black[i].x + 1, black[i].y + 1);
            putchar(black[i].rank);
        }
    }
}

void Game::PrintPieceAt(int x, int y, bool holding, Piece held) {
    wm.SetCursorPosition(x + 1, y + 1);
    int color;
    int rank = ' ';
    if (y % 2 == x % 2) {
        color = wm.BG_WHITE;
    }
    else {
        color = wm.BG_BLACK;
    }
    for (int i = 0; i < 16; ++i) {
        if (white[i].x == x && white[i].y == y) {
            if (!(holding && (x == held.x && y == held.y))) {
                color |= wm.FG_WHITE;
                rank = white[i].rank;
            }
            break;
        }
        if (black[i].x == x && black[i].y == y) {
            if (!(holding && (x == held.x && y == held.y))) {
                color |= wm.FG_BLACK;
                rank = black[i].rank;
            }
            break;
        }
    }
    wm.SetTextColor(color);
    putchar(rank);
}

void Game::PrintCursorAt(int x, int y, bool holding, Piece held, int color) {
    wm.SetCursorPosition(x + 1, y + 1);
    int rank = ' ';
    if (holding) {
        color &= wm.FG_WHITE | FOREGROUND_INTENSITY;
        color |= wm.BG_RED;
        rank = held.rank;
    }
    else {
        color &= wm.BG_WHITE | BACKGROUND_BLUE;
        for (int i = 0; i < 16; ++i) {
            if (white[i].x == x && white[i].y == y) {
                color |= wm.FG_WHITE;
                rank = white[i].rank;
                break;
            }
            if (black[i].x == x && black[i].y == y) {
                color |= wm.FG_BLACK;
                rank = black[i].rank;
                break;
            }
        }
    }
    wm.SetTextColor(color);
    putchar(rank);
}

bool Game::IsPieceAt(int x, int y) {
    for (int i = 0; i < 16; ++i) {
        if ((white[i].x == x && white[i].y == y) ||
            (black[i].x == x && black[i].y == y)) {
            return true;
        }
    }
    return false;
}

bool Game::IsPieceAt(int x, int y, Piece team[]) {
    for (int i = 0; i < 16; ++i) {
        if (team[i].x == x && team[i].y == y) {
            return true;
        }
    }
    return false;
}


bool Game::IsPieceBetween(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        if (y2 < y1) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (int i = y1 + 1; i < y2; ++i) {
            if (IsPieceAt(x1, i)) {
                return true;
            }
        }
    }
    else if (y1 == y2) {
        if (x2 < x1) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (int i = x1 + 1; i < x2; ++i) {
            if (IsPieceAt(i, y1)) {
                return true;
            }
        }
    }
    else if (abs(x1 - x2) == abs(y1 - y2)) {
        if (x1 < x2 && y1 < y2) {
            for (int xi = x1 + 1, yi = y1 + 1; xi < x2; ++xi, ++yi) {
                if (IsPieceAt(xi, yi)) {
                    return true;
                }
            }
        }
        else if (x1 < x2 && y1 > y2) {
            for (int xi = x1 + 1, yi = y1 - 1; xi < x2; ++xi, --yi) {
                if (IsPieceAt(xi, yi)) {
                    return true;
                }
            }
        }
        else if (x1 > x2 && y1 < y2) {
            for (int xi = x1 - 1, yi = y1 + 1; xi > x2; --xi, ++yi) {
                if (IsPieceAt(xi, yi)) {
                    return true;
                }
            }
        }
        else { // if (x1 > x2 && y1 > y2) {
            for (int xi = x1 - 1, yi = y1 - 1; xi > x2; --xi, --yi) {
                if (IsPieceAt(xi, yi)) {
                    return true;
                }
            }
        }
    }
    else {
        // ???
    }
    return false;
}

int Game::PieceAt(int x, int y) {
    for (int i = 0; i < 16; ++i) {
        if (white[i].x == x && white[i].y == y) {
            return i;
        }
        if (black[i].x == x && black[i].y == y) {
            return i;
        }
    }
    return 0;
}

void Game::HighlightMoves(Piece player[], Piece opp[], int piece) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (CanMove(player, opp, piece, x, y) && !WillCauseCheck(player, opp, piece, x, y)) {
                if (IsPieceAt(x, y, opp)) {
                    PrintCursorAt(x, y, false, player[piece], wm.BG_RED);
                }
                else {
                    PrintCursorAt(x, y, false, player[piece], wm.BG_GREEN);
                }
            }
        }
    }
}

void Game::TakeTurn(Piece player[], Piece opp[], int &cursorX, int &cursorY, bool &player1) {
    bool holding = false;
    int held = 0;
    PrintCursorAt(cursorX, cursorY, holding, player[held], player[0].color | wm.BG_BLUE);
    while (true) {
        if (_kbhit()) {
            int key = tolower(_getch());
            if (key == 'a') {
                if (cursorX > 0) {
                    PrintPieceAt(cursorX, cursorY, holding, player[held]);
                    --cursorX;
                    if (holding) {
                        HighlightMoves(player, opp, held);
                    }
                    PrintCursorAt(cursorX, cursorY, holding, player[held], player[0].color | wm.BG_BLUE);
                }
            }
            else if (key == 'd') {
                if (cursorX < 7) {
                    PrintPieceAt(cursorX, cursorY, holding, player[held]);
                    ++cursorX;
                    if (holding) {
                        HighlightMoves(player, opp, held);
                    }
                    PrintCursorAt(cursorX, cursorY, holding, player[held], player[0].color | wm.BG_BLUE);
                }
            }
            else if (key == 'w') {
                if (cursorY > 0) {
                    PrintPieceAt(cursorX, cursorY, holding, player[held]);
                    --cursorY;
                    if (holding) {
                        HighlightMoves(player, opp, held);
                    }
                    PrintCursorAt(cursorX, cursorY, holding, player[held], player[0].color | wm.BG_BLUE);
                }
            }
            else if (key == 's') {
                if (cursorY < 7) {
                    PrintPieceAt(cursorX, cursorY, holding, player[held]);
                    ++cursorY;
                    if (holding) {
                        HighlightMoves(player, opp, held);
                    }
                    PrintCursorAt(cursorX, cursorY, holding, player[held], player[0].color | wm.BG_BLUE);
                }
            }
            else if (key == '\r') {
                if (holding) {
                    if (CanMove(player, opp, held, cursorX, cursorY) &&
                        !WillCauseCheck(player, opp, held, cursorX, cursorY)) {
                        if (IsPieceAt(cursorX, cursorY, opp)) {
                            int oppPiece = PieceAt(cursorX, cursorY);
                            opp[oppPiece].x = -1;
                            opp[oppPiece].y = -1;
                        }
                        holding = false;
                        player[held].x = cursorX;
                        player[held].y = cursorY;
                        if (player[held].rank == 'P' && (cursorY == 0 || cursorY == 7)) {
                            player[held].rank = 'Q';
                        }
                        PrintBoard();
                        PrintPieces();
                        player1 = !player1;
                        break;
                    }
                }
                else {
                    if (IsPieceAt(cursorX, cursorY, player)) {
                        held = PieceAt(cursorX, cursorY);
                        holding = true;
                        HighlightMoves(player, opp, held);
                        PrintCursorAt(cursorX, cursorY, holding, player[held], player[0].color | wm.BG_BLUE);
                    }
                }
            }
            else if (key == 'x') {  
                if (holding) {
                    holding = false;
                    PrintBoard();
                    PrintPieces();
                    PrintCursorAt(cursorX, cursorY, holding, player[held], player[0].color | wm.BG_BLUE);
                }

            }
        }
    }
}

bool Game::CanMove(Piece player[], Piece opp[], int piece, int x, int y) {
    bool canMove = false;
    switch (player[piece].rank) {
    case 'P': {
                  int direction = (player[0].color == wm.FG_WHITE) ? -1 : 1;
                  if (x == player[piece].x &&
                      y == player[piece].y + direction &&
                      !IsPieceAt(x, y)) {
                      canMove = true;
                  }
                  if ((x == player[piece].x + 1 || x == player[piece].x - 1) &&
                      y == player[piece].y + direction &&
                      IsPieceAt(x, y, opp)) {
                      canMove = true;
                  }
                  if (x == player[piece].x &&
                      abs(y - player[piece].y) == 2 &&
                      (player[piece].y == 1 || player[piece].y == 6) &&
                      !IsPieceAt(x, y)) {
                      canMove = true;
                  }
                  break;
    }
    case 'R': {
                  if ((x == player[piece].x || y == player[piece].y) &&
                      !IsPieceBetween(x, y, player[piece].x, player[piece].y) &&
                      !IsPieceAt(x, y, player)) {
                      canMove = true;
                  }
                  break;
    }
    case 'N': {
                  if (((abs(x - player[piece].x) == 1 && abs(y - player[piece].y) == 2) ||
                      (abs(x - player[piece].x) == 2 && abs(y - player[piece].y) == 1)) &&
                      !IsPieceAt(x, y, player)) {
                      canMove = true;
                  }
                  break;
    }
    case 'B': {
                  if (abs(x - player[piece].x) == abs(y - player[piece].y) &&
                      !IsPieceBetween(x, y, player[piece].x, player[piece].y) &&
                      !IsPieceAt(x, y, player)) {
                      canMove = true;
                  }
                  break;
    }
    case 'Q': {
                  if ((x == player[piece].x || y == player[piece].y) &&
                      !IsPieceBetween(x, y, player[piece].x, player[piece].y) &&
                      !IsPieceAt(x, y, player)) {
                      canMove = true;
                  }
                  if (abs(x - player[piece].x) == abs(y - player[piece].y) &&
                      !IsPieceBetween(x, y, player[piece].x, player[piece].y) &&
                      !IsPieceAt(x, y, player)) {
                      canMove = true;
                  }
                  break;
    }
    case 'K': {
                  if (abs(x - player[piece].x) <= 1 &&
                      abs(y - player[piece].y) <= 1 &&
                      !IsPieceAt(x, y, player)) {
                      canMove = true;
                  }
                  break;
    }
    default: {
                 break;
    }
    }
    return canMove;
}

bool Game::IsInCheck(Piece player[], Piece opp[]) {
    for (int i = 0; i < 16; ++i) {
        if (CanMove(opp, player, i, player[15].x, player[15].y)) {
            return true;
        }
    }
    return false;
}

bool Game::IsInCheckMate(Piece player[], Piece opp[]) {
    if (IsInCheck(player, opp)) {
        for (int i = 0; i < 16; ++i) {
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    if (CanMove(player, opp, i, x, y) && !WillCauseCheck(player, opp, i, x, y)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

bool Game::WillCauseCheck(Piece player[], Piece opp[], int piece, int x, int y) {
    bool check;
    int tempPlayerX = player[piece].x;
    int tempPlayerY = player[piece].y;
    int oppPiece = -1;
    int tempOppX;
    int tempOppY;
    if (IsPieceAt(x, y, opp)) {
        oppPiece = PieceAt(x, y);
        tempOppX = opp[oppPiece].x;
        tempOppY = opp[oppPiece].y;
        opp[oppPiece].x = -1;
        opp[oppPiece].y = -1;
    }
    player[piece].x = x;
    player[piece].y = y;
    check = IsInCheck(player, opp);
    player[piece].x = tempPlayerX;
    player[piece].y = tempPlayerY;
    if (oppPiece >= 0) {
        opp[oppPiece].x = tempOppX;
        opp[oppPiece].y = tempOppY;
    }
    return check;
}
