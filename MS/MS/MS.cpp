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

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {
      return FALSE;
   }
   // 비트맵 로드
   hMineBitmap = (HBITMAP)LoadImage(hInstance, L"resources/mine.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
   hFlagBitmap = (HBITMAP)LoadImage(hInstance, L"resources/flag.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

   // 창 크기 조정 (난이도에 따라)
   ResizeWindow(hWnd, *currentLevel);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
// 창 크기 조정 함수
void ResizeWindow(HWND hWnd, const Ms_level& level)
{
    // 보드 크기 계산
    int boardWidth = level.getWidth() * CELL_WIDTH;
    int boardHeight = level.getHeight() * CELL_HEIGHT;

    // 창 크기 조정
    RECT rect = { 0, 0, boardWidth, boardHeight };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);

    SetWindowPos(hWnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}
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



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        InitializeInterface(hWnd); // 인터페이스 초기화
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BUTTON_EASY:
            currentLevel = &Easy;
            InvalidateRect(hWnd, NULL, TRUE); // 보드 갱신
            break;
        case ID_BUTTON_NORMAL:
            currentLevel = &Normal;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ID_BUTTON_HARD:
            currentLevel = &Hard;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ID_BUTTON_RESET:
            timerCount = 0; // 타이머 초기화
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;
    case WM_TIMER:
        if (wParam == ID_TIMER) {
            timerCount++;
            HDC hdc = GetDC(hWnd);
            WCHAR timerText[20];
            swprintf_s(timerText, L"Time: %d", timerCount);
            TextOutW(hdc, 400, 10, timerText, wcslen(timerText));
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 보드 초기화
        InitializeBoard(hWnd, *currentLevel);

        // 지뢰 비트맵 테스트 출력
        if (hMineBitmap) {
            DrawMine(hdc, hMineBitmap, 50, 50);
        }

        // 깃발 비트맵 테스트 출력
        if (hFlagBitmap) {
            DrawFlag(hdc, hFlagBitmap, 100, 50);
        }

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_LBUTTONDOWN: // 좌클릭 시
    {
        int x = LOWORD(lParam) / CELL_WIDTH;  // 클릭된 셀의 x 좌표
        int y = HIWORD(lParam) / CELL_HEIGHT; // 클릭된 셀의 y 좌표
        // TODO: 셀 클릭 로직 추가
    }
    break;

    case WM_DESTROY:
        // 비트맵 리소스 해제
        DeleteObject(hMineBitmap);
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
