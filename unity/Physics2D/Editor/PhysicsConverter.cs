﻿using UnityEditor;
using UnityEngine;
using System.IO;
using System.Collections.Generic;

public class PhysicsConverter : MonoBehaviour
{

    [MenuItem("XXPhysics/Convert")]
    static void Convert()
    {
        ConvertCircles();
        ConvertBoxes();
        ConvertEdges();
        ConvertPolys();
    }

    [MenuItem("Liquid Physics 2D/Remove Unity Colliders")]
    static void RemoveAllUnityColliders()
    {
        Undo.SetCurrentGroupName("Undo generate outline.");
        int undoGroup = Undo.GetCurrentGroup();

        Debug.Log("Removed " + Resources.FindObjectsOfTypeAll<Collider>().Length + " Unity colliders from scene.");
        foreach (Collider col in Resources.FindObjectsOfTypeAll<Collider>())
        {
            Undo.DestroyObjectImmediate(col);
        }

        Undo.CollapseUndoOperations(undoGroup);
    }

    static void Setupdynamics(GameObject ob)
    {
        Rigidbody2D rigidb = ob.GetComponent<Rigidbody2D>();
        if (rigidb)
        {
            Body bod = ob.GetComponent<Body>();
            if (rigidb.isKinematic) bod.BodyType = BodyTypes.Kinematic;
            else bod.BodyType = BodyTypes.Dynamic;
            bod.LinearDamping = rigidb.drag;
            bod.AngularDamping = rigidb.angularDrag;
            bod.GravityScale = rigidb.gravityScale;
            bod.FixedRotation = rigidb.constraints!=0;
            if (rigidb.collisionDetectionMode == CollisionDetectionMode2D.Continuous) bod.IsBullet = true;
            if (rigidb.sleepMode == RigidbodySleepMode2D.NeverSleep) bod.AllowSleep = false;

            Undo.DestroyObjectImmediate(rigidb);
        }
    }

    static void CopyGeneric(Collider2D unity, Fixture lp2d)
    {
        #if UNITY_5_0
        lp2d.Offset = unity.offset;
        #endif
        lp2d.PhysMaterial = unity.sharedMaterial;
        lp2d.IsSensor = unity.isTrigger;
    }

    static void ConvertCircles()
    {
        foreach (CircleCollider2D circle in FindObjectsOfType<CircleCollider2D>())
        {
            GameObject ob = circle.gameObject;
            FixtureCircle lpcircle = Undo.AddComponent<FixtureCircle>(ob);

            CopyGeneric(circle, lpcircle);
            float mult = 1f;

            if (ob.transform.lossyScale.x != ob.transform.lossyScale.y)
            {
                if (ob.transform.lossyScale.x > ob.transform.lossyScale.y)
                {
                    mult = ob.transform.lossyScale.x / ob.transform.lossyScale.y;
                }
                else 
                {
                    mult = ob.transform.lossyScale.y / ob.transform.lossyScale.x;
                }
            }

            lpcircle.Radius = circle.radius*mult;

            Undo.DestroyObjectImmediate(circle);

            Setupdynamics(ob);
        }
    }

    static void ConvertBoxes()
    {
        foreach (BoxCollider2D Box in FindObjectsOfType<BoxCollider2D>())
        {
            GameObject ob = Box.gameObject;
            FixtureBox lpBox = Undo.AddComponent<FixtureBox>(ob);

            lpBox.Size = Box.size ;
            CopyGeneric(Box, lpBox);

            Undo.DestroyObjectImmediate(Box);

            Setupdynamics(ob);
        }
    }

    static void ConvertEdges()
    {
        foreach (EdgeCollider2D Edge in FindObjectsOfType<EdgeCollider2D>())
        {
            GameObject ob = Edge.gameObject;
            FixtureChainShape lpEdge = Undo.AddComponent<FixtureChainShape>(ob);

            lpEdge.DefinePoints(ShapeTools.Vec2ArrayToVec3Array(Edge.points));
            CopyGeneric(Edge, lpEdge);

            Undo.DestroyObjectImmediate(Edge);

            Setupdynamics(ob);
        }
    }

    static void ConvertPolys()
    {
        foreach (PolygonCollider2D poly in FindObjectsOfType<PolygonCollider2D>())
        {
            GameObject ob = poly.gameObject;

            for (int i = 0; i < poly.pathCount; i++)
            {
                FixturePoly lppoly = Undo.AddComponent<FixturePoly>(ob);
                lppoly.DefinePoints(ShapeTools.Vec2ArrayToVec3Array(poly.GetPath(i)));
                CopyGeneric(poly, lppoly);
            }

            Undo.DestroyObjectImmediate(poly);

            Setupdynamics(ob);
        }
    }
}