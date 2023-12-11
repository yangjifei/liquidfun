using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

/// <summary>
/// Represents a polygon shaped fixture in the liquidfun simulation</summary>
public class FixturePoly : Fixture
{
	[Tooltip("This poly shapes rotation relative to the body")]
	public float Rotation;
	
	[Range(3,8)]	
	[Tooltip("How many sides this poly has. Note: if you change this it will reset this shape to a regular polygon")]
	public int NumberOfSides = 5;
	[Tooltip("Size of this poly shape")]
	public float radius = 0.25f;
	
	[SerializeField][HideInInspector]
	private Vector2 LastOffset;
	[SerializeField][HideInInspector]
	private float LastRotation;
	[SerializeField][HideInInspector]
	private int LastNumberOfSides = 5;
	[SerializeField][HideInInspector]
	private float LastRadius = 0.25f;
			
	public override IntPtr GetShape()
	{
		Shapetype = ShapeTypes.Polygon;
		return GetPolyShape(NumberOfSides,radius,transform.position);
	}	
    
    void OnDrawGizmos()
	{ 	
		if (NumberOfSides != LastNumberOfSides)
		{
			pointsList = ShapeTools.makePolyPoints(NumberOfSides,radius);
			LastNumberOfSides = NumberOfSides;
			LastRotation = 0f;
			LastOffset = Vector2.zero;
        }
		if (radius != LastRadius)
		{
			pointsList = ShapeTools.ChangeRadius(radius - LastRadius,pointsList, new Vector3(Offset.x,Offset.y)); 
			LastRadius = radius;
        }
        
		if (Offset != LastOffset)
		{
			pointsList = ShapeTools.OffsetPoints(Offset -LastOffset,pointsList); 
			LastOffset = Offset;
		}
        
		if (Rotation != LastRotation)
		{
			pointsList = ShapeTools.RotatePoints(pointsList,Rotation - LastRotation,new Vector3(Offset.x,Offset.y)); 
			LastRotation = Rotation;
		}		
		
		bool loop = true;
		if (DontDrawLoop)loop  = false;
		
        if(!Application.isPlaying)
		{
			if (pointsList == null)
			{
				pointsList = ShapeTools.makePolyPoints(NumberOfSides,radius);
            }
			ShapeTools.DrawGizmos(GetColor(),ShapeTools.TransformPoints(transform,Vector3.zero,pointsList),loop);
		}
		else
		{
			if (PointsCopy != null)
            {
				ShapeTools.DrawGizmosPlaying(transform,true,GetComponent<Body>().GetDiff(),GetColor(),PointsCopy,loop);
            }               
        } 
    }	
}