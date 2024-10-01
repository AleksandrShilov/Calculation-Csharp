using ReactiveUI;
using Avalonia.ReactiveUI;
using Avalonia.Markup.Xaml;
using SimpleCalc.ViewModels;
using System.Reactive.Disposables;
using Avalonia.Controls;


namespace SimpleCalc.Views;

public partial class BaseCalcView : UserControl
{
    public BaseCalcView()
    {
        InitializeComponent();
    }
}
