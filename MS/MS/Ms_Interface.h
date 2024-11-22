#pragma once
#include <windows.h>
#include "Ms_Level.h"
#include "Ms_Logic.h" // 탐색 로직과의 연계를 위해 추가

// 셀 크기 정의
#define CELL_WIDTH 16   // 셀의 가로 크기 (픽셀)
#define CELL_HEIGHT 16  // 셀의 세로 크기 (픽셀)

// 타이머 및 버튼 ID 정의
#define ID_TIMER 1          // 타이머 ID
#define ID_BUTTON_RESET 2   // 리셋 버튼 ID

// 전역 비트맵 변수 선언 (extern)
extern HBITMAP hCellBitmap;
extern HBITMAP hCellClickedBitmap;
extern HBITMAP hFlagBitmap;
extern HBITMAP hMineBitmap;
extern HBITMAP hAdjBombBitmap;
extern HBITMAP hExplodeBitmap;

// 함수 선언

/**
 * @brief 보드 초기화 (전체 셀 그리기)
 * @param hwnd 윈도우 핸들
 * @param level 현재 난이도 (Ms_level)
 * @param logic 게임 로직 객체 (Ms_Logic)
 */
void InitializeBoard(HDC hdc, const Ms_level& level, Ms_Logic& logic);

/**
 * @brief UI 초기화 (타이머 및 리셋 버튼 생성)
 * @param hwnd 윈도우 핸들
 */
void InitializeInterface(HWND hwnd);

/**
 * @brief 단일 셀을 비트맵으로 그립니다.
 * @param hdc 현재 HDC
 * @param isRevealed 셀이 클릭되었는지 여부
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawCell(HDC hdc, bool isRevealed, int x, int y);

/**
 * @brief 비트맵 지뢰 이미지를 그리는 함수
 * @param hdc 현재 HDC
 * @param hBitmap 지뢰 비트맵 핸들
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief 비트맵 깃발 이미지를 그리는 함수
 * @param hdc 현재 HDC
 * @param hBitmap 깃발 비트맵 핸들
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief 숫자 셀을 그리는 함수 (주변 지뢰 수를 비트맵으로 출력)
 * @param hdc 현재 HDC
 * @param number 주변 지뢰 개수 (1~8)
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawNumberBitmap(HDC hdc, int number, int x, int y);

/**
 * @brief 리소스를 로드합니다.
 * @param hInstance 애플리케이션 인스턴스 핸들
 */
void LoadResources(HINSTANCE hInstance);

/**
 * @brief 모든 리소스를 해제합니다.
 */
void CleanupResources();
/**
 * @brief 남은 지뢰 수를 갱신하고 텍스트로 표시합니다.
 * @param hwnd 윈도우 핸들
 * @param remainingMines 남은 지뢰 수
 */
void UpdateRemainingMines(HWND hWnd, int remainingMines);


