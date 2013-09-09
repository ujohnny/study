package jsonmodifier;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class JSONmodifier {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Solver s = new Solver(4);
        ExecutorService exec = Executors.newSingleThreadExecutor();
        exec.execute(s);
    }
}
