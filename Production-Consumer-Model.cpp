#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <queue>
#include <condition_variable> //条件变量

// 生产—消费者模型
using namespace std;

class AA
{
    mutex m_mutex;                    // 互斥锁
    condition_variable m_cond;        // 条件变量
    queue<string, deque<string>> m_q; // 缓存队列
public:
    // 生产者线程
    void incache(int num) // 生产num个数据
    {
        lock_guard<mutex> lock(m_mutex); // 申请加锁
        for (int i = 0; i < num; i++)
        {
            static int index = 1;
            string message = to_string(index++) + "data"; // 生成一个数据
            m_q.push(message);                            // 将数据加入缓存队列
        }
        // m_cond.notify_one(); // 唤醒"一个"被当前条件变量m_cond阻塞的线程
        m_cond.notify_all(); // 唤醒全部线程
    }
    // 消费者线程
    void outcache()
    {
        while (true)
        {
            string message;
            {
                unique_lock<mutex> lock(m_mutex);

                while (m_q.empty())
                    m_cond.wait(lock); // 当队列为空时，当前线程被阻塞，等待生产者唤醒信号，直到新元素入队

                message = m_q.front();
                m_q.pop();
                cout << "thread:" << this_thread::get_id() << ", " << message << endl;
            }
            // 处理出队的数据
            this_thread::sleep_for(chrono::milliseconds(1)); // 假设需要1ms
            // cout << "thread:" << this_thread::get_id() << ", " << message << endl;
        }
    }
};
signed main()
{
    AA aa;

    thread t1(&AA::outcache, &aa);
    thread t2(&AA::outcache, &aa);
    thread t3(&AA::outcache, &aa);

    this_thread::sleep_for(chrono::seconds(3));
    aa.incache(3); // 生产3个数据

    this_thread::sleep_for(chrono::seconds(5));
    aa.incache(5); // 生产5个数据

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
