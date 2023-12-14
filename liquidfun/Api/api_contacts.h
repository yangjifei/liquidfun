#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include <vector>
// 定义三个结构体来接收接触信息
struct ContactFixFix {
    int BodyAIndex;
    int BodyBIndex;
    int FixtureAIndex;
    int FixtureBIndex;
    b2Vec2 ManifoldPoint1;
    b2Vec2 ManifoldPoint2;
    b2Vec2 Normal;
    bool IsTouching;
};

struct ContactPartFix {
    int ParticleSystemIndex;
    int ParticleIndex;
    int BodyIndex;
    int FixtureIndex;
    b2Vec2 Normal;
};

struct ContactPartPart {
    int ParticleSystemIndex;
    int ParticleAIndex;
    int ParticleBIndex;
};
class MyContactListener : public b2ContactListener {
public:
    std::vector<float> data;
    std::vector<ContactFixFix> fixFixContacts;
    std::vector<ContactPartFix> partFixContacts;
    std::vector<ContactPartPart> partPartContacts;

    void BeginContact(b2Contact* contact) override {
        // 获取碰撞的两个物体
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        // 判断碰撞的类型
        bool isFixtureAFixture = fixtureA->GetType() == b2Shape::e_polygon;
        bool isFixtureBFixture = fixtureB->GetType() == b2Shape::e_polygon;

        if (isFixtureAFixture && isFixtureBFixture) {
            // 固定物体与固定物体的碰撞
            ContactFixFix contactInfo;
            contactInfo.BodyAIndex = fixtureA->GetBody()->GetUserData();
            contactInfo.BodyBIndex = fixtureB->GetBody()->GetUserData();
            contactInfo.FixtureAIndex = fixtureA->GetUserData();
            contactInfo.FixtureBIndex = fixtureB->GetUserData();
            contactInfo.IsTouching = contact->IsTouching();

            b2WorldManifold worldManifold;
            contact->GetWorldManifold(&worldManifold);
            contactInfo.ManifoldPoint1 = worldManifold.points[0];
            contactInfo.ManifoldPoint2 = worldManifold.points[1];
            contactInfo.Normal = worldManifold.normal;

            fixFixContacts.push_back(contactInfo);
            
            
            
        } else if (isFixtureAFixture || isFixtureBFixture) {
            // 固定物体与粒子的碰撞
            ContactPartFix contactInfo;
            // 假设你有一个方法来获取粒子系统索引
            contactInfo.ParticleSystemIndex = GetParticleSystemIndex(fixtureA, fixtureB);
            // 假设你有一个方法来获取粒子索引
            contactInfo.ParticleIndex = GetParticleIndex(fixtureA, fixtureB);
            // 假设你有一个方法来获取物体索引
            contactInfo.BodyIndex = GetBodyIndex(fixtureA, fixtureB);
            // 假设你有一个方法来获取固定装置索引
            contactInfo.FixtureIndex = GetFixtureIndex(fixtureA, fixtureB);
            // 假设你有一个方法来获取法线方向
            contactInfo.Normal = GetNormal(fixtureA, fixtureB);

            partFixContacts.push_back(contactInfo);
        } else {
            // 粒子与粒子的碰撞
            ContactPartPart contactInfo;
            // 假设你有一个方法来获取粒子系统索引
            contactInfo.ParticleSystemIndex = GetParticleSystemIndex(fixtureA, fixtureB);
            // 假设你有一个方法来获取粒子A索引
            contactInfo.ParticleAIndex = GetParticleAIndex(fixtureA, fixtureB);
            // 假设你有一个方法来获取粒子B索引
            contactInfo.ParticleBIndex = GetParticleBIndex(fixtureA, fixtureB);

            partPartContacts.push_back(contactInfo);
        }
    }

    void EndContact(b2Contact* contact) override {
        // 在这里你可以处理碰撞结束的情况
        // ...
    }
};


extern "C" {

// 创建并设置碰撞监听器
void* SetContactListener(b2World* world) {
    MyContactListener* listener = new MyContactListener();
    world->SetContactListener(listener);
    return listener;
}

// 更新碰撞监听器并返回碰撞信息
void* UpdateContactListener(MyContactListener* listener) {
    // 清空数据
    listener->data.clear();

    // 添加碰撞信息的数量
    listener->data.push_back(listener->fixFixContacts.size());
    listener->data.push_back(listener->partFixContacts.size());
    listener->data.push_back(listener->partPartContacts.size());

    // 添加固定物体与固定物体的碰撞信息
    for (const ContactFixFix& contact : listener->fixFixContacts) {
        listener->data.push_back(contact.BodyAIndex);
        listener->data.push_back(contact.BodyBIndex);
        listener->data.push_back(contact.FixtureAIndex);
        listener->data.push_back(contact.FixtureBIndex);
        listener->data.push_back(contact.ManifoldPoint1.x);
        listener->data.push_back(contact.ManifoldPoint1.y);
        listener->data.push_back(contact.ManifoldPoint2.x);
        listener->data.push_back(contact.ManifoldPoint2.y);
        listener->data.push_back(contact.Normal.x);
        listener->data.push_back(contact.Normal.y);
        listener->data.push_back(contact.IsTouching ? 1.0f : 0.0f);
    }

    // 添加固定物体与粒子的碰撞信息
    for (const ContactPartFix& contact : listener->partFixContacts) {
        listener->data.push_back(contact.ParticleSystemIndex);
        listener->data.push_back(contact.ParticleIndex);
        listener->data.push_back(contact.BodyIndex);
        listener->data.push_back(contact.FixtureIndex);
        listener->data.push_back(contact.Normal.x);
        listener->data.push_back(contact.Normal.y);
    }

    // 添加粒子与粒子的碰撞信息
    for (const ContactPartPart& contact : listener->partPartContacts) {
        listener->data.push_back(contact.ParticleSystemIndex);
        listener->data.push_back(contact.ParticleAIndex);
        listener->data.push_back(contact.ParticleBIndex);
    }

    // 返回碰撞信息的指针
    return listener->data.data();
}

} // extern "C"
