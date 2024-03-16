#include <iostream>
#include<string>
using namespace std;

//委托构造&&继承构造

class AA{
    private:
    int ma=0;
    int mb=0;
    string mc="TTC";
    public:
    AA()=default;
    AA(int a,int b):ma(a),mb(b){cout<<"use AA(int,int)"<<endl;}
    AA(int a,int b,string c):AA(a,b){//委托构造AA(a,b),简化代码
        mc=c;
        cout<<"use AA(int,int,string)"<<endl;
    }
    void show_AA(){
        cout<<ma<<" "<<mb<<" "<<mc<<endl;
    }
};
class BB:public AA{
    private:
    int B=0;
    public:
    using AA::AA;//继承构造：使用基类的构造函数
    BB(int a,int b,string s,int c):AA(a,b,s),B(c){}
    void show_AA_BB(){show_AA();cout<<"B:"<<B<<endl;}
};
signed main(){
    AA a(1,2,"T_SQUARE");
    a.show_AA();

    BB b1(4,2);
    b1.show_AA_BB();

    BB b2(4,2,"Universe");
    b2.show_AA_BB();  

    BB b3(4,2,"Universe",42);
    b3.show_AA_BB();
    return 0;
}