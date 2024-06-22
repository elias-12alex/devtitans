/*
 * Projetos_de_Programas
 * Atividade_Lista_4
 * @EliasAlexander
 * 
 * */

public class Professor {
	
	String nome;
	String titulacao;
	int matricula;
	
	
	Professor(){
	}
	Professor(String titulacao, String nome, int matricula){
		this.titulacao = titulacao;
		this.nome = nome;
		this.matricula = matricula;
	}
	
	String getDescricao() {
		return ("Prof. " + titulacao + " " + nome + "- mat " + matricula + "");
	}
	
	public String toString() {
        return nome + " - mat " + matricula;
    }
	
}
