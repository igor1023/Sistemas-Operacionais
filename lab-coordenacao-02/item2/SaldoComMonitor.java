package item2;

class SaldoComMonitor{

    private int saldo = 100;
    
    public synchronized void atualiza_conta(int valor){

        this.saldo += valor;

    }

    public synchronized int getSaldo(){

        return this.saldo;

    }

}