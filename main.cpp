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
        rplidar_response_measurement_node_t nodes[count];

        lidarGetScanData(nodes,&count,2000);
//        cout<<count<<endl;
#define RPLIDAR_RESP_MEASUREMENT_SYNCBIT        (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT  2
#define RPLIDAR_RESP_MEASUREMENT_CHECKBIT       (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT    1
        for (int pos = 0; pos < (int)count ; ++pos) {
            printf("%s theta: %03.2f Dist: %08.2f Q: %d ",
                (nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ?"S ":"  ",
                (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f,
                nodes[pos].distance_q2/4.0f,
                nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
            uint8_t nodesU8[5];
            memcpy(nodesU8,&nodes[pos],5*sizeof(uint8_t));
            cout<<(int)nodes[pos].angle_q6_checkbit<<ends;
            for(int i=0;i<5;i++)
                cout<<(int)nodesU8[i]<<ends;
            cout<<endl;
        }

        if (ctrl_c_pressed){
            break;
        }
    }

    lidarStop();
    return 0;
}
