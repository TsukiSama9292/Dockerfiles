using System;

class Program
{
    static void Main()
    {
        long sum = 0;
        for (int i = 0; i < 10_000_000; i++)
        {
            sum += i;
        }
        Console.WriteLine("Sum: " + sum);
    }
}
