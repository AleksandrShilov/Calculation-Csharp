using System;
using Avalonia;
using ReactiveUI;
using DynamicData;
using System.Reactive;
using SimpleCalc.Views;
using System.Windows.Input;
using System.Runtime.Serialization;
using Avalonia.Controls.ApplicationLifetimes;
using System.Collections.ObjectModel;


namespace SimpleCalc.ViewModels;


public partial class MainViewModel : ViewModelBase, IScreen
{
    private bool _isMenuOpen = false;
    private bool _isHistoryVisible = false;
    private int _windowWidth = 310;
    private int _indentationBtnHist = 185;
    private string _currentMode = "Обычный";
    private string _selectedItem;

    private PlotViewModel _plotViewModel;
    private DepositViewModel _depositViewModel;
    private RoutingState _router = new RoutingState();

    private CalculateViewModel BaseViewCalcModel { get; set; }
    public ReadOnlyObservableCollection<string> HistoryItems { get; private set; }


    [DataMember]
    public RoutingState Router
    {
        get => _router;
        set => this.RaiseAndSetIfChanged(ref _router, value);
    }

    public bool IsMenuOpen
    {
        get => _isMenuOpen;
        set => this.RaiseAndSetIfChanged(ref _isMenuOpen, value);
    }       

    public bool IsHistoryVisible
    {
        get => _isHistoryVisible;
        set => this.RaiseAndSetIfChanged(ref _isHistoryVisible, value);
    }

    public string CurrentMode 
    {
        get => _currentMode;
        set => this.RaiseAndSetIfChanged(ref _currentMode, value);
    }

    public string SelectedItem
    {
        get => _selectedItem;
        set
        {
            if(value != null)
                BaseViewCalcModel.ShownValue = value;
            
            this.RaiseAndSetIfChanged(ref _selectedItem, value);
        }
    }

    public int WindowWidth
    {
        get => _windowWidth;
        set => this.RaiseAndSetIfChanged(ref _windowWidth, value);
    }

    public int IndentationBtnHist
    {
        get => _indentationBtnHist;
        set => this.RaiseAndSetIfChanged(ref _indentationBtnHist, value);
    }


    public ReactiveCommand<Unit, Unit> OpenAboutCommand { get; }
    public ReactiveCommand<Unit, Unit> OpenPlotViewCommand { get; }
    public ReactiveCommand<Unit, Unit> ClearHistoryCommand { get; }
    public ReactiveCommand<Unit, Unit> TriggerMenuCommand { get; }
    public ReactiveCommand<Unit, Unit> ShowHistoryCommand { get; }
    public ReactiveCommand<string, Unit> AddToHistoryCommand { get; }

    private readonly ReactiveCommand<Unit, Unit> DepositDisplayCommand;
    private readonly ReactiveCommand<string, Unit> BaseCalculateDisplayCommand;

    public MainViewModel(CalculateViewModel baseCalculateViewModel, PlotViewModel plotViewModel)
    {
        _plotViewModel = plotViewModel;
        BaseViewCalcModel = baseCalculateViewModel;

        Router.Navigate.Execute(baseCalculateViewModel);

        BaseViewCalcModel.HistoryItemsChanges
              .Transform(item => item)
              .Bind(out var readOnlyHistoryItems)
              .Subscribe();

        HistoryItems = readOnlyHistoryItems;

        OpenAboutCommand = ReactiveCommand.Create(OpenAbout);
        ShowHistoryCommand = ReactiveCommand.Create(ShowHistory);
        TriggerMenuCommand = ReactiveCommand.Create(TriggerMenu);
        OpenPlotViewCommand = ReactiveCommand.Create(OpenPlotView);
        ClearHistoryCommand = ReactiveCommand.Create(ClearHistory);

        DepositDisplayCommand = ReactiveCommand.Create(DepositDisplay);
        BaseCalculateDisplayCommand = ReactiveCommand.Create<string>(BaseCalculateDisplay);
    }


    private void ShowHistory()
    {
        IsHistoryVisible = !IsHistoryVisible;
    }

    public void ClearHistory()
    {
        BaseViewCalcModel.ClearHistory();
    }

    public void SaveHistory()
    {
        BaseViewCalcModel.SaveHistory();
    }

    private void TriggerMenu()
    {
        IsMenuOpen = !IsMenuOpen;
    }

    private void DepositDisplay()
    {
        if (_depositViewModel != null)
        {
            Router.Navigate.Execute(_depositViewModel);
        }
        else
        {
            Router.Navigate.Execute(new DepositViewModel());
        }
    }

    private void BaseCalculateDisplay(string selectedMode)
    {
        CurrentMode = selectedMode;
        if(selectedMode.Equals("Расширенный"))
        {
            
            WindowWidth = WindowWidth == 315 ? WindowWidth + 200 : WindowWidth;
            IndentationBtnHist = IndentationBtnHist == 185 ? IndentationBtnHist + 200 : IndentationBtnHist;
            BaseViewCalcModel.IsBaseCalcVisible = false;
            BaseViewCalcModel.IsAdditionalBtnVisible = true;
        }
        else if (selectedMode.Equals("Обычный"))
        {
            WindowWidth -= 200;
            IndentationBtnHist -= 200;
            BaseViewCalcModel.IsBaseCalcVisible = true;
            BaseViewCalcModel.IsAdditionalBtnVisible = false;
        }

        Router.Navigate.Execute(BaseViewCalcModel);
    }

    private void OpenAbout()
    {
        var aboutWindow = new AboutView();

        if (Application.Current.ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktopLifetime)
        {
            // Открытие модального окна
            aboutWindow.ShowDialog(desktopLifetime.MainWindow);
        }
    }

    private void OpenPlotView()
    {
        try
        {
            _plotViewModel.Expression = BaseViewCalcModel.ShownValue;

            var plotDialog = new PlotView()
            {
                DataContext = _plotViewModel
            };

            if (Application.Current.ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktopLifetime)
            {
                plotDialog.ShowDialog(desktopLifetime.MainWindow);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Exception: {ex.Message}");
            throw;
        }
    }


    public ICommand IDepositDisplayCommand => DepositDisplayCommand;
    public ICommand IBaseCalculateDisplayCommand => BaseCalculateDisplayCommand;
}
