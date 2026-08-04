#include "GlassOfWaterVerification.h"

typedef enum
{
    PRE_FILLING,
    FILLING,
    POST_FILLING
} FillingState_t;

static FillingState_t fillingState = PRE_FILLING;
static float previousLevel = 0.0f;

uint8_t PreFillingCheck(unsigned long delta)
{
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

uint8_t VerifyGlassFilling(unsigned long cycleTime, float actualLevel, float desiredLevel, float tapOpening)
{
    uint8_t result = 0;
    switch (fillingState)
    {
    case PRE_FILLING:
        if (tapOpening > 0.0f)
        {
            fillingState = FILLING;
        }
        else
        {
            result = PreFillingCheck(cycleTime);
            break;
        }
    case FILLING:
        if (tapOpening <= 0.0f)
        {
            fillingState = POST_FILLING;
        }
        else
        {
            result = FillingCheck(cycleTime, actualLevel, previousLevel);
            break;
        }
    case POST_FILLING:
        result = PostFillingCheck(cycleTime, actualLevel, desiredLevel);
        break;
    default:
        result = 0;
        break;
    }
    previousLevel = actualLevel;
    return result;
}
