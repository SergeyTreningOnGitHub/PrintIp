#include "print_ip.h"
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

/*!
    This is test print ip function
*/

TEST(PrintIp, TestIntegralTypes){
    ostringstream out;    
    print_ip(char(-1), out);
    ASSERT_EQ("255", out.str());

    out.str("");

    print_ip(short(0x5555), out);
    ASSERT_EQ("85.85", out.str());

    out.str("");

    print_ip(0xFFFFFFFF, out);
    ASSERT_EQ("255.255.255.255", out.str());

    out.str("");

    print_ip(uint64_t(0x7F7F7F7F7F7F7F7F), out);
    ASSERT_EQ("127.127.127.127.127.127.127.127", out.str());    
    
}

TEST(PrintIp, TestString){
    ostringstream out;
    print_ip(string("127.0.0.1"), out);
    ASSERT_EQ("127.0.0.1", out.str());
}

TEST(PrintIp, TestVector){
    ostringstream out;
    vector<int> ip = {127, 0, 0, 1};
    print_ip(ip, out);

    ASSERT_EQ("127.0.0.1", out.str());
}

TEST(PrintIp, TestList){
    ostringstream out;
    list<int> ip = {192, 168, 23, 23};
    print_ip(ip, out);

    ASSERT_EQ("192.168.23.23", out.str());
}

TEST(PrintIp, TestTuple){
    ostringstream out;
    auto ip = make_tuple(1, 2, 3, 4, 5);
    
    print_ip(ip, out);

    ASSERT_EQ("1.2.3.4.5", out.str());
}