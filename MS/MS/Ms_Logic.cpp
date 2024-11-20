#include "Ms_Logic.h"
#include <cstdlib>
#include <ctime>
#include <queue>

// 생성자
Ms_Logic::Ms_Logic(int width, int height, int mines)
    : width(width), height(height), mineCount(mines), gameOver(false), gameWon(false) {
    mineField.resize(height, std::vector<Cell>(width));
    InitializeBoard();
}

// 보드 초기화
void Ms_Logic::InitializeBoard() {
    for (auto& row : mineField) {
        for (auto& cell : row) {
            cell.isMine = false;
            cell.isRevealed = false;
            cell.isFlagged = false;
            cell.surroundingMines = 0;
        }
    }
}

// 지뢰 배치
void Ms_Logic::PlaceMines(int startX, int startY, int exclusionRadius) {
    srand(static_cast<unsigned>(time(0)));
    int placedMines = 0;

    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;

        if (!mineField[y][x].isMine &&
            !(x >= startX - exclusionRadius && x <= startX + exclusionRadius &&
                y >= startY - exclusionRadius && y <= startY + exclusionRadius)) {
            mineField[y][x].isMine = true;
            placedMines++;
        }
    }
}

// 주변 지뢰 개수 계산
void Ms_Logic::CalculateSurroundingMines() {
    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (mineField[y][x].isMine) continue;

            int count = 0;
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < width && ny >= 0 && ny < height && mineField[ny][nx].isMine) {
                    count++;
                }
            }
            mineField[y][x].surroundingMines = count;
        }
    }
}

// 특정 셀 열기
void Ms_Logic::RevealCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || mineField[y][x].isRevealed || mineField[y][x].isFlagged) {
        return;
    }

    if (mineField[y][x].isMine) {
        gameOver = true;
        return;
    }

    mineField[y][x].isRevealed = true;

    if (mineField[y][x].surroundingMines == 0) {
        RevealAdjacentCells(x, y);
    }

    CheckWinCondition();
}

// 빈 칸 주변 셀 열기
void Ms_Logic::RevealAdjacentCells(int x, int y) {
    std::queue<std::pair<int, int>> q;
    q.push({ x, y });

    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

    while (!q.empty()) {
        std::pair<int, int> current = q.front(); // 큐의 front() 값 가져오기
        q.pop();

        int cx = current.first;  // 현재 셀의 X 좌표
        int cy = current.second; // 현재 셀의 Y 좌표

        for (int i = 0; i < 8; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                !mineField[ny][nx].isRevealed && !mineField[ny][nx].isMine) {
                mineField[ny][nx].isRevealed = true;

                if (mineField[ny][nx].surroundingMines == 0) {
                    q.push({ nx, ny });
                }
            }
        }
    }
}


// 깃발 설정/해제
void Ms_Logic::ToggleFlag(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || mineField[y][x].isRevealed) {
        return;
    }

    mineField[y][x].isFlagged = !mineField[y][x].isFlagged;
}

// 게임 종료 여부 반환
bool Ms_Logic::IsGameOver() const {
    return gameOver;
}

// 게임 승리 여부 반환
bool Ms_Logic::IsGameWon() const {
    return gameWon;
}

// 승리 조건 확인
void Ms_Logic::CheckWinCondition() {
    gameWon = true;

    for (const auto& row : mineField) {
        for (const auto& cell : row) {
            if (!cell.isMine && !cell.isRevealed) {
                gameWon = false;
                return;
            }
        }
    }
}

// 보드 상태 반환
const std::vector<std::vector<Cell>>& Ms_Logic::GetBoard() const {
    return mineField;
}
