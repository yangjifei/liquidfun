using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

/// <summary>
/// Represents a chain shaped fixture in the liquidfun simulation</summary>
public class FixtureChainShape : Fixture
{
	[Tooltip("This chainshapes rotation relative to the body")]
	public float Rotation;
	[Tooltip("Should this shape form a closed loop?")]
	public bool IsLoop = false;
	
	[SerializeField][HideInInspector]
	private Vector2 LastOffset;
	[SerializeField][HideInInspector]
	private float LastRotation;	
	
	public override IntPtr GetShape()
	{
		if (pointsList == null)
		{
			pointsList = ShapeTools.MakeEdgePoints();
		}
		PointsCopy = ShapeTools.TransformPoints(transform,transform.position,pointsList);
		
		if (pointsList.Count > 2)
		{
			Shapetype = ShapeTypes.ChainShape;
			return API_Shape.GetChainShapeDef(ShapeTools.GetfloatArray(PointsCopy),IsLoop);
		}
		else
		{
			Shapetype = ShapeTypes.Edge;
			return API_Shape.GetEdgeShapeDef(PointsCopy[0].x,PointsCopy[0].y,PointsCopy[1].x,PointsCopy[1].y);
		}

	}
	
	void OnDrawGizmos()
	{ 	
		if (Rotation != LastRotation)
		{
			pointsList = ShapeTools.RotatePoints(pointsList,Rotation - LastRotation,new Vector3(Offset.x,Offset.y)); 
			LastRotation = Rotation;
		}		
		if (Offset != LastOffset)
		{
			pointsList = ShapeTools.OffsetPoints(Offset -LastOffset,pointsList); 
			LastOffset = Offset;
		}
		
		if(!Application.isPlaying)
		{
			if (pointsList == null)
			{
				pointsList = ShapeTools.MakeEdgePoints();
			}
			ShapeTools.DrawGizmos(GetColor(),ShapeTools.TransformPoints(transform,Vector3.zero,pointsList),IsLoop);
		}
		else
		{
			if (PointsCopy != null)
			{
				ShapeTools.DrawGizmosPlaying(transform,true,GetComponent<Body>().GetDiff(),GetColor(),PointsCopy,IsLoop);
			}               
		} 
	}	
}
