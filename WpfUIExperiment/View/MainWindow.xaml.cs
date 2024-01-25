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
using static WpfUIExperiment.MainWindow;
using WpfUIExperiment.Model;
using WpfUIExperiment.ViewModel;

namespace WpfUIExperiment
{

    public partial class MainWindow : Window
    {
        public MainWindow ()
        {
            InitializeComponent();
            MainViewModel mainViewModel = new ();
            DataContext = mainViewModel;
        }

        private void OnMouseMove (object sender, MouseEventArgs e)
        {
            if (DataContext is MainViewModel viewModel)
                viewModel.MousePosition = e.GetPosition((IInputElement)sender);
        }

        private void StackPanel_MouseLeftButtonDown (object sender, MouseButtonEventArgs e)
        {
            // Check if the sender is a FrameworkElement
            if (sender is FrameworkElement frameworkElement) {
                // Access the data context if it's set
                if (frameworkElement.DataContext is NodeViewModel vnode) {
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

        private void itemsControl_MouseLeftButtonDown (object sender, MouseButtonEventArgs e)
        {
            // Get the UI element that was clicked
            var clickedElement = e.OriginalSource as UIElement;

            // Check if the click was on the StackPanel or its children
            if (!IsClickOnStackPanel(clickedElement)) {
                if (DataContext is MainViewModel viewModel)
                    viewModel.SelectNothingCommand.Execute(sender);
            }
        }

        private bool IsClickOnStackPanel (UIElement clickedElement)
        {
            // Check if the clicked element is a StackPanel or its child
            while (clickedElement != null) {
                if (clickedElement is StackPanel) {
                    return true;
                }

                clickedElement = VisualTreeHelper.GetParent(clickedElement) as UIElement;
            }

            return false;
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
            if (value is NodeViewModel vnode) {
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
