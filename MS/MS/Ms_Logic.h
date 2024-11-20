#pragma once
#include <vector>

// �� ���� ���¸� ǥ���ϴ� ����ü
struct Cell {
    bool isMine;            // ���� ����
    bool isRevealed;        // ���� ���ȴ��� ����
    bool isFlagged;         // ��� ǥ�� ����
    int surroundingMines;   // �ֺ� ���� ����
};

// ����ã�� ���� ������ �����ϴ� Ŭ����
class Ms_Logic {
public:
    // ������: ���� ũ��� ���� ������ ����
    Ms_Logic(int width, int height, int mines);

    // ���� �ʱ�ȭ
    void InitializeBoard();

    // ���� ��ġ (ù Ŭ�� ��ġ�� �ֺ��� ����)
    void PlaceMines(int startX, int startY, int exclusionRadius);

    // �ֺ� ���� ���� ���
    void CalculateSurroundingMines();

    // Ư�� �� ����
    void RevealCell(int x, int y);

    // Ư�� �� ��� ����/����
    void ToggleFlag(int x, int y);

    // ���� ���� ���� ��ȯ
    bool IsGameOver() const;

    // ���� �¸� ���� ��ȯ
    bool IsGameWon() const;

    // ���� ���� ���� ��ȯ
    const std::vector<std::vector<Cell>>& GetBoard() const;

private:
    int width;                                 // ������ ���� ũ��
    int height;                                // ������ ���� ũ��
    int mineCount;                             // ���� ����
    bool gameOver;                             // ���� ���� ����
    bool gameWon;                              // ���� �¸� ����
    std::vector<std::vector<Cell>> mineField; // ���� ���¸� �����ϴ� 2D �迭

    // �� ĭ �ֺ� �� ����
    void RevealAdjacentCells(int x, int y);

    // ���� �¸� ���� Ȯ��
    void CheckWinCondition();
};
