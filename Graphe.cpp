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
        Arete* a = new Arete{indice, getSommetByIndice(extremite1), getSommetByIndice(extremite2)};
        m_aretes.push_back(a);

        getSommetByIndice(extremite1)->ajouter_voisins(getSommetByIndice(extremite2));
        getSommetByIndice(extremite2)->ajouter_voisins(getSommetByIndice(extremite1));
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
    int choix;
    while(choix != 6)
    {
        choix = 0;
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
            break;
        case 2 :
            centralite_vecteur_propre();
            break;
        case 3 :
            indice_proximite();
            break;
        case 4 :
            //supprimerAretes();
            break;
        case 5 :
            ponderation();
            break;
        case 6 :
            exit(1);
            break;
        case 7:
            Sommet* b;
            b=getSommetByIndice(2);
            std::vector<Arete*> a;
            a=getAretesBySommet(b);
            for(size_t i=0; i<a.size(); i++)
            {
                std::cout<<a[i]->getPoids();
            }
            break;
        }
    }
}

void Graphe::supprimerAretes()
{
    int choix;
    system("cls");
    do
    {
        std::cout << "Tapez enter pour revenir au menu principal" << std::endl;
        std::cout << "Indiquez l'indice de l'arete a supprimer : ";
        std::cin >> choix;
        delete getAreteByIndice(choix);
        m_aretes.erase(m_aretes.begin() + choix);
        dessiner();
    }
    while(getch() != 13);
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
    std::vector<int> degres;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        degres.push_back(m_sommets[i]->getVoisins().size());
    }

    system("cls");
    std::cout << "                                              Centralite de degre" << std::endl << std::endl << std::endl;
    std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   "<< degres[i] << "               " << degres[i] / (m_ordre-1) << std::endl;
    }
    std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
    while(getch() != 13)
    {

    }
}

void Graphe::centralite_vecteur_propre()
{
    std::vector<double> tmp(m_ordre);
    double a;
    double lambda = 0;
    double ancienLambda;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        m_sommets[i]->setIndice_vecteur_propre(1);
    }
    do
    {
        ancienLambda = lambda;
        lambda = 0;
        a = 0;
        tmp = {};
        for(int i=0 ; i<m_ordre ; ++i)
        {
            double somme=0;
            for(size_t j=0 ; j < m_sommets[i]->getVoisins().size() ; ++j)
            {
                somme += m_sommets[i]->getVoisins()[j]->getIndice_vecteur_propre();
            }
            tmp.push_back(somme);
        }
        for(int i=0 ; i < m_ordre ; ++i)
        {
            a+= (tmp[i] * tmp[i]);
        }
        lambda = sqrt(a);
        for(int i=0 ; i<m_ordre ; ++i)
        {
            m_sommets[i]->setIndice_vecteur_propre(tmp[i] / lambda);
        }
    }
    while((lambda < (0.95 * ancienLambda)) || (lambda > (1.05 * ancienLambda)));

    system("cls");
    std::cout << "                                              Centralite de vecteur propre" << std::endl << std::endl << std::endl;
    std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   "<< m_sommets[i]->getIndice_vecteur_propre() << "               " << m_sommets[i]->getIndice_vecteur_propre() / (m_ordre-1) << std::endl;
    }

    std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
    while(getch() != 13)
    {

    }
}

std::vector<Arete*> Graphe::getAretesBySommet(Sommet* sommet)
{
    std::vector<Arete*> aretes;
    for(int i=0 ; i<m_taille ; ++i)
    {
        if(m_aretes[i]->getExtremites().first->getIndice() == sommet->getIndice() || m_aretes[i]->getExtremites().second->getIndice() == sommet->getIndice())
        {
            aretes.push_back(m_aretes[i]);
        }
    }
    return aretes;
}

float Graphe::Dijkstrat(int num_s0, int num_Sf)
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
        for(size_t i=0; i<dists.size(); ++i)
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

        for(auto s2:s->getVoisins())
        {

            int id2 = s2->getIndice();
            std::vector<Arete*> a ;
            a = getAretesBySommet(s2);
            int dis2;

            for(size_t o =0; o<a.size(); o++)
            {

                dis2=a[o]->getPoids();
                if(!(couleurs[id2]))
                {
                    if((dMin+dis2)<dists[id2] ||dists[id2]==-1)//1=poids arrete (s2.second)
                    {
                        dists[id2]=dMin+dis2;//pareil que ligne 149
                        preds[id2]=id;
                    }
                }
            }
        }

    }
    while(couleurs[num_Sf]==0);

    ///Affichage du parcours
    std::vector<int> longueur;
    float cpt=0;

    int i=num_Sf;
    if(i!=num_s0)
    {
        if(preds[i]!=-1)
        {
            //std::cout<<i<<" <-- ";
            longueur.push_back(dists[i]);

            int j=preds[i];
            while(j!=num_s0)
            {
                //std::cout<<j<<" <-- ";
                longueur.push_back(dists[j]);
                j=preds[j];
            }
            //std::cout<<j<<" : longueur ";
        }
        longueur.push_back(0);
        for(size_t y=0; y<longueur.size()-1; ++y)
        {
            std::cout<<longueur[y]-longueur[y+1];
            if(y!=longueur.size()-2)
                int a = 1;
            //std::cout<<"+";
            else
                //std::cout<<"="<<dists[num_Sf]<<std::endl;
                cpt=dists[num_Sf];



        }
    }
    return cpt;
}


void Graphe::indice_proximite()
{

    float calcul;
    std::vector<float> nonnorm;
    float distance=0;
    float res;



    for(int j=0; j<m_sommets.size(); j++)
    {
        calcul=0;
        distance=0;

        for(int i=0; i<m_sommets.size(); i++)
        {

            if(m_sommets[j]->getIndice() == m_sommets[i]->getIndice())
            {
                i++;
            }
            if(i<m_sommets.size())
            {
            res=Dijkstrat(m_sommets[j]->getIndice(), m_sommets[i]->getIndice());
            distance+=res;
            }


        }
        calcul=1/distance;

        //std::cout<<m_sommets[j]->getNom()<<"="<<calcul<<std::endl;

        nonnorm.push_back(calcul);

    }

    system("cls");
    std::cout << "                                              Centralite de proximité" << std::endl << std::endl << std::endl;
    std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
    for(int i=0 ; i<m_ordre ; ++i)
    {
       std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   "<< nonnorm[i] << "\t\t\t" << nonnorm[i]*(m_ordre-1) << std::endl;
    }

    std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
    while(getch() != 13)
    {

    }


}


