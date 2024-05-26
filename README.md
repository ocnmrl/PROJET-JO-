# PROJET-JO

Notre équipe se compose de trois personnes: Océane, Bouchra et Maëlle. Nous avons choisi d’effectuer le projet Projet-CER-JO, un projet de gestion qui nous a semblé adapté aux capacités de chacune. Ce projet a pour but de créer un programme permettant à un entraîneur de consulter et modifier les athlètes et leurs performances pour le 100m, le 400m, le 5000m, le marathon et le relais 4x400m. Afin de mener à bien ce projet nous avons dû utiliser les notions vues en TD comme les structures, les fichiers et les tris.

Nous avons démarré le projet le dimanche 12 mai de 9h à 19h. Au cours de cette journée, nous avons d'abord analysé en profondeur le projet sélectionné et identifié les éléments principaux (fonctions, structures) à développer. Ensuite, nous nous sommes réunies le mardi 14 mai de 10h30 à 14h30. Durant cette réunion, nous nous sommes réparties les fonctions à développer, chacune travaillant sur son ordinateur pour les coder et les tester. Nous avons ensuite envoyé nos fonctions à Bouchra pour qu'elle les publie sur GitHub. Notre programme ne fonctionnait pas lors de la compilation, donc nous avons planifié une autre réunion l'après-midi de 16h30 à 18h15. Après cette réunion, le programme fonctionnait, mais plusieurs éléments importants manquaient encore. Nous avons donc décidé de travailler dessus pendant le cours d'informatique le 22 mai de 8h30 à 11h45. Le professeur a pu nous indiquer ce qui fonctionnait et ce qui posait problème, et nous avons apporté les modifications nécessaires.

Comme vous l’avez lu nous avons eu beaucoup de réunions car nous avons porté beaucoup d’importance à la communication au sein du groupe et à l’avancée homogène et régulière du projet. De plus, le fait de travailler ensemble nous a permis de mieux comprendre nos difficultés et surtout de mieux les résoudre car chacune disait ce qu’elle pensait ouvertement.

Nous avons choisi de travailler principalement sur le PC de Bouchra pour l’historique des fichiers des athlètes ce qui malgré un début efficace à été un frein pour le travail de groupe par la suite. En effet le fait que toute l’équipe ne puisse pas avoir accès aux fichiers à été quelque peu problématique pour tester les différentes fonctions faisant appel aux fichiers. Pour remédier à ce problème nous avons décidé de nous donner des fonctions respectives à développer une fois que nous avons eu une idée du squelette. Ensuite la fonction afficher les statistiques d’un athlète nous a donné du fil à retordre car il a fallu effectuer plus de calcul que pour les autres fonctions et la décomposer en trois parties. La partie tri nous à mis au pied du mur car il s’agissait du dernier TD de l’année. Nous avons demandé l’aide de camarades pour essayer de s’aider mutuellement sur le fonctionnement des tris qu'eux non plus n’avaient pas compris, et le type de tri à utiliser. 
De plus, nous avons organisé une réunion le vendredi 24 mai de 10h à 19h pour finaliser le projet. Au cours de cette réunion, nous pensions terminer le programme et finir de rédiger le rapport mais nous n'avons pas réussi à coder une fonction permettant d'afficher la progression de l'athlète entre deux dates malgré plusieurs essais infructueux. Pour remédier à cela, le lendemain matin (samedi 25 mai) nous avons fait une dernière réunion pour réessayer de faire fonctionner cette fonction. Cela nous a pris pas mal de temps mais nous étions motivées à réussir le programme en entier. Enfin nous avons travaillé sur la robustesse du programme car lorsque nous métions autre chose que des nombres le programme crashait. A la fin de cette journée notre programme était terminé.
Explication du code : 

Nous avons commencé par déclarer les fonctions nécessaires au programme. La structure 'Date' représente une date avec le jour, le mois, l'année. La structure 'Temps' représente un temps avec des minutes, des secondes et des millisecondes. La structure 'Performance' contient les informations d'une performance : date, épreuve, temps et position dans un relais (si applicable). La structure 'Athlete' contient les informations d'un athlète : nom, tableau de performances, et le nombre de performances. Et la structure 'StatistiquesEpreuve' stocke les statistiques d'une épreuve : le meilleur temps, le pire temps, et le temps moyen.

La fonction principale affiche le menu principal et appelle les fonctions correspondantes selon le choix de l'utilisateur. Elle permet de : ajouter un nouvel athlète, ajouter une nouvelle performance pour un athlète existant, afficher l'historique des performances d'un athlète, afficher les statistiques d'un athlète, quitter le programme. Chaque case du switch correspond à une fonctionnalité du programme, et les fonctions associées sont appelées en conséquence. 

La fonction 'typeEpreuves' affiche une liste d'épreuves disponibles que les athlètes peuvent réaliser.

Les fonctions 'modifierAthlete' et 'ouvrirAthlete' ouvrent un fichier correspondant à l'athlète choisi. 'modifierAthlete' ouvre le fichier en mode lecture et écriture (r+), tandis que 'ouvrirAthlete' l'ouvre en mode lecture seule (r). Elles recherchent l'athlète sélectionné dans le fichier 'Athlete.txt', construisent le nom de fichier spécifique de l'athlète, et ouvrent ce fichier.

La fonction 'ligne' compte et retourne le nombre de lignes dans un fichier. Elle lit le fichier caractère par caractère et incrémente le compteur de lignes chaque fois qu'elle rencontre un caractère de nouvelle ligne ('\n').

La fonction 'afficherNomEpreuve' lit et affiche le nom d'une épreuve à partir d'un fichier. 'ListeEpreuve' utilise 'afficherNomEpreuve' pour afficher toutes les épreuves présentes dans 'Epreuves.txt'.

La fonction 'afficherNomAthlete' lit et affiche le nom d'un athlète à partir d'un fichier. Et la fonction 'ListeAthlete' utilise 'afficherNomAthlete' pour afficher tous les athlètes présents dans 'Athlete.txt'.

La fonction 'afficherAthlete' affiche toutes les performances d'un athlète sélectionné. Elle liste d'abord les athlètes disponibles, puis demande à l'utilisateur de choisir un athlète. Ensuite, elle ouvre le fichier de cet athlète et affiche les détails de chaque performance.

La fonction 'creeAthlete' crée un nouveau fichier pour un nouvel athlète et ajoute son nom au fichier 'Athlete.txt'. Elle demande à l'utilisateur de fournir le prénom de l'athlète, crée un fichier pour cet athlète, et met à jour la liste des athlètes avec un numéro d'athlète unique.

La fonction 'ajouterEntrainement' ajoute une nouvelle performance pour un athlète existant. Elle demande à l'utilisateur de choisir un athlète et une épreuve, et d'entrer les détails de la performance. Ensuite, elle ouvre le fichier de l'athlète et ajoute cette nouvelle performance.

La fonction 'afficherPireTemps' affiche le pire temps (le plus long) pour une épreuve spécifique.

La fonction 'afficherMoyenneTemps' calcule et retourne le temps moyen pour une épreuve spécifique.

La fonction 'afficherMeilleurTemps' affiche le meilleur temps (le plus court) pour une épreuve spécifique.

La fonction 'perfoAthlete' affiche les meilleures, pires et moyennes performances d'un athlète pour une épreuve choisie.

Ici, nous avons ajouter une structure nécessaire à la suite du programme : la structure 'MoyenneIndex' contient deux champs : un entier moyenne pour stocker une moyenne et un entier index pour stocker un indice.

La fonction 'comparer' compare deux éléments de type 'MoyenneIndex' en fonction de leur attribut 'moyenne', en plaçant les éléments avec une moyenne de 0 en fin de liste lors du tri.

La fonction 'quiJO' détermine quels athlètes envoyer aux Jeux Olympiques en fonction de leurs meilleures moyennes pour une épreuve spécifique. Elle affiche les trois meilleures moyennes pour une épreuve choisie.

La fonction 'progressionAthlete' permet de choisir un athlète et une épreuve, puis calcule et affiche la différence de temps de performance de l'athlète pour cette épreuve entre deux dates spécifiées par l’utilisateur.

La fonction 'statistiqueAthlete' gère le menu des statistiques. Elle permet à l'utilisateur de choisir entre afficher un résumé des performances d'un athlète ou déterminer quels athlètes envoyer aux JO.
