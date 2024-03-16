#include<iostream>
#include<chrono>
#include<iomanip>
#include<sstream>//stringstream
using namespace std;

auto Time(int day=0, int hour=0, int minutes=0, int seconds=0){
    //时间转换：C++时间(time_point)->UTC时间(t_time)-> tm结构体 ->iomanip::localtime()格式化输出or写入stringstream   

    //静态成员函数std::chrono::systme_clock::now() 获取C++时间 ->time_point类型
    auto now=chrono::system_clock::now();

    //静态成员函数chorono::system_clock::to_time_t() 获取UTC时间 ->time_t类型
    auto t_now=chrono::system_clock::to_time_t(now);

    t_now+=seconds+60*minutes+3600*hour+86400*day;

    //std::localtime()函数将time_t转换为本地时间->返回结构体
    auto tm_now=std::localtime(&t_now);
    
    //格式化输出tm结构体成员
    return tm_now;
}
signed main(){
    //std::chrono::duration
    chrono::hours t1(1);
    chrono::minutes t2(60);
    chrono::seconds t3(3600);
    chrono::milliseconds t4(3600000);

    //chrono类重载了各种运算符
    cout<<(t1==t2)<<endl;
    cout<<(t1==t3)<<endl;
    cout<<(t1==t4)<<endl;
    
    //chrono::count() 获取chrono对象(时钟周期)的值
    cout<<"t1 "<<t1.count()<<endl;
    cout<<"t2 "<<t2.count()<<endl;
    cout<<"t3 "<<t3.count()<<endl;
    cout<<"t4 "<<t4.count()<<endl;


    //格式化输出tm结构体成员
    cout<<std::put_time(Time(),"%Y-%m-%d %H:%M:%S")<<endl;

    stringstream ss;
    ss<<put_time(Time(0,2,45,60),"%Y-%m-%d %H:%M:%S");//将时间输出到stirngstream对象ss中
    string time_str=ss.str();//将ss对象转换为string对象time_str
    cout<<time_str<<endl;


    //计时器chrono::steady_clock
    auto start=chrono::steady_clock::now();

    cout<<"Time start "<<endl;
    for(int i=0;i<100;i++){
    }
    cout<<"Time end "<<endl;
    auto end=chrono::steady_clock::now();

    auto dt=end-start;
    cout<<"消耗时间"<<(double)dt.count()<<"纳秒"<<(double)dt.count()/1e6<<"毫秒"<<endl;
    
    
    
}