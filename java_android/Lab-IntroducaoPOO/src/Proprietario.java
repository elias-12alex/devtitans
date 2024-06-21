
public class Proprietario {
	String nome;
	int cnh;
	int anoNascimento;
	
	public Proprietario() {
		
	}
	
	public Proprietario(String nome, int cnh, int anoNascimento) {
		this.nome = nome;
		this.cnh = cnh;
		this.anoNascimento = anoNascimento;
	}
	
	int getIdade(int anoReferencia){
		return anoReferencia - anoNascimento;
	}
	String	getDescricao() {
		String descricao =  "Proprietario: nome=" + nome + ", cnh=" + cnh + ", anoNascimento=" + anoNascimento +".";
		return descricao;
	}

}
