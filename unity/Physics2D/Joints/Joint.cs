using UnityEngine;
using System;

public abstract class Joint : B2Object,IPlayAble
{
    [Tooltip("Should this joint spawn on play")]
    public bool SpawnOnPlay = true;
	[Tooltip("Gameobject with 1st body attached to this joint")]
	public GameObject BodyA;
	[Tooltip("Gameobject with 2nd body attached to this joint")]
	public GameObject BodyB;
	[Tooltip("Should the bodies connected by this joint collide with each other?")]
	public bool CollideConnected = false;
	
	protected PhysicsWorld physicsWorld;

    public bool initialised = false;
	
	/// <summary>Create this joint in the simulation</summary>	
	public void Initialise(PhysicsWorld world)
	{
        physicsWorld = world;
		if (BodyA !=null && BodyB !=null && BodyA.GetComponent<Body>() != null && BodyB.GetComponent<Body>() != null)
		{
            if (BodyA.GetComponent<Body>().Initialised && BodyB.GetComponent<Body>().Initialised)
            {
			    Initialise2(physicsWorld.GetPtr());
                initialised = true;
            }
		}
		else Debug.LogError("The " + gameObject.name + " Joint must be assigned 2 Bodies to connect in order to be created");
	}
	
	protected abstract void Initialise2(IntPtr world);
	
	/// <summary>Delete this joint, in the simulation and in unity</summary>	
	public override void Delete()
	{
		API_Joint.DeleteJoint(physicsWorld.GetPtr(),B2ObjectPtr);
	}

    internal void SetPhysicsWorld(PhysicsWorld physicsWorld)
    {
        this.physicsWorld = physicsWorld;
    }

    public void OnPlayAwake()
    {
        Initialise(PhysicsWorld.Instance);
    }

    public void OnPlayEnd()
    {
        Delete();
    }
}
