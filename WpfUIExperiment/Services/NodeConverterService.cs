using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfUIExperiment.Model;
using WpfUIExperiment.ViewModel;

namespace WpfUIExperiment.Services
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
