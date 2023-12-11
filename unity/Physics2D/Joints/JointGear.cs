using UnityEngine;
using System.Collections;
using System;

/// <summary>Simulates round or stright mechanical gears between two bodies</summary>
public class JointGear : Joint
{
	[Tooltip("The 1st joint component attached to this gear (Must be either revolute or prismatic)")]
	public Joint JointA;
	[Tooltip("The 2nd joint component attached to this gear (Must be either revolute or prismatic)")]
	public Joint JointB;
	[Tooltip("The mechanical gear ratio")]
	public float Ratio = 1;
	
	protected override void Initialise2(IntPtr world)	
	{		
		bool isArev = false;
		bool isBrev = false;
		
		if (JointA !=null && JointB !=null 
		    &&(JointA.GetType() == typeof(JointRevolute )||JointA.GetType() == typeof(JointPrismatic))
		    &&(JointB.GetType() == typeof(JointRevolute )||JointB.GetType() == typeof(JointPrismatic)))
		{
			if (JointA.GetType() == typeof(JointRevolute)) isArev = true;
			if (JointB.GetType() == typeof(JointRevolute)) isBrev = true;
		
			B2ObjectPtr = API_Joint.CreateGearJoint(world,BodyA.GetComponent<Body>().GetPtr(),BodyB.GetComponent<Body>().GetPtr()	 
			                                             ,JointA.GetPtr(),isArev,JointB.GetPtr(),isBrev,Ratio,CollideConnected);
        }
        else
        {
			Debug.LogError("This Gear Joint must be assigned 2 Other Joints in order to be created"
			               +", also both joints need to be a type of either LPJointRevolute or LPJointPrismatic");
        }        
	}
	
	void OnDrawGizmos()
	{		
		Gizmos.DrawIcon(transform.position,@"LiquidPhysics2D/Icon_gear",false);							
	}
}
