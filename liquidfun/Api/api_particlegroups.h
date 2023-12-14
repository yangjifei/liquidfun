#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>
#include <Box2D/Box2D.h>

// Particle Groups
extern "C" {
    // CreateParticleGroup
    void* CreateParticleGroup(void* particlePointer, int types, int groupTypes,
                              float angle, float strength, float angularVelocity,
                              float linearVelocityX, float linearVelocityY,
                              void* shape, int r, int g, int b, int a,
                              float stride, float lifetime, int userdata) {
        b2ParticleSystem* particleSystemPtr = static_cast<b2ParticleSystem*>(particlePointer);
        b2Shape* b2ShapePtr = static_cast<b2Shape*>(shape);

        b2ParticleGroupDef groupDef;
        groupDef.shape = b2ShapePtr;
        groupDef.flags = static_cast<uint32>(types);
        groupDef.groupFlags = static_cast<uint32>(groupTypes);
        groupDef.angle = angle;
        groupDef.strength = strength;
        groupDef.angularVelocity = angularVelocity;
        groupDef.linearVelocity.Set(linearVelocityX, linearVelocityY);
        groupDef.color.Set(r, g, b, a);
        groupDef.stride = stride;
        groupDef.lifetime = lifetime;
        groupDef.userData = reinterpret_cast<void*>(userdata);

        b2ParticleGroup* particleGroup = particleSystemPtr->CreateParticleGroup(groupDef);
        return static_cast<void*>(particleGroup);
    }

    // DeleteParticlesInGroup
    void DeleteParticlesInGroup(void* particleGroupPointer) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        b2ParticleSystem* particleSystem = particleGroup->GetParticleSystem();
        particleSystem->DestroyParticleGroup(particleGroup);
    }

    // GetParticlesInGroupCount
    int GetParticlesInGroupCount(void* particleGroupPointer) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        return particleGroup->GetParticleCount();
    }

    // SetParticleFlagsInGroup
    void SetParticleFlagsInGroup(void* particleGroupPointer, void* particleSystemPointer, int particleFlags) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        // Set the particle flags for the entire group
        particleGroup->SetGroupFlags(static_cast<uint32>(particleFlags));
    }

    // SetParticleLifetimesInGroup
    void SetParticleLifetimesInGroup(void* particleGroupPointer, void* particleSystemPointer, int lifetime) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        b2ParticleSystem* particleSystem = static_cast<b2ParticleSystem*>(particleSystemPointer);

        // Get the buffer index for the entire group
        int32 groupBufferIndex = particleGroup->GetBufferIndex();

        // Set the lifetime for each particle in the group
        int32 particleCount = particleGroup->GetParticleCount();
        for (int32 i = 0; i < particleCount; ++i) {
            int32 particleIndex = groupBufferIndex + i;
            particleSystem->SetParticleLifetime(particleIndex, static_cast<float32>(lifetime));
        }
    }

    // ApplyForceToParticleGroup
    void ApplyForceToParticleGroup(void* particleGroupPointer, float forceX, float forceY) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        particleGroup->ApplyForce(b2Vec2(forceX, forceY));
    }

    // ApplyLinearImpulseToParticleGroup
    void ApplyLinearImpulseToParticleGroup(void* particleGroupPointer, float impulseX, float impulseY) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        particleGroup->ApplyLinearImpulse(b2Vec2(impulseX, impulseY));
    }

    // SplitParticleGroup
    void SplitParticleGroup(void* particleSystemPointer, void* groupPointer) {
        b2ParticleSystem* particleSystem = static_cast<b2ParticleSystem*>(particleSystemPointer);
        b2ParticleGroup* groupA = static_cast<b2ParticleGroup*>(groupPointer);
        particleSystem->SplitParticleGroup(groupA);
    }

    // JoinParticleGroups
    void JoinParticleGroups(void* particleSystemPointer, void* groupAPointer, void* groupBPointer) {
        b2ParticleSystem* particleSystem = static_cast<b2ParticleSystem*>(particleSystemPointer);
        b2ParticleGroup* groupA = static_cast<b2ParticleGroup*>(groupAPointer);
        b2ParticleGroup* groupB = static_cast<b2ParticleGroup*>(groupBPointer);
        particleSystem->JoinParticleGroups(groupA, groupB);
    }

    // AreParticlesInGroup
    int* AreParticlesInGroup(void* particleGroupPointer, int* indices) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        int count = particleGroup->GetParticleCount();
        int* result = new int[count];

        const int* indicesArray = indices + 1;  // Skip the first element, which contains the count
        for (int i = 0; i < count; ++i) {
            result[i] = particleGroup->ContainsParticle(indicesArray[i]) ? 1 : 0;
        }

        return result;
    }

    // GetParticleGroupPosition
    float* GetParticleGroupPosition(void* particleGroupPointer) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        b2Vec2 position = particleGroup->GetCenter();
        float* result = new float[2];
        result[0] = position.x;
        result[1] = position.y;
        return result;
    }

    // GetParticleGroupCentroid
    float* GetParticleGroupCentroid(void* particleGroupPointer) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        b2Vec2 centroid = particleGroup->GetCenter();
        float* result = new float[2];
        result[0] = centroid.x;
        result[1] = centroid.y;
        return result;
    }

    // GetParticleGroupVelocity
    float* GetParticleGroupVelocity(void* particleGroupPointer) {
        b2ParticleGroup* particleGroup = static_cast<b2ParticleGroup*>(particleGroupPointer);
        b2Vec2 velocity = particleGroup->GetLinearVelocity();
        float* result = new float[2];
        result[0] = velocity.x;
        result[1] = velocity.y;
        return result;
    }
}
