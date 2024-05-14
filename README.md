#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

typedef struct {
    char date[11];  // Format AAAA-MM-JJ
    char epreuve[20];  // Type d'épreuve (100m, 400m, etc.)
    float temps;  // Temps réalisé
    int position_relais;  // Position dans le relais, -1 si non applicable
} Performance;

typedef struct {
    char nom[50];
    Performance performances[100]; // Tableau des performances, taille arbitraire
    int nbPerformances;
} Athlete;

// Définition d'une structure pour stocker et afficher les statistiques d'une épreuve
typedef struct {
    char epreuve[20];
    float meilleurTemps;
    float pireTemps;
    float tempsMoyen;
} StatistiquesEpreuve;  

void enregistrerAthlete(const char *nom_fichier, Performance performance) {
    FILE *fichier = fopen(nom_fichier, "a"); // Ouvre le fichier en mode append pour ajouter les nouvelles données sans écraser les anciennes
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }
    // Écriture de la performance dans le fichier
    fprintf(fichier, "%s %s %.2f %d\n", performance.date, performance.epreuve, performance.temps, performance.position_relais);
    fclose(fichier);  // Fermeture du fichier
    printf("Performance enregistrée pour %s\n", nom_fichier);
}

void chargerPerformances(const char *nom_fichier, Performance*performances, int *nbPerformances) {
    // Ouvrir le fichier en mode lecture
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier %s pour lecture.\n", nom_fichier);
        *nbPerformances = 0;  // Aucune performance chargée
        return;
    }

    // Initialiser le compteur de performances
    *nbPerformances = 0;

    // Lire le fichier et stocker les performances dans le tableau
    while (fscanf(fichier, "%s %s %f %d", 
                  performances[*nbPerformances].date, 
                  performances[*nbPerformances].epreuve, 
                  &performances[*nbPerformances].temps, 
                  &performances[*nbPerformances].position_relais) == 4) {
        (*nbPerformances)++;
    }

    // Fermer le fichier après la lecture
    fclose(fichier);
}

void updatePerformance(const char *filename, Performance performance) {
    FILE *file = fopen(filename, "ab+"); // Ouverture du fichier en mode lecture/écriture binaire, création s'il n'existe pas

    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }

    // Recherche de la performance dans le fichier
    int found = 0;
    rewind(file); // Retour au début du fichier
    while (fread(&performance, sizeof(Performance), 1, file)) {
        // Comparaison des dates et des types d'épreuve
        if (strcmp(performance.date, performance.date) == 0 && strcmp(performance.epreuve, performance.epreuve) == 0) {
            // Performance trouvée, mise à jour
            fseek(file, -sizeof(Performance), SEEK_CUR); // Retour à la position avant la lecture
            fwrite(&performance, sizeof(Performance), 1, file); // Écriture de la nouvelle performance
            found = 1;
            break;
        }
    }

    // Si la performance n'a pas été trouvée, elle est ajoutée à la fin du fichier
    if (!found) {
        fwrite(&performance, sizeof(Performance), 1, file);
    }

    fclose(file); // Fermeture du fichier
}

void afficherHistoriqueAthlete(const char *nom_fichier) {
    // Construire le nom complet du fichier basé sur le nom de l'athlète
    char nomCompletFichier[64];
    snprintf(nomCompletFichier, sizeof(nomCompletFichier), "%s.txt", nom_fichier);

    // Ouvrir le fichier en mode lecture
    FILE *fichier = fopen(nomCompletFichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier %s pour lecture.\n", nomCompletFichier);
        return;
    }

    // Lire et afficher les performances de l'athlète
    Performance performance;
    printf("Historique des performances pour %s :\n", nom_fichier);
    while (fscanf(fichier, "%s %s %f %d", 
                  performance.date, performance.epreuve, 
                  &performance.temps, &performance.position_relais) == 4) {
        printf("Date : %s, Épreuve : %s, Temps : %.2f secondes", 
               performance.date, performance.epreuve, performance.temps);
        if (performance.position_relais != -1) {
            printf(", Position dans le relais : %d", performance.position_relais);
        }
        printf("\n");
    }

    // Fermer le fichier
    fclose(fichier);
}


void afficherStatistiques(const char *nom_fichier) {
    char nomCompletFichier[64];
    snprintf(nomCompletFichier, sizeof(nomCompletFichier), "%s.txt", nom_fichier);
    
    FILE *fichier = fopen(nomCompletFichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier %s pour lecture.\n", nomCompletFichier);
        return;
    }

    Performance performances[100]; // Tableau pour stocker temporairement les performances
    int count = 0;
    while (count < 100 && fscanf(fichier, "%s %s %f %d",
                                 performances[count].date, performances[count].epreuve,
                                 &performances[count].temps, &performances[count].position_relais) == 4) {
        count++;
    }
    fclose(fichier);

    // Tableau pour stocker les statistiques des différentes épreuves
    StatistiquesEpreuve statistiques[20]; // Supposons qu'il n'y a pas plus de 20 épreuves différentes
    int nombreEpreuves = 0;

    // Initialiser les statistiques pour chaque épreuve
    for (int i = 0; i < count; i++) {
        int found = -1;
        for (int j = 0; j < nombreEpreuves; j++) {
            if (strcmp(performances[i].epreuve, statistiques[j].epreuve) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) { // Nouvelle épreuve, initialiser les statistiques
            found = nombreEpreuves++;
            strcpy(statistiques[found].epreuve, performances[i].epreuve);
            statistiques[found].meilleurTemps = FLT_MAX;
            statistiques[found].pireTemps = FLT_MIN;
            statistiques[found].tempsMoyen = 0;
        }
        // Mettre à jour les statistiques pour cette épreuve
        if (performances[i].temps < statistiques[found].meilleurTemps) {
            statistiques[found].meilleurTemps = performances[i].temps;
        }
        if (performances[i].temps > statistiques[found].pireTemps) {
            statistiques[found].pireTemps = performances[i].temps;
        }
        statistiques[found].tempsMoyen += performances[i].temps;
    }

    // Calculer la moyenne et afficher les résultats
    for (int i = 0; i < nombreEpreuves; i++) {
        statistiques[i].tempsMoyen /= count; // Moyenne sur le nombre total de performances, pas par épreuve
        printf("Épreuve : %s\n", statistiques[i].epreuve);
        printf("  Meilleur temps : %.2f secondes\n", statistiques[i].meilleurTemps);
        printf("  Pire temps : %.2f secondes\n", statistiques[i].pireTemps);
        printf("  Temps moyen : %.2f secondes\n", statistiques[i].tempsMoyen);
    }
}

int partitionParDate(Performance *performances, int gauche, int droite) {
    char *pivot = performances[droite].date;
    int i = (gauche - 1);
    for (int j = gauche; j <= droite - 1; j++) {
        if (strcmp(performances[j].date, pivot) < 0) {
            i++;
            Performance temp = performances[i];
            performances[i] = performances[j];
            performances[j] = temp;
        }
    }
    Performance temp = performances[i + 1];
    performances[i + 1] = performances[droite];
    performances[droite] = temp;
    return (i + 1);
}

void quickSortParDate(Performance *performances, int gauche, int droite) {
    if (gauche < droite) {
        int pivotIndex = partitionParDate(performances, gauche, droite);
        quickSortParDate(performances, gauche, pivotIndex - 1);
        quickSortParDate(performances, pivotIndex + 1, droite);
    }
}

void trierPerformancesParDate(Performance *performances, int nbPerformances) {
    quickSortParDate(performances, 0, nbPerformances - 1);
}

int partitionParEpreuve(Performance *performances, int gauche, int droite) {
    char *pivot = performances[droite].epreuve;
    int i = (gauche - 1);
    for (int j = gauche; j <= droite - 1; j++) {
        if (strcmp(performances[j].epreuve, pivot) < 0) {
            i++;
            Performance temp = performances[i];
            performances[i] = performances[j];
            performances[j] = temp;
        }
    }
    Performance temp = performances[i + 1];
    performances[i + 1] = performances[droite];
    performances[droite] = temp;
    return (i + 1);
}

void quickSortParEpreuve(Performance *performances, int gauche, int droite) {
    if (gauche < droite) {
        int pivotIndex = partitionParEpreuve(performances, gauche, droite);
        quickSortParEpreuve(performances, gauche, pivotIndex - 1);
        quickSortParEpreuve(performances, pivotIndex + 1, droite);
    }
}


void trierPerformancesParEpreuve(Performance *performances, int nbPerformances) {
    quickSortParEpreuve(performances, 0, nbPerformances - 1);
}


// Programme principal
int main() {
    // Initialisation des variables nécessaires
    Athlete athlete;
    Performance performance;
    int choix;
    
    // Menu principal pour interagir avec l'utilisateur
    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Entrer un nouvel athlète\n");
        printf("2. Entrer une nouvelle performance\n");
        printf("3. Afficher l'historique d'un athlète\n");
        printf("4. Afficher les statistiques d'un athlète\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                printf("Nom de l'athlète : ");
                scanf("%s", athlete.nom);
                break;
            case 2:
                printf("Nom de l'athlète : ");
                scanf("%s", athlete.nom);
                printf("Date (AAAA-MM-JJ) : ");
                scanf("%s", performance.date);
                printf("Type d'épreuve : ");
                scanf("%s", performance.epreuve);
                printf("Temps réalisé : ");
                scanf("%f", &performance.temps);
                performance.position_relais = -1;  // Modifier si relais
                char filename[64];  // Assurez-vous que la longueur est suffisante pour contenir le nom de fichier
                snprintf(filename, sizeof(filename), "%s_performances.txt", athlete.nom);
                // Enregistrer la performance
                enregistrerAthlete(filename, performance);
                break;
            case 3:
                printf("Nom de l'athlète pour l'historique : ");
                scanf("%s", athlete.nom);
                afficherHistoriqueAthlete(athlete.nom);
                break;
            case 4:
                printf("Nom de l'athlète pour les statistiques : ");
                scanf("%s", athlete.nom);
                afficherStatistiques(athlete.nom);
                break;
            case 5:
                return 0;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }
    
    return 0;
}
