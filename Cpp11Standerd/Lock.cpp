#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mtx; // 互斥锁对象

int N = 0;
// void func()
//{
// for (int i = 0; i < 1e5; ++i)
// {
//     //cout << "lock on " << this_thread::get_id() << '\n';
//     mtx.lock();
//     //cout << "locking " << this_thread::get_id() << '\n';
//     N++;
//     //this_thread::sleep_for(std::chrono::seconds(5));
//     mtx.unlock();
//     //cout << "unlock " << this_thread::get_id() << '\n';
//     //this_thread::sleep_for(std::chrono::seconds(1));
// }
//}
void func()
{
    for (int i = 0; i < 1e5; ++i)
    {
        lock_guard<mutex> m_lock(mtx); // lock_guard模板类，构造时加锁，析构时解锁(RALL思想)
        N++;
    }
}
signed main()
{ // 超时互斥锁
    // timed_mutex tm;
    // tm.try_lock_for(std::chrono::seconds(10));
    // 递归互斥锁->解决死锁问题
    // recursive_mutex rm;
    // rm.lock();
    // rm.unlock();

    thread t1(func);
    thread t2(func);

    t1.join();
    t2.join();

    std::cout << "N=" << N << endl;
}
