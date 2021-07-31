#pragma once

#include <vector>
#include <math.h>
#include <iostream>

template<typename T>
class MatrixTool {
public:
    void rotate90clockwise(std::vector<T>& arr);
private:
    int size = 0;
    int getInd(int x, int y);
};

template<typename T>
void MatrixTool<T>::rotate90clockwise(std::vector<T>& arr){
    int n = (int)(sqrt(arr.size()));
    size = n;
    if ((n * n) != arr.size()) {
        std::cout << "Matrix Tool : size error" << std::endl;
        return;
    }

    int maxInd = size - 1;
    for (int x = 0; x < n / 2; x++) {
        for (int y = 0; y < maxInd - x; y++) {
            int temp                            = arr[getInd(x, y)];
            arr[getInd(x, y)]                   = arr[getInd(y, maxInd - x)];
            arr[getInd(y, maxInd - x)]          = arr[getInd(maxInd - x, maxInd - y)];
            arr[getInd(maxInd - x, maxInd - y)] = arr[getInd(maxInd - y, x)];
            arr[getInd(maxInd - y, x)]          = temp;
        }
    }
}

template<typename T>
int MatrixTool<T>::getInd(int x, int y){
    return x + (y * size);
}
