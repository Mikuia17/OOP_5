#include <fstream>
#include "threadThs.h"
#include <thread>

bool finished = false;
std::mutex mx;
std::condition_variable cv;
std::queue< uint64_t > tasks;;
uint64_t inp;
std::string str;

void threadThs::producer() {
    std::ifstream fin( file_name );
    while (!fin.eof() && !isExit){
        {
            std::getline( fin, str );
            if ( str != "" ) {
                std::istringstream stream ( str );
                stream >> inp;
            }
            std::lock_guard<std::mutex> lk( mx );
            tasks.push( inp );
            std::cout << " + " << std::endl;
            while ( isPause ) {
                std::this_thread::sleep_for ( std::chrono::seconds(1) );
            }
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
        cv.wait( lk, [] { return finished || !tasks.empty(); } );
        lk.unlock();
        while( !tasks.empty() ) {
            lk.lock();
            inp = tasks.front();
            tasks.pop();
            lk.unlock();
            DIS -> dism( inp );
            ans_str = DIS -> generate_str();
            fout << ans_str << std::endl;
            std::cout << " - " << std::endl;
            if ( isExit ) {
                while ( !tasks.empty() ) {
                    tasks.pop();
                }
            }
            while ( isPause ) {
                std::this_thread::sleep_for ( std::chrono::seconds(1) );
            }
        }
        if( finished ) {
            isDone = true;
            break;
        }
    }
}

void threadThs::run() {
    isExit = false;
    isDone = false;
    isPause = false;
    std::thread t1( &threadThs::producer, this );
    std::thread t2( &threadThs::consumer, this );
    std::string cons_in;
    while ( !isExit ) {
        std::cin >> cons_in;
        if ( cons_in == "exit" || isDone ) {
            isExit = true;
        }
        if ( cons_in == "pause" ) {
            isPause = true;
        }
        if ( cons_in == "go" ) {
            isPause = false;
        }
    }
    t1.join();
    t2.join();
}
