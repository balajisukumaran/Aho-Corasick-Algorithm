# Aho-Corasick Automaton Model

## Introduction

This Python project utilizes the 'networkx' library to model both standard and Aho-Corasick search tries. These structures are crucial for efficient pattern matching, which has applications in various fields such as text processing and bioinformatics.

## Prerequisites

Ensure that you have Python 3.6 or later installed on your system.

## Setup and Installation

### Virtual Environment

Set up a virtual environment to manage the project's dependencies:

```shell
python -m venv venv
```

Activate the virtual environment:

On Windows:

```shell
.\venv\Scripts\activate
```

On Unix or MacOS:

```shell
source venv/bin/activate
```

### Install Dependencies

Install the necessary dependencies with:

```shell
pip install -r requirements.txt
```

### Usage

Trie Search Model

To run the Trie search model, execute the following command with the path to your input file:

```shell
python TrieModel.py <input-file-path>
```

For example:

```shell
python TrieModel.py C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\test.txt
```

Aho-Corasick Search Trie Model

To run the Aho-Corasick search trie model, use the command:

```shell
python AhoCorasickModel.py <input-file-path>
```

For example:

```shell
python AhoCorasickModel.py C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\test.txt
```

There's a text.txt file in this directory for trail.run

### Visualization

The trie structures are visualized using 'matplotlib'. Make sure you have a GUI environment set up to display the generated graphs.
