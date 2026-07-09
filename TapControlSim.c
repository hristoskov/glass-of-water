#include "GlassOfWaterLib.h"

#include "cppmodel/CModel.h"

float tapOpening = 0.0f;

void RunCyclic(CModelSimulation_ts *ctx, unsigned long cycleTime)
{
    if (cycleTime == 0)
    {
        tapOpening = 0.0f;
    }
    float dt = ctx->stepTime_ms / 1000.0f; // Convert milliseconds to seconds

    float defalutError = (cycleTime <= 2000) ? 1.0f : -1.0f;

    float openingSlope = CppModel_getParameterF32(ctx, "openingSlope", 1.0f);
    float closingSlope = CppModel_getParameterF32(ctx, "closingSlope", 2.0f);

    float error = CppModel_getInputF32(ctx, "error", defalutError);

    tapOpening = control(dt, openingSlope, closingSlope, tapOpening, error);

    CppModel_setOutputF32(ctx, "tapOpening", tapOpening);
}

int main()
{
    // Create a simulation that runs for 4000 milliseconds with a step time of 10 milliseconds
    CModelSimulation_ts *sim = CppModel_create("Tap Controller Simulation", 4000, 10);

    // Assign the simulation step function to RunCyclic, which will be called at each simulation step
    CppModel_setRunStepFunction(sim, RunCyclic);

    CppModel_Simulate(sim);

    int result = CppModel_getSimulationResult(sim);

    return result;
}
