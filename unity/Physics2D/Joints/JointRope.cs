using UnityEngine;
using System.Collections;
using System;

/// <summary>Prevents 2 bodies from going over a cetain distance apart as if they were connected by a rope</summary>
public class JointRope : Joint
{	
	[Tooltip("Offset of the anchor point of this joint on bodyA relative to the body position")]
	public Vector2 BodyAAnchorOffset; 
	[Tooltip("Offset of the anchor point of this joint on bodyB relative to the body position")]
	public Vector2 BodyBAnchorOffset; 
	[Tooltip("Lenght of the 'rope' (maximum distance the bodies can be apart)")]
	public float MaximumLenght = 2f;
	
	protected override void Initialise2(IntPtr world)	
	{				
		B2ObjectPtr = API_Joint.CreateRopeJoint(world,BodyA.GetComponent<Body>().GetPtr(),BodyB.GetComponent<Body>().GetPtr()	 
		                                      ,BodyAAnchorOffset.x,BodyAAnchorOffset.y,BodyBAnchorOffset.x
		                                      ,BodyBAnchorOffset.y,MaximumLenght,CollideConnected);
		            
	}
	
	void OnDrawGizmos()
	{		
		if (true)
		{
			Gizmos.color = Colors.Joint;
			
			Gizmos.DrawLine(BodyA.transform.position+ ShapeTools.RotatePoint((Vector3)BodyAAnchorOffset,BodyA.transform.rotation.eulerAngles.z,Vector3.zero)  ,
			                BodyB.transform.position+ ShapeTools.RotatePoint((Vector3)BodyBAnchorOffset,BodyB.transform.rotation.eulerAngles.z,Vector3.zero)); 	
		}
		Gizmos.DrawIcon(transform.position,@"LiquidPhysics2D/Icon_rope",false);							
	}
}
