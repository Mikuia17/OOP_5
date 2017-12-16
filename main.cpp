#include "dismantler.h"
#include "threadThs.h"

int main() {
    std::string file_name, file_name_o;
    //std::cin >> file_name >> file_name_o;
    file_name = "d://in.txt";
    file_name_o = "d://out.txt";
    threadThs tr( file_name, file_name_o );
    tr.run();
}
