#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;

#define DBLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define DWHITE 15

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void SetClr2(int tcl, int bcl)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}

enum colour { White, Black };
struct position
{
    int ri, ci;
};

void init(char**& B, char X[][9], char Y[][9], int& dim, string Ns[], int& turn)
{
    ifstream rdr("text.txt");
    rdr >> dim;
    B = new char* [dim];
    for (int ri = 0; ri < dim; ri++)
        B[ri] = new char[dim];

    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
            rdr >> B[ri][ci];
    }
    for (int r = 0; r <= 2; r++)
    {
        for (int c = 0; c <= 9; c += 1)
        {
            X[r][c] = '-';
            Y[r][c] = '-';
        }
    }
    cout << "Enter Name of 1st player : ";
    cin >> Ns[0];
    cout << "Enter Name of 2nd player : ";
    cin >> Ns[1];
    cout << endl << endl;
    turn = White;
}

void drawPawn(int r, int c)
{
    char sym = -37;
    gotoRowCol(r - 1, c + 1);
    cout << sym;
    gotoRowCol(r, c - 1);
    cout << sym << sym << sym << sym << sym;
    gotoRowCol(r + 1, c);
    cout << sym << sym << sym;
    gotoRowCol(r + 2, c - 1);
    cout << sym << sym << sym << sym << sym;
}

void drawKing(int r, int c)
{
    char sym = -37;
    gotoRowCol(r, c - 1);
    cout << sym << " " << sym << " " << sym;
    gotoRowCol(r + 1, c - 1);
    cout << sym << sym << sym << sym << sym;
    gotoRowCol(r + 2, c - 1);
    cout << sym << " " << sym << " " << sym;
    gotoRowCol(r + 3, c - 1);
    cout << sym << sym << sym << sym << sym;
}

void drawLance(int r, int c)
{
    char sym = -37;
    gotoRowCol(r - 1, c + 1);
    cout << sym;
    gotoRowCol(r, c);
    cout << sym << sym << sym;
    gotoRowCol(r + 1, c - 1);
    cout << sym << sym << sym << sym << sym;
    gotoRowCol(r + 2, c - 1);
    cout << sym << sym << sym << sym << sym;
    gotoRowCol(r + 3, c - 1);
    cout << sym << sym << sym << sym << sym;
}

void drawKnight(int r, int c)
{
    char sym = -37;
    gotoRowCol(r - 1, c + 1);
    cout << sym;
    gotoRowCol(r, c);
    cout << sym << sym << sym;
    gotoRowCol(r + 1, c - 1);
    cout << sym << sym << "  " << sym;
    gotoRowCol(r + 2, c - 1);
    cout << sym << sym << sym;
    gotoRowCol(r + 3, c - 1);
    cout << sym << sym << sym << sym;

}

void drawSG(int r, int c)
{
    char sym = -37;
    gotoRowCol(r - 1, c + 1);
    cout << sym;
    gotoRowCol(r, c);
    cout << sym << " " << sym;
    gotoRowCol(r + 1, c - 1);
    cout << sym << sym << sym << sym << sym;
    gotoRowCol(r + 2, c);
    cout << sym << " " << sym;
    gotoRowCol(r + 3, c - 1);
    cout << sym << sym << sym << sym << sym;
}

void drawGG(int r, int c)
{
    char sym = -37;
    gotoRowCol(r - 1, c + 1);
    cout << sym;
    gotoRowCol(r, c);
    cout << sym << " " << sym;
    gotoRowCol(r + 1, c - 1);
    cout << sym << "   " << sym;
    gotoRowCol(r + 2, c);
    cout << sym << " " << sym;
    gotoRowCol(r + 3, c - 1);
    cout << sym << sym << sym << sym << sym;
}

void drawBishop(int r, int c)
{
    char sym = -37;
    gotoRowCol(r - 1, c + 1);
    cout << sym;
    gotoRowCol(r, c);
    cout << sym << sym << sym;
    gotoRowCol(r + 1, c + 1);
    cout << sym;
    gotoRowCol(r + 2, c);
    cout << sym << sym << sym;
    gotoRowCol(r + 3, c - 1);
    cout << sym << sym << sym << sym << sym;
}

void drawRook(int r, int c)
{
    char sym = -37;
    gotoRowCol(r - 1, c - 1);
    cout << sym << " " << sym << " " << sym;
    gotoRowCol(r, c - 1);
    cout << sym << sym << sym << sym << sym;
    gotoRowCol(r + 1, c - 1);
    cout << " " << sym << " " << sym;
    gotoRowCol(r + 2, c - 1);
    cout << " " << sym << sym << sym;
    gotoRowCol(r + 3, c - 1);
    cout << sym << sym << sym << sym << sym;
}

void drawPieces(char sym, int r, int c)
{
    switch (sym)
    {
    case 'p':
    case 'P':
    case 'A':
    case 'a':
        return drawPawn(r, c);

    case 'b':
    case 'B':
    case 'H':
    case 'h':
        return  drawBishop(r, c);

    case 'r':
    case 'R':
    case 'F':
    case 'f':
        return drawRook(r, c);

    case 'l':
    case 'L':
    case 'C':
    case 'c':
        return drawLance(r, c);

    case 'n':
    case 'N':
    case 'D':
    case 'd':
        return drawKnight(r, c);

    case 's':
    case 'S':
    case 'E':
    case 'e':
        return drawSG(r, c);

    case 'g':
    case 'G':
        return drawGG(r, c);

    case 'k':
    case 'K':
        return drawKing(r, c);
    }
}

bool isBlack(char p)
{
    if (p >= 'a' && p <= 'z')
        return true;
    return false;
}

bool isWhite(char p)
{
    if (p >= 'A' && p <= 'Z')
        return true;
    return false;
}

bool isMyPiece(char sym, int  turn)
{
    if (turn == Black)
        return isBlack(sym);
    return isWhite(sym);
}

void selectPos(position& p, int row, int col)
{
    int r, c;
    getRowColbyLeftClick(r, c);
    p.ri = (r / row) - 1;
    p.ci = (c / col);
    cout << char(p.ci + 'A') << p.ri + 1;
}

bool isValidSrc(char** B, int dim, position sc, int turn)
{
    if (sc.ri < 0 || sc.ri > dim || sc.ci < 0 || sc.ci > dim)
        return false;
    return (isMyPiece(B[sc.ri][sc.ci], turn));
}

bool isValidDes(char** B, int dim, position dc, int turn)
{
    if (dc.ri < 0 || dc.ri > dim || dc.ci < 0 || dc.ci > dim)
        return false;
    return (!isMyPiece(B[dc.ri][dc.ci], turn));
}

void updateBoard(char** B, position sc, position dc)
{
    char p = B[sc.ri][sc.ci];
    B[dc.ri][dc.ci] = p;
    B[sc.ri][sc.ci] = '-';
}

void changeTurn(int& turn)
{
    if (turn == White)
        turn = Black;
    else
        turn = White;
}

void Turn(string Ns, int turn)
{
    if (turn == White)
        SetClr(4);
    else
        SetClr(9);
    cout << "\n\n\n\n\n\n";
    cout << Ns << "`s Turn\n\n";
}

void Box(char** B, int row, int col, int para, int a, int b)
{
    col -= 5, row += 1;
    char sym = -37;
    for (int i = 0; i < para; i++)
    {
        gotoRowCol(row, col++);
        cout << sym;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(row++, col);
        cout << sym;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(row, col--);
        cout << sym;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(row--, col);
        cout << sym;
    }
    if (isWhite(B[a][b]))
        SetClr(4);
    else if (isBlack(B[a][b]))
        SetClr(9);
    if (para != 6)
        drawPieces(B[a][b], row + 3, col + 3);
}

void label(int r, int c)
{
    int X[10] = { 1,2,3,4,5,6,7,8,9 };
    char Y[10] = { 'A','B','C','D','E','F','G','H','I' };
    SetClr(7);
    for (int i = 0; i <= 9; i++)
    {
        gotoRowCol(r - 1, c - 1);
        cout << Y[i];
        c += 8;
    }
    for (int i = 0; i < 9; i++)
    {
        gotoRowCol(r + 4, c - 87);
        cout << X[i];
        r += 8;
    }
}

void mainBoard(char** B, int dim)
{
    label(8, 8);
    for (int r = 1; r <= dim; r++)
    {
        for (int c = 1; c <= dim; c++)
        {
            SetClr(7);
            Box(B, r * 8, c * 8, 8, r - 1, c - 1);
        }
    }
    gotoRowCol(80, 100);
    SetClr2(0, 15);
    cout << " UNDO ";
}

bool isHorizontal(position sc, position dc)
{
    return sc.ri == dc.ri;
}

bool isVertical(position sc, position dc)
{
    return sc.ci == dc.ci;
}

bool isDiagonal(position sc, position dc)
{
    int Dr = abs(sc.ri - dc.ri);
    int Dc = abs(sc.ci - dc.ci);
    return Dr == Dc;
}

bool isHorizonPathClr(char** B, position sc, position dc)
{
    int cs, ce;
    if (sc.ci < dc.ci)
    {
        cs = sc.ci + 1;
        ce = dc.ci - 1;
    }
    else
    {
        cs = dc.ci + 1;
        ce = sc.ci - 1;
    }

    for (int c = cs; c <= ce; c++)
    {
        if (B[sc.ri][c] != '-')
            return false;
    }
    return true;
}

bool isVerticalPathClr(char** B, position sc, position dc)
{
    int cs, ce;
    if (sc.ri < dc.ri)
    {
        cs = sc.ri + 1;
        ce = dc.ri - 1;
    }
    else
    {
        cs = dc.ri + 1;
        ce = sc.ri - 1;
    }   
    for (int r = cs; r <= ce; r++)
    {
        if (B[r][sc.ci] != '-')
            return false;
    }
    return true;
}

bool isDiagonalPathClrL2R(char** B, position sc, position dc)
{
    if (sc.ri < dc.ri)
    {
        int Dr = dc.ri - sc.ri - 1;
        for (int i = 1; i <= Dr; i++)
        {
            if (B[sc.ri + i][sc.ci + i] != '-')
                return false;
        }
        return true;
    }
    else
    {
        int Dr = sc.ri - dc.ri - 1;
        for (int i = 1; i <= Dr; i++)
        {
            if (B[sc.ri - i][sc.ci + i] != '-')
                return false;
        }
        return true;
    }
}

bool isDiagonalPathClrR2L(char** B, position sc, position dc)
{
    if (sc.ri < dc.ri)
    {
        int Dr = dc.ri - sc.ri - 1;
        for (int i = 0; i <= Dr; i++)
        {
            if (B[sc.ri - i][sc.ci - i] != '-')
                return false;
        }
        return true;
    }
    else
    {
        int Dr = sc.ri - dc.ri - 1;
        for (int i = 1; i <= Dr; i++)
        {
            if (B[sc.ri + i][sc.ci - i] != '-')
                return false;
        }
        return true;
    }
}

bool rookLegality(char** B, position Sc, position Dc)
{
    return ((isHorizontal(Sc, Dc) && isHorizonPathClr(B, Sc, Dc)) || (isVertical(Sc, Dc) && isVerticalPathClr(B, Sc, Dc)));
}

bool bishopLegality(char** B, position Sc, position Dc)
{
    return (isDiagonal(Sc, Dc) && (isDiagonalPathClrL2R(B, Sc, Dc) || isDiagonalPathClrR2L(B, Sc, Dc)));
}

bool kingLegality(char** B, position Sc, position Dc)
{
    int dr = abs(Sc.ri - Dc.ri);
    int dc = abs(Sc.ci - Dc.ci);
    return ((rookLegality(B, Sc, Dc) || bishopLegality(B, Sc, Dc)) && dr <= 1 && dc <= 1);
}

bool pawnLegality(char** B, position Sc, position Dc, int Turn)
{
    int dr = abs(Sc.ri - Dc.ri);
    if (Turn == White)
        return ((Sc.ci == Dc.ci) && dr <= 1 && (Sc.ri > Dc.ri) && (rookLegality(B, Sc, Dc)));
    else
        return ((Sc.ci == Dc.ci) && dr <= 1 && (Sc.ri < Dc.ri) && (rookLegality(B, Sc, Dc)));
}

bool lancesLegality(char** B, position Sc, position Dc, int Turn)
{
    if (Turn == White)
        return ((Sc.ci == Dc.ci) && (Sc.ri > Dc.ri) && (rookLegality(B, Sc, Dc)));
    else
        return ((Sc.ci == Dc.ci) && (Sc.ri < Dc.ri) && (rookLegality(B, Sc, Dc)));
}

bool knightLegality(char** B, position Sc, position Dc, int Turn)
{
    int dr = abs(Sc.ri - Dc.ri);
    int dc = abs(Sc.ci - Dc.ci);
    if (Turn == White)
        return (dr == 2 && dc == 1 && (Sc.ri > Dc.ri));
    else
        return (dr == 2 && dc == 1 && (Sc.ri < Dc.ri));
}

bool silverGeneralLegality(char** B, position Sc, position Dc, int Turn)
{
    int dr = abs(Sc.ri - Dc.ri);
    int dc = abs(Sc.ci - Dc.ci);
    return (dr <= 1 && dc <= 1 && (pawnLegality(B, Sc, Dc, Turn) || bishopLegality(B, Sc, Dc)));
}

bool goldGeneralLegality(char** B, position Sc, position Dc, int Turn)
{
    int dr = abs(Sc.ri - Dc.ri);
    int dc = abs(Sc.ci - Dc.ci);
    if (Turn == White)
        return dr <= 1 && dc <= 1 && (rookLegality(B, Sc, Dc) || ((Sc.ri > Dc.ri) && bishopLegality(B, Sc, Dc)));
    else
        return dr <= 1 && dc <= 1 && (rookLegality(B, Sc, Dc) || ((Sc.ri < Dc.ri) && bishopLegality(B, Sc, Dc)));
}

bool IsLegalMove(char** B, position Sc, position Dc, int Dim, int Turn)
{
    switch (B[Sc.ri][Sc.ci])
    {
    case 'p':
    case 'P':
        return pawnLegality(B, Sc, Dc, Turn);

    case 'b':
    case 'B':
        return  bishopLegality(B, Sc, Dc);

    case 'r':
    case 'R':
        return rookLegality(B, Sc, Dc);

    case 'l':
    case 'L':
        return lancesLegality(B, Sc, Dc, Turn);

    case 'n':
    case 'N':
        return knightLegality(B, Sc, Dc, Turn);

    case 's':
    case 'S':
        return silverGeneralLegality(B, Sc, Dc, Turn);

    case 'k':
    case 'K':
        return kingLegality(B, Sc, Dc);

    case 'G':
    case 'g':
    case 'A':
    case 'a':
    case 'D':
    case 'd':
    case 'C':
    case 'c':
    case 'E':
    case 'e':
        return goldGeneralLegality(B, Sc, Dc, Turn);

    case 'F':
    case 'f':
        return (rookLegality(B, Sc, Dc) && kingLegality(B, Sc, Dc));

    case 'H':
    case 'h':
        return (bishopLegality(B, Sc, Dc) && kingLegality(B, Sc, Dc));
    }
}

void Promotion(char**& B, position Sc)
{
    char sym = B[Sc.ri][Sc.ci];
    if (sym == 'P' && Sc.ri < 3)
        sym = 'A';

    else if (sym == 'L' && Sc.ri < 3)
        sym = 'C';

    else if (sym == 'N' && Sc.ri < 3)
        sym = 'D';

    else if (sym == 'S' && Sc.ri < 3)
        sym = 'E';

    else if (sym == 'R' && Sc.ri < 3)
        sym = 'F';

    else if (sym == 'B' && Sc.ri < 3)
        sym = 'H';

    else if (sym == 'p' && Sc.ri > 5)
        sym = 'a';

    else if (sym == 'l' && Sc.ri > 5)
        sym = 'c';

    else if (sym == 'n' && Sc.ri > 5)
        sym = 'd';

    else if (sym == 's' && Sc.ri > 5)
        sym = 'e';

    else if (sym == 'r' && Sc.ri > 5)
        sym = 'f';

    else if (sym == 'b' && Sc.ri > 5)
        sym = 'h';
}

bool** ComputeHighlight(char** B, position& sc, int dim, int turn)
{
    bool** bMap = new bool* [dim];
    for (int bi = 0; bi < dim; bi++)
        bMap[bi] = new bool[dim] {};
    position dc;
    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
        {
            dc.ri = ri;
            dc.ci = ci;
            if ((isValidDes(B, dim, dc, turn) && IsLegalMove(B, sc, dc, dim, turn)))
                bMap[ri][ci] = true;
        }
    }
    return bMap;
}

void BoxHighlight(bool**& M, char** B, int dim, int row, int col, int turn)
{
    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
        {
            if (M[ri][ci] == true)
            {
                SetClr(2);
                Box(B, ri * row + row + 1, ci * col + col + 1, 6, ri, ci);
            }
        }
    }
    if (turn == White)
        SetClr(4);
    else
        SetClr(9);
}

void UnHighlight(bool**& M, char** B, int dim, int row, int col, int turn)
{
    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
        {
            if (M[ri][ci] == true)
            {
                SetClr(0);
                Box(B, ri * row + row + 1, ci * col + col + 1, 6, ri, ci);
            }
        }
    }
    if (turn == White)
        SetClr(4);
    else
        SetClr(9);
}

bool capture(char** B, position sc, position dc, int turn)
{
    return (!isMyPiece(B[dc.ri][dc.ci], turn) && B[dc.ri][dc.ci] != '-');
}

void RedCapture(char X[][9], int ri, int ci, int para, int a, int b)
{
    SetClr(4);
    char s = -37;
    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri, ci++);
        cout << s;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri++, ci);
        cout << s;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri, ci--);
        cout << s;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri--, ci);
        cout << s;
    }

    SetClr(9);
    if (X[a][b] == '-')
    {
        gotoRowCol(ri + 4, ci + 4);
        cout << X[a][b];
    }
    else
        drawPieces(X[a][b], ri + 3, ci + 3);
    SetClr(4);
}

void BlueCapture(char Y[][9], int ri, int ci, int para, int a, int b)
{
    SetClr(9);
    char s = -37;
    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri, ci++);
        cout << s;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri++, ci);
        cout << s;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri, ci--);
        cout << s;
    }

    for (int i = 0; i < para; i++)
    {
        gotoRowCol(ri--, ci);
        cout << s;
    }

    SetClr(4);
    if (Y[a][b] == '-')
    {
        gotoRowCol(ri + 4, ci + 4);
        cout << Y[a][b];
    }
    else
        drawPieces(Y[a][b], ri + 3, ci + 3);
    SetClr(9);
}

void capture_placement(char** B, char X[][9], char Y[][9], position dc, int turn, string Ns)
{
    int p = 0;
    if (turn == White)
    {
        SetClr(4);
        for (int r = 0; r <= 2; r++)
        {
            for (int c = 0; c <= 9; c += 1)
            {
                if (Y[r][c] == '-')
                {
                    Y[r][c] = B[dc.ri][dc.ci];
                    p = 1;
                    break;
                }
            }
            if (p == 1)
                break;
        }
        for (int r = 1, a = 0; r <= 2; r++, a++)
            for (int c = 60, b = 0; c <= 150; c += 8, b++)
                RedCapture(Y, r * 8 + 13, c, 8, a, b);
    }
    if (turn == Black)
    {
        SetClr(9);
        for (int r = 0; r <= 2; r++)
        {
            for (int c = 0; c <= 9; c += 1)
            {
                if (X[r][c] == '-')
                {
                    X[r][c] = B[dc.ri][dc.ci];
                    p = 1;
                    break;
                }
            }
            if (p == 1)
                break;
        }
        for (int r = 4, a = 0; r <= 5; r++, a++)
            for (int c = 90, b = 0; c <= 150; c += 8, b++)
                BlueCapture(X, r * 8 + 18, c, 8, a, b);
    }
    if (turn == White)
        SetClr(4);
    else
        SetClr(9);
}

void Placement(char X[][9], char Y[][9], int turn, string Ns)
{
    SetClr(4);
    gotoRowCol(12, 88);
    cout << Ns << "'s Captured pieces!";
    for (int r = 1, a = 0; r < 4; r++, a++)
        for (int c = 78, b = 0; c <= 115; c += 8, b++)
            RedCapture(Y, r * 8 + 6, c, 8, a, b);

    SetClr(9);
    gotoRowCol(44, 88);
    cout << Ns << "'s Captured pieces!";
    for (int r = 4, a = 0; r < 7; r++, a++)
        for (int c = 78, b = 0; c <= 115; c += 8, b++)
            BlueCapture(X, r * 8 + 14, c, 8, a, b);

    if (turn == White)
        SetClr(4);
    else
        SetClr(9);
}

position findKing(char** B, int dim, int turn)
{
    position dc;
    if (turn == White)
    {
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (B[i][j] == 'K')
                {
                    dc.ri = i;
                    dc.ci = j;
                    return dc;
                }
            }
        }
    }
    if (turn == Black)
    {
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (B[i][j] == 'k')
                {
                    dc.ri = i;
                    dc.ci = j;
                    return dc;
                }
            }
        }
    }
}

bool check(char** B, int dim, int turn,int sum,int count)
{
    changeTurn(turn);
    position dc, sc;
    dc = findKing(B, dim, turn);
    changeTurn(turn);
    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
        {
            sc.ri = ri;
            sc.ci = ci;
            if (isMyPiece(B[sc.ri][sc.ci], turn) && IsLegalMove(B, sc, dc, dim, turn))
                return true;
        }
    }
    return false;
}

bool selfCheck(char** B, int dim, int turn,int sum,int count)
{
    changeTurn(turn);
    return check(B, dim, turn,sum,count);
}

void save(char** B, int dim, int turn)
{
    ofstream write("text1.txt");
    write << turn;
    write << dim << endl;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            write << B[i][j];
    }
}

int main()
{
    char** B, X[2][9]{}, Y[2][9]{};
    string Ns[2];
    position sc, dc;
    int brow = 8, bcol = 8;
    bool** Map;
    int dim, turn;
    int sum = 0,count=0;
    init(B, X, Y, dim, Ns, turn);
    cout << endl;
    mainBoard(B, dim);
    while (sum !=3 || count!=3)
    {
        Turn(Ns[turn], turn);
        do
        {
            do
            {
                do
                {
                    Placement(X, Y, turn, Ns[turn]);
                    gotoRowCol(85, 0);
                    cout << "SOURCE COORDINATE: ";
                    selectPos(sc, brow, bcol);
                    if (!isValidSrc(B, dim, sc, turn))
                        cout << "\nInvalid SOURCE selection..!!!\n";
                } while (!isValidSrc(B, dim, sc, turn));
                Promotion(B, sc);
                Map = ComputeHighlight(B, sc, dim, turn);
                BoxHighlight(Map, B, dim, brow, bcol, turn);
                gotoRowCol(86, 0);
                cout << "\nDESTINATION COORDINATE: ";
                selectPos(dc, brow, bcol);
                UnHighlight(Map, B, dim, brow, bcol, turn);
                if (!isValidDes(B, dim, dc, turn))
                {
                    gotoRowCol(88, 0);
                    cout << "Invalid DESTINATION selection..!!!\n";
                }
            } while (!isValidDes(B, dim, dc, turn));
            if (!Map[dc.ri][dc.ci])
            {
                gotoRowCol(88, 0);
                cout << "Invalid MOVE...!!!\n";
            }
        } while (!Map[dc.ri][dc.ci]);
        if (IsLegalMove(B, sc, dc, dim, turn) && capture(B, sc, dc, turn))
            capture_placement(B, X, Y, dc, turn, Ns[turn]);
        updateBoard(B, sc, dc);
        system("cls");
        mainBoard(B, dim);
        save(B, dim, turn);
        if (check(B, dim, turn, sum, count))
        {
            gotoRowCol(70, 95);
            cout << "check";
           
            if (turn == White)
            {
                sum++;
                if (sum == 4)
                {
                    gotoRowCol(72, 95);
                    cout << turn << "LOSES";
                }
            }
            else if (turn == Black)
            {
                count++;
                if (count == 4)
                    cout << turn << "LOSES";
            }
        }
        changeTurn(turn);
    }
    return _getch();
}