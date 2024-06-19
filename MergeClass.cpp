#include <iostream>
#include <vector>
#include <thread>
#include <functional>
using namespace std;
class MergeSort {
public:
    void Sort(vector<int>& array) {
        if (array.size() <= 1) {
            return;
        }
        vector<int> left(array.begin(), array.begin() + array.size() / 2);
        vector<int> right(array.begin() + array.size() / 2, array.end());

        // Sort the halves in parallel
        thread leftThread(&MergeSort::Sort, this, ref(left));
        thread rightThread(&MergeSort::Sort, this, ref(right));

        leftThread.join();
        rightThread.join();

        Merge(array, left, right);
    }

private:
    void Merge(vector<int>& array, const vector<int>& left, const vector<int>& right) {
        size_t leftIndex = 0, rightIndex = 0, mergeIndex = 0;
        while (leftIndex < left.size() && rightIndex < right.size()) {
            if (left[leftIndex] < right[rightIndex]) {
                array[mergeIndex++] = left[leftIndex++];
            } else {
                array[mergeIndex++] = right[rightIndex++];
            }
        }
        while (leftIndex < left.size()) {
            array[mergeIndex++] = left[leftIndex++];
        }
        while (rightIndex < right.size()) {
            array[mergeIndex++] = right[rightIndex++];
        }
    }
};