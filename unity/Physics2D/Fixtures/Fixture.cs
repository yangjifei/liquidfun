using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;
#if UNITY_EDITOR
using UnityEditor;
#endif

/// <summary>
/// Represents a fixture in the liquidfun simulation</summary>
[RequireComponent (typeof (Body))]
public abstract class Fixture : PolygonThing
{
	[Tooltip("Density of this fixture. Will determine its mass")]
	public float Density = 1f;
	[Tooltip("Is this fixture a sensor? Sensors dont interact in collisions")]
	public bool IsSensor = false;
	[Tooltip("Offset of this fixture from the body")]
	public Vector2 Offset;
	[Tooltip("What material is this made out of? Governs bounciness and friction")]
	public PhysicsMaterial2D PhysMaterial;
	
	public int CollisionGroupIndex = 0;
		
	protected float actualRestitution;
	protected float actualFriction;
	protected float defaultRestitution = 0.2f;
	protected float defaultFriction = 0.1f;
	protected ShapeTypes Shapetype;
	/// <summary>key of this fixture in the LPbody dictionary myFixtures
	/// and its userdata value in the simulation</summary>	
	protected int myIndex;	
	private Body body;
		
	UInt16 categoryBits = 0x0001;
	UInt16 maskBits = 0xFFFF;

    /// <summary>Set the collision filter data for this fixture</summary>
    public void SetFixtureFilterData(Int16 groupIndex, UInt16 categoryBits, UInt16 maskBits)
    {
        API_Fixture.SetFixtureFilterData(B2ObjectPtr, groupIndex, categoryBits, maskBits);

        if (SubPtrs != null)
        {
            foreach (IntPtr ptr in SubPtrs)
            {
                API_Fixture.SetFixtureFilterData(ptr, groupIndex, categoryBits, maskBits);
            }
        }
        
    }
	
	/// <summary>Determine this fixtures physics properties</summary>
	protected void GetPhysProps()
	{
		if (PhysMaterial != null) 
		{
			actualRestitution = PhysMaterial.bounciness;
			actualFriction = PhysMaterial.friction;
		}
		else
		{
			actualRestitution = defaultRestitution;
			actualFriction = defaultFriction;
		}
	}
	/// <summary>Determine what colour to draw this fixtures gizmo</summary>
	protected Color GetColor()
	{	
		#if UNITY_EDITOR
		if (Selection.Contains(gameObject))
		{
		 	return Colors.Selected;
		}
		else if (IsSensor)
		{
		 	return Colors.Sensor;
		}
		#endif
		if (body != null) return body.GetColor();
		return GetComponent<Body>().GetColor();	

	}	
	/// <summary>Get the shape pointer for this fixture</summary>	
	public abstract IntPtr GetShape();
    protected virtual void Awake()
    {
		body=GetComponentInParent<Body>();
        myIndex = body.AddFixture(this);
    }
    /// <summary>Create this fixture in the simulation</summary>								
    public virtual void Initialise()
	{
		GetPhysProps();
		
	    IntPtr shape = GetShape();

		B2ObjectPtr = API_Fixture.AddFixture(body.GetPtr(),(int)Shapetype
		                                   ,shape
		                                   ,Density,actualFriction,actualRestitution,IsSensor,myIndex);	
		                                   
		API_Fixture.SetFixtureFilterData(B2ObjectPtr,(Int16)CollisionGroupIndex,categoryBits,maskBits);
	}
	
	/// <summary>Create this fixture in the simulation with a shape pointer you already have
	/// Note: Used for concave fixtures or fixtures with more than 8 vertices
	/// They are broken up into several fixtures </summary>	
	protected override void InitialiseWithShape(IntPtr shape)
	{
		IntPtr fix = API_Fixture.AddFixture(body.GetPtr(),(int)Shapetype
		                                     ,shape
		                                     ,Density,actualFriction,actualRestitution,IsSensor,myIndex);
		                                     
		API_Fixture.SetFixtureFilterData(fix,(Int16)CollisionGroupIndex,categoryBits,maskBits);    
		                               
		SubPtrs.Add(fix);	
	}
	
	/// <summary>If the shape you attempt to make is complex log an error</summary>	
	protected override void LogComplex()
	{
		Debug.LogError("Polygon fixture # "+myIndex+" on Body # "+body.myIndex+
		               " is complex! ie. has self intersecting edges. Creating default shape instead");
		
	}
	
	/// <summary>Delete this fixture. In the simulation and in unity</summary>	
	public override void Delete ()
	{
		API_Fixture.DeleteFixture(body.GetPtr(),B2ObjectPtr);
		if (SubPtrs != null)
		{
			foreach (IntPtr fix in SubPtrs)
			{
				API_Fixture.DeleteFixture(body.GetPtr(),fix);
            }	
		}
	}

    public bool isFixtureStatic()
    {
        if (body == null)
        {
            body = GetComponent<Body>();
        }
        return body.BodyType == BodyTypes.Static;
    }

}
