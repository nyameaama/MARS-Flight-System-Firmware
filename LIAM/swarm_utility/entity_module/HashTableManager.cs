/*MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

using System;
using System.Collections;
using System.Collections.Generic;

public class HashTableManager
{
    private Dictionary<string, Hashtable> hashTableCollection = new Dictionary<string, Hashtable>();

    // Function to create a hash table with a specific ID
    public void CreateHashTable(string id)
    {
        if (!hashTableCollection.ContainsKey(id))
        {
            Hashtable newHashTable = new Hashtable();
            hashTableCollection.Add(id, newHashTable);
            Console.WriteLine($"Hashtable with ID '{id}' created.");
        }
        else
        {
            Console.WriteLine($"Hashtable with ID '{id}' already exists.");
        }
    }

    // Function to retrieve data from a hash table given an ID
    public object RetrieveData(string id, object key)
    {
        if (hashTableCollection.ContainsKey(id))
        {
            Hashtable hashTable = hashTableCollection[id];
            if (hashTable.ContainsKey(key))
            {
                return hashTable[key];
            }
            else
            {
                Console.WriteLine($"Key '{key}' does not exist in Hashtable with ID '{id}'.");
            }
        }
        else
        {
            Console.WriteLine($"Hashtable with ID '{id}' does not exist.");
        }

        return null;
    }

    // Function to append data to a hash table given an ID
    public void AppendData(string id, object key, object value)
    {
        if (hashTableCollection.ContainsKey(id))
        {
            Hashtable hashTable = hashTableCollection[id];
            if (!hashTable.ContainsKey(key))
            {
                hashTable.Add(key, value);
                Console.WriteLine($"Data appended to Hashtable with ID '{id}' - Key: '{key}', Value: '{value}'.");
            }
            else
            {
                Console.WriteLine($"Key '{key}' already exists in Hashtable with ID '{id}'.");
            }
        }
        else
        {
            Console.WriteLine($"Hashtable with ID '{id}' does not exist.");
        }
    }
}