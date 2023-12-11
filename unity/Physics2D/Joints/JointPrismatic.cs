using UnityEngine;
using System.Collections;
using System;

/// <summary>Simulates a joint that can translate in one direction only, like an elevator platform</summary>
public class JointPrismatic : Joint
{
	[Tooltip("Does this joint have a motor?")]
	public bool HasMotor = false;
	[Tooltip("The maximum force this joint can exert")]
	public float MaxMotorForce = 500f;
	[Tooltip("The movement speed this motorised joint should try to achieve")]
	public float MotorSpeed = 1.5f;
	
	[Tooltip("Does this joint have limits?")]
	public bool HasLimits = false;
	[Tooltip("The distance along the line of translation the lower limit is from the joint position")]
	public float LowerLimit = -1f;
	[Tooltip("The distance along the line of translation the upper limit is from the joint position")]
	public float UpperLimit = 1f;
	[Tooltip("vector2 representing the angle of the line of translation for this joint")]
	public Vector2 Translation = new Vector2(2f,2f);

	Vector3 Back;	
	Vector3 Forward;
	Vector3 BodyAStartPos;
			
	protected override void Initialise2(IntPtr world)	
	{	
		getbackfor();
        RotateTranslation();

		Vector3 anchorA = transform.position - BodyA.transform.position;
		Vector3 anchorB = transform.position - BodyB.transform.position;
		B2ObjectPtr = API_Joint.CreatePrismaticJoint(world,BodyA.GetComponent<Body>().GetPtr(),BodyB.GetComponent<Body>().GetPtr()	 
                                                         ,anchorA.x,anchorA.y,anchorB.x,anchorB.y,Translation.x,Translation.y,CollideConnected);	                                   
		if (HasMotor)
		{
			API_Joint.EnablePrismaticJointMotor(B2ObjectPtr,HasMotor);
			API_Joint.SetPrismaticJointMaxMotorForce(B2ObjectPtr,MaxMotorForce);
			API_Joint.SetPrismaticJointMotorSpeed(B2ObjectPtr,MotorSpeed);
		}
		
		if (HasLimits)
		{
			API_Joint.EnablePrismaticJointLimits(B2ObjectPtr,HasLimits);
			API_Joint.SetPrismaticJointLimits(B2ObjectPtr,LowerLimit,UpperLimit);
		}
	}

    private void RotateTranslation()
    {
        float cos = Mathf.Cos(transform.rotation.eulerAngles.z*Mathf.Deg2Rad);
        float sin = Mathf.Sin(transform.rotation.eulerAngles.z*Mathf.Deg2Rad);

        Translation = new Vector2(
            Translation.x*cos - Translation.y*sin
            , Translation.x * sin + Translation.y * cos
            );     
    }
	
	private void getbackfor()
	{
		BodyAStartPos = BodyA.transform.position;
		
		if (HasLimits)
		{
			Vector2 tran = Translation.normalized ;
			Back = transform.position + (Vector3)(tran*LowerLimit);
			Forward = transform.position + (Vector3)(tran*UpperLimit);
		}
		else
		{
			Back = transform.position - (Vector3)Translation;
			Forward = transform.position + (Vector3)Translation;
		}
	}
	
	void OnDrawGizmos()
	{					
		if (!Application.isPlaying)
		{		
			getbackfor();
		}
						
		Gizmos.DrawIcon(transform.position,@"LiquidPhysics2D/Icon_prismatic",false);				
		Gizmos.color = Colors.Joint;
	
		Gizmos.DrawLine(Back + (BodyA.transform.position - BodyAStartPos), Forward + (BodyA.transform.position - BodyAStartPos));			
	}
}
