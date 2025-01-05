
# Topic 5: Queue for Dynamic Data Tracking
from queue import Queue

# Queue to track incoming orders
order_queue = Queue()
order_queue.put("Order1")
order_queue.put("Order2")

# Process orders dynamically
while not order_queue.empty():
    print("Processing:", order_queue.get())
