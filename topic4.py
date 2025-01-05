
# Topic 4: Linked List for Fixed Number of Orders
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
        self.size = 0
        self.limit = 5  # Limit for fixed number of orders

    def add_order(self, order):
        if self.size == self.limit:
            print("Order limit reached. Cannot add more orders.")
            return
        new_node = Node(order)
        new_node.next = self.head
        self.head = new_node
        self.size += 1

    def display_orders(self):
        current = self.head
        while current:
            print(current.data)
            current = current.next

orders_list = LinkedList()
orders_list.add_order("Order1")
orders_list.add_order("Order2")
orders_list.add_order("Order3")
orders_list.display_orders()
