package org.example.object;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonProperty;

/**
 * Book information class
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class Book {

    @JsonProperty("id")
    public int id;

    @JsonProperty("title")
    public String title;

    @JsonProperty("formats")
    public Formats formats;
}
