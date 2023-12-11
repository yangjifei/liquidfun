using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class WeightAndColorDrawer : DrawParticleSystem
{
	public Color AddColor = Color.white;
	public Color SubtractColor = Color.black;
	
	public AnimationCurve curve;
	
	public float divisor = 5f;
	public float threshold = 0.8f;
	
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
				
				float val = 1- ( curve.Evaluate(partdata[i].Weight/divisor));
				
				if (val < threshold)
				{
					particles[i].startColor = Color.Lerp(partdata[i]._Color - SubtractColor,partdata[i]._Color ,val/threshold) ;
				}
				else
				{
					particles[i].startColor = Color.Lerp(partdata[i]._Color,partdata[i]._Color + AddColor,(val-threshold)/(1f-threshold));
				}				
			}		
		}
        GetComponent<UnityEngine.ParticleSystem>().SetParticles(particles);
	}
}
