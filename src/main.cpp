#include <iostream>
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
    Toy* _toy;
    int* _count; //указатель на счетчик указателей

public:

    shared_ptr_toy(const std::string& name)
    {
        _toy = new Toy(name);
        _count = new int(1); //инициализируем счетчик 1 объектом
    }
    shared_ptr_toy() : shared_ptr_toy("no ptr name") {}

    shared_ptr_toy(const shared_ptr_toy& oth)
    {
        _toy = new Toy(*oth._toy);
        ++*oth._count;  //увеличиваем общий счетчик
        _count = oth._count; //делимся указателем на счетчик
    }

    shared_ptr_toy& operator= (const shared_ptr_toy& oth)
    {
        if(this == &oth)
            return *this;
        
        if(_toy != nullptr)
            delete _toy;
        _toy = new Toy(*oth._toy);

        return *this;
    }

    ~shared_ptr_toy()
    {
        std::cout <<"destruct copy toy"<<std::endl;
        --*_count; //уменьшаем счетчик при выходи из области видимости одного из объектов
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
    {
        shared_ptr_toy ptr2(ptr);
        std::cout << "test2" << std::endl;
    }
    std::cout << "test" << std::endl;
}