using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

/// <summary>
/// Represents a box shaped particle group in the liquidfun simulation</summary>
public class ParticleGroupBox : ParticleGroup
{	
	[Tooltip("This boxes dimensions")]
	public Vector2 Size = new Vector2(0.5f,0.5f);
	[Tooltip("This boxes rotation relative to the body")]
	public float Rotation;
	
	[SerializeField][HideInInspector]
	private float LastRotation;
	
	[SerializeField][HideInInspector]
	private Vector2 LastSize;
	
	protected override IntPtr GetShape()
	{
		if (pointsList == null)
		{
			pointsList = ShapeTools.MakeBoxPoints(Size);
		}
		PointsCopy = ShapeTools.TransformPoints(transform,Vector3.zero,pointsList);
		
		return ShapeTools.Initialise(PointsCopy);
	}
	
	void OnDrawGizmos()
	{ 	
		if (Size != LastSize)
		{
			pointsList = ShapeTools.MakeBoxPoints(Size);
			LastRotation = 0f;
			LastSize = Size;
		}
		
		if (Rotation != LastRotation)
		{
			pointsList = ShapeTools.RotatePoints(pointsList,Rotation - LastRotation,Vector3.zero); 
			LastRotation = Rotation;
		}		
		
		if(!Application.isPlaying)
		{
			if (pointsList == null)
			{
				pointsList = ShapeTools.MakeBoxPoints(Size);
			}
			ShapeTools.DrawGizmos(GetColors(),ShapeTools.TransformPoints(transform,Vector3.zero,pointsList),true);
		}
	}	
}