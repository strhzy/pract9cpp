#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <string>
#include "MergeClass.cpp"
#include <vector>
using namespace std;

int main() {
    MergeSort sorter;
    
    cout << "Введите количество элементов массива: ";
    int num;
    cin >> num;
    vector<int> array(num);
    for (int i = 0; i < num; ++i) {
        cout << "Введите " << i+1 << " элемент массива: ";
        cin >> array[i];
    }

    auto sortFunc = [&sorter](vector<int>& arr) {
        sorter.Sort(arr);
    };

    thread mergeSortThread(sortFunc, ref(array));

    mergeSortThread.join();

    cout << "Отсортированный массив: ";
    for (const int& num : array) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}