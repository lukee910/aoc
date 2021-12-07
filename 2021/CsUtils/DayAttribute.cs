using System.Runtime.CompilerServices;

namespace Aoc.Y21.CsUtils;

[AttributeUsage(AttributeTargets.Class)]
public class DayAttribute : Attribute
{
    public DayAttribute(int day)
    {
    }
}