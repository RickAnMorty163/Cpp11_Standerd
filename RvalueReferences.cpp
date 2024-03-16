#include <iostream>

using namespace std;

class AA
{   public:
    int ma=42;
    AA(){cout<<"Creat"<<endl;}
    ~AA(){cout<<"Destory"<<endl;}
};
AA getTemp()
{
    return AA(); // 返回匿名对象
}
signed main()
{

    int a = 3; // a为左值，3是字面常量，不能取地址，为右值

    int b = a + 3; // 同理(a+3)是右值

    AA &&aa = getTemp(); // getTemp()返回匿名对象，使用右值引用延长了临时对象的生命周期
    //只要aa不被赋值，aa的生命周期结束，临时对象被销毁

    cout<<aa.ma<<endl;

    int &&_a=3;
    int &&_b=_a+3;

    //右值引用后可以当做是左值使用
    cout<<_a<<" "<<_b<<endl;


    //PS:常量左值引用也可以是右值引用
    const int & pt=42;//42是右值，pt是左值

    cout<<"End"<<endl;
    return 0;
}