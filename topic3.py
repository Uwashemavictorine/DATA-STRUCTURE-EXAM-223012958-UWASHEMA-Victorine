
# Topic 3: Implement Heap for Priority Processing in Drone Tracking
import heapq

# Priority queue for drone deliveries (lower number -> higher priority)
deliveries = [(3, 'Package3'), (1, 'Package1'), (2, 'Package2')]
heapq.heapify(deliveries)

# Add a new delivery with priority
heapq.heappush(deliveries, (0, 'EmergencyPackage'))

# Process deliveries by priority
while deliveries:
    print("Processing:", heapq.heappop(deliveries))
