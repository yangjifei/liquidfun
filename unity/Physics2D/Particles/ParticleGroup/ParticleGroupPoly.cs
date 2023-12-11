using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

/// <summary>
/// Represents a polygon shaped particle group in the liquidfun simulation</summary>
public class ParticleGroupPoly : ParticleGroup
{	
	[Range(3,8)]
	[Tooltip("How many sides this poly has. Note: if you change this it will reset this shape to a regular polygon")]
	public int NumberOfSides = 5;
	[Tooltip("Size of this poly shape")]
	public float radius = 0.25f;
	
	[SerializeField][HideInInspector]
	private int LastNumberOfSides;
	[SerializeField][HideInInspector]
	private float LastRadius;
	
	protected override IntPtr GetShape()
	{
		return GetPolyShape(NumberOfSides,radius,Vector3.zero);
	}
	
	void OnDrawGizmos()
	{ 	
		if (NumberOfSides != LastNumberOfSides)
		{
			pointsList = ShapeTools.makePolyPoints(NumberOfSides,radius);
			LastNumberOfSides = NumberOfSides;
			LastRadius = radius;
		}
		if (radius != LastRadius)
		{
			pointsList = ShapeTools.ChangeRadius(radius - LastRadius,pointsList,Vector3.zero); 
			LastRadius = radius;
		}	
		
		bool loop = true;
		if (DontDrawLoop)loop  = false;
		
		if(!Application.isPlaying)
		{
			if (pointsList == null)
			{
				pointsList = ShapeTools.makePolyPoints(NumberOfSides,radius);
			}
			ShapeTools.DrawGizmos(GetColors(),ShapeTools.TransformPoints(transform,Vector3.zero,pointsList),loop);
        }
    }	
}