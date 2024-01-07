#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>
#include "api.h"

extern "C" {

    // AddFixture
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API AddFixture(void* bodyPointer, int shapeType, void* shapePointer, float density, float friction, float restitution, bool isSensor, int userData) {
        b2Body* body = static_cast<b2Body*>(bodyPointer);
        b2Shape* shape = static_cast<b2Shape*>(shapePointer);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;
        fixtureDef.isSensor = isSensor;
        fixtureDef.userData = reinterpret_cast<void*>(userData);
        return body->CreateFixture(&fixtureDef);
    }

    // GetFixtureInfo
    UNITY_INTERFACE_EXPORT float* UNITY_INTERFACE_API GetFixtureInfo(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        b2Vec2 position = fixture->GetBody()->GetPosition(); // Use GetPosition() for the body's origin

        float* info = GetFloatBuffer(3);
        info[0] = position.x;
        info[1] = position.y;
        info[2] = fixture->GetBody()->GetAngle();

        return info;
    }

    // GetFixtureUserData
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureUserData(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return static_cast<int32>(reinterpret_cast<uintptr_t>(fixture->GetUserData()));
    }

    // SetFixtureFilterData
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetFixtureFilterData(void* fixturePointer, int16_t groupIndex, uint16_t categoryBits, uint16_t maskBits) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        b2Filter filter = fixture->GetFilterData();
        filter.groupIndex = groupIndex;
        filter.categoryBits = categoryBits;
        filter.maskBits = maskBits;
        fixture->SetFilterData(filter);
    }

    // GetFixtureGroupIndex
    uint16_t UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureGroupIndex(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFilterData().groupIndex;
    }

    // GetFixtureCategoryBits
    uint16_t UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureCategoryBits(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFilterData().categoryBits;
    }

    // GetFixtureMaskBits
    uint16_t UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureMaskBits(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFilterData().maskBits;
    }

    // TestPoint
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API TestPoint(void* fixturePointer, float x, float y) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        b2Vec2 point(x, y);
        return fixture->TestPoint(point);
    }

    // SetFixtureIsSensor
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetFixtureIsSensor(void* fixturePointer, bool flag) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetSensor(flag);
    }

    // GetFixtureIsSensor
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureIsSensor(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->IsSensor();
    }

    // SetFixtureDensity
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetFixtureDensity(void* fixturePointer, float density) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetDensity(density);
        fixture->GetBody()->ResetMassData();
    }

    // GetFixtureDensity
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureDensity(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetDensity();
    }

    // SetFixtureFriction
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetFixtureFriction(void* fixturePointer, float friction) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetFriction(friction);
    }

    // GetFixtureFriction
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureFriction(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFriction();
    }

    // SetFixtureRestitution
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetFixtureRestitution(void* fixturePointer, float restitution) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetRestitution(restitution);
    }

    // GetFixtureRestitution
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFixtureRestitution(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetRestitution();
    }

    // DeleteFixture
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API DeleteFixture(void* bodyPointer, void* fixturePointer) {
        b2Body* body = static_cast<b2Body*>(bodyPointer);
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        body->DestroyFixture(fixture);
    }
}
