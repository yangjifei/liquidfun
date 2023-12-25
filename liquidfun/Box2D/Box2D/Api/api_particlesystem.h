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
    b2ParticleSystem *CreateParticleSystem(b2World *world, float radius, float damping, float gravityScale, int index)
    {
        b2ParticleSystemDef particleSystemDef;
        particleSystemDef.radius = radius;
        particleSystemDef.dampingStrength = damping;
        particleSystemDef.gravityScale = gravityScale;
        particleSystemDef.index =index;

        return world->CreateParticleSystem(&particleSystemDef);
    }

    // CreateParticleSystem2
    b2ParticleSystem *CreateParticleSystem2(b2World *world, float radius, float damping, float gravityScale, int index, float tennorm, float tenpres, float viscstr)
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
    void SetParticleSystemIndex(b2ParticleSystem *particleSystem, int index)
    {
        particleSystem->index = index;
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
    float *GetParticlePositionsAndColors(b2ParticleSystem *particleSystem)
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
    float *GetParticlesDetails(b2ParticleSystem *particleSystem, bool position, bool color, bool age, bool weight, bool velocity, bool userdata)
    {
        const b2Vec2 *positions = particleSystem->GetPositionBuffer();
        const b2ParticleColor *colors = particleSystem->GetColorBuffer();
        const int32 *lifetimes = particleSystem->GetExpirationTimeBuffer();
        const float32 *weights = particleSystem->GetWeightBuffer();
        const b2Vec2 *velocities = particleSystem->GetVelocityBuffer();
        const void **userDatas = particleSystem->GetUserDataBuffer();
        int particleCount = particleSystem->GetParticleCount();
        int arraySize = (position ? 2 : 0) + (color ? 4 : 0) + (age ? 1 : 0) + (weight ? 1 : 0) + (velocity ? 2 : 0) + (userdata ? 1 : 0) + 1;
        float *result = GetFloatBuffer(arraySize);
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
            if (age)
            {
                result[currentIndex++] = lifetimes[i];
            }
            if (weight)
            {
                result[currentIndex++] = weights[i];
            }
            if (velocity)
            {
                result[currentIndex++] = velocities[i].x;
                result[currentIndex++] = velocities[i].y;
            }
            if (userdata)
            {
                int32 userDataFloat = reinterpret_cast<int>(userDatas[i]);
                result[currentIndex++] = userDataFloat;
            }
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
        transform.Set(b2Vec2(shapeX, shapeY),shapeRotation);

        return particleSystem->DestroyParticlesInShape(*shape, transform, callDestructionListener);
    }

    // GetParticlesInShape
    int *GetParticlesInShape(b2World *world, b2ParticleSystem *particleSystem, b2Shape *shape, float shapeX, float shapeY, float shapeRotation)
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
    float *GetParticleSystemBodyContacts(b2ParticleSystem *particleSystem)
    {
        auto userDataBuffer = particleSystem->GetUserDataBuffer();
        auto m_contactBuffer = particleSystem->GetBodyContacts();
        int32 count = particleSystem->GetBodyContactCount();
        float *result = GetFloatBuffer(count * 4 + 1);
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
    int GetParticleGroupCount(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetParticleGroupCount();
    }

    // GetParticleGroupPointers
    b2ParticleGroup *  const* GetParticleGroupPointers(b2ParticleSystem *particleSystem)
    {
        return particleSystem->GetGroupBuffer();
    }

    // GetParticleGroupPointerForLargestGroup
    b2ParticleGroup* GetParticleGroupPointerForLargestGroup(b2ParticleSystem* particleSystem)
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
