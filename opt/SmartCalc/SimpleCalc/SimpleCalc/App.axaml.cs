using Splat;
using Avalonia;
using ReactiveUI;
using LiveChartsCore;
using SimpleCalc.Views;
using Avalonia.Markup.Xaml;
using SimpleCalc.ViewModels;
using Avalonia.Controls.ApplicationLifetimes;


namespace SimpleCalc;

public partial class App : Application
{
    public override void Initialize()
    {
        AvaloniaXamlLoader.Load(this);

        LiveCharts.Configure(config =>
           config
               // you can override the theme 
               //.AddDarkTheme()  

               // In case you need a non-Latin based font, you must register a typeface for SkiaSharp
               //.HasGlobalSKTypeface(SKFontManager.Default.MatchCharacter('汉')) // <- Chinese 
               //.HasGlobalSKTypeface(SKFontManager.Default.MatchCharacter('あ')) // <- Japanese 
               //.HasGlobalSKTypeface(SKFontManager.Default.MatchCharacter('헬')) // <- Korean 
               //.HasGlobalSKTypeface(SKFontManager.Default.MatchCharacter('Ж'))  // <- Russian 

               //.HasGlobalSKTypeface(SKFontManager.Default.MatchCharacter('أ'))  // <- Arabic 
               //.UseRightToLeftSettings() // Enables right to left tooltips 

               // finally register your own mappers
               // you can learn more about mappers at:
               // https://livecharts.dev/docs/avalonia/2.0.0-rc2/Overview.Mappers

               // here we use the index as X, and the population as Y 
               .HasMap<City>((city, index) => new(index, city.Population))
           // .HasMap<Foo>( .... ) 
           // .HasMap<Bar>( .... ) 
           );
    }

    public override void OnFrameworkInitializationCompleted()
    {
        var plotViewModel = new PlotViewModel();
        var baseCalculateViewModel = new CalculateViewModel();

        var mainViewModel = new MainViewModel(baseCalculateViewModel, plotViewModel);

        Locator.CurrentMutable.RegisterConstant<IScreen>(mainViewModel);
        Locator.CurrentMutable.Register<IViewFor<DepositViewModel>>(() => new DepositView());
        Locator.CurrentMutable.Register<IViewFor<CalculateViewModel>>(() => new BaseCalculateView());

        if (Application.Current.ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
        {
            desktop.MainWindow = new MainWindow
            {
                DataContext = Locator.Current.GetService<IScreen>()
            };
            desktop.MainWindow.Show();

            desktop.Exit += (sender, e) =>
            {
                mainViewModel.SaveHistory();
            };
        }

        base.OnFrameworkInitializationCompleted();
    }
    public record City(string Name, double Population);
}
