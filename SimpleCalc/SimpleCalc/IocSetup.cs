using SimpleCalc.Views;
using SimpleCalc.ViewModels;
using Microsoft.Extensions.DependencyInjection;
using CommunityToolkit.Mvvm.DependencyInjection;

namespace SimpleCalc;

public static class IocSetup
{
    public static void ConfigureServices()
    {
        var services = new ServiceCollection();

        // Регистрация ViewModels
        services.AddTransient<MainViewModel>();
        services.AddTransient<BaseCalculateViewModel>();
        services.AddTransient<DepositViewModel>();

        // Регистрация Views
        services.AddTransient<MainWindow>();
        services.AddTransient<BaseCalculateView>();
        services.AddTransient<DepositView>();

        Ioc.Default.ConfigureServices(services.BuildServiceProvider());
    }
}
