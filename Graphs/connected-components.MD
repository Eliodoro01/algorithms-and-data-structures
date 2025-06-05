# Algoritmo di Kosaraju per SCC - Pseudocodice Commentato
ALGORITHM FindSCCs(graph)
    stack = new Stack()  // LIFO for node ordering
    time = 0             // Global DFS timer
    
    FOR EACH node IN graph.nodes  // Initialize nodes
        node.color = white        // Unvisited state
        node.d = 0               // Discovery time
        node.f = 0               // Finishing time
    END FOR
    
    FOR EACH node IN graph.nodes  // First DFS pass
        IF node.color == white
            DFS_FirstPass(node, stack)
        END IF
    END FOR
    
    t_graph = TransposeGraph(graph)  // Reverse all edges
    
    FOR EACH node IN t_graph.nodes  // Reset visit states
        node.color = white
    END FOR
    
    scc_list = []  // Result list
    
    WHILE stack.notEmpty()  // Process in reverse order
        node = stack.pop()
        IF node.color == white
            scc = []  // New SCC
            DFS_SecondPass(node, t_graph, scc)
            scc_list.add(scc)  // Store component
        END IF
    END WHILE
    
    RETURN scc_list
END ALGORITHM

PROCEDURE DFS_FirstPass(node, stack)
    time = time + 1
    node.d = time         // Record discovery
    node.color = gray     // Visiting
    
    FOR EACH neighbor IN node.adjacent_nodes
        IF neighbor.color == white
            DFS_FirstPass(neighbor, stack)
        END IF
    END FOR
    
    node.color = black    // Visited
    time = time + 1
    node.f = time         // Record finish
    stack.push(node)      // Add to stack
END PROCEDURE

PROCEDURE DFS_SecondPass(node, t_graph, scc)
    node.color = gray
    scc.add(node)  // Add to component
    
    FOR EACH neighbor IN t_graph.getAdjacent(node)
        IF neighbor.color == white
            DFS_SecondPass(neighbor, t_graph, scc)
        END IF
    END FOR
    
    node.color = black  // Mark complete
END PROCEDURE

FUNCTION TransposeGraph(graph)
    t_graph = new Graph()
    
    FOR EACH node IN graph.nodes  // Reverse edges
        FOR EACH neighbor IN node.adjacent_nodes
            t_graph.addEdge(neighbor, node)
        END FOR
    END FOR
    
    RETURN t_graph
END FUNCTION