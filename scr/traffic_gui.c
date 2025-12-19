#include "traffic_simulator.h"

/* ================== WINDOW / GEOMETRY ================== */

#define W 800
#define H 800

#define ROAD_W   120
#define LANE_W   40

#define CAR_L 14
#define CAR_W  8

SDL_Window   *win;
SDL_Renderer *ren;

/* ================== ROAD + LANES ================== */

static void draw_roads_and_lanes(void)
{
    int cx = W / 2;
    int cy = H / 2;

    /* road background */
    SDL_SetRenderDrawColor(ren, 70, 70, 70, 255);

    SDL_Rect north = { cx - ROAD_W/2, 0, ROAD_W, cy };
    SDL_Rect south = { cx - ROAD_W/2, cy, ROAD_W, cy };
    SDL_Rect west  = { 0, cy - ROAD_W/2, cx, ROAD_W };
    SDL_Rect east  = { cx, cy - ROAD_W/2, cx, ROAD_W };

    SDL_RenderFillRect(ren, &north);
    SDL_RenderFillRect(ren, &south);
    SDL_RenderFillRect(ren, &west);
    SDL_RenderFillRect(ren, &east);

    /* intersection box */
    SDL_Rect center = {
        cx - ROAD_W/2,
        cy - ROAD_W/2,
        ROAD_W,
        ROAD_W
    };
    SDL_RenderFillRect(ren, &center);

    /* lane markings */
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

    for (int i = -1; i <= 1; i++) {
        SDL_RenderDrawLine(ren, cx + i*LANE_W, 0, cx + i*LANE_W, H);
        SDL_RenderDrawLine(ren, 0, cy + i*LANE_W, W, cy + i*LANE_W);
    }
}

/* ================== TRAFFIC LIGHTS ================== */

static void draw_light(int x, int y, int green)
{
    SDL_Rect box = { x-12, y-12, 24, 24 };

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderFillRect(ren, &box);

    if (green)
        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

    SDL_Rect lamp = { x-7, y-7, 14, 14 };
    SDL_RenderFillRect(ren, &lamp);
}

static void draw_traffic_lights(void)
{
    int cx = W/2;
    int cy = H/2;

    draw_light(cx,               cy - ROAD_W/2 - 25, junction.green_straight[NORTH]);
    draw_light(cx + ROAD_W/2+25, cy,                junction.green_straight[EAST]);
    draw_light(cx,               cy + ROAD_W/2+25, junction.green_straight[SOUTH]);
    draw_light(cx - ROAD_W/2-25, cy,                junction.green_straight[WEST]);
}

/* ================== VEHICLES ================== */

static void draw_vehicle(const Vehicle *v)
{
    int cx = W/2;
    int cy = H/2;

    int lane_offset[3] = {
        -LANE_W + 10,
         0,
         LANE_W - 10
    };

    SDL_Rect r;

    switch (v->dir) {
        case NORTH:
            r = (SDL_Rect){
                cx + lane_offset[v->lane] - CAR_W/2,
                cy - (int)v->pos,
                CAR_W, CAR_L
            };
            break;

        case SOUTH:
            r = (SDL_Rect){
                cx - lane_offset[v->lane] - CAR_W/2,
                cy + (int)v->pos,
                CAR_W, CAR_L
            };
            break;

        case EAST:
            r = (SDL_Rect){
                cx + (int)v->pos,
                cy + lane_offset[v->lane] - CAR_W/2,
                CAR_L, CAR_W
            };
            break;

        case WEST:
            r = (SDL_Rect){
                cx - (int)v->pos,
                cy - lane_offset[v->lane] - CAR_W/2,
                CAR_L, CAR_W
            };
            break;
    }

    SDL_SetRenderDrawColor(ren, 0, 220, 0, 255);
    SDL_RenderFillRect(ren, &r);
}

/* ================== MAIN RENDER ================== */

void render(void)
{
    SDL_SetRenderDrawColor(ren, 25, 25, 25, 255);
    SDL_RenderClear(ren);

    draw_roads_and_lanes();
    draw_traffic_lights();

    for (int d = 0; d < 4; d++)
        for (int l = 0; l < 3; l++)
            for (int i = 0; i < junction.road[d].lanes[l].count; i++)
                draw_vehicle(&junction.road[d].lanes[l].v[i]);

    SDL_RenderPresent(ren);
}

/* ================== SDL INIT / CLEANUP ================== */

int init_graphics(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow(
        "Engineered 4-Way Traffic Simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        W, H,
        0
    );
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    return 0;
}

void cleanup_graphics(void)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
