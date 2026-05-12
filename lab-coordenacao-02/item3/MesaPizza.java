package item3;

import java.util.LinkedList;
import java.util.Queue;

class MesaPizza {
    
    private Queue<String> pizzas_prontas = new LinkedList<String>();
    private int MAX_PIZZAS = 10;

    // Monitor: Garante que só um mexe na mesa por vez
    public synchronized void colocarPizza(String nomePizza) throws InterruptedException {

        // Se a fila encheu a capacidade, o cozinheiro vai descansar
        while (pizzas_prontas.size() >= MAX_PIZZAS) {
            wait();
            System.out.println("Cozinheiro ocioso... ZZZ");
        }

        // se a fila ainda nao atingiu o limite, dá para cozinhar mais pizzas
        pizzas_prontas.add(nomePizza);
        // Avisa o entregador que tem pizza pronta
        notifyAll();
        System.out.println("Cozinheiro colocou a pizza de: " + nomePizza);
        
        
    }

    public synchronized String retirarPizza() throws InterruptedException {
        // Se a mesa estiver vazia, o entregador dorme e solta o lock
        while (pizzas_prontas.isEmpty()) {
            wait();
            System.out.println("Entregador ocioso... ZZZ");
        }

        String p = pizzas_prontas.poll();
        System.out.println("Entregador levou a pizza de: " + p);

        // Avisa o cozinheiro que a mesa liberou
        notifyAll();
        return p;
    }
}