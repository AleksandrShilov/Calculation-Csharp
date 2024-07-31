using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.ComponentModel;

namespace SimpleCalc.ViewModels;

public partial class BaseCalculateViewModel : ViewModelBase
{
    public BaseCalculateViewModel()
    {
        // Инициализация команды
        OnButtonClickedCommand = new RelayCommand(OnButtonClicked);
    }

    // Команда для кнопки
    public RelayCommand OnButtonClickedCommand { get; }

    [ObservableProperty]
    private string _yourProperty;

    private void OnButtonClicked()
    {
        // Ваш код обработки нажатия кнопки
        YourProperty = _yourProperty + "7";
    }

    public void AddNumber(int value)
    {

    }
}

//public class BaseCalculateViewModel : ViewModelBase 
//{
//    private double _secondValue;

//    public double ShownValue
//    {
//        get => _secondValue;
//        set => this.RaiseAndSelfChanged(ref _secondValue, value);
//    }

//    public void AddNumber(int value)
//    {

//    }
//}
