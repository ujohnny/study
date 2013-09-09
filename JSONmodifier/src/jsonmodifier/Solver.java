package jsonmodifier;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Solver implements Runnable {
    
    public Solver(int threadsCount) {
        this.threadsCount = threadsCount;
    }
    
    @Override
    public void run() {
        try {
            ArrayBlockingQueue<String> in = new ArrayBlockingQueue(5);
            LinkedBlockingQueue<String> out = new LinkedBlockingQueue();
            
            ExecutorService ex = Executors.newFixedThreadPool(threadsCount);
            
            CountDownLatch c = new CountDownLatch(threadsCount);
            ex.execute(new IOThread(in, out, c));
            for (int i = 0; i < threadsCount - 1; ++i) {
                ex.execute(new WorkerThread(in, out, c));
            }
            
            ex.shutdown();
            c.await();           

        } catch (InterruptedException ex) {
            Logger.getLogger(Solver.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    private class IOThread implements Runnable {
        public IOThread(BlockingQueue in, BlockingQueue out, CountDownLatch c) {
            inQueue = in;
            cd = c;
            outQueue = out;
            inputCacheSize = in.remainingCapacity() + in.size();
            outThresholdSize = 10;
        }
        @Override
        public void run() {
            Path in = Paths.get("data/intern-task.json.filtered");
            Path out = Paths.get("data/out");
            
            try (BufferedReader reader = Files.newBufferedReader(in, Charset.forName("UTF-8"));
                    BufferedWriter writer = Files.newBufferedWriter(out, Charset.forName("UTF-8"))) 
            {
                while (true) {
                    while (!inQueue.isEmpty()) {}
                    
                    for (int i = 0; i < inputCacheSize; ++i) {
                        String s = reader.readLine();
                        if (s == null) {
                            shutdown = true;
                            inQueue.add("END");
                            while (!(cd.getCount() == 1)) {}
                            writeCache(writer);
                            cd.countDown();
                            return;
                        }
                        inQueue.add(s);
                    }

                    if (outQueue.size() > outThresholdSize) {
                        writeCache(writer);
                    }
                }
            } catch ( IOException | InterruptedException ex) {
                Logger.getLogger(Solver.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        private void writeCache(BufferedWriter writer) throws InterruptedException, IOException {
            while (!outQueue.isEmpty()) {
                writer.write(outQueue.take());
                writer.flush();
            }
        }
        private CountDownLatch cd;
        private boolean shutdown;
        private int inputCacheSize;
        private int outThresholdSize;
        private BlockingQueue<String> inQueue;
        private BlockingQueue<String> outQueue;
    }
    
    private class WorkerThread implements Runnable {
        public WorkerThread(BlockingQueue in, BlockingQueue out, CountDownLatch c) {
            inQueue = in;
            cd = c;
            outQueue = out;
        }
        
        @Override
        public void run() {
            Gson gson = new GsonBuilder()
                    .disableHtmlEscaping()
                    .create();
            
                while (true) {
                    try {
                        String s = inQueue.take();
                        if ("END".equals(s)) {
                            inQueue.put(s);
                            cd.countDown();
                            return;
                        }
                        Article a = gson.fromJson(s, Article.class);
                        Annotation an = new Annotation(a);
                        outQueue.add(gson.toJson(an) + System.lineSeparator());
                    } catch (InterruptedException ex) {
                        Logger.getLogger(Solver.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
        }
        
        private CountDownLatch cd;
        private BlockingQueue<String> inQueue;
        private BlockingQueue<String> outQueue;
    }
    
    private int threadsCount;
    
}
