package jsonmodifier;

public class Annotation {
    public Annotation (Article ar) {
        url = ar.getUrl();
        snippet = ar.getContent();
        snippet = snippet.replaceAll("<.+?>", "").replaceAll("[\n|\r|\r\n]", "");
        if (!snippet.toLowerCase().startsWith(ar.getTitle().toLowerCase())) {
            snippet = ar.getTitle() + " " + snippet;
        }
        
        if (snippet.length() > maxLength) {
            snippet = snippet.substring(0, maxLength - cont.length()) + cont;
        }
    }

    private String url;
    private String snippet;
    private static final transient int maxLength = 300;
    private static final transient String cont = "...";
}
