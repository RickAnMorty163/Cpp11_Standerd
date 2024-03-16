#include<iostream>

using namespace std;

//cp11可参数模板，Cpp98中不支持
//处理任意数量的参数

//展开参数包的递归函数模板
template<typename T>
void show(T a){
    cout<<"Hello , "<<a<<endl;
}
void Print(){//剩余参数为0，递归终止
    cout<<"递归终止"<<endl;
}

template<typename T ,typename ...Args>//Args可变参数
void Print(T arg,Args... args){
    cout<<"参数："<<arg<<endl;

    show(arg);

    cout<<"剩余参数数量"<<sizeof...(args)<<endl;
    Print(args...);

}

template<typename ...Args>
void function( const string &str, Args... args){//第一个参数为普通类型参数，剩余参数为可变参数
    cout<<str<<endl;
    Print(args...);
    cout<<"end"<<endl;
}

signed main(){
    Print(1,1,5,0,1,2,2,0,2,4,0,2,9);
    function("Welcome to Cpp11 ! \n",2,3,4,5,6,7,8,9,10);
    
    return 0;
}