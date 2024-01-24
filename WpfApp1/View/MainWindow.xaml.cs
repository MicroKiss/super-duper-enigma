using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Collections.ObjectModel;
using System.Globalization;
using System.IO;
using Image = System.Windows.Controls.Image;
using System.ComponentModel;
using static WpfApp1.MainWindow;
using WpfApp1.Model;
using WpfApp1.ViewModel;

namespace WpfApp1
{

    public partial class MainWindow : Window
    {
        public MainWindow ()
        {
            InitializeComponent();
            MainViewModel mainViewModel = new ();
            DataContext = mainViewModel;
        }

        private void StackPanel_MouseLeftButtonDown (object sender, MouseButtonEventArgs e)
        {
            // Check if the sender is a FrameworkElement
            if (sender is FrameworkElement frameworkElement) {
                // Access the data context if it's set
                if (frameworkElement.DataContext is ViewNode vnode) {
                    if (DataContext is MainViewModel viewModel) {
                        if (e.ClickCount == 1) { 
                            viewModel.SelectNodeCommand.Execute(vnode);
                        } else {
                            viewModel.OpenNodeCommand.Execute(vnode);
                        }
                    }
                }
            }
        }
    }

    public class BytesToImageSourceConverter : IValueConverter
    {
        public object Convert (object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is List<byte> byteList) {
                BitmapImage bitmapImage = new ();
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = new MemoryStream(byteList.ToArray());
                bitmapImage.EndInit();
                return bitmapImage;
            }
            return null;
        }

        public object ConvertBack (object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

    public class YourValueConverter : IValueConverter
    {
        public object Convert (object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is ViewNode vnode) {
                return vnode.Selected;
            }
            return false; 
                
        }

        public object ConvertBack (object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }

}
