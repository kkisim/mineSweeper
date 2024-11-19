#pragma once
#ifndef MS_INTERFACE_H
#define MS_INTERFACE_H

#include <windows.h>
#include "Ms_Level.h"

// �� ũ�� ����
#define CELL_WIDTH 32
#define CELL_HEIGHT 32

// ��ư ID ����
#define ID_BUTTON_EASY    101
#define ID_BUTTON_NORMAL  102
#define ID_BUTTON_HARD    103
#define ID_BUTTON_RESET   104


// Ÿ�̸� ID ����
#define ID_TIMER          201

// �������̽� �ʱ�ȭ �Լ� ����
void InitializeInterface(HWND hwnd);


// �Լ� ����

// ���带 �ʱ�ȭ�մϴ�.
void InitializeBoard(HWND hwnd, const Ms_level& level);

// ���� ���� �׸��ϴ�.
void DrawCell(HDC hdc, int x, int y, COLORREF color);

// ��Ʈ�� ���� �̹����� �׸��ϴ�.
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

// ��Ʈ�� ��� �̹����� �׸��ϴ�.
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);

#endif // MS_INTERFACE_H
