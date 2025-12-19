#include "traffic_simulator.h"
#include <time.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
    srand(time(NULL));
    init_sim();
    init_graphics();

    Uint32 last = SDL_GetTicks();
    int running=1;

    while (running) {
        Uint32 now = SDL_GetTicks();
        double dt = (now-last)/1000.0;
        last = now;

        generate_vehicle();
        update_signals();
        update_vehicles(dt);
        render();

        SDL_Event e;
        while (SDL_PollEvent(&e))
            if (e.type==SDL_QUIT) running=0;

        SDL_Delay(16);
    }

    cleanup_graphics();
    return 0;
}
