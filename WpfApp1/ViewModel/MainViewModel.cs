using System;
using System.Collections.ObjectModel;
using WpfApp1.Model;
using WpfApp1.Commands;
using System.Windows.Input;
using WpfApp1.Services;
using System.ComponentModel;

namespace WpfApp1.ViewModel
{
    internal class MainViewModel : INotifyPropertyChanged
    {
        private ConnectorMock connector;

        private ObservableCollection<ViewNode> _nodes;
        public ObservableCollection<ViewNode> Nodes
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
        public ICommand LargeIconsCommand { get; set; }
        public ICommand SmallIconsCommand { get; set; }
        public ICommand SelectNodeCommand { get; set; }
        public ICommand OpenNodeCommand { get; set; }
        public ICommand BackToRootCommand { get; set; }

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

            LargeIconsCommand = new RelayCommand(ShowLargeIcons, CanShowLargeIcons);
            SmallIconsCommand = new RelayCommand(ShowSmallIcons, CanShowSmallIcons);
            SelectNodeCommand = new RelayCommand(HandleSelectNode, CanHandleSelectNode);
            OpenNodeCommand = new RelayCommand(HandleOpenNode, CanHandleOpenNode);
            BackToRootCommand = new RelayCommand(HandleBackToRoot, CanHandleBackToRoot);
            selectedNodeIndex = null;
            atRootLevel = true;
            CurrentNodeName = "Root";
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
        }

        private bool CanHandleOpenNode (object obj)
        {
            return true;
        }

        private void HandleOpenNode (object obj)
        {
            if (!atRootLevel)
                return;
            if (obj is ViewNode currentNode) {
                uint index = (uint)Nodes.IndexOf(currentNode);
                Nodes = NodeConverterService.ConvertNodesToViewNodes(connector.GetChildrenOfRootNode(index));
                CurrentNodeName = currentNode.BaseNode.Label;
                selectedNodeIndex = null;
                atRootLevel = false;
            }
        }

        private bool CanHandleSelectNode (object obj)
        {
            return true;
        }

        private void HandleSelectNode (object obj)
        {
            if (obj is ViewNode currentNode) {
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
            ChangeIconAndFontSize(32, 10);
        }

        private bool CanShowLargeIcons (object obj)
        {
            return true;
        }

        private void ShowLargeIcons (object obj)
        {
            ChangeIconAndFontSize(64, 12);
        }

        private void ChangeIconAndFontSize (int iconSize, int fontSize) {
            foreach (ViewNode node in Nodes) {
                node.IconSize = iconSize;
                node.FontSize = fontSize;
            }
        }
    }
}
