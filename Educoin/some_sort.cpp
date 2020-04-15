#include <iostream>

int * partition(int *start, int *end) {
    bool go_forward = true;

    while (start < end) {
        if (*start > *end) {
            std::swap(*start, *end);
            go_forward ? end-- : start++;
            go_forward = !go_forward;
        } else {
            go_forward ? start++ : end--;
        }
    }
    return end;
}

void m_qsort(int *start, int *end) {

    // int size = ((unsigned long long int)(end) - (unsigned long long int)(start)) / sizeof(int) + 1;

    // for (int i = 0; i < size; i++) {
    //     std::cout << start[i] << " ";
    // }
    // std::cout << std::endl;

    int *center = partition(start, end);

    if (start != center)
        m_qsort(start, center - 1);
    if (end != center)
        m_qsort(center + 1, end);
}

void bubble_sort(int *start, int *end) {

    for (int *i = start; i < end; i++)
        for (int *j = start; j < end; j++)
            if (*j > *(j + 1))
                std::swap(*j, *(j + 1) );
}

int main() {

    const int num_elem = 50;
    int max_elem = 100;


    int *data = new int[num_elem];
    for (int i = 0; i < num_elem; i++) {
        data[i] = rand() % max_elem;
    }

    m_qsort(&data[0], &data[num_elem - 1]);
    // bubble_sort(&data[0], &data[num_elem - 1]);

    // partition(&data[0], &data[num_elem - 1]);

    for (int i = 0; i < num_elem; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}