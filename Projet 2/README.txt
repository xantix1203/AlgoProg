************************** Utilisation du programme ****************************
* Préliminaires:
  Il est possible d'éditer manuellement les fichiers suivants
  (se reporter à la section "Fichiers utilisés par le programme"):
  - "Data/data.txt"
  - "Data/power.csv"
  - "Data/monthly_data"
  - "house_config.txt"

* Lancez l'executable main

* Le menu de démarrage permet d'accéder à 3 options:
  - Configurer le logement
  - Lancer la simulation
  - Changer les paramètres de panneaux solaires
  Entrez le chiffre 1 et appuyez sur entrée pour configurer la maison.

* Dans le menu de "Configuration du logement" vous pouvez modifier l'ensemble
  des paramètres du logement à savoir sa surface exploitable, sa surface et la
  liste de ses équipements. Le bouton "charger la config" permet de charger les
  informations contenues dans le fichier "house_config.txt", et le bouton
  "sauvegarder la config" permet de la configuration actuelle sauvegarder dans
  ce même fichier.

* Une fois que les informations sont correctes, entrez le chiffre 6 afin de
  revenir au menu principal.

* Si les informations relatives aux panneaux solaires sont correctes vous pouvez
  procéder à la simulation en entrant le chiffre 2 et en appuyant sur entrée.

* Suivez ensuite les instructions du programme.

* À la simulation le programme revient au menu principal vous pouvez alors
  changer les paramètres et lancer une nouvelle simulation.
********************************************************************************


********************* Fichiers utilisés par le programme ***********************
* Dossier "Data":
  - data.txt:
    Ce fichier contient divers informations sur le coût de reviens et
    d'installation des panneaux solaires.
  - monthly_data.csv
    Données météorologiques mensuelles téléchargée depuis le site
    "https://re.jrc.ec.europa.eu/pvg_tools/en/". Ce fichier contient indicateurs
    d'illumination mensuelle à Gardanne sur l'année 2016 et doit être remplacé
    par un fichier du même type contenant les informations pour la ville voulue.
  - power.csv
    Ce fichier contient une banque de données liées aux appareils électriques du
    quotidien. Il est écrit avec sur chaque ligne le nom d'un appareil
    éléctrique suivi d'un espace et de la consommation de cette appareil en W.
    Le cas du "chauffage" est particulier, le chiffre indiqué est la
    consommation moyenne hebdomadaire par mètre carré d'un système de chauffage.
    en Wh/m^2. (la valeur préenregistrée est issu d'une étude trouvée sur le web)
* "house_config.txt"
  Ce fichier contient l'ensemble des données relatives à la configuration du
  logement:
  - La surface expoitable en (m^2) dont la valeur doit être écrites après la
     mention exploitable_surface.
  - La surface de l'habitation (en m^2) nécessaire au calcul de la facture de
     chauffage.
  - La liste des équipements de la maison. Chaque équipement est écrit sur
     une ligne avec le nom de l'équipement (correspondant à celui présent dans
     le fichier "power.csv"), suivi du nombre d'unités présentes dans le
     logement et du nombre d'heures de fonctionnement par semaine).
     Le cas du chauffage est un cas particulier, si l'utilisateur souhaite avoir
     une estimation globale pour le chauffage de l'ensemble de sa maison, il
     doit rentrer dans le fichier "house_config.txt" le mot chauffage suivi de 1
     (1 installation de chauffage pour toute la maison) et 1 (ce chiffre permet
     d'obtenir l'estimation actuelle correcte même si le chauffage est allumé
     plus d'une heure par semaine).
* "save.txt"
  Ce fichier stocke le résultat de la simulation, il est écrasé à chaque
  nouvelle simulation.

  ******************************************************************************
