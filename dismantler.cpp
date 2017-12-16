#include "dismantler.h"

void dismatler::dism( uint64_t inp ) {
    data.clear();
    uint64_t i = 2;
    uint64_t count_ = 0;
    while ( i <= inp ) {
        if ( inp % i == 0 ) {
            count_++;
            inp /= i;
        } else {
            data [ i ] = count_;
            i++;
            count_ = 0;
        }
    }
    data [ i ] = count_;
}

std::string dismatler::generate_str() {
    str_print.clear();
    for ( const auto & it : data ) {
        if ( it.second != 0 ) {
            str_print += " * ";
            str_print += patch::to_string( it.first );
            if ( it.second != 1) {
                str_print += "^";
                str_print += patch::to_string( it.second );
            }
        }
    }
    str_print.erase(0,3);
    return str_print;
}

