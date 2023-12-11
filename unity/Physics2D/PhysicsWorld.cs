using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using UnityEngine.UIElements;

/// <summary>
/// Represents and manages the liquidfun physics simulation world.
/// You will need an instance of this component on a gameobject in your scene in order for the physics simulation to run.</summary>
[DefaultExecutionOrder(-1)]
public class PhysicsWorld : SceneSingleton<PhysicsWorld>
{
    [Tooltip("Gravity Vector in the world")]	
	public Vector2 Gravity = new Vector2(0f, -9.81f);	
	[Tooltip("How much time should pass in the simulation every time it steps")]	
	public float TimeStep = 1.0f / 60.0f;	
	[Tooltip("How accurate body velocity calculations should be. Note: More accurate = more expensive")]	
	public int VelocityIterations = 6;	
	[Tooltip("How accurate body position calculations should be. Note: More accurate = more expensive ")]	
	public int m_positionIterations = 2;	
	[Tooltip("Should non-error debug messages appear in unity editor ")]	
	public bool DebugMessages = true;	
	[Tooltip("Override the recommended number of particle iterations")]	
	public bool OverrideParticleIterations;		
	[Tooltip("If overriding use this many particle iterations. Note: less particle iterations can dramatically improve performance. but does so at the cost of a less accurate, more volatile simulation")]
	public int ParticleIterationsOverride = 2;	
	[Tooltip("Use a contact listener. Will reduce performance especially if you have particles with contact listener flags set")]
	public bool UseContactListener = false;
	private int m_particleIterations = 2;
	
	private IntPtr worldPtr;
	
	/// <summary>
	/// Get the pointer to the C++ object represented by this object (In this case it is the world object)</summary>
	public IntPtr GetPtr()
	{
		return worldPtr;
    }
    /// <summary>
    /// Sets up the physics world and the bodies, particle systems and joints in it.
    /// This is called on Awake() so you can implement your code on Start() and the liquidfun stuff will be ready</summary>				
    protected override void Awake()
    {
        base.Awake();
        //Always turn off debug messages in a build (Debug.Log writes to a log file and costs performance)
        if (!Application.isEditor && !Debug.isDebugBuild)
        {
            DebugMessages = false;
        }
    }
    protected void Start() {
        //Create World
        worldPtr = API_World.CreateWorld(Gravity.x, Gravity.y);
        if (DebugMessages) Debug.Log("World Created at: 0x" + worldPtr.ToInt64());
        //Create contact listener c# object
        ContactListener = new ContactListener();

        //Initialise Contact Listener
        if (UseContactListener)
        {
            ContactListener.Initialise(worldPtr);
        }
        //Set or Determine recommended number of particle iterations
        if (OverrideParticleIterations)
        {
            m_particleIterations = ParticleIterationsOverride;
        }
        else
        {
            m_particleIterations = API_ParticleSystems.GetParticleIterations(Gravity.magnitude, ParticleSystem.Instance.ParticleRadius, TimeStep);
            if (DebugMessages) Debug.Log("Recommended number of particle iterations is "+ m_particleIterations.ToString());
        }

    }
    #region Body
    public Dictionary<int,Body> allBodies = new Dictionary<int, Body>();
	private int bodiesIndex = 0;
	
	/// <summary>
	/// Pass an LPBody in here after creation to add it to the list of all the bodies in the world and assign it an index</summary>
	public int AddBody(Body body)
	{
		allBodies.Add(bodiesIndex,body);
		bodiesIndex++;
		return bodiesIndex -1;
	}

	/// <summary>
	/// Pass the index of an LPBody object in here in order to remove it from the list of all bodies in the world</summary>
	public void RemoveBody(int index)
	{
		allBodies.Remove(index);
    }
    public Body TestPointForBody(float x, float y)
    {
        int bodyIndex = API_World.WorldTestPointForBody(worldPtr, x, y);
        if (bodyIndex == -1)
        {
            return null;
        }
        return allBodies[bodyIndex];
    }
    #endregion

    #region Things
    protected Dictionary<Type,List<IPlayAble>> allThings = new Dictionary<Type, List<IPlayAble>>
            {
                { typeof(Thing), new List<IPlayAble>() },
                { typeof(Body), new List<IPlayAble>() },
                { typeof(Joint), new List<IPlayAble>() },
                { typeof(ParticleGroup), new List<IPlayAble>() }
            };
    protected void FillAllThing()
    {
        this.GetComponentsInChildren<Thing>().HandleEach(v => allThings[typeof(Thing)].Add(v));
        this.GetComponentsInChildren<Body>().HandleEach(v => allThings[typeof(Body)].Add(v));
        this.GetComponentsInChildren<Joint>().HandleEach(v => allThings[typeof(Joint)].Add(v));
        this.GetComponentsInChildren<ParticleGroup>().HandleEach(v => allThings[typeof(ParticleGroup)].Add(v));
    }
    protected void ClearAllThing()
    {
        allThings[typeof(Thing)].Clear();
        allThings[typeof(ParticleGroup)].Clear();
        allThings[typeof(Joint)].Clear();
        allThings[typeof(Body)].Clear();
    }
    #endregion

    #region Play

    private bool isPlaying = false;
    public ContactListener ContactListener { get; private set; }
    public void StartSimulate()
    {
        FillAllThing();
        foreach (var bod in allThings[typeof(Thing)])
        {
            bod.OnPlayAwake();
        }
        foreach (var bod in allThings[typeof(Body)])
        {
            bod.OnPlayAwake();
        }
        if (DebugMessages) Debug.Log(allThings[typeof(Body)].Count + " Bodies created");

        foreach (var bod in allThings[typeof(Joint)])
        {
            bod.OnPlayAwake();
        }
        foreach (var bod in allThings[typeof(ParticleGroup)])
        {
            bod.OnPlayAwake();
        }
        isPlaying=true;
    }

    /// <summary>
    /// Update the position and rotation of non static bodies in the world.
    /// The bodies positions and angles are updated in unitys update event handler method.
    /// This is so that this information is only fetched when it is needed (ie when you are going to draw the item associated with the body)
    /// If the frame rate slow this data will be fetched less and will help improve performance.</summary>
    public void OnPlayVisualUpdate()
    {
        List<Body> bodies = new List<Body>();

        foreach (KeyValuePair<int, Body> bod in allBodies)
        {
            if (bod.Value.shouldUpdate())
            {
                bodies.Add(bod.Value);
            }
        }

        if (bodies.Count > 0)
        {
            IntPtr[] ptrs = new IntPtr[bodies.Count];

            for (int i = 0; i < bodies.Count; i++)
            {
                ptrs[i] = bodies[i].GetPtr();
            }

            IntPtr bodinfoptr = API_Body.GetAllBodyInfo(ptrs, bodies.Count);

            float[] bodinfo = new float[bodies.Count*3];
            Marshal.Copy(bodinfoptr, bodinfo, 0, bodies.Count*3);

            for (int i = 0; i < bodies.Count; i++)
            {
                bodies[i].PhysicsWorldUpdate(bodinfo[i*3]
                                      , bodinfo[(i*3)+1]
                                      , bodinfo[(i*3)+2]

                );
            }
        }
        ParticleSystem.Instance.OnPlayVisualUpdate();
    }
    void SimulateUpdate()
    {
        API_World.StepWithParticleIterations(worldPtr, TimeStep, VelocityIterations, m_positionIterations, m_particleIterations);
        if (UseContactListener)
        {
            ContactListener.FetchContactInfo();
        }
    }
    public void EndSimulate()
    {
        isPlaying=false;
        foreach (var bod in allThings[typeof(ParticleGroup)])
        {
            bod.OnPlayEnd();
        }
        foreach (var bod in allThings[typeof(Joint)])
        {
            bod.OnPlayEnd();
        }
        foreach (var bod in allThings[typeof(Body)])
        {
            bod.OnPlayEnd();
        }
        foreach (var bod in allThings[typeof(Thing)])
        {
            bod.OnPlayEnd();
        }
        ClearAllThing();
        //Initialise Contact Listener
        if (UseContactListener)
        {//TODO 
            ContactListener = null;
        }
    }

    #endregion

    #region Update


    /// <summary>
    /// The physics world is 'stepped' on SimulateUpdate
    /// Also if the contact listener is active it is updated at this time</summary>	
    /// may be more than one call at one frame
    private void FixedUpdate()
    {
        if (isPlaying)
        {
            SimulateUpdate();
        }
    }
    private void Update()
    {
        if (isPlaying)
        {
            OnPlayVisualUpdate();
        }
    }
    #endregion
}
