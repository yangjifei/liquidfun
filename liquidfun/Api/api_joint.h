#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>

// Gear Joint
extern "C" {
    void* CreateGearJoint(void* world, void* joint1, void* joint2, float ratio, bool collideConnected) {
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

    float GetGearJointRatio(void* joint) {
        b2GearJoint* gearJoint = static_cast<b2GearJoint*>(joint);
        return gearJoint->GetRatio();
    }
}

// Wheel Joint
extern "C" {
    void* CreateWheelJoint(void* world, void* bodyA, void* bodyB,
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

    void SetWheelJointMotorSpeed(void* joint, float speed) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetMotorSpeed(speed);
    }

    void SetWheelJointMaxMotorTorque(void* joint, float torque) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetMaxMotorTorque(torque);
    }

    void EnableWheelJointMotor(void* joint, bool isEnabled) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->EnableMotor(isEnabled);
    }

    bool IsWheelJointMotorEnabled(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->IsMotorEnabled();
    }

    float GetWheelJointMotorSpeed(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetMotorSpeed();
    }

    float GetWheelJointMotorTorque(void* joint, float inverseDeltaTime) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetMotorTorque(inverseDeltaTime);
    }

    float GetWheelJointMaxMotorTorque(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetMaxMotorTorque();
    }

    void SetWheelJointSpringDampingRatio(void* joint, float ratio) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetSpringDampingRatio(ratio);
    }

    float GetWheelJointSpringDampingRatio(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetSpringDampingRatio();
    }

    void SetWheelJointSpringFrequency(void* joint, float frequency) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        wheelJoint->SetSpringFrequencyHz(frequency);
    }

    float GetWheelJointSpringFrequency(void* joint) {
        b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(joint);
        return wheelJoint->GetSpringFrequencyHz();
    }
}

// Weld Joint
extern "C" {
    void* CreateWeldJoint(void* world, void* bodyA, void* bodyB,
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

    void SetWeldJointDampingRatio(void* joint, float ratio) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        weldJoint->SetDampingRatio(ratio);
    }

    float GetWeldJointDampingRatio(void* joint) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        return weldJoint->GetDampingRatio();
    }

    void SetWeldJointFrequency(void* joint, float frequency) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        weldJoint->SetFrequency(frequency);
    }

    float GetWeldJointFrequency(void* joint) {
        b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(joint);
        return weldJoint->GetFrequency();
    }
}

// Friction Joint
extern "C" {
    void* CreateFrictionJoint(void* world, void* bodyA, void* bodyB,
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

    float GetFrictionJointMaxTorque(void* joint) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        return frictionJoint->GetMaxTorque();
    }

    void SetFrictionJointMaxTorque(void* joint, float torque) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        frictionJoint->SetMaxTorque(torque);
    }

    float GetFrictionJointMaxForce(void* joint) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        return frictionJoint->GetMaxForce();
    }

    void SetFrictionJointMaxForce(void* joint, float force) {
        b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(joint);
        frictionJoint->SetMaxForce(force);
    }
}

// Rope Joint
extern "C" {
    void* CreateRopeJoint(void* world, void* bodyA, void* bodyB,
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

    float GetRopeJointMaxLength(void* joint) {
        b2RopeJoint* ropeJoint = static_cast<b2RopeJoint*>(joint);
        return ropeJoint->GetMaxLength();
    }

    void SetRopeJointMaxLength(void* joint, float length) {
        b2RopeJoint* ropeJoint = static_cast<b2RopeJoint*>(joint);
        ropeJoint->SetMaxLength(length);
    }
}


// Mouse Joint
extern "C" {
    void* CreateMouseJoint(void* world, void* bodyA, void* bodyB,
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

    void SetMouseJointDampingRatio(void* joint, float ratio) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        mouseJoint->SetDampingRatio(ratio);
    }

    float GetMouseJointDampingRatio(void* joint) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        return mouseJoint->GetDampingRatio();
    }

    void SetMouseJointFrequency(void* joint, float frequency) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        mouseJoint->SetFrequency(frequency);
    }

    float GetMouseJointFrequency(void* joint) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        return mouseJoint->GetFrequency();
    }

    void SetMouseJointMaxForce(void* joint, float maxForce) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        mouseJoint->SetMaxForce(maxForce);
    }

    float GetMouseJointMaxForce(void* joint) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        return mouseJoint->GetMaxForce();
    }
}

// Generic Joint
extern "C" {
    void* CreateGenericJoint(void* world, void* bodyA, void* bodyB,
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
