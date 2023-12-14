#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>

extern "C" {

    // AddFixture
    void* AddFixture(void* bodyPointer, int shapeType, void* shapePointer, float density, float friction, float restitution, bool isSensor, int userData) {
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
    float* GetFixtureInfo(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        b2Vec2 position = fixture->GetBody()->GetPosition(); // Use GetPosition() for the body's origin

        float* info = new float[3];
        info[0] = position.x;
        info[1] = position.y;
        info[2] = fixture->GetBody()->GetAngle();

        return info;
    }

    // GetFixtureUserData
    int GetFixtureUserData(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return reinterpret_cast<int>(fixture->GetUserData());
    }

    // SetFixtureFilterData
    void SetFixtureFilterData(void* fixturePointer, int16_t groupIndex, uint16_t categoryBits, uint16_t maskBits) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        b2Filter filter = fixture->GetFilterData();
        filter.groupIndex = groupIndex;
        filter.categoryBits = categoryBits;
        filter.maskBits = maskBits;
        fixture->SetFilterData(filter);
    }

    // GetFixtureGroupIndex
    uint16_t GetFixtureGroupIndex(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFilterData().groupIndex;
    }

    // GetFixtureCategoryBits
    uint16_t GetFixtureCategoryBits(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFilterData().categoryBits;
    }

    // GetFixtureMaskBits
    uint16_t GetFixtureMaskBits(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFilterData().maskBits;
    }

    // TestPoint
    bool TestPoint(void* fixturePointer, float x, float y) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        b2Vec2 point(x, y);
        return fixture->TestPoint(point);
    }

    // SetFixtureIsSensor
    void SetFixtureIsSensor(void* fixturePointer, bool flag) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetSensor(flag);
    }

    // GetFixtureIsSensor
    bool GetFixtureIsSensor(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->IsSensor();
    }

    // SetFixtureDensity
    void SetFixtureDensity(void* fixturePointer, float density) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetDensity(density);
        fixture->GetBody()->ResetMassData();
    }

    // GetFixtureDensity
    float GetFixtureDensity(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetDensity();
    }

    // SetFixtureFriction
    void SetFixtureFriction(void* fixturePointer, float friction) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetFriction(friction);
    }

    // GetFixtureFriction
    float GetFixtureFriction(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetFriction();
    }

    // SetFixtureRestitution
    void SetFixtureRestitution(void* fixturePointer, float restitution) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        fixture->SetRestitution(restitution);
    }

    // GetFixtureRestitution
    float GetFixtureRestitution(void* fixturePointer) {
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        return fixture->GetRestitution();
    }

    // DeleteFixture
    void DeleteFixture(void* bodyPointer, void* fixturePointer) {
        b2Body* body = static_cast<b2Body*>(bodyPointer);
        b2Fixture* fixture = static_cast<b2Fixture*>(fixturePointer);
        body->DestroyFixture(fixture);
    }
}
