#include "GlassOfWaterLib.h"

#include "cppmodel/CModel.h"

float filledVolume05 = 0.0f;
float filledVolume10 = 0.0f;
float filledVolume20 = 0.0f;

void Reset(CModelSimulation_ts *ctx)
{
    filledVolume05 = 0.0f;
    filledVolume10 = 0.0f;
    filledVolume20 = 0.0f;
}

void RunCyclic(CModelSimulation_ts *ctx, unsigned long cycleTime)
{
    if (cycleTime == 0)
    {
        Reset(ctx);
    }

    float dt = ctx->stepTime_ms / 1000.0f; // Convert milliseconds to seconds

    float glassesCapacity = CppModel_getParameterF32(ctx, "glassesCapacity [ml]", 250.0f) / 1000.0f; // Default capacity is 250 ml

    float waterFlow05 = CppModel_getInputF32(ctx, "waterFlow05 [l/s]", 5.0f / 60.0f);  // 5 liters per minute converted to liters per second
    float waterFlow10 = CppModel_getInputF32(ctx, "waterFlow10 [l/s]", 10.0f / 60.0f); // 10 liters per minute converted to liters per second
    float waterFlow20 = CppModel_getInputF32(ctx, "waterFlow20 [l/s]", 20.0f / 60.0f); // 20 liters per minute converted to liters per second

    filledVolume05 = glass(dt, glassesCapacity, filledVolume05, waterFlow05);
    filledVolume10 = glass(dt, glassesCapacity, filledVolume10, waterFlow10);
    filledVolume20 = glass(dt, glassesCapacity, filledVolume20, waterFlow20);

    CppModel_setOutputF32(ctx, "currentVolume05 [l]", filledVolume05);
    CppModel_setOutputF32(ctx, "currentVolume10 [l]", filledVolume10);
    CppModel_setOutputF32(ctx, "currentVolume20 [l]", filledVolume20);
}

int main()
{
    // Create a simulation that runs for 4000 milliseconds with a step time of 10 milliseconds
    CModelSimulation_ts *sim = CppModel_create("Glasses Filling", 4000, 10);

    // Assign the simulation step function to RunCyclic, which will be called at each simulation step
    CppModel_setRunStepFunction(sim, RunCyclic);

    CppModel_Simulate(sim);

    int result = CppModel_getSimulationResult(sim);

    return result;
}
