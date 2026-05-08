import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

public class MutexContador{

    static ReentrantLock cadeado = new ReentrantLock();
    static final int NUM_THREADS = 100;
    static final int NUM_STEPS = 100000;
    static int sum = 0;

    public static void somar(){

        cadeado.lock();
        
        for(int i = 0; i < NUM_STEPS; i++)
            sum++;

        cadeado.unlock();

    }

    public static void main(String args[]){
        
        ArrayList<Thread> t = new ArrayList<Thread>(NUM_THREADS);
        long expected = (long) NUM_STEPS * NUM_THREADS;

        // agora eu vou criar as threads e depois inicia-las
        for(int i = 0; i < NUM_THREADS; i++){

            Thread ti = new Thread(()->{

                somar();

            });

            t.add(ti);
            ti.start();

        }

        for(Thread ti : t){
            try{
                ti.join();
            } catch(InterruptedException e){
                System.err.println(e);
            }
        }

        System.out.println("Valor esperado: " + expected);
        System.out.println("Valor obtido:   " + sum);

    }

}