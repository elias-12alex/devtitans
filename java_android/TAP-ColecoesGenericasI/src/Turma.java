import java.util.ArrayList;
import java.util.List;

public class Turma {

    String disciplina;
    int ano;
    int semestre;
    Professor professor;
    ArrayList<Aluno> alunos = new ArrayList<>();

    Turma(String disciplina, int ano, int semestre, Professor professor) {
        this.disciplina = disciplina;
        this.ano = ano;
        this.semestre = semestre;
        this.professor = professor;
    }

    void addAluno(Aluno aluno) {
        for (Aluno a : alunos) {
            if (a.matricula == aluno.matricula) {
                return; // Aluno já existe na turma
            }
        }
        alunos.add(aluno);
    }

    Aluno getAluno(int matricula) {
        for (Aluno aluno : alunos) {
            if (aluno.matricula == matricula) {
                return aluno;
            }
        }
        return null; // Aluno não encontrado na turma
    }

    double getMediaIdade() {
        if (alunos.isEmpty()) {
            return 0;
        }

        int totalIdades = 0;
        for (Aluno aluno : alunos) {
            totalIdades += aluno.getIdade();
        }

        return (double) totalIdades / alunos.size();
    }

    String getDescricao() {
        String descricao = String.format("Turma %s - %d/%d (%s):\n", disciplina, ano, semestre, professor.getDescricao());
        int count = 1;  // Inicia o contador de alunos
        for (Aluno aluno : alunos) {
            descricao += String.format("  - Aluno %d: %s\n", count, aluno.getDescricao());
            count++;  // Incrementa o contador após adicionar cada aluno à descrição        
        }
        return descricao;
    }
}