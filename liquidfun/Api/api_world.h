#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"

extern "C" {

    // CreateWorld
    b2World* CreateWorld(float gravityX, float gravityY) {
        b2Vec2 gravity(gravityX, gravityY);
        return new b2World(gravity);
    }

    // End
    int End(b2World* world) {
        delete world;
        return 0;
    }

    // StepWithParticleIterations
    float StepWithParticleIterations(b2World* world, float timeStep, int velocityIterations, int positionIterations, int particleIterations) {
        world->Step(timeStep, velocityIterations, positionIterations, particleIterations);
        return 0.0f;
    }

    // GetAllowSleeping
    bool GetAllowSleeping(b2World* world) {
        return world->GetAllowSleeping();
    }

    // SetAllowSleeping
    void SetAllowSleeping(b2World* world, bool flag) {
        world->SetAllowSleeping(flag);
    }

    // GetWorldGravity
    b2Vec2 GetWorldGravity(b2World* world) {
        return world->GetGravity();
    }

    // SetWorldGravity
    void SetWorldGravity(b2World* world, float gravityX, float gravityY) {
        b2Vec2 gravity(gravityX, gravityY);
        world->SetGravity(gravity);
    }

    // WorldTestPointForBody
    b2Body* WorldTestPointForBody(b2World* world, float x, float y) {
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
