#pragma once
#include <windows.h>
#include "Ms_Level.h"

// 셀 크기 정의
#define CELL_WIDTH 32
#define CELL_HEIGHT 32

// 타이머 및 버튼 ID 정의
#define ID_TIMER 1
#define ID_BUTTON_RESET 2

// 함수 선언

// 보드 초기화 (전체 셀 그리기)
void InitializeBoard(HWND hwnd, const Ms_level& level);

// UI 초기화 (타이머 및 리셋 버튼 생성)
void InitializeInterface(HWND hwnd);

// 단일 셀 그리기 (닫힌 셀)
void DrawCell(HDC hdc, int x, int y, COLORREF color);

// 비트맵 지뢰 이미지를 그리는 함수
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

// 비트맵 깃발 이미지를 그리는 함수
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);
