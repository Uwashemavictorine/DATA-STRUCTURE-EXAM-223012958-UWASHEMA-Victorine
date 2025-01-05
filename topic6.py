
# Topic 6: Tree for Hierarchical Data Representation
class TreeNode:
    def __init__(self, name):
        self.name = name
        self.children = []

    def add_child(self, child_node):
        self.children.append(child_node)

    def display(self, level=0):
        print(" " * level * 2, self.name)
        for child in self.children:
            child.display(level + 1)

# Create hierarchy for drone hubs
root = TreeNode("Main Hub")
hub1 = TreeNode("Hub 1")
hub2 = TreeNode("Hub 2")

root.add_child(hub1)
root.add_child(hub2)
hub1.add_child(TreeNode("Drone A"))
hub2.add_child(TreeNode("Drone B"))

root.display()
