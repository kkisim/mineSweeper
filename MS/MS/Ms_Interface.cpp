#include "Ms_Interface.h"
#include "Ms_Logic.h"

// 전역 변수
extern Ms_Logic logic;            // 게임 로직 객체
extern HBITMAP hMineBitmap;       // 지뢰 비트맵 핸들
extern HBITMAP hFlagBitmap;       // 깃발 비트맵 핸들
extern int timerCount;            // 타이머 값

// 보드 초기화 (전체 보드 그리기)
void InitializeBoard(HWND hwnd, const Ms_level& level) {
    HDC hdc = GetDC(hwnd);

    int boardWidth = level.getWidth();    // 보드 가로 칸 수
    int boardHeight = level.getHeight(); // 보드 세로 칸 수
    int startY = 100;                     // 보드 시작 Y 좌표 (타이머 + 버튼 아래)

    const auto& board = logic.GetBoard(); // 게임 로직에서 보드 상태 가져오기

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            int x = j * CELL_WIDTH;
            int y = i * CELL_HEIGHT + startY;

            if (board[i][j].isRevealed) {
                if (board[i][j].isMine) {
                    DrawMine(hdc, hMineBitmap, x, y); // 지뢰 그리기
                }
                else {
                    DrawCell(hdc, x, y, RGB(255, 255, 255)); // 빈 셀
                    if (board[i][j].surroundingMines > 0) {
                        WCHAR text[2];
                        swprintf_s(text, L"%d", board[i][j].surroundingMines);
                        TextOutW(hdc, x + CELL_WIDTH / 3, y + CELL_HEIGHT / 4, text, 1);
                    }
                }
            }
            else {
                if (board[i][j].isFlagged) {
                    DrawFlag(hdc, hFlagBitmap, x, y); // 깃발 그리기
                }
                else {
                    DrawCell(hdc, x, y, RGB(200, 200, 200)); // 닫힌 셀
                }
            }
        }
    }

    ReleaseDC(hwnd, hdc);
}

// UI 초기화 (타이머와 버튼 설정)
void InitializeInterface(HWND hwnd) {
    // 초기화 버튼
    CreateWindowW(L"BUTTON", L"Reset", WS_VISIBLE | WS_CHILD,
        10, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_RESET, GetModuleHandle(NULL), NULL);

    // 타이머 표시
    CreateWindowW(L"STATIC", L"Time: 0", WS_VISIBLE | WS_CHILD | SS_CENTER,
        400, 10, 120, 30, hwnd, (HMENU)ID_TIMER, GetModuleHandle(NULL), NULL);

    // 타이머 시작
    SetTimer(hwnd, ID_TIMER, 1000, NULL); // 1초 간격으로 타이머 설정
}

// 단일 셀 그리기 (회색 셀, 기본 닫힘 상태)
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
