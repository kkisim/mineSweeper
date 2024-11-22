#pragma once
#include <windows.h>
#include "Ms_Level.h"
#include "Ms_Logic.h" // Ž�� �������� ���踦 ���� �߰�

// �� ũ�� ����
#define CELL_WIDTH 16   // ���� ���� ũ�� (�ȼ�)
#define CELL_HEIGHT 16  // ���� ���� ũ�� (�ȼ�)

// Ÿ�̸� �� ��ư ID ����
#define ID_TIMER 1          // Ÿ�̸� ID
#define ID_BUTTON_RESET 2   // ���� ��ư ID

// ���� ��Ʈ�� ���� ���� (extern)
extern HBITMAP hCellBitmap;
extern HBITMAP hCellClickedBitmap;
extern HBITMAP hFlagBitmap;
extern HBITMAP hMineBitmap;
extern HBITMAP hAdjBombBitmap;
extern HBITMAP hExplodeBitmap;

// �Լ� ����

/**
 * @brief ���� �ʱ�ȭ (��ü �� �׸���)
 * @param hwnd ������ �ڵ�
 * @param level ���� ���̵� (Ms_level)
 * @param logic ���� ���� ��ü (Ms_Logic)
 */
void InitializeBoard(HDC hdc, const Ms_level& level, Ms_Logic& logic);

/**
 * @brief UI �ʱ�ȭ (Ÿ�̸� �� ���� ��ư ����)
 * @param hwnd ������ �ڵ�
 */
void InitializeInterface(HWND hwnd);

/**
 * @brief ���� ���� ��Ʈ������ �׸��ϴ�.
 * @param hdc ���� HDC
 * @param isRevealed ���� Ŭ���Ǿ����� ����
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawCell(HDC hdc, bool isRevealed, int x, int y);

/**
 * @brief ��Ʈ�� ���� �̹����� �׸��� �Լ�
 * @param hdc ���� HDC
 * @param hBitmap ���� ��Ʈ�� �ڵ�
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief ��Ʈ�� ��� �̹����� �׸��� �Լ�
 * @param hdc ���� HDC
 * @param hBitmap ��� ��Ʈ�� �ڵ�
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief ���� ���� �׸��� �Լ� (�ֺ� ���� ���� ��Ʈ������ ���)
 * @param hdc ���� HDC
 * @param number �ֺ� ���� ���� (1~8)
 * @param x ���� X ��ǥ (�ȼ� ����)
 * @param y ���� Y ��ǥ (�ȼ� ����)
 */
void DrawNumberBitmap(HDC hdc, int number, int x, int y);

/**
 * @brief ���ҽ��� �ε��մϴ�.
 * @param hInstance ���ø����̼� �ν��Ͻ� �ڵ�
 */
void LoadResources(HINSTANCE hInstance);

/**
 * @brief ��� ���ҽ��� �����մϴ�.
 */
void CleanupResources();
/**
 * @brief ���� ���� ���� �����ϰ� �ؽ�Ʈ�� ǥ���մϴ�.
 * @param hwnd ������ �ڵ�
 * @param remainingMines ���� ���� ��
 */
void UpdateRemainingMines(HWND hWnd, int remainingMines);


