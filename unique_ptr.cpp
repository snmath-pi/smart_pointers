#include <iostream>

template <typename T> 
class uniqueptr {
private:
    T* res;
public:
    uniqueptr(T* a = nullptr): res(a) {
        std::cout << "ctor is called\n";
    }
    uniqueptr(const uniqueptr<T>& ptr) = delete;
    uniqueptr &operator= (const uniqueptr<T>& ptr) = delete;

    uniqueptr(uniqueptr<T>&& ptr) {
        res = ptr.res;
        ptr.res = nullptr;
    }
    uniqueptr& operator= (uniqueptr<T>&& ptr) {
        if(this != &ptr) {
            if(res) {
                delete res;
            }
            res = ptr.res;
            ptr.res = nullptr;
        }
        return *this;
    }
    T* operator->() {
        return res;
    }
    T& operator*() {
        return *res;
    }
    T* get() {
        return res;
    }
    void reset(T* newptr) {
        if(res) {
            delete res;
        }
        res = newptr;
    }
    ~uniqueptr() {
        if(res) {
            delete res;
        }
    }

};
int main() {
    uniqueptr <int> ptr1(new int(10));
    uniqueptr <int> ptr2 = std::move(ptr1);
    std::cout << *ptr2.get() << std::endl;
    uniqueptr <int> ptr3 = std::move(ptr2);
    std::cout << *ptr3.get() << std::endl;

}
