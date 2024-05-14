#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure pour stocker une performance d'un athlète
typedef struct {
    char date[11];  // Format JJ/MM/AAAA
    char epreuve[20];
    double temps;   // Temps réalisé en secondes
    int positionRelais; // Position dans le relais, 1 à 4 pour les positions du relais 4*400 m
} Performance;

// Structure pour un athlète
typedef struct {
    char nom[50];
    Performance performances[100]; // Tableau des performances, taille arbitraire
    int nombrePerformances;
} Athlete;

// Liste des épreuves valides
const char *epreuvesValides[] = {"100 m", "400 m", "5000 m", "marathon", "relais 4*400 m"};
const int nombreEpreuves = 5;

// Fonction pour vérifier si l'épreuve est valide
int estEpreuveValide(char *epreuve) {
    int i = 0; // Initialisation de l'index à zéro
    while (i < nombreEpreuves) { // Continue tant que l'index est inférieur au nombre total d'épreuves
        if (strcmp(epreuvesValides[i], epreuve) == 0) {
            return 1; // Retourne 1 si l'épreuve correspond à une épreuve valide
        }
        i++; // Incrémente l'index
    }
    return 0; // Retourne 0 si aucune correspondance n'a été trouvée après avoir parcouru toutes les épreuves
}

// Fonction pour convertir les abréviations ou variations courantes en noms d'épreuves complets
void normaliserEpreuve(char *input, char *epreuveNormalisee) {
    if (strcmp(input, "100") == 0 || strcmp(input, "100m") == 0) {
        strcpy(epreuveNormalisee, "100 m");
    } else if (strcmp(input, "400") == 0 || strcmp(input, "400m") == 0) {
        strcpy(epreuveNormalisee, "400 m");
    } else if (strcmp(input, "5000") == 0 || strcmp(input, "5000m") == 0) {
        strcpy(epreuveNormalisee, "5000 m");
    } else if (strcmp(input, "marathon") == 0) {
        strcpy(epreuveNormalisee, "marathon");
    } else if (strcmp(input, "relais") == 0 || strcmp(input, "4*400") == 0 || strcmp(input, "relais 4*400") == 0) {
        strcpy(epreuveNormalisee, "relais 4*400 m");
    } else {
        strcpy(epreuveNormalisee, input);  // Aucune normalisation possible
    }
}

// Fonction pour convertir une date de DD/MM/YYYY à YYYY-MM-DD pour uniformité des fichiers
void convertirDateVersFichier(char *dateSource, char *dateDestination) {
    int jour, mois, annee;
    sscanf(dateSource, "%d/%d/%d", &jour, &mois, &annee);
    sprintf(dateDestination, "%04d-%02d-%02d", annee, mois, jour);
}

// Fonction pour convertir une date de YYYY-MM-DD à DD/MM/YYYY pour l'affichage
void convertirDatePourAffichage(char *dateSource, char *dateDestination) {
    int annee, mois, jour;
    sscanf(dateSource, "%d-%d-%d", &annee, &mois, &jour);
    sprintf(dateDestination, "%02d/%02d/%04d", jour, mois, annee);
}

// Fonction pour sauvegarder les performances d'un athlète dans un fichier
void sauvegarderPerformances(Athlete *athlete) {
    char nomFichier[60];
    sprintf(nomFichier, "%s.txt", athlete->nom);
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", nomFichier);
        return;
    }
    for (int i = 0; i < athlete->nombrePerformances; i++) {
        char datePourFichier[11];
        convertirDateVersFichier(athlete->performances[i].date, datePourFichier);
        fprintf(fichier, "%s %s %lf %d\n", datePourFichier,
                athlete->performances[i].epreuve, athlete->performances[i].temps,
                athlete->performances[i].positionRelais);
    }
    fclose(fichier);
}

// Fonction pour charger les performances d'un athlète depuis un fichier
void chargerPerformances(Athlete *athlete) {
    char nomFichier[60];
    sprintf(nomFichier, "%s.txt", athlete->nom);
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        return;
    }
    Performance p;
    while (fscanf(fichier, "%s %s %lf %d", p.date, p.epreuve, &p.temps, &p.positionRelais) == 4) {
        char datePourAffichage[11];
        convertirDatePourAffichage(p.date, datePourAffichage);
        strcpy(p.date, datePourAffichage);
        athlete->performances[athlete->nombrePerformances++] = p;
    }
    fclose(fichier);
}

// Fonction pour afficher les statistiques d'un athlète pour une épreuve donnée
void statistiquesAthlete(Athlete *athlete, const char *epreuve) {
    double min = 1e9, max = 0, total = 0;
    int count = 0;
    for (int i = 0; i < athlete->nombrePerformances; i++) {
        if (strcmp(athlete->performances[i].epreuve, epreuve) == 0) {
            double temps = athlete->performances[i].temps;
            if (temps < min) min = temps;
            if (temps > max) max = temps;
            total += temps;
            count++;
        }
    }
    if (count == 0) {
        printf("Aucune performance trouvée pour %s dans l'épreuve %s\n", athlete->nom, epreuve);
        return;
    }
    printf("Athlète: %s, Épreuve: %s\n", athlete->nom, epreuve);
    printf("Meilleur temps: %lf, Pire temps: %lf, Moyenne: %lf\n", min, max, total / count);
}

// Fonction pour ajouter une nouvelle performance, avec logique spéciale pour le relais
void ajouterPerformance(Athlete *athlete) {
    if (athlete->nombrePerformances >= 100) {
        printf("Nombre maximum de performances atteint pour %s.\n", athlete->nom);
        return;
    }
    Performance p;
    printf("Entrer la date de l'entrainement (DD/MM/YYYY): ");
    fgets(p.date, 11, stdin);
    p.date[strcspn(p.date, "\n")] = 0;  // Supprime le newline

    // Afficher les épreuves disponibles et vérifier l'entrée
    printf("Entrer le type d'épreuve parmi les suivantes :\n");
    for (int i = 0; i < nombreEpreuves; i++) {
        printf("- %s\n", epreuvesValides[i]);
    }
    char inputEpreuve[20];
    fgets(inputEpreuve, 20, stdin);
    inputEpreuve[strcspn(inputEpreuve, "\n")] = 0;  // Supprime le newline
    normaliserEpreuve(inputEpreuve, p.epreuve);

    while (!estEpreuveValide(p.epreuve)) {
        printf("Epreuve invalide. Veuillez choisir parmi les suivantes :\n");
        for (int i = 0; i < nombreEpreuves; i++) {
            printf("- %s\n", epreuvesValides[i]);
        }
        fgets(inputEpreuve, 20, stdin);
        inputEpreuve[strcspn(inputEpreuve, "\n")] = 0;
        normaliserEpreuve(inputEpreuve, p.epreuve);
    }

    // Logique spéciale pour le relais 4*400 m
    if (strcmp(p.epreuve, "relais 4*400 m") == 0) {
        Athlete autresAthletes[3];
        printf("Vous avez choisi une épreuve de relais. Veuillez entrer les informations pour les 4 athlètes du relais.\n");
        for (int i = 0; i < 4; i++) {
            printf("Athlète %d: Entrez le nom: ", i + 1);
            fgets(autresAthletes[i].nom, 50, stdin);
            autresAthletes[i].nom[strcspn(autresAthletes[i].nom, "\n")] = 0;
            autresAthletes[i].nombrePerformances = 0; // Initialise pour ce contexte
            Performance performanceRelais = p; // Copie les informations communes
            performanceRelais.positionRelais = i + 1;
            printf("Athlète %d: Entrez le temps réalisé: ", i + 1);
            char buffer[50];
            fgets(buffer, 50, stdin);
            sscanf(buffer, "%lf", &performanceRelais.temps); // Convertit le texte en double
            autresAthletes[i].performances[autresAthletes[i].nombrePerformances++] = performanceRelais;
            sauvegarderPerformances(&autresAthletes[i]);
        }
    } else {
        printf("Entrer le temps réalisé: ");
        char buffer[50];
        fgets(buffer, 50, stdin);
        if (sscanf(buffer, "%lf", &p.temps) == 1) {
            p.positionRelais = 0;  // Non applicable ici
            athlete->performances[athlete->nombrePerformances++] = p;
            sauvegarderPerformances(athlete);
        } else {
            printf("Entrée invalide pour le temps. Veuillez réessayer.\n");
        }
    }
}

// Fonction pour afficher l'historique des performances
void afficherHistorique(Athlete *athlete) {
    printf("Historique des performances pour %s:\n", athlete->nom);
    for (int i = 0; i < athlete->nombrePerformances; i++) {
        printf("%s - %s - %lf s - Position Relais: %d\n", athlete->performances[i].date,
               athlete->performances[i].epreuve, athlete->performances[i].temps,
               athlete->performances[i].positionRelais);
    }
}

// Menu principal pour interagir avec l'utilisateur
void menu() {
    Athlete athlete;
    strcpy(athlete.nom, "John Doe");  // Modifier selon les besoins
    athlete.nombrePerformances = 0;
    chargerPerformances(&athlete);

    int choix;
    bool continuer = true;

    while (continuer) {
        printf("\n1. Entrer une nouvelle performance\n");
        printf("2. Afficher l'historique des performances\n");
        printf("3. Afficher les statistiques d'un athlète pour une épreuve\n");
        printf("4. Quitter\n");
        printf("Choisir une option: ");
        scanf("%d", &choix);
        getchar();  // Nettoie le buffer d'entrée pour éviter de sauter les entrées futures

        switch (choix) {
            case 1:
                ajouterPerformance(&athlete);
                break;
            case 2:
                afficherHistorique(&athlete);
                break;
            case 3:
                {
                    char epreuve[20];
                    printf("Entrer le nom de l'épreuve pour les statistiques: ");
                    fgets(epreuve, 20, stdin);
                    epreuve[strcspn(epreuve, "\n")] = 0;  // Supprime le newline
                    while (!estEpreuveValide(epreuve)) {
                        printf("Epreuve invalide. Veuillez choisir parmi les suivantes :\n");
                        for (int i = 0; i < nombreEpreuves; i++) {
                            printf("- %s\n", epreuvesValides[i]);
                        }
                        fgets(epreuve, 20, stdin);
                        epreuve[strcspn(epreuve, "\n")] = 0;
                    }
                    statistiquesAthlete(&athlete, epreuve);
                }
                break;
            case 4:
                continuer = false;
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
