import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.net.MalformedURLException;
import java.util.Scanner;

public class ClientRMI {
    private ICompte gestionCompte;

    public ClientRMI(String host) throws RemoteException, NotBoundException, MalformedURLException {
        gestionCompte = (ICompte) Naming.lookup("rmi://" + host + "/GestionCompteService");
    }

    public void creerCompte(String pseudo, String motDePasse) throws RemoteException {
        boolean isCreated = gestionCompte.creerCompte(pseudo, motDePasse);
        if (isCreated) {
            System.out.println("Compte cree avec succes.");
        } else {
            System.out.println("Le pseudo est deja utilise.");
        }
    }

    public void seConnecter(String pseudo, String motDePasse) throws RemoteException {
        boolean isConnected = gestionCompte.connexion(pseudo, motDePasse);
        if (isConnected) {
            System.out.println("Connexion reussie.");
        } else {
            System.out.println("Echec de la connexion. Verifiez vos identifiants.");
        }
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.println("Entrez l'adresse du serveur RMI (e.g., localhost):");
            String host = scanner.nextLine();

            ClientRMI client = new ClientRMI(host);

            System.out.println("Entrez votre pseudo:");
            String pseudo = scanner.nextLine();
            System.out.println("Entrez votre mot de passe:");
            String motDePasse = scanner.nextLine();

            client.creerCompte(pseudo, motDePasse);
            client.seConnecter(pseudo, motDePasse);

        } catch (RemoteException | NotBoundException | MalformedURLException e) {
            System.err.println("Erreur RMI : " + e.getMessage());
        }
    }
}