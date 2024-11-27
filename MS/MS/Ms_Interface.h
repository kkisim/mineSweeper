#pragma once
#include <windows.h>
#include "Ms_Level.h" // ���̵� ���� Ŭ����
#include "Ms_Logic.h" // ���� �������� ���踦 ���� �߰�

// �� ũ�� ���� (�ȼ� ����)
#define CELL_WIDTH 16   // �� ���� ���� ũ��
#define CELL_HEIGHT 16  // �� ���� ���� ũ��

// Ÿ�̸� �� ��ư ID ����
#define ID_TIMER 1          // Ÿ�̸��� ���� ID
#define ID_BUTTON_RESET 2   // ���� ��ư�� ���� ID

// ���� ��Ʈ�� ���� ���� (�ٸ� ���Ͽ��� ������ ���ǵ�, ���⼭�� ������ ��)
extern HBITMAP hCellBitmap;         // �⺻ �� ��Ʈ��
extern HBITMAP hCellClickedBitmap;  // Ŭ���� �� ��Ʈ��
extern HBITMAP hFlagBitmap;         // ��� ��Ʈ��
extern HBITMAP hMineBitmap;         // ���� ��Ʈ��
extern HBITMAP hAdjBombBitmap;      // �ֺ� ���� ���� ��Ʈ��
extern HBITMAP hExplodeBitmap;      // ���� �̹��� ��Ʈ��

// �Լ� �����

/**
 * @brief ���� �ʱ�ȭ �Լ�.
 *        ���� ���� ��ü�� �ʱ�ȭ�ϰ�, �� ���� ��Ʈ������ �׸��ϴ�.
 * @param hwnd ������ �ڵ�
 * @param level ���� ���̵� (Ms_level ��ü�� ����)
 * @param logic ���� ���� ��ü (Ms_Logic Ŭ���� ����)
 */
void InitializeBoard(HDC hdc, Ms_level& level, Ms_Logic& logic);

/**
 * @brief UI �ʱ�ȭ �Լ�.
 *        Ÿ�̸�, ���� ��ư �� UI ��Ҹ� �����մϴ�.
 * @param hwnd ������ �ڵ�
 */
void InitializeInterface(HWND hwnd);

/**
 * @brief ���� ���� ��Ʈ������ �׸��� �Լ�.
 * @param hdc ���� ��ġ ���ؽ�Ʈ �ڵ�
 * @param isRevealed ���� Ŭ���Ǿ����� ���� (true: Ŭ����, false: Ŭ������ ����)
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawCell(HDC hdc, bool isRevealed, int x, int y);

/**
 * @brief ��Ʈ�� ���� �̹����� �׸��� �Լ�.
 * @param hdc ���� ��ġ ���ؽ�Ʈ �ڵ�
 * @param hBitmap ���� ��Ʈ�� �ڵ�
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief ��Ʈ�� ��� �̹����� �׸��� �Լ�.
 * @param hdc ���� ��ġ ���ؽ�Ʈ �ڵ�
 * @param hBitmap ��� ��Ʈ�� �ڵ�
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief ���� ���� �׸��� �Լ�.
 *        �ֺ� ���� ������ ��Ÿ���� ��Ʈ�� ���ڸ� ���� ����մϴ�.
 * @param hdc ���� ��ġ ���ؽ�Ʈ �ڵ�
 * @param number �ֺ� ���� ���� (1~8 ����)
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawNumberBitmap(HDC hdc, int number, int x, int y);

/**
 * @brief ���ҽ��� �ε��ϴ� �Լ�.
 *        ��Ʈ�� ���ҽ��� �޸𸮿� �ε��մϴ�.
 * @param hInstance ���ø����̼� �ν��Ͻ� �ڵ�
 */
void LoadResources(HINSTANCE hInstance);

/**
 * @brief ���ҽ��� �����ϴ� �Լ�.
 *        ���α׷� ���� �� ��� ��Ʈ�� ���ҽ��� �޸𸮿��� �����մϴ�.
 */
void CleanupResources();

/**
 * @brief ���� ���� ���� ������Ʈ�ϰ� ȭ�鿡 ǥ���մϴ�.
 * @param hwnd ������ �ڵ�
 * @param remainingMines ���� ���� ��
 */
void UpdateRemainingMines(HWND hwnd, int remainingMines);
