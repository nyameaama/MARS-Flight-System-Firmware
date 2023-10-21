using UnityEngine;
using UnityEngine.UI;

public class TransponderRangeIndicator : MonoBehaviour
{
    public GameObject[] uavObjects; 
    public float transponderRange = 100f; 
    public Text uiText; /

    
    public Color[] uavColors;

    private void Start()
    {
        if (uavColors.Length != uavObjects.Length)
        {
            Debug.LogError("The number of colors should match the number of UAV objects.");
            return;
        }

        for (int i = 0; i < uavObjects.Length; i++)
        {
            GameObject uav = uavObjects[i];

            if (uav != null)
            {
                
                GameObject sphere = new GameObject("TransparentSphere");
                sphere.transform.SetParent(uav.transform);
                sphere.transform.localPosition = Vector3.zero;

                
                MeshRenderer sphereRenderer = sphere.AddComponent<MeshRenderer>();
                MeshFilter sphereFilter = sphere.AddComponent<MeshFilter>();

                
                Mesh sphereMesh = new Mesh();
                sphereFilter.mesh = sphereMesh;
                sphereMesh.name = "TransparentSphereMesh";
                sphereMesh.Clear();

                int segments = 360;
                int verticesCount = (segments + 1) * (segments + 1);
                Vector3[] vertices = new Vector3[verticesCount];
                int[] triangles = new int[segments * segments * 6];

                for (int j = 0; j <= segments; j++)
                {
                    for (int k = 0; k <= segments; k++)
                    {
                        int index = j * (segments + 1) + k;
                        float angleX = j * 360f / segments;
                        float angleY = k * 360f / segments;
                        float x = Mathf.Cos(angleX * Mathf.Deg2Rad) * Mathf.Cos(angleY * Mathf.Deg2Rad) * transponderRange;
                        float y = Mathf.Sin(angleX * Mathf.Deg2Rad) * Mathf.Cos(angleY * Mathf.Deg2Rad) * transponderRange;
                        float z = Mathf.Sin(angleY * Mathf.Deg2Rad) * transponderRange;
                        vertices[index] = new Vector3(x, y, z);
                    }
                }

                int triangleIndex = 0;
                for (int j = 0; j < segments; j++)
                {
                    for (int k = 0; k < segments; k++)
                    {
                        int vertexIndex = j * (segments + 1) + k;
                        triangles[triangleIndex++] = vertexIndex;
                        triangles[triangleIndex++] = vertexIndex + 1;
                        triangles[triangleIndex++] = vertexIndex + segments + 1;

                        triangles[triangleIndex++] = vertexIndex + 1;
                        triangles[triangleIndex++] = vertexIndex + segments + 2;
                        triangles[triangleIndex++] = vertexIndex + segments + 1;
                    }
                }

                sphereMesh.vertices = vertices;
                sphereMesh.triangles = triangles;

                
                Material transparentMaterial = new Material(Shader.Find("Standard"));
                transparentMaterial.SetFloat("_Mode", 2); // Set rendering mode to Transparent.
                transparentMaterial.SetInt("_SrcBlend", (int)UnityEngine.Rendering.BlendMode.SrcAlpha);
                transparentMaterial.SetInt("_DstBlend", (int)UnityEngine.Rendering.BlendMode.OneMinusSrcAlpha);
                transparentMaterial.SetInt("_ZWrite", 0); // Disable ZWrite for transparency.
                transparentMaterial.DisableKeyword("_ALPHATEST_ON");
                transparentMaterial.EnableKeyword("_ALPHABLEND_ON");
                transparentMaterial.DisableKeyword("_ALPHAPREMULTIPLY_ON");
                transparentMaterial.renderQueue = (int)UnityEngine.Rendering.RenderQueue.Transparent;
                transparentMaterial.color = uavColors[i]; // Set the color from the array.
                sphereRenderer.material = transparentMaterial;
            }
        }
    }
}
