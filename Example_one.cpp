#include <iostream>
#include <thread>
#include <functional>
using namespace std;

// 可变函数及参数实现
void show0()
{
    cout << "space function OMO " << endl;
}
void show1(const string &s)
{
    cout << s << " function has one ref " << endl;
}

class CC
{
public:
    void show2(int x, const string &s)
    {
        cout << x << " and " << s << " is the two reference " << endl;
    }
};

template <typename Fn, typename... Args>
auto show(Fn &&fn, Args &&...args) // 支持移动语义
//->decltype(bind(forward<Fn>(fn), forward<Args>(args)...)) //C++14标准中不必再使用decltype
{
    cout << "Begin>>>" << endl;
    // args...参数包可以作为整体传入并自动匹配占位符
    // 使用完美转发std::forward<T>保持参数右值属性
    auto f = bind(forward<Fn>(fn), forward<Args>(args)...); // 使用包装器bind实现thread构造函数的效果
    f();
    cout << "Endl>>>" << endl;

    return f;
}
signed main()
{
    // thread t1(show0);
    // thread t2(show1, "message");
    // CC cc;
    // thread t3(&CC::show2, &cc, 42, "message");
    // t1.join();
    // t2.join();
    // t3.join();

    show(show0);
    show(show1, " change ");
    CC cc;
    auto func = show(&CC::show2, &cc, 42, "message");
    func();
}
