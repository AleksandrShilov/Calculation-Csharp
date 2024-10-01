using ReactiveUI;
using Avalonia.ReactiveUI;
using Avalonia.Markup.Xaml;
using SimpleCalc.ViewModels;
using System.Reactive.Disposables;


namespace SimpleCalc.Views;

public partial class BaseCalculateView : ReactiveUserControl<CalculateViewModel>
{
    public BaseCalculateView()
    {
        this.WhenActivated((CompositeDisposable disposable) => { });
        AvaloniaXamlLoader.Load(this);
    }
}