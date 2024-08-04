using ReactiveUI;
using System.Reactive;

namespace SimpleCalc.ViewModels;


public class BaseCalculateViewModel : ViewModelBase 
{
    private string _displayStr = "0";

    public ReactiveCommand<string, Unit> AddCharCommand { get; }
    public ReactiveCommand<string, Unit> RemoveLastCharCommand { get; }
    public ReactiveCommand<Unit, Unit> RemoveAllStrCommand { get; }

    public BaseCalculateViewModel()
    {
        AddCharCommand = ReactiveCommand.Create<string>(AddChar);
        RemoveLastCharCommand = ReactiveCommand.Create<string>(RemoveLastChar);
        RemoveAllStrCommand = ReactiveCommand.Create(RemoveAllStr);
    }

    private void AddChar(string value)
    {
        if (ShownValue.Length == 1 && ShownValue.Equals("0") && int.TryParse(value, out _))
            ShownValue = value;
        else
            ShownValue += value;
    }

    public void RemoveLastChar(string value)
    {
        if (ShownValue.Length == 1)
            ShownValue = "0";
        else if (ShownValue.Length > 1)
            ShownValue = ShownValue.Remove((ShownValue.Length - 1), 1);
    }    
    
    public void RemoveAllStr()
    {
        ShownValue = "0";
    }

    public string ShownValue
    {
        get => _displayStr;
        set => this.RaiseAndSetIfChanged(ref _displayStr, value);
    }


}
