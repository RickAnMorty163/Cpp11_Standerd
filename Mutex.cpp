#include <iostream>
#include <mutex>  //std::once_flag  std::call_once()
#include <thread> //std::thread::ndative_handle()获取原生的操作系统线程句柄

using namespace std;

once_flag onceflag; // once_flag全局变量，本质上是0-1锁
void once_func()
{

    cout << "this function is only called once" << endl;
}
void func()
{
    call_once(onceflag, once_func);
    for (int i = 0; i < 10; ++i)
    {
        cout << "the " << i << " 's use func " << '\n';
    }
}
signed main()
{
    thread t1(func);
    thread t2(func);

    t1.join();
    t2.join();
}