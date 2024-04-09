package org.example.services;

import org.example.Constants;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.example.object.Book;
import org.example.object.Books;

/**
 * Contains methods to hit the Gutendex API
 */
public class GutendexServices {

    /**
     * gets the books details
     * @return return book object (based on the output link)
     * @throws IOException throws IO Exception
     * @throws InterruptedException throws interrupted exception
     */
    public Books getBooksDetail() throws IOException, InterruptedException {

        HttpClient httpClient = HttpClient.newBuilder()
                .followRedirects(HttpClient.Redirect.NORMAL)
                .build();

        HttpRequest request = HttpRequest.newBuilder().uri(URI.create(Constants.GUNTENDEX_URL + "/books"))
                .GET().build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        ObjectMapper mapper = new ObjectMapper();

        return mapper.readValue(response.body(), Books.class);
    }

    /**
     * get particular book details
     * @param id book id
     * @return book object based on the gutendex api
     * @throws IOException throws IOException
     * @throws InterruptedException InterruptedException
     */
    public Book getBookDetail(int id) throws IOException, InterruptedException {

        HttpClient httpClient = HttpClient.newBuilder()
                .followRedirects(HttpClient.Redirect.NORMAL)
                .build();

        HttpRequest request = HttpRequest.newBuilder().uri(URI.create(Constants.GUNTENDEX_URL + "/books/" + id))
                .GET().build();

        HttpResponse<String> response = httpClient.send(request, HttpResponse.BodyHandlers.ofString());

        ObjectMapper mapper = new ObjectMapper();

        return mapper.readValue(response.body(), Book.class);
    }
}
