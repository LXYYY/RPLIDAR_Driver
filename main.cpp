#include <iostream>
#include "librplidar_global.h"
using namespace std;

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

int main(int argc, char *argv[])
{
    lidarInit();

    lidarStart();

    while(1){
        size_t count=360*2;
        rplidar_measurement_node_t nodes[count];

        lidarGetScanData(nodes,count,2000);
        if (ctrl_c_pressed){
            break;
        }
    }

    lidarStop();
    return 0;
}
