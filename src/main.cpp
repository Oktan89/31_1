#include <iostream>
#include "shared_ptr_toy.h"



int main()
{
    Toy t("name");
    shared_ptr_toy ptr = make_shared_toy(t);
    std::cout << "Count ptr: "<< ptr.use_count() << std::endl;
    {
        
        shared_ptr_toy ptr2(ptr);
        std::cout << "Count ptr: "<< ptr.use_count() << std::endl;
        shared_ptr_toy ptr3 = ptr;
        std::cout << "Count ptr: "<< ptr.use_count() << std::endl;
       
    }
    std::cout << "Count ptr: "<< ptr.use_count() << std::endl;

    shared_ptr_toy p;
    std::cout<< "Count ptr new: "<<p.use_count()<<std::endl;

}