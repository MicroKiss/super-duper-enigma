using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfUIExperiment.Model
{
    interface IConnector
    {
        //gets the root nodes ( startup nodes)
        public List<Node> GetRootNodes();
        //gets parent node od the given node at the index
        public Node GetRootNodeAtIndex(uint rootNodeIndex);
        //sets label at node with given index
        public void SetRootNodeLabel(uint rootNodeIndex, string label);
        //sets display at node with given index
        public void SetRootNodeDisplayMode(uint rootNodeIndex, DisplayMode? displayMode);
        //gets children from index
        public List<Node> GetChildrenOfRootNode(uint rootNodeIndex);
        //gets n-th kid from node at index
        public Node GetChildNodeAtIndex(uint rootNodeIndex, uint childNodeIndex);
        //sets n-th kid's label
        public void SetChildNodeLabel(uint rootNodeIndex, uint childNodeIndex, string label);
        //sets n-th kid's display
        public void SetChildNodeDisplayMode(uint rootNodeIndex, uint childNodeIndex, DisplayMode? displayMode);
    }


    class ConnectorMock : IConnector
    {
        Dictionary<uint, List<Node>> children;
        Dictionary<uint, Node> parents;
        List<Node> nodes;
        List<Node> rootNodes;
        public ConnectorMock()
        {

            nodes = new List<Node> {
                new Node("HomeWork ;)"),
                new Node("Videos"),
                new Node("Falling of Stalingrad"),
                new Node("Math"),
                new Node("Phisycs"),
                new Node("Cats"),
                new Node("Beginning"),
                new Node("End"),
                new Node("Aftermatch"),
                new Node("Games"),
            };


            rootNodes = new List<Node> { nodes[0], nodes[1], nodes[2] };

            children = new Dictionary<uint, List<Node>> {
                { 0, new List<Node>{ nodes[3], nodes[4] } },
                { 1, new List<Node>{ nodes[5] } },
                { 2, new List<Node>{ nodes[6], nodes[7], nodes[8], nodes[9] } },

            };
            parents = new Dictionary<uint, Node> { { 1, nodes[0] }, { 2, nodes[0] } };
        }

        public List<Node> GetRootNodes()
        {
            return rootNodes;
        }

        public Node GetRootNodeAtIndex(uint rootNodeIndex)
        {
            return parents[rootNodeIndex];
        }

        public void SetRootNodeLabel(uint rootNodeIndex, string label)
        {
            nodes[(int)rootNodeIndex].Label = label;
        }
        public void SetRootNodeDisplayMode(uint rootNodeIndex, DisplayMode? displayMode)
        {
            nodes[(int)rootNodeIndex].DisplayMode = displayMode;

        }
        public List<Node> GetChildrenOfRootNode(uint rootNodeIndex)
        {
            return children[rootNodeIndex];
        }
        public Node GetChildNodeAtIndex(uint rootNodeIndex, uint childNodeIndex)
        {
            return GetChildrenOfRootNode(rootNodeIndex)[(int)childNodeIndex];
        }
        public void SetChildNodeLabel(uint rootNodeIndex, uint childNodeIndex, string label)
        {
            GetChildNodeAtIndex(rootNodeIndex, childNodeIndex).Label = label;
        }
        public void SetChildNodeDisplayMode(uint rootNodeIndex, uint childNodeIndex, DisplayMode? displayMode)
        {
            GetChildNodeAtIndex(rootNodeIndex, childNodeIndex).DisplayMode = displayMode;
        }
    }
}
