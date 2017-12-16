#include <fstream>
#include "threadThs.h"
#include <thread>
#include "d_exc.h"

bool finished = false;
std::mutex mx;
std::condition_variable cv;
std::queue< uint64_t > q_of_num;;
uint64_t inp;
std::string str;

void threadThs::producer() {
    std::ifstream fin( file_name );
    while (!fin.eof()){
        {
            std::getline( fin, str );
            if ( str != "" ) {
                std::istringstream stream ( str );
                stream >> inp;
            }
            std::lock_guard<std::mutex> lk( mx );
            q_of_num.push( inp );
        }
        cv.notify_one();
    }
    {
        std::lock_guard< std::mutex > lk( mx );
        finished = true;
    }
    cv.notify_one();
}

void threadThs::consumer() {
    std::ofstream fout( file_name_o, std::ofstream::app );
    uint64_t inp;
    std::string ans_str;
    while( true ) {
        std::unique_lock< std::mutex > lk( mx );
        cv.wait( lk, [] { return finished || !q_of_num.empty(); } );
        lk.unlock();
        while( !q_of_num.empty() ) {
            lk.lock();
            inp = q_of_num.front();
            q_of_num.pop();
            lk.unlock();
            DIS -> dism( inp );
            ans_str = DIS -> generate_str();
            fout << ans_str << std::endl;
        }
        if( finished ) {
            fout.close();
            isDone = true;
            break;
        }
    }
}

void threadThs::run() {
    isExit = false;
    isDone = false;
    std::thread t1( &threadThs::producer, this );
    std::thread t2( &threadThs::consumer, this );
    std::string cons_in;
    while ( !isExit ) {
        std::cin >> cons_in;
        if ( cons_in == "exit" ) {
            isExit = true;
        }
        if ( isExit || isDone ) {
            t1.join();
            t2.join();
            isExit = true;
        }
    }
}
