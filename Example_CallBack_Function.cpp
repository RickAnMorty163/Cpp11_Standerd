#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <deque>
#include <queue>
#include <condition_variable>
using namespace std;
void show(const string &message)
{
    cout << "Deal with message " << endl;
}
class AA
{
    mutex m_mutex;
    condition_variable m_cond;
    queue<string, deque<string>> m_q;
    function<void(const string &)> m_callback;

public:
    // 注册回调函数callback，接受一个参数
    template <typename Fn, typename... Args>
    void callback(Fn &&fn, Args &&...args)
    {
        // 当args参数包没有参数无法展开时，std::placeholders::_1占位
        m_callback = bind(forward<Fn>(fn), forward<Args>(args)..., placeholders::_1);
    }
    void incache(int num)
    {
        lock_guard<mutex> lock(m_mutex);
        for (int i = 0; i < num; i++)
        {
            static int index = 1;
            string message = to_string(index++) + "data";
            m_q.push(message);
        }
        m_cond.notify_all();
    }
    void outcache()
    {
        while (true)
        {
            unique_lock<mutex> lock(m_mutex);

            while (m_q.empty())
                m_cond.wait(lock);

            string message = m_q.front();
            m_q.pop();
            cout << "thread:" << this_thread::get_id() << ", " << message << endl;
            lock.unlock();
            // 处理数据
            // this_thread::sleep_for(chrono::milliseconds(1));
            if (m_callback)
                m_callback(message); // 将接受到的参数message传递给回调函数
        }
    }
};
signed main()
{
    AA aa;
    aa.callback(show);

    thread t1(&AA::outcache, &aa);
    thread t2(&AA::outcache, &aa);
    thread t3(&AA::outcache, &aa);

    this_thread::sleep_for(chrono::seconds(3));
    aa.incache(3);
    this_thread::sleep_for(chrono::seconds(5));
    aa.incache(5);
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
