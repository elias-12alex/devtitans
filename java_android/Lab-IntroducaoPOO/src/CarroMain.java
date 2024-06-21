public class CarroMain {
    public static void main(String[] args) {
        // Criando objetos necessários
        Proprietario proprietario = new Proprietario("Emmett L. Brown", 98008173, 1920);
        Placa placa = new Placa("OAT-3966", 6);
        Motor motor = new Motor(1, 2.85, 130);

        // Criando objeto da classe Carro
        Carro carro = new Carro("DeLorean", "DMC-12", proprietario, placa, motor);

        // Imprimindo a descrição do carro
        System.out.println(carro.getDescricao());
    }
}
