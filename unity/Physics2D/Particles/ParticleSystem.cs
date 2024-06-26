﻿using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using System.Runtime.InteropServices;

/// <summary>
/// Class holding information about one particle. Note may be partially filled out depending on LPparticlesystem settings</summary>
public class Particle
{
    /// <summary>Position of the particle</summary>
    public Vector3 Position;
    /// <summary>Color of the particle</summary>
    public Color _Color;
    /// <summary>Remaining lifetime of the particle, < 0 = infinite, 0 = particle will be destroyed next step</summary>
    public float LifeTime;
    /// <summary>Pressure the particle is experiencing</summary>
    public float Weight;
    /// <summary>Velocity of the particle</summary>
    public Vector3 Velocity;
    /// <summary>Userdata value of the particle. Can be used for gameplay mechanics</summary>
    public int UserData;
}

/// <summary>
/// Class holding information about one particle/particle contact</summary>
public struct SystemPartPartContact
{
    /// <summary>Index of 1st particle involved in the collision</summary>
    public int ParticleAIndex;
    /// <summary>Index of 2nd particle involved in the collision</summary>
    public int ParticleBIndex;
    /// <summary>Userdata value of 1st particle involved in the collision</summary>
    public int ParticleAUserData;
    /// <summary>Userdata value of 2nd particle involved in the collision</summary>
    public int ParticleBUserData;
}

/// <summary>
/// Class holding information about one fixture/particle contact</summary>
public struct SystemFixPartContact
{
    /// <summary>index of the body involved in the collision</summary>
    public int BodyIndex;
    /// <summary>index of the fixture in the body involved in the collision</summary>
    public int FixtureIndex;
    /// <summary>index of the particle involved in the collision</summary>
    public int ParticleIndex;
    /// <summary>Userdata value of the particle involved in the collision</summary>
    public int ParticleUserData;
    /// <summary>Normal to the collision vector</summary>
    public Vector3 Normal;
    /// <summary>Weight or pressure of the collision</summary>
    public float Weight;
}


/// <summary>
/// Represents and manages a liquidfun particle system</summary>	
public class ParticleSystem : MonoBehaviour
{
    public static ParticleSystem Instance;
    private void Awake()
    {
        Instance = this;
    }

    private void Start()
    {
        Initialise(PhysicsWorld.Instance.GetPtr(), PhysicsWorld.Instance.DebugMessages, 0);
    }

    [Tooltip("particles or particle groups with this index will be created in this particle system")]
    public int Index;
    [Tooltip("Radius of all the particles in the system")]
    public float ParticleRadius = 0.1f;
    [Tooltip("How much particles loose their velocity")]
    public float Damping = 0.6f;
    [Tooltip("Scale of the world gravity in relation to this particle system. A higher value makes the simultion look smaller. Minus value will make the particles fall 'upwards'")]
    public float GravityScale = 1f;
    [Tooltip("Can particles be destroyed autmatically according to their age?")]
    public bool DestroyByAgeAllowed = true;
    public List<DrawParticleSystem> Drawers=new List<DrawParticleSystem>();
    [Tooltip("Limit for the amount of particles this particle system can contain." +
             "If limit is exceeded and DestroyByAgeAllowed is true oldest particles are destroyed 1st." +
             "If limit is exceeded and DestroyByAgeAllowed is false, new particles will not be added to the system" +
            " Value of 0 or less indicates no limit")]
    public int ParticleAmountLimit = 0;

    private bool GetPositions = true;
    [Tooltip("Should all the particles colour info be retrieved on Update")]
    public bool GetColors = true;
    [Tooltip("Should all the particles lifetime info be retrieved on Update")]
    public bool GetLifeTimes = false;
    [Tooltip("Should all the particles weight info be retrieved on Update")]
    public bool GetWeights = false;
    [Tooltip("Should all the particles velocity info be retrieved on Update")]
    public bool GetVelocities = false;
    [Tooltip("Should all the particles userdatas be retrieved on Update")]
    public bool GetUserData = false;
    [Tooltip("Should we update particle groups. IMPORTANT: Only needed if SplitGroups() is called")]
    public bool GetGroupData = false;

    public float SurfaceTensionNormalStrenght = 0.2f;
    public float SurfaceTensionPressureStrenght = 0.2f;
    public float ViscousStrenght = 1f;

    ///[SerializeField]
    //public LPParticle[] SavedParticles;

	public List<Particle> Particles;
    public ParticleGroup[] Groups;

    /// <summary>
    /// Work in progress</summary>
    public void Save()
    {
        //SavedParticles = new LPParticle[Particles.Length];
        //Particles.CopyTo(SavedParticles,0);
    }

    private IntPtr PartSysPtr;
    private PhysicsWorld physicsWorld;
    private float[] particlesCountArray;
    private float[] particleData;


    /// <summary>
    /// Get the pointer to the C++ object represented by this object (In this case it is the particle system object)</summary>
    public IntPtr GetPtr()
    {
        return PartSysPtr;
    }

    /// <summary>
    /// Creates the particle system in the physics simulation and creates any existing particle groups</summary>
    public void Initialise(IntPtr world, bool debug, int index)
    {
        physicsWorld = PhysicsWorld.Instance;
        if (Particles != null) Debug.Log(Particles.Count);
        Index = index;
        //PartSysPtr = LPAPIParticleSystems.CreateParticleSystem(world, ParticleRadius, Damping, GravityScale, Index);
        PartSysPtr = API_ParticleSystems.CreateParticleSystem2(world,ParticleRadius,Damping,GravityScale,Index,
        SurfaceTensionNormalStrenght,SurfaceTensionPressureStrenght,ViscousStrenght);
        API_ParticleSystems.SetDestructionByAge(PartSysPtr, DestroyByAgeAllowed);

        if (ParticleAmountLimit > 0)
        {
			API_ParticleSystems.SetMaxParticleCount(PartSysPtr,ParticleAmountLimit);
        }

		API_ParticleSystems.SetParticleSystemIndex(PartSysPtr,Index);

		if (debug)Debug.Log("Particle System Created at: 0x" + PartSysPtr.ToInt64());

        particlesCountArray = new float[1];
        Particles = new List<Particle>();
        particleData = new float[0];
    }

    /// <summary>
    /// Update the chosen particle data from the simulation and store it in this class</summary>
    public void UpdateData()
    {
        IntPtr particlesPointer = API_ParticleSystems.GetParticlesDetails(PartSysPtr, GetPositions, GetColors, GetLifeTimes
        , GetWeights, GetVelocities, GetUserData);

		Marshal.Copy (particlesPointer,particlesCountArray,0,1);
		int partsNum = (int)particlesCountArray[0];

        // Allocate or remove particles
        // Removal is done so that the count will be correct. Reusable pooled objects would be better if performance is a problem
        if (Particles.Count < partsNum)
        {
            while (Particles.Count < partsNum)
            {
                Particles.Add(new Particle());
            }
        }
        else if (partsNum == 0)
        {
            Particles.RemoveRange(0, Particles.Count);
        }
        else if (Particles.Count > partsNum)
        {
            Particles.RemoveRange(partsNum - 1, Particles.Count - partsNum - 1);
        }

        if (partsNum > 0)
        {
            int datanum = 0;

			if (GetPositions) datanum +=2;
			if (GetColors) datanum +=4;
			if (GetLifeTimes) datanum +=1;
			if (GetWeights) datanum +=1;
			if (GetVelocities) datanum +=2;
			if (GetUserData) datanum +=1;

            int numberOfCoordinates = (partsNum * datanum) + 1;
            if (particleData.Length < numberOfCoordinates)
            {
                particleData = new float[(int)(numberOfCoordinates*1.5f)];
            }
			Marshal.Copy(particlesPointer, particleData, 0, numberOfCoordinates);
			
			

            int curpos = 1;

            if (GetPositions)
            {
                for (int i = 0; i < partsNum; i++)
                {
					Particles[i].Position = new Vector3(particleData[curpos +(i*2)],particleData[curpos +(i*2)+1]);
                }
				curpos += partsNum*2;
            }

            if (GetColors)
            {
                for (int i = 0; i < partsNum; i++)
                {
					Particles[i]._Color = new Color(particleData[curpos +(i*4)]/255f,particleData[curpos +(i*4)+1]/255f
					        ,particleData[curpos +(i*4)+2]/255f,particleData[curpos +(i*4)+3]/255f);
                }
				curpos += partsNum*4;
            }
            if (GetLifeTimes)
            {
                for (int i = 0; i < partsNum; i++)
                {
					Particles[i].LifeTime =  particleData[curpos +i];
                }
                curpos += partsNum;
            }
            if (GetWeights)
            {
                for (int i = 0; i < partsNum; i++)
                {
					Particles[i].Weight =  particleData[curpos +i];			
                }
                curpos += partsNum;
            }
            if (GetVelocities)
            {
                for (int i = 0; i < partsNum; i++)
                {
					Particles[i].Velocity = new Vector3(particleData[curpos +(i*2)],particleData[curpos +(i*2)+1]);
                }
				curpos += partsNum*2;
            }
            if (GetUserData)
            {
                for (int i = 0; i < partsNum; i++)
                {
					Particles[i].UserData =  (int)particleData[curpos +i];
                }
            }

            if (GetGroupData)
            {
                GetGroupDataFromPlugin();
            }
        }
    }

    public ParticleGroup[] GetGroupDataFromPlugin()
    {
        int groupCount = API_ParticleSystems.GetParticleGroupCount(PartSysPtr);

        Groups = new ParticleGroup[groupCount];
        if (groupCount > 0)
        {
            IntPtr groupsPointer = API_ParticleSystems.GetParticleGroupPointers(PartSysPtr);

            IntPtr[] groupThingPtrs = new IntPtr[groupCount];
            Marshal.Copy(groupsPointer, groupThingPtrs, 0, groupCount);

            for (int i = 0; i < groupCount; i++)
            {
                Groups[i] = new ParticleGroup();
                Groups[i].SetThingPtr(groupThingPtrs[i]);
                //Debug.Log("Group " + i + " has " + Groups[i].GetParticleCount());
            }
        }

        return Groups;
    }

    public IntPtr GetLargestGroupDataFromPlugin()
    {
        return API_ParticleSystems.GetParticleGroupPointerForLargestGroup(PartSysPtr);
    }

    /// <summary>
    /// The particles positions and colours are updated in unitys update event handler method.
    /// This is so that this information is only fetched when it is needed (ie when you are going to draw the particles)
    /// If the frame rate slow this data will be fetched less and will help improve performance.
    /// This data is also stored between frames in the Particles field. You can access the data here by the particles index
    /// but it will not be 100% accurate to the simulation as SimulateUpdate and world->Step may be called more frequently </summary>
    /// 
	public void OnPlayVisualUpdate() 
    {
        UpdateData();
        foreach (var drawer in Drawers)
        {
            drawer.OnPlayVisualUpdate();
        }
    }


    /// <summary>
    /// Returns an array of the indices of every particle in this particle system within the shape passed to it
    /// Note that the 1st element of the array is the lenght of the array</summary>
    public int[] GetParticlesInShape(IntPtr shape, Transform tran)
    {
        IntPtr worldPtr = physicsWorld.GetPtr();
        IntPtr particlesPointer = API_ParticleSystems.GetParticlesInShape(worldPtr, PartSysPtr
                                                                           , shape, tran.position.x, tran.position.y
                                                                           , tran.rotation.eulerAngles.z);

        int[] particlesArray = new int[1];
        Marshal.Copy(particlesPointer, particlesArray, 0, 1);
        int partsNum = particlesArray[0];

        int[] particlePositions = new int[partsNum + 1];

        if (partsNum > 0)
        {
            Marshal.Copy(particlesPointer, particlePositions, 0, partsNum + 1);
        }
        return particlePositions;
    }

    /// <summary>
    /// Returns a List of all Particle-Fixture contacts in this particle system at the time it is called</summary>
    public List<SystemFixPartContact> GetBodyContacts()
    {
        List<SystemFixPartContact> contactslist = new List<SystemFixPartContact>();
        IntPtr fixpartcontactsPtr = API_ParticleSystems.GetParticleSystemBodyContacts(PartSysPtr);

        float[] contactsArray = new float[1];
        Marshal.Copy(fixpartcontactsPtr, contactsArray, 0, 1);

        int am = 7;
        int contsNum = (int)contactsArray[0];
        int lenght = (contsNum * am) + 1;

        if (contsNum > 0)
        {
			float[] contactdata= new float[lenght];
            Marshal.Copy(fixpartcontactsPtr, contactdata, 0, lenght);

            for (int i = 0; i < contsNum; i++)
            {
				contactslist.Add (new SystemFixPartContact()
                {
					ParticleIndex =  (int)contactdata[(i * am) + 1]
					,ParticleUserData =  (int)contactdata[(i * am) + 2]
					,BodyIndex =         (int)contactdata[(i * am) + 3]
					,FixtureIndex =  (int)contactdata[(i * am) + 4]
					,Normal = new Vector3(contactdata[(i * am) + 5]
					,contactdata[(i * am) + 6])
					,Weight = contactdata[(i * am) + 7]
                });
            }
        }
        return contactslist;
    }


    /// <summary>
    /// Returns a List of all Particle-Particle contacts in this particle system at the time it is called</summary>
    public List<SystemPartPartContact> GetParticleContacts()
    {
        List<SystemPartPartContact> contactslist = new List<SystemPartPartContact>();
        IntPtr partpartcontactsPtr = API_ParticleSystems.GetParticleSystemContacts(PartSysPtr);

        int[] contactsArray = new int[1];
        Marshal.Copy(partpartcontactsPtr, contactsArray, 0, 1);

        int contsNum = contactsArray[0];
        int lenght = (contsNum * 4) + 1;

        if (contsNum > 0)
        {
            int[] contactdata = new int[lenght];
            Marshal.Copy(partpartcontactsPtr, contactdata, 0, lenght);

            for (int i = 0; i < contsNum; i++)
            {
				contactslist.Add (new SystemPartPartContact()
                {
					 ParticleAIndex =  contactdata[(i * 4) + 1]
					,ParticleBIndex =  contactdata[(i * 4) + 2]
					,ParticleAUserData =  contactdata[(i * 4) + 3]
					,ParticleBUserData =  contactdata[(i * 4) + 4]
                });
            }
        }
        return contactslist;
    }

    /// <summary>
    /// Returns an array of LPParticle objects with selected information about selected particles</summary>
    /// <param name="indices">An array of ints indicating the indices of the particles you want to get the details of.
    /// Note that the 1st member of the array must be the total number of indices in the array. ie. the lenght of thr array -1</param>
	public Particle[] GetSelectedPartDetails(int[] indices,bool position,bool color,bool age,bool weight,bool velocity,bool userdata)
    {
        Particle[] ParticleData = new Particle[indices[0]];

		IntPtr particlesPointer = API_Particles.GetSelectedParticlesDetails(PartSysPtr,indices,position,color,age,weight,velocity,userdata);

        float[] particlesArray = new float[1];
		Marshal.Copy(particlesPointer, particlesArray, 0, 1);
        int partsNum = (int)particlesArray[0];

        if (partsNum > 0)
        {
            int datanum = 0;

            if (position) datanum += 2;
            if (color) datanum += 4;
            if (age) datanum += 1;
            if (weight) datanum += 1;
            if (velocity) datanum += 2;
            if (userdata) datanum += 1;

            int numberOfCoordinates = (partsNum * datanum) + 1;
            float[] pd = new float[numberOfCoordinates];
            Marshal.Copy(particlesPointer, pd, 0, numberOfCoordinates);

            for (int i = 0; i < partsNum; i++)
            {
                ParticleData[i] = new Particle();
            }

            int curpos = 1;

            if (position)
            {
                for (int i = 0; i < partsNum; i++)
                {
					ParticleData[i].Position = new Vector3(pd[curpos +(i*2)],pd[curpos +(i*2)+1]);
                }
				curpos += partsNum*2;
            }

            if (color)
            {
                for (int i = 0; i < partsNum; i++)
                {
					ParticleData[i]._Color = new Color(pd[curpos +(i*4)]/255f,pd[curpos +(i*4)+1]/255f
					                                ,pd[curpos +(i*4)+2]/255f,pd[curpos +(i*4)+3]/255f);
                }
				curpos += partsNum*4;
            }
            if (age)
            {
                for (int i = 0; i < partsNum; i++)
                {
					ParticleData[i].LifeTime =  pd[curpos +i];
                }
                curpos += partsNum;
            }
            if (weight)
            {
                for (int i = 0; i < partsNum; i++)
                {
					ParticleData[i].Weight =  pd[curpos +i];			
                }
                curpos += partsNum;
            }
            if (velocity)
            {
                for (int i = 0; i < partsNum; i++)
                {
					ParticleData[i].Velocity = new Vector3(pd[curpos +(i*2)],pd[curpos +(i*2)+1]);
                }
				curpos += partsNum*2;
            }
            if (userdata)
            {
                for (int i = 0; i < partsNum; i++)
                {
					ParticleData[i].UserData =  (int)pd[curpos +i];
                }
            }
        }

        return ParticleData;
    }
}
