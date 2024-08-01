using ReactiveUI;
using System;
using System.Reactive;

namespace SimpleCalc.ViewModels;


public class BaseCalculateViewModel : ViewModelBase 
{
    private string _displayStr = "0";

    public ReactiveCommand<string, Unit> AddNumberCommand { get; }
    public ReactiveCommand<string, Unit> RemoveLastCharCommand { get; }
    public ReactiveCommand<Unit, Unit> RemoveAllStrCommand { get; }

    public BaseCalculateViewModel()
    {
        AddNumberCommand = ReactiveCommand.Create<string>(AddNumber);
        RemoveLastCharCommand = ReactiveCommand.Create<string>(RemoveLastChar);
        RemoveAllStrCommand = ReactiveCommand.Create(RemoveAllStr);
    }

    private void AddNumber(string value)
    {
        ShownValue += value;
    }

    public void RemoveLastChar(string value)
    {
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
