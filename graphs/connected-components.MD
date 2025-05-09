# Algoritmo di Kosaraju per SCC - Pseudocodice Commentato
/**
 * ================================================
 * MAIN ALGORITHM
 * ================================================
 * Input: Directed graph G = (V, E)
 * Output: List of strongly connected components (SCCs)
 * Complexity: O(V + E)
 */
ALGORITHM FindSCCs(graph)
    // --------------------------------------------
    // Phase 1: Order nodes by finishing time
    // --------------------------------------------
    stack = new Stack()  // LIFO structure for node ordering
    time = 0             // Global DFS timer
    
    // Initialize nodes
    FOR EACH node IN graph.nodes
        node.color = white  // Unvisited state
        node.d = 0          // Discovery time
        node.f = 0          // Finishing time
    END FOR
    
    // First DFS pass (fills stack)
    FOR EACH node IN graph.nodes
        IF node.color == white
            DFS_FirstPass(node, stack)  // Recursive visit
        END IF
    END FOR
    
    // --------------------------------------------
    // Phase 2: Build transposed graph
    // --------------------------------------------
    t_graph = TransposeGraph(graph)  // Reverse all edges
    
    // --------------------------------------------
    // Phase 3: Find SCCs in transposed graph
    // --------------------------------------------
    // Reset visit states
    FOR EACH node IN t_graph.nodes
        node.color = white
    END FOR
    
    scc_list = []  // Result list
    
    // Process nodes in reverse finishing order
    WHILE stack.notEmpty()
        node = stack.pop()
        IF node.color == white
            scc = []  // New connected component
            DFS_SecondPass(node, t_graph, scc)
            scc_list.add(scc)  // Add found SCC
        END IF
    END WHILE
    
    RETURN scc_list
END ALGORITHM


/**
 * ================================================
 * FIRST DFS PASS (Node ordering)
 * ================================================
 * Fills stack in decreasing finishing time order
 * Complexity: O(V + E)
 */
PROCEDURE DFS_FirstPass(node, stack)
    time = time + 1
    node.d = time           // Record discovery time
    node.color = gray       // Mark as "visiting"
    
    // Recursive neighbor visit
    FOR EACH neighbor IN node.adjacent_nodes
        IF neighbor.color == white
            DFS_FirstPass(neighbor, stack)
        END IF
    END FOR
    
    // Completion
    node.color = black      // Mark as "fully visited"
    time = time + 1
    node.f = time           // Record finishing time
    stack.push(node)        // Add to stack (LIFO order)
END PROCEDURE


/**
 * ================================================
 * SECOND DFS PASS (SCC identification)
 * ================================================
 * Finds all reachable nodes in transposed graph
 * Complexity: O(V + E)
 */
PROCEDURE DFS_SecondPass(node, t_graph, scc)
    node.color = gray
    scc.add(node)  // Add node to current SCC
    
    // Visit neighbors in TRANSPOSED graph
    FOR EACH neighbor IN t_graph.getAdjacent(node)
        IF neighbor.color == white
            DFS_SecondPass(neighbor, t_graph, scc)
        END IF
    END FOR
    
    node.color = black  // Mark as visited
END PROCEDURE


/**
 * ================================================
 * GRAPH TRANSPOSITION
 * ================================================
 * Creates new graph with reversed edges
 * Complexity: O(E)
 */
FUNCTION TransposeGraph(graph)
    t_graph = new Graph()
    
    // For each edge (u → v), create (v → u)
    FOR EACH node IN graph.nodes
        FOR EACH neighbor IN node.adjacent_nodes
            t_graph.addEdge(neighbor, node)  // Edge reversal
        END FOR
    END FOR
    
    RETURN t_graph
END FUNCTION