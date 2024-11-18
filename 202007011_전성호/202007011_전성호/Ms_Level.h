#pragma once
#ifndef MS_LEVEL
#define MS_LEVEL
#include "string" ///�̸� ����� ���� �ҷ���


class  Ms_level //���̵� ������ ���� Ŭ����
{
public:
    //��� ���� �ʱ�ȭ
    Ms_level(const std::string& name, int width, int height, int mines) {
        this->name = name;
        this->width = width;
        this->height = height;
        this->mines = mines;
    }

    // �̸� ��ȯ
    std::string getName() const { return name; }

    // ���� ũ�� ��ȯ
    int getWidth() const { return width; }

    // ���� ũ�� ��ȯ
    int getHeight() const { return height; }

    // ���� ���� ��ȯ
    int getMines() const { return mines; }

private:
	std::string name;  // ���̵� �̸� (����,����,�����)
	int width;         // ���� ũ��
	int height;        // ���� ũ��
	int mines;         // ���� ����
};



#endif 