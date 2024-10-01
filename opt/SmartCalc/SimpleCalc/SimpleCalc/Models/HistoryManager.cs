using System;
using System.IO;
using System.Collections.ObjectModel;
using DynamicData;
using System.Linq;


namespace SimpleCalc.Models;


public class HistoryManager
{
    private readonly string _historyFilePath;

    public HistoryManager()
    {
        _historyFilePath = Path.Combine(Environment.CurrentDirectory, "SmartCalc_V_3.0", "history.txt");

        Directory.CreateDirectory(Path.GetDirectoryName(_historyFilePath));
    }

    public void SaveHistory(SourceList<string> historyItems)
    {
        try
        {
            File.WriteAllLines(_historyFilePath, historyItems.Items.ToArray());
        }
        catch (Exception ex)
        {
            // Обработка исключений (логирование, оповещение пользователя и т.д.)
        }
    }

    public void LoadHistory(SourceList<string> _historyItems)
    {
        try
        {
            if (File.Exists(_historyFilePath))
            {
                var lines = File.ReadAllLines(_historyFilePath);
                foreach (var line in lines)
                {
                    _historyItems.Add(line);
                }
            }
        }
        catch (Exception ex)
        {
            // Обработка исключений (логирование, оповещение пользователя и т.д.)
        }
    }
}


