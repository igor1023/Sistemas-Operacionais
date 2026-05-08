package item2;

public class ContaBancariaMonitor{

    static final int VALOR_T1 = 30;
    static final int VALOR_T2 = 50;

    static SaldoComMonitor saldo = new SaldoComMonitor();

    public static void main(String args[]){

        int expected = saldo.getSaldo() + VALOR_T1 + VALOR_T2;

        Thread t1 = new Thread(()->{

            try{
                saldo.atualiza_conta(VALOR_T1);
                Thread.sleep(0);

            }catch(InterruptedException e){
                System.err.println(e);
            }

        });

        Thread t2 = new Thread(()->{

            try{
                saldo.atualiza_conta(VALOR_T2);
                Thread.sleep(0);

            }catch(InterruptedException e){
                System.err.println(e);
            }

        });

        t1.start();
        t2.start();

        try{

            t1.join();
            t2.join();

        } catch(InterruptedException e){
            System.err.println(e);
        }

        System.out.println("Valor final esperado: " + expected);
        System.out.println("Valor final obtido:   " + saldo.getSaldo());

    }

}