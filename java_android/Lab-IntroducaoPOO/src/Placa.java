
public class Placa {
	String placa;
	int tipo;
	
	public Placa(){
		
	}
	public Placa(String placa, int tipo){
		this.placa = placa;
		this.tipo = tipo;
	}
	
	String getTipoString(){
        switch (tipo) {
	        case 1:
	            return "Normal";
	        case 2:
	            return "Servico";
	        case 3:
	            return "Oficial";
	        case 4:
	            return "Auto Escola";
	        case 5:
	            return "Prototipo";
	        case 6:
	            return "Colecionador";
	        default:
	            return "Outros";
	    }
	}

	public boolean temEstacionamentoLivre(){
		if((tipo == 2) || (tipo==3)) {
			return true;
		}else {
			return false;
		}
	}

	public String getDescricao(){
		String descricao = "Placa: placa=" + placa + ", tipo=" + getTipoString() + ", estacionamentoLivre=" + temEstacionamentoLivre() + ".";
		return descricao;
	}
}
