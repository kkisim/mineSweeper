// MS.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "MS.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 함수 선언
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Ms_Level.h에서 선언된 전역 객체 참조
Ms_level* currentLevel = &Easy;                 // 현재 난이도 (가변 객체)
static int timerCount = 0;                      // 타이머 값
Ms_Logic logic(Easy.getWidth(), Easy.getHeight(), Easy.getMines(), true); // 초기 게임 로직 객체


// 창 크기 계산 및 UI 재배치 함수
void ResizeWindow(HWND hWnd, const Ms_level& level);
void AdjustUIPositions(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열 초기화
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MS));

    MSG msg;

    // 메시지 루프
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return FALSE;
    }

    // 창 크기 설정 및 초기화
    ResizeWindow(hWnd, *currentLevel);
    logic.InitializeBoard();               // 초기 보드 설정
    logic.PlaceMines(-1, -1, 0);           // 지뢰 배치
    logic.CalculateSurroundingMines();     // 주변 지뢰 개수 계산

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
// 창 크기 조정
//
void ResizeWindow(HWND hWnd, const Ms_level& level) {
    int boardWidth = level.getWidth() * CELL_WIDTH;
    int boardHeight = level.getHeight() * CELL_HEIGHT;
    int clientWidth = boardWidth;
    int clientHeight = boardHeight + 100; // UI 포함 크기

    RECT rect = { 0, 0, clientWidth, clientHeight };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

    SetWindowPos(hWnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
    AdjustUIPositions(hWnd);
}

//
// UI 위치 조정
//
void AdjustUIPositions(HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    HWND hResetButton = GetDlgItem(hWnd, ID_BUTTON_RESET);
    HWND hTimer = GetDlgItem(hWnd, ID_TIMER);

    if (hResetButton) {
        MoveWindow(hResetButton, 10, 10, 80, 30, TRUE); // 리셋 버튼 위치
    }

    if (hTimer) {
        int timerWidth = 100;
        int timerX = rect.right - timerWidth - 10;
        MoveWindow(hTimer, timerX, 10, timerWidth, 30, TRUE); // 타이머 위치
    }
}

//
// 메시지 처리 함수
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        LoadResources(hInst);  // 리소스 로드
        InitializeInterface(hWnd);
        break;

    case WM_SIZE:
        AdjustUIPositions(hWnd);
        break;

    case WM_LBUTTONDOWN: {
        int x = LOWORD(lParam) / CELL_WIDTH;
        int y = (HIWORD(lParam) - 100) / CELL_HEIGHT;

        if (y >= 0 && x >= 0 && x < logic.GetBoard()[0].size() && y < logic.GetBoard().size()) {
            logic.SetCellClicked(x, y, true);
            RECT cellRect = {
                x * CELL_WIDTH, y * CELL_HEIGHT + 100,
                (x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT + 100
            };
            InvalidateRect(hWnd, &cellRect, TRUE);
        }
        break;
    }

    case WM_LBUTTONUP: {
        int x = LOWORD(lParam) / CELL_WIDTH;
        int y = (HIWORD(lParam) - 100) / CELL_HEIGHT;

        if (y >= 0 && x >= 0 && x < logic.GetBoard()[0].size() && y < logic.GetBoard().size()) {
            logic.SetCellClicked(x, y, false);
            auto revealedCells = logic.RevealCell(x, y);

            for (const auto& cell : revealedCells) {
                RECT cellRect = {
                    cell.first * CELL_WIDTH, cell.second * CELL_HEIGHT + 100,
                    (cell.first + 1) * CELL_WIDTH, (cell.second + 1) * CELL_HEIGHT + 100
                };
                InvalidateRect(hWnd, &cellRect, TRUE);
            }

            if (logic.IsGameOver()) {
                MessageBox(hWnd, L"Game Over", L"You clicked on a mine!", MB_ICONERROR | MB_OK);
                SendMessage(hWnd, WM_COMMAND, ID_BUTTON_RESET, 0);
            }
            else if (logic.IsGameWon()) {
                MessageBox(hWnd, L"Congratulations!", L"You won the game!", MB_ICONINFORMATION | MB_OK);
                SendMessage(hWnd, WM_COMMAND, ID_BUTTON_RESET, 0);
            }
        }
        break;
    }

    case WM_RBUTTONDOWN: {
        int x = LOWORD(lParam) / CELL_WIDTH;
        int y = (HIWORD(lParam) - 100) / CELL_HEIGHT;

        if (y >= 0 && x >= 0 && x < logic.GetBoard()[0].size() && y < logic.GetBoard().size()) {
            logic.ToggleFlag(x, y);
            RECT cellRect = {
                x * CELL_WIDTH, y * CELL_HEIGHT + 100,
                (x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT + 100
            };
            InvalidateRect(hWnd, &cellRect, TRUE);
        }
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_32771: // Easy 난이도
            currentLevel = &Easy;
            timerCount = 0;
            logic = Ms_Logic(Easy.getWidth(), Easy.getHeight(), Easy.getMines(), true);
            logic.ResetGameState();
            ResizeWindow(hWnd, *currentLevel);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case ID_32772: // Normal 난이도
            currentLevel = &Normal;
            timerCount = 0;
            logic = Ms_Logic(Normal.getWidth(), Normal.getHeight(), Normal.getMines(), true);
            logic.ResetGameState();
            ResizeWindow(hWnd, *currentLevel);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case ID_32773: // Hard 난이도
            currentLevel = &Hard;
            timerCount = 0;
            logic = Ms_Logic(Hard.getWidth(), Hard.getHeight(), Hard.getMines(), true);
            logic.ResetGameState();
            ResizeWindow(hWnd, *currentLevel);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case ID_BUTTON_RESET:
            timerCount = 0;
            logic.ResetGameState();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;

    case WM_TIMER:
        if (wParam == ID_TIMER) {
            timerCount++;
            WCHAR timerText[20];
            swprintf_s(timerText, L"Time: %d", timerCount);
            SetWindowTextW(GetDlgItem(hWnd, ID_TIMER), timerText);
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 백 버퍼 생성
        HDC memDC = CreateCompatibleDC(hdc);
        RECT rect;
        GetClientRect(hWnd, &rect);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

        // 배경 초기화
        FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        // 남은 지뢰 표시
        RECT minesRect = { 0, 50, 120, 80 }; // 리셋 버튼 아래
        WCHAR mineCountText[20];
        swprintf_s(mineCountText, L"Mines: %d", logic.GetRemainingMines());
        FillRect(memDC, &minesRect, (HBRUSH)(COLOR_WINDOW + 1));
        DrawText(memDC, mineCountText, -1, &minesRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        // 보드 렌더링
        const auto& board = logic.GetBoard();
        for (int y = 0; y < board.size(); ++y) {
            for (int x = 0; x < board[y].size(); ++x) {
                int startX = x * CELL_WIDTH;
                int startY = y * CELL_HEIGHT + 100;

                if (board[y][x].isClicked) {
                    DrawCell(memDC, true, startX, startY);
                }
                else if (board[y][x].isRevealed) {
                    if (board[y][x].isMine) {
                        DrawMine(memDC, hMineBitmap, startX, startY);
                    }
                    else {
                        DrawCell(memDC, true, startX, startY);
                        if (board[y][x].surroundingMines > 0) {
                            DrawNumberBitmap(memDC, board[y][x].surroundingMines, startX, startY);
                        }
                    }
                }
                else {
                    if (board[y][x].isFlagged) {
                        DrawFlag(memDC, hFlagBitmap, startX, startY);
                    }
                    else {
                        DrawCell(memDC, false, startX, startY);
                    }
                }
            }
        }

        // 백 버퍼에서 실제 화면으로 출력
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

        // 리소스 정리
        SelectObject(memDC, oldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
        break;
    }


    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
