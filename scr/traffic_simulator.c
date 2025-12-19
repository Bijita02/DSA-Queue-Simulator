#include "traffic_simulator.h"
#include <string.h>

Junction junction;

void init_sim() {
    memset(&junction, 0, sizeof(junction));
}

int can_move(Direction d, LaneType l) {
    if (l == RIGHT) return 1;
    if (l == LEFT) return junction.green_left[d];
    return junction.green_straight[d];
}

void update_signals() {
    static int phase = 0;
    static double timer = 0;

    timer += 0.016;
    if (timer > 4.0) {
        timer = 0;
        phase = (phase + 1) % 2;
    }

    for (int d=0; d<4; d++) {
        junction.green_straight[d] = 0;
        junction.green_left[d] = 0;
    }

    if (phase == 0) {
        junction.green_straight[NORTH] = junction.green_straight[SOUTH] = 1;
        junction.green_left[NORTH] = junction.green_left[SOUTH] = 1;
    } else {
        junction.green_straight[EAST] = junction.green_straight[WEST] = 1;
        junction.green_left[EAST] = junction.green_left[WEST] = 1;
    }
}

void update_vehicles(double dt) {
    for (int d=0; d<4; d++) {
        for (int l=0; l<3; l++) {
            Lane *ln = &junction.road[d].lanes[l];

            for (int i=0; i<ln->count; i++) {
                Vehicle *v = &ln->v[i];
                if (v->state == EXITED) continue;

                if (v->pos <= STOP_LINE && !can_move(d,l)) {
                    v->state = WAITING;
                    continue;
                }

                v->state = ACTIVE;
                v->pos -= VEHICLE_SPEED * dt;

                if (v->pos < -40)
                    v->state = EXITED;
            }

            int n=0;
            for (int i=0;i<ln->count;i++)
                if (ln->v[i].state != EXITED)
                    ln->v[n++] = ln->v[i];
            ln->count = n;
        }
    }
}
