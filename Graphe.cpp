#include "Graphe.h"

Graphe::Graphe(std::string nomFichier)
{
    int indice, extremite1, extremite2;
    double x, y;
    std::string nom;
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error("Impossible d'ouvrir " + nomFichier);
    ifs >> m_orientation >> m_ordre;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        ifs >> indice >> nom >> x >> y;
        m_sommets.push_back(new Sommet{indice, nom, x, y});
    }
    ifs >> m_taille;
    for(int i=0 ; i<m_taille ; ++i)
    {
        ifs >> indice >> extremite1 >> extremite2;
        m_aretes.push_back(new Arete{indice, getSommetByIndice(extremite1), getSommetByIndice(extremite2)});
    }
}

void Graphe::ponderation()
{
    int indice;
    int choix = 0, taille, poids;
    int choixTaille = 0;
    std::string nomFichier;
    std::cout << std::endl << "Le graphe est-il pondere ?" << std::endl;
    while(choix != 1 && choix != 2)
    {
        std::cout << "Ecrivez 1 pour oui, 2 pour non : ";
        std::cin >> choix;
    }
    if(choix == 1)
    {
        std::cout << "Ecrivez le nom du fichier de ponderation : ";
        std::cin >> nomFichier;
        std::ifstream ifs{nomFichier};
        if (!ifs)
            throw std::runtime_error("Impossible d'ouvrir " + nomFichier);
        ifs >> taille;
        if (taille != m_taille)
        {
            std::cout << "La taille du graphe ne correspond pas entre les 2 fichiers." << std::endl;
            std::cout << "Que garde-t-on ?" << std::endl;
            std::cout << "1) " << m_taille << "  2) " << taille << std::endl;
            std::cin >> choixTaille;
            if (choixTaille == 2)
                m_taille = taille;
        }
        for(int i=0 ; i<m_taille ; ++i)
        {
            ifs >> indice >> poids;
            getAreteByIndice(indice)->setPoids(poids);
        }
    }
}

void Graphe::dessiner()
{
    Svgfile svgout;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        svgout.addDisk(m_sommets[i]->getX() * 100, m_sommets[i]->getY() * 100, 7);
        svgout.addText((m_sommets[i]->getX() * 100) - 7, (m_sommets[i]->getY() * 100) - 15, m_sommets[i]->getNom());
    }
    for(int i=0 ; i<m_taille ; ++i)
    {
        svgout.addLine(((m_aretes[i]->getExtremites()).first)->getX() * 100, ((m_aretes[i]->getExtremites()).first)->getY() * 100, ((m_aretes[i]->getExtremites()).second)->getX() * 100, ((m_aretes[i]->getExtremites()).second)->getY() * 100);
    }
}

Sommet* Graphe::getSommetByIndice(int indice)
{
    int i = 0;
    while(m_sommets[i]->getIndice() != indice)
    {
        ++i;
    }
    return m_sommets[i];
}

Arete* Graphe::getAreteByIndice(int indice)
{
    int i = 0;
    while(m_aretes[i]->getIndice() != indice)
    {
        ++i;
    }
    return m_aretes[i];
}

void Graphe::menu()
{
    int choix = 0;
    while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8 && choix != 9)
    {
        system("cls");
        std::cout << "1) Calculer les indices de centralite de degre" << std::endl;
        std::cout << "2) Calculer les indices de centralite de vecteur propre" << std::endl;
        std::cout << "3) Calculer les indices de centralite de proximite" << std::endl << std::endl;
        std::cout << "4) Supprimer des aretes du graphe" << std::endl << std::endl;
        std::cout << "5) Charger un nouveau fichier de ponderation" << std::endl;
        std::cout << "6) Quitter" << std::endl << std::endl;
        std::cout << "Que choisissez-vous ? ";
        std::cin >> choix;
    }
    switch(choix)
    {
    case 1:
        centralite_degre();
        std::cout<<std::endl;
        getAretesBySommet(m_sommets[0]);

        break;
    case 2 :
        centralite_vecteur_propre();
    case 4 :
        supprimerAretes();
        break;
    case 5 :
        ponderation();
        break;
    case 6 :
        exit(1);
        break;
    }
}

void Graphe::supprimerAretes()
{
    int choix;
    system("cls");
    do
    {
        std::cout << "Indiquez l'indice de l'arete a supprimer : ";
        std::cin >> choix;
        delete getAreteByIndice(choix);
        m_aretes.erase(m_aretes.begin() + choix);
        dessiner();
    }
    while(choix!= 50);
}

int Graphe::getOrdre() const
{
    return m_ordre;
}

int Graphe::getTaille()
{
    return m_taille;
}

void Graphe::centralite_degre()
{
    std::vector<int> voisins;
    float numberv=0;
    std::vector<int> gauche;
    std::vector<int> droite;
    int a;
    std::vector<Sommet*> sommets;
    system("cls");
    std::cout << "L'odre du graphe est de " << m_ordre << std::endl<< std::endl << std::endl;

    for(int i=0 ; i<m_ordre ; ++i)
    {
        sommets.push_back(getSommetByIndice(i));
    }
    for(int i=0 ; i<m_taille ; ++i)
    {
        gauche.push_back(getAreteByIndice(i)->getExtremites().first->getIndice());
        droite.push_back(getAreteByIndice(i)->getExtremites().second->getIndice());
    }
    for(int c=0; c<m_ordre; ++c)
    {
        voisins.push_back(numberv);
    }

    std::cout << "Choisir un sommet : ";
    std::cin >> a;

    for(int i=0 ; i<m_ordre ; ++i)
    {
        if(sommets[a]->getIndice()==gauche[i])
        {
            numberv++;
        }
        if(sommets[a]->getIndice()==droite[i])
        {
            numberv++;
        }
    }
    std::cout << std::endl << "Le degre du sommet " << a << " est " << numberv << "." << std::endl;
    float resultat=(numberv/(m_ordre-1));
    std::cout << "L'indice normalise du sommet " << a << " est " << resultat << ".";
}

void Graphe::getAretesBySommet(Sommet* sommet)
{
    std::vector<Arete*> aretes;
    for(int i=0 ; i<m_taille ; ++i)
    {
        if(m_aretes[i]->getExtremites().first->getIndice()==sommet->getIndice() ||  m_aretes[i]->getExtremites().second->getIndice()==sommet->getIndice())
        {
            aretes.push_back(m_aretes[i]);
        }
    }
    for(int i=0 ; i<aretes.size(); ++i)
    {
        std::cout<<aretes[i]->getIndice();
    }
    //return aretes;
}

void Graphe::centralite_vecteur_propre()
{

}
