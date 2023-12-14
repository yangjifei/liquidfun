#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Testbed/Tests/RayCast.h"
#include <vector>
#define IntPtr void *

extern "C"
{
    // ReleaseFloatArray
    int ReleaseFloatArray(float *floatArray)
    {
        delete[] floatArray;
        return 0; // Return success
    }

    // ReleaseIntArray
    int ReleaseIntArray(int *intArray)
    {
        delete[] intArray;
        return 0; // Return success
    }

    // ReleaseShape
    int ReleaseShape(b2Shape *shape)
    {
        delete shape;
        return 0; // Return success
    }
}