import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ICompte extends Remote {
    boolean creerCompte(String pseudo, String mdp) throws RemoteException;
    boolean supprimerCompte(String pseudo, String mdp) throws RemoteException;
    boolean connexion(String pseudo, String mdp) throws RemoteException;
}