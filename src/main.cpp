#include <iostream>
#include <memory>
#include "shared_ptr_toy.h"



int main()
{
    Toy t("name");
    shared_ptr_toy ptr = make_shared_toy(t);
    shared_ptr_toy ptr4 = make_shared_toy("test");
    std::cout << "Count ptr: "<< ptr.use_count() << " : " << ptr->get() << std::endl;
    {
        
        shared_ptr_toy ptr2(ptr);
        std::cout << "Count ptr: "<< ptr.use_count() << " : " << ptr->get() << std::endl;
        shared_ptr_toy ptr3 = ptr;
        std::cout << "Count ptr: "<< ptr.use_count() << " : " << ptr->get() << std::endl;
        ptr4 = ptr3; // Для проверки освобождения памяти поменять местами ptr3=ptr4
        std::cout << "Count ptr4: "<< ptr4.use_count() << " : " << ptr4->get() << std::endl;
       
    }
    std::cout << "Count ptr: "<< ptr.use_count() << " : " << ptr->get() << std::endl;
    std::cout << "Count ptr4: "<< ptr4.use_count() << " : " << ptr4->get() << std::endl;
}