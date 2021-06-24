#include <iostream>
#include <chrono>
#include <thread>
#include <random>
using namespace std;

/*
  Write a function that can measure the execution time of a function
  (with any number of arguments) in any required duration (such as
  seconds, milliseconds, microseconds, and so on).
*/

template< typename Time = ratio<1>, typename Clock = chrono::steady_clock >
struct Timer
{
    template< typename Func, typename... Args >
    static double duration(Func f, Args...args)
    {
        auto begin = Clock::now();
        (f(args), ...);
        auto end = Clock::now();
        return chrono::duration<double, Time>(end - begin).count();
    }
};

void someFunc1(int a)
{
//    cout << a << endl;
    this_thread::sleep_for(100ms);
}

void someFunc2(string a)
{
//    cout << a << endl;
    this_thread::sleep_for(1s);

}
int main()
{
    thread t1([]() {
        auto time1 = Timer<>::duration(someFunc1, 1, 2, 3, 4, 5);
        cout << "Timer 1: " << time1 << " seconds" << endl;
    });

    thread t2([]() {
        auto time2 = Timer<ratio<60>>::duration(someFunc1, 1, 2, 3, 4, 5);
        cout << "Timer 2: " << time2 << " minutes" << endl;
    });
    thread t3([]() {
        auto time3 = Timer<>::duration(someFunc2, "Juan", "Leroy", "Jason", "Eddy");
        cout << "Timer 3: " << time3 << " seconds" << endl;
    });

    thread t4([]() {
        auto time4 = Timer<ratio<3600>>::duration(someFunc2, "Juan", "Leroy", "Jason");
        cout << "Timer 4: " << time4 << " hours" << endl;
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();


    return 0;
}
