#include "Ms_Interface.h"
#include "Ms_Logic.h"

// ���� ����
extern Ms_Logic logic;            // ���� ���� ��ü
extern HBITMAP hMineBitmap;       // ���� ��Ʈ�� �ڵ�
extern HBITMAP hFlagBitmap;       // ��� ��Ʈ�� �ڵ�
extern int timerCount;            // Ÿ�̸� ��

// ���� �ʱ�ȭ (��ü ���� �׸���)
void InitializeBoard(HWND hwnd, const Ms_level& level) {
    HDC hdc = GetDC(hwnd);

    int boardWidth = level.getWidth();    // ���� ���� ĭ ��
    int boardHeight = level.getHeight(); // ���� ���� ĭ ��
    int startY = 100;                     // ���� ���� Y ��ǥ (Ÿ�̸� + ��ư �Ʒ�)

    const auto& board = logic.GetBoard(); // ���� �������� ���� ���� ��������

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            int x = j * CELL_WIDTH;
            int y = i * CELL_HEIGHT + startY;

            if (board[i][j].isRevealed) {
                if (board[i][j].isMine) {
                    DrawMine(hdc, hMineBitmap, x, y); // ���� �׸���
                }
                else {
                    DrawCell(hdc, x, y, RGB(255, 255, 255)); // �� ��
                    if (board[i][j].surroundingMines > 0) {
                        WCHAR text[2];
                        swprintf_s(text, L"%d", board[i][j].surroundingMines);
                        TextOutW(hdc, x + CELL_WIDTH / 3, y + CELL_HEIGHT / 4, text, 1);
                    }
                }
            }
            else {
                if (board[i][j].isFlagged) {
                    DrawFlag(hdc, hFlagBitmap, x, y); // ��� �׸���
                }
                else {
                    DrawCell(hdc, x, y, RGB(200, 200, 200)); // ���� ��
                }
            }
        }
    }

    ReleaseDC(hwnd, hdc);
}

// UI �ʱ�ȭ (Ÿ�̸ӿ� ��ư ����)
void InitializeInterface(HWND hwnd) {
    // �ʱ�ȭ ��ư
    CreateWindowW(L"BUTTON", L"Reset", WS_VISIBLE | WS_CHILD,
        10, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_RESET, GetModuleHandle(NULL), NULL);

    // Ÿ�̸� ǥ��
    CreateWindowW(L"STATIC", L"Time: 0", WS_VISIBLE | WS_CHILD | SS_CENTER,
        400, 10, 120, 30, hwnd, (HMENU)ID_TIMER, GetModuleHandle(NULL), NULL);

    // Ÿ�̸� ����
    SetTimer(hwnd, ID_TIMER, 1000, NULL); // 1�� �������� Ÿ�̸� ����
}

// ���� �� �׸��� (ȸ�� ��, �⺻ ���� ����)
void DrawCell(HDC hdc, int x, int y, COLORREF color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    RECT rect = { x, y, x + CELL_WIDTH, y + CELL_HEIGHT };
    FillRect(hdc, &rect, hBrush);
    FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH)); // �׵θ�

    DeleteObject(hBrush);
}

// ��Ʈ�� ���� �̹����� �׸��� �Լ�
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y) {
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

// ��Ʈ�� ��� �̹����� �׸��� �Լ�
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y) {
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}
