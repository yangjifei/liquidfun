#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "../Unity/IUnityInterface.h"

extern "C" {

    // CreateWorld
    UNITY_INTERFACE_EXPORT b2World* UNITY_INTERFACE_API CreateWorld(float gravityX, float gravityY) {
        b2Vec2 gravity(gravityX, gravityY);
        return new b2World(gravity);
    }

    // End
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API End(b2World* world) {
        if(world->GetContactManager().m_contactListener!=NULL){
            delete world->GetContactManager().m_contactListener;
        }
        delete world;
        return 0;
    }

    // StepWithParticleIterations
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API StepWithParticleIterations(b2World* world, float timeStep, int velocityIterations, int positionIterations, int particleIterations) {
        world->Step(timeStep, velocityIterations, positionIterations, particleIterations);
        return 0.0f;
    }

    // GetAllowSleeping
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetAllowSleeping(b2World* world) {
        return world->GetAllowSleeping();
    }

    // SetAllowSleeping
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetAllowSleeping(b2World* world, bool flag) {
        world->SetAllowSleeping(flag);
    }

    // GetWorldGravity
    b2Vec2 UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWorldGravity(b2World* world) {
        return world->GetGravity();
    }

    // SetWorldGravity
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetWorldGravity(b2World* world, float gravityX, float gravityY) {
        b2Vec2 gravity(gravityX, gravityY);
        world->SetGravity(gravity);
    }

    // WorldTestPointForBody
    UNITY_INTERFACE_EXPORT b2Body* UNITY_INTERFACE_API WorldTestPointForBody(b2World* world, float x, float y) {
        b2Vec2 point(x, y);
        for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
            for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
                if (f->TestPoint(point)) {
                    return b;
                }
            }
        }
        return nullptr;
    }
}
