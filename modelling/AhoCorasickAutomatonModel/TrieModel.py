import networkx as nx
import matplotlib.pyplot as plt


class TrieNode:
    def __init__(self):
        self.children = {}
        self.word = ""


class Trie:
    def __init__(self):
        self.root = TrieNode()
        self.graph = nx.DiGraph()  # Initialize a directed graph

    def insert(self, word):
        node = self.root
        prev_node = "root"  # Start from a pseudo "root" node
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()

                # For visualization: add nodes and edges to the graph
                if char not in self.graph:
                    self.graph.add_node(char)
                if prev_node not in self.graph:
                    self.graph.add_node(prev_node)
                self.graph.add_edge(prev_node, char)

            node = node.children[char]
            prev_node = char  # Update prev_node for the next iteration
        node.word = word

    def draw_graph(self):
        pos = nx.spring_layout(self.graph, k=5, iterations=20)  # Increase 'k' for more space

        # Draw the graph with smaller node sizes
        nx.draw(self.graph, pos, with_labels=True, node_size=500, node_color="lightblue", font_size=10,
                font_weight="bold", arrows=True)
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
