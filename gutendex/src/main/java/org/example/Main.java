package org.example;

import org.example.object.Book;
import org.example.services.FileServices;
import org.example.services.GutendexServices;

public class Main {
    public static void main(String[] args) {
        try {
            GutendexServices services = new GutendexServices();

            for (int i = Constants.START_INDEX; i <= Constants.END_INDEX; i++) {
                try {
                    Book book = services.getBookDetail(i);

                    if (book != null && book.title != null && book.title.length() > 0) {
                        String fileName = book.id + "_" + book.title.replaceAll(" ", "_").substring(0, Math.min(book.title.length(), 30)) + ".txt";
                        FileServices.saveBook(fileName, book.formats.textFile);
                    }
                } catch (Exception e) {
                    System.out.println("Skipped book " + i + ". Book meta-details missing");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}