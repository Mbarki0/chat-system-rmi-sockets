import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.concurrent.ConcurrentHashMap;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;

public class GestionCompte extends UnicastRemoteObject implements ICompte {
    private ConcurrentHashMap<String, String> comptes;

    public GestionCompte() throws RemoteException {
        super();
        comptes = new ConcurrentHashMap<>();
    }

    private String hashPassword(String password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(password.getBytes());
            return Base64.getEncoder().encodeToString(hash);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Erreur de hachage", e);
        }
    }

    @Override
    public boolean creerCompte(String pseudo, String mdp) throws RemoteException {
        if (comptes.containsKey(pseudo)) {
            return false;
        }
        comptes.put(pseudo, hashPassword(mdp));
        return true;
    }

    @Override
    public boolean supprimerCompte(String pseudo, String mdp) throws RemoteException {
        String hashedMdp = hashPassword(mdp);
        if (comptes.containsKey(pseudo) && comptes.get(pseudo).equals(hashedMdp)) {
            comptes.remove(pseudo);
            return true;
        }
        return false;
    }

    @Override
    public boolean connexion(String pseudo, String mdp) throws RemoteException {
        String hashedMdp = hashPassword(mdp);
        return comptes.containsKey(pseudo) && comptes.get(pseudo).equals(hashedMdp);
    }
}