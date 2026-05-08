package item3;

class MesaPizza {
    private String pizza;
    private boolean mesaVazia = true;

    // Monitor: Garante que só um mexe na mesa por vez
    public synchronized void colocarPizza(String nomePizza) throws InterruptedException {
        // Se a mesa NÃO estiver vazia, o cozinheiro dorme e solta o lock
        while (!mesaVazia) {
            wait();
        }

        this.pizza = nomePizza;
        this.mesaVazia = false;
        System.out.println("Cozinheiro colocou a pizza de: " + pizza);

        // Avisa o entregador que tem pizza pronta
        notify();
    }

    public synchronized String retirarPizza() throws InterruptedException {
        // Se a mesa estiver vazia, o entregador dorme e solta o lock
        while (mesaVazia) {
            wait();
        }

        String p = pizza;
        mesaVazia = true;
        System.out.println("Entregador levou a pizza de: " + p);

        // Avisa o cozinheiro que a mesa liberou
        notify();
        return p;
    }
}