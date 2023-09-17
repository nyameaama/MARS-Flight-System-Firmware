using System;

public class Program
{
    public static void Main()
    {
        string formattedLog = LogFormatterParser.FormatLog("Event", "12345", 10.5, 1, 2, "Additional Information");
        Console.WriteLine("Formatted Log:");
        Console.WriteLine(formattedLog);

        string inputLog = "Event:\n{\n    ID: 12345\n    POS_LAT: 10.5\n    POS_LONG: 1\n    POS_ALT: 2\n    INFO: Additional Information\n}";
        bool parsed = LogFormatterParser.ParseLog(inputLog, out string logEv, out string ID, out double _lat, out double _long, out double _alt, out string additionalInfo);

        if (parsed)
        {
            Console.WriteLine("\nParsed Values:");
            Console.WriteLine($"Log Event: {logEv}");
            Console.WriteLine($"ID: {ID}");
            Console.WriteLine($"POS_LAT: {_lat}");
            Console.WriteLine($"POS_LONG: {_long}");
            Console.WriteLine($"POS_ALT: {_alt}");
            Console.WriteLine($"Additional Info: {additionalInfo}");
        }
        else
        {
            Console.WriteLine("\nParsing failed.");
        }
    }
}