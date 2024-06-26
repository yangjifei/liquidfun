using UnityEngine;
using System.Collections;
using System;

/// <summary>Creates a fixed immobile connection between two bodies at a certain point.
/// Note that movement can occur between the bodies when large forces are applied to one of the bodies for example</summary>
public class JointWeld : Joint
{	
	protected override void Initialise2(IntPtr world)
	{
		Vector3 anchorA = transform.position - BodyA.transform.position;
		Vector3 anchorB = transform.position - BodyB.transform.position;
        B2ObjectPtr = API_Joint.CreateWeldJoint(world, BodyA.GetComponent<Body>().GetPtr(), BodyB.GetComponent<Body>().GetPtr()
		                                  ,anchorA.x,anchorA.y,anchorB.x,anchorB.y,CollideConnected);
	}
	
    void OnDrawGizmos()
	{		
		Gizmos.DrawIcon(transform.position,@"LiquidPhysics2D/Icon_weld",false);				
	}
}
