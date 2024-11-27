#pragma once
#include <windows.h>
#include "Ms_Level.h" // 난이도 설정 클래스
#include "Ms_Logic.h" // 게임 로직과의 연계를 위해 추가

// 셀 크기 정의 (픽셀 단위)
#define CELL_WIDTH 16   // 각 셀의 가로 크기
#define CELL_HEIGHT 16  // 각 셀의 세로 크기

// 타이머 및 버튼 ID 정의
#define ID_TIMER 1          // 타이머의 고유 ID
#define ID_BUTTON_RESET 2   // 리셋 버튼의 고유 ID

// 전역 비트맵 변수 선언 (다른 파일에서 실제로 정의됨, 여기서는 참조만 함)
extern HBITMAP hCellBitmap;         // 기본 셀 비트맵
extern HBITMAP hCellClickedBitmap;  // 클릭된 셀 비트맵
extern HBITMAP hFlagBitmap;         // 깃발 비트맵
extern HBITMAP hMineBitmap;         // 지뢰 비트맵
extern HBITMAP hAdjBombBitmap;      // 주변 지뢰 숫자 비트맵
extern HBITMAP hExplodeBitmap;      // 폭발 이미지 비트맵

// 함수 선언부

/**
 * @brief 보드 초기화 함수.
 *        게임 보드 전체를 초기화하고, 각 셀을 비트맵으로 그립니다.
 * @param hwnd 윈도우 핸들
 * @param level 현재 난이도 (Ms_level 객체로 전달)
 * @param logic 게임 로직 객체 (Ms_Logic 클래스 참조)
 */
void InitializeBoard(HDC hdc, Ms_level& level, Ms_Logic& logic);

/**
 * @brief UI 초기화 함수.
 *        타이머, 리셋 버튼 등 UI 요소를 생성합니다.
 * @param hwnd 윈도우 핸들
 */
void InitializeInterface(HWND hwnd);

/**
 * @brief 단일 셀을 비트맵으로 그리는 함수.
 * @param hdc 현재 장치 컨텍스트 핸들
 * @param isRevealed 셀이 클릭되었는지 여부 (true: 클릭됨, false: 클릭되지 않음)
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawCell(HDC hdc, bool isRevealed, int x, int y);

/**
 * @brief 비트맵 지뢰 이미지를 그리는 함수.
 * @param hdc 현재 장치 컨텍스트 핸들
 * @param hBitmap 지뢰 비트맵 핸들
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawMine(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief 비트맵 깃발 이미지를 그리는 함수.
 * @param hdc 현재 장치 컨텍스트 핸들
 * @param hBitmap 깃발 비트맵 핸들
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawFlag(HDC hdc, HBITMAP hBitmap, int x, int y);

/**
 * @brief 숫자 셀을 그리는 함수.
 *        주변 지뢰 개수를 나타내는 비트맵 숫자를 셀에 출력합니다.
 * @param hdc 현재 장치 컨텍스트 핸들
 * @param number 주변 지뢰 개수 (1~8 범위)
 * @param x 셀의 X 좌표 (픽셀 단위)
 * @param y 셀의 Y 좌표 (픽셀 단위)
 */
void DrawNumberBitmap(HDC hdc, int number, int x, int y);

/**
 * @brief 리소스를 로드하는 함수.
 *        비트맵 리소스를 메모리에 로드합니다.
 * @param hInstance 애플리케이션 인스턴스 핸들
 */
void LoadResources(HINSTANCE hInstance);

/**
 * @brief 리소스를 해제하는 함수.
 *        프로그램 종료 시 모든 비트맵 리소스를 메모리에서 해제합니다.
 */
void CleanupResources();

/**
 * @brief 남은 지뢰 수를 업데이트하고 화면에 표시합니다.
 * @param hwnd 윈도우 핸들
 * @param remainingMines 남은 지뢰 수
 */
void UpdateRemainingMines(HWND hwnd, int remainingMines);
