using System;

class Program
{
    static void Main()
    {
        HashTableManager manager = new HashTableManager();

        // Create a hash table with ID "myTable"
        manager.CreateHashTable("Agent1");

        // Append data to the hash table
        manager.AppendData("Agent1", "ID", "XCFF1");
        manager.AppendData("Agent1", "x_pos", 30);
        manager.AppendData("Agent1", "y_pos", 80);
        manager.AppendData("Agent1", "z_pos", 60);

        // Retrieve and display data
        Console.WriteLine("ID: " + manager.RetrieveData("Agent1", "ID"));
        Console.WriteLine("x_pos: " + manager.RetrieveData("Agent1", "x_pos"));
        Console.WriteLine("y_pos: " + manager.RetrieveData("Agent1", "y_pos"));
        Console.WriteLine("z_pos: " + manager.RetrieveData("Agent1", "z_pos"));
    }
}