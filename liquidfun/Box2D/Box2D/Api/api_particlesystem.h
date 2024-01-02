#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>
#include <cstdint>
#include "api.h"
#define IntPtr void *
extern "C"
{
    // CreateParticleSystem
    UNITY_INTERFACE_EXPORT b2ParticleSystem* UNITY_INTERFACE_API CreateParticleSystem(b2World *world, float radius, float damping, float gravityScale, int index)
    {
        b2ParticleSystemDef particleSystemDef;
        particleSystemDef.radius = radius;
        particleSystemDef.dampingStrength = damping;
        particleSystemDef.gravityScale = gravityScale;
        particleSystemDef.index =index;

        return world->CreateParticleSystem(&particleSystemDef);
    }

    // CreateParticleSystem2
    UNITY_INTERFACE_EXPORT b2ParticleSystem* UNITY_INTERFACE_API CreateParticleSystem2(b2World *world, float radius, float damping, float gravityScale, int index, float tennorm, float tenpres, float viscstr)
    {
        b2ParticleSystemDef particleSystemDef;
        particleSystemDef.radius = radius;
        particleSystemDef.dampingStrength = damping;
        particleSystemDef.gravityScale = gravityScale;
        particleSystemDef.index =index;
        particleSystemDef.surfaceTensionNormalStrength = tennorm;
        particleSystemDef.surfaceTensionPressureStrength = tenpres;
        particleSystemDef.viscousStrength = viscstr;

        return world->CreateParticleSystem(&particleSystemDef);
    }

    // SetParticleSystemIndex
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetParticleSystemIndex(b2ParticleSystem *particleSystem, int index)
    {
        particleSystem->systemIndex = index;
    }

    // GetParticleIterations
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetParticleIterations(float gravity, float particleRadius, float timeStep)
    {
        return b2CalculateParticleIterations(gravity, particleRadius, timeStep);
    }

    // GetParticlePositions
    UNITY_INTERFACE_EXPORT float* UNITY_INTERFACE_API GetParticlePositions(b2ParticleSystem *particleSystem)
    {
        const b2Vec2 *positions = particleSystem->GetPositionBuffer();
        int particleCount = particleSystem->GetParticleCount();
        int arraySize = 2 * particleCount + 1;
        float *result = GetFloatBuffer(arraySize);
        result[0] = static_cast<float>(particleCount);

        for (int i = 0; i < particleCount; ++i)
        {
            result[2 * i + 1] = positions[i].x;
            result[2 * i + 2] = positions[i].y;
        }

        return result;
    }

    // GetParticlePositionsAndColors
    UNITY_INTERFACE_EXPORT float* UNITY_INTERFACE_API GetParticlePositionsAndColors(b2ParticleSystem *particleSystem)
    {
        const b2Vec2 *positions = particleSystem->GetPositionBuffer();
        const b2ParticleColor *colors = particleSystem->GetColorBuffer();
        int particleCount = particleSystem->GetParticleCount();
        int arraySize = 6 * particleCount + 1;
        float *result = GetFloatBuffer(arraySize);
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
    UNITY_INTERFACE_EXPORT float* UNITY_INTERFACE_API GetParticlesDetails(b2ParticleSystem *particleSystem, bool position, bool color, bool age, bool weight, bool velocity, bool userdata)
    {
        const b2Vec2 *positions = particleSystem->GetPositionBuffer();
        const b2ParticleColor *colors = particleSystem->GetColorBuffer();
        const int32 *lifetimes = particleSystem->GetExpirationTimeBuffer();
        const float32 *weights = particleSystem->GetWeightBuffer();
        const b2Vec2 *velocities = particleSystem->GetVelocityBuffer();
        void **userDatas = particleSystem->GetUserDataBuffer();
        int particleCount = particleSystem->GetParticleCount();
        int arraySize = (position ? 2 : 0) + (color ? 4 : 0) + (age ? 1 : 0) + (weight ? 1 : 0) + (velocity ? 2 : 0) + (userdata ? 1 : 0);
        float *result = GetFloatBuffer(particleCount*arraySize+1);
        result[0] = static_cast<float>(particleCount);

        int currentIndex = 1;
        if (position)
        {
            for (int i = 0; i < particleCount; ++i)
            {
                result[currentIndex++] = positions[i].x;
                result[currentIndex++] = positions[i].y;
            }
        }
        if (color)
        {
            for (int i = 0; i < particleCount; ++i)
            {
                result[currentIndex++] = colors[i].r;
                result[currentIndex++] = colors[i].g;
                result[currentIndex++] = colors[i].b;
                result[currentIndex++] = colors[i].a;
            }
        }
        if (age)
        {
            for (int i = 0; i < particleCount; ++i)
            {
                result[currentIndex++] = lifetimes[i];
            }
        }
        if (weight)
        {
            for (int i = 0; i < particleCount; ++i)
            {
                result[currentIndex++] = weights[i];
            }
        }
        if (velocity)
        {
            for (int i = 0; i < particleCount; ++i)
            {
                result[currentIndex++] = velocities[i].x;
                result[currentIndex++] = velocities[i].y;
            }
        }
        if (userdata)
        {
            for (int i = 0; i < particleCount; ++i)
            {
                int32 userDataFloat = reinterpret_cast<int>(userDatas[i]);
                result[currentIndex++] = userDataFloat;
            }
        }

        return result;
    }

    // GetNumberOfParticles
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetNumberOfParticles(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetParticleCount();
    }

    // DeleteParticleSystem
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API DeleteParticleSystem(b2World *world, b2ParticleSystem *particleSystem)
    {
        world->DestroyParticleSystem(particleSystem);
    }

    // SetAllParticleFlags
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetAllParticleFlags(b2ParticleSystem *particleSystem, int particleFlags)
    {
        for (int i = 0; i < particleSystem->GetParticleCount(); ++i)
        {
            particleSystem->SetParticleFlags(i, particleFlags);
        }
    }

    // SetParticleFlagsUpToLimit
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetParticleFlagsUpToLimit(b2ParticleSystem *particleSystem, int particleFlags, int upperBound)
    {
        int particleCount = particleSystem->GetParticleCount();
        for (int i = 0; i < std::min(upperBound, particleCount); ++i)
        {
            particleSystem->SetParticleFlags(i, particleFlags);
        }
    }

    // GetStuckCandidateCount
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetStuckCandidateCount(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetStuckCandidateCount();
    }

    // SetStuckThreshold
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetStuckThreshold(b2ParticleSystem *particleSystem, int iterations)
    {
        particleSystem->SetStuckThreshold(iterations);
    }

    // DestroyParticlesInShape
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API DestroyParticlesInShape(b2ParticleSystem *particleSystem, b2Shape *shape, float shapeX, float shapeY, float shapeRotation, bool callDestructionListener)
    {
        b2Transform transform;
        transform.SetIdentity();
        transform.Set(b2Vec2(shapeX, shapeY),shapeRotation);

        return particleSystem->DestroyParticlesInShape(*shape, transform, callDestructionListener);
    }

    // GetParticlesInShape
    UNITY_INTERFACE_EXPORT int* UNITY_INTERFACE_API GetParticlesInShape(b2World *world, b2ParticleSystem *particleSystem, b2Shape *shape, float shapeX, float shapeY, float shapeRotation)
    {
        b2Transform transform;
        transform.SetIdentity();
        transform.Set(b2Vec2(shapeX, shapeY),shapeRotation);

        b2AABB aabb;
        shape->ComputeAABB(&aabb, transform, 0);
        auto enumerator = particleSystem->GetInsideBoundsEnumerator(aabb);
        
        std::vector<int32> particleIndices;
        int32 particleIndex = 0;
        while ((particleIndex = enumerator.GetNext()) != b2_invalidParticleIndex)
        {
            particleIndices.push_back(particleIndex);
        }
        int count = particleIndices.size();
        int* result = GetIntBuffer(count+1);
        result[0] = count;
        for (int i = 0; i < count; ++i)
        {
            result[i + 1] = particleIndices[i];
        }

        return result;
    }

    // SetDestructionByAge
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetDestructionByAge(b2ParticleSystem *particleSystem, bool isSet)
    {
        particleSystem->SetDestructionByAge(isSet);
    }

    // GetDestructionByAge
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetDestructionByAge(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetDestructionByAge();
    }

    // SetAllParticleLifetimes
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetAllParticleLifetimes(b2ParticleSystem *particleSystem, float lifetime)
    {
        for (int i = 0; i < particleSystem->GetParticleCount(); ++i)
        {
            particleSystem->SetParticleLifetime(i, lifetime);
        }
    }

    // GetMaxParticleCount
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetMaxParticleCount(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetMaxParticleCount();
    }

    // SetMaxParticleCount
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMaxParticleCount(b2ParticleSystem *particleSystem, int maxParticleCount)
    {
        particleSystem->SetMaxParticleCount(maxParticleCount);
    }

    // GetParticleSystemContacts
    UNITY_INTERFACE_EXPORT int* UNITY_INTERFACE_API GetParticleSystemContacts(b2ParticleSystem *particleSystem)
    {
        auto userDataBuffer = particleSystem->GetUserDataBuffer();
        auto m_contactBuffer = particleSystem->GetContacts();
        int32 count = particleSystem->GetContactCount();
        int *result = GetIntBuffer(count * 4 + 1);
        result[0] = count;

        for (int i = 0; i < count; ++i)
        {
            result[4 * i + 1] = m_contactBuffer[i].GetIndexA();
            result[4 * i + 2] = m_contactBuffer[i].GetIndexB();
            result[4 * i + 3] = reinterpret_cast<int>(userDataBuffer[m_contactBuffer[i].GetIndexA()]);
            result[4 * i + 4] = reinterpret_cast<int>(userDataBuffer[m_contactBuffer[i].GetIndexB()]);
        }
        return result;
    }

    // GetParticleSystemBodyContacts
    UNITY_INTERFACE_EXPORT float* UNITY_INTERFACE_API GetParticleSystemBodyContacts(b2ParticleSystem *particleSystem)
    {
        auto userDataBuffer = particleSystem->GetUserDataBuffer();
        auto m_contactBuffer = particleSystem->GetBodyContacts();
        int32 count = particleSystem->GetBodyContactCount();
        float *result = GetFloatBuffer(count * 7 + 1);
        result[0] = count;

        for (int i = 0; i < count; ++i)
        {
            result[7 * i + 1] = static_cast<float>(m_contactBuffer[i].index);
            result[7 * i + 2] = reinterpret_cast<int>(userDataBuffer[m_contactBuffer[i].index]);
            result[7 * i + 3] = reinterpret_cast<int>(m_contactBuffer[i].body->GetUserData());
            result[7 * i + 4] = reinterpret_cast<int>(m_contactBuffer[i].fixture->GetUserData());
            result[7 * i + 5] = m_contactBuffer[i].normal.x;
            result[7 * i + 6] = m_contactBuffer[i].normal.y;
            result[7 * i + 7] = m_contactBuffer[i].weight;
        }
        return result;
    }

    // GetParticleGroupCount
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetParticleGroupCount(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetParticleGroupCount();
    }

    // GetParticleGroupPointers
    UNITY_INTERFACE_EXPORT b2ParticleGroup* const* UNITY_INTERFACE_API GetParticleGroupPointers(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetGroupBuffer();
    }

    // GetParticleGroupPointerForLargestGroup
    UNITY_INTERFACE_EXPORT b2ParticleGroup* UNITY_INTERFACE_API GetParticleGroupPointerForLargestGroup(b2ParticleSystem* particleSystem)
    {
        b2ParticleGroup* largestGroup = nullptr;
        int32 maxParticleCount = 0;

        // 迭代粒子组
        for (b2ParticleGroup* group = particleSystem->GetParticleGroupList(); group; group = group->GetNext())
        {
            int32 particleCount = group->GetParticleCount();
            if (particleCount > maxParticleCount)
            {
                maxParticleCount = particleCount;
                largestGroup = group;
            }
        }

        return largestGroup;
    }
}
