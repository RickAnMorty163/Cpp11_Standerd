#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
// atomic原子类型

using namespace std;

signed main()
{
    atomic<int> a = 3;
    cout << a.load() << endl;
    a.store(2);
    cout << a.load() << '\n';
    a = 42;
    cout << a.load() << endl;

    int sum0;
    sum0 = a.fetch_add(5);            // fetch__add相当于后缀加a++;
    cout << "sum0= " << sum0 << endl; // sum0=42,a=47

    auto temp_get_atomic = a.exchange(24); // 取出42，放入24
    cout << temp_get_atomic << endl;
    cout << "now atomic value " << a.load() << endl;

    // CAS指令 -> 实现无锁队列

    atomic<int> t = 3;
    int expect = 4; // 期待值
    int val = 5;    // 打算存入的原子变量的值

    bool bret = t.compare_exchange_strong(expect, val);
    // 比较原子变量的值和预期值expect,如果相同，则存入val,返回true
    // 反之用原子变量的值更新expect的值,返回false
    cout << "bret:" << bret << endl;     // false
    cout << "expect:" << expect << endl; // expect=3
    cout << "val:" << val << endl;       // val=5

    cout << "检查编译器是否支持原子类型" << t.is_lock_free() << endl;

    // 原子类型重载了各种类型的运算符
}