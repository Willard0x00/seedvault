#include <iostream>
#include <thread>
#include <intrin.h>

#include "Clock.h"
#include "cpu_info.h"
void math_stuff() {
    double d = 12319.123123123;

    while(1) {
        d += 1231.1241241;
        d *= d;
        d /= d;
        d += d;
        d -= d;
    }
}

void make_stuff() {
    while(1) {
        float* data = new float[1000000000];
        delete[] data;
    }
}

void rec_stuff(int count) {
    if( count >= 10000 ) {
        return; 
    }
    rec_stuff(count + 1);
}

void rec_stuff_m() {
    while(1) {
        rec_stuff(0);
    }
}

int main() {
    std::cout << "yo\n";

//    std::thread math_stuff_t(math_stuff);
//    std::thread make_stuff_t(make_stuff);
//    std::thread rec_stuff_t(rec_stuff_m);
//    math_stuff_t.detach();
//    make_stuff_t.detach();
//    rec_stuff_t.detach();

    Clock clock;

    CPUInfo cpu_info;
    cpu_info.print();




   // while(1) {
   //     clock.update();
//      std::cout << "\r " << clock.get_fps();
  //  }
    std::cout << "\n";

    return 0;
}
