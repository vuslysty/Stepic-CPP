#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <stack>

int * find_medium(int *start, int *end) {
    int min = *start;
    int max = *start;

    for (int *i = start; i <= end; i++) {
        if (min > *i)
            min = *i;
        if (max < *i)
            max = *i;
    }

    int smallest_diff = INT32_MAX;

    int *medium = start;
    for (int *i = start; i <= end; i++) {
        int distance_to_min = abs(min - *i);
        int distance_to_max = abs(max - *i);
        int diff = abs(distance_to_max - distance_to_min);
        if (smallest_diff > diff) {
            smallest_diff = diff;
            medium = i;
            if (smallest_diff <= 1)
                break ;
        }
    }

    return medium;
}

int * find_medium(int *start, int *end, int part) {
    int min = *start;
    int max = *start;

    for (int *i = start; i <= end; i++) {
        if (min > *i)
            min = *i;
        if (max < *i)
            max = *i;
    }

    int prefered_dist = (part - 1) * 100;

    int *partition_ptr = start;
    int greater_diff = INT32_MAX;
    
    for (int *i = start; i <= end; i++) {
        int distance_to_min = abs(min - *i);
        int distance_to_max = abs(max - *i);

        if (distance_to_min >= distance_to_max) {
            int curr_distance = (distance_to_min * 100) / (distance_to_max + 1);

            if (abs(curr_distance - prefered_dist) < greater_diff) {
                greater_diff = abs(curr_distance - prefered_dist);
                partition_ptr = i;
                if (greater_diff == prefered_dist)
                    break;
            }
        }
    }

    return partition_ptr;
}


int * partition(int *start, int *end) {
    bool go_forward = true;
    // int *real_start = start;

    while (start < end) {
        if (*start > *end) {
            std::swap(*start, *end);
            go_forward ? end-- : start++;
            go_forward = !go_forward;
        } else {
            go_forward ? start++ : end--;
        }
    }

    // int value = *end;

    return end;
}

std::pair<int*, int*> new_partition(int *start, int *end) {

    std::pair<int*, int*> p;
    
    p.first = partition(start, end);
    p.second = p.first;

    for (int *i = start; i <= p.first; i++) {
        while (p.first != i && *p.first == *(p.first - 1))
            p.first--;
        if (*i == *p.first && i < p.first)
            std::swap(*i, *(p.first - 1));
    }

    for (int *i = end; i >= p.second; i--) {
        while (p.second != i && *p.second == *(p.second + 1))
            p.second++;
        if (*i == *p.second && i > p.second)
            std::swap(*i, *(p.second + 1));
    }

    return p;
}

void m_qsort(int *start, int *end) {

    int *center = partition(start, end);

    if (start != center)
        m_qsort(start, center - 1);
    if (end != center)
        m_qsort(center + 1, end);
}

void new_m_qsort(int *start, int *end) {

    std::pair<int*, int*> p = new_partition(start, end);

    if (start != p.first)
        m_qsort(start, p.first - 1);
    if (end != p.second)
        m_qsort(p.second + 1, end);
}

std::stack<std::pair<int*, int*>> get_range_stack(int *start, int *end, size_t parts) {
    
    std::stack<std::pair<int*, int*>> range_stack; // range stack;
    std::pair<int*, int*> pair;

    for (int i = 0; i < parts && start != end; i++) {

        if (!range_stack.empty())
            end = range_stack.top().first - 2;

        if (parts - i == 1) {
            pair.first = start;
            pair.second = end;
        } else {
            int *elem = find_medium(start, end, parts - i);
            std::swap(*elem, *end);
            int* partition_place = partition(start, end);

            if (partition_place == end) {
                parts /= 2;
                continue ;
            } else {
                pair.first = partition_place + 1;
                pair.second = end;
            }
        }
        range_stack.push(pair);
    }
    return range_stack;
}

void qsort_in_2_threads(int *start, int *end) {

    std::thread array_threads[2];

    int *elem = find_medium(start, end, 2);
    std::swap(*elem, *end);
    int* partition_place = partition(start, end);

    array_threads[0] = std::thread(m_qsort, start, partition_place - 1);
    array_threads[1] = std::thread(m_qsort, partition_place + 1, end);

    array_threads[0].join();
    array_threads[1].join();
}

void qsort_in_threads(int *start, int *end, size_t threads) {

    std::stack<std::pair<int*, int*>> range_stack; // range stack;
    std::stack<std::thread> threads_stack;

    range_stack = get_range_stack(start, end, threads);

    while (!range_stack.empty()) {

        threads_stack.push(std::thread(m_qsort, range_stack.top().first, range_stack.top().second));
        range_stack.pop();
    }

    while (!threads_stack.empty()) {
        if (threads_stack.top().joinable())
            threads_stack.top().join();
        threads_stack.pop();
    }
}

void bubble_sort(int *start, int *end) {

    for (int *i = start; i < end; i++)
        for (int *j = start; j < end; j++)
            if (*j > *(j + 1))
                std::swap(*j, *(j + 1) );
}

int main() {

    const int num_elem = 1000000;
    int max_elem = 100000;
    int thread_num = 2;

    srand (time(NULL)); 


    int *data = new int[num_elem];// {4, 4, 4, 3, 4, 4, 4, 4, 4, 4};
    for (int i = 0; i < num_elem; i++) {
        data[i] = 1 + rand() % max_elem;
    }

    auto start = std::chrono::steady_clock::now();



    // qsort_in_threads(&data[0], &data[num_elem - 1], thread_num);
    // qsort_in_2_threads(&data[0], &data[num_elem - 1]);
    m_qsort(&data[0], &data[num_elem - 1]);
    // new_m_qsort(&data[0], &data[num_elem - 1]);
    // bubble_sort(&data[0], &data[num_elem - 1]);
    

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << duration.count() / 1000.0 << " seconds" << std::endl;

    return 0;
}