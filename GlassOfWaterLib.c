#include "GlassOfWaterLib.h"

float glass(float dt, float capacity, float filledVolume, float waterFlow)
{
    float deltaVolume = waterFlow * dt;
    filledVolume += deltaVolume;
    if (filledVolume > capacity)
    {
        filledVolume = capacity;
    }
    return filledVolume;
}

float control(float dt, float openingSlope, float closingSlope, float actualOpening, float error)
{
    if (error > 0) // we need to open the tap
    {
        actualOpening += openingSlope * dt;
        if (actualOpening > 1.0) // limit to 100%
        {
            actualOpening = 1.0;
        }
    }
    else if (error < 0) // we need to close the tap
    {
        actualOpening -= closingSlope * dt; // error is negative, so this will decrease actualOpening
        if (actualOpening < 0.0)            // limit to 0%
        {
            actualOpening = 0.0;
        }
    }
    return actualOpening;
}

float sensor(float capacity, float filledVolume)
{
    return filledVolume / capacity;
}

float actuator(float maxFlow, float valveOpening)
{
    return maxFlow * valveOpening;
}