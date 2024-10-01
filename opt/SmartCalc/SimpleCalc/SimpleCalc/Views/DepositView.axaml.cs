using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Avalonia.ReactiveUI;
using ReactiveUI;
using SimpleCalc.ViewModels;
using System.Reactive.Disposables;

namespace SimpleCalc;

public partial class DepositView : ReactiveUserControl<DepositViewModel>
{
    public DepositView()
    {
        this.WhenActivated((CompositeDisposable disposable) => { });
        AvaloniaXamlLoader.Load(this);
    }
}