#include "Ms_Logic.h"
#include <cstdlib>
#include <ctime>
#include <queue>

// 생성자: 보드의 크기, 지뢰 개수, 탐색 방식(BFS 또는 DFS)을 초기화합니다.
Ms_Logic::Ms_Logic(int width, int height, int mines, bool useBFS)
    : width(width), height(height), mineCount(mines), remainingMines(mines),
    gameOver(false), gameWon(false), useBFS(useBFS) {
    // 보드 상태를 저장하는 2D 배열 초기화
    mineField.resize(height, std::vector<Cell>(width));
    InitializeBoard();
}

// 보드 초기화: 각 셀의 상태를 기본값으로 설정
void Ms_Logic::InitializeBoard() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            mineField[i][j].isMine = false;          // 지뢰 여부 초기화
            mineField[i][j].isRevealed = false;      // 열림 상태 초기화
            mineField[i][j].isFlagged = false;       // 깃발 상태 초기화
            mineField[i][j].surroundingMines = 0;    // 주변 지뢰 개수 초기화
            mineField[i][j].isClicked = false;       // 클릭 상태 초기화
            mineField[i][j].isQMark = false;         // 물음표 상태 초기화
        }
    }
}



 // 지뢰 배치: 보드에 지뢰를 무작위로 배치
void Ms_Logic::PlaceMines(int startX, int startY, int exclusionRadius) {
    srand(static_cast<unsigned>(time(0))); // 랜덤 시드 설정
    int placedMines = 0;

    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;

        // 배치 조건: 지뢰가 없는 셀이고, 시작 위치 및 반경 제외
        if (!mineField[y][x].isMine &&
            //(startX == -1 || startY == -1 || // 처음 클릭하지 않은 상태에서는 제한 없음
            !(x >= startX - exclusionRadius && x <= startX + exclusionRadius &&
                y >= startY - exclusionRadius && y <= startY + exclusionRadius)) {
            mineField[y][x].isMine = true; // 지뢰 배치
            placedMines++;
        }
    }
}


// 주변 지뢰 개수 계산: 각 셀에 인접한 지뢰 개수를 계산
void Ms_Logic::CalculateSurroundingMines() {
    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 }; // 8방향 X 좌표
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 }; // 8방향 Y 좌표

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (mineField[y][x].isMine) continue; // 지뢰가 있는 셀은 건너뜀

            int count = 0;
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                // 경계 내의 지뢰 개수 카운트
                if (nx >= 0 && nx < width && ny >= 0 && ny < height && mineField[ny][nx].isMine) {
                    count++;
                }
            }
            mineField[y][x].surroundingMines = count; // 주변 지뢰 개수 저장
        }
    }
}

std::vector<std::pair<int, int>> Ms_Logic::RevealCell(int x, int y) {
    std::vector<std::pair<int, int>> revealedCells;

    // 경계 조건: 보드의 범위를 벗어나거나 이미 열려 있거나 플래그가 설정된 셀은 무시합니다.
    if (x < 0 || x >= width || y < 0 || y >= height || mineField[y][x].isRevealed || mineField[y][x].isFlagged) {
        return revealedCells;
    }

    // 현재 셀을 열고 해당 좌표를 탐색된 셀 목록에 추가합니다.
    mineField[y][x].isRevealed = true;
    revealedCells.push_back(std::make_pair(x, y));

    // 클릭한 셀이 지뢰인 경우
    if (mineField[y][x].isMine) {
        gameOver = true; // 게임 상태를 게임 오버로 설정

        // 모든 지뢰를 드러냅니다.
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if (mineField[row][col].isMine) {
                    mineField[row][col].isRevealed = true;
                    revealedCells.push_back(std::make_pair(col, row)); // 지뢰의 좌표를 추가
                }
            }
        }
        CheckWinCondition();
        return revealedCells; // 지뢰를 클릭했으므로 탐색을 종료하고 반환합니다.
    }

    // 주변 지뢰가 없는 경우 BFS 또는 DFS를 사용하여 인접 셀 탐색
    if (mineField[y][x].surroundingMines == 0) {
        if (useBFS) {
            RevealAdjacentCellsBFS(x, y, revealedCells);
        }
        else {
            RevealAdjacentCellsDFS(x, y, revealedCells);
        }
    }

    // **여기에 승리 조건 확인 로직 추가**
    CheckWinCondition(); // 모든 비지뢰 셀이 열렸는지 확인

    return revealedCells; // 탐색된 모든 셀의 좌표를 반환합니다.
}




// BFS 탐색: 빈 칸 주변 열기
void Ms_Logic::RevealAdjacentCellsBFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells) {
    std::queue<std::pair<int, int>> q; // 탐색 큐
    q.push(std::make_pair(x, y));

    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 }; // 8방향 X 좌표
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 }; // 8방향 Y 좌표

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();

        int cx = current.first;
        int cy = current.second;

        for (int i = 0; i < 8; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            // 경계 조건 및 이미 열린 셀 제외
            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                !mineField[ny][nx].isRevealed && !mineField[ny][nx].isMine) {
                mineField[ny][nx].isRevealed = true;
                revealedCells.push_back(std::make_pair(nx, ny)); // 열린 셀 좌표 저장

                // 주변 지뢰가 없는 경우 큐에 추가
                if (mineField[ny][nx].surroundingMines == 0) {
                    q.push(std::make_pair(nx, ny));
                }
            }
        }
    }
  
}

// DFS 탐색: 빈 칸 주변 열기
void Ms_Logic::RevealAdjacentCellsDFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells) {
    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 }; // 8방향 X 좌표
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 }; // 8방향 Y 좌표

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
            !mineField[ny][nx].isRevealed && !mineField[ny][nx].isMine) {
            mineField[ny][nx].isRevealed = true;
            revealedCells.push_back(std::make_pair(nx, ny)); // 열린 셀 좌표 저장

            // 주변 지뢰가 없는 경우 재귀적으로 탐색
            if (mineField[ny][nx].surroundingMines == 0) {
                RevealAdjacentCellsDFS(nx, ny, revealedCells);
            }
        }
    }
  
}

// 깃발 설정/해제
// 깃발 및 물음표 설정/해제
void Ms_Logic::ToggleFlag(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || mineField[y][x].isRevealed) {
        return; // 경계 초과 또는 이미 열려 있는 셀은 무시
    }

    if (mineField[y][x].isFlagged) {
        // 깃발에서 물음표로 전환
        mineField[y][x].isFlagged = false;
        mineField[y][x].isQMark = true;
        remainingMines++; // 깃발 해제 → 지뢰 개수 증가
        
    }
    else if (mineField[y][x].isQMark) {
        // 물음표에서 기본 상태로 전환
        mineField[y][x].isQMark = false;
       
    }
    else {
        // 기본 상태에서 깃발로 전환
        mineField[y][x].isFlagged = true;
        
        remainingMines--; // 깃발 설정 → 지뢰 개수 감소
       
    }
    CheckWinCondition();
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
    gameWon = true; // 기본값: 승리로 설정

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // 지뢰가 아닌 셀은 반드시 열려 있어야 함
            if (!mineField[y][x].isMine && !mineField[y][x].isRevealed ) {
                gameWon = false;
                return;
            }
            // 지뢰가 있는 셀은 반드시 깃발이 꽂혀 있어야 함
            if ((mineField[y][x].isMine && !mineField[y][x].isFlagged) ) {
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

// 셀 클릭 상태 설정
void Ms_Logic::SetCellClicked(int x, int y, bool clicked) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        mineField[y][x].isClicked = clicked;
    }
   
}

// 남은 지뢰 개수 반환
int Ms_Logic::GetRemainingMines() const {

    return remainingMines;

}




void Ms_Logic::ResetGameState() {
    gameOver = false;  // 게임 오버 상태 초기화
    gameWon = false;   // 게임 승리 상태 초기화
    remainingMines = mineCount;  // 남은 지뢰 개수 초기화
}

//// Ms_Logic 클래스 내부
//bool Ms_Logic::IsFirstClick() const {
//    return isFirstClick;
//}
//
//void Ms_Logic::SetFirstClick(bool value) {
//    isFirstClick = value;
//}
