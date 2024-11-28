#include "Ms_Interface.h"
#include "Ms_Logic.h"

// 전역 변수 정의
HBITMAP hMineBitmap = NULL;           // 지뢰 비트맵 핸들
HBITMAP hFlagBitmap = NULL;           // 깃발 비트맵 핸들
HBITMAP hCellBitmap = NULL;           // 닫힌 셀 비트맵 핸들
HBITMAP hCellClickedBitmap = NULL;    // 클릭된 셀 비트맵 핸들
HBITMAP hAdjBombBitmap = NULL;        // 주변 지뢰 비트맵 핸들
HBITMAP qmarkBitmap = NULL;        // 물음표 셀 비트맵 핸들 //추가
extern Ms_Logic logic;                // 게임 로직 객체
extern int timerCount;                // 타이머 값


/**
 * @brief 셀의 상태에 따라 닫힌 셀 또는 클릭된 셀 이미지를 렌더링합니다.
 * @param hdc 현재 HDC
 * @param isRevealed 셀 클릭 여부
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawCell(HDC hdc, bool isRevealed, int x, int y) {
    HBITMAP hBitmap = isRevealed ? hCellClickedBitmap : hCellBitmap; // 클릭 여부에 따라 비트맵 선택
    if (!hBitmap) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

/**
 * @brief 지뢰를 렌더링합니다.
 * @param hdc 현재 HDC
 * @param hBitmap 지뢰 비트맵 핸들
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y) {
    if (!hBitmap) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

/**
 * @brief 깃발을 렌더링합니다.
 * @param hdc 현재 HDC
 * @param hBitmap 깃발 비트맵 핸들
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y) {
    if (!hBitmap) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}
void Drawqmark(HDC hdc, HBITMAP hBitmap, int x, int y) {
    if (!hBitmap) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}
/**
 * @brief 주변 지뢰 수를 비트맵으로 렌더링합니다.
 * @param hdc 현재 HDC
 * @param number 주변 지뢰 수 (1~8)
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawNumberBitmap(HDC hdc, int number, int x, int y) {
    if (number < 1 || number > 8) return; // 유효한 숫자(1~8)만 처리

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hAdjBombBitmap);

    // 각 숫자의 비트맵 영역 (16x 픽셀 기준)
    int srcX = (number - 1) * CELL_WIDTH; // 숫자별 시작 X 좌표
    int srcY = 0;                         // Y 좌표는 항상 0

    // 숫자 출력
    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, srcX, srcY, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

/**
 * @brief 보드를 초기화하고 셀 상태에 따라 렌더링합니다.
 * @param hwnd 윈도우 핸들
 * @param level 현재 난이도 객체
 * @param logic 게임 로직 객체
 */
void InitializeBoard(HDC hdc,  Ms_level& level, Ms_Logic& logic) {
    int boardWidth = level.getWidth();    // 보드의 가로 칸 수
    int boardHeight = level.getHeight(); // 보드의 세로 칸 수
    int startY = 100;                     // 보드 시작 Y 좌표 (타이머 + 버튼 아래)

    const auto& board = logic.GetBoard(); // 게임 로직에서 보드 상태 가져오기

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            int x = j * CELL_WIDTH;
            int y = i * CELL_HEIGHT + startY;

            if (board[i][j].isRevealed) {
                if (board[i][j].isMine) {
                    DrawMine(hdc, hMineBitmap, x, y); // 지뢰 렌더링
                }
                else {
                    DrawCell(hdc, true, x, y);
                    if (board[i][j].surroundingMines > 0) {
                        DrawNumberBitmap(hdc, board[i][j].surroundingMines, x, y);
                    }
                }
            }
            else {
                if (board[i][j].isFlagged) {
                    DrawFlag(hdc, hFlagBitmap, x, y); // 깃발 렌더링
                }
                else {
                    DrawCell(hdc, false, x, y); // 닫힌 셀 렌더링
                }
            }
        }
    }
}




/**
 * @brief UI 초기화: 리셋 버튼과 타이머를 생성합니다.
 * @param hwnd 윈도우 핸들
 */
void InitializeInterface(HWND hwnd) {
    // 리셋 버튼 생성
    CreateWindowW(L"BUTTON", L"Reset", WS_VISIBLE | WS_CHILD,
        10, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_RESET, GetModuleHandle(NULL), NULL);

    // 타이머 표시
    CreateWindowW(L"STATIC", L"Time: 0", WS_VISIBLE | WS_CHILD | SS_CENTER,
        400, 10, 120, 30, hwnd, (HMENU)ID_TIMER, GetModuleHandle(NULL), NULL);

    // 1초 간격으로 타이머 시작
    SetTimer(hwnd, ID_TIMER, 1000, NULL);
}

/**
 * @brief 리소스를 로드합니다.
 * @param hInstance 애플리케이션 인스턴스 핸들
 */
void LoadResources(HINSTANCE hInstance) {
    hCellBitmap = (HBITMAP)LoadImage(hInstance, L"..\\cell.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hCellClickedBitmap = (HBITMAP)LoadImage(hInstance, L"..\\cell_clicked.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hFlagBitmap = (HBITMAP)LoadImage(hInstance, L"..\\flag.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hMineBitmap = (HBITMAP)LoadImage(hInstance, L"..\\bomb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hAdjBombBitmap = (HBITMAP)LoadImage(hInstance, L"..\\adjbomb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    qmarkBitmap = (HBITMAP)LoadImage(hInstance, L"..\\qmark.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

/**
 * @brief 모든 리소스를 해제합니다.
 */
void CleanupResources() {
    if (hCellBitmap) { DeleteObject(hCellBitmap); hCellBitmap = NULL; }
    if (hCellClickedBitmap) { DeleteObject(hCellClickedBitmap); hCellClickedBitmap = NULL; }
    if (hFlagBitmap) { DeleteObject(hFlagBitmap); hFlagBitmap = NULL; }
    if (hMineBitmap) { DeleteObject(hMineBitmap); hMineBitmap = NULL; }
    if (hAdjBombBitmap) { DeleteObject(hAdjBombBitmap); hAdjBombBitmap = NULL; }
    if (qmarkBitmap) { DeleteObject(qmarkBitmap); qmarkBitmap = NULL; }
}
// 남은 지뢰 수를 저장할 전역 변수
static int lastRemainingMines = -1;

/**
 * @brief 남은 지뢰 수를 갱신하고 텍스트로 표시합니다.
 * @param hwnd 윈도우 핸들
 * @param remainingMines 남은 지뢰 수
 */
void UpdateRemainingMines(HWND hWnd, int remainingMines) {
    // 남은 지뢰 수 표시 영역 정의 (리셋 버튼 아래)
    RECT minesRect = { 10, 50, 130, 80 };

    // 텍스트 생성
    WCHAR mineCountText[20];
    swprintf_s(mineCountText, L"Mines: %d", remainingMines);

    // 화면 업데이트
    HDC hdc = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 130, 30); // 120x30 영역
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    // 배경 초기화
    FillRect(memDC, &minesRect, (HBRUSH)(COLOR_WINDOW + 1));

    // 텍스트 출력
    SetBkMode(memDC, TRANSPARENT);
    DrawText(memDC, mineCountText, -1, &minesRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // 백 버퍼에서 실제 화면으로 출력
    BitBlt(hdc, minesRect.left, minesRect.top, 130, 30, memDC, 0, 0, SRCCOPY);

    // 메모리 해제
    SelectObject(memDC, oldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
}