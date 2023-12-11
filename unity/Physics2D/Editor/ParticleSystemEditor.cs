using UnityEngine;
using System.Collections;
using UnityEditor;

[CustomEditor(typeof(ParticleSystem))]
public class ParticleSystemEditor : Editor
{
	public override void OnInspectorGUI()
	{
		DrawDefaultInspector();
		
		ParticleSystem sys = (ParticleSystem)target;
		if(GUILayout.Button("Save"))
		{
			sys.Save();
		}
	}
}