#pragma once
#include <windows.h>
#include "Ms_Level.h"

// �� ũ�� ����
#define CELL_WIDTH 32
#define CELL_HEIGHT 32

// Ÿ�̸� �� ��ư ID ����
#define ID_TIMER 1
#define ID_BUTTON_RESET 2

// �Լ� ����

// ���� �ʱ�ȭ (��ü �� �׸���)
void InitializeBoard(HWND hwnd, const Ms_level& level);

// UI �ʱ�ȭ (Ÿ�̸� �� ���� ��ư ����)
void InitializeInterface(HWND hwnd);

// ���� �� �׸��� (���� ��)
void DrawCell(HDC hdc, int x, int y, COLORREF color);

// ��Ʈ�� ���� �̹����� �׸��� �Լ�
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

// ��Ʈ�� ��� �̹����� �׸��� �Լ�
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);
