#include "shared_ptr_toy.h"

void shared_ptr_toy::add_count()
{
    std::lock_guard<std::mutex> lg(m_ptr);
    if (_count != nullptr)
        *_count += 1;
}

void shared_ptr_toy::subtract_count()
{
    std::lock_guard<std::mutex> lg(m_ptr);
    if (_count != nullptr)
        *_count -= 1;
}

int shared_ptr_toy::use_count()
{
    std::lock_guard<std::mutex> lg(m_ptr);
    return *_count;
}

shared_ptr_toy::shared_ptr_toy(Toy* toy)
{
    _toy = toy;
    _count = (nullptr == toy)? new int(0) : new int(1); //инициализируем счетчик
}

shared_ptr_toy::shared_ptr_toy(const shared_ptr_toy &oth)
{
    _toy = oth._toy;
    _count = oth._count; //делимся указателем на счетчик
    add_count();         //увеличиваем общий счетчик
}

shared_ptr_toy &shared_ptr_toy::operator=(const shared_ptr_toy &oth)
{
    if (this == &oth)
        return *this;

    subtract_count(); //уменьшаем счетчик this
    if (use_count() == 0) //если больше нет владельцев удаляем так как этот объект последний и мы его перезаписываем деструктор вызван не будет и произойдет утечка
    {
        std::cout << "delete toy " <<_toy->get()<< std::endl;
        delete _toy;
        _toy = nullptr;
        delete _count;
        _count = nullptr;
    }
    _toy = oth._toy;
    _count = oth._count;
    add_count(); //увеличиваем ссылку счетчик копируемого объекта oth
    return *this;
}

shared_ptr_toy::~shared_ptr_toy()
{
    std::cout << "destruct ptr copy toy "<< _toy->get() <<" : "<<use_count() << std::endl;

    subtract_count(); //уменьшаем счетчик при выходи из области видимости одного из объектов
    if (*_count == 0) //если больше нет владельцев удаляем
    {
        std::cout << "delete toy " <<_toy->get()<< std::endl;
        delete _toy;
        _toy = nullptr;
        delete _count;
        _count = nullptr;
    }
}

shared_ptr_toy make_shared_toy(const std::string& name)
{
    return shared_ptr_toy(new Toy(name));
}

shared_ptr_toy make_shared_toy(const Toy& toy)
{
    return shared_ptr_toy(new Toy(toy));
}