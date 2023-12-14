#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>

extern "C" {

    // CreateBody
    b2Body* CreateBody(b2World* world, int bodyType, float xPosition, float yPosition,
                        float angleInRadians, float linearDamping, float angularDamping,
                        bool allowSleep, bool fixedRotation, bool bullet, float gravityScale, int userData) {
        b2BodyDef bodyDef;
        bodyDef.type = static_cast<b2BodyType>(bodyType);
        bodyDef.position.Set(xPosition, yPosition);
        bodyDef.angle = angleInRadians;
        bodyDef.linearDamping = linearDamping;
        bodyDef.angularDamping = angularDamping;
        bodyDef.allowSleep = allowSleep;
        bodyDef.fixedRotation = fixedRotation;
        bodyDef.bullet = bullet;
        bodyDef.gravityScale = gravityScale;
        bodyDef.userData = reinterpret_cast<void*>(userData);

        return world->CreateBody(&bodyDef);
    }

    // ApplyForceToCentreOfBody
    void ApplyForceToCentreOfBody(b2Body* body, float impulseX, float impulseY) {
        body->ApplyForceToCenter(b2Vec2(impulseX, impulseY), true);
    }

    // GetBodyInfo
    b2Vec3 GetBodyInfo(b2Body* body) {
        b2Transform transform = body->GetTransform();
        return b2Vec3(transform.p.x, transform.p.y, transform.q.GetAngle());
    }

    // GetAllBodyInfo
    b2Vec3* GetAllBodyInfo(b2Body** bodyArray, int numBodies) {
        b2Vec3* bodyInfoArray = new b2Vec3[numBodies];
        for (int i = 0; i < numBodies; ++i) {
            bodyInfoArray[i] = GetBodyInfo(bodyArray[i]);
        }
        return bodyInfoArray;
    }

    // SetBodyAwake
    void SetBodyAwake(b2Body* body, bool isAwake) {
        body->SetAwake(isAwake);
    }

    // GetBodyAwake
    bool GetBodyAwake(b2Body* body) {
        return body->IsAwake();
    }

    // SetBodyActive
    void SetBodyActive(b2Body* body, bool isActive) {
        body->SetActive(isActive);
    }

    // GetBodyActive
    bool GetBodyActive(b2Body* body) {
        return body->IsActive();
    }

    // GetBodyFixturesCount
    void GetBodyFixturesCount(b2Body* body, int& count) {
        count = body->GetFixtureList() ? 1 : 0;
    }

    // GetBodyFixturesList
    void GetBodyFixturesList(b2Body* body, b2Fixture**& fixturesList, int& count) {
        GetBodyFixturesCount(body, count);
        fixturesList = new b2Fixture*[count];
        fixturesList[0] = body->GetFixtureList();
    }

    // SetBodyType
    void SetBodyType(b2Body* body, int type) {
        body->SetType(static_cast<b2BodyType>(type));
    }

    // SetBodyPosition
    void SetBodyPosition(b2Body* body, float x, float y) {
        body->SetTransform(b2Vec2(x, y), body->GetAngle());
    }

    // SetBodyRotation
    void SetBodyRotation(b2Body* body, float angle) {
        body->SetTransform(body->GetPosition(), angle);
    }

    // SetBodyLinearVelocity
    void SetBodyLinearVelocity(b2Body* body, float x, float y) {
        body->SetLinearVelocity(b2Vec2(x, y));
    }

    // GetBodyLinearVelocity
    b2Vec2 GetBodyLinearVelocity(b2Body* body) {
        return body->GetLinearVelocity();
    }

    // SetBodyAngularVelocity
    void SetBodyAngularVelocity(b2Body* body, float omega) {
        body->SetAngularVelocity(omega);
    }

    // GetBodyAngularVelocity
    float GetBodyAngularVelocity(b2Body* body) {
        return body->GetAngularVelocity();
    }

    // GetBodyUserData
    int GetBodyUserData(b2Body* body) {
        return reinterpret_cast<int>(body->GetUserData());
    }

    // GetBodyContactsCount
    void GetBodyContactsCount(b2Body* body, int& count) {
        count = 0;
        b2ContactEdge* contactEdge = body->GetContactList();
        while (contactEdge) {
            count++;
            contactEdge = contactEdge->next;
        }
    }

    // GetBodyContacts
    void GetBodyContacts(b2Body* body, int*& contacts, int& count) {
        GetBodyContactsCount(body, count);
        contacts = new int[count];
        int index = 0;
        b2ContactEdge* contactEdge = body->GetContactList();
        while (contactEdge) {
            contacts[index++] = reinterpret_cast<int>(contactEdge->contact);
            contactEdge = contactEdge->next;
        }
    }

    // SetBodyLinearDamping
    void SetBodyLinearDamping(b2Body* body, float linearDamping) {
        body->SetLinearDamping(linearDamping);
    }

    // GetBodyLinearDamping
    float GetBodyLinearDamping(b2Body* body) {
        return body->GetLinearDamping();
    }

    // SetBodyAngularDamping
    void SetBodyAngularDamping(b2Body* body, float angularDamping) {
        body->SetAngularDamping(angularDamping);
    }

    // GetBodyAngularDamping
    float GetBodyAngularDamping(b2Body* body) {
        return body->GetAngularDamping();
    }

    // SetBodyGravityScale
    void SetBodyGravityScale(b2Body* body, float gravityScale) {
        body->SetGravityScale(gravityScale);
    }

    // GetBodyGravityScale
    float GetBodyGravityScale(b2Body* body) {
        return body->GetGravityScale();
    }

    // SetBodyIsBullet
    void SetBodyIsBullet(b2Body* body, bool isBullet) {
        body->SetBullet(isBullet);
    }

    // GetBodyIsBullet
    bool GetBodyIsBullet(b2Body* body) {
        return body->IsBullet();
    }

    // SetBodyFixedRotation
    void SetBodyFixedRotation(b2Body* body, bool fixedRotation) {
        body->SetFixedRotation(fixedRotation);
    }

    // GetBodyFixedRotation
    bool GetBodyFixedRotation(b2Body* body) {
        return body->IsFixedRotation();
    }
}
