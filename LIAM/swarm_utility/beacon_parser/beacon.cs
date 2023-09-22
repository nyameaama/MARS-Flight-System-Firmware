using System;
using System.Text.RegularExpressions;

public class LogFormatterParser
{
    public static string FormatLog(string logEv, string ID, double _lat, double _long, double _alt, string additionalInfo)
    {
        return $@"{logEv}:
{{
    ID: {ID}
    POS_LAT: {_lat}
    POS_LONG: {_long}
    POS_ALT: {_alt}
    INFO: {additionalInfo}
}}";
    }

    public static bool ParseLog(string input, out string logEv, out string ID, out double _lat, out double _long, out double _alt, out string additionalInfo)
    {
        logEv = ID = additionalInfo = "";
        _lat = 0;
        _long = _alt = 0;

        string pattern = @"(\w+):\s*\{\s*ID:\s*([^}]+)\s*POS_LAT:\s*([\d.]+)\s*POS_LONG:\s*(\d+)\s*POS_ALT:\s*(\d+)\s*INFO:\s*([^}]+)\s*\}";

        Match match = Regex.Match(input, pattern);

        if (match.Success)
        {
            logEv = match.Groups[1].Value;
            ID = match.Groups[2].Value;
            if (double.TryParse(match.Groups[3].Value, out _lat) &&
                double.TryParse(match.Groups[4].Value, out _long) &&
                double.TryParse(match.Groups[5].Value, out _alt))
            {
                additionalInfo = match.Groups[6].Value;
                return true;
            }
        }

        return false;
    }
}