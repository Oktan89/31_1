#pragma once
#include <iostream>
#include <mutex>
#include <string>

class Toy
{
    std::string _ltoy;

public:
    Toy(const std::string &toy) : _ltoy(toy){std::cout <<"create toy"<<std::endl;}

    Toy() : Toy("no name") {}
    std::string get()
    {
        return _ltoy;
    }
 
};

class shared_ptr_toy
{
    Toy* _toy = nullptr;
    int* _count = nullptr; //указатель на счетчик
    std::mutex m_ptr;
    void add_count();
    void subtract_count();
public:
    int use_count();
    shared_ptr_toy(Toy* toy);
    shared_ptr_toy() : shared_ptr_toy(nullptr) {}
    shared_ptr_toy(const shared_ptr_toy& oth);
    shared_ptr_toy& operator= (const shared_ptr_toy& oth);
    ~shared_ptr_toy();
};

shared_ptr_toy make_shared_toy(const std::string& name);
shared_ptr_toy make_shared_toy(const Toy& toy);