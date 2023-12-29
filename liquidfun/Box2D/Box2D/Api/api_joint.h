#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>

// Gear Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateGearJoint(void* world, void* joint1, void* joint2, float ratio, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Joint* b2Joint1Ptr = static_cast<b2Joint*>(joint1);
        b2Joint* b2Joint2Ptr = static_cast<b2Joint*>(joint2);

        b2GearJointDef jointDef;
        jointDef.bodyA = b2Joint1Ptr->GetBodyA();
        jointDef.bodyB = b2Joint2Ptr->GetBodyB();
        jointDef.joint1 = b2Joint1Ptr;
        jointDef.joint2 = b2Joint2Ptr;
        jointDef.ratio = ratio;
        jointDef.collideConnected = collideConnected;

        b2GearJoint* gearJoint = static_cast<b2GearJoint*>(b2WorldPtr->CreateJoint(&jointDef));
        return static_cast<void*>(gearJoint);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetGearJointRatio(void* joint) {
        b2GearJoint* gearJoint = static_cast<b2GearJoint*>(joint);
        return gearJoint->GetRatio();
    }
}

// Wheel Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateWheelJoint(void* world, void* bodyA, void* bodyB,
                            float anchorAX, float anchorAY,
                            float anchorBX, float anchorBY,
                            float axisX, float axisY, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2WheelJointDef jointDef;
        jointDef.Initialize(b2BodyAPtr, b2BodyBPtr, b2Vec2(anchorAX, anchorAY), b2Vec2(axisX, axisY));
        jointDef.localAnchorB.Set(anchorBX, anchorBY);
        jointDef.collideConnected = collideConnected;

        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(b2WorldPtr->CreateJoint(&jointDef));
        return static_cast<void*>(wheelJoint);
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetWheelJointMotorSpeed(void* joint, float speed) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetMotorSpeed(speed);
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetWheelJointMaxMotorTorque(void* joint, float torque) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetMaxMotorTorque(torque);
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API EnableWheelJointMotor(void* joint, bool isEnabled) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->EnableMotor(isEnabled);
    }

    bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API IsWheelJointMotorEnabled(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->IsMotorEnabled();
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWheelJointMotorSpeed(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetMotorSpeed();
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWheelJointMotorTorque(void* joint, float inverseDeltaTime) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetMotorTorque(inverseDeltaTime);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWheelJointMaxMotorTorque(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetMaxMotorTorque();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetWheelJointSpringDampingRatio(void* joint, float ratio) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetSpringDampingRatio(ratio);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWheelJointSpringDampingRatio(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetSpringDampingRatio();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetWheelJointSpringFrequency(void* joint, float frequency) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetSpringFrequencyHz(frequency);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWheelJointSpringFrequency(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetSpringFrequencyHz();
    }
}

// Weld Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateWeldJoint(void* world, void* bodyA, void* bodyB,
                          float anchorAX, float anchorAY,
                          float anchorBX, float anchorBY, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2WeldJointDef jointDef;
        jointDef.Initialize(b2BodyAPtr, b2BodyBPtr, b2Vec2(anchorAX, anchorAY));
        jointDef.localAnchorB.Set(anchorBX, anchorBY);
        jointDef.collideConnected = collideConnected;

        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(b2WorldPtr->CreateJoint(&jointDef));
        return static_cast<void*>(weldJoint);
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetWeldJointDampingRatio(void* joint, float ratio) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        weldJoint->SetDampingRatio(ratio);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWeldJointDampingRatio(void* joint) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        return weldJoint->GetDampingRatio();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetWeldJointFrequency(void* joint, float frequency) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        weldJoint->SetFrequency(frequency);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetWeldJointFrequency(void* joint) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        return weldJoint->GetFrequency();
    }
}

// Friction Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateFrictionJoint(void* world, void* bodyA, void* bodyB,
                              float anchorAX, float anchorAY,
                              float anchorBX, float anchorBY, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2FrictionJointDef jointDef;
        jointDef.Initialize(b2BodyAPtr, b2BodyBPtr, b2Vec2(anchorAX, anchorAY));
        jointDef.localAnchorB.Set(anchorBX, anchorBY);
        jointDef.collideConnected = collideConnected;

        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(b2WorldPtr->CreateJoint(&jointDef));
        return static_cast<void*>(frictionJoint);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFrictionJointMaxTorque(void* joint) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        return frictionJoint->GetMaxTorque();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetFrictionJointMaxTorque(void* joint, float torque) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        frictionJoint->SetMaxTorque(torque);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetFrictionJointMaxForce(void* joint) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        return frictionJoint->GetMaxForce();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetFrictionJointMaxForce(void* joint, float force) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        frictionJoint->SetMaxForce(force);
    }
}

// Rope Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateRopeJoint(void* world, void* bodyA, void* bodyB,
                          float anchorAX, float anchorAY,
                          float anchorBX, float anchorBY, float maxLength, bool collideConnect) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2RopeJointDef jointDef;
        jointDef.bodyA = b2BodyAPtr;
        jointDef.bodyB = b2BodyBPtr;
        jointDef.localAnchorA.Set(anchorAX, anchorAY);
        jointDef.localAnchorB.Set(anchorBX, anchorBY);
        jointDef.maxLength = maxLength;
        jointDef.collideConnected = collideConnect;

        b2RopeJoint* ropeJoint = static_cast<b2RopeJoint*>(b2WorldPtr->CreateJoint(&jointDef));
        return static_cast<void*>(ropeJoint);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRopeJointMaxLength(void* joint) {
        b2RopeJoint* ropeJoint = static_cast<b2RopeJoint*>(joint);
        return ropeJoint->GetMaxLength();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetRopeJointMaxLength(void* joint, float length) {
        b2RopeJoint* ropeJoint = static_cast<b2RopeJoint*>(joint);
        ropeJoint->SetMaxLength(length);
    }
}


// Mouse Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateMouseJoint(void* world, void* bodyA, void* bodyB,
                           float targetX, float targetY, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2MouseJointDef jointDef;
        jointDef.bodyA = b2BodyAPtr;
        jointDef.bodyB = b2BodyBPtr;
        jointDef.target.Set(targetX, targetY);
        jointDef.collideConnected = collideConnected;

        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(b2WorldPtr->CreateJoint(&jointDef));
        return static_cast<void*>(mouseJoint);
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseJointDampingRatio(void* joint, float ratio) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        mouseJoint->SetDampingRatio(ratio);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetMouseJointDampingRatio(void* joint) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        return mouseJoint->GetDampingRatio();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseJointFrequency(void* joint, float frequency) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        mouseJoint->SetFrequency(frequency);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetMouseJointFrequency(void* joint) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        return mouseJoint->GetFrequency();
    }

    void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseJointMaxForce(void* joint, float maxForce) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        mouseJoint->SetMaxForce(maxForce);
    }

    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetMouseJointMaxForce(void* joint) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        return mouseJoint->GetMaxForce();
    }
}

// Generic Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateGenericJoint(void* world, void* bodyA, void* bodyB,
                             float anchorAX, float anchorAY,
                             float anchorBX, float anchorBY,
                             float axisX, float axisY, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2RevoluteJointDef revoluteDef;
        revoluteDef.bodyA = b2BodyAPtr;
        revoluteDef.bodyB = b2BodyBPtr;
        revoluteDef.localAnchorA.Set(anchorAX, anchorAY);
        revoluteDef.localAnchorB.Set(anchorBX, anchorBY);
        revoluteDef.collideConnected = collideConnected;

        b2RevoluteJoint* revoluteJoint = static_cast<b2RevoluteJoint*>(b2WorldPtr->CreateJoint(&revoluteDef));
        return static_cast<void*>(revoluteJoint);
    }
}
