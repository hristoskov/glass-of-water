#pragma once

#include <stdint.h>

uint8_t VerifyGlassFilling(unsigned long cycleTime, float actualLevel, float desiredLevel, float tapOpening, float previousLevel);
