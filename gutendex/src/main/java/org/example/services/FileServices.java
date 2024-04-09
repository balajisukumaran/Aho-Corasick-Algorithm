package org.example.services;

import org.example.Constants;

import java.io.BufferedInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

/**
 * File services class
 */
public class FileServices {

    /**
     * saves books for the web url
     *
     * @param fileName location to save the file
     * @param fileUrl  web url for the file
     */
    public static void saveBook(String fileName, String fileUrl) {
        try {
            String filePath = Constants.BOOKS_FOLDER_PATH + fileName;
            URL url = new URL(fileUrl);
            HttpURLConnection httpURLConnection = (HttpURLConnection) url.openConnection();

            if (httpURLConnection.getResponseCode() == HttpURLConnection.HTTP_MOVED_PERM ||
                    httpURLConnection.getResponseCode() == HttpURLConnection.HTTP_MOVED_TEMP) {
                String newUrl = httpURLConnection.getHeaderField("Location");
                saveBook(fileName, newUrl);
            } else {
                try (InputStream in = httpURLConnection.getInputStream();
                     BufferedInputStream bis = new BufferedInputStream(in);
                     FileOutputStream fos = new FileOutputStream(filePath)) {

                    byte[] dataBuffer = new byte[1024];
                    int bytesRead;
                    while ((bytesRead = bis.read(dataBuffer, 0, 1024)) != -1) {
                        fos.write(dataBuffer, 0, bytesRead);
                    }
                    System.out.println("File downloaded successfully: " + fileName);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}