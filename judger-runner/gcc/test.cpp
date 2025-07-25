#include <iostream>

int main() {
    long long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i;
    }
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}

/*

g++ test.cpp -o test_cpp
./test_cpp

*/