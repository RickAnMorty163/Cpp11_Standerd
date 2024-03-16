#include <iostream>
#include <windows.h>
#include <thread>
using namespace std;
void func(std::string s)
{
    this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << this_thread::get_id() << std::endl;
    std::cout << "hello," << s << std::endl;
}
void func0()
{
    std::cout << this_thread::get_id() << std::endl;
    std::cout << "This is function " << std::endl;
}
signed main()
{
    std::thread t1(func, "world");
    thread t2(func0);
    thread t3(std::move(t2));
    cout << "CPU:" << thread::hardware_concurrency() << endl;

    t1.join();
    t3.join();
}