import java.util.Calendar;

public class Aluno {
	
	String nome;
	int matricula;
	int anoNascimento;
	int ano = Calendar.getInstance().get(Calendar.YEAR);
	
	public Aluno(){
	
	}
	
	Aluno(String nome, int matricula, int anoNascimento){
		this.nome = nome;
		this.matricula = matricula;
		this.anoNascimento = anoNascimento;
	}
	
	
	int	getIdade() {	
		return (ano - anoNascimento);
	}
	
	String getDescricao() {
		return ("" + nome + " (mat=" + matricula + ", idade=" + getIdade() + ")");
	}
	
	
}


