# RailOptiNav C++ Project
RailOptiNav is a Railway Ticket Reservation System that addresses the challenges inherent in traditional ticket booking systems. The project aims to create a console based and efficient platform for booking train tickets, focusing on user authentication, optimal route planning, and seat reservation for different classes. The objective is to streamline the ticket booking process, enhance user experience, and optimize resource utilization in the railway network. 

The project employs several fundamental Data Structure concepts using C++, showcasing a robust foundation for efficient operations namely Priority Queues based Min-Heaps, Dijkstra's Algorithm, Dynamic Arrays, Hashing and Graphs.


# -> Description of Used Data Structure Concepts:
Hash Table:
Hash tables are instrumental in user authentication and management, with usernames as keys and user account details as values, the system ensures constant time complexity for key operations like insertion, retrieval, and deletion. Chaining concept is used to resolve collisions using Linked Lists.

Graph:
The representation of the railway network as an undirected graph facilitates efficient route planning. Dijkstra's algorithm, implemented on the adjacency matrix, provides the shortest path between two cities, optimizing the overall travel experience.

Dynamic Array:
Dynamic arrays are employed in implementing the adjacency matrix, offering flexibility in resizing as the railway network expands. This ensures efficient memory utilization as the system dynamically adjusts to changes.

Priority Queue & Min-Heap:
The project incorporates a min heap based priority queue specifically for the efficient implementation of Dijkstra's algorithm. It enables the prioritization of cities based on their distances, expediting the search for the optimal path during route planning. By ensuring the selection of the city with the smallest distance first during traversal, the algorithm's overall time efficiency is enhanced.


# -> Efficiency Analysis:
Time Complexity:
The utilization of Dijkstra's algorithm for route planning ensures a time complexity of O ((V + E) log V), where V is the number of vertices (cities) and E is the number of edges (routes). This efficient algorithm provides an optimal solution for finding the shortest path.

Space Complexity:
The primary contributor to space complexity is the adjacency matrix representing the graph, with O(V^2) complexity for V vertices. The hash table introduces an additional O(V) space. Overall, the project maintains reasonable space complexity for the given problem scale.
