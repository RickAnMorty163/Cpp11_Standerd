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
            // 把互斥锁转换成unique_lock<mutex>,并申请加锁
            unique_lock<mutex> lock(m_mutex);

            // 使用while死循环的目的：防止条件变量虚假唤醒，即消费者线程被唤醒后，缓存队列中没有数据
            while (m_q.empty())
                // wait():1.解开互斥锁 -> 2.阻塞，等待被唤醒，-> 3.给互斥锁加锁
                m_cond.wait(lock); // 当队列为空时，当前线程被阻塞，等待生产者唤醒信号，直到新元素入队
            // m_cond.wait(lock,[this]{return !m_q.empty();});//wait方法重载版本，效果与while相同
            //  数据元素出队
            string message = m_q.front();
            m_q.pop();
            cout << "thread:" << this_thread::get_id() << ", " << message << endl;
            lock.unlock();

            // 处理出队的数据
            this_thread::sleep_for(chrono::milliseconds(1)); // 假设需要1ms
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
