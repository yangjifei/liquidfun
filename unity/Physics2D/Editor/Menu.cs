using UnityEditor;
using UnityEngine;
using System.IO;

public class Menu : MonoBehaviour 
{	
	[MenuItem ("Component/Physics2D/Body")] 
	static void AddaBody()
	{ 
		if (Selection.activeGameObject != null)
		{
			if (Selection.activeGameObject.GetComponent<Body>() == null) 
			{	
				Undo.AddComponent<Body>(Selection.activeGameObject);	
			}
			else
			{
				Debug.LogError("This gameobject already has a body component (only one is allowed per unity gameobject)");
			}
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	
	//Add fixtures
	[MenuItem  ("Component/Physics2D/Collider/Circle")] 
	static void AddaCircle()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<FixtureCircle>(Selection.activeGameObject);	
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
		
	//box
	/*
	[MenuItem( "GameObject/Create Other/Physics2D/Collider/Box" ) ]
	static void CreateaBox()
	{ 
		GameObject box = new GameObject("Box");
		box.AddComponent<LPFixtureBox>();
	}*/
		
	[MenuItem  ("Component/Physics2D/Collider/Box")] 
	static void AddaBox()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<FixtureBox>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}	
	}
	
	[MenuItem  ("Component/Physics2D/Collider/Polygon")] 
	static void AddaPoly()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<FixturePoly>(Selection.activeGameObject);	
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}	
	[MenuItem  ("Component/Physics2D/Collider/Edge")] 
	static void AddaChainShape()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<FixtureChainShape>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}	
	}
	
	//Add particles
	[MenuItem  ("Component/Physics2D/Particle Group/Circle")] 
	static void AddaParticleGroupCircle()
	{ 	
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<ParticleGroupCircle>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Particle Group/Square")] 
	static void AddaParticleGroupBox()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<ParticleGroupBox>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Particle Group/Polygon")] 
	static void AddaParticleGroupPoly()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<ParticleGroupPoly>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
			
	//Add Joints
	[MenuItem  ("Component/Physics2D/Joint/Weld")] 
	static void AddajointWeld()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointWeld>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Revolute")] 
	static void AddajointRevolute()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointRevolute>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Prismatic")] 
	static void AddajointPrismatic()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointPrismatic>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Rope")] 
	static void AddajointRope()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointRope>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Distance")] 
	static void AddajointDistance()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointDistance>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Pulley")] 
	static void AddajointPulley()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointPulley>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Wheel")] 
	static void AddajointWheel()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointWheel>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Mouse")] 
	static void AddajointMouse()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointMouse>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}
	[MenuItem  ("Component/Physics2D/Joint/Friction")] 
	static void AddajointFriction()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointFriction>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}		
	[MenuItem  ("Component/Physics2D/Joint/Gear")] 
	static void AddajointGear()
	{ 
		if (Selection.activeGameObject != null)
		{
			Undo.AddComponent<JointGear>(Selection.activeGameObject);
		}
		else
		{
			Debug.LogError("No gameobject selected");
		}
	}	
	
	
	//Create Materials
	[MenuItem  ("Assets/Create/PLParticleMaterial")] 
	static void AddaPartMat()
	{ 		
		AddAnAsset("/PLParticleMaterial",".asset",typeof(ParticleMaterial));
	}
	
	[MenuItem  ("Assets/Create/PLParticleGroupMaterial")] 
	static void AddaGroupMat()
	{ 		
		AddAnAsset("/PLParticleGroupMaterial",".asset",typeof(ParticleGroupMaterial));
	}
	
	private static void AddAnAsset(string name,string ext,System.Type type)
	{
		int iter = 0;
		string path = GetCurrentPath()+name+iter.ToString()+ext;
		while(File.Exists(path))
		{
			iter++;
			path = GetCurrentPath()+name+iter.ToString()+ext;
		}
		AssetDatabase.CreateAsset(ScriptableObject.CreateInstance(type),path);
	}
	
	private static string GetCurrentPath()
	{
		string path = "Assets";
		foreach (UnityEngine.Object obj in Selection.GetFiltered(typeof(UnityEngine.Object), SelectionMode.Assets))
		{
			path = AssetDatabase.GetAssetPath(obj);
			if (File.Exists(path))
			{
				path = Path.GetDirectoryName(path);
			}
			return path;
		}
		return path;
	}
}
