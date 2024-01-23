﻿using System;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Collections.ObjectModel;
using System.Globalization;
using System.IO;
using static System.Net.Mime.MediaTypeNames;
using Image = System.Windows.Controls.Image;

namespace WpfApp1
{

    public partial class MainWindow : Window
    {
        public ObservableCollection<Node> NodeCollection { get; set; }
        enum DisplayType
        {
            Large,
            Small,
            //List ???
        }


        public MainWindow ()
        {
            InitializeComponent();
            // Initialize the NodeCollection and add sample nodes
            NodeCollection = new ObservableCollection<Node>
            {
                new Node ( "Node 1" ),
                new Node ( "Node 2" ),
                // Add more sample nodes as needed
            };

            // Set the DataContext of the window to this instance
            DataContext = this;

        }

        private void OnItemClicked (object sender, MouseButtonEventArgs e)
        {
            if (sender is FrameworkElement clickedElement && clickedElement.DataContext is Node clickedNode) {
                // Handle the click event logic here
                MessageBox.Show($"Node clicked: {clickedNode.Label}");
            }
        }
        private void OnLargeClicked (object sender, MouseButtonEventArgs e)
        {
            ChangeDisplayType(DisplayType.Large);
        }        
        private void OnSmallClicked (object sender, MouseButtonEventArgs e)
        {
            ChangeDisplayType(DisplayType.Small);
        }


        private void ChangeDisplayType (DisplayType newType) {

            if (newType == DisplayType.Large) {
                ChangeIconsSize(64, 12);
            } else if (newType == DisplayType.Small) {
                ChangeIconsSize(32, 10);
            }

        }

        private void ChangeIconsSize (int imageSize, int fontSize) 
        {

            foreach (var node in NodeCollection) {
                var itemContainer = itemsControl.ItemContainerGenerator.ContainerFromItem(node) as ContentPresenter;
                var dataTemplate = itemsControl.ItemTemplate;
                var image = FindVisualChild<Image>(itemContainer, "myImage");
                var textBlock = FindVisualChild<TextBlock>(itemContainer, "myLabel");

                if (image != null && textBlock != null) {
                    image.Width = imageSize;
                    image.Height = imageSize;

                    textBlock.FontSize = fontSize;
                }
            }
        }
        private T FindVisualChild<T> (DependencyObject parent, string name) where T : DependencyObject
        {
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(parent); i++) {
                var child = VisualTreeHelper.GetChild(parent, i);

                if (child is T typedChild && (child as FrameworkElement)?.Name == name) {
                    return typedChild;
                }

                var result = FindVisualChild<T>(child, name);
                if (result != null)
                    return result;
            }

            return null;
        }
    }

    public class BytesToImageSourceConverter : IValueConverter
    {
        public object Convert (object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is List<byte> byteList) {
                BitmapImage bitmapImage = new BitmapImage();
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
}