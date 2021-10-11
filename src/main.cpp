#include <iostream>
#include <mutex>
#include <string>

class Toy
{
    std::string _ltoy;

public:
    Toy(const std::string &toy) : _ltoy(toy){std::cout <<"create toy"<<std::endl;}

    Toy() : Toy("no name") {}    

};

class shared_ptr_toy
{
    Toy* _toy = nullptr;
    int* _count = nullptr; //указатель на счетчик указателей
    std::mutex m_ptr;
    void add_count()
    {
        std::lock_guard<std::mutex> lg(m_ptr);
        if(_count != nullptr)
            *_count += 1;
    }
    void subtract_count()
    {
        std::lock_guard<std::mutex> lg(m_ptr);
        if(_count != nullptr)
            *_count -= 1;
    }
public:
    int use_count()
    {
        std::lock_guard<std::mutex> lg(m_ptr);
        return *_count;
    }
    shared_ptr_toy(const std::string& name)
    {
        _toy = new Toy(name);
        _count = new int(1); //инициализируем счетчик 1 объектом
    }
    shared_ptr_toy() : shared_ptr_toy("no ptr name") {}

    shared_ptr_toy(const shared_ptr_toy& oth)
    {
        _toy = new Toy(*oth._toy);
        _count = oth._count; //делимся указателем на счетчик
        add_count(); //увеличиваем общий счетчик
    }

    shared_ptr_toy& operator= (const shared_ptr_toy& oth)
    {
        if(this == &oth)
            return *this;
        
        if(_toy != nullptr)
        {
            delete _toy;
            delete _count;
        }
            
        _toy = new Toy(*oth._toy);
        _count = oth._count;
        add_count();
        return *this;
    }

    ~shared_ptr_toy()
    {
        std::cout <<"destruct copy toy"<<std::endl;
      
        subtract_count();//уменьшаем счетчик при выходи из области видимости одного из объектов
        if(*_count == 0) //если больше нет владельцев удаляем 
        {
            delete _toy;
            delete _count;
            std::cout <<"delete toy"<<std::endl;
        }

    }
};

shared_ptr_toy make_shared_toy(const std::string& name)
{
    return shared_ptr_toy(name);
}

int main()
{
    
    shared_ptr_toy ptr = make_shared_toy("test");
    std::cout << "Count: "<< ptr.use_count() << std::endl;
    {
        
        shared_ptr_toy ptr2(ptr);
        std::cout << "Count: "<< ptr.use_count() << std::endl;
        shared_ptr_toy ptr3 = ptr;
        std::cout << "Count: "<< ptr.use_count() << std::endl;
       
    }
    std::cout << "Count: "<< ptr.use_count() << std::endl;
}