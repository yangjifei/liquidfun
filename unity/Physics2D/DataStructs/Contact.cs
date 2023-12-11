using UnityEngine;
using System.Collections;

//This class contains information about a fixture / fixture contact
public struct ContactFixFix
{
	public int BodyAIndex;
	public int FixtureAIndex;
	
	public int BodyBIndex;
	public int FixtureBIndex;
	
	public Vector3 ManifoldPoint1;
	public Vector3 ManifoldPoint2;
	
	public Vector3 Normal;
	
	public bool IsTouching;
}

//This class contains information about a particle / fixture contact
public struct ContactPartFix
{
	public int ParticleSystemIndex;
	public int ParticleIndex;
	
	public int BodyIndex;
	public int FixtureIndex;
		
	public Vector3 Normal;
}

//This class contains information about a particle / particle contact
public struct ContactPartPart
{
	public int ParticleSystemIndex;
	public int ParticleAIndex;
	public int ParticleBIndex;	
}