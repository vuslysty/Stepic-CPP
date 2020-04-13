#include<iostream>
#include<thread> //Файл в котором определен класс thread
#include<mutex>
using namespace std;

void anyFunc(int const i, mutex &m) {

    // this_thread::sleep_for(chrono::microseconds(10));

    m.lock();
    cout << i << " thread function " << this_thread::get_id() << endl;
    m.unlock();
}

int main() {

    mutex m;
    thread func_thread[100];
    size_t size = sizeof(func_thread) / sizeof(*func_thread);

    for (int i = 0; i < size; i++) {
        func_thread[i] = thread(anyFunc, i, ref(m));
    }

    for (int i = 0; i < size; i++) {

        if (func_thread[i].joinable())
        func_thread[i].join();
    }

    // Выполнение возвращается функции main когда поток заканчивается 
    return 0;
}