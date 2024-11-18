#pragma once
#ifndef MS_LOGIC_H
#define MS_LOGIC_H
#include "framework.h"
#include <vector>

// --- ���� ���� ���� ---
extern std::vector<std::vector<int>> gameBoard;      // ������ ����
extern std::vector<std::vector<bool>> isCellRevealed; // ���� ���ȴ��� ����
extern bool isGameOver;                              // ���� ���� ����

// --- �Լ� ���� ---
void InitializeGame(const Ms_level& level); // ���� �ʱ�ȭ
void OpenCell(int x, int y);                // �� ����
bool CheckWinCondition();                   // �¸� ���� Ȯ��
int GetCellValue(int x, int y);             // Ư�� �� �� ��������
bool IsGameOver();                          // ���� ���� ���� Ȯ��
void ExplodeBomb();                         // ���� ���� ó��

#endif
