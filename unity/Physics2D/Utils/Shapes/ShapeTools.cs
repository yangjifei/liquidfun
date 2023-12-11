using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

public struct Line
{
	public Vector3 P1;
	public Vector3 P2;
}

public static class ShapeTools
{		
	public static IntPtr Initialise(Vector3[] plist)
	{
		return API_Shape.GetPolygonShapeDef(GetfloatArray(plist));
	}
	
	//Check if shape is complex by checking if each non-consecutive line intersects
	public static bool CheckComplex(Vector3[] plist)
	{
		if (plist.Length > 3)
		{
			for (int a = 0; a < plist.Length; a++)
			{
				int index2 = a+1;
				if (index2 == plist.Length) index2 = 0;
				
				Line lineA = new Line()
				{
				P1 = plist[a]
				,P2 = plist[index2]
				};
				
				for (int b = 0; b < plist.Length; b++)
				{			
                 	if (b == a || b == a+1 || b == a-1 ) continue;
					if (a==0 && b == plist.Length -1 ) continue;
					if (a==plist.Length -1 && b == 0 ) continue;
					
					int indexb2 = b+1;		
					if (indexb2 == plist.Length) indexb2 = 0;
					
					Line lineB = new Line()
					{
                        P1 = plist[b]
                        ,P2 = plist[indexb2]
					};
					if (DoLinesIntersect(lineA,lineB)) return true;   
                }
			}
		}
		return false;
	}
	
	//Check if two lines intersect using cross product
	public static bool DoLinesIntersect(Line line1, Line line2)
	{
		if (IsCrossProductPos(line1.P1,line1.P2,line2.P1) != IsCrossProductPos(line1.P1,line1.P2,line2.P2) && 
		    IsCrossProductPos(line2.P1,line2.P2,line1.P1) != IsCrossProductPos(line2.P1,line2.P2,line1.P2) ) 
		    return true;
				
		return false;
    }
	
	//Return whether cross product of 3 points is positive or negative
	public static bool IsCrossProductPos(Vector3 p1, Vector3 p2, Vector3 test)
	{
		if( ((p2.x - p1.x)*(test.y - p2.y)) - ((p2.y - p1.y)*(test.x - p2.x)) >0f )return true;
		return false;
	}
	
	//Check if shape is convex using the sum over edges
    public static bool CheckAntiClockwise(Vector3[] plist)
	{
		float cw = 0;
		for (int i = 0; i < plist.Length; i++)
		{
			Vector3 pointA = plist[i];	
			Vector3 pointB;	
			if (i == plist.Length-1)
			{
				pointB = plist[0];
			}
			else
			{
				pointB = plist[i+1];
			}
			
			cw -= ((pointA.x - pointB.x)*(pointA.y + pointB.y));
		}
		if (cw < 0f) return true;
		
		return false;
	}
	
	//Check if shape is convex using the cross product
	public static bool CheckConvex(Vector3[] plist)
	{
		if(plist.Length < 4)return true;
		
		bool crosslessthanzero = false;
		
		for (int i = 0; i < plist.Length ; i++)
		{
			Vector3 midpoint = plist[i];
			
			Vector3 nextpoint;
			if (i+1 >plist.Length -1 ) 
			{
				nextpoint = plist[0];
			}
			else
			{
				nextpoint = plist[i+1];
			} 
			Vector3 lastpoint;
			if (i-1 <0 ) 
			{
				lastpoint = plist[plist.Length -1];
			}
			else
			{
				lastpoint = plist[i-1];
			} 
			
			Vector3 NexttoMid = midpoint - nextpoint;
			Vector3 LasttoMid = midpoint - lastpoint;
			
			float zcrossproduct = (NexttoMid.x * LasttoMid.y)-(NexttoMid.y * LasttoMid.x);	
			if (i == 0)
			{
				if (zcrossproduct < 0f)crosslessthanzero = true;
				else crosslessthanzero = false;
			}
			else
			{
				if ((crosslessthanzero && zcrossproduct > 0f)||(!crosslessthanzero && zcrossproduct < 0f))
				{
					return false;
				}
			}				
		}		
		return true;
	}
	
	public static List<Vector3> MakeEdgePoints()
	{
		List<Vector3> PointsList = new List<Vector3>();
			
		PointsList.Add(new Vector3(-1,0));
		PointsList.Add(new Vector3(1,0));

		return PointsList;
	}
	
	public static List<Vector3> MakeBoxPoints(Vector2 Size)
	{
		List<Vector3> PointsList = new List<Vector3>();
		int[,] pm = new int[,]
		{
			{-1,1}
			,{-1,-1}
			,{1,-1}
			,{1,1}
		};				
		for (int i = 0; i < 4; i++) 
		{
			float xcoord = Size.x/2*pm[i,0];
			float ycoord = Size.y/2*pm[i,1];		
			PointsList.Add(new Vector3(xcoord,ycoord));
        }
        return PointsList;
	}
	
	public static List<Vector3> makePolyPoints(int sides,float r)
	{		
		List<Vector3> PointsList = new List<Vector3>();
		if (sides < 3) 
		{
			Debug.LogError("You tried to make a polygon shape with less than 3 sides, making one with 3 instead");
			sides = 3;
		}
		if (sides > 8) 
		{
			Debug.LogError("You tried to make a polygon shape with more than 8 sides, making one with 8 instead.");
			sides = 8;
		}
		for (int i = 0; i < sides; i++)
		{
			PointsList.Add (new Vector3(r * Mathf.Cos(2 * Mathf.PI * (float)i / (float)sides), r * Mathf.Sin(2 * Mathf.PI * (float)i / (float)sides)));
    	}
    	return PointsList;
    }
    
    public static Vector3 RotatePoint(Vector3 point,float Angle,Vector3 tran)
    {
    	List<Vector3> onelist = new List<Vector3>{point};
		onelist = RotatePoints(onelist,Angle,tran);
		return onelist[0];
    }
    
	public static List<Vector3> RotatePoints(List<Vector3> PointsList,float Angle,Vector3 tran)
    {
		for (int i = 0; i < PointsList.Count; i++)
		{
			PointsList[i] -= tran;
			PointsList[i] = new Vector3
				(
				 (PointsList[i].x*Mathf.Cos(Angle*Mathf.Deg2Rad)) - (PointsList[i].y*Mathf.Sin(Angle*Mathf.Deg2Rad))
				,(PointsList[i].x*Mathf.Sin(Angle*Mathf.Deg2Rad)) + (PointsList[i].y*Mathf.Cos(Angle*Mathf.Deg2Rad))
				);	
			PointsList[i] += tran;
		}
		return PointsList;
    }
    
	public static List<Vector3> ChangeRadius(float diff,List<Vector3> PointsList,Vector3 tran)
	{
		for (int i = 0; i < PointsList.Count; i++)
		{
			PointsList[i] -= tran;
			PointsList[i] += PointsList[i]*diff;
			PointsList[i] += tran;
		}
		return PointsList;
    }
    
    public static List<Vector3> OffsetPoints(Vector2 offset,List<Vector3> PointsList)
    {
		for (int i = 0; i < PointsList.Count; i++)
		{
			PointsList[i] = new Vector3(PointsList[i].x+offset.x,PointsList[i].y+offset.y);
		}
		return PointsList;
    }
    
	public static Vector3[] TransformPoints(Transform transform,Vector3 pos,List<Vector3> PointsList)
	{
		Vector3[] Points = new Vector3[PointsList.Count];  	
		for (int i = 0; i < Points.Length; i++)
		{
			Points[i] = transform.TransformPoint(new Vector3(PointsList[i].x,PointsList[i].y))-pos;
        }
        return Points;
    }
    
	public static float[] GetfloatArray(Vector3[] PointsList)
	{
		float[] pointfloats = new float[(PointsList.Length*2)+1];
		pointfloats[0] = PointsList.Length;
		for (int i = 0; i < PointsList.Length; i++)
		{
			pointfloats[(i*2)+1] = PointsList[i].x;
			pointfloats[(i*2)+2] = PointsList[i].y;
		}
		return pointfloats;
	}
	
	public static Vector3[] Vec2listToVec3Array(List<Vector2> PointsList)
	{
		Vector3[] returnarray = new Vector3[PointsList.Count];
		for (int i = 0; i < returnarray.Length; i++)
		{
			returnarray[i] = new Vector3(PointsList[i].x,PointsList[i].y);  
		}
		return returnarray;
	}

    public static Vector3[]Vec2ArrayToVec3Array(Vector2[] vec2array)
    {
        Vector3[] points = new Vector3[vec2array.Length];
            for (int i = 0; i < points.Length; i++)
            {
                points[i] = vec2array[i];
            }
            return points;
    }
	   
    public static void DrawGizmos (Color colour,Vector3[] Points,bool loop)
	{								
		Gizmos.color = colour;	
		
		if (Points != null)
		{
			for (int i = 0; i < Points.Length; i++)
			{
				if (i == Points.Length-1) 
				{
					if (loop) 
					{
						Gizmos.DrawLine(Points[i] ,Points[0]);
					}
					else
					{
						break;
					}
				}
				else
				{
					Gizmos.DrawLine(Points[i],Points[i+1]);
				}
			}				
		}
		
	}
	
	public static void DrawGizmosPlaying (Transform transform,bool tran,float diff, Color colour,Vector3[] Points,bool loop)
	{	
		Vector3 pos;
		Quaternion ang;
		if (tran)pos = transform.position;
		else pos = Vector3.zero;
		if (diff !=0f) ang = Quaternion.AngleAxis(diff,Vector3.forward);
		else ang = Quaternion.identity;
		
		Gizmos.matrix = Matrix4x4.TRS(pos,ang,Vector3.one); 
		
		DrawGizmos(colour,Points,loop);
    }

    // Return True if the point is in the polygon.
    public static bool PointInPolygon(List<Vector3> pointsList, Vector3 point)
    {
        int i, j, c = 0;
        for (i = 0, j = pointsList.Count - 1; i < pointsList.Count; j = i++)
        {
            if (((pointsList[i].y > point.y) != (pointsList[j].y > point.y)) && (point.x < (pointsList[j].x - pointsList[i].x) * (point.y - pointsList[i].y) / (pointsList[j].y - pointsList[i].y) + pointsList[i].x))
            {
                c = 1 + c; ;
            }
        }
        return c % 2 != 0;
    }
	//判定两个凸多边形是否相交
    public static bool ArePolygonsIntersectingSAT(List<Vector3> polygon1, List<Vector3> polygon2)
    {
        // 判定多边形1和多边形2的所有边是否分离
        if (IsSeparatingAxis(polygon1, polygon2) || IsSeparatingAxis(polygon2, polygon1))
        {
            return false; // 分离轴，两多边形不相交
        }

        return true; // 未找到分离轴，两多边形相交
    }





    // 判定是否存在分离轴的函数
    private static bool IsSeparatingAxis(List<Vector3> polygon1, List<Vector3> polygon2)
    {
        int edgeCount = polygon1.Count;

        for (int i = 0; i < edgeCount; i++)
        {
            Vector3 edge = polygon1[(i + 1) % edgeCount] - polygon1[i];
            Vector3 axis = new Vector3(-edge.y, edge.x).normalized;

            if (IsSeparatingAxisOnAxis(axis, polygon1, polygon2))
            {
                return true; // 发现分离轴，两多边形不相交
            }
        }

        return false; // 未找到分离轴，两多边形可能相交
    }

    // 在给定轴上判定是否有分离轴的函数
    private static bool IsSeparatingAxisOnAxis(Vector3 axis, List<Vector3> polygon1, List<Vector3> polygon2)
    {
        float min1, max1, min2, max2;

        ProjectPolygonOnAxis(axis, polygon1, out min1, out max1);
        ProjectPolygonOnAxis(axis, polygon2, out min2, out max2);

        return !(max1 >= min2 && max2 >= min1);
    }

    // 在给定轴上投影多边形的函数
    private static void ProjectPolygonOnAxis(Vector3 axis, List<Vector3> polygon, out float min, out float max)
    {
        float dotProduct = Vector3.Dot(axis, polygon[0]);
        min = max = dotProduct;

        for (int i = 1; i < polygon.Count; i++)
        {
            dotProduct = Vector3.Dot(axis, polygon[i]);
            min = Mathf.Min(min, dotProduct);
            max = Mathf.Max(max, dotProduct);
        }
    }

}
