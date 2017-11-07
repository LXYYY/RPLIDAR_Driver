#ifndef LIBRPLIDAR_GLOBAL_H
#define LIBRPLIDAR_GLOBAL_H


#if defined(LIBRPLIDAR_LIBRARY)
#  define LIBRPLIDARSHARED_EXPORT __declspec(dllexport)
#else
//#  define LIBRPLIDARSHARED_EXPORT __declspec(dllimport)
#  define LIBRPLIDARSHARED_EXPORT
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _rplidar_measurement_node_t {
    uint8_t    sync_quality;      // syncbit:1;syncbit_inverse:1;quality:6;
    uint16_t   angle_q6_checkbit; // check_bit:1;angle_q6:15;
    uint16_t   distance_q2;
} __attribute__((packed)) rplidar_measurement_node_t;

LIBRPLIDARSHARED_EXPORT int lidarInit(const char* portname="//./com3",unsigned int baudrate=115200);
LIBRPLIDARSHARED_EXPORT int lidarStart(void);
LIBRPLIDARSHARED_EXPORT int lidarGetScanData(rplidar_measurement_node_t * nodes,size_t count, unsigned int timeout = 2000);
LIBRPLIDARSHARED_EXPORT int lidarStop(void);

#endif // LIBRPLIDAR_GLOBAL_H
