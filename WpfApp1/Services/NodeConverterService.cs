using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfApp1.Model;
using WpfApp1.ViewModel;

namespace WpfApp1.Services
{
    public class NodeConverterService
    {
        static public ObservableCollection<NodeViewModel> ConvertNodesToViewNodes (List<Node> nodes)
        {
            return new ObservableCollection<NodeViewModel>(
                nodes.Select(node => new NodeViewModel(node))
            );
        }
    }
}
