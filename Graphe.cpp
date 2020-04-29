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
        m_aretes.push_back(std::make_pair(getSommetByIndice(extremite1), getSommetByIndice(extremite2)));
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
            m_poids.push_back(poids);
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
        svgout.addLine((m_aretes[i].first)->getX() * 100, (m_aretes[i].first)->getY() * 100, (m_aretes[i].second)->getX() * 100, (m_aretes[i].second)->getY() * 100);
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

void Graphe::menu()
{
    int choix = 0;
    while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8 && choix != 9)
    {
        system("cls");
        std::cout << "1) Calculer l'indice normalise de centralite de degre" << std::endl;
        std::cout << "2) Calculer l'indice non normalise de centralite de degre" << std::endl << std::endl;
        std::cout << "3) Calculer l'indice normalise de vecteur propre" << std::endl;
        std::cout << "4) Calculer l'indice non normalise de vecteur propre" << std::endl << std::endl;
        std::cout << "5) Calculer l'indice normalise de centralite de degre" << std::endl;
        std::cout << "6) Calculer l'indice non normalise de centralite de degre" << std::endl << std::endl;
        std::cout << "7) Supprimer des aretes du graphe" << std::endl << std::endl;
        std::cout << "8) Charger un nouveau fichier de ponderation" << std::endl;
        std::cout << "9) Quitter" << std::endl << std::endl;
        std::cout << "Que choisissez-vous ? ";
        std::cin >> choix;
    }
    switch(choix)
    {
    case 6 :

    case 7 :
        Dijkstrat(0, 1);
        break;
    case 8 :
        ponderation();
        break;
    case 9 :
        exit(1);
        break;
    }
}

void Graphe::Dijkstrat(int num_s0, int num_Sf)
{

    ///Initialisation
    std::vector<int> couleurs((int)m_sommets.size(),0);
    std::vector<int> preds((int)m_sommets.size(),-1);
    std::vector<double> dists((int)m_sommets.size(),-1);



    dists[num_s0]=0;

    ///Boucle de recherche
    do
    {
        int dMin=-1;
        Sommet* s;
        for(int i=0; i<dists.size(); ++i)
        {
            if(dists[i]!=-1 && couleurs[i]!=1)
            {
                if(dists[i]<dMin || dMin==-1)
                {
                    dMin=dists[i];
                    s=m_sommets[i];
                }
            }
        }

        int id=s->getIndice();
        couleurs[id]=1;
        std::cout<<s->getNom();
        std::cout<<s->getVoisins()[0];



        for(auto s2:s->getVoisins())
        {
            std::cout<<"oui";
            int id2 = s2->getIndice();
            if(!(couleurs[id2]))
            {
                if((dMin+1)<dists[id2] ||dists[id2]==-1)//1=poids arrete (s2.second)
                {
                    dists[id2]=dMin+1;//pareil que ligne 149
                    preds[id2]=id;
                }
            }
        }

    }
    while(couleurs[num_Sf]==0);

    std::cout<<"c'est bon";

    ///Affichage du parcours
    std::vector<int> longueur;

    int i=num_Sf;
    if(i!=num_s0)
    {
        if(preds[i]!=-1)
        {
            std::cout<<i<<" <-- ";
            longueur.push_back(dists[i]);

            size_t j=preds[i];
            while(j!=num_s0)
            {
                std::cout<<j<<" <-- ";
                longueur.push_back(dists[j]);
                j=preds[j];
            }
            std::cout<<j<<" : longueur ";
        }
        longueur.push_back(0);
        for(int y=0; y<longueur.size()-1; ++y)
        {
            std::cout<<longueur[y]-longueur[y+1];
            if(y!=longueur.size()-2)
                std::cout<<"+";
            else
                std::cout<<"="<<dists[num_Sf];
        }
    }
}
