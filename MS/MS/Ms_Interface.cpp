#include "Ms_Interface.h"

// 보드 초기화
void InitializeBoard(HWND hwnd, const Ms_level& level) {
    HDC hdc = GetDC(hwnd);

    int boardWidth = level.getWidth();    // 보드의 가로 칸 수
    int boardHeight = level.getHeight(); // 보드의 세로 칸 수

    // 셀 초기화: 회색 셀 그리기
    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            int x = j * CELL_WIDTH;
            int y = i * CELL_HEIGHT;
            DrawCell(hdc, x, y, RGB(200, 200, 200)); // 회색 배경 셀
        }
    }

    ReleaseDC(hwnd, hdc);
}
// 버튼 및 타이머 초기화
void InitializeInterface(HWND hwnd) {
    // 버튼 생성
    CreateWindowW(L"BUTTON", L"Easy", WS_VISIBLE | WS_CHILD,
        10, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_EASY, GetModuleHandle(NULL), NULL);
    CreateWindowW(L"BUTTON", L"Normal", WS_VISIBLE | WS_CHILD,
        100, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_NORMAL, GetModuleHandle(NULL), NULL);
    CreateWindowW(L"BUTTON", L"Hard", WS_VISIBLE | WS_CHILD,
        190, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_HARD, GetModuleHandle(NULL), NULL);
    CreateWindowW(L"BUTTON", L"Reset", WS_VISIBLE | WS_CHILD,
        280, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_RESET, GetModuleHandle(NULL), NULL);

    // 타이머 시작
    SetTimer(hwnd, ID_TIMER, 1000, NULL); // 1초 간격으로 타이머 설정
}

// 단일 셀 그리기
void DrawCell(HDC hdc, int x, int y, COLORREF color) {
    HBRUSH hBrush = CreateSolidBrush(color);
    RECT rect = { x, y, x + CELL_WIDTH, y + CELL_HEIGHT };
    FillRect(hdc, &rect, hBrush);
    FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH)); // 테두리

    DeleteObject(hBrush);
}

// 비트맵 지뢰 이미지를 그리는 함수
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y) {
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

// 비트맵 깃발 이미지를 그리는 함수
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y) {
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}
