#include "traffic_simulator.h"
#include <stdlib.h>

void generate_vehicle() {
    if (rand()%30) return;

    Direction d = rand()%4;
    LaneType l = rand()%3;

    Lane *ln = &junction.road[d].lanes[l];
    if (ln->count >= MAX_VEHICLES) return;

    Vehicle v;
    v.pos = ROAD_LENGTH;
    v.dir = d;
    v.lane = l;
    v.state = ACTIVE;

    ln->v[ln->count++] = v;
}
