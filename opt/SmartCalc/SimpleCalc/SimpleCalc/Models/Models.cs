using System.Runtime.InteropServices;


namespace SimpleCalc.ViewModels;

public class Models
{
    [DllImport("CalcWrapper", CallingConvention = CallingConvention.Cdecl)]
    public static extern double CalculateValue(string temp, double x);

    public double GetResult(string calcStr, double x)
    {
        return CalculateValue(calcStr, x);
    }
}
