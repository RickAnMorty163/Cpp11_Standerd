#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>

using namespace std;

void func(string s)
{
    for (int i = 0; i < 10; i++)
    {
        cout << s << endl;
        Sleep(100);
    }
}
signed main()
{
    // thread（function,Args...);
    std::thread t1(func, "OMO");

    auto f = []
    {for(int i=0;i<10;i++){cout<<"lambda function "<<endl;Sleep(100);} };
    std::thread t2(f);

    cout << "Start to Work " << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "main thread Working..." << endl;
        Sleep(100);
    }
    cout << "Finish Work" << endl;
    cout << "Thread Finish" << endl;

    t1.join();
    t2.join();

    return 0;
}