#include "Ms_Interface.h"

// ���� �ʱ�ȭ
void InitializeBoard(HWND hwnd, const Ms_level& level) {
    HDC hdc = GetDC(hwnd);

    int boardWidth = level.getWidth();    // ������ ���� ĭ ��
    int boardHeight = level.getHeight(); // ������ ���� ĭ ��

    // �� �ʱ�ȭ: ȸ�� �� �׸���
    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            int x = j * CELL_WIDTH;
            int y = i * CELL_HEIGHT;
            DrawCell(hdc, x, y, RGB(200, 200, 200)); // ȸ�� ��� ��
        }
    }

    ReleaseDC(hwnd, hdc);
}

// ���� �� �׸���
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
