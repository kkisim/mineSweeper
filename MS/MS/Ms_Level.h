#pragma once
#include <string> // �̸� ����� ���� �ҷ���

class Ms_level // ���̵� ������ ���� Ŭ����
{
public:
    // �����ڸ� ���� ��� ���� �ʱ�ȭ
    Ms_level(const std::string& name, int width, int height, int mines)
        : name(name), width(width), height(height), mines(mines) {
    }

    // �̸� ��ȯ
    std::string getName() const { return name; }

    // �̸� ����
    void setName(const std::string& newName) { name = newName; }

    // ���� ũ�� ��ȯ
    int getWidth() const { return width; }

    // ���� ũ�� ����
    void setWidth(int newWidth) { width = newWidth; }

    // ���� ũ�� ��ȯ
    int getHeight() const { return height; }

    // ���� ũ�� ����
    void setHeight(int newHeight) { height = newHeight; }

    // ���� ���� ��ȯ
    int getMines() const { return mines; }

    // ���� ���� ����
    void setMines(int newMines) { mines = newMines; }

private:
    std::string name; // ���̵� �̸� (����)
    int width;        // ���� ũ�� (����)
    int height;       // ���� ũ�� (����)
    int mines;        // ���� ���� (����)
};
extern Ms_level Easy;
extern Ms_level Normal;
extern Ms_level Hard;