#include <iostream>
#include <functional>

using namespace std;

// std::bind 绑定器
void show(const string &s)
{
    cout << "Hello," << s << endl;
}
void show_other(const string &s, int x)
{
    cout << x << " Hello, " << s << endl;
}
signed main()
{
    function<void(const string &)> fn = show;
    fn("World");
    function<void(const string &)> fn0 = bind(show, placeholders::_1); // 参数占位符
    fn0("python");
    // 绑定缺省参数 tip:缺省参数为值传递，若要改为引用传递，使用std::ref;
    function<void(const string &)> f = bind(show_other, placeholders::_1, 42);
    f("world");
    // 调换参数位置
    function<void(int, const string &)> fn3 = std::bind(show_other, placeholders::_2, placeholders::_1);
    fn3(1, "world");
    // 无效参数绑定
    function<void(const string &, int)> f_zero = bind(show, placeholders::_1);
    f_zero("world", 0);
}