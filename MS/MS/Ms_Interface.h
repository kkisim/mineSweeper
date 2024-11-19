#pragma once
#ifndef MS_INTERFACE_H
#define MS_INTERFACE_H

#include <windows.h>
#include "Ms_Level.h"

// 셀 크기 정의
#define CELL_WIDTH 32
#define CELL_HEIGHT 32

// 버튼 ID 정의
#define ID_BUTTON_EASY    101
#define ID_BUTTON_NORMAL  102
#define ID_BUTTON_HARD    103
#define ID_BUTTON_RESET   104


// 타이머 ID 정의
#define ID_TIMER          201

// 인터페이스 초기화 함수 선언
void InitializeInterface(HWND hwnd);


// 함수 선언

// 보드를 초기화합니다.
void InitializeBoard(HWND hwnd, const Ms_level& level);

// 단일 셀을 그립니다.
void DrawCell(HDC hdc, int x, int y, COLORREF color);

// 비트맵 지뢰 이미지를 그립니다.
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

// 비트맵 깃발 이미지를 그립니다.
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);

#endif // MS_INTERFACE_H
