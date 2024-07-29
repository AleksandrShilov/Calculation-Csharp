using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using SimpleCalc.ViewModels;
using SimpleCalc.Views;

namespace SimpleCalc;

public partial class App : Application
{
    public override void Initialize()
    {
        AvaloniaXamlLoader.Load(this);
    }

    public override void OnFrameworkInitializationCompleted()
    {
        var locator = new ViewLocator();
        DataTemplates.Add(locator);


        if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
        {
            IocSetup.ConfigureServices();

            desktop.MainWindow = new MainWindow
            {
                DataContext = new MainViewModel()
            };
        }

        base.OnFrameworkInitializationCompleted();
    }
}
