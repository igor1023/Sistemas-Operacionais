package item2;
import java.util.concurrent.*;

public class ContaBancariaSemaforo{

    static final int PERMISSOES = 1;
    static final int VALOR_T1 = 30;
    static final int VALOR_T2 = 50;
    
    static int conta = 100;
    static Semaphore s = new Semaphore(PERMISSOES);

    public static void atualiza_conta(int valor){

        try{
            s.acquire();
        } catch(InterruptedException e){
            System.err.println(e);
        }

        conta += valor;

        s.release();

    }

    public static void main(String args[]){

        final long expected = conta + VALOR_T1 + VALOR_T2;

        Thread t1 = new Thread(()->{

            atualiza_conta(VALOR_T1);

        });

        Thread t2 = new Thread(()->{

            atualiza_conta(VALOR_T2);

        });

        t1.start();
        t2.start();

        try{

            t1.join();
            t2.join();

        }catch(InterruptedException e){
            System.err.println(e);
        }

        System.out.println("Valor final esperado: " + expected);
        System.out.println("Valor final obtido:   " + conta);
        
    }

}