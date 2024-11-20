#pragma once
#include <vector>

// 각 셀의 상태를 표현하는 구조체
struct Cell {
    bool isMine;            // 지뢰 여부
    bool isRevealed;        // 셀이 열렸는지 여부
    bool isFlagged;         // 깃발 표시 여부
    int surroundingMines;   // 주변 지뢰 개수
};

// 지뢰찾기 게임 로직을 관리하는 클래스
class Ms_Logic {
public:
    // 생성자: 보드 크기와 지뢰 개수를 설정
    Ms_Logic(int width, int height, int mines);

    // 보드 초기화
    void InitializeBoard();

    // 지뢰 배치 (첫 클릭 위치와 주변은 제외)
    void PlaceMines(int startX, int startY, int exclusionRadius);

    // 주변 지뢰 개수 계산
    void CalculateSurroundingMines();

    // 특정 셀 열기
    void RevealCell(int x, int y);

    // 특정 셀 깃발 설정/해제
    void ToggleFlag(int x, int y);

    // 게임 종료 여부 반환
    bool IsGameOver() const;

    // 게임 승리 여부 반환
    bool IsGameWon() const;

    // 현재 보드 상태 반환
    const std::vector<std::vector<Cell>>& GetBoard() const;

private:
    int width;                                 // 보드의 가로 크기
    int height;                                // 보드의 세로 크기
    int mineCount;                             // 지뢰 개수
    bool gameOver;                             // 게임 종료 여부
    bool gameWon;                              // 게임 승리 여부
    std::vector<std::vector<Cell>> mineField; // 보드 상태를 저장하는 2D 배열

    // 빈 칸 주변 셀 열기
    void RevealAdjacentCells(int x, int y);

    // 게임 승리 조건 확인
    void CheckWinCondition();
};
