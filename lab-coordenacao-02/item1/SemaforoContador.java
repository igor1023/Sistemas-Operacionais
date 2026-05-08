// Semaforo: https://docs.oracle.com/javase/8/docs/api/java/util/concurrent/Semaphore.html
// Thread: https://docs.oracle.com/javase/8/docs/api/java/lang/Thread.html
// Fiz o codigo m5-semaforo (as trhreads somam a variavel sum).

import java.util.ArrayList;
import java.util.concurrent.Semaphore;

public class SemaforoContador {

    static final int NUM_THREADS = 100;
    static final int NUM_STEPS = 100000;
    static final int vagas = 1;
    
    static int sum = 0;
    static Semaphore s = new Semaphore(vagas);
    
    private static void somar(){
        
        for(int i = 0; i < NUM_STEPS; i++){
            
            try{
                s.acquire();
            } catch(InterruptedException e){
                System.out.println(e);
            }
            
            sum ++;
            
            if(sum % NUM_STEPS == 0)
                System.out.println("Sum: " + sum + "\n");
            
            s.release();
            
        }
        
    }
    
    public static void main(String args[]){
        
        ArrayList<Thread> t = new ArrayList<Thread>(NUM_THREADS);

        // valor final esperado
        long expected = NUM_THREADS * NUM_STEPS;

        // criar as threads e iniciá-las
        // vou adicioná-las numa lista para depois utilizar o método join
        for(int i = 0; i < NUM_THREADS; i++){

            //final int id = i; // para eu ler no terminal

            Thread ti = new Thread(()->{
                somar();
                //System.out.println("Eu sou a thread - " + id);
            });

            t.add(ti);
            ti.start();

        }

        for(Thread ti : t){ // for each (para cada thread dentro do Arraylist t) -> join
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