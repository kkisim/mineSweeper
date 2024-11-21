// MS.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "MS.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


HBITMAP hMineBitmap = NULL;                     // 지뢰 비트맵 핸들
HBITMAP hFlagBitmap = NULL;                     // 깃발 비트맵 핸들
const Ms_level* currentLevel = &Easy;           // 현재 난이도 (기본: Easy)


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MS));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

// 창 크기 계산
void ResizeWindow(HWND hWnd, const Ms_level& level);
void ResizeWindow(HWND hWnd, const Ms_level& level) {
    int boardWidth = level.getWidth() * CELL_WIDTH;
    int boardHeight = level.getHeight() * CELL_HEIGHT;

    // 클라이언트 영역 크기 설정 (보드 크기 + 상단 UI)
    int clientWidth = boardWidth;
    int clientHeight = boardHeight + 100; // 100: 타이머와 버튼 높이 포함

    // 전체 창 크기 계산
    RECT rect = { 0, 0, clientWidth, clientHeight };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

    // 창 크기 조정
    SetWindowPos(hWnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return FALSE;

    // 창 크기 설정
    ResizeWindow(hWnd, *currentLevel);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//       CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);
//
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//   // 비트맵 로드
//   hMineBitmap = (HBITMAP)LoadImage(hInstance, L"resources/mine.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//   hFlagBitmap = (HBITMAP)LoadImage(hInstance, L"resources/flag.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//
//   // 창 크기 조정 (난이도에 따라)
//   ResizeWindow(hWnd, *currentLevel);
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}
// 창 크기 조정 함수
//void ResizeWindow(HWND hWnd, const Ms_level& level)
//{
//    // 보드 크기 계산
//    int boardWidth = level.getWidth() * CELL_WIDTH;
//    int boardHeight = level.getHeight() * CELL_HEIGHT;
//
//    // 창 크기 조정
//    RECT rect = { 0, 0, boardWidth, boardHeight };
//    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);
//
//    SetWindowPos(hWnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
//}
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//경과 시간 저장

static int timerCount = 0;
// 현재 난이도와 연동된 Ms_Logic 객체
Ms_Logic logic(Easy.getWidth(), Easy.getHeight(), Easy.getMines());
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        InitializeInterface(hWnd); // 인터페이스 초기화 (타이머 및 버튼 생성)
        break;

    case WM_LBUTTONDOWN: { // 왼쪽 클릭
        int x = LOWORD(lParam) / CELL_WIDTH; // 셀 X 좌표
        int y = (HIWORD(lParam) - 100) / CELL_HEIGHT; // 셀 Y 좌표 (상단 UI 높이 제외)

        if (y >= 0) { // 유효한 셀 클릭 처리
            logic.RevealCell(x, y); // 셀 열기

            if (logic.IsGameOver()) { // 게임 종료 시
                MessageBox(hWnd, L"Game Over!", L"지뢰찾기", MB_OK);
                logic.InitializeBoard(); // 게임 재시작
            }
            else if (logic.IsGameWon()) { // 승리 조건 달성 시
                MessageBox(hWnd, L"You Win!", L"지뢰찾기", MB_OK);
                logic.InitializeBoard(); // 게임 재시작
            }

            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
        }
        break;
    }

    case WM_RBUTTONDOWN: { // 오른쪽 클릭
        int x = LOWORD(lParam) / CELL_WIDTH; // 셀 X 좌표
        int y = (HIWORD(lParam) - 100) / CELL_HEIGHT; // 셀 Y 좌표 (상단 UI 높이 제외)

        if (y >= 0) { // 유효한 셀 클릭 처리
            logic.ToggleFlag(x, y); // 깃발 설정/해제
            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신
        }
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_32771: // Easy 난이도
            currentLevel = &Easy;
            timerCount = -1;
            logic = Ms_Logic(Easy.getWidth(), Easy.getHeight(), Easy.getMines());
            logic.InitializeBoard();
            ResizeWindow(hWnd, *currentLevel);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case ID_32772: // Normal 난이도
            currentLevel = &Normal;
            timerCount = -1;
            logic = Ms_Logic(Normal.getWidth(), Normal.getHeight(), Normal.getMines());
            logic.InitializeBoard();
            ResizeWindow(hWnd, *currentLevel);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case ID_32773: // Hard 난이도
            currentLevel = &Hard;
            timerCount = -1;
            logic = Ms_Logic(Hard.getWidth(), Hard.getHeight(), Hard.getMines());
            logic.InitializeBoard();
            ResizeWindow(hWnd, *currentLevel);
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case ID_BUTTON_RESET:
            timerCount = -1;
            logic.InitializeBoard();
            
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;
    case WM_SIZE: {
        int width = LOWORD(lParam);  // 창의 너비
        int height = HIWORD(lParam); // 창의 높이

        // 타이머 컨트롤의 크기 및 위치 계산 (오른쪽 상단)
        int timerWidth = 120;
        int timerHeight = 30;
        int timerX = width - timerWidth - 10; // 오른쪽 여백 10 픽셀
        int timerY = 10;                     // 상단 여백 10 픽셀

        HWND hTimer = GetDlgItem(hWnd, ID_TIMER);
        if (hTimer) {
            MoveWindow(hTimer, timerX, timerY, timerWidth, timerHeight, TRUE);
        }

        break;
    }


    case WM_TIMER:
        if (wParam == ID_TIMER) {
            timerCount++; // 타이머 값 증가

            // 타이머 값을 문자열로 변환하여 표시
            HWND hTimer = GetDlgItem(hWnd, ID_TIMER);
            if (hTimer) {
                WCHAR timerText[20];
                swprintf_s(timerText, L"Time: %d", timerCount);
                SetWindowTextW(hTimer, timerText); // 타이머 텍스트 업데이트
            }
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

        // 백 버퍼 초기화
        FillRect(memDC, &rect, (HBRUSH)(COLOR_WINDOW + 1));

        // 보드 및 셀 그리기
        const auto& board = logic.GetBoard();
        for (int y = 0; y < board.size(); ++y) {
            for (int x = 0; x < board[y].size(); ++x) {
                int startX = x * CELL_WIDTH;
                int startY = y * CELL_HEIGHT + 100; // 상단 UI 높이 제외
                if (board[y][x].isRevealed) {
                    if (board[y][x].isMine) {
                        DrawMine(memDC, hMineBitmap, startX, startY);
                    }
                    else {
                        DrawCell(memDC, startX, startY, RGB(255, 255, 255));
                        if (board[y][x].surroundingMines > 0) {
                            WCHAR text[2];
                            swprintf_s(text, L"%d", board[y][x].surroundingMines);
                            TextOutW(memDC, startX + CELL_WIDTH / 3, startY + CELL_HEIGHT / 4, text, 1);
                        }
                    }
                }
                else {
                    if (board[y][x].isFlagged) {
                        DrawFlag(memDC, hFlagBitmap, startX, startY);
                    }
                    else {
                        DrawCell(memDC, startX, startY, RGB(200, 200, 200));
                    }
                }
            }
        }

        // 백 버퍼에서 화면으로 출력
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

        // 메모리 해제
        SelectObject(memDC, oldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY:
        KillTimer(hWnd, ID_TIMER); // 타이머 제거
        DeleteObject(hMineBitmap); // 리소스 해제
        DeleteObject(hFlagBitmap);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
