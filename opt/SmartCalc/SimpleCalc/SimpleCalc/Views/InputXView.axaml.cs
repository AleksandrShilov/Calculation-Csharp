using Avalonia.ReactiveUI;
using SimpleCalc.ViewModels;
using ReactiveUI;
using System;

namespace SimpleCalc;

public partial class InputXView : ReactiveWindow<InputXViewModel>
{
    public InputXView()
    {
        InitializeComponent();
        this.WhenActivated(d => d(ViewModel!.GetXCommand.Subscribe(Close)));
    }
}