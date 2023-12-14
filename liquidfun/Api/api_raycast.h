#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Testbed/Tests/RayCast.h"
#include <vector>
#define IntPtr void *

extern "C"
{
    class MyRaycastCallback : public b2RayCastCallback
    {
    public:
        MyRaycastCallback() : m_fixture(nullptr) {}

        float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) override
        {
            // Handle the ray-cast result here
            // The callback will be called for each fixture intersected by the ray
            // 'fixture' is the fixture that was hit
            // 'point' is the point in world coordinates where the ray hits the fixture
            // 'normal' is the normal vector at the hit point
            // 'fraction' is the fraction along the original ray the intersection point is located

            // For simplicity, this example just stores the first fixture hit by the ray
            m_fixture = fixture;
            m_point = point;
            m_normal = normal;
            m_fraction = fraction;

            // Returning 1.0f allows the ray-casting to continue and check for other fixtures
            return 1.0f;
        }

        // Accessors to retrieve the results
        b2Fixture *GetFixture() const { return m_fixture; }
        const b2Vec2 &GetPoint() const { return m_point; }
        const b2Vec2 &GetNormal() const { return m_normal; }
        float32 GetFraction() const { return m_fraction; }

    private:
        b2Fixture *m_fixture;
        b2Vec2 m_point;
        b2Vec2 m_normal;
        float32 m_fraction;
    };

    float *RaycastWorld(IntPtr worldPointer, float x1, float y1, float x2, float y2, int mode, bool shouldQueryParticleSystem)
    {
        b2World *world = reinterpret_cast<b2World *>(worldPointer);
        b2Vec2 p1(x1, y1);
        b2Vec2 p2(x2, y2);

        MyRaycastCallback callback;
        // Raycasting with termination callback
        if (mode == 0)
        {
            world->RayCast(&callback, p1, p2);
        }
        // Raycasting with fraction
        else if (mode == 1)
        {
            world->RayCast(&callback, p1, p2);
        }
        // Raycasting with filtering
        else if (mode == -1)
        {
            b2RayCastInput input;
            input.p1 = p1;
            input.p2 = p2;
            input.maxFraction = 1.0f;

            b2RayCastOutput output;
            for (b2Body *body = world->GetBodyList(); body; body = body->GetNext())
            {
                for (b2Fixture *fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
                {
                    if (shouldQueryParticleSystem || !fixture->IsLiquidFunParticleSystem())
                    {
                        if (fixture->RayCast(&output, input, 0))
                        {
                            callback.ReportFixture(fixture, output.p1, output.p2, output.normal, output.fraction);
                        }
                    }
                }
            }
        }

        // Collect results from the callback
        std::vector<float> results;
        results.push_back(callback.fixtureHits.size());  // Number of fixture hits
        results.push_back(callback.particleHits.size()); // Number of particle hits

        // Collect fixture hits
        for (const auto &hit : callback.fixtureHits)
        {
            results.push_back(static_cast<float>(hit.bodyIndex));
            results.push_back(static_cast<float>(hit.fixtureIndex));
            results.push_back(hit.posX);
            results.push_back(hit.posY);
            results.push_back(hit.normalX);
            results.push_back(hit.normalY);
            results.push_back(hit.fraction);
        }

        // Collect particle hits
        for (const auto &hit : callback.particleHits)
        {
            results.push_back(static_cast<float>(hit.systemIndex));
            results.push_back(static_cast<float>(hit.particleIndex));
            results.push_back(hit.posX);
            results.push_back(hit.posY);
            results.push_back(hit.normalX);
            results.push_back(hit.normalY);
            results.push_back(hit.fraction);
        }

        // Convert the results vector to a float array
        float *resultArray = new float[results.size()];
        std::copy(results.begin(), results.end(), resultArray);

        return resultArray;
    }
}