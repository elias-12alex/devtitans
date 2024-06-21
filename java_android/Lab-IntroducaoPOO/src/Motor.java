public class Motor {
	int tipo;
	double capacidade;
	int potencia;

	public Motor() {
		
	}

	public Motor(int tipo, double capacidade, int potencia) {
		this.tipo = tipo;
		this.capacidade = capacidade;
		this.potencia = potencia;
	}
	
	public String getTipoString() {
		switch(tipo){
			case 1: 
				return "Gasolina";
			case 2:
				return "Alcool";
			case 3:
				return "Flex";
			case 4:
				return "Diesel";
			case 5:
				return "Eletrico";
			default:
				return "Outros";
		}
	}
	public String getDescricao(){
		return "Motor: tipo=" + getTipoString() + ", capacidade=" + capacidade + "L, potencia=" + potencia + "CV.";
	}
}
