#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>
#include "api.h"

extern "C"
{
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API CreateParticleInSystem(b2ParticleSystem* system, int32_t flags, float positionX, float positionY, float velocityX, float velocityY, int r, int g, int b, int a, float lifetime)
    {
        b2ParticleDef particleDef;
        particleDef.flags = static_cast<uint32>(flags);
        particleDef.position.Set(positionX, positionY);
        particleDef.velocity.Set(velocityX, velocityY);
        particleDef.color.Set(r, g, b, a);
        particleDef.lifetime = lifetime;

        system->CreateParticle(particleDef);
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSelectedParticleColor(b2ParticleSystem* particles, const int32_t* indexArray, int r, int g, int b, int a)
    {
        b2ParticleColor* colors = particles->GetColorBuffer();
        for (int32_t i = 0; i < indexArray[0]; ++i)
        {
            b2ParticleColor& color = colors[indexArray[i + 1]];
            color.Set(r, g, b, a);
        }
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSelectedParticleUserData(b2ParticleSystem* particles, const int32_t* indexArray, int userdata)
    {
        for (int32_t i = 0; i < indexArray[0]; ++i)
        {
            int32_t particleIndex = indexArray[i + 1];

            // 设置用户数据
            void** userDataBuffer = particles->GetUserDataBuffer();
            userDataBuffer[particleIndex] = reinterpret_cast<void*>(userdata);
        }
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetSelectedParticleFlags(b2ParticleSystem* particles, const int32_t* indexArray, int particleFlags)
    {
        for (int32_t i = 0; i < indexArray[0]; ++i)
        {
            particles->SetParticleFlags(indexArray[i + 1], particleFlags);
        }
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API DestroySelectedParticles(b2ParticleSystem* particles, const int32_t* indexArray)
    {
        for (int32_t i = 0; i < indexArray[0]; ++i)
        {
            particles->DestroyParticle(indexArray[i + 1]);
        }
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ExplodeSelectedParticles(b2ParticleSystem* particles, const int32_t* indexArray, float CentreX, float CentreY, float Strength)
    {
        b2Vec2 explosionCenter(CentreX, CentreY);

        for (int32_t i = 0; i < indexArray[0]; ++i)
        {
            int32_t particleIndex = indexArray[i + 1];
            b2Vec2 particlePos = particles->GetPositionBuffer()[particleIndex];
            b2Vec2 explosionForce = (particlePos - explosionCenter) * Strength;

            particles->ApplyLinearImpulse(particleIndex, particleIndex + 1, explosionForce);
        }
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ApplyForceToSelectedParticles(b2ParticleSystem* particles, const int32_t* indexArray, float forceX, float forceY)
    {
        b2Vec2 force(forceX, forceY);

        for (int32_t i = 0; i < indexArray[0]; ++i)
        {
            particles->ApplyForceToSelectedParticles(particles,indexArray,forceX,forceY);
        }
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ApplyLinearImpulseToSelectedParticles(b2ParticleSystem* particles, const int32_t* indexArray, float impulseX, float impulseY)
    {
        b2Vec2 impulse(impulseX, impulseY);

        for (int32_t i = 0; i < indexArray[0]; ++i)
        {
            particles->ApplyLinearImpulseToSelectedParticles(particles,indexArray,impulseX,impulseY);
        }
    }

    UNITY_INTERFACE_EXPORT float* UNITY_INTERFACE_API GetSelectedParticlesDetails(b2ParticleSystem* particles, const int32_t* indexArray, bool position, bool color, bool age, bool weight, bool velocity, bool userdata)
    {
        int32_t numParticles = indexArray[0];
        int32_t numInfoPerParticle = 11; // x, y, r, g, b, a, age, weight, userdata,particleVelocity

        float* details = GetFloatBuffer(numParticles * numInfoPerParticle);

        for (int32_t i = 0; i < numParticles; ++i)
        {
            int32_t particleIndex = indexArray[i + 1];
            b2Vec2 particlePos = particles->GetPositionBuffer()[particleIndex];
            b2ParticleColor particleColor = particles->GetColorBuffer()[particleIndex];

            int dataIndex = i * numInfoPerParticle;

            if (position)
            {
                details[dataIndex] = particlePos.x;
                details[dataIndex + 1] = particlePos.y;
            }

            if (color)
            {
                details[dataIndex + 2] = particleColor.r;
                details[dataIndex + 3] = particleColor.g;
                details[dataIndex + 4] = particleColor.b;
                details[dataIndex + 5] = particleColor.a;
            }

            if (age)
            {
                details[dataIndex + 6] = particles->GetParticleLifetime(particleIndex);
            }

            if (weight)
            {
                details[dataIndex + 7] = particles->GetParticleMass();
            }

            if (userdata)
            {
                // 在这里处理用户数据，例如，将用户数据转换为整数
                details[dataIndex + 8] = static_cast<int32>(reinterpret_cast<uintptr_t>(particles->GetUserDataBuffer()[particleIndex]));
            }

            if (velocity)
            {
                b2Vec2 particleVelocity = particles->GetVelocityBuffer()[particleIndex];
                details[dataIndex + 9] = particleVelocity.x;
                details[dataIndex + 10] = particleVelocity.y;
            }
        }

        return details;
    }
}
