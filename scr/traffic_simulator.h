#ifndef TRAFFIC_SIMULATOR_H
#define TRAFFIC_SIMULATOR_H

#include <SDL2/SDL.h>

#define MAX_VEHICLES 60
#define ROAD_LENGTH 260
#define STOP_LINE 110
#define VEHICLE_SPEED 60.0

typedef enum { NORTH=0, EAST, SOUTH, WEST } Direction;
typedef enum { LEFT=0, STRAIGHT, RIGHT } LaneType;
typedef enum { ACTIVE=0, WAITING, EXITED } Status;

typedef struct {
    double pos;
    Direction dir;
    LaneType lane;
    Status state;
} Vehicle;

typedef struct {
    Vehicle v[MAX_VEHICLES];
    int count;
} Lane;

typedef struct {
    Lane lanes[3];
} Road;

typedef struct {
    Road road[4];
    int green_straight[4];
    int green_left[4];
} Junction;

extern Junction junction;

/* core */
void init_sim();
void update_signals();
void update_vehicles(double dt);

/* generator */
void generate_vehicle();

/* gui */
int init_graphics();
void render();
void cleanup_graphics();

#endif
