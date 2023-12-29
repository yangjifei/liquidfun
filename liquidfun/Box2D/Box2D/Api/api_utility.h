#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>
#include "../Unity/IUnityInterface.h"
#define IntPtr void *

extern "C"
{
    // ReleaseFloatArray
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ReleaseFloatArray(float *floatArray)
    {
        delete[] floatArray;
        return 0; // Return success
    }

    // ReleaseIntArray
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ReleaseIntArray(int *intArray)
    {
        delete[] intArray;
        return 0; // Return success
    }

    // ReleaseShape
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ReleaseShape(b2Shape *shape)
    {
        delete shape;
        return 0; // Return success
    }
}