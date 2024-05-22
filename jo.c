#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct{
    int jour;
    int mois;
    int annee;
} Date;

typedef struct{
    int minute;
    int seconde;
    int ms;
} Temps;

typedef struct {
    Date date;  // Format AAAA-MM-JJ
    char epreuve[100];  // Type d'épreuve (100m, 400m, etc.)
    Temps temps;  // Temps réalisé
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

void typeEpreuves(){
    printf("1. 100m\n");
    printf("2. 400m\n");
    printf("3. 5000m\n");
    printf("4. marathon\n");
    printf("5. relais\n");
}



void enregistrerPerformance(const char *nom_fichier, Performance performance) {
    FILE *fichier = fopen(nom_fichier, "a"); // Mode append pour ajouter sans écraser
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }
    fprintf(fichier, "%s %s %.2f %d\n", performance.date, performance.epreuve, performance.temps, performance.position_relais);
    fclose(fichier);
    printf("Performance enregistrée pour %s\n", nom_fichier);
}

void saisirPerformancesAthlete(Athlete *athlete, const char *nom_fichier) {
    printf("Nombre de performances à entrer : ");
    scanf("%d", &athlete->nbPerformances);

    for (int i = 0; i < athlete->nbPerformances; i++) {
        printf("Performance %d:\n", i + 1);
        printf("Date (AAAA-MM-JJ) : ");
        scanf("%s", athlete->performances[i].date);
        printf("Type d'épreuve : ");
        scanf("%s", athlete->performances[i].epreuve);
        printf("Temps réalisé : ");
        scanf("%f", &athlete->performances[i].temps);
        athlete->performances[i].position_relais = -1;  // Modifier si relais

        enregistrerPerformance(nom_fichier, athlete->performances[i]);
    }
}

void chargerPerformances(const char *nom_fichier, Performance* performances, int *nbPerformances) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier %s pour lecture.\n", nom_fichier);
        *nbPerformances = 0;  // Aucune performance chargée
        return;
    }

    *nbPerformances = 0;
    while (fscanf(fichier, "%s %s %f %d", 
                  performances[*nbPerformances].date, 
                  performances[*nbPerformances].epreuve, 
                  &performances[*nbPerformances].temps, 
                  &performances[*nbPerformances].position_relais) == 4) {
        (*nbPerformances)++;
    }
    fclose(fichier);
}

void afficherHistoriqueAthlete(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier %s pour lecture.\n", nom_fichier);
        return;
    }

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
    fclose(fichier);
}

void afficherStatistiques(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier %s pour lecture.\n", nom_fichier);
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

    StatistiquesEpreuve statistiques[20]; // Supposons qu'il n'y a pas plus de 20 épreuves différentes
    int nombreEpreuves = 0;

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
        
    }

    for (int i = 0; i < nombreEpreuves; i++) {
        statistiques[i].tempsMoyen /= count; // Moyenne sur le nombre total de performances, pas par épreuve
        printf("Épreuve : %s\n", statistiques[i].epreuve);
        printf("  Meilleur temps : %.2f secondes\n", statistiques[i].meilleurTemps);
        printf("  Pire temps : %.2f secondes\n", statistiques[i].pireTemps);
        printf("  Temps moyen : %.2f secondes\n", statistiques[i].tempsMoyen);
    }
}

FILE *ouvrirAthlete(int choix){
    int choixAthlete;
    char nomFicher[100];
    char nomAthlete[100];

    FILE *Athlete = fopen("/workspaces/PROJET-JO-/Athlete.txt", "r");

    while(fgets(nomAthlete, sizeof(Athlete), Athlete)){
        sscanf(nomAthlete, "%d", &choixAthlete);
        nomAthlete[strcspn(nomAthlete, "\n")] = 0;

        if(choixAthlete == choix){
            printf("%s : \n", nomAthlete + 2);
            break;
        }
    }

    sprintf(nomFicher, "/workspaces/PROJET-JO-/%s.txt", nomAthlete + 2);

    FILE *file = fopen(nomFicher, "r");

    return file;
}

int ligne(FILE *file){
    int c;
    int lignes = 0;

    while((c = fgetc(file)) != EOF){
        if (c == '\n'){
            lignes++;
        }
    }
    return lignes;
}

void afficherNomEpreuve(FILE *file){
    char nomEpreuve[100];

    fseek(file, 2, SEEK_CUR);
    fgets(nomEpreuve, sizeof(nomEpreuve), file);
    nomEpreuve[strcspn(nomEpreuve, "\n")] = 0;
    printf("%s\n", nomEpreuve);
}

void ListeEpreuve(FILE *file){
    int lignes = ligne(file);
    rewind(file);
    printf("\n");

    for(int i=0; i<lignes; i++){
        printf("%d. ", i+1);
        afficherNomEpreuve(file);
    }
}

void afficherNomAthlete(FILE *file){
    char nomAthlete[100];

    fseek(file, 2, SEEK_CUR);
    fgets(nomAthlete, sizeof(nomAthlete), file);
    nomAthlete[strcspn(nomAthlete, "\n")] = 0;
    printf("%s\n", nomAthlete);
}

void ListeAthlete(FILE *file){
    int lignes = ligne(file);
    rewind(file);
    printf("\n");

    for(int i=0; i<lignes; i++){
        printf("%d. ", i+1);
        afficherNomAthlete(file);
    }
}

void kk(){
    Athlete athlete;
    Performance performance;
    printf("Nom de l'athlète (lucie, sarah, jack) : ");
                scanf("%s", athlete.nom);

                printf("Date (jour, mois, année) : ");
                scanf("%d %d %d", &performance.date.jour, &performance.date.mois, &performance.date.annee);

                typeEpreuves();
                printf("Type d'épreuve : ");
                scanf("%d", &performance.epreuve);

                printf("Temps réalisé : \n");
                printf("Minute :");
                scanf("%d", &performance.temps.minute);
                printf("Seconde :");
                scanf("%d", &performance.temps.seconde);
                printf("Ms :");
                scanf("%d", &performance.temps.ms);

                printf("\n");

                printf("L'athlète %s a effectué un temps de %dmin %dsec %dms\n", athlete.nom, performance.temps.minute, performance.temps.seconde, performance.temps.ms);
}

void afficherAthlete(Performance performance){
    char nomAthlete[100];
    int choix;

    FILE *file = fopen("/workspaces/PROJET-JO-/Athlete.txt", "r");
    if(file == NULL){
        printf("Erreur ouverture fichier\n");
        return;
    }

    ListeAthlete(file);
    
    printf("Choix : ");
    scanf("%d", &choix);

    printf("\n");
    FILE *Athlete = ouvrirAthlete(choix);
    if(Athlete == NULL){
        printf("Erreur ouverture fichier\n");
    }

    //Sauter une ligne dans le fichier de l'athlete
    while(fgetc(Athlete) != '\n');

    while(fscanf(Athlete, "%d %d %d %s %d %d %d %d", &performance.date.jour, &performance.date.mois, &performance.date.annee, performance.epreuve, &performance.temps.minute, &performance.temps.seconde, &performance.temps.ms, &performance.position_relais) != EOF){
        printf("Le %d/%d/%d\n", performance.date.jour, performance.date.mois, performance.date.annee);
        printf("Temps : %dmin %dsec %dms\n", performance.temps.minute, performance.temps.seconde, performance.temps.ms);
        if(strcmp(performance.epreuve, "relais") == 0){
            printf("Position relais : %d\n", performance.position_relais);
        }
        printf("\n");
    }

    fclose(Athlete);
}

void creeAthlete(){
    char prenom[100], chemin[100], ligne[100];
    int dernierNumero = 0;

    FILE *nomAthletes = fopen("/workspaces/PROJET-JO-/Athlete.txt", "r");
    if(nomAthletes == NULL){
        printf("Erreur ouverture fichier");
    }else{
        while(fgets(ligne, sizeof(ligne), nomAthletes) != NULL){
            sscanf(ligne, "%d", &dernierNumero);
        }
        fclose(nomAthletes);
    }

    printf("Quel est le prénom : ");
    scanf("%s", prenom);

    sprintf(chemin, "/workspaces/PROJET-JO-/%s.txt", prenom);

    FILE *file = fopen(chemin, "w");
    if(file == NULL){
        printf("Erreur ouverture fichier");
        return;
    }
    fprintf(file, "%s\n", prenom);
    fclose(file);

    nomAthletes = fopen("/workspaces/PROJET-JO-/Athlete.txt", "a");
    if(nomAthletes != NULL){
        fprintf(nomAthletes, "%d %s\n", dernierNumero+1, prenom);
        fclose(nomAthletes);
    }
}

void ajouterEntrainement(){
    int choix, choixEpreuve;

    FILE *nomAthletes = fopen("/workspaces/PROJET-JO-/Athlete.txt", "r");
    if(nomAthletes == NULL){
        printf("Erreur ouverture fichier\n");
        return;
    }

    FILE *nomEpreuve = fopen("/workspaces/PROJET-JO-/Epreuves.txt", "r");
    if(nomEpreuve == NULL){
        printf("Erreur ouverture fichier");
        return;
    }


    ListeAthlete(nomAthletes);
    printf("Choix : ");
    scanf("%d", &choix);

    printf("\n");
    FILE *Athlete = ouvrirAthlete(choix);
    if(Athlete == NULL){
        printf("Erreur ouverture fichier\n");
    }

    ListeEpreuve(nomEpreuve);
    printf("Choix : ");
    scanf("%d", &choixEpreuve);

}

int main() {
    Athlete athlete;
    Performance performance;
    int choix;

    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Entrer un nouvel athlète\n");
        printf("2. Entrer une nouvelle performance pour un athlète existant\n");
        printf("3. Afficher l'historique d'un athlète\n");
        printf("4. Afficher les statistiques d'un athlète\n");
        printf("5. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creeAthlete();
                break;
            case 2:
                ajouterEntrainement();
                break;
            case 3:
                afficherAthlete(performance);
                break;
            case 4:
                printf("Nom de l'athlète pour les statistiques (lucie, sarah, jack) : ");
                scanf("%s", athlete.nom);
                if (strcmp(athlete.nom, "lucie") == 0) {
                    afficherStatistiques("lucie.txt");
                } else if (strcmp(athlete.nom, "sarah") == 0) {
                    afficherStatistiques("sarah.txt");
                } else if (strcmp(athlete.nom, "jack") == 0) {
                    afficherStatistiques("jack.txt");
                } else {
                    printf("Nom d'athlète invalide.\n");
                }
                break;
            case 5:
                return 0;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }
    return 0;
}
