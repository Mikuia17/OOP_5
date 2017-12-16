#ifndef DISMANTLER_H_INCLUDED
#define DISMANTLER_H_INCLUDED

#include<map>
#include<iostream>
#include<sstream>

class dismatler {
public:
    explicit dismatler( const std::string &f_in, const std::string &f_ou) {
        file_name = f_in;
        file_name_o = f_ou;
    }
    void dism( uint64_t );
    std::string generate_str();
private:
    std::map< uint64_t, uint64_t > data;
    std::string file_name, file_name_o, str_print;
    uint64_t inp;
};

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#endif // DISMANTLER_H_INCLUDED
