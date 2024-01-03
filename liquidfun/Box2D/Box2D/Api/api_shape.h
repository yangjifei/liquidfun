#include "Box2D/Box2D.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include <vector>
#include "api.h"
#include "../Unity/IUnityInterface.h"
#define IntPtr void *

extern "C"
{
    // GetBoxShapeDef
    UNITY_INTERFACE_EXPORT b2PolygonShape* UNITY_INTERFACE_API GetBoxShapeDef(float width, float height, float centreX, float centreY, float angle)
    {
        b2PolygonShape *shape = new b2PolygonShape();
        b2Vec2 center(centreX, centreY);
        shape->SetAsBox(width * 0.5f, height * 0.5f, center, angle);
        return shape;
    }

    // GetCircleShapeDef
    UNITY_INTERFACE_EXPORT b2CircleShape* UNITY_INTERFACE_API GetCircleShapeDef(float radius, float centreX, float centreY)
    {
        b2CircleShape *shape = new b2CircleShape();
        shape->m_p.Set(centreX, centreY);
        shape->m_radius = radius;
        return shape;
    }

    // GetPolygonShapeDef
    UNITY_INTERFACE_EXPORT b2PolygonShape* UNITY_INTERFACE_API GetPolygonShapeDef(float *vertexArray)
    {
        int vertexCount = static_cast<int>(vertexArray[0]);
        b2Vec2 *vertices = new b2Vec2[vertexCount];
        for (int i = 0; i < vertexCount; ++i)
        {
            vertices[i].Set(vertexArray[i * 2 + 1], vertexArray[i * 2 + 2]);
        }

        b2PolygonShape *shape = new b2PolygonShape();
        shape->Set(vertices, vertexCount);

        delete[] vertices;
        return shape;
    }

    // GetChainShapeDef
    UNITY_INTERFACE_EXPORT b2ChainShape* UNITY_INTERFACE_API GetChainShapeDef(float *vertexArray, bool loop)
    {
        int vertexCount = static_cast<int>(vertexArray[0]);
        b2Vec2 *vertices = new b2Vec2[vertexCount];
        for (int i = 0; i < vertexCount; ++i)
        {
            vertices[i].Set(vertexArray[i * 2 + 1], vertexArray[i * 2 + 2]);
        }

        b2ChainShape *shape = new b2ChainShape();
        if (loop)
        {
            shape->CreateLoop(vertices, vertexCount);
        }
        else
        {
            shape->CreateChain(vertices, vertexCount);
        }

        delete[] vertices;
        return shape;
    }

    // GetEdgeShapeDef
    UNITY_INTERFACE_EXPORT b2EdgeShape* UNITY_INTERFACE_API GetEdgeShapeDef(float x1, float y1, float x2, float y2)
    {
        b2EdgeShape *shape = new b2EdgeShape();
        shape->Set(b2Vec2(x1, y1), b2Vec2(x2, y2));
        return shape;
    }

    // GetEllipseShapeDef
    UNITY_INTERFACE_EXPORT b2PolygonShape* UNITY_INTERFACE_API GetEllipseShapeDef(float outerRadius, float divisions)
    {
        // Create an ellipse shape using a polygon shape
        b2PolygonShape *shape = new b2PolygonShape();
        int vertexCount = static_cast<int>(divisions);
        b2Vec2 *vertices = new b2Vec2[vertexCount];

        for (int i = 0; i < vertexCount; ++i)
        {
            float angle = static_cast<float>(i) / static_cast<float>(divisions) * 2.0f * b2_pi;
            float x = outerRadius * cosf(angle);
            float y = outerRadius * sinf(angle);
            vertices[i].Set(x, y);
        }

        shape->Set(vertices, vertexCount);

        delete[] vertices;
        return shape;
    }

    // Returns a 2 element float array containing the x and y positions of a polygon shape's centroid. The array must be marshalled before use.
    UNITY_INTERFACE_EXPORT float* UNITY_INTERFACE_API GetPolyShapeCentroid(void* shape) {
        b2PolygonShape* polyShape = static_cast<b2PolygonShape*>(shape);

        // Check if the shape pointer is valid
        if (!polyShape) {
            // Handle the case where the pointer is invalid
            return nullptr;
        }

        // Get the centroid of the polygon shape
        b2Vec2 centroid = polyShape->m_centroid;

        // Create a float array to hold the x and y positions
        float* centroidArray = GetFloatBuffer(2);
        centroidArray[0] = centroid.x;
        centroidArray[1] = centroid.y;

        return centroidArray;
    }
}