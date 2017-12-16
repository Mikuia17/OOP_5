#include "dismantler.h"
#include "d_exc.h"
#include "threadThs.h"

int main() {
    std::string file_name, file_name_o;
    std::cin >> file_name >> file_name_o;
    threadThs tr( file_name, file_name_o );
    tr.run();
}
