using UnityEngine;
using System.Collections;
using UnityEditor;


[CustomEditor(typeof(FixtureChainShape))]
public class ChainShapeEditor : ShapeEditor
{
	public override void OnInspectorGUI()
	{
		DrawPointsUI();
	}
}



