#include "print_ip.h"
#include <iostream>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

/*!
    This is example code uses printIp funtions.
*/

int main(){
    print_ip( char{-1} ); // 255
    cout << endl;
    print_ip( short{0} ); // 0.0
    cout << endl;
    print_ip( int{2130706433} ); // 127.0.0.1
    cout << endl;
    print_ip( long{8875824491850138409} ); //123.45.67.89.101.112.131.41
    cout << endl;
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    cout << endl;
    print_ip( std::vector<int>{100, 200, 300, 400} ); //100.200.300.400
    cout << endl;
    print_ip( std::list<short>{400, 300, 200, 100} ); //400.300.200.100
    cout << endl;
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    cout << endl;

    //print_ip(std::make_tuple(123, "123")); //Compile error!
}