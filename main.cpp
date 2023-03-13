
#include "Sort.h"
#include <chrono>
#include <functional>
#include <string>
struct Att{
    float timer;
    void(*function)(int *,int);
};
void insertSortF(float* a, int n){
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && a[j - 1] > a[j]; j--) {
            std::swap(a[j - 1], a[j]);
        }
    }
}
void secundomer() {
    int size = 100;
    int slag;
    void (*func[6])(int *, int) ={countSort,quickSort, mergeSort,
                                          bubbleSort, insertSort,gnomeSort};
    auto ttime_array=new Att [6];
    for (int i = 0; i < 6; ++i) {
        ttime_array[i].function =func[i];
        ttime_array[i].timer=0;
    }
    FILE *flog;
    flog = fopen("result.txt", "w");
    fprintf(flog, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "size","countSort","quickSort","mergeSort",
                                                                        "bubbleSort","insertSort","gnomeSort");
    while (size <= 10000000) {
        slag=size/3;
        fprintf(flog, "%d\t",size);
        srand(time(nullptr));
        int *arr = new int[size];
        auto middle_t=new float [6];
        float aver;
        float sum=0;
        std::chrono::duration<float> res_time;
        for (int h = 0; h<6; h++) {//счётчик,проходящий по массиву функций
            if(ttime_array[h].timer<=20) {
                for (int i = 0; i < 7; ++i) {
                    for (int q = 0; q < size; q++) {
                        arr[q] = rand();
                    }
                    auto start = std::chrono::high_resolution_clock::now(); //подчсёт времени
                    ttime_array[h].function(arr, size);
                    test_Sort(arr, size);
                    auto end = std::chrono::high_resolution_clock::now();
                    res_time = end - start;
                    middle_t[i]=res_time.count();
                }
                insertSortF(middle_t,7);
                for (int i = 3; i <5 ; ++i) {
                    sum=+middle_t[i];
                }
                aver=sum/2;
                ttime_array[h].timer=aver;
                fprintf(flog,"%f\t",ttime_array[h].timer);
            }
        }
        fprintf(flog,"\n");
        size = size + slag;
        delete[] arr;
        delete[] middle_t;
    }
    delete[] ttime_array;
    fclose(flog);
}

int main() {
    secundomer();
    return 0;
}

