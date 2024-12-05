#include "Ms_Logic.h"
#include <cstdlib>
#include <ctime>
#include <queue>

// ������: ������ ũ��, ���� ����, Ž�� ���(BFS �Ǵ� DFS)�� �ʱ�ȭ�մϴ�.
Ms_Logic::Ms_Logic(int width, int height, int mines, bool useBFS)
    : width(width), height(height), mineCount(mines), remainingMines(mines),
    gameOver(false), gameWon(false), useBFS(useBFS) {
    // ���� ���¸� �����ϴ� 2D �迭 �ʱ�ȭ
    mineField.resize(height, std::vector<Cell>(width));
    InitializeBoard();
}

// ���� �ʱ�ȭ: �� ���� ���¸� �⺻������ ����
void Ms_Logic::InitializeBoard() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            mineField[i][j].isMine = false;          // ���� ���� �ʱ�ȭ
            mineField[i][j].isRevealed = false;      // ���� ���� �ʱ�ȭ
            mineField[i][j].isFlagged = false;       // ��� ���� �ʱ�ȭ
            mineField[i][j].surroundingMines = 0;    // �ֺ� ���� ���� �ʱ�ȭ
            mineField[i][j].isClicked = false;       // Ŭ�� ���� �ʱ�ȭ
            mineField[i][j].isQMark = false;         // ����ǥ ���� �ʱ�ȭ
        }
    }
}



 // ���� ��ġ: ���忡 ���ڸ� �������� ��ġ
void Ms_Logic::PlaceMines(int startX, int startY, int exclusionRadius) {
    srand(static_cast<unsigned>(time(0))); // ���� �õ� ����
    int placedMines = 0;

    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;

        // ��ġ ����: ���ڰ� ���� ���̰�, ���� ��ġ �� �ݰ� ����
        if (!mineField[y][x].isMine &&
            //(startX == -1 || startY == -1 || // ó�� Ŭ������ ���� ���¿����� ���� ����
            !(x >= startX - exclusionRadius && x <= startX + exclusionRadius &&
                y >= startY - exclusionRadius && y <= startY + exclusionRadius)) {
            mineField[y][x].isMine = true; // ���� ��ġ
            placedMines++;
        }
    }
}


// �ֺ� ���� ���� ���: �� ���� ������ ���� ������ ���
void Ms_Logic::CalculateSurroundingMines() {
    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 }; // 8���� X ��ǥ
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 }; // 8���� Y ��ǥ

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (mineField[y][x].isMine) continue; // ���ڰ� �ִ� ���� �ǳʶ�

            int count = 0;
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                // ��� ���� ���� ���� ī��Ʈ
                if (nx >= 0 && nx < width && ny >= 0 && ny < height && mineField[ny][nx].isMine) {
                    count++;
                }
            }
            mineField[y][x].surroundingMines = count; // �ֺ� ���� ���� ����
        }
    }
}

std::vector<std::pair<int, int>> Ms_Logic::RevealCell(int x, int y) {
    std::vector<std::pair<int, int>> revealedCells;

    // ��� ����: ������ ������ ����ų� �̹� ���� �ְų� �÷��װ� ������ ���� �����մϴ�.
    if (x < 0 || x >= width || y < 0 || y >= height || mineField[y][x].isRevealed || mineField[y][x].isFlagged) {
        return revealedCells;
    }

    // ���� ���� ���� �ش� ��ǥ�� Ž���� �� ��Ͽ� �߰��մϴ�.
    mineField[y][x].isRevealed = true;
    revealedCells.push_back(std::make_pair(x, y));

    // Ŭ���� ���� ������ ���
    if (mineField[y][x].isMine) {
        gameOver = true; // ���� ���¸� ���� ������ ����

        // ��� ���ڸ� �巯���ϴ�.
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if (mineField[row][col].isMine) {
                    mineField[row][col].isRevealed = true;
                    revealedCells.push_back(std::make_pair(col, row)); // ������ ��ǥ�� �߰�
                }
            }
        }
        CheckWinCondition();
        return revealedCells; // ���ڸ� Ŭ�������Ƿ� Ž���� �����ϰ� ��ȯ�մϴ�.
    }

    // �ֺ� ���ڰ� ���� ��� BFS �Ǵ� DFS�� ����Ͽ� ���� �� Ž��
    if (mineField[y][x].surroundingMines == 0) {
        if (useBFS) {
            RevealAdjacentCellsBFS(x, y, revealedCells);
        }
        else {
            RevealAdjacentCellsDFS(x, y, revealedCells);
        }
    }

    // **���⿡ �¸� ���� Ȯ�� ���� �߰�**
    CheckWinCondition(); // ��� ������ ���� ���ȴ��� Ȯ��

    return revealedCells; // Ž���� ��� ���� ��ǥ�� ��ȯ�մϴ�.
}




// BFS Ž��: �� ĭ �ֺ� ����
void Ms_Logic::RevealAdjacentCellsBFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells) {
    std::queue<std::pair<int, int>> q; // Ž�� ť
    q.push(std::make_pair(x, y));

    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 }; // 8���� X ��ǥ
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 }; // 8���� Y ��ǥ

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();

        int cx = current.first;
        int cy = current.second;

        for (int i = 0; i < 8; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            // ��� ���� �� �̹� ���� �� ����
            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                !mineField[ny][nx].isRevealed && !mineField[ny][nx].isMine) {
                mineField[ny][nx].isRevealed = true;
                revealedCells.push_back(std::make_pair(nx, ny)); // ���� �� ��ǥ ����

                // �ֺ� ���ڰ� ���� ��� ť�� �߰�
                if (mineField[ny][nx].surroundingMines == 0) {
                    q.push(std::make_pair(nx, ny));
                }
            }
        }
    }
  
}

// DFS Ž��: �� ĭ �ֺ� ����
void Ms_Logic::RevealAdjacentCellsDFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells) {
    int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 }; // 8���� X ��ǥ
    int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 }; // 8���� Y ��ǥ

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
            !mineField[ny][nx].isRevealed && !mineField[ny][nx].isMine) {
            mineField[ny][nx].isRevealed = true;
            revealedCells.push_back(std::make_pair(nx, ny)); // ���� �� ��ǥ ����

            // �ֺ� ���ڰ� ���� ��� ��������� Ž��
            if (mineField[ny][nx].surroundingMines == 0) {
                RevealAdjacentCellsDFS(nx, ny, revealedCells);
            }
        }
    }
  
}

// ��� ����/����
// ��� �� ����ǥ ����/����
void Ms_Logic::ToggleFlag(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || mineField[y][x].isRevealed) {
        return; // ��� �ʰ� �Ǵ� �̹� ���� �ִ� ���� ����
    }

    if (mineField[y][x].isFlagged) {
        // ��߿��� ����ǥ�� ��ȯ
        mineField[y][x].isFlagged = false;
        mineField[y][x].isQMark = true;
        remainingMines++; // ��� ���� �� ���� ���� ����
        
    }
    else if (mineField[y][x].isQMark) {
        // ����ǥ���� �⺻ ���·� ��ȯ
        mineField[y][x].isQMark = false;
       
    }
    else {
        // �⺻ ���¿��� ��߷� ��ȯ
        mineField[y][x].isFlagged = true;
        
        remainingMines--; // ��� ���� �� ���� ���� ����
       
    }
    CheckWinCondition();
}




// ���� ���� ���� ��ȯ
bool Ms_Logic::IsGameOver() const {
    return gameOver;
}

// ���� �¸� ���� ��ȯ
bool Ms_Logic::IsGameWon() const {
    return gameWon;
}

// �¸� ���� Ȯ��
void Ms_Logic::CheckWinCondition() {
    gameWon = true; // �⺻��: �¸��� ����

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // ���ڰ� �ƴ� ���� �ݵ�� ���� �־�� ��
            if (!mineField[y][x].isMine && !mineField[y][x].isRevealed ) {
                gameWon = false;
                return;
            }
            // ���ڰ� �ִ� ���� �ݵ�� ����� ���� �־�� ��
            if ((mineField[y][x].isMine && !mineField[y][x].isFlagged) ) {
                gameWon = false;
                return;
            }

        }
    }
}



// ���� ���� ��ȯ
const std::vector<std::vector<Cell>>& Ms_Logic::GetBoard() const {
    return mineField;
}

// �� Ŭ�� ���� ����
void Ms_Logic::SetCellClicked(int x, int y, bool clicked) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        mineField[y][x].isClicked = clicked;
    }
   
}

// ���� ���� ���� ��ȯ
int Ms_Logic::GetRemainingMines() const {

    return remainingMines;

}




void Ms_Logic::ResetGameState() {
    gameOver = false;  // ���� ���� ���� �ʱ�ȭ
    gameWon = false;   // ���� �¸� ���� �ʱ�ȭ
    remainingMines = mineCount;  // ���� ���� ���� �ʱ�ȭ
}

//// Ms_Logic Ŭ���� ����
//bool Ms_Logic::IsFirstClick() const {
//    return isFirstClick;
//}
//
//void Ms_Logic::SetFirstClick(bool value) {
//    isFirstClick = value;
//}
