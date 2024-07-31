using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.ComponentModel;

namespace SimpleCalc.ViewModels;

public partial class BaseCalculateViewModel : ViewModelBase
{
    public BaseCalculateViewModel()
    {
        // ������������� �������
        OnButtonClickedCommand = new RelayCommand(OnButtonClicked);
    }

    // ������� ��� ������
    public RelayCommand OnButtonClickedCommand { get; }

    [ObservableProperty]
    private string _yourProperty;

    private void OnButtonClicked()
    {
        // ��� ��� ��������� ������� ������
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
