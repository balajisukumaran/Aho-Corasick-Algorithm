package org.example.object;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonProperty;

/**
 * Book output format class
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public class Formats {
    @JsonProperty("text/html")
    public String textHtml;
    @JsonProperty("application/epub+zip")
    public String epubZip;

    @JsonProperty("application/x-mobipocket-ebook")
    public String eBook;

    @JsonProperty("application/rdf+xml")
    public String rdfXml;

    @JsonProperty("text/plain; charset=us-ascii")
    public String textFile;
}
