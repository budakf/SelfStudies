#include "referencecounter.h"

ReferenceCounter::ReferenceCounter(unsigned int initValue){
    this->mcounter = initValue;
}


ReferenceCounter::ReferenceCounter(const ReferenceCounter & ref){
    this->mcounter = ref.mcounter;
}


unsigned int ReferenceCounter::get() const{
    return this->mcounter;
}


void ReferenceCounter::set(unsigned int counter){
    this->mcounter = counter;
}


void ReferenceCounter::operator++(){ // Prefix ++Object
    ++(this->mcounter);
}


ReferenceCounter  ReferenceCounter::operator++(int){ // Postfix Object++
    ReferenceCounter temp = *this;
    (this->mcounter)++;
    return temp;
}


void ReferenceCounter::operator--(){ // Prefix --Object
    --(this->mcounter);
}


ReferenceCounter  ReferenceCounter::operator--(int){ // Postfix Object--
    ReferenceCounter temp = *this;
    (this->mcounter)--;
    return temp;
}





