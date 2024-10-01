using Splat;
using System;
using Avalonia;
using ReactiveUI;
using DynamicData;
using System.Reactive;
using SimpleCalc.Models;
using System.Runtime.Serialization;
using Avalonia.Controls.ApplicationLifetimes;


namespace SimpleCalc.ViewModels;


public class CalculateViewModel : ViewModelBase, IRoutableViewModel
{
    private string _searchQuery;
    private string _calcExpresion;
    private string _displayStr = "0";
    private bool _isBaseCalcVisible = true;
    private bool _isAdditionalBtnVisible = false;

    private Models _model = new Models();
    private readonly HistoryManager _historyManager = new HistoryManager();
    private SourceList<string> _historyItems { get; set; } = new SourceList<string>();

    public IObservable<IChangeSet<string>> HistoryItemsChanges => _historyItems.Connect();


    [DataMember]
    public string SearchQuery
    {
        get => _searchQuery;
        set => this.RaiseAndSetIfChanged(ref _searchQuery, value);
    }

    public string ShownValue
    {
        get => _displayStr;
        set => this.RaiseAndSetIfChanged(ref _displayStr, value);
    }

    public string ShownCalculateExpresion
    {
        get => _calcExpresion;
        set => this.RaiseAndSetIfChanged(ref _calcExpresion, value);
    }

    public bool IsAdditionalBtnVisible
    {
        get => _isAdditionalBtnVisible;
        set => this.RaiseAndSetIfChanged(ref _isAdditionalBtnVisible, value);
    }    
    
    public bool IsBaseCalcVisible
    {
        get => _isBaseCalcVisible;
        set => this.RaiseAndSetIfChanged(ref _isBaseCalcVisible, value);
    }


    public ReactiveCommand<string, Unit> AddCharCommand { get; }
    public ReactiveCommand<string, Unit> RemoveLastCharCommand { get; }
    public ReactiveCommand<Unit, Unit> RemoveAllStrCommand { get; }
    public ReactiveCommand<Unit, Unit> CalculateCommand { get; }
    public ReactiveCommand<Unit, Unit> TextBoxClickCommand { get; }


    public CalculateViewModel(IScreen screen = null)
    {
        HostScreen = screen ?? Locator.Current.GetService<IScreen>();

        _historyManager.LoadHistory(_historyItems);

        AddCharCommand = ReactiveCommand.Create<string>(AddChar);
        RemoveLastCharCommand = ReactiveCommand.Create<string>(RemoveLastChar);
        RemoveAllStrCommand = ReactiveCommand.Create(RemoveAllStr);
        CalculateCommand = ReactiveCommand.Create(Calculate);
    }

    private async void Calculate()
    {
        double x = 0;
        
        string historyNewStr = ShownValue;
        
        if(historyNewStr.Contains('x'))
        {
            var dialog = new InputXView();

            if (Application.Current.ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktopLifetime)
            {
                var result = await dialog.ShowDialog<string>(desktopLifetime.MainWindow);

                if (result == null || !double.TryParse(result, out x))
                {
                    x = 0;
                }
            }

        }


        ShownValue = Convert.ToString(_model.GetResult(_displayStr, x));

        historyNewStr += "=" + ShownValue;
        _historyItems.Add(historyNewStr);

        ShownCalculateExpresion = historyNewStr;
    }


    private void AddChar(string value)
    {
        if (ShownValue.Length == 1 && ShownValue.Equals("0"))
            ShownValue = value;
        else
            ShownValue += value;
    }

    public void RemoveLastChar(string value)
    {
        if (ShownValue.Length == 1)
            ShownValue = "0";
        else if (ShownValue.Length > 1)
            ShownValue = ShownValue.Remove((ShownValue.Length - 1), 1);
    }    
    
    public void RemoveAllStr()
    {
        ShownValue = "0";
    }

    public void ClearHistory()
    {
        _historyItems.Clear();
    }   
    
    public void SaveHistory()
    {
       _historyManager.SaveHistory(_historyItems);
    }

    public string UrlPathSegment => "/search";

    public IScreen HostScreen { get; }
}
