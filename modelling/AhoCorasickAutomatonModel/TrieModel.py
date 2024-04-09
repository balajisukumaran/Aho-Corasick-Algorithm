import sys
import networkx as nx
import matplotlib.pyplot as plt

# Class for creating nodes of the Trie structure.
class TrieNode:
    def __init__(self):
        self.children = {}  # Dictionary to hold children (next characters)
        self.word = ""  # Word that ends at this node, if any


# Class for creating a Trie structure, which is a kind of search tree.
class Trie:
    def __init__(self):
        self.root = TrieNode()  # The root node of the Trie
        self.graph = nx.DiGraph()  # Directed graph for visual representation

    # Method to insert a word into the Trie.
    def insert(self, word):
        node = self.root
        prev_node = "root"  # Placeholder for the root node in graph
        for char in word:
            # If character not present, add it as a child of the current node.
            if char not in node.children:
                node.children[char] = TrieNode()

                # Add the character as a node in the graph, if not already added.
                if char not in self.graph:
                    self.graph.add_node(char)
                # Add the previous node to the graph, if not already added.
                if prev_node not in self.graph:
                    self.graph.add_node(prev_node)
                # Add an edge from the previous node to the current character.
                self.graph.add_edge(prev_node, char)

            # Move to the child node associated with the current character.
            node = node.children[char]
            # Update the previous node to the current character.
            prev_node = char  
        # Set the word at the final node.
        node.word = word

    # Method to draw and display the Trie as a graph.
    def draw_graph(self):
        # Generate positions for all nodes.
        pos = nx.spring_layout(self.graph, k=500, iterations=200)  

        # Draw the graph with specified visual settings.
        nx.draw(self.graph, pos, with_labels=True, node_size=500, node_color="lightblue", font_size=10,
                font_weight="bold", arrows=True)
        # Display the graph.
        plt.show()

# Function to insert words into the Trie from a given file.
def insert_words_from_file(trie, filename):
    # Open the file and read lines.
    with open(filename, 'r') as file:
        for line in file:
            # Remove any leading/trailing whitespace from the line.
            word = line.strip()  
            # Insert the cleaned word into the Trie.
            trie.insert(word)

# Check for the correct usage and presence of input file path in command-line arguments.
if len(sys.argv) < 2:
    print("Usage: python TrieModel.py <input-file-path>")
    sys.exit(1)

# Store the file path provided by the user.
input_file_path = sys.argv[1]
print(f"The input file path is: {input_file_path}")

# Create a Trie instance.
trie = Trie()
# Variable for file name from command-line argument.
filename = input_file_path
# Insert words from the file into the Trie.
insert_words_from_file(trie, filename)

# Draw the Trie graph.
trie.draw_graph()
