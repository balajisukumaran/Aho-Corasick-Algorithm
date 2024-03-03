package org.example;

import org.example.object.Book;
import org.example.services.FileServices;
import org.example.services.GutendexServices;

public class Main {
    public static void main(String[] args) {
        try {
            GutendexServices services = new GutendexServices();
            // Books books=services.getBooksDetail();

            for (int i = 1001; i <= 11000; i++) {
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