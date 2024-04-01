import networkx as nx
import matplotlib.pyplot as plt
from collections import deque

class TrieNode:
    def __init__(self):
        self.children = {}
        self.word = ""
        self.suffix_link = None
        self.output_link = None

class Trie:
    def __init__(self):
        self.root = TrieNode()
        self.graph = nx.DiGraph()  # Initialize a directed graph

    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.word = word

    def build_links(self):
        self.root.suffix_link = self.root
        queue = deque([self.root])

        while queue:
            current_node = queue.popleft()

            for char, child_node in current_node.children.items():
                queue.append(child_node)
                fallback = current_node.suffix_link

                while fallback is not self.root and char not in fallback.children:
                    fallback = fallback.suffix_link

                child_node.suffix_link = fallback.children.get(char, self.root)
                child_node.output_link = child_node.suffix_link if child_node.suffix_link.word else child_node.suffix_link.output_link

                # Add suffix and output links to the graph
                if child_node.suffix_link is not self.root:
                    self.graph.add_edge(child_node, child_node.suffix_link, color='green')
                if child_node.output_link:
                    self.graph.add_edge(child_node, child_node.output_link, color='purple')

    def draw_graph(self):
        pos = nx.spring_layout(self.graph, k=2.15, iterations=20)  # Increase 'k' for more space
        # Extract edge colors from the graph's edge attribute
        edge_colors = [self.graph[u][v]['color'] for u, v in self.graph.edges()]
        # Draw nodes
        nx.draw_networkx_nodes(self.graph, pos, node_size=300, node_color="lightblue")
        # Draw edges
        nx.draw_networkx_edges(self.graph, pos, edge_color=edge_colors)
        # Draw labels
        nx.draw_networkx_labels(self.graph, pos, font_size=10, font_weight="bold")
        plt.show()

def insert_words_from_file(trie, filename):
    with open(filename, 'r') as file:
        for line in file:
            # Assuming each word is on a new line
            word = line.strip()  # Remove any leading/trailing whitespace
            trie.insert(word)


trie = Trie()
# trie.insert("hello")
# trie.insert("hi")
filename = "C:\\Users\\balaj\\source\\repos\\Aho-Corasick-Algorithm\\implementation\\SentimentAnalysis\\words\\positive-words.txt"  # Replace with your file path
insert_words_from_file(trie, filename)

trie.draw_graph()  # Draw the Trie graph

