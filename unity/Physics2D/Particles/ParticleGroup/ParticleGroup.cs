using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;

#if UNITY_EDITOR
using UnityEditor;
#endif

/// <summary>
/// Represents particle group in the liquidfun simulation</summary>
public class ParticleGroup : PolygonThing, IPlayAble
{
    public bool Initialised = false;
	
    [Tooltip("The partcle physics material for this particle group. Drag a LPparticleMaterial scriptable object in here")]
    public ParticleMaterial ParticlesMaterial;
    [Tooltip("The particle group physics material for this particle group. Drag a LPparticleGroupMaterial scriptable object in here")]
    public ParticleGroupMaterial GroupMaterial;
    [Tooltip("Color of all the particles created in this group")]
    public Color _Color = Colors.DefaultParticleCol;
    [Tooltip("This particle group will be created in the particle system with this index")]
    public int ParticleSystemImIn = 0;
    [Tooltip("Strenght of forces between the particles. Affected by the particles material flags, eg. elastic")]
    public float Strenght = 1f;
    [Tooltip("Angular velocity this particle group should be created with")]
    public float AngularVelocity = 0f;
    [Tooltip("Linear velocity this particle group should be created with")]
    public Vector2 LinearVelocity = Vector2.zero;
    [Tooltip("Lifetime particles should start with. They will be deleted when their lifetime runs out. Value of 0 indicates infinite lifetime")]
    public float LifeTime = 0.0f;
    [Tooltip("What distance to space between the particles when creating the group. Value of 0 means distance will be the same as particle diamater")]
    public float Stride = 0;
    [Tooltip("Should this particle group be created when the game play?")]
    public bool SpawnOnPlay = true;
    [Tooltip("Userdata value for particles in this group. Use this to denote gameplay properties of particles. eg acid, lava")]
    public int UserData = 0;

    private ParticleSystem sys;

    /// <summary>
    /// Get the int representing this particles material flags.</summary>
    private int getPartNum()
    {
        Int32 partnum = 0;
        if (ParticlesMaterial != null)
        {
            partnum = ParticlesMaterial.GetInt();
        }
        return partnum;
    }

    /// <summary>
    /// Get the int representing this particles group material flags.</summary>
    private int getGroupNum()
    {
        Int32 groupnum = 0;
        if (GroupMaterial != null)
        {
            groupnum = GroupMaterial.GetInt();
        }
        return groupnum;
    }

    /// <summary>If the shape you attempt to make is complex log an error</summary>	
    protected override void LogComplex()
    {
        Debug.LogError("Particle Group # ? is complex! ie. has self intersecting edges. Creating default shape instead"); //HACK		
    }

    /// <summary>Create this particle group in the simulation</summary>	
    protected void Initialise()
    {
        sys = ParticleSystem.Instance;
        IntPtr shape = GetShape();
		B2ObjectPtr = API_ParticleGroups.CreateParticleGroup(sys.GetPtr(),getPartNum(),getGroupNum(),0f,Strenght,AngularVelocity
		                                                   ,LinearVelocity.x,LinearVelocity.y
		                                                   ,shape
		                                                   ,(int)(_Color.r*255f),(int)(_Color.g*255f),(int)(_Color.b*255f),(int)(_Color.a*255f)
														   ,Stride,LifeTime,UserData);
        API_Utility.ReleaseShape(shape);

		if (SubPtrs !=null && ParticlesMaterial !=null && (ParticlesMaterial.elastic || ParticlesMaterial.spring))
        {
            foreach (IntPtr groupptr in SubPtrs)
            {
                API_ParticleGroups.JoinParticleGroups(sys.GetPtr(), B2ObjectPtr, groupptr);
            }
        }

        Initialised = true;
    }

    /// <summary>Create this particle group in the simulation with a shape pointer you already have
    /// Note: Used for concave fixtures or fixtures with more than 8 vertices
    /// They are broken up into several fixtures </summary>	
    protected override void InitialiseWithShape(IntPtr shape)
    {
		SubPtrs.Add( API_ParticleGroups.CreateParticleGroup(sys.GetPtr(),getPartNum(),getGroupNum(),0f,Strenght,AngularVelocity
		                                               ,LinearVelocity.x,LinearVelocity.y
		                                               ,shape
		                                               ,(int)(_Color.r*255f),(int)(_Color.g*255f),(int)(_Color.b*255f),(int)(_Color.a*255f)
		                                               ,Stride,LifeTime,UserData)
                     );
    }

    /// <summary>Delete this particle group. In the simulation and in unity</summary>	
    public override void Delete()
    {
        API_ParticleGroups.DeleteParticlesInGroup(B2ObjectPtr);
        Initialised = false;
    }

    /// <summary>Get the velocity of particle group</summary>
    public Vector2 GetVelocity()
    {
        IntPtr particlesPointer = API_ParticleGroups.GetParticleGroupVelocity(B2ObjectPtr);

        float[] particlesArray = new float[2];
        Marshal.Copy(particlesPointer, particlesArray, 0, 2);

        return new Vector2(particlesArray[0], particlesArray[1]);
    }

    /// <summary>Get the position of particle group Note: only works with rigid groups</summary>
    public Vector2 GetPosition()
    {
        IntPtr particlesPointer = API_ParticleGroups.GetParticleGroupPosition(B2ObjectPtr);

        float[] particlesArray = new float[2];
        Marshal.Copy(particlesPointer, particlesArray, 0, 2);

        return new Vector2(particlesArray[0], particlesArray[1]);
    }

    /// <summary>Get the center of particle group</summary>
    public Vector2 GetCenter()
    {
        if (B2ObjectPtr == IntPtr.Zero)
        {
            return new Vector2(999, 999);
        }
        IntPtr particlesPointer = API_ParticleGroups.GetParticleGroupCentroid(B2ObjectPtr);

        float[] particlesArray = new float[2];
        Marshal.Copy(particlesPointer, particlesArray, 0, 2);

        return new Vector2(particlesArray[0], particlesArray[1]);
    }

    /// <summary>Determine what colour to draw this particle groups gizmo</summary>
    protected Color GetColors()
    {
		#if UNITY_EDITOR
        if (Selection.Contains(gameObject))
        {
            return Colors.Selected;
        }
        #endif
        return Colors.ParticleGroup;
    }

    protected virtual IntPtr GetShape()
    {
        return (IntPtr)(-1);
    }


    public int GetParticleCount()
    {
        if (Initialised)
        {
        	return API_ParticleGroups.GetParticlesInGroupCount(this.GetPtr());
    	}
        return 0;
    }

    internal void SetThingPtr(IntPtr intPtr)
    {
        if (intPtr == IntPtr.Zero)
        {
            Debug.Log("ThingPtr set to zero... exception here");
            throw new Exception();
        }
        B2ObjectPtr = intPtr;
    }

    public void OnPlayAwake()
    {
        Initialise();
    }

    public void OnPlayEnd()
    {
        Delete();
    }
}
