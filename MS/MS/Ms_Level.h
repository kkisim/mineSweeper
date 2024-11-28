
#ifndef MS_LEVEL
#pragma once
#define MS_LEVEL

#include <string>

class Ms_level {
public:
    Ms_level(const std::string& name, int width, int height, int mines)
        : name(name), width(width), height(height), mines(mines) {
    }

    std::string getName() const { return name; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMines() const { return mines; }
    void setMines(int newMines) { mines = newMines; }

private:
    std::string name;
    int width;
    int height;
    int mines;
};

 //전역 객체 선언
extern Ms_level Easy;
extern Ms_level Normal;
extern Ms_level Hard;

#endif
