#include <iostream>

///////////////////////////////////////////
template<int N>
const int factorial = N * factorial<N-1>;

template<>
const int factorial<0> = 1;

///////////////////////////////////////////
template<int E, int N=1>
const int pow = E * pow<E,N-1>;

template<int E>
const int pow<E,0> = 1;

///////////////////////////////////////////
template<int N, int M=N-1>
const bool isPrime = N % M && isPrime<N,M-1>;

template<int N>
const bool isPrime<N,1> = N != 1;

template<int N>
const bool isPrime<N,0> = false;

///////////////////////////////////////////
template<int N>
const bool isPoweorOf2 = (N & N-1) == 0 && N != 0;

///////////////////////////////////////////
template<int N>
const int fibonacci = fibonacci<N-1> + fibonacci<N-2>;

template<>
const int fibonacci<1> = 1;

template<>
const int fibonacci<2> = 1;

///////////////////////////////////////////






int main(){

    std::cout<< factorial<7> <<'\n';
    std::cout<< pow<2,7> <<'\n';
    std::cout<< isPrime<35> <<'\n';
    std::cout<< isPoweorOf2<32> <<'\n';
    std::cout<< fibonacci<9> <<'\n';
    
    return 0;

}


