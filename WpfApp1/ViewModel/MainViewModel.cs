using System;
using System.Collections.ObjectModel;
using WpfApp1.Model;
using WpfApp1.Commands;
using System.Windows.Input;
using WpfApp1.Services;
using System.ComponentModel;
using System.Windows;
using System.Reflection.Metadata;

namespace WpfApp1.ViewModel
{
    enum View
    {
        smallIcons,
        largeIcons,
        list
    }
    internal class MainViewModel : INotifyPropertyChanged
    {
        private ConnectorMock connector;
        private View viewType;

        private ObservableCollection<NodeViewModel> _nodes;
        public ObservableCollection<NodeViewModel> Nodes
        {
            get { return _nodes; }
            set
            {
                if (_nodes != value) {
                    _nodes = value;
                    OnPropertyChanged(nameof(Nodes));
                }
            }
        }

        private string _currentNodeName;
        public string CurrentNodeName
        {
            get { return _currentNodeName; }
            set
            {
                if (_currentNodeName != value) {
                    _currentNodeName = value;
                    OnPropertyChanged(nameof(CurrentNodeName));
                }
            }
        }

        private Point _mousePosition;

        public Point MousePosition
        {
            get { return _mousePosition; }
            set
            {
                if (_mousePosition != value) {
                    _mousePosition = value;
                    OnPropertyChanged(nameof(MousePosition));
                }
            }
        }



        public ICommand LargeIconsCommand { get; set; }
        public ICommand SmallIconsCommand { get; set; }
        public ICommand SelectNodeCommand { get; set; }
        public ICommand SelectNothingCommand { get; set; }
        public ICommand OpenNodeCommand { get; set; }
        public ICommand BackToRootCommand { get; set; }
        public ICommand CloseCommand { get; set; }
        public ICommand ChangeFontCommand { get; set; }

        private int? selectedNodeIndex;
        private bool atRootLevel;

        public event PropertyChangedEventHandler? PropertyChanged;
        protected virtual void OnPropertyChanged (string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public MainViewModel ()
        {
            connector = new ConnectorMock();
            Nodes = NodeConverterService.ConvertNodesToViewNodes(connector.GetRootNodes());
            MousePosition = new Point(0, 0);
            viewType = View.largeIcons;

            LargeIconsCommand = new RelayCommand(ShowLargeIcons, CanShowLargeIcons);
            SmallIconsCommand = new RelayCommand(ShowSmallIcons, CanShowSmallIcons);
            SelectNodeCommand = new RelayCommand(HandleSelectNode, CanHandleSelectNode);
            SelectNothingCommand = new RelayCommand(HandleSelectNothing, CanHandleSelectNothing);
            OpenNodeCommand = new RelayCommand(HandleOpenNode, CanHandleOpenNode);
            BackToRootCommand = new RelayCommand(HandleBackToRoot, CanHandleBackToRoot);
            CloseCommand = new RelayCommand(HandleClose, CanHandleClose);
            ChangeFontCommand = new RelayCommand(HandleChangeFont, CanHandleHandleChangeFont);
            selectedNodeIndex = null;

            atRootLevel = true;
            CurrentNodeName = "Root";
        }

        private bool CanHandleHandleChangeFont (object obj)
        {
            return true;
        }

        private void HandleChangeFont (object obj)
        {
            if (selectedNodeIndex != null) {
                var currentDisplayMode = Nodes[selectedNodeIndex.Value].DisplayMode;
                var newDisplayMode = (DisplayMode)(((int)currentDisplayMode.Value + 1) % Enum.GetValues(typeof(DisplayMode)).Length);
                Nodes[selectedNodeIndex.Value].DisplayMode = newDisplayMode;
            } else {
                foreach (NodeViewModel node in Nodes) {
                    var currentDisplayMode = node.DisplayMode;
                    var newDisplayMode = (DisplayMode)(((int)currentDisplayMode.Value + 1) % Enum.GetValues(typeof(DisplayMode)).Length);
                    node.DisplayMode = newDisplayMode;
                }
            }
        }

        private bool CanHandleClose (object obj)
        {
            return true;
        }

        private void HandleClose (object obj)
        {
            (obj as Window)?.Close();
        }

        private bool CanHandleSelectNothing (object obj)
        {
            return true;
        }

        private void HandleSelectNothing (object obj)
        {
            if (selectedNodeIndex != null) {
                Nodes[selectedNodeIndex.Value].Selected = false;
            selectedNodeIndex = null;
            }
        }

        private bool CanHandleBackToRoot (object obj)
        {
            return true;
        }

        private void HandleBackToRoot (object obj)
        {
            Nodes = NodeConverterService.ConvertNodesToViewNodes(connector.GetRootNodes());
            selectedNodeIndex = null;
            atRootLevel = true;
            CurrentNodeName = "Root";
            ChangeToViewType(viewType);
        }

        private bool CanHandleOpenNode (object obj)
        {
            return true;
        }

        private void HandleOpenNode (object obj)
        {
            if (!atRootLevel)
                return;
            if (obj is NodeViewModel currentNode) {
                uint index = (uint)Nodes.IndexOf(currentNode);
                Nodes = NodeConverterService.ConvertNodesToViewNodes(connector.GetChildrenOfRootNode(index));
                CurrentNodeName = currentNode.Label;
                selectedNodeIndex = null;
                atRootLevel = false;
                ChangeToViewType(viewType);
            }
        }

        private bool CanHandleSelectNode (object obj)
        {
            return true;
        }

        private void HandleSelectNode (object obj)
        {
            if (obj is NodeViewModel currentNode) {
                int index = Nodes.IndexOf(currentNode);

                if (selectedNodeIndex != null) {
                    if (index == selectedNodeIndex)
                        return;
                    Nodes[selectedNodeIndex.Value].Selected = false;
                }
                selectedNodeIndex = index;
                currentNode.Selected = true;
            }
        }


        private bool CanShowSmallIcons (object obj)
        {
            return true;
        }

        private void ShowSmallIcons (object obj)
        {
            ChangeToViewType(View.smallIcons);
        }

        private bool CanShowLargeIcons (object obj)
        {
            return true;
        }

        private void ShowLargeIcons (object obj)
        {
            ChangeToViewType(View.largeIcons);
        }

        private void ChangeToViewType (View newType) {
            switch (newType) {
                case View.smallIcons:
                    ChangeIconAndFontSize(32, 10);
                    break;
                case View.largeIcons:
                    ChangeIconAndFontSize(64, 12);
                    break;
                case View.list:
                    throw new NotImplementedException();
                    break;
                default:
                    throw new NotImplementedException();
                    break;
            }
            viewType = newType;
        }

        private void ChangeIconAndFontSize (int iconSize, int fontSize) {
            foreach (NodeViewModel node in Nodes) {
                node.IconSize = iconSize;
                node.FontSize = fontSize;
            }
        }
    }
}
