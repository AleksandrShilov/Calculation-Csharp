using ReactiveUI;
using System.Reactive;


namespace SimpleCalc.ViewModels;

public class InputXViewModel : ViewModelBase
{
    public string _inputText;
    public string InputText
    {
        get => _inputText;
        set => this.RaiseAndSetIfChanged(ref _inputText, value);
    }

    public ReactiveCommand<Unit, string> GetXCommand { get; }

    public InputXViewModel()
    {
        GetXCommand = ReactiveCommand.Create<string>(GetX);
    }

    private string GetX()
    {
       
        return InputText;
    }
}
