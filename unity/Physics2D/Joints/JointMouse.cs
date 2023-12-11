using UnityEngine;
using System.Collections;
using System;

/// <summary>This is like a rope joint that always tries to drag Body B to the target point
/// You must specify a BodyA for the joint to be created successfully but apart from that it has no influence</summary>
public class JointMouse : Joint
{	
	[Tooltip("The maximum force this joint can exert")]
	public float MaximumForce = 10000f;
	[Tooltip("How much damping this joint has")]
	public float DampingRatio = 0.6f;
	[Tooltip("This joints natural frequency in hertz. Note: it is recommended to keep this slower than the simulation timestep")]
	public float Frequency = 4f;
	[Tooltip("How close to the target should this joint attempt to bring BodyB")]
	public float Accuracy = 0.1f;
	
	protected override void Initialise2(IntPtr world)	
	{		
		
		B2ObjectPtr = API_Joint.CreateMouseJoint(world,BodyA.GetComponent<Body>().GetPtr(),BodyB.GetComponent<Body>().GetPtr()	 
		                                       ,BodyB.transform.position.x,BodyB.transform.position.y,true);
		                                             
		API_Joint.SetMouseJointMaxForce(B2ObjectPtr,MaximumForce);
		API_Joint.SetMouseJointDampingRatio(B2ObjectPtr,DampingRatio);
		API_Joint.SetMouseJointFrequency(B2ObjectPtr,Frequency);
		                                         
	}
	
	public void SetTarget(Vector3 target)
	{
		if ((transform.position - target).magnitude > Accuracy)
		{
			API_Joint.SetMouseJointTarget(B2ObjectPtr,target.x,target.y);
		}
	}
	
	void OnDrawGizmos()
	{		
		Gizmos.DrawIcon(transform.position,@"LiquidPhysics2D/Icon_mouse",false);							
	}
}
