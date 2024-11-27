#pragma once
#include <string> // 이름 사용을 위해 불러옴

class Ms_level // 난이도 설정을 위한 클래스
{
public:
    // 생성자를 통해 멤버 변수 초기화
    Ms_level(const std::string& name, int width, int height, int mines)
        : name(name), width(width), height(height), mines(mines) {
    }

    // 이름 반환
    std::string getName() const { return name; }

    // 이름 설정
    void setName(const std::string& newName) { name = newName; }

    // 가로 크기 반환
    int getWidth() const { return width; }

    // 가로 크기 설정
    void setWidth(int newWidth) { width = newWidth; }

    // 세로 크기 반환
    int getHeight() const { return height; }

    // 세로 크기 설정
    void setHeight(int newHeight) { height = newHeight; }

    // 지뢰 개수 반환
    int getMines() const { return mines; }

    // 지뢰 개수 설정
    void setMines(int newMines) { mines = newMines; }

private:
    std::string name; // 난이도 이름 (가변)
    int width;        // 가로 크기 (가변)
    int height;       // 세로 크기 (가변)
    int mines;        // 지뢰 개수 (가변)
};
extern Ms_level Easy;
extern Ms_level Normal;
extern Ms_level Hard;