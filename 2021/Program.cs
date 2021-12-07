using Aoc.Y21.CsUtils;
using Aoc.Y21.day1;

namespace Aoc.Y21;

public static class Program
{
    public static void Main(string[] args)
    {
        string dayInput;
        if (args.Length == 0)
        {
            Console.Write("Enter the number of the day to run: ");
            dayInput = Console.ReadLine() ?? "";
            
        }
        else
        {
            dayInput = args[0];
        }

        if (!int.TryParse(dayInput.Trim(), out var day))
        {
            Console.WriteLine("Input not a valid integer");
            return;
        }

        var dayTypes = typeof(Day1).Assembly.GetTypes()
            .Where(t =>
                t.CustomAttributes.Any(c =>
                {
                    if (c.AttributeType == typeof(DayAttribute))
                    {
                        return (int) (c.ConstructorArguments.First().Value ?? -1) == day;
                    }
                    return false;
                })
            )
            .ToList();

        if (dayTypes.Count < 1)
        {
            Console.WriteLine("Did not find day");
            return;
        }

        if (dayTypes.Count > 1)
        {
            Console.WriteLine("Found multiple classes with the given day:");
            foreach (var type in dayTypes)
            {
                Console.WriteLine(type);
            }

            return;
        }

        if (dayTypes.Single().GetInterfaces().All(i => i != typeof(IDay)))
        {
            Console.WriteLine("Found class does not implement IDay.");
            return;
        }

        var runner = (IDay) dayTypes
            .Single()
            .GetConstructors()
            .Single()
            .Invoke(Array.Empty<object>());

        runner.Run();
    }
}