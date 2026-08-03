#include "GlassOfWaterVerification.h"

typedef enum
{
    PRE_FILLING,
    FILLING,
    POST_FILLING
} FillingState_t;

static FillingState_t fillingState = PRE_FILLING;

uint8_t PreFillingCheck(unsigned long delta)
{
    // Before we start filling, the result is always satisfactory, as we haven't started yet.
    return 1;
}

uint8_t FillingCheck(unsigned long delta, float actualLevel, float previousLevel)
{
    return (actualLevel > previousLevel && actualLevel > 0.0f) ? 1 : 0;
}

uint8_t PostFillingCheck(unsigned long delta, float actualLevel, float desiredLevel)
{
    return (actualLevel >= desiredLevel) ? 1 : 0;
}

uint8_t VerifyGlassFilling(unsigned long cycleTime, float actualLevel, float desiredLevel, float actualFlow, float previousLevel)
{
    switch (fillingState)
    {
    case PRE_FILLING:
        if (actualFlow > 0.0f)
        {
            fillingState = FILLING;
        }
        else
            return PreFillingCheck(cycleTime);
    case FILLING:
        if (actualFlow <= 0.0f)
        {
            fillingState = POST_FILLING;
        }
        else
            return FillingCheck(cycleTime, actualLevel, previousLevel);
    case POST_FILLING:
        return PostFillingCheck(cycleTime, actualLevel, desiredLevel);
    default:
        return 0;
    }
}
