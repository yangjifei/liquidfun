using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using static UnityEngine.ParticleSystem;

/// <summary>
/// This class uses unity's particle emitter to draw the particles in a particle system
/// It is designed to be a seperate modular element so you may implement your own drawer to suit your particular game</summary>
public class DrawParticleSystem : MonoBehaviour
{	
	[Tooltip("How big should the particles appear relative to their size in the simulation")]	
	public float ParticleDrawScale = 4f;
	[Tooltip("This drawer will draw particles in its parent particle system with the same userdata value as this")]
	public int DrawParticlesWithThisUserData = 0;
	protected UnityEngine.ParticleSystem.Particle[] particles = new UnityEngine.ParticleSystem.Particle[0];
	protected ParticleSystem sys;
	public bool debug;
    private UnityEngine.ParticleSystem ParticleSystemObj;
	
	protected void Start()
	{
		var main = GetComponent<UnityEngine.ParticleSystem>().main;
		main.startSize = new MinMaxCurve(ParticleSystem.Instance.ParticleRadius*ParticleDrawScale);
        ParticleSystemObj = GetComponent<UnityEngine.ParticleSystem>();
        particles = new UnityEngine.ParticleSystem.Particle[main.maxParticles];
		ParticleSystem.Instance.Drawers.Add(this);
    }
	
	/// <summary>
	/// Redraw the particles in the particle system</summary>
	/// <param name="partdata">An array of LPParticle structs, this is available in LPParticle system</param>
	public virtual void UpdateParticles(List<Particle> partdata)
	{	
        if (ParticleSystemObj.particleCount < partdata.Count) 
		{
            ParticleSystemObj.Emit(partdata.Count - ParticleSystemObj.particleCount);
            ParticleSystemObj.GetParticles(particles);
		}
		
		if (debug && particles.Length > 2)
		{
			Debug.Log ( "part 0 "+ particles[0].rotation +" part 1 "+ particles[1].rotation +" part 2 "+ particles[2].rotation);
		}
	
		for (int i=0; i < particles.Length; i ++)
		{		
            if (i > partdata.Count - 1)
			{
				particles[i].remainingLifetime = 0f;
			}
			else
			{
				particles[i].position  = partdata[i].Position;
				particles[i].startColor = partdata[i]._Color;
			}		
		}
		
        ParticleSystemObj.SetParticles(particles);
	}
	
	/// <summary>
	/// Redraw the particles in the particle system, but only ones with a certain userdata value</summary>
	/// <param name="partdata">An array of LPParticle structs, this is available in LPParticle system</param>
	protected void UpdateParticles(List<Particle> allpartdata,bool multi)
	{
		List<Particle> partsforme = new List<Particle>();
		
		foreach (Particle part in allpartdata)
		{
			if (part.UserData == DrawParticlesWithThisUserData)
			{
				partsforme.Add(part);
			}
		}
		
		UpdateParticles(partsforme);
	}
#if UNITY_EDITOR
	private void Reset()
    {
		if (GetComponent<UnityEngine.ParticleSystem>()==null)
		{
            gameObject.AddComponent<UnityEngine.ParticleSystem>();
		}
		var	 shape = GetComponent<UnityEngine.ParticleSystem>().shape;
		shape.enabled = false;
        var emission = GetComponent<UnityEngine.ParticleSystem>().emission;
		emission.rateOverTime = 0f;
        var main = GetComponent<UnityEngine.ParticleSystem>().main;
		main.simulationSpace = ParticleSystemSimulationSpace.World;
        GetComponent<Renderer>().sharedMaterial = UnityEditor.AssetDatabase.GetBuiltinExtraResource<Material>("Default-ParticleSystem.mat");
    }
    public void OnPlayVisualUpdate()
    {
		UpdateParticles(ParticleSystem.Instance.Particles, true);
    }
#endif
}
