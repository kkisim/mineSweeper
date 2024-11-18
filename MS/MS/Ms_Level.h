#pragma once
#ifndef MS_LEVEL
#define MS_LEVEL
#include "string" ///이름 사용을 위해 불러옴


class  Ms_level //난이도 설정을 위한 클래스
{
public:
    //멤버 변수 초기화
    Ms_level(const std::string& name, int width, int height, int mines) {
        this->name = name;
        this->width = width;
        this->height = height;
        this->mines = mines;
    }

    // 이름 반환
    std::string getName() const { return name; }

    // 가로 크기 반환
    int getWidth() const { return width; }

    // 세로 크기 반환
    int getHeight() const { return height; }

    // 지뢰 개수 반환
    int getMines() const { return mines; }

private:
	std::string name;  // 난이도 이름 (쉬움,보통,어려움)
	int width;         // 가로 크기
	int height;        // 세로 크기
	int mines;         // 지뢰 개수
};



#endif 