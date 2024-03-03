import networkx as nx
import matplotlib.pyplot as plt


# Re-defining the Aho-Corasick automaton class with the addition of a root node.

class AhoCorasickAutomaton:
    def __init__(self, words):
        self.goto = {}  # Transition function
        self.output = {}  # Output function
        self.fail = {}  # Failure function
        self.words = words
        self.states = 1
        self.build_goto_function(words)
        self.build_failure_function()

    def build_goto_function(self, words):
        self.goto[('root', '')] = 0
        for word in words:
            current_state = 0
            for character in word:
                if (current_state, character) not in self.goto:
                    self.goto[(current_state, character)] = self.states
                    current_state = self.states
                    self.states += 1
                else:
                    current_state = self.goto[(current_state, character)]
            self.output[current_state] = self.output.get(current_state, []) + [word]

        # All other characters from root go to root (self-loop for other characters)
        alphabet = set(char for word in words for char in word)
        for character in alphabet:
            if ('root', character) not in self.goto:
                self.goto[('root', character)] = 0

    def build_failure_function(self):
        queue = []
        for character in set(char for word in words for char in word):
            if self.goto[('root', character)] != 0:
                self.fail[self.goto[('root', character)]] = 0
                queue.append(self.goto[('root', character)])

        while queue:
            rstate = queue.pop(0)
            for character in set(char for word in words for char in word):
                if (rstate, character) in self.goto:
                    fstate = self.fail[rstate]
                    while (fstate, character) not in self.goto and fstate != 0:
                        fstate = self.fail[fstate]
                    self.fail[self.goto[(rstate, character)]] = self.goto.get((fstate, character), 0)
                    self.output[self.goto[(rstate, character)]] = self.output.get(self.goto[(rstate, character)],
                                                                                  []) + self.output.get(
                        self.fail[self.goto[(rstate, character)]], [])
                    queue.append(self.goto[(rstate, character)])

    def get_trie_graph(self):
        G = nx.DiGraph()
        G.add_node('root', label='root', color='red')
        for (from_state, char), to_state in self.goto.items():
            if from_state == 'root':
                from_state = 'root'
            else:
                G.add_node(from_state, label=char)
            G.add_edge(from_state, to_state, label=char)

        for from_state, to_state in self.fail.items():
            if to_state != 0:
                G.add_edge(from_state, to_state, label='fail', style='dashed')

        for state, words in self.output.items():
            if words:
                G.nodes[state]['label'] = ','.join(words)
                G.nodes[state]['shape'] = 'doublecircle'

        return G


# Example usage
words = ['he', 'she', 'his', 'hers']
aho_corasick = AhoCorasickAutomaton(words)
trie_graph = aho_corasick.get_trie_graph()

# Draw the graph
# Spring layout often looks good for trees
pos = nx.spring_layout(trie_graph)
nx.draw(trie_graph, pos, with_labels=True,
        labels={n: trie_graph.nodes[n]['label'] for n in trie_graph.nodes if 'label' in trie_graph.nodes[n]})
edge_labels = {(u, v): d['label'] for u, v, d in trie_graph.edges(data=True) if 'label' in d}
nx.draw_networkx_edge_labels(trie_graph, pos, edge_labels=edge_labels)
plt.show()

