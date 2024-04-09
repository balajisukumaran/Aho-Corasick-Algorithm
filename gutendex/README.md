# Bulk Download Project Gutenberg Books

## About

This Java console application enables users to bulk download books from the Project Gutenberg collection via the Gutendex API (https://gutendex.com/). It is streamlined for ease of use and designed for efficient bulk downloading.

## Getting Started

Follow these instructions to set up and run the application on your local machine for development and operational purposes.

### Prerequisites

- Java JDK 8 or higher installed on your machine
- Access to the command line interface

### Setup

1. **Modify Constants**

   Modify the `Constants.java` file with the necessary configuration:

   ```plaintext
   src/main/java/org/example/Constants.java
   ```

   Open this file in your text editor or IDE and configure the necessary constants such as API keys or download parameters.

2. **Clean and Package the Application**

   Clean and package the application using Maven Wrapper:

   ```bash
   .\mvnw.cmd clean package
   ```

3. **Execute the Packaged JAR**

   Run the packaged JAR file:

   ```bash
   java -jar target/gutendex-1.0-SNAPSHOT.jar
   ```

## Usage

Execute the JAR file to begin the bulk download process. The application will interface with the Gutendex API and download books according to the specifications in `Constants.java`.
