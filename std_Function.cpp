#include <iostream>
#include <functional>
using namespace std;

// functional包装器
void showMessage(const string &message)
{
    cout << message << '\n';
}

class AA
{
public:
    static void showMessage(const string &message)
    {
        cout << message << endl;
    }
    void operator()()
    {
        cout << "this is a () function" << endl;
    }
    void numsAdd(int num)
    {
        cout << ++num << endl;
    }
};
signed main()
{
    // 包装普通函数
    function<void(const string &)> fn = showMessage;
    fn("Hello World");

    // 包装静态成员函数
    function<void(const string &)> fn2 = &AA::showMessage;
    fn2("Hello World");

    // 包装仿函数
    AA a;
    a();
    function<void()> fn3 = AA();
    fn3();

    // 包装普通成员函数
    function<void(AA &, int num)> fn4 = &AA::numsAdd;
    AA aa;
    fn4(aa, 41);

    // 异常
    function<void(int)> fn0;
    try
    {
        fn0(42);
    }
    catch (std::bad_function_call e)
    {
        cout << "使用未包装的function对象会抛出异常" << endl;
    }
}