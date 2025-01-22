package labo06;

public class Lecon {
    private String matiere;
    private int jourSemaine;
    private String periodeDebut;
    private int duree; // Durée en minutes
    private String salle;
    private Professeur professeur;

    public Lecon(String matiere, int jourSemaine, String periodeDebut, int duree, String salle, Professeur professeur) {
        this.matiere = matiere;
        this.jourSemaine = jourSemaine;
        this.periodeDebut = periodeDebut;
        this.duree = duree;
        this.salle = salle;
        this.professeur = professeur;
    }

    public static String horaire(Lecon[] lecons) {
        String[][] schedule = new String[10][5]; // 10 créneaux horaires, 5 jours

        // Pré-remplissage du tableau
        for (int i = 0; i < schedule.length; i++) {
            for (int j = 0; j < schedule[i].length; j++) {
                schedule[i][j] = "";
            }
        }

        // Remplir le tableau avec les leçons
        for (Lecon lecon : lecons) {
            int startHour = Integer.parseInt(lecon.periodeDebut.split(":")[0]);
            int startMinute = Integer.parseInt(lecon.periodeDebut.split(":")[1]);
            int slot = (startHour - 8) * 2 + (startMinute >= 30 ? 1 : 0) - 1; // Décalage vers le haut
            int slotsNeeded = (lecon.duree + 44) / 45; // Nombre de créneaux nécessaires

            // Remplissage des créneaux dans la limite de l'horaire
            for (int i = 0; i < slotsNeeded && slot + i < 10; i++) {
                if (lecon.jourSemaine > 0 && lecon.jourSemaine <= 5) {
                    if (i == 0) {
                        // Remplir le premier créneau avec les informations du cours
                        schedule[slot + i][lecon.jourSemaine - 1] = String.format("%s %s %s", lecon.matiere, lecon.salle,
                                lecon.professeur != null ? lecon.professeur.getAbreviation() : "");
                    } else {
                        // Marquer les créneaux suivants comme partie du même cours (utiliser un marqueur pour indiquer la continuité)
                        schedule[slot + i][lecon.jourSemaine - 1] = "|";
                    }
                }
            }
        }

        // Construire l'affichage de l'horaire
        StringBuilder sb = new StringBuilder();
        String[] jours = {"Lun", "Mar", "Mer", "Jeu", "Ven"};
        String[] heures = {"8:30", "9:15", "10:25", "11:15", "12:00", "13:15", "14:00", "14:55", "15:45", "16:35"};

        // Entêtes des jours
        sb.append("     | ");
        for (String jour : jours) {
            sb.append(String.format("%-12s| ", jour));
        }
        sb.append("\n");

        // Séparation
        sb.append("     |");
        for (int i = 0; i < 5; i++) sb.append("-------------|");
        sb.append("\n");

        // Lignes horaires
        for (int i = 0; i < 10; i++) {
            sb.append(String.format("%5s|", heures[i]));
            for (int j = 0; j < 5; j++) {
                if (schedule[i][j].equals("|")) {
                    // Remplissage sans bordure pour les créneaux de continuité
                    sb.append("             ");
                } else {
                    sb.append(String.format(" %-12s|", schedule[i][j]));
                }
            }
            sb.append("\n");

            // Séparation entre les créneaux horaires, en évitant les séparations pour les créneaux de continuité
            sb.append("     |");
            for (int j = 0; j < 5; j++) {
                if (i < 9 && schedule[i + 1][j].equals("|")) {
                    // Pas de séparation si le prochain créneau dans le même jour est une continuité
                    sb.append("             ");
                } else {
                    sb.append("-------------|");
                }
            }
            sb.append("\n");
        }

        return sb.toString();
    }
}
