package item3;

import java.util.Random;

public class PizzaMonitor{

    public static void main(String[] args) {

        MesaPizza mesa = new MesaPizza();
        final String[] CARDAPIO = {"Calabresa", "Mussarela", "Portuguesa"};
        Random r = new Random();

        // Thread do Cozinheiro
        new Thread(() -> {

            try {

                while(true){

                    String pizza_preparada = CARDAPIO[r.nextInt(CARDAPIO.length)];
                    mesa.colocarPizza(pizza_preparada);
                    Thread.sleep(0); // Demora para cozinhar
                    
                    // Quando coloquei o cozinheiro com 10 ms e o entregador com 1000 ms, a fila encheu 
                    // as 10 pizzas, o cozinheiro dormiu e aguardou o entregador retirar pelo menos uma pizza.
                    // Quando o entregador removia uma pizza, o cozinheiro preparava outra e a adicionava na fila.

                    // Quando coloquei ambos em 0, nunca enchia a fila

                    // Quando coloquei o cozinheiro com 1000 ms e o entregador com 0 ms, nunca enchia a fila: assim
                    // que o cozinheiro preparava uma pizza, o entregador já a entregava.

                }

            } catch (InterruptedException e) {}

        }).start();

        // Thread do Entregador
        new Thread(() -> {
            try {

                while(true){

                    mesa.retirarPizza();
                    Thread.sleep(0); // Demora para entregar

                }

            } catch (InterruptedException e) {}

        }).start();
    }

}