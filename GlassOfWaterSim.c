#include "GlassOfWaterLib.h"

#include "cppmodel/CModel.h"

float tapOpening = 0.0f;
float actualVolume = 0.0f;

void RunCyclic(CModelSimulation_ts *ctx, unsigned long cycleTime)
{
    float dt = ctx->stepTime_ms / 1000.0f; // Convert milliseconds to seconds

    float plumbingFlow = CppModel_getParameterF32(ctx, "plumbingFlow [l/min]", 15.0f) / 60.0f;   // Default plumbing flow is 15 liters per minute converted to liters per second
    float glassCapacity = CppModel_getParameterF32(ctx, "glassCapacity [ml]", 250.0f) / 1000.0f; // Default glass capacity is 250 ml converted to liters
    float openingSlope = CppModel_getParameterF32(ctx, "openingSlope [%/s]", 100.0f) * 0.01f;    // Default opening slope is 1% per second converted to a fraction
    float closingSlope = CppModel_getParameterF32(ctx, "closingSlope [%/s]", 400.0f) * 0.01f;    // Default closing slope is 4% per second converted to a fraction

    float desiredLevel = CppModel_getInputF32(ctx, "desiredLevel [0.01%]", 0.8f); // Default desired level is 80%

    float actualLevel = sensor(glassCapacity, actualVolume);
    float error = desiredLevel - actualLevel;
    tapOpening = control(dt, openingSlope, closingSlope, tapOpening, error);
    float actualFlow = actuator(plumbingFlow, tapOpening);
    actualVolume = glass(dt, glassCapacity, actualVolume, actualFlow);

    CppModel_setOutputF32(ctx, "error [0.01%]", error);
    CppModel_setOutputF32(ctx, "tapOpening [0.01%]", tapOpening);
    CppModel_setOutputF32(ctx, "actualFlow [l/s]", actualFlow);
    CppModel_setOutputF32(ctx, "actualVolume [l]", actualVolume);
    CppModel_setOutputF32(ctx, "actualLevel [0.01%]", actualLevel);
}

int main()
{
    CModelSimulation_ts *sim = CppModel_create("Glass of Water", 2000, 10);

    CppModel_setRunStepFunction(sim, RunCyclic);

    CppModel_Simulate(sim);

    int result = CppModel_getSimulationResult(sim);

    return result;
}
