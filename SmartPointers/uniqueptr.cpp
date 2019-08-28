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
            if(mPtr)    delete mPtr;
        }

        UniquePtr(UniquePtr<T> && uPtr){
            if(mPtr) delete mPtr; // avoid memory leak
            this->swap(uPtr);
            uPtr.set2nullptr();
        }

        UniquePtr<T> & operator=(UniquePtr<T> && uPtr){
            if(mPtr) delete mPtr; //  avoid memory leak

            this->swap(uPtr);
            uPtr.set2nullptr();
            return *this;
        }

        friend std::ostream & operator<<(std::ostream & os, UniquePtr<T> & uPtr){
            os << uPtr.get() << "   " << *(uPtr.get()) << std::endl;
            return os;
        }


        T * release(){
            T * temp = nullptr;
            std::swap(mPtr, temp);
            return temp;
        }

        T * get(){ return mPtr; }
        void set2nullptr(){ mPtr = nullptr; }
        bool isNullptr(){ return mPtr == nullptr; }

    private:
        T * mPtr;

        void set(T * ptr){
            if(mPtr) delete mPtr;
            mPtr = ptr;
        }

        void swap(UniquePtr<T> & uPtr){
            T * temp = mPtr;
            mPtr = uPtr.get();
            uPtr.set(temp);
        }


};
