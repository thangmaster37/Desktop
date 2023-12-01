#pragma once
#include <iostream>
#include <vector>

class Object
{
private:
    std::pair<int, int> current;
    int lengthPath;
    bool getTarget;

public:
    Object(std::pair<int, int> start) {
        current = start;
        lengthPath = 0;
        getTarget = false;
    }

    void move(std::pair<int, int> point) {
        // Khi sử dụng cần đảm bảo trước sử dụng point là hàng xóm của current 
        // Tránh trường hợp dịch chuyển tức thời 
        current = point;
        ++lengthPath;
    }

    bool isTarget() {
        return getTarget;
    }

    void gotTarget() {
        getTarget = true;
    }

    std::pair<int, int> currentPoint() {
        return current;
    }

    int length() {
        return lengthPath;
    }
};