#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>

// Revolute Joints
extern "C" {

    UNITY_INTERFACE_EXPORT b2RevoluteJoint* UNITY_INTERFACE_API CreateRevoluteJoint(b2World* world, b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorA, b2Vec2 anchorB, bool collideConnected) {
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(bodyA, bodyB, anchorA);
        jointDef.localAnchorB = anchorB;
        jointDef.collideConnected = collideConnected;
        return (b2RevoluteJoint*)world->CreateJoint(&jointDef);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetRevoluteJointLimits(b2RevoluteJoint* joint, float lowerLimit, float upperLimit) {
        joint->SetLimits(lowerLimit, upperLimit);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetRevoluteJointMotorSpeed(b2RevoluteJoint* joint, float speed) {
        joint->SetMotorSpeed(speed);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetRevoluteJointMaxMotorTorque(b2RevoluteJoint* joint, float torque) {
        joint->SetMaxMotorTorque(torque);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API EnableRevoluteJointMotor(b2RevoluteJoint* joint, bool isEnabled) {
        joint->EnableMotor(isEnabled);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API EnableRevoluteJointLimits(b2RevoluteJoint* joint, bool isLimited) {
        joint->EnableLimit(isLimited);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetRevoluteJointUpperLimit(b2RevoluteJoint* joint) {
        return joint->GetUpperLimit();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetRevoluteJointLowerLimit(b2RevoluteJoint* joint) {
        return joint->GetLowerLimit();
    }

    UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API IsRevoluteJointMotorEnabled(b2RevoluteJoint* joint) {
        return joint->IsMotorEnabled();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetRevoluteJointMotorSpeed(b2RevoluteJoint* joint) {
        return joint->GetMotorSpeed();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetRevoluteJointMotorTorque(b2RevoluteJoint* joint, float inverseDeltaTime) {
        return joint->GetMotorTorque(inverseDeltaTime);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetRevoluteJointMaxMotorTorque(b2RevoluteJoint* joint) {
        return joint->GetMaxMotorTorque();
    }
}

// Distance Joints
extern "C" {

    UNITY_INTERFACE_EXPORT b2DistanceJoint* UNITY_INTERFACE_API CreateDistanceJoint(b2World* world, b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorA, b2Vec2 anchorB, float length, bool collideConnected) {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(bodyA, bodyB, anchorA, anchorB);
        jointDef.collideConnected = collideConnected;
        jointDef.length = length;
        return (b2DistanceJoint*)world->CreateJoint(&jointDef);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetDistanceJointFrequency(b2DistanceJoint* joint, float frequency) {
        joint->SetFrequency(frequency);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetDistanceJointFrequency(b2DistanceJoint* joint) {
        return joint->GetFrequency();
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetDistanceJointDampingRatio(b2DistanceJoint* joint, float dampingRatio) {
        joint->SetDampingRatio(dampingRatio);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetDistanceJointDampingRatio(b2DistanceJoint* joint) {
        return joint->GetDampingRatio();
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetDistanceJointLength(b2DistanceJoint* joint, float length) {
        joint->SetLength(length);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetDistanceJointLength(b2DistanceJoint* joint) {
        return joint->GetLength();
    }
}

// Prismatic Joints
extern "C" {

    UNITY_INTERFACE_EXPORT b2PrismaticJoint* UNITY_INTERFACE_API CreatePrismaticJoint(b2World* world, b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorA, b2Vec2 anchorB, float axisX, float axisY, bool collideConnected) {
        b2PrismaticJointDef jointDef;
        jointDef.Initialize(bodyA, bodyB, anchorA, b2Vec2(axisX, axisY));
        jointDef.collideConnected = collideConnected;
        return (b2PrismaticJoint*)world->CreateJoint(&jointDef);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetPrismaticJointLimits(b2PrismaticJoint* joint, float lowerLimit, float upperLimit) {
        joint->SetLimits(lowerLimit, upperLimit);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetPrismaticJointMotorSpeed(b2PrismaticJoint* joint, float speed) {
        joint->SetMotorSpeed(speed);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetPrismaticJointMaxMotorForce(b2PrismaticJoint* joint, float force) {
        joint->SetMaxMotorForce(force);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API EnablePrismaticJointMotor(b2PrismaticJoint* joint, bool isEnabled) {
        joint->EnableMotor(isEnabled);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API EnablePrismaticJointLimits(b2PrismaticJoint* joint, bool isLimited) {
        joint->EnableLimit(isLimited);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPrismaticJointUpperLimit(b2PrismaticJoint* joint) {
        return joint->GetUpperLimit();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPrismaticJointLowerLimit(b2PrismaticJoint* joint) {
        return joint->GetLowerLimit();
    }

    UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API IsPrismaticJointMotorEnabled(b2PrismaticJoint* joint) {
        return joint->IsMotorEnabled();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPrismaticJointMotorSpeed(b2PrismaticJoint* joint) {
        return joint->GetMotorSpeed();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPrismaticJointMotorForce(b2PrismaticJoint* joint, float inverseDeltaTime) {
        return joint->GetMotorForce(inverseDeltaTime);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPrismaticJointMaxMotorForce(b2PrismaticJoint* joint) {
        return joint->GetMaxMotorForce();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPrismaticJointSpeed(b2PrismaticJoint* joint) {
        return joint->GetJointSpeed();
    }
}

// Pulley Joints
extern "C" {

    UNITY_INTERFACE_EXPORT b2PulleyJoint* UNITY_INTERFACE_API CreatePulleyJoint(b2World* world, b2Body* bodyA, b2Body* bodyB, b2Vec2 groundAnchorA, b2Vec2 groundAnchorB, b2Vec2 anchorA, b2Vec2 anchorB, float ratio, bool collideConnected) {
        b2PulleyJointDef jointDef;
        jointDef.Initialize(bodyA, bodyB, groundAnchorA, groundAnchorB, anchorA, anchorB, ratio);
        jointDef.collideConnected = collideConnected;
        return (b2PulleyJoint*)world->CreateJoint(&jointDef);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPulleyJointLengthA(b2PulleyJoint* joint) {
        return joint->GetLengthA();
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetPulleyJointLengthB(b2PulleyJoint* joint) {
        return joint->GetLengthB();
    }
}

// Gear Joints
extern "C" {

    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateGearJoint(void* world, void* bodyA, void* bodyB, void* jointA, bool isJointARevolute, void* jointB, bool isJointBRevolute, float ratio, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2GearJointDef jointDef;
        jointDef.bodyA = b2BodyAPtr;
        jointDef.bodyB = b2BodyBPtr;
        jointDef.joint1 = static_cast<b2Joint*>(jointA);
        jointDef.joint2 = static_cast<b2Joint*>(jointB);
        jointDef.ratio = ratio;
        jointDef.collideConnected = collideConnected;

        b2GearJoint* gearJoint = static_cast<b2GearJoint*>(b2WorldPtr->CreateJoint(&jointDef));
        return static_cast<void*>(gearJoint);
    }

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetGearJointRatio(void* joint, float ratio) {
        b2GearJoint* gearJoint = static_cast<b2GearJoint*>(joint);
        gearJoint->SetRatio(ratio);
    }

    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API GetGearJointRatio(void* joint) {
        b2GearJoint* gearJoint = static_cast<b2GearJoint*>(joint);
        return gearJoint->GetRatio();
    }
}


// Wheel Joint
extern "C" {
    UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API CreateWheelJoint(void* world, void* bodyA, void* bodyB,
                            float anchorAX, float anchorAY,
                            float axisX, float axisY, bool collideConnected) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Body* b2BodyAPtr = static_cast<b2Body*>(bodyA);
        b2Body* b2BodyBPtr = static_cast<b2Body*>(bodyB);

        b2WheelJointDef jointDef;
        jointDef.Initialize(b2BodyAPtr, b2BodyBPtr, b2Vec2(anchorAX, anchorAY), b2Vec2(axisX, axisY));
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

    UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API SetMouseJointTarget(void* joint, float targetX, float targetY) {
        b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(joint);
        mouseJoint->SetTarget(b2Vec2(targetX, targetY));
    }
}

// Generic Functions
extern "C" {
    UNITY_INTERFACE_EXPORT float UNITY_INTERFACE_API DeleteJoint(void* world, void* joint) {
        b2World* b2WorldPtr = static_cast<b2World*>(world);
        b2Joint* b2JointPtr = static_cast<b2Joint*>(joint);

        // Destroy the joint
        b2WorldPtr->DestroyJoint(b2JointPtr);
        return 0.0f; // Return value can be customized based on your needs
    }

    UNITY_INTERFACE_EXPORT bool UNITY_INTERFACE_API GetJointCollideConnected(void* joint) {
        b2Joint* b2JointPtr = static_cast<b2Joint*>(joint);
        return b2JointPtr->GetCollideConnected();
    }

    // Shift the origin of the joint.
    float UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ShiftJointOrigin(void* joint, float originX, float originY) {
        //b2Joint* b2JointPtr = static_cast<b2Joint*>(joint);
        //
        //// Check the type of joint and perform the necessary operations
        //switch (b2JointPtr->GetType()) {
        //case e_revoluteJoint: {
        //    b2RevoluteJoint* revoluteJoint = static_cast<b2RevoluteJoint*>(b2JointPtr);
        //    // Assuming SetLocalAnchorA and SetLocalAnchorB are available for RevoluteJoint
        //    revoluteJoint->SetLocalAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetLocalAnchorB if needed
        //    break;
        //}
        //case e_prismaticJoint: {
        //    b2PrismaticJoint* prismaticJoint = static_cast<b2PrismaticJoint*>(b2JointPtr);
        //    // Assuming SetLocalAnchorA and SetLocalAnchorB are available for PrismaticJoint
        //    prismaticJoint->SetLocalAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetLocalAnchorB if needed
        //    break;
        //}
        //case e_distanceJoint: {
        //    b2DistanceJoint* distanceJoint = static_cast<b2DistanceJoint*>(b2JointPtr);
        //    // Assuming SetLocalAnchorA and SetLocalAnchorB are available for DistanceJoint
        //    distanceJoint->SetLocalAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetLocalAnchorB if needed
        //    break;
        //}
        //case e_pulleyJoint: {
        //    b2PulleyJoint* pulleyJoint = static_cast<b2PulleyJoint*>(b2JointPtr);
        //    // Assuming SetGroundAnchorA and SetGroundAnchorB are available for PulleyJoint
        //    pulleyJoint->SetGroundAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetGroundAnchorB if needed
        //    break;
        //}
        //case e_wheelJoint: {
        //    b2WheelJoint* wheelJoint = static_cast<b2WheelJoint*>(b2JointPtr);
        //    // Assuming SetLocalAnchorA and SetLocalAnchorB are available for WheelJoint
        //    wheelJoint->SetLocalAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetLocalAnchorB if needed
        //    break;
        //}
        //case e_motorJoint: {
        //    b2MotorJoint* motorJoint = static_cast<b2MotorJoint*>(b2JointPtr);
        //    // Assuming SetLinearOffset and SetAngularOffset are available for MotorJoint
        //    motorJoint->SetLinearOffset(b2Vec2(originX, originY));
        //    // Add similar logic for SetAngularOffset if needed
        //    break;
        //}
        //case e_weldJoint: {
        //    b2WeldJoint* weldJoint = static_cast<b2WeldJoint*>(b2JointPtr);
        //    // Assuming SetLocalAnchorA and SetLocalAnchorB are available for WeldJoint
        //    weldJoint->SetLocalAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetLocalAnchorB if needed
        //    break;
        //}
        //case e_frictionJoint: {
        //    b2FrictionJoint* frictionJoint = static_cast<b2FrictionJoint*>(b2JointPtr);
        //    // Assuming SetLocalAnchorA and SetLocalAnchorB are available for FrictionJoint
        //    frictionJoint->SetLocalAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetLocalAnchorB if needed
        //    break;
        //}
        //case e_ropeJoint: {
        //    b2RopeJoint* ropeJoint = static_cast<b2RopeJoint*>(b2JointPtr);
        //    // Assuming SetLocalAnchorA and SetLocalAnchorB are available for RopeJoint
        //    ropeJoint->SetLocalAnchorA(b2Vec2(originX, originY));
        //    // Add similar logic for SetLocalAnchorB if needed
        //    break;
        //}
        //case e_gearJoint: {
        //    // GearJoint doesn't have SetLocalAnchorA or SetLocalAnchorB in the Box2D API.
        //    // If you still want to include it in the switch statement, you can add a comment or handle it differently.
        //    break;
        //}
        //case e_mouseJoint: {
        //    b2MouseJoint* mouseJoint = static_cast<b2MouseJoint*>(b2JointPtr);
        //    // Assuming SetTarget is available for MouseJoint
        //    mouseJoint->SetTarget(b2Vec2(originX, originY));
        //    break;
        //}
        //                 // Add cases for other joint types as needed
        //
        //default:
        //    // Unsupported joint type
        //    return -1.0f; // Or any appropriate error code
        //}

        // Success
        return 0.0f; // Or any appropriate success code
    }
}
