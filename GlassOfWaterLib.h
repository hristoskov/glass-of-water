#pragma once

float glass(float dt, float capacity, float filledVolume, float waterFlow);
float control(float dt, float openingSlope, float closingSlope, float actualOpening, float error);

float sensor(float capacity, float filledVolume);
float actuator(float maxFlow, float valveOpening);
