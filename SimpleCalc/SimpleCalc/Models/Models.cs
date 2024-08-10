using System.Runtime.InteropServices;

namespace SimpleCalc.ViewModels;

class Models
{
    //[DllImport("libCalcWrapper.dll", CallingConvention = CallingConvention.Cdecl)]
    [DllImport("CMakeProject1.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern double CalculateValue(string temp, double x);

    public double GetResult(string calcStr, double x)
    {
        return CalculateValue(calcStr, x);
    }
}
