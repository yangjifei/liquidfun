using UnityEngine;
using System.Collections;
using UnityEditor;

[CustomEditor(typeof(FixturePoly))]
public class FixturePolyEditor : ShapeEditor
{
	public override void OnInspectorGUI()
	{
		DrawPointsUI();
	}
}
