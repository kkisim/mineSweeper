#pragma once
#ifndef MS_LOGIC_H
#define MS_LOGIC_H
#include "framework.h"
#include <vector>

// --- 전역 변수 선언 ---
extern std::vector<std::vector<int>> gameBoard;      // 게임판 상태
extern std::vector<std::vector<bool>> isCellRevealed; // 셀이 열렸는지 여부
extern bool isGameOver;                              // 게임 종료 여부

// --- 함수 선언 ---
void InitializeGame(const Ms_level& level); // 게임 초기화
void OpenCell(int x, int y);                // 셀 열기
bool CheckWinCondition();                   // 승리 조건 확인
int GetCellValue(int x, int y);             // 특정 셀 값 가져오기
bool IsGameOver();                          // 게임 종료 상태 확인
void ExplodeBomb();                         // 지뢰 폭발 처리

#endif
