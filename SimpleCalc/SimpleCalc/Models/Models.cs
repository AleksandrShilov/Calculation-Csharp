using System.Runtime.InteropServices;

namespace SimpleCalc.ViewModels;

class Models
{
    private const string LIBRARY_NAME = "CalcWrapper.dll";

    #if LINUX
            LIBRARY_NAME = "libCalcWrapper.so";
    #elif OSX
            LIBRARY_NAME = "libCalcWrapper.dylib";
    #endif

    [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
    public static extern double CalculateValue(string temp, double x);

    public double GetResult(string calcStr, double x)
    {
        return CalculateValue(calcStr, x);
    }
}
