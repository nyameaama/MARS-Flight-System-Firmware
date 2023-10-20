using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;

[System.Serializable]
public class UAVData
{
    public GameObject uavObject;
    public Text headingText;
    public Text locationText;
    public Text altitudeText;
    public Text detectedUAVsText;
    private string uniqueID;
    private List<string> detectedUAVs = new List<string>();
    private bool isUavMissing = false; 

    
    public void GenerateUniqueID()
    {
        uniqueID = Random.Range(100000, 999999).ToString(); 
    }

    
    public string GetUniqueID()
    {
        return uniqueID;
    }

    
    public void AddDetectedUAV(string uavID)
    {
        if (!detectedUAVs.Contains(uavID))
        {
            detectedUAVs.Add(uavID);
        }
    }

    
    public List<string> GetDetectedUAVs()
    {
        return detectedUAVs;
    }

 
    public void SetMissing(bool missing)
    {
        isUavMissing = missing;
    }

    
    public bool IsUavMissing()
    {
        return isUavMissing;
    }
}

public class UAVDisplay : MonoBehaviour
{
    public UAVData[] uavDataArray = new UAVData[9];

    private void Start()
    {
        
        foreach (var uavData in uavDataArray)
        {
            if (uavData != null)
            {
                uavData.GenerateUniqueID();
            }
        }
    }

    private void Update()
    {
       
        for (int i = 0; i < uavDataArray.Length; i++)
        {
            UAVData uavData = uavDataArray[i];

            if (uavData != null)
            {
                
                bool isUavMissing = uavData.uavObject == null;

                
                string idText = "UAV " + uavData.GetUniqueID();
                if (isUavMissing)
                {
                    idText += " (Offline)";
                }

                if (!isUavMissing && uavData.headingText != null &&
                    uavData.locationText != null && uavData.altitudeText != null && uavData.detectedUAVsText != null)
                {
                    
                    Quaternion uavRotation = uavData.uavObject.transform.rotation;
                    Vector3 uavPosition = uavData.uavObject.transform.position;
                    float altitude = uavPosition.y;

                    
                    float heading = Quaternion.Euler(0, uavRotation.eulerAngles.y, 0).eulerAngles.y;

                   
                    uavData.headingText.text = idText + ": Heading: " + heading.ToString("F2") + "°";
                    uavData.headingText.color = Color.green; 

                    
                    float latitude = Mathf.Asin(uavPosition.y / 6371.0f) * Mathf.Rad2Deg;
                    float longitude = Mathf.Atan2(uavPosition.x, uavPosition.z) * Mathf.Rad2Deg;

                    
                    uavData.locationText.text = idText + ": " +
                                                "Lat: " + latitude.ToString("F2") +
                                                " Lon: " + longitude.ToString("F2");
                    uavData.locationText.color = Color.green; 

                    
                    uavData.altitudeText.text = idText + ": " +
                                                "Altitude: " + altitude.ToString("F2") + " meters";
                    uavData.altitudeText.color = Color.green; 

                    
                    DetectNearbyUAVs(uavData);

                    /
                    uavData.detectedUAVsText.text = "Detected UAVs: " + string.Join(", ", uavData.GetDetectedUAVs().ToArray());
                    uavData.detectedUAVsText.color = Color.green; 

                    /
                    uavData.SetMissing(false);
                }
                else
                {
                    
                    if (!uavData.IsUavMissing()) 
                    {
                        uavData.headingText.text = idText + " (Offline)";
                        uavData.headingText.color = Color.red; 

                        uavData.locationText.text = idText + " (Offline)";
                        uavData.locationText.color = Color.red; 

                        uavData.altitudeText.text = idText + " (Offline)";
                        uavData.altitudeText.color = Color.red; 

                        uavData.detectedUAVsText.text = "Detected UAVs: None";
                        uavData.detectedUAVsText.color = Color.red; 

                        
                        uavData.SetMissing(true);
                    }
                }
            }
        }
    }

    private void DetectNearbyUAVs(UAVData uavData)
    {
        
        uavData.GetDetectedUAVs().Clear();

        
        foreach (var otherUAVData in uavDataArray)
        {
            if (otherUAVData != null && otherUAVData != uavData)
            {
               
                float distance = Vector3.Distance(uavData.uavObject.transform.position, otherUAVData.uavObject.transform.position);

                
                if (distance <= 100.0f && otherUAVData.uavObject != null)
                {
                    uavData.AddDetectedUAV(otherUAVData.GetUniqueID());
                }
            }
        }
    }
}
