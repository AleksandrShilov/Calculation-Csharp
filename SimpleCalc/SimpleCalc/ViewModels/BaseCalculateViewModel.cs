using ReactiveUI;
using System;
using System.Reactive;

namespace SimpleCalc.ViewModels;


public class BaseCalculateViewModel : ViewModelBase 
{
    private string _displayStr = "0";

    public ReactiveCommand<int, Unit> AddNumberCommand { get; }
    public ReactiveCommand<string, Unit> RemoveLastNumberCommand { get; }

    public BaseCalculateViewModel()
    {
        AddNumberCommand = ReactiveCommand.Create<int>(AddNumber);
        RemoveLastNumberCommand = ReactiveCommand.Create<string>(RemoveLastNumber);
    }

    private void AddNumber(int value)
    {
        switch(value)
        {
            case 1:
                ShownValue += "1";
                break;
        }
    }

    public void RemoveLastNumber(string value)
    {
        ShownValue = ShownValue;
    }

    public string ShownValue
    {
        get => _displayStr;
        set => this.RaiseAndSetIfChanged(ref _displayStr, value);
    }


}
