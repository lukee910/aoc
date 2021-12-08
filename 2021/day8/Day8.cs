using Aoc.Y21.CsUtils;

namespace Aoc.Y21.day8;

[Day(8)]
public class Day8 : IDay
{
    public void Run()
    {
        var input = File.ReadAllLines("day8/input.txt")
            .Select(l => l.Split("|", StringSplitOptions.TrimEntries))
            .Select(l => l.Select(p => p.Split(" ")).ToList())
            .ToList();
        
        // Task 1: Count number of 1, 4, 7, 8
        var soughtLengths = new[] { 2, 3, 4, 7 };
        Console.WriteLine(input.Sum(l => l[1].Count(e => soughtLengths.Contains(e.Length))));
        
        // Task 2: Sum of all encoded values
        var sum = 0;
        foreach (var line in input)
        {
            var all = new[] {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
            var options = new Dictionary<char, char[]>();
            for (var ch = 'a'; ch <= 'g'; ch++)
            {
                options[ch] = all;
            }

            var one = line[0].Single(p => p.Length == 2);
            RestrictOptions(one, new[] {'c', 'f'}, options);

            var four = line[0].Single(p => p.Length == 4);
            var fourNotOne = four.Where(c => !one.Contains(c));
            RestrictOptions(fourNotOne, new[] {'b', 'd'}, options);

            var a = line[0].Single(p => p.Length == 3).Single(c => !one.Contains(c));
            RestrictOptions(a, new []{'a'}, options);

            var length6 = line[0].Where(p => p.Length == 6).ToList();

            // Console.WriteLine("Four: " + four);
            // Console.WriteLine("Length 6:");
            // length6.ForEach(Console.WriteLine);

            var nine = length6.Single(p => p.Intersect(four).Count() == four.Length);
            var e = all.Single(ch => !nine.Contains(ch));
            RestrictOptions(e, new []{'e'}, options);

            var six = length6.Single(p => p != nine && p.Intersect(one).Count() == 1);
            var f = six.Intersect(one).Single();
            RestrictOptions(f, new []{'f'}, options);
            var c = one.Single(ch => ch != f);
            RestrictOptions(c, new []{'c'}, options);

            var two = line[0].Single(p => p.Length == 5 && p.Intersect(new[]
            {
                a, c, e
            }).Count() == 3);
            var d = two.Intersect(four).Single(ch => ch != c);
            RestrictOptions(d, new[]{'d'}, options);

            var g = two.Single(ch => ch != a && ch != c && ch != d && ch != e);
            RestrictOptions(g, new[]{'g'}, options);

            var b = four.Intersect(six).Single(ch => ch != d && ch != f);
            RestrictOptions(b, new []{'b'}, options);

            var translation = new Dictionary<string, int>
            {
                [one] = 1,
                [two] = 2,
                [$"{a}{c}{d}{f}{g}"] = 3,
                [four] = 4,
                [$"{a}{b}{d}{f}{g}"] = 5,
                [six] = 6,
                [$"{a}{c}{f}"] = 7,
                [string.Join("", all)] = 8,
                [nine] = 9,
                [string.Join("", all.Except(new [] {d}))] = 0
            };

            var cancel = false;
            foreach (var (ch, opt) in options)
            {
                if (opt.Length != 1)
                {
                    Console.WriteLine($"Invalid options for char {ch}: " + string.Join(", ", opt));
                    cancel = true;
                }
            }

            if (cancel)
            {
                return;
            }

            var lineValues = new List<int>();
            foreach (var code in line[1])
            {
                var value = translation[
                    translation.Keys.Single(k => k.All(code.Contains) && k.Length == code.Length)
                ];
                Console.WriteLine($"Code {code}, Value {value}");
                lineValues.Add(value);
            }

            var lineSum = lineValues[0] * 1000 + lineValues[1] * 100 + lineValues[2] * 10 + lineValues[3];
            sum += lineSum;
            Console.WriteLine("Line sum: " + lineSum);
        }

        Console.WriteLine(sum);
    }

    private static void RestrictOptions(char c, char[] restrictTo, Dictionary<char, char[]> options)
        => RestrictOptions(new [] {c}, restrictTo, options);

    private static void RestrictOptions(string chars, char[] restrictTo, Dictionary<char, char[]> options)
        => RestrictOptions(chars.ToArray(), restrictTo, options);

    private static void RestrictOptions(IEnumerable<char> chars, char[] restrictTo, Dictionary<char, char[]> options)
    {
        chars = chars.ToArray();
        foreach (var c in chars)
        {
            options[c] = options[c].Intersect(restrictTo).ToArray();
        }
    }
}