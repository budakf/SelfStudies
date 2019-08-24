#ifndef REFERENCECOUNTER_H
#define REFERENCECOUNTER_H

#include <iostream>


class ReferenceCounter{
    public:
        ReferenceCounter(unsigned int initValue = 0);
        ReferenceCounter(const ReferenceCounter &) ;
        //ReferenceCounter & operator=(const ReferenceCounter &);
        ~ReferenceCounter(){};

        void operator++();
        ReferenceCounter operator++(int);
        void operator--();
        ReferenceCounter operator--(int);

        unsigned int get() const;
        void set(unsigned int);
        void reset() {this->mcounter = 0;}

        friend std::ostream & operator<<(std::ostream & os , ReferenceCounter & counter){
            os<<counter.get();
            return os;
        }

    private:
        unsigned int mcounter;

};

#endif // REFERENCECOUNTER_H
