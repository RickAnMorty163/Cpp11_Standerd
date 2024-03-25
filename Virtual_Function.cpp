#include <iostream>
#include <functional>
#include <vector>
using namespace std;

// std::function std::bind 取代虚函数，提高效率

class AA
{
public:
    // virtual void show() { cout << " virtual " << endl; }
    function<void()> m_callback;
    template <typename Fn, typename... Args>
    void call_back(Fn &&fn, Args &&...args)
    {
        m_callback = std::bind(forward<Fn>(fn), forward<Args>(args)...);
    }
    void show() { m_callback(); }
};

class BB : public AA
{
public:
    void show() { cout << " non virtual BB " << endl; }
};

class CC : public AA
{
public:
    void show() { cout << " non virtual CC " << endl; }
};

signed
main()
{
    AA *ptr = nullptr;
    ptr = new AA;
    ptr->call_back(&AA::show, static_cast<AA *>(ptr));
}