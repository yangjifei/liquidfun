#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include <vector>
// 定义三个结构体来接收接触信息
struct ContactFixFix {
    int BodyAIndex;
    int BodyBIndex;
    int FixtureAIndex;
    int FixtureBIndex;
    float ManifoldPoint1_x;
    float ManifoldPoint1_y;
    float ManifoldPoint2_x;
    float ManifoldPoint2_y;
    float Normal_x;
    float Normal_y;
    bool IsTouching;
};

struct ContactPartFix {
    int ParticleSystemIndex;
    int ParticleIndex;
    int BodyIndex;
    int FixtureIndex;
    float Normal_x;
    float Normal_y;
};

struct ContactPartPart {
    int ParticleSystemIndex;
    int ParticleAIndex;
    int ParticleBIndex;
};
class MyContactListener : public b2ContactListener {
public:
	float* buffer;
    std::vector<ContactFixFix> fixFixContacts;
    std::vector<ContactPartFix> partFixContacts;
    std::vector<ContactPartPart> partPartContacts;

    // Constructor
    MyContactListener() : buffer(nullptr) {}

    #define ff 11
    #define pf 6
    #define pp 3
	size_t preSize = -1;
    // Function to create and return the buffer
    float* UpdateContactBuffer() {
		size_t size = 3 + ff * fixFixContacts.size() + pf * partFixContacts.size() + pp * partPartContacts.size();
        if (preSize==-1) {
            buffer = (float*)malloc(size);
			preSize = size;
        }
		if(size>preSize){
			buffer = (float*)realloc(buffer, size);
		}
		buffer[0] = fixFixContacts.size();
		buffer[1] = partFixContacts.size();
		buffer[2] = partPartContacts.size();
		memcpy(buffer + 3, fixFixContacts.data(), fixFixContacts.size() * ff * sizeof(float));
		memcpy(buffer + 3 + ff * fixFixContacts.size(), partFixContacts.data(), partFixContacts.size() * pf * sizeof(float));
		memcpy(buffer + 3 + ff * fixFixContacts.size() + pf * partFixContacts.size(), partPartContacts.data(), partPartContacts.size() * pp * sizeof(float));
        fixFixContacts.clear();
        partFixContacts.clear();
        partPartContacts.clear();
        return buffer;
    }

    // Function to clear the contact vectors and reset the buffer
    void ClearContacts() {
        fixFixContacts.clear();
        partFixContacts.clear();
        partPartContacts.clear();
        if (buffer) {
            free(buffer);
            buffer = nullptr;
        }
    }

    // Destructor to free the buffer if not freed already
    ~MyContactListener() {
        ClearContacts();
    }

    
	/// Called when two fixtures begin to touch.
	void BeginContact(b2Contact* contact) override {
		fixFixContacts.push_back(
		    ContactFixFix{reinterpret_cast<int>(contact->GetFixtureA()->GetBody()->GetUserData()),
		                  reinterpret_cast<int>(contact->GetFixtureB()->GetBody()->GetUserData()),
		                  reinterpret_cast<int>(contact->GetFixtureA()->GetUserData()),
		                  reinterpret_cast<int>(contact->GetFixtureB()->GetUserData()),
		                  contact->GetManifold()->localNormal.x,
		                  contact->GetManifold()->localNormal.y,
		                  contact->GetManifold()->localPoint.x,
		                  contact->GetManifold()->localPoint.y,
		                  contact->IsTouching()?1.0f:0.0f});
	}

	/// Called when two fixtures cease to touch.
	void EndContact(b2Contact* contact) override { B2_NOT_USED(contact); }

	/// Called when a fixture and particle start touching if the
	/// b2_fixtureContactFilterParticle flag is set on the particle.
	void BeginContact(b2ParticleSystem* particleSystem,
							  b2ParticleBodyContact* particleBodyContact) override
	{
		partFixContacts.push_back(
		    ContactPartFix{	particleSystem->index,
							particleBodyContact->index,
		                    reinterpret_cast<int>(particleBodyContact->body->GetUserData()),
		                    reinterpret_cast<int>(particleBodyContact->fixture->GetUserData()),
		                    particleBodyContact->normal.x,
		                    particleBodyContact->normal.y});
	}

	/// Called when a fixture and particle stop touching if the
	/// b2_fixtureContactFilterParticle flag is set on the particle.
	void EndContact(b2Fixture* fixture,
							b2ParticleSystem* particleSystem, int32 index) override
	{
		B2_NOT_USED(fixture);
		B2_NOT_USED(particleSystem);
		B2_NOT_USED(index);
	}

	/// Called when two particles start touching if
	/// b2_particleContactFilterParticle flag is set on either particle.
	void BeginContact(b2ParticleSystem* particleSystem,
							  b2ParticleContact* particleContact) override
	{
		partPartContacts.push_back(
		    ContactPartPart{particleSystem->index,
							particleContact->GetIndexA(),
							particleContact->GetIndexB()});
	}

	/// Called when two particles start touching if
	/// b2_particleContactFilterParticle flag is set on either particle.
	void EndContact(b2ParticleSystem* particleSystem,
							int32 indexA, int32 indexB) override
	{
		B2_NOT_USED(particleSystem);
		B2_NOT_USED(indexA);
		B2_NOT_USED(indexB);
	}

	/// This is called after a contact is updated. This allows you to inspect a
	/// contact before it goes to the solver. If you are careful, you can modify the
	/// contact manifold (e.g. disable contact).
	/// A copy of the old manifold is provided so that you can detect changes.
	/// Note: this is called only for awake bodies.
	/// Note: this is called even when the number of contact points is zero.
	/// Note: this is not called for sensors.
	/// Note: if you set the number of contact points to zero, you will not
	/// get an EndContact callback. However, you may get a BeginContact callback
	/// the next step.
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	/// This lets you inspect a contact after the solver is finished. This is useful
	/// for inspecting impulses.
	/// Note: the contact manifold does not include time of impact impulses, which can be
	/// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
	/// in a separate data structure.
	/// Note: this is only called for contacts that are touching, solid, and awake.
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
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
    float* buffer = listener->UpdateContactBuffer();
    return buffer;
}

} // extern "C"
