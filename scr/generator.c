#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "traffic_simulation.h"

/*
    Writes one vehicle's data to a file
*/
void writeVehicleToFile(FILE *file, Vehicle *vehicle)
{
    fprintf(file, "%f %f %d %d %d %d %f %d\n",
            vehicle->x,
            vehicle->y,
            vehicle->direction,
            vehicle->type,
            vehicle->turnDirection,
            vehicle->state,
            vehicle->speed,
            vehicle->canSkipLight);
}

/*
    Generates vehicles and saves them to a file
    (helper function — NOT a program entry point)
*/
void generateVehiclesToFile(void)
{
    srand((unsigned int)time(NULL));

    FILE *file = fopen("vehicles.txt", "w");
    if (!file)
    {
        perror("Failed to open vehicles.txt");
        return;
    }

    // Generate a fixed number of vehicles
    for (int i = 0; i < 50; i++)
    {
        Direction spawnDirection = (Direction)(rand() % 4);
        Vehicle *vehicle = createVehicle(spawnDirection);

        writeVehicleToFile(file, vehicle);
        free(vehicle);
    }

    fclose(file);
}
