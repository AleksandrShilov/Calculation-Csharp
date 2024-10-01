using System;
using SkiaSharp;
using ReactiveUI;
using System.Linq;
using System.Reactive;
using LiveChartsCore;
using LiveChartsCore.Defaults;
using System.Collections.Generic;
using LiveChartsCore.SkiaSharpView;
using LiveChartsCore.SkiaSharpView.Painting;


namespace SimpleCalc.ViewModels;


public class PlotViewModel : ViewModelBase
{
    private readonly int _step = 10000;

    private double _xMin = -10;
    private double _xMax = 10;

    private double _yMin = -10;
    private double _yMax = 10;
    
    private string _expression;
    
    private ISeries[] _series;
    
    private Axis[] _xAxes;
    private Axis[] _yAxes;

    private Models _model;

    public string Expression
    {
        get => _expression;
        set => this.RaiseAndSetIfChanged(ref _expression, value);
    }

    public double XMin
    {
        get => _xMin;
        set => this.RaiseAndSetIfChanged(ref _xMin, value);
    }

    public double XMax
    {
        get => _xMax;
        set => this.RaiseAndSetIfChanged(ref _xMax, value);
    }

    public double YMax
    {
        get => _yMax;
        set => this.RaiseAndSetIfChanged(ref _yMax, value);
    }

    public double YMin
    {
        get => _yMin;
        set => this.RaiseAndSetIfChanged(ref _yMin, value);
    }

    public ISeries[] Series
    {
        get => _series;
        private set => this.RaiseAndSetIfChanged(ref _series, value);
    }

    public Axis[] XAxes
    {
        get => _xAxes;
        private set => this.RaiseAndSetIfChanged(ref _xAxes, value);
    }

    public Axis[] YAxes
    {
        get => _yAxes;
        private set => this.RaiseAndSetIfChanged(ref _yAxes, value);
    }

    public ReactiveCommand<Unit, Unit> BuildPlotCommand { get; }

    public PlotViewModel()
    {
        BuildPlotCommand = ReactiveCommand.Create(BuildPlot);
        Series = new ISeries[] { };
        _model = new Models();

        CreateAxis();
    }

    private void BuildPlot()
    {
        try
        {
            XAxes[0].MinLimit = XMin;
            XAxes[0].MaxLimit = XMax;

            YAxes[0].MinLimit = YMin;
            YAxes[0].MaxLimit = YMax;

            List<double> xValues = new List<double>();
            List<double> yValues = new List<double>();

            double dynamicStep = (XMax - XMin) / _step;
            int sizeList = (int)((XMax / dynamicStep) + (XMin / dynamicStep));

            for (var i = XMin; i <= XMax; i += dynamicStep)
            {
                xValues.Add(i);

                var y = _model.GetResult(_expression, i);
                yValues.Add(y);
            }


            var points = xValues.Zip(yValues, (x, y) => new ObservablePoint(x, y)).ToList();

            Series = new ISeries[]
            {
                new LineSeries<ObservablePoint>
                {
                    Values = points,
                    Fill = null,
                    Stroke = new SolidColorPaint(SKColors.Blue),
                    GeometrySize = 0, // Убрать точки с линии
                    LineSmoothness = 0 // Прямая линия
                }
            };


        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }

    private void CreateAxis()
    {
        XAxes = new Axis[]
        {
            new Axis
            {
                Name = "X",
                MinLimit = XMin,
                MaxLimit = XMax,
                Labeler = value => value.ToString("N1"), // Формат меток оси Y
                SeparatorsPaint = new SolidColorPaint(SKColors.LightSlateGray) { StrokeThickness = 2 }, // Цвет разделителей
                UnitWidth = 1, // Шаг сетки
            }
        };

        YAxes = new Axis[]
        {
            new Axis
            {
                Name = "Y",
                MinLimit = YMin,
                MaxLimit = YMax,
                Labeler = value => value.ToString("N1"),
                SeparatorsPaint = new SolidColorPaint(SKColors.LightSlateGray)
                    {
                        StrokeThickness = 2,
                    } ,
                UnitWidth = 1,
            }
        };
    }
}

