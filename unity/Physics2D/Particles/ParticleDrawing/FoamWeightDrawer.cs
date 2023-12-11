using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class FoamWeightDrawer : DrawParticleSystem
{
	public Color Foam;
	public Color Liquid;
	
	public AnimationCurve curve;
		
	public override void UpdateParticles(List<Particle> partdata)
	{	
        if (GetComponent<UnityEngine.ParticleSystem>().particleCount < partdata.Count) 
		{
            GetComponent<UnityEngine.ParticleSystem>().Emit(partdata.Count - GetComponent<UnityEngine.ParticleSystem>().particleCount);
            GetComponent<UnityEngine.ParticleSystem>().GetParticles(particles);
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
				particles[i].startColor = Color.Lerp(Foam,Liquid,curve.Evaluate( partdata[i].Weight));
			}		
		}

        GetComponent<UnityEngine.ParticleSystem>().SetParticles(particles);
	}
}

