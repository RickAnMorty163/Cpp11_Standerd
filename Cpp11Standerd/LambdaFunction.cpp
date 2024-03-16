#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void func(string &s)
{
    cout << "Hello," << s << " World!"
         << "\n";
}

class F
{
public:
    void operator()(const string &s)
    {
        cout << "Hello," << s << " World!"
             << "\n";
    }
};
signed main()
{
    vector<string> str{"Concurrent", "Beautiful", "IDEA"};

    // for_each(str.begin(),str.end(),func);//普通函数
    // for_each(str.begin(),str.end(),F());//仿函数

    // lambda表达式（匿名函数）
    for_each(str.begin(), str.end(),
             [](string &s) -> void
             { cout << "Hello," << s << " World!" << endl; });
    // 如果省略返回值类型，编译器会自动推导

    // 捕获列表
    // lambda函数可以捕获父作用域的非静态局部变量，可以用值(无法修改值)或引用的方式捕获
    int i = 42, j = 23;

    // auto fLambda = [i, &j]() -> void
    // { cout << i << " " << ++j << endl; };//显式捕获

    // auto fLambda = [=]() -> void
    // { cout << i << " " << j << endl; }; //[=]自动进行值捕获

    auto fLambda = [&]() -> void
    { cout << ++i << " " << ++j << endl; };//[&]自动进行引用捕获

    fLambda();
    //PS:以上三种方式可以混用

    int a=123;
    auto flambda_C = [a]()mutable->void{cout<<++a<<endl;} ;
    //要在内部改变a的值，必须用mutable关键字
    cout<<a<<endl;

    return 0;
}