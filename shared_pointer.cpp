#include <iostream> 

template <typename T>
class sharedptr {
private:
    T* res;
    int* counter;
    void incrementCounter() {
        if(counter) {
            (*counter)++;
        }
    }
    void decrementCounter() {
        if(counter) {
            (*counter)--;
            if((*counter) == 0) {
                if(res) {
                    delete res;
                    delete counter;
                    res = nullptr;
                    counter = nullptr;
                }
            }
        }
    }
public:
    sharedptr(T* a = nullptr): res(a), counter(new int(1)) {
        std::cout << "ctor called\n";
    }
    sharedptr <T> (const sharedptr <T> &ptr) {
        res = ptr.res;
        counter = ptr.counter;
        incrementCounter();
    }
    sharedptr <T>&operator= (const sharedptr <T> &ptr) {
        if(this != &ptr) {
            decrementCounter();
            res = ptr.res;
            counter = ptr.counter;
            incrementCounter();
        }
        return *this;
    }
    sharedptr <T> (sharedptr <T> &&ptr) {
        res = ptr.res;
        counter = ptr.counter;
        ptr.res = nullptr;
        ptr.counter = nullptr;
        // we don't increase the counter because
        // we are assigning res to ptr ka resource
        // so when res leaves apna previous resource so that's -1
        // when res acquire ptr ka resource then it's +1
        // so in total -1 + 1 = 0
        // so we don't need to increment our counter
    }
    sharedptr <T>&operator= (const sharedptr <T> &&ptr) {
        if(this != &ptr) {
            decrementCounter();
            res = ptr.res;
            counter = ptr.counter;
            
        }
        return *this;
    }

    void reset(T* newres) {
        decrementCounter();
        res = newres;
        counter = new int(1);
    }

    int getCount() {
        if(counter)
            return (*counter);
        return -1;
    }
    T* operator->() {
        return res;
    }
    T& operator* () {
        return (*res); 
    }
    T* get() {
        return res;
    }


    ~sharedptr() {
        decrementCounter();
    }
};
int main() {
    sharedptr <int> ptr1;
    sharedptr <int> ptr2(new int(10));
    sharedptr <int> ptr3(ptr2); // copy ctor
    ptr3 = ptr2; // copy assignment operator

    sharedptr <int> ptr4(std::move(ptr1)); // move copy ctor;
    ptr2 = std::move(ptr3); // move copy assignment operator;

    // ptr1.reset();
    ptr1.reset(new int(5));

    std::cout << (*ptr1) << std::endl; // implementing star operator
    // ptr1->func(); // implementing -> operator

    std:: cout << ptr1.get() << std::endl; // raw pointer
    std:: cout << ptr1.getCount() << std::endl; // number of objects connected to same resource
}
