#include "e2e_protector.h"
#include <iostream>



// build + run
// g++ -std=c++11 test_e2e_protector.cpp e2e_protector.cpp dbc.cpp dbc_reader.cpp E2E/src/E2E_P01.c E2E/src/E2E_P05.c Crc/src/Crc_8.c Crc/src/Crc_16.c && ./a.out

/* Main function to test E2EProtector with P01 */
int main(){
    kcan::DBCReader::init();
    vector<uint8_t> data = {0x54, 0x00, 0x00, 0x00, 0x50, 0x02, 0x00, 0x00};
    E2EProtector p(kcan::dbc::CarModInCrashStsSafe);
    for(uint8_t j=0; j<4; j++){
        p.applyProfile(data);
        for(uint8_t i=0; i<data.size(); i++){
            std::cout << hex << (int)data.at(i) << " ";
        }
        std::cout << endl;
    }
    return 0;
}
