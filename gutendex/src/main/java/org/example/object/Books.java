package org.example.object;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonProperty;

/**
 * Books information class
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class Books {

    @JsonProperty("count")
    public int count;
}
