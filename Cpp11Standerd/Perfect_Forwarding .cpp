#include<iostream>
#include<assert.h>

using namespace std;

//Cpp11完美转发：保持参数传递过程中左右值属性不变
//完美转发是实现移动语义的基础

//模板中参数T写为 T&& ，既可接受左值又可以接受右值
//std::forward<T>(t) 会将t转换为T&&类型，然后返回T&&类型
void func1(int &a){
    cout<<a<<" is lrefence"<<endl;
}
void func1(int &&a){
    cout<<a<<" is rrefence"<<endl;
}

template<typename T>
void func2(T&& args){ //tips:若使用int&&接受形参，则只能接受右值
    cout<<"Try to forward args "<<endl;
    func1(std::forward<T>(args));
}
signed main(){
    int a=42;
    func1(a);
    func1(move(a));
    
    func2(a);
    func2(move(a));
    return 0;
}
