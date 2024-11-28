#pragma once

#include <vector>

// 셀의 상태를 나타내는 구조체
struct Cell {
    bool isMine;            // 지뢰 여부
    bool isRevealed;        // 셀이 열렸는지 여부
    bool isFlagged;         // 깃발 표시 여부
    bool isQMark = false;  // 물음표 상태 추가
    int surroundingMines;   // 주변 지뢰 개수
    bool isClicked;         // 클릭 상태 여부
};

// 지뢰찾기 게임 로직을 처리하는 클래스
class Ms_Logic {
public:
    /**
     * @brief 생성자: 보드 크기와 지뢰 개수를 초기화합니다.
     * @param width 보드의 가로 크기
     * @param height 보드의 세로 크기
     * @param mines 지뢰 개수
     * @param useBFS 탐색 방식 선택 (true: BFS, false: DFS)
     */
    Ms_Logic(int width, int height, int mines, bool useBFS = true);

    /**
     * @brief 보드를 초기화합니다.
     */
    void InitializeBoard();

    /**
     * @brief 특정 위치와 반경을 제외하고 지뢰를 배치합니다.
     * @param startX 시작 위치 X 좌표
     * @param startY 시작 위치 Y 좌표
     * @param exclusionRadius 제외 반경
     */
    void PlaceMines(int startX, int startY, int exclusionRadius);

    /**
     * @brief 각 셀의 주변 지뢰 개수를 계산합니다.
     */
    void CalculateSurroundingMines();

    /**
     * @brief 특정 셀을 열고 인접한 빈 공간을 탐색합니다.
     * @param x 셀의 X 좌표
     * @param y 셀의 Y 좌표
     * @return 탐색된 셀의 좌표를 반환
     */
    std::vector<std::pair<int, int>> RevealCell(int x, int y);

    /**
     * @brief 특정 셀에 깃발을 설정하거나 해제합니다.
     * @param x 셀의 X 좌표
     * @param y 셀의 Y 좌표
     */
    void ToggleFlag(int x, int y);

    /**
     * @brief 게임 종료 여부를 확인합니다.
     * @return 게임이 종료되었으면 true
     */
    bool IsGameOver() const;

    /**
     * @brief 게임 승리 여부를 확인합니다.
     * @return 승리 조건이 만족되었으면 true
     */
    bool IsGameWon() const;

    /**
     * @brief 보드의 현재 상태를 반환합니다.
     * @return 보드 상태를 저장하는 2D 배열
     */
    const std::vector<std::vector<Cell>>& GetBoard() const;

    /**
     * @brief 남은 지뢰 개수를 반환합니다.
     * @return 남은 지뢰 개수
     */
    int GetRemainingMines() const;

    /**
     * @brief 특정 셀의 클릭 상태를 설정합니다.
     * @param x 셀의 X 좌표
     * @param y 셀의 Y 좌표
     * @param clicked 클릭 여부
     */
    void SetCellClicked(int x, int y, bool clicked);

    /**
     * @brief 게임 상태를 초기화합니다.
     */
    void ResetGameState(); // **새롭게 추가된 메서드 선언**

private:
    int width;                                // 보드의 가로 크기
    int height;                               // 보드의 세로 크기
    int mineCount;                            // 전체 지뢰 개수
    int remainingMines;                       // 남은 지뢰 개수
    bool gameOver;                            // 게임 종료 여부
    bool gameWon;                             // 게임 승리 여부
    bool useBFS;                              // BFS 또는 DFS 선택 여부
    std::vector<std::vector<Cell>> mineField; // 보드 상태를 저장하는 2D 배열

    /**
     * @brief DFS를 사용하여 빈 칸 주변을 탐색하고 셀을 엽니다.
     * @param x 셀의 X 좌표
     * @param y 셀의 Y 좌표
     * @param revealedCells 탐색된 셀 좌표를 저장할 벡터
     */
    void RevealAdjacentCellsDFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells);

    /**
     * @brief BFS를 사용하여 빈 칸 주변을 탐색하고 셀을 엽니다.
     * @param x 셀의 X 좌표
     * @param y 셀의 Y 좌표
     * @param revealedCells 탐색된 셀 좌표를 저장할 벡터
     */
    void RevealAdjacentCellsBFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells);

    /**
     * @brief 승리 조건을 확인합니다.
     */
    void CheckWinCondition();
};
