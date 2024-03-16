#include <iostream>
#include <cstring>
using namespace std;

// 移动语义
//使用移动语义可以提高性能，尤其在涉及大型数据结构或动态分配内存的情况下。
//移动语义避免了不必要的数据复制，取而代之的是对资源所有权的转移。这对于容器类（如std::vector）等数据结构的性能优化非常有帮助。
class AA
{
public:
    int *data = nullptr;

    AA() = default; // 启用默认构造函数
    void alloc()
    {
        data = new int;               // 开辟堆区内存
        memset(data, 0, sizeof(int)); // 初始化为0
    }
    // AA(const AA &a)
    // {
    //     cout << "Using Copy Function" << endl;
    //     if (!data)
    //         alloc(); // 如果data为空，调用alloc函数分配内存
    //     memcpy(data,a.data,sizeof(int));//拷贝原对象数据
    // }
   
   //移动构造函数
    AA(AA &&a)//右值引用 对a的资源进行修改操作，不能使用const修饰
    {
        cout<<"Using move constructor Function"<<endl;
        if (data){
            delete data;
        }//若已分配内存，先释放,预留一个指针
        data=a.data;//将资源从源对象中转移过来
        a.data=nullptr;//将源对象指针置空
        
    }
    // AA &operator=(const AA &a)
    // {
    //     cout << "Using = operator overload" << endl;
    //     if (&a == this)
    //         return *this; // 避免自我赋值，返回当前对象
    //     if (!data)
    //         alloc();
    //     memcpy(data, a.data, sizeof(int));//拷贝原对象数据 a.data->data
    //     return *this;
    // }
    
    //移动赋值函数
    AA &operator=( AA &&a)//右值引用
    {
        cout << "Using move = operator overload" << endl;
        if (&a == this)
            return *this; // 避免自我赋值，返回当前对象
        if (data)
            delete data;
        data=a.data;
        a.data=nullptr;
        return *this;
    }
    ~AA()
    {
        if (data)//释放堆区内存
        {
            delete data;
            data = nullptr;
        }
    }
};
signed main(){
    AA a1;
    a1.alloc();
    *a1.data=4;
    cout<<"a1-> data "<<*a1.data<<endl;

    //使用lambda函数构造临时右值对象
    auto f=[](int val)->AA{AA a;a.alloc();*a.data=val;return a;};

    AA a2(move(a1)); //std::move()直接将左值转换为右值
    cout<<"a2-> data "<<*a2.data<<endl;

    AA a3;
    a3=f(42);
    cout<<"a3-> data "<<*a3.data<<endl;

    return 0;
}