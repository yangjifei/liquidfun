using UnityEngine;
using System.Collections;
using UnityEditor;

[CustomEditor(typeof(ParticleGroupPoly))]
public class ParticleGroupPolyEditor : ShapeEditor
{
	public override void OnInspectorGUI()
	{
		DrawPointsUI();
	}
}