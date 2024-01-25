using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using WpfUIExperiment.Model;

namespace WpfUIExperiment.ViewModel
{

    public class NodeViewModel : INotifyPropertyChanged
    {
        private string _label { get; set; }
        private DisplayMode? _displayMode { get; set; }
        private List<byte>? _largeIcon { get; set; }
        private List<byte>? _smallIcon { get; set; }
        private int _iconSize;
        private int _fontSize;
        private bool _selected;

        public string Label
        {
            get { return _label; }
            set
            {
                if (_label != value) {
                    _label = value;
                    OnPropertyChanged(nameof(Label));
                }
            }
        }
        public DisplayMode? DisplayMode
        {
            get { return _displayMode; }
            set
            {
                if (_displayMode != value) {
                    _displayMode = value;
                    OnPropertyChanged(nameof(DisplayMode));
                    OnPropertyChanged(nameof(DisplayTemplate));
                }
            }
        }

        public List<byte>? LargeIcon
        {
            get { return _largeIcon; }
            set
            {
                if (_largeIcon != value) {
                    _largeIcon = value;
                    OnPropertyChanged(nameof(LargeIcon));
                }
            }
        }
        public List<byte>? SmallIcon
        {
            get { return _smallIcon; }
            set
            {
                if (_smallIcon != value) {
                    _smallIcon = value;
                    OnPropertyChanged(nameof(SmallIcon));
                }
            }
        }

        public int IconSize
        {
            get { return _iconSize; }
            set
            {
                if (_iconSize != value) {
                    _iconSize = value;
                    OnPropertyChanged(nameof(IconSize));
                }
            }
        }

        public int FontSize
        {
            get { return _fontSize; }
            set
            {
                if (_fontSize != value) {
                    _fontSize = value;
                    OnPropertyChanged(nameof(FontSize));
                }
            }
        }

        public bool Selected
        {
            get { return _selected; }
            set
            {
                if (_selected != value) {
                    _selected = value;
                    OnPropertyChanged(nameof(Selected));
                }
            }
        }

        public NodeViewModel (Node baseNode)
        {
            Label = baseNode.Label;
            DisplayMode = baseNode.DisplayMode;
            LargeIcon = baseNode.LargeIcon;
            SmallIcon = baseNode.SmallIcon;
            Selected = false;
            IconSize = 64;
            FontSize = 12;
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        protected virtual void OnPropertyChanged (string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }


        private static readonly Dictionary<WpfUIExperiment.Model.DisplayMode, string> TemplateKeyMapping = new Dictionary<WpfUIExperiment.Model.DisplayMode, string>
        {
            { WpfUIExperiment.Model.DisplayMode.Bold, "BoldTextTemplate" },
            { WpfUIExperiment.Model.DisplayMode.Italic, "ItalicTextTemplate" },
            { WpfUIExperiment.Model.DisplayMode.Underlined, "UnderLinedTextTemplate" },
            { WpfUIExperiment.Model.DisplayMode.Regular, "RegularTextTemplate" },
        };



        public DataTemplate DisplayTemplate
        {
            get
            {
                var dict = (ResourceDictionary)Application.Current.MainWindow.FindResource("NodeViewModelResources");

                if (_displayMode == null)
                    return (DataTemplate)dict["RegularTextTemplate"];

                string templateKey = TemplateKeyMapping.GetValueOrDefault(_displayMode.Value, "RegularTextTemplate");

                if (dict.Contains(templateKey)) {
                    return (DataTemplate)dict[templateKey];
                } else {
                    // Handle error: Template not found
                    // You might want to log a warning or provide a default template
                    return (DataTemplate)dict["RegularTextTemplate"];
                }
            }
        }
    }
}
