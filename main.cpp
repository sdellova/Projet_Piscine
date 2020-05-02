#include <iostream>
#include "Graphe.h"

int main()
{
    Graphe graphe(graphe.afficherMenu());
    graphe.ponderation();
    graphe.centralite_degre(0);
    graphe.centralite_vecteur_propre(0);
    graphe.indice_proximite(0);
    graphe.sauvegarde();
    graphe.dessiner(0);
    graphe.menu();
    return 0;
}
