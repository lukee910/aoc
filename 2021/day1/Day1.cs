using Aoc.Y21.CsUtils;

namespace Aoc.Y21.day1;

[Day(1)]
public class Day1 : IDay
{
    public void Run()
    {
        var input = File.ReadAllLines("./day1/d1input.txt")
            .Select(int.Parse)
            .ToList();

        // Task 1, increases over all
        Console.WriteLine(input.Skip(1).Where((value, index) => value > input[index]).Count());

        // Task 2, increases in a three wide window
        // TIL .Zip(..) exists, will do everything with a zip here :D
        var zipped = ZipSum(ZipSum(input, input.Skip(1)), input.Skip(2)).ToList();
        Console.WriteLine(zipped.Zip(zipped.Skip(1), (left, right) => left < right).Count(isLarger => isLarger));
    }

    private static IEnumerable<int> ZipSum(IEnumerable<int> a, IEnumerable<int> b) => a.Zip(b, (valA, valB) => valA + valB);
}
