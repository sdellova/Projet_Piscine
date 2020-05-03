#include <iostream>
#include "Graphe.h"

int main()
{
    ///on cree une variable de type Graphe///
    ///puis on affiche le menu grace au constructeur de type Graphe et a la methode menu///
    Graphe graphe(graphe.afficherMenu());
    ///permet de charger un graphe ponderee///
    graphe.ponderation();
    ///permet de calculer la centralite de degree non normalise et normalise de tout les sommets du graphe///
    graphe.centralite_degre(0);
    ///permet de calculer la centralite vecteur propre non normalise et normalise de tout les sommets du graphe///
    graphe.centralite_vecteur_propre(0);
    ///permet de calculer la centralite de proximite non normalise et normalise de tout les sommets du graphe///
    graphe.indice_proximite(0);
    ///permet de sauvegarder dans un fichier les resultats precedent///
    graphe.sauvegarde();
    ///dessine le graphe sous format svg///
    graphe.dessiner(0);
    ///reaffiche le menu///
    graphe.menu();
    return 0;
}
