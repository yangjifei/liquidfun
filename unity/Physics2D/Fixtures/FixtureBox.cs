using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

/// <summary>
/// Represents a box shaped fixture in the liquidfun simulation</summary>
public class FixtureBox : Fixture
{
	[Tooltip("This boxes dimensions")]
	public Vector2 Size = new Vector2(0.5f,0.5f);
	[Tooltip("This boxes rotation relative to the body")]
	public float Rotation;
	
	[SerializeField][HideInInspector]
	private Vector2 LastOffset;
	[SerializeField][HideInInspector]
	private float LastRotation;
	
	[SerializeField][HideInInspector]
	private Vector2 LastSize;
	
	public override IntPtr GetShape()
	{
		Shapetype = ShapeTypes.Polygon;	
		if (pointsList == null)
		{
			pointsList = ShapeTools.MakeBoxPoints(Size);
		}
		PointsCopy = ShapeTools.TransformPoints(transform,transform.position,pointsList);
		return ShapeTools.Initialise(PointsCopy);
	}
	
	void OnDrawGizmos()
	{ 	
		if (Size != LastSize)
		{
			pointsList = ShapeTools.MakeBoxPoints(Size);
			LastRotation = 0f;
			LastOffset = Vector2.zero;
			LastSize = Size;
		}
		
		if (Offset != LastOffset)
		{
			pointsList = ShapeTools.OffsetPoints(Offset -LastOffset,pointsList); 
			LastOffset = Offset;
		}
		
		if (Rotation != LastRotation)
		{
			pointsList = ShapeTools.RotatePoints(pointsList,Rotation - LastRotation, new Vector3(Offset.x,Offset.y)); 
			LastRotation = Rotation;
		}		

		
		if(!Application.isPlaying)
		{
			if (pointsList == null)
			{
				pointsList = ShapeTools.MakeBoxPoints(Size);
			}
			ShapeTools.DrawGizmos(GetColor(),ShapeTools.TransformPoints(transform,Vector3.zero,pointsList),true);
		}
		else
		{
			ShapeTools.DrawGizmosPlaying(transform,true,GetComponent<Body>().GetDiff(),GetColor(),PointsCopy,true);
		} 
	}	
}
