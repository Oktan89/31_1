#include <iostream>
#include <string>

class Toy
{
    std::string _ltoy;
public:
    Toy(const std::string& toy = "no name"):_ltoy(toy)
    {
        std::cout << "constructor default\n";
    }
    ~Toy()
    {
        std::cout << "destructor\n";
    }
    Toy(const Toy& toy) : _ltoy(toy._ltoy)
    {
        std::cout << "Copy constructor worked\n";
    }

    Toy& operator= (const Toy& toy)
    {
        std::cout << "Operator =\n";
        if(this == &toy)
            return *this;

        _ltoy = toy._ltoy;
        
        return *this;
    }
  
    friend std::ostream& operator<< (std::ostream& out, Toy& toy)
    {
        out << toy._ltoy;
        return out;
    }

};

class shared_ptr_toy
{
    std::size_t count{0};
    Toy* _toy;
public:
    shared_ptr_toy(Toy* toy = nullptr) : _toy(toy)
    {
        if(_toy != nullptr)
            ++count;
        std::cout << "Constructor chared_ptr_toy\n";
    }
    
    shared_ptr_toy(const shared_ptr_toy& ptr)
    {
        _toy = ptr._toy;
        
    }

    ~shared_ptr_toy()
    {
        std::cout << "Destructor chared_ptr_toy\n";
        if(count <= 1)
        {
            --count;
            delete _toy;
            std::cout << "destroy\n";
        }
        else
        {
            std::cout << "not destroy\n";
        }
            
    }

};

int main()
{
  Toy* t = new Toy;
  shared_ptr_toy ptr(t);
  {
      shared_ptr_toy ptr2(ptr);
  }
  std::cout<<"e"<<std::endl;
  //  delete t;
}