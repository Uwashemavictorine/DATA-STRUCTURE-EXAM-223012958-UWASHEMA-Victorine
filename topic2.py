
# Topic 2: Implement Deque and Linked List for Drone Tracking System
from collections import deque

# Deque for storing active drones (front: oldest, rear: newest)
active_drones = deque(["Drone1", "Drone2", "Drone3"])

# Add new drone
active_drones.append("Drone4")
# Remove a drone from the front (oldest drone)
active_drones.popleft()

print("Active Drones after updates:", list(active_drones))
