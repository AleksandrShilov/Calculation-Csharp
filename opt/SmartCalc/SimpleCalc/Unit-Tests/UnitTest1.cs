using System.Reflection;
using Xunit;
using SimpleCalc.ViewModels;

namespace Unit_Tests;

public class UnitTest1
{
    [Fact]
    public void GetResult_ValidExpression_ReturnsExpectedResult()
    {
        // Arrange
        var model = new Models();
        string expression = "2*x+1";
        double x = 3;
        double expected = 7;

        // Act
        double result = model.GetResult(expression, x);

        // Assert
        Assert.Equal(expected, result);
    }
}