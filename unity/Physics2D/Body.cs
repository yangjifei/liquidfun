using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.Runtime.InteropServices;
#if UNITY_EDITOR
using UnityEditor;
#endif

/// <summary>Represents a b2Body object in the liquidfun simulation world</summary>
public class Body : B2Object, IPlayAble
{	
	[Tooltip("What kind of body is this. Static = cant move. Dynamic = can move. Kinematic = not affected by gravity or collisons")]
	public BodyTypes BodyType = BodyTypes.Static;
	[Tooltip("how much linear velocity this body will lose over time")]
	public float LinearDamping = 0.1f;
	[Tooltip("how much angular velocity this body will lose over time")]
	public float AngularDamping = 0.1f;
	[Tooltip("Can this body sleep? Recommended, improves performance")]
	public bool AllowSleep = true;
	[Tooltip("Can this body not rotate?")]
	public bool FixedRotation = false;
	[Tooltip("Is this body a bullet? Bullets are simulated more accurately(and will not pass thorugh other objects when they are going fast), but more expensively")]
	public bool IsBullet  = false;
	[Tooltip("Scale of gravity in relation to this object. Eg minus value will make this fall 'upwards'")]
	public float GravityScale = 1f;
	[Tooltip("Should this body be created when the game plays")]	
	public bool SpawnOnPlay = true;
	/// <summary>key of this body in the PhysicsWorld dictionary allBodies
	/// and its userdata value in the simulation</summary>	
	public int myIndex {get; private set;}
	public bool Initialised = false;
	private PhysicsWorld world;
	private float StartRotation;
	private float diff = 0f;

	/// All the references to Fixtures associated with this body are stored here
	/// I use a dictionary so each key is unique
	public Dictionary<int,Fixture> myFixtures = new Dictionary<int, Fixture>();
	private int fixturesIndex = 0;
	
	/// <summary>Add a fixture to this bodies list of fixtures
	///Note: this is normally called from the fixtures Initialise method</summary>	
	public int AddFixture(Fixture fixture)
	{
		myFixtures.Add(fixturesIndex,fixture);
		fixturesIndex++;
		return fixturesIndex -1;
	}
	
	/// <summary>Remove a fixture from this bodies list of fixtures
	///Note: this is normally called from the fixtures delete method</summary>	
	public void RemoveFixture(int index)
    {
		myFixtures.Remove(index);
    }
	
	public float GetDiff()
	{
		return diff;
	}
	
	
	//This creates the body and its fixtures in the physics simulation
	public void Initialise(PhysicsWorld w)
	{
		StartRotation = transform.localEulerAngles.z;
		world = w;

        myIndex = world.AddBody(this);                  
		B2ObjectPtr = API_Body.CreateBody(world.GetPtr(),(int)BodyType,transform.position.x,transform.position.y
										  ,0f
		                                  ,LinearDamping,AngularDamping,AllowSleep,FixedRotation,IsBullet,GravityScale
		                                  ,myIndex);
		Initialised = true;
	}
	
	/// <summary>Returns whether this body needs to be updated or not</summary>
	public bool shouldUpdate()
	{
		if (gameObject.activeSelf && Initialised && BodyType != BodyTypes.Static)
		{
			return true;
		}
		return false;
	}
	
	/// <summary> This is called from the PhysicsWorld compoonent during the Update event handler call
	/// It updates the position and rotation of the gameobject of which this body is a component
	/// All the bodies info is fetched simultaneously to reduce calls to the native library and improve performance on iOS</summary>
	public void PhysicsWorldUpdate(float x,float y,float ang)
	{
		transform.position = new Vector3(x,y,transform.position.z);
		diff = Mathf.Rad2Deg*ang;
		transform.localEulerAngles = new Vector3(0f,0f,diff+StartRotation);
	}
	
	/// <summary> Determines what colour to draw the bodies fixtures based on its state / type  </summary>
	public Color GetColor()
	{    
		if (BodyType == BodyTypes.Static) 
		{
			if (Initialised && Application.isPlaying) 
			{
				if (!API_Body.GetBodyActive(B2ObjectPtr)) 
				{
					return Colors.StaticInactive;
				}
				if (!API_Body.GetBodyAwake(B2ObjectPtr)) 
				{
                    return Colors.StaticAsleep;
                }	  
            }	
			return Colors.StaticAwake;	
		}
		if (BodyType == BodyTypes.Dynamic)
		{
			if (Initialised && Application.isPlaying) 
			{
				if (!API_Body.GetBodyActive(B2ObjectPtr)) 
				{
					return Colors.DynamicInActive;
				}
				if (!API_Body.GetBodyAwake(B2ObjectPtr)) 
				{
                    return Colors.DynamicAsleep;
                }	 
            }
			return Colors.DynamicAwake;
		}
		if (BodyType == BodyTypes.Kinematic)
		{
			if (Initialised && Application.isPlaying) 
			{
				if (!API_Body.GetBodyActive(B2ObjectPtr)) 
				{
					return Colors.KinematicInActive;
				}
				if (!API_Body.GetBodyAwake(B2ObjectPtr)) 
                {
                    return Colors.KinematicAsleep;
                }	
			}
			return Colors.KinematicAwake;
		}
		return  Color.white;		
	}
	
	/// <summary>
	/// Returns an array of the indices of every body currently in contact with this body
	/// Note that the 1st element of the array is the lenght of the array</summary>
	public int[] GetContacts()
	{
		IntPtr contactsPointer = API_Body.GetBodyContacts(B2ObjectPtr); 
		
		int[] contactsArray = new int[1];
		Marshal.Copy (contactsPointer,contactsArray,0,1);
		int contsNum = contactsArray[0];
		
		int[] contacts = new int[contsNum+1];
        if (contsNum > 0) 
		{		
            Marshal.Copy(contactsPointer, contacts, 0, contsNum+1);		
        }	
        
        // LPAPIUtility.ReleaseIntArray(contactsPointer);	
		return contacts;
    }
	
	//Delete the body (and its fixtures) from the physics simulation, also destroy the gameobject in unity. 
	public override void Delete()
	{
		world.RemoveBody(myIndex);
		API_Body.DeleteBody(world.GetPtr(),B2ObjectPtr);
	}

    //Delete the body (and its fixtures) from the physics simulation
    public void DeleteWithoutRemovingGameObject()
    {
        world.RemoveBody(myIndex);
        API_Body.DeleteBody(world.GetPtr(), B2ObjectPtr);
        foreach (Fixture f in GetComponents<Fixture>())
        {
            Destroy(f);
        }
        Destroy(GetComponent<Body>());
    }

    public void DeleteWithoutRemovingComponents()
    {
        world.RemoveBody(myIndex);
        API_Body.DeleteBody(world.GetPtr(), B2ObjectPtr);
    }

    public void OnPlayAwake()
    {
        Initialise(PhysicsWorld.Instance);
        foreach (var item in myFixtures)
        {
            item.Value.Initialise();
        }
    }

    public void OnPlayEnd()
    {
        foreach (var item in myFixtures)
        {
			item.Value.Delete();
        }
        Delete();
    }
}
