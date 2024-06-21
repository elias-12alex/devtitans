
public class Carro {
	String marca;
	String carro;
	String modelo;
	Proprietario proprietario;
	Placa placa;
	Motor motor;
	
	public Carro(String marca, String modelo, Proprietario proprietario, Placa placa, Motor motor){
		this.marca = marca;
		this.modelo = modelo;
		this.proprietario = proprietario;
		this.placa = placa;
		this.motor = motor;
	}

	public String getDescricao() {
        String descricao = String.format("Carro %s/%s.\n", marca, modelo);
        descricao += "" + proprietario.getDescricao() + "\n";
        descricao += "" + placa.getDescricao() + "\n";
        descricao += "" + motor.getDescricao();
        return descricao;
	}
}


