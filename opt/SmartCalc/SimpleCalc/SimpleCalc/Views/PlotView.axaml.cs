using Avalonia.Controls;
using SimpleCalc.ViewModels;


namespace SimpleCalc.Views;

public partial class PlotView : Window
{
    public PlotView()
    {
        InitializeComponent();
        DataContext = new PlotViewModel();
    }
}