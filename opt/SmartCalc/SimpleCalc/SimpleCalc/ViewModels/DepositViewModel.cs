using Splat;
using ReactiveUI;
using System.Runtime.Serialization;


namespace SimpleCalc.ViewModels;


public class DepositViewModel : ViewModelBase, IRoutableViewModel
{
    private string _searchQuery;
    public IScreen HostScreen { get; }


    [DataMember]
    public string SearchQuery
    {
        get => _searchQuery;
        set => this.RaiseAndSetIfChanged(ref _searchQuery, value);
    }

    public string UrlPathSegment => "/search";
    

    public DepositViewModel(IScreen screen = null)
    {
        HostScreen = screen ?? Locator.Current.GetService<IScreen>();
    }
}