using UnityEngine;
using System.Collections;
using System;

/// <summary>This joint creates friction between the two bodies. Can be used to approximate a 'top down' view</summary>
/// seams tobe useless
public class JointFriction : Joint
{	
	[Tooltip("maximum force for this joint")]
	public float MaximumForce = 10f;
	[Tooltip("maximum torque for this joint")]
	public float MaximumTorque = 10f;
	
	protected override void Initialise2(IntPtr world)	
	{		
		Vector3 anchorA = Vector3.zero;
		Vector3 anchorB = Vector3.zero;
		
		B2ObjectPtr = API_Joint.CreateFrictionJoint(world,BodyA.GetComponent<Body>().GetPtr(),BodyB.GetComponent<Body>().GetPtr()	 
		                                             ,anchorA.x,anchorA.y,anchorB.x,anchorB.y,CollideConnected);
		                                             
		API_Joint.SetFrictionJointMaxForce(B2ObjectPtr,MaximumForce);
		API_Joint.SetFrictionJointMaxTorque(B2ObjectPtr,MaximumTorque);
		
	}
	
	void OnDrawGizmos()
	{		
		Gizmos.DrawIcon(transform.position,@"LiquidPhysics2D/Icon_friction",false);							
    }
}
