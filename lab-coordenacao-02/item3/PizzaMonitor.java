package item3;

public class PizzaMonitor{

    public static void main(String[] args) {
        MesaPizza mesa = new MesaPizza();

        // Thread do Cozinheiro
        new Thread(() -> {
            try {
                String[] cardapio = {"Calabresa", "Mussarela", "Portuguesa"};
                for (String p : cardapio) {
                    mesa.colocarPizza(p);
                    Thread.sleep(1000); // Demora para cozinhar
                }
            } catch (InterruptedException e) {}
        }).start();

        // Thread do Entregador
        new Thread(() -> {
            try {
                for (int i = 0; i < 3; i++) {
                    mesa.retirarPizza();
                    Thread.sleep(2000); // Demora para entregar
                }
            } catch (InterruptedException e) {}
        }).start();
    }

}