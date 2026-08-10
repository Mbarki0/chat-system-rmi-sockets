import java.io.Serializable;

// Serializable est obligatoire car l'objet Compte va transiter sur le reseau via RMI
public class Compte implements Serializable {
    private String pseudo;
    private String motDePasse;

    public Compte(String pseudo, String motDePasse) {
        this.pseudo = pseudo;
        this.motDePasse = motDePasse;
    }

    public String getPseudo() {
        return pseudo;
    }

    public void setPseudo(String pseudo) {
        this.pseudo = pseudo;
    }

    public String getMotDePasse() {
        return motDePasse;
    }

    public void setMotDePasse(String motDePasse) {
        this.motDePasse = motDePasse;
    }
}