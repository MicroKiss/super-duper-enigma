using System.ComponentModel;
using WpfApp1.Model;

namespace WpfApp1.ViewModel
{
    
    public class ViewNode : INotifyPropertyChanged
    {
        public Node BaseNode { get; }
        private int _iconSize;
        private int _fontSize;
        private bool _selected;

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

        public ViewNode (Node baseNode)
        {
            BaseNode = baseNode;
            Selected = false;
            IconSize = 64;
            FontSize = 12;
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        protected virtual void OnPropertyChanged (string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
