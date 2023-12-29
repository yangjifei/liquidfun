#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "api.h"
#include "../Unity/IUnityInterface.h"

// 光线投射结果的结构体
struct RaycastResult
{
    int bodyIndex;
    int fixtureIndex;
    float posX;
    float posY;
    float normalX;
    float normalY;
    float fraction;
};

// 创建光线投射回调
class RaycastCallback : public b2RayCastCallback
{
public:
    b2GrowableBuffer<RaycastResult> results;
    bool shouldQueryParticleSystem = false;
    int fixtureCount;
    int particleCount;
    RaycastCallback(b2GrowableBuffer<RaycastResult> results, bool shouldQueryParticleSystem = false)
        : results(results), shouldQueryParticleSystem(shouldQueryParticleSystem) {}

    float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) override
    {
        fixtureCount++;
        RaycastResult* result = &(results.Append());
        result->bodyIndex = reinterpret_cast<int>(fixture->GetBody()->GetUserData());
        result->fixtureIndex = reinterpret_cast<int>(fixture->GetUserData());
        result->posX = point.x;
        result->posY = point.y;
        result->normalX = normal.x;
        result->normalY = normal.y;
        result->fraction = fraction;
        return 1.0f; // 继续检查更多的fixture
    }

    float32 ReportParticle(const b2ParticleSystem* particleSystem, int32 index, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override {
        particleCount++;
        RaycastResult* result = &(results.Append());
        result->bodyIndex = reinterpret_cast<int>(particleSystem->GetUserDataBuffer()[index]);
        result->fixtureIndex = -1;  // 在粒子与fixture的碰撞中，fixtureIndex为-1
        result->posX = point.x;
        result->posY = point.y;
        result->normalX = normal.x;
        result->normalY = normal.y;
        result->fraction = fraction;
        return 1.0f;  // 继续检查更多的粒子
    }

    bool ShouldQueryParticleSystem(const b2ParticleSystem *particleSystem) override
    {
        return shouldQueryParticleSystem;
    }
};

// C++函数，用于执行液体物理引擎中的光线投射
extern "C" UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API RaycastWorld(b2World *world, float x1, float y1, float x2, float y2, int mode, bool shouldQueryParticleSystem)
{
    // 设置光线投射的参数
    b2Vec2 p1(x1, y1);
    b2Vec2 p2(x2, y2);

    // 初始化光线投射结果
    b2GrowableBuffer<RaycastResult> results(world->m_blockAllocator);

    // 创建光线投射回调实例
    RaycastCallback callback(results);

    // 执行光线投射
    world->RayCast(&callback, p1, p2);

    auto r = GetFloatBuffer(2+7*(results.GetCount()));
    r[0]=callback.fixtureCount;
    r[1]=callback.particleCount;
    memcpy(r+2, results.Data(), 7*results.GetCount()*sizeof(float));

    return r;
}
