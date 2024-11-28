#pragma once

#include <vector>

// ���� ���¸� ��Ÿ���� ����ü
struct Cell {
    bool isMine;            // ���� ����
    bool isRevealed;        // ���� ���ȴ��� ����
    bool isFlagged;         // ��� ǥ�� ����
    bool isQMark = false;  // ����ǥ ���� �߰�
    int surroundingMines;   // �ֺ� ���� ����
    bool isClicked;         // Ŭ�� ���� ����
};

// ����ã�� ���� ������ ó���ϴ� Ŭ����
class Ms_Logic {
public:
    /**
     * @brief ������: ���� ũ��� ���� ������ �ʱ�ȭ�մϴ�.
     * @param width ������ ���� ũ��
     * @param height ������ ���� ũ��
     * @param mines ���� ����
     * @param useBFS Ž�� ��� ���� (true: BFS, false: DFS)
     */
    Ms_Logic(int width, int height, int mines, bool useBFS = true);

    /**
     * @brief ���带 �ʱ�ȭ�մϴ�.
     */
    void InitializeBoard();

    /**
     * @brief Ư�� ��ġ�� �ݰ��� �����ϰ� ���ڸ� ��ġ�մϴ�.
     * @param startX ���� ��ġ X ��ǥ
     * @param startY ���� ��ġ Y ��ǥ
     * @param exclusionRadius ���� �ݰ�
     */
    void PlaceMines(int startX, int startY, int exclusionRadius);

    /**
     * @brief �� ���� �ֺ� ���� ������ ����մϴ�.
     */
    void CalculateSurroundingMines();

    /**
     * @brief Ư�� ���� ���� ������ �� ������ Ž���մϴ�.
     * @param x ���� X ��ǥ
     * @param y ���� Y ��ǥ
     * @return Ž���� ���� ��ǥ�� ��ȯ
     */
    std::vector<std::pair<int, int>> RevealCell(int x, int y);

    /**
     * @brief Ư�� ���� ����� �����ϰų� �����մϴ�.
     * @param x ���� X ��ǥ
     * @param y ���� Y ��ǥ
     */
    void ToggleFlag(int x, int y);

    /**
     * @brief ���� ���� ���θ� Ȯ���մϴ�.
     * @return ������ ����Ǿ����� true
     */
    bool IsGameOver() const;

    /**
     * @brief ���� �¸� ���θ� Ȯ���մϴ�.
     * @return �¸� ������ �����Ǿ����� true
     */
    bool IsGameWon() const;

    /**
     * @brief ������ ���� ���¸� ��ȯ�մϴ�.
     * @return ���� ���¸� �����ϴ� 2D �迭
     */
    const std::vector<std::vector<Cell>>& GetBoard() const;

    /**
     * @brief ���� ���� ������ ��ȯ�մϴ�.
     * @return ���� ���� ����
     */
    int GetRemainingMines() const;

    /**
     * @brief Ư�� ���� Ŭ�� ���¸� �����մϴ�.
     * @param x ���� X ��ǥ
     * @param y ���� Y ��ǥ
     * @param clicked Ŭ�� ����
     */
    void SetCellClicked(int x, int y, bool clicked);

    /**
     * @brief ���� ���¸� �ʱ�ȭ�մϴ�.
     */
    void ResetGameState(); // **���Ӱ� �߰��� �޼��� ����**

private:
    int width;                                // ������ ���� ũ��
    int height;                               // ������ ���� ũ��
    int mineCount;                            // ��ü ���� ����
    int remainingMines;                       // ���� ���� ����
    bool gameOver;                            // ���� ���� ����
    bool gameWon;                             // ���� �¸� ����
    bool useBFS;                              // BFS �Ǵ� DFS ���� ����
    std::vector<std::vector<Cell>> mineField; // ���� ���¸� �����ϴ� 2D �迭

    /**
     * @brief DFS�� ����Ͽ� �� ĭ �ֺ��� Ž���ϰ� ���� ���ϴ�.
     * @param x ���� X ��ǥ
     * @param y ���� Y ��ǥ
     * @param revealedCells Ž���� �� ��ǥ�� ������ ����
     */
    void RevealAdjacentCellsDFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells);

    /**
     * @brief BFS�� ����Ͽ� �� ĭ �ֺ��� Ž���ϰ� ���� ���ϴ�.
     * @param x ���� X ��ǥ
     * @param y ���� Y ��ǥ
     * @param revealedCells Ž���� �� ��ǥ�� ������ ����
     */
    void RevealAdjacentCellsBFS(int x, int y, std::vector<std::pair<int, int>>& revealedCells);

    /**
     * @brief �¸� ������ Ȯ���մϴ�.
     */
    void CheckWinCondition();
};
