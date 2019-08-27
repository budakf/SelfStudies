#include<iostream>

template <typename T>
class UniquePtr{

    public:

        UniquePtr() : mPtr(nullptr){}

        explicit UniquePtr(T * uPtr){
            mPtr = uPtr;
        }

//        explicit UniquePtr(T & uPtr){
//            mPtr = &uPtr;
//        }

        UniquePtr(const UniquePtr<T> &) = delete;
        UniquePtr<T> & operator=(const UniquePtr<T> &) = delete;

        ~UniquePtr(){
            if(mPtr)
                delete mPtr;
        }

        UniquePtr(UniquePtr<T> && uPtr){
            if(mPtr) delete mPtr; // for avoid memory leak

            mPtr = std::move(uPtr.get());
            uPtr.set2nullptr();
        }

        UniquePtr<T> && operator=(UniquePtr<T> && uPtr){
            if(mPtr) delete mPtr; // for avoid memory leak

            mPtr = std::move(uPtr.get());
            uPtr.set2nullptr();
            return *this;
        }

        friend std::ostream & operator<<(std::ostream & os, UniquePtr<T> & uPtr){
            os << uPtr.get() << "   " << *(uPtr.get()) << std::endl;
            return os;
        }

        T * get(){ return mPtr; }
        void set2nullptr(){ mPtr = nullptr; }
        bool isNullptr(){ return mPtr == nullptr; }

    private:
        T * mPtr;

};
