#include <iostream> 

int main(){
    int *pointer = nullptr;
    int x = 123;

    pointer = &x;
    
    if(pointer == nullptr){
        std::cout << "Address was not assigned\n";
        std::cout << *pointer;
    }else{
        std::cout << "Address was assigned\n";
    }

    return 0;
}
    // Null value = a special value that means something has no value. 
    //              When a pointer is holding to null value, 
    //              that pointer is not pointing at anything(null pointer)

    // nullptr = Keyword represents a null pointer literal 

    // nullptrs are helpful when determining if an address 
    // was successfully assigned to a pointer

    // When using pointers, be careful that you code isn't 
    // dereferencing nullptr or pointing to a free memory 
    // this will cause undefined behaviour