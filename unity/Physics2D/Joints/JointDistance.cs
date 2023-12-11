using UnityEngine;
using System.Collections;
using System;

/// <summary>This joint keeps two bodies a certain distance apart as if they were connected by a rigid stick</summary>
public class JointDistance : Joint
 {		
	[Tooltip("How much damping this joint has")]
 	public float Dampingratio = 1f;
	[Tooltip("This joints natural frequency in hertz. Note: it is recommended to keep this slower than the simulation timestep")]
 	public float FrequencyInHertz = 4f;
	[Tooltip("Offset of the anchor point of this joint on bodyA relative to the body position")]
 	public Vector2 BodyAAnchorOffset; 
	[Tooltip("Offset of the anchor point of this joint on bodyB relative to the body position")]
	public Vector2 BodyBAnchorOffset; 
    
	protected override void Initialise2(IntPtr world)	
	{		
		float lenght = (BodyA.transform.position-BodyB.transform.position).magnitude;
		B2ObjectPtr = API_Joint.CreateDistanceJoint(world,BodyA.GetComponent<Body>().GetPtr(),BodyB.GetComponent<Body>().GetPtr()	 
		                                          ,BodyAAnchorOffset.x,BodyAAnchorOffset.y
		                                          ,BodyBAnchorOffset.x,BodyBAnchorOffset.y,lenght,CollideConnected);
		                                                  
		API_Joint.SetDistanceJointDampingRatio(B2ObjectPtr,Dampingratio);	
		API_Joint.SetDistanceJointFrequency(B2ObjectPtr,FrequencyInHertz);		            
	}
	
	void OnDrawGizmos()
	{		
		if (BodyA!=null&&BodyB!=null)
		{
			Gizmos.color = Colors.Joint;
			
			Gizmos.DrawLine(BodyA.transform.position+ ShapeTools.RotatePoint((Vector3)BodyAAnchorOffset,
							BodyA.transform.rotation.eulerAngles.z,Vector3.zero) ,
			                BodyB.transform.position+ ShapeTools.RotatePoint((Vector3)BodyBAnchorOffset,
			                BodyB.transform.rotation.eulerAngles.z,Vector3.zero)); 	
		}
		Gizmos.DrawIcon(transform.position,@"LiquidPhysics2D/Icon_distance",false);							
	}
}
