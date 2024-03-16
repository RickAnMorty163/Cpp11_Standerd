#include <iostream>
#include <assert.h> //cpp断言
using namespace std;

auto swapData(int *ptr1, int *ptr2)
{
    assert(ptr1 && ptr2); // 断言检查函数形参是否合法
    swap(*ptr1, *ptr2);
    return;
}
signed main()
{
    int a = 0, b = 1;
    // swapData(nullptr,&b);//assert断言失败，程序终止，但不是抛出异常
    // swapData(&a, nullptr);
    swapData(&a, &b);
    cout << a << " " << b << endl;

    // cpp11新增静态断言(不需要包含头文件) static_assert 用于在编译时检查源码
    const int c = 1;
    static_assert(c, "wrong value"); // static_assert第一个参数仅接受常量
    return 0;
}