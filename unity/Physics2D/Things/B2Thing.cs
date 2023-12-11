using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(B2Object))]
public abstract class B2Thing : Thing
{
    [MakerProperty]
    public Vector2 position { get => transform.localPosition;set=>transform.localPosition = value; }
    [MakerProperty]
    public float angle {get=>transform.rotation.eulerAngles.z;set=>transform.rotation=Quaternion.Euler(0,0,value);}
    public abstract bool selectAble { get; }
    public override bool CheckThingSelectAble()
    {
        return selectAble;
    }
    public override bool CheckSelectionRayHit(Vector3 point, Vector3 direction)
    {
        if (!selectAble)
        {
            return false;
        }
        var polys = GetComponentsInChildren<PolygonThing>();
        for (int i = 0; i < polys.Length; i++)
        {
            if (polys[i].CheckPointInPoly(point))
            {
                return true;
            }
        }
        return false;
    }

    public override void OnDragMove(Ray ray)
    {
        base.OnDragMove(ray);
        position = transform.position;
    }
}