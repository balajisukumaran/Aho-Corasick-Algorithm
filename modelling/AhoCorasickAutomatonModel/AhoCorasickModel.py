import sys
import networkx as nx
import matplotlib.pyplot as plt
from collections import deque

# This class represents a node in the Trie data structure.
class TrieNode:
    def __init__(self):
        self.children = {}  # Dictionary to keep track of children nodes.
        self.word = ""  # Variable to store a word that terminates at this node.
        self.suffix_link = None  # Suffix link used in the Aho-Corasick algorithm.
        self.output_link = []  # Output links used in the Aho-Corasick algorithm.

# This class represents the Trie data structure with additional methods to insert words and compute links.
class Trie:
    def __init__(self):
        self.root = TrieNode()  # The root node of the Trie.
        self.graph = nx.DiGraph()  # Directed graph for visual representation.

    # Method to insert a word into the Trie.
    def insert(self, word):
        node = self.root
        prev_node = "root"  # Initialize previous node as root for graph visualization.
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
                self.manage_graph_nodes_edges(char, prev_node)
            node = node.children[char]
            prev_node = char
        node.word = word  # Set the end of word at the last node.

    # Helper method to manage nodes and edges in the visualization graph.
    def manage_graph_nodes_edges(self, char, prev_node):
        """Add nodes and edges to the graph for visualization"""
        if char not in self.graph:
            self.graph.add_node(char)
        if prev_node not in self.graph:
            self.graph.add_node(prev_node)
        self.graph.add_edge(prev_node, char)

    # Method to compute the suffix and output links for the Aho-Corasick algorithm.
    def compute_suffix_and_output_links(self):
        queue = deque([self.root])
        while queue:
            current_node = queue.popleft()
            for char, child_node in current_node.children.items():
                queue.append(child_node)
                fallback_node = current_node.suffix_link
                while fallback_node is not None and char not in fallback_node.children:
                    fallback_node = fallback_node.suffix_link
                child_node.suffix_link = fallback_node.children[char] if fallback_node else self.root
                if child_node.suffix_link.word:
                    child_node.output_link.append(child_node.suffix_link)
                child_node.output_link.extend(child_node.suffix_link.output_link)

    # Method to draw the Trie structure using matplotlib.
    def draw_graph(self):
        pos = nx.spring_layout(self.graph, k=500, iterations=200)
        nx.draw(self.graph, pos, with_labels=True, node_size=500, node_color="lightblue", font_size=10, font_weight="bold", arrows=True)
        plt.show()

# Function to insert words into the Trie from a file.
def insert_words_from_file(trie, filename):
    with open(filename, 'r') as file:
        for line in file:
            word = line.strip()  # Clean the word.
            trie.insert(word)  # Insert the cleaned word into the Trie.

# Main execution block that checks command-line arguments and runs the Trie operations.
if len(sys.argv) < 2:
    print("Usage: python TrieModel.py <input-file-path>")
    sys.exit(1)

input_file_path = sys.argv[1]
print(f"The input file path is: {input_file_path}")

trie = Trie()  # Create a Trie instance.
filename = input_file_path  # Assign the file name from command-line argument.
insert_words_from_file(trie, filename)  # Insert words from the file into the Trie.
trie.compute_suffix_and_output_links()  # Compute the necessary links for Aho-Corasick algorithm.
trie.draw_graph()  # Draw and display the Trie graph.
