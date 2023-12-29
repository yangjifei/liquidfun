#include <Box2D/Box2D.h>
#include <Box2D/Particle/b2ParticleSystem.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <vector>
#include "api.h"

extern "C" {

    // CreateBody
    UNITY_INTERFACE_EXPORT b2Body* UNITY_INTERFACE_API CreateBody(b2World* world, int bodyType, float xPosition, float yPosition,
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
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ApplyForceToCentreOfBody(b2Body* body, float impulseX, float impulseY) {
        body->ApplyForceToCenter(b2Vec2(impulseX, impulseY), true);
    }

    // GetBodyInfo
    b2Vec3 UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyInfo(b2Body* body) {
        b2Transform transform = body->GetTransform();
        return b2Vec3(transform.p.x, transform.p.y, transform.q.GetAngle());
    }

    // GetAllBodyInfo
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API GetAllBodyInfo(b2Body** bodyArray, int numBodies) {
        auto result = GetFloatBuffer(numBodies * 3);
        for (int i = 0; i < numBodies; ++i) {
            b2Transform transform = bodyArray[i]->GetTransform();
            result[3 * i + 0] = transform.p.x;
            result[3 * i + 1] = transform.p.y;
            result[3 * i + 2] = transform.q.GetAngle();
        }
        return result;
    }

    // SetBodyAwake
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyAwake(b2Body* body, bool isAwake) {
        body->SetAwake(isAwake);
    }

    // GetBodyAwake
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyAwake(b2Body* body) {
        return body->IsAwake();
    }

    // SetBodyActive
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyActive(b2Body* body, bool isActive) {
        body->SetActive(isActive);
    }

    // GetBodyActive
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyActive(b2Body* body) {
        return body->IsActive();
    }

    // GetBodyFixturesCount
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyFixturesCount(b2Body* body, int& count) {
        count = body->GetFixtureList() ? 1 : 0;
    }

    // SetBodyType
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyType(b2Body* body, int type) {
        body->SetType(static_cast<b2BodyType>(type));
    }

    // SetBodyPosition
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyPosition(b2Body* body, float x, float y) {
        body->SetTransform(b2Vec2(x, y), body->GetAngle());
    }

    // SetBodyRotation
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyRotation(b2Body* body, float angle) {
        body->SetTransform(body->GetPosition(), angle);
    }

    // SetBodyLinearVelocity
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyLinearVelocity(b2Body* body, float x, float y) {
        body->SetLinearVelocity(b2Vec2(x, y));
    }

    // GetBodyLinearVelocity
    b2Vec2 UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyLinearVelocity(b2Body* body) {
        return body->GetLinearVelocity();
    }

    // SetBodyAngularVelocity
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyAngularVelocity(b2Body* body, float omega) {
        body->SetAngularVelocity(omega);
    }

    // GetBodyAngularVelocity
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyAngularVelocity(b2Body* body) {
        return body->GetAngularVelocity();
    }

    // GetBodyUserData
    int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyUserData(b2Body* body) {
        return reinterpret_cast<int>(body->GetUserData());
    }

    // GetBodyContactsCount
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyContactsCount(b2Body* body, int& count) {
        count = 0;
        b2ContactEdge* contactEdge = body->GetContactList();
        while (contactEdge) {
            count++;
            contactEdge = contactEdge->next;
        }
    }

    // GetBodyContacts
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyContacts(b2Body* body) {
        int count =0;
        GetBodyContactsCount(body,count);
        int* contacts = GetIntBuffer(count+1);
        contacts[0]=count;
        int index = 1;
        b2ContactEdge* contactEdge = body->GetContactList();
        while (contactEdge) {
            contacts[index++] = reinterpret_cast<int>(contactEdge->other->GetUserData());
            contactEdge = contactEdge->next;
        }
    }

    // SetBodyLinearDamping
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyLinearDamping(b2Body* body, float linearDamping) {
        body->SetLinearDamping(linearDamping);
    }

    // GetBodyLinearDamping
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyLinearDamping(b2Body* body) {
        return body->GetLinearDamping();
    }

    // SetBodyAngularDamping
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyAngularDamping(b2Body* body, float angularDamping) {
        body->SetAngularDamping(angularDamping);
    }

    // GetBodyAngularDamping
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyAngularDamping(b2Body* body) {
        return body->GetAngularDamping();
    }

    // SetBodyGravityScale
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyGravityScale(b2Body* body, float gravityScale) {
        body->SetGravityScale(gravityScale);
    }

    // GetBodyGravityScale
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyGravityScale(b2Body* body) {
        return body->GetGravityScale();
    }

    // SetBodyIsBullet
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyIsBullet(b2Body* body, bool isBullet) {
        body->SetBullet(isBullet);
    }

    // GetBodyIsBullet
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyIsBullet(b2Body* body) {
        return body->IsBullet();
    }

    // SetBodyFixedRotation
    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetBodyFixedRotation(b2Body* body, bool fixedRotation) {
        body->SetFixedRotation(fixedRotation);
    }

    // GetBodyFixedRotation
    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetBodyFixedRotation(b2Body* body) {
        return body->IsFixedRotation();
    }
}
