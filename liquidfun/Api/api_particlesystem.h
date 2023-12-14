#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>
#define IntPtr void *
extern "C"
{
    // CreateParticleSystem
    b2ParticleSystem *CreateParticleSystem(b2World *world, float radius, float damping, float gravityScale, int number)
    {
        b2ParticleSystemDef particleSystemDef;
        particleSystemDef.radius = radius;
        particleSystemDef.dampingStrength = damping;
        particleSystemDef.gravityScale = gravityScale;
        particleSystemDef.maxCount = number;

        return world->CreateParticleSystem(&particleSystemDef);
    }

    // CreateParticleSystem2
    b2ParticleSystem *CreateParticleSystem2(b2World *world, float radius, float damping, float gravityScale, int number, float tennorm, float tenpres, float viscstr)
    {
        b2ParticleSystemDef particleSystemDef;
        particleSystemDef.radius = radius;
        particleSystemDef.dampingStrength = damping;
        particleSystemDef.gravityScale = gravityScale;
        particleSystemDef.maxCount = number;
        particleSystemDef.surfaceTensionNormalStrength = tennorm;
        particleSystemDef.surfaceTensionPressureStrength = tenpres;
        particleSystemDef.viscousStrength = viscstr;

        return world->CreateParticleSystem(&particleSystemDef);
    }

    // SetParticleSystemIndex
    void SetParticleSystemIndex(b2ParticleSystem *particleSystem, int userData)
    {
        // Assuming you have a structure or method to store user data in particle system
        particleSystem->GetParticleHandleFromIndex(reinterpret_cast<void *>(userData));
    }

    // GetParticleIterations
    int GetParticleIterations(float gravity, float particleRadius, float timeStep)
    {
        return b2CalculateParticleIterations(gravity, particleRadius, timeStep);
    }

    // GetParticlePositions
    float *GetParticlePositions(b2ParticleSystem *particleSystem)
    {
        const b2Vec2 *positions = particleSystem->GetPositionBuffer();
        int particleCount = particleSystem->GetParticleCount();
        int arraySize = 2 * particleCount + 1;
        float *result = new float[arraySize];
        result[0] = static_cast<float>(particleCount);

        for (int i = 0; i < particleCount; ++i)
        {
            result[2 * i + 1] = positions[i].x;
            result[2 * i + 2] = positions[i].y;
        }

        return result;
    }

    // GetParticlePositionsAndColors
    float *GetParticlePositionsAndColors(b2ParticleSystem *particleSystem)
    {
        const b2Vec2 *positions = particleSystem->GetPositionBuffer();
        const b2ParticleColor *colors = particleSystem->GetColorBuffer();
        int particleCount = particleSystem->GetParticleCount();
        int arraySize = 6 * particleCount + 1;
        float *result = new float[arraySize];
        result[0] = static_cast<float>(particleCount);

        for (int i = 0; i < particleCount; ++i)
        {
            result[6 * i + 1] = positions[i].x;
            result[6 * i + 2] = positions[i].y;
            result[6 * i + 3] = colors[i].r;
            result[6 * i + 4] = colors[i].g;
            result[6 * i + 5] = colors[i].b;
            result[6 * i + 6] = colors[i].a;
        }

        return result;
    }

    // GetParticlesDetails
    float *GetParticlesDetails(b2ParticleSystem *particleSystem, bool position, bool color, bool age, bool weight, bool velocity, bool userdata)
    {
        // Assuming you have corresponding methods to get age, weight, velocity, and user data
        // You may need to modify this based on the actual Box2D API for particle properties
        const b2Vec2 *positions = particleSystem->GetPositionBuffer();
        const b2ParticleColor *colors = particleSystem->GetColorBuffer();
        const int32 *indices = particleSystem->GetIndexBuffer();
        int particleCount = particleSystem->GetParticleCount();
        int arraySize = (position ? 2 : 0) + (color ? 4 : 0) + (age ? 1 : 0) + (weight ? 1 : 0) + (velocity ? 2 : 0) + (userdata ? 1 : 0) + 1;
        float *result = new float[arraySize];
        result[0] = static_cast<float>(particleCount);

        int currentIndex = 1;
        for (int i = 0; i < particleCount; ++i)
        {
            if (position)
            {
                result[currentIndex++] = positions[i].x;
                result[currentIndex++] = positions[i].y;
            }
            if (color)
            {
                result[currentIndex++] = colors[i].r;
                result[currentIndex++] = colors[i].g;
                result[currentIndex++] = colors[i].b;
                result[currentIndex++] = colors[i].a;
            }
            // Add other particle details based on the parameters
            // ...
        }

        return result;
    }

    // GetNumberOfParticles
    int GetNumberOfParticles(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetParticleCount();
    }

    // DeleteParticleSystem
    void DeleteParticleSystem(b2World *world, b2ParticleSystem *particleSystem)
    {
        world->DestroyParticleSystem(particleSystem);
    }

    // SetAllParticleFlags
    void SetAllParticleFlags(b2ParticleSystem *particleSystem, int particleFlags)
    {
        for (int i = 0; i < particleSystem->GetParticleCount(); ++i)
        {
            particleSystem->SetParticleFlags(i, particleFlags);
        }
    }

    // SetParticleFlagsUpToLimit
    void SetParticleFlagsUpToLimit(b2ParticleSystem *particleSystem, int particleFlags, int upperBound)
    {
        int particleCount = particleSystem->GetParticleCount();
        for (int i = 0; i < std::min(upperBound, particleCount); ++i)
        {
            particleSystem->SetParticleFlags(i, particleFlags);
        }
    }

    // GetStuckCandidateCount
    int GetStuckCandidateCount(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetStuckCandidateCount();
    }

    // SetStuckThreshold
    void SetStuckThreshold(b2ParticleSystem *particleSystem, int iterations)
    {
        particleSystem->SetStuckThreshold(iterations);
    }

    // DestroyParticlesInShape
    int DestroyParticlesInShape(b2ParticleSystem *particleSystem, b2Shape *shape, float shapeX, float shapeY, float shapeRotation, bool callDestructionListener)
    {
        b2Transform transform;
        transform.SetIdentity();
        transform.SetPosition(b2Vec2(shapeX, shapeY));
        transform.SetRotation(shapeRotation);

        return particleSystem->DestroyParticlesInShape(*shape, transform, callDestructionListener);
    }

    // GetParticlesInShape
    int *GetParticlesInShape(b2World *world, b2ParticleSystem *particleSystem, b2Shape *shape, float shapeX, float shapeY, float shapeRotation)
    {
        b2Transform transform;
        transform.SetIdentity();
        transform.SetPosition(b2Vec2(shapeX, shapeY));
        transform.SetRotation(shapeRotation);

        b2ParticleSystem::InsideBoundsEnumerator enumerator;
        b2AABB aabb;
        shape->ComputeAABB(&aabb, transform, 0);
        int32 *indices = new int32[particleSystem->GetParticleCount()];
        int32 count = particleSystem->GetInsideBoundsEnumerator(aabb).GetIndices(indices, particleSystem->GetParticleCount());
        int *result = new int[count + 1];
        result[0] = count;

        for (int i = 0; i < count; ++i)
        {
            result[i + 1] = indices[i];
        }

        delete[] indices;
        return result;
    }

    // SetDestructionByAge
    void SetDestructionByAge(b2ParticleSystem *particleSystem, bool isSet)
    {
        particleSystem->SetDestructionByAge(isSet);
    }

    // GetDestructionByAge
    bool GetDestructionByAge(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetDestructionByAge();
    }

    // SetAllParticleLifetimes
    void SetAllParticleLifetimes(b2ParticleSystem *particleSystem, float lifetime)
    {
        for (int i = 0; i < particleSystem->GetParticleCount(); ++i)
        {
            particleSystem->SetParticleLifetime(i, lifetime);
        }
    }

    // GetMaxParticleCount
    int GetMaxParticleCount(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetMaxParticleCount();
    }

    // SetMaxParticleCount
    void SetMaxParticleCount(b2ParticleSystem *particleSystem, int maxParticleCount)
    {
        particleSystem->SetMaxParticleCount(maxParticleCount);
    }

    // GetParticleSystemContacts
    int *GetParticleSystemContacts(b2ParticleSystem *particleSystem)
    {
        b2ParticleContact *contacts = particleSystem->GetParticleContacts();
        int32 count = particleSystem->GetParticleContactCount();
        int *result = new int[count * 4 + 1];
        result[0] = count;

        for (int i = 0; i < count; ++i)
        {
            result[4 * i + 1] = contacts[i].GetIndexA();
            result[4 * i + 2] = contacts[i].GetIndexB();
            result[4 * i + 3] = static_cast<int>(contacts[i].GetUserDataA());
            result[4 * i + 4] = static_cast<int>(contacts[i].GetUserDataB());
        }

        return result;
    }

    // GetParticleSystemBodyContacts
    float *GetParticleSystemBodyContacts(b2ParticleSystem *particleSystem)
    {
        b2ParticleBodyContact *contacts = particleSystem->GetBodyContacts();
        int32 count = particleSystem->GetBodyContactCount();
        int arraySize = 7 * count + 1;
        float *result = new float[arraySize];
        result[0] = count;

        for (int i = 0; i < count; ++i)
        {
            result[7 * i + 1] = static_cast<float>(contacts[i].index);
            result[7 * i + 2] = static_cast<float>(contacts[i].userData);
            result[7 * i + 3] = static_cast<float>(contacts[i].bodyUserData);
            result[7 * i + 4] = static_cast<float>(contacts[i].fixtureUserData);
            result[7 * i + 5] = contacts[i].normal.x;
            result[7 * i + 6] = contacts[i].normal.y;
            result[7 * i + 7] = contacts[i].weight;
        }

        return result;
    }

    // GetParticleGroupCount
    int GetParticleGroupCount(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetParticleGroupCount();
    }

    // GetParticleGroupPointers
    b2ParticleGroup **GetParticleGroupPointers(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetParticleGroups();
    }

    // GetParticleGroupPointerForLargestGroup
    b2ParticleGroup *GetParticleGroupPointerForLargestGroup(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetLargestParticleGroup();
    }

    // LiquidFunAPI.cpp (continued)

    // SetAllParticleFlags
    void SetAllParticleFlags(b2ParticleSystem *particleSystem, int particleFlags)
    {
        particleSystem->SetAllParticleFlags(particleFlags);
    }

    // SetParticleFlagsUpToLimit
    void SetParticleFlagsUpToLimit(b2ParticleSystem *particleSystem, int particleFlags, int upperBound)
    {
        particleSystem->SetParticleFlagsUpToLimit(particleFlags, upperBound);
    }

    // SetDesctructionByAge
    void SetDestructionByAge(IntPtr particleSystemPointer, bool isSet)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        particleSystem->SetDestructionByAge(isSet);
    }

    // GetDestructionByAge
    bool GetDestructionByAge(IntPtr particleSystemPointer)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        return particleSystem->GetDestructionByAge();
    }

    // SetAllParticleLifetimes
    void SetAllParticleLifetimes(IntPtr particleSystemPointer, float lifetime)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        for (int i = 0; i < particleSystem->GetParticleCount(); ++i)
        {
            particleSystem->SetParticleLifetime(i, lifetime);
        }
    }

    // GetMaxParticleCount
    int GetMaxParticleCount(IntPtr particleSystemPointer)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        return particleSystem->GetMaxParticleCount();
    }

    // SetMaxParticleCount
    void SetMaxParticleCount(IntPtr particleSystemPointer, int maxParticleCount)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        particleSystem->SetMaxParticleCount(maxParticleCount);
    }

    // GetParticleSystemContacts
    int *GetParticleSystemContacts(IntPtr particleSystemPointer)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        b2ParticleContact *contacts = particleSystem->GetParticleContacts();
        int32 count = particleSystem->GetParticleContactCount();
        int *result = new int[count * 4 + 1];
        result[0] = count;

        for (int i = 0; i < count; ++i)
        {
            result[4 * i + 1] = contacts[i].GetIndexA();
            result[4 * i + 2] = contacts[i].GetIndexB();
            result[4 * i + 3] = static_cast<int>(contacts[i].GetUserDataA());
            result[4 * i + 4] = static_cast<int>(contacts[i].GetUserDataB());
        }

        return result;
    }

    // GetParticleSystemBodyContacts
    float *GetParticleSystemBodyContacts(IntPtr particleSystemPointer)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        b2ParticleBodyContact *contacts = particleSystem->GetBodyContacts();
        int32 count = particleSystem->GetBodyContactCount();
        int arraySize = 7 * count + 1;
        float *result = new float[arraySize];
        result[0] = count;

        for (int i = 0; i < count; ++i)
        {
            result[7 * i + 1] = static_cast<float>(contacts[i].index);
            result[7 * i + 2] = static_cast<float>(contacts[i].userData);
            result[7 * i + 3] = static_cast<float>(contacts[i].bodyUserData);
            result[7 * i + 4] = static_cast<float>(contacts[i].fixtureUserData);
            result[7 * i + 5] = contacts[i].normal.x;
            result[7 * i + 6] = contacts[i].normal.y;
            result[7 * i + 7] = contacts[i].weight;
        }

        return result;
    }

    // GetParticleGroupCount
    int GetParticleGroupCount(IntPtr particleSystemPointer)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        return particleSystem->GetParticleGroupCount();
    }

    // GetParticleGroupPointers
    b2ParticleGroup **GetParticleGroupPointers(IntPtr particleSystemPointer)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        return particleSystem->GetParticleGroups();
    }

    // GetParticleGroupPointerForLargestGroup
    b2ParticleGroup *GetParticleGroupPointerForLargestGroup(IntPtr particleSystemPointer)
    {
        b2ParticleSystem *particleSystem = reinterpret_cast<b2ParticleSystem *>(particleSystemPointer);
        return particleSystem->GetLargestParticleGroup();
    }
}
