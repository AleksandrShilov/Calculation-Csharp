using System.Runtime.InteropServices;

namespace SimpleCalc.ViewModels;

class Models
{
    #if LINUX
            private const string LIBRARY_NAME = "libCalcWrapper.so";
    #elif OSX
            private const string LIBRARY_NAME = "libCalcWrapper.dylib";
    #elif WIN
            private const string LIBRARY_NAME = "CalcWrapper.dll";
    #endif

    [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
    public static extern double CalculateValue(string temp, double x);

    public double GetResult(string calcStr, double x)
    {
        return CalculateValue(calcStr, x);
    }
}
