using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using Unity.VisualScripting;

/// <summary>
///The contact listener class stores information about contacts.
///There are 2 kinds of conatcts in liquidfun, contacts between 2 fixtures, contacts between 2 particles
///and contacts between a a fixture and a particle.</summary>
public class ContactListener 
{
	private IntPtr ContactListenerPtr;

	/// <summary>
	/// Array of contact data for fixture / fixture contacts that took place during the last step. This is updated on SimulateUpdate</summary>	
	public Dictionary<long, ContactFixFix> FixtureFixtureContacts;
    public Dictionary<long, ContactFixFix> BodyBodyContacts;
    /// <summary>
    /// Array of contact data for fixture / particle contacts that took place during the last step. This is updated on SimulateUpdate</summary>
    public Dictionary<long, ContactPartFix> ParticleFixtureContacts;
    public Dictionary<long, ContactPartFix> ParticleBodyContacts;
    /// <summary>
    /// Array of contact data for particle / particle contacts that took place during the last step. This is updated on SimulateUpdate</summary>
    public Dictionary<long, ContactPartPart> ParticleParticleContacts;
	
	private int ff = 11;
	private int pf = 6;
	private int pp = 3;
	
	/// <summary>
	/// Get the pointer to the C++ object represented by this object (in this case the contact listener)</summary>
	public IntPtr GetPtr()
	{
		return ContactListenerPtr;
	}
	
	/// <summary>
	/// Create a contact listener object in the simulation</summary>
	public void Initialise(IntPtr worldptr)
	{
		ContactListenerPtr = API_Contacts.SetContactListener(worldptr);	
	}
	
	private bool floattoBool(float input)
	{
		if(input == 1f) return true;
		else return false;
	}
	
	/// <summary>
	/// Get the latest contact info from the simulation and parse that infor into easily readable arrays of structs</summary>
	public void FetchContactInfo()
	{
		IntPtr contactinfo = API_Contacts.UpdateContactListener(ContactListenerPtr);
		
		//find out how many contacts there were
		float[] info = new float[3];
		Marshal.Copy (contactinfo,info,0,3);
		int fixfixnum = (int)info[0];  
		int fixpartnum = (int)info[1];
		int partpartnum = (int)info[2];  //Debug.Log("fixfix "+fixfixnum +" fixpart "+fixpartnum+ " partpart "+partpartnum );
		int totalnum = 3+ fixfixnum*ff + fixpartnum*pf + partpartnum*pp;
		float[] allinfo = new float[totalnum];
		Marshal.Copy (contactinfo,allinfo,0,totalnum);
		
		//Parse contacts into structsS
		FixtureFixtureContacts = new Dictionary<long, ContactFixFix>(fixfixnum);
		BodyBodyContacts = new Dictionary<long, ContactFixFix>();
		for (int i = 0; i < fixfixnum; i++)
		{
			var c = new ContactFixFix
			{
				 BodyAIndex = (int)allinfo[3+(i*ff)]
				,BodyBIndex = (int)allinfo[4+(i*ff)]
				,FixtureAIndex = (int)allinfo[5+(i*ff)]
				,FixtureBIndex = (int)allinfo[6+(i*ff)]
				,ManifoldPoint1 = new Vector3(allinfo[7+(i*ff)],allinfo[8+(i*ff)])
				,ManifoldPoint2 = new Vector3(allinfo[9+(i*ff)],allinfo[10+(i*ff)])
				,Normal = new Vector3(allinfo[11+(i*ff)],allinfo[12+(i*ff)])
				,IsTouching = floattoBool(allinfo[12+(i*ff)])
			};
            FixtureFixtureContacts.Add(c.FixtureAIndex<<32+c.FixtureBIndex, c);
            BodyBodyContacts.TryAdd(c.BodyAIndex<<32+c.FixtureBIndex, c);
        }
		
		int start = 3+(fixfixnum*ff);
		ParticleFixtureContacts = new Dictionary<long, ContactPartFix>(fixpartnum);
		ParticleBodyContacts = new Dictionary<long, ContactPartFix>();
		for (int i = 0; i < fixpartnum; i++)
		{
			var c = new ContactPartFix
			{
				ParticleSystemIndex = (int)allinfo[start+(i*pf)]
				,ParticleIndex = (int)allinfo[start+(i*pf)+1]
				,BodyIndex = (int)allinfo[start+(i*pf)+2]
				,FixtureIndex = (int)allinfo[start+(i*pf)+3]
				,Normal = new Vector3((int)allinfo[start+(i*pf)+4],(int)allinfo[start+(i*pf)+5])
			};
			ParticleFixtureContacts.Add(c.ParticleIndex<<32+c.FixtureIndex, c);
            ParticleBodyContacts.TryAdd(c.ParticleIndex<<32+c.BodyIndex, c);
        }
		
		start = 3+(fixfixnum*ff)+(fixpartnum*pf);
		ParticleParticleContacts = new Dictionary<long, ContactPartPart>(partpartnum);
		for (int i = 0; i < partpartnum; i++)
		{
			var c = new ContactPartPart
			{
				 ParticleSystemIndex = (int)allinfo[start+(i*pp)]
				,ParticleAIndex = (int)allinfo[start+(i*pp)+1]
				,ParticleBIndex = (int)allinfo[start+(i*pp)+2]
				//,Normal = new Vector3((int)allinfo[start+(i*pp)+3],(int)allinfo[start+(i*pp)+4])
			};
            ParticleParticleContacts.Add(c.ParticleAIndex<<32+c.ParticleBIndex, c);
        }
	}
}
