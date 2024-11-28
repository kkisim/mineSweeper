#include "Ms_Interface.h"
#include "Ms_Logic.h"

// ���� ���� ����
HBITMAP hMineBitmap = NULL;           // ���� ��Ʈ�� �ڵ�
HBITMAP hFlagBitmap = NULL;           // ��� ��Ʈ�� �ڵ�
HBITMAP hCellBitmap = NULL;           // ���� �� ��Ʈ�� �ڵ�
HBITMAP hCellClickedBitmap = NULL;    // Ŭ���� �� ��Ʈ�� �ڵ�
HBITMAP hAdjBombBitmap = NULL;        // �ֺ� ���� ��Ʈ�� �ڵ�
HBITMAP qmarkBitmap = NULL;        // ����ǥ �� ��Ʈ�� �ڵ� //�߰�
extern Ms_Logic logic;                // ���� ���� ��ü
extern int timerCount;                // Ÿ�̸� ��


/**
 * @brief ���� ���¿� ���� ���� �� �Ǵ� Ŭ���� �� �̹����� �������մϴ�.
 * @param hdc ���� HDC
 * @param isRevealed �� Ŭ�� ����
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawCell(HDC hdc, bool isRevealed, int x, int y) {
    HBITMAP hBitmap = isRevealed ? hCellClickedBitmap : hCellBitmap; // Ŭ�� ���ο� ���� ��Ʈ�� ����
    if (!hBitmap) return;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);
    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

/**
 * @brief ���ڸ� �������մϴ�.
 * @param hdc ���� HDC
 * @param hBitmap ���� ��Ʈ�� �ڵ�
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
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
 * @brief ����� �������մϴ�.
 * @param hdc ���� HDC
 * @param hBitmap ��� ��Ʈ�� �ڵ�
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
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
 * @brief �ֺ� ���� ���� ��Ʈ������ �������մϴ�.
 * @param hdc ���� HDC
 * @param number �ֺ� ���� �� (1~8)
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawNumberBitmap(HDC hdc, int number, int x, int y) {
    if (number < 1 || number > 8) return; // ��ȿ�� ����(1~8)�� ó��

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hAdjBombBitmap);

    // �� ������ ��Ʈ�� ���� (16x �ȼ� ����)
    int srcX = (number - 1) * CELL_WIDTH; // ���ں� ���� X ��ǥ
    int srcY = 0;                         // Y ��ǥ�� �׻� 0

    // ���� ���
    BitBlt(hdc, x, y, CELL_WIDTH, CELL_HEIGHT, memDC, srcX, srcY, SRCCOPY);

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}

/**
 * @brief ���带 �ʱ�ȭ�ϰ� �� ���¿� ���� �������մϴ�.
 * @param hwnd ������ �ڵ�
 * @param level ���� ���̵� ��ü
 * @param logic ���� ���� ��ü
 */
void InitializeBoard(HDC hdc,  Ms_level& level, Ms_Logic& logic) {
    int boardWidth = level.getWidth();    // ������ ���� ĭ ��
    int boardHeight = level.getHeight(); // ������ ���� ĭ ��
    int startY = 100;                     // ���� ���� Y ��ǥ (Ÿ�̸� + ��ư �Ʒ�)

    const auto& board = logic.GetBoard(); // ���� �������� ���� ���� ��������

    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            int x = j * CELL_WIDTH;
            int y = i * CELL_HEIGHT + startY;

            if (board[i][j].isRevealed) {
                if (board[i][j].isMine) {
                    DrawMine(hdc, hMineBitmap, x, y); // ���� ������
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
                    DrawFlag(hdc, hFlagBitmap, x, y); // ��� ������
                }
                else {
                    DrawCell(hdc, false, x, y); // ���� �� ������
                }
            }
        }
    }
}




/**
 * @brief UI �ʱ�ȭ: ���� ��ư�� Ÿ�̸Ӹ� �����մϴ�.
 * @param hwnd ������ �ڵ�
 */
void InitializeInterface(HWND hwnd) {
    // ���� ��ư ����
    CreateWindowW(L"BUTTON", L"Reset", WS_VISIBLE | WS_CHILD,
        10, 10, 80, 30, hwnd, (HMENU)ID_BUTTON_RESET, GetModuleHandle(NULL), NULL);

    // Ÿ�̸� ǥ��
    CreateWindowW(L"STATIC", L"Time: 0", WS_VISIBLE | WS_CHILD | SS_CENTER,
        400, 10, 120, 30, hwnd, (HMENU)ID_TIMER, GetModuleHandle(NULL), NULL);

    // 1�� �������� Ÿ�̸� ����
    SetTimer(hwnd, ID_TIMER, 1000, NULL);
}

/**
 * @brief ���ҽ��� �ε��մϴ�.
 * @param hInstance ���ø����̼� �ν��Ͻ� �ڵ�
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
 * @brief ��� ���ҽ��� �����մϴ�.
 */
void CleanupResources() {
    if (hCellBitmap) { DeleteObject(hCellBitmap); hCellBitmap = NULL; }
    if (hCellClickedBitmap) { DeleteObject(hCellClickedBitmap); hCellClickedBitmap = NULL; }
    if (hFlagBitmap) { DeleteObject(hFlagBitmap); hFlagBitmap = NULL; }
    if (hMineBitmap) { DeleteObject(hMineBitmap); hMineBitmap = NULL; }
    if (hAdjBombBitmap) { DeleteObject(hAdjBombBitmap); hAdjBombBitmap = NULL; }
    if (qmarkBitmap) { DeleteObject(qmarkBitmap); qmarkBitmap = NULL; }
}
// ���� ���� ���� ������ ���� ����
static int lastRemainingMines = -1;

/**
 * @brief ���� ���� ���� �����ϰ� �ؽ�Ʈ�� ǥ���մϴ�.
 * @param hwnd ������ �ڵ�
 * @param remainingMines ���� ���� ��
 */
void UpdateRemainingMines(HWND hWnd, int remainingMines) {
    // ���� ���� �� ǥ�� ���� ���� (���� ��ư �Ʒ�)
    RECT minesRect = { 10, 50, 130, 80 };

    // �ؽ�Ʈ ����
    WCHAR mineCountText[20];
    swprintf_s(mineCountText, L"Mines: %d", remainingMines);

    // ȭ�� ������Ʈ
    HDC hdc = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 130, 30); // 120x30 ����
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

    // ��� �ʱ�ȭ
    FillRect(memDC, &minesRect, (HBRUSH)(COLOR_WINDOW + 1));

    // �ؽ�Ʈ ���
    SetBkMode(memDC, TRANSPARENT);
    DrawText(memDC, mineCountText, -1, &minesRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // �� ���ۿ��� ���� ȭ������ ���
    BitBlt(hdc, minesRect.left, minesRect.top, 130, 30, memDC, 0, 0, SRCCOPY);

    // �޸� ����
    SelectObject(memDC, oldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
}