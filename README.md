# Multi-pattern Search Algorithm for Sentiment Polarity Determination

## About the Project

This project's objective was to establish the competency of a system through a multipattern search algorithm. A sentiment polarity determining module was developed, which searches for positive, negative, and stop words within a large dataset. The core searching logic supports various algorithms, with a particular emphasis on the Aho-Corasick algorithm.

The algorithms included are:

1. Aho-Corasick
2. Trie search
3. Knuth-Morris-Pratt (KMP)

A `config.ini` file is also part of the implementation, allowing users to toggle between the search algorithms.

### Application of Algorithm Engineering Concepts

- **Modelling**: The Trie data structure was constructed and optimized, using the Python NetworkX library for effective modelling.
- **Implementation**: The application was developed in Microsoft Visual C++ 17. Profiling utilized the Tracy library for performance insights.
- **Experimentation**: Performance and resource usage were visualized and compared across algorithms using Jupyter notebooks.

## Running the Application

To run the application:

1. Navigate to the `run` folder.
2. Modify the `config.ini` file as follows (ensure that the specified subfolders and files exist), you can use the sample input and word files from books (run/books), words (run/words) folders respectively:

   ```ini
   [algorithm]
   type = 2 // 1: Aho-Corasick, 2: Trie Search, 3: KMP Algorithm
   parellel = 1 // 1: Parallel, 2: Sequential

   [file]
   input_path = C:\Users\balaj\source\repos\Dataset\Books\20000  // Dataset path
   output_path = C:\Users\balaj\source\repos\Dataset\Books\Analysis\20000\ // Results path
   positive_words_file = C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\positive-words.txt // Positive words list
   negative_words_file = C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\negative-words.txt // Negative words list
   stop_words_file = C:\Users\balaj\source\repos\Aho-Corasick-Algorithm\implementation\SentimentAnalysis\words\stop-words.txt  // Stop words list
   ```

3. Execute `SentimentAnalysis.exe`. This generates `table_*.txt` for sentiment analysis and `result_*.txt` for the performance metrics of the chosen algorithm.

4. For Visualization

   To visualize the application results, follow these steps to set up your environment:

   ### 1. Navigate to '\_experiment' folder

   ```bash
    cd _experiment
   ```

   ### 2. Install Python and Virtual Environment

   Ensure Python is installed and then set up a virtual environment for the project:

   ```bash
   # Install virtualenv if not available
   pip install virtualenv

   # Create a virtual environment in the project directory
   virtualenv venv

   # Activate the virtual environment
   source venv/bin/activate  # On Windows use `venv\Scripts\activate`
   ```

   ### 3. Install Dependencies

   With the virtual environment activated, install the required dependencies:

   ```bash
   # Install dependencies
   pip install -r requirements.txt
   ```

   ### 4. Launch the Jupyter Notebook

   Start the Jupyter notebook server:

   ```bash
   # Start Jupyter
   jupyter notebook
   ```

   Navigate to the run/\_experiment folder, open the performanceComparison.ipynb notebook, and run the cells sequentially.

   ### 5. Visualize Results

   Modify the first cell to match your directory paths and execute the cells to visualize the analysis.

   Note: Cuurrent code is setup to the run the visualize the results of artifacts in run/\_experiment/analysis folder.

   To exit the virtual environment when done:

   ```bash
   # Deactivate the virtual environment
   deactivate
   ```

## Individual Components

For detailed instructions on running specific parts of the application, please refer to the following README files:

1. [Gutendex](./gutendex/README.md)
2. [Modelling](./modelling/README.md)
3. [Implementation](./implementation/README.md)

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make to this project are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repository and create a pull request. You can also simply open an issue with the tag "enhancement". Don't forget to give the project a star! Thanks again!

### How to Contribute

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Pull Request Process

1. Ensure any install or build dependencies are removed before the end of the layer when doing a build.
2. Update the README.md with details of changes to the interface, this includes new environment variables, exposed ports, useful file locations, and container parameters.
