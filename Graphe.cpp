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
    std::string couleur;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        std::ostringstream oss1;
        std::ostringstream oss2;
        std::ostringstream oss3;
        oss1 << "CD : " << m_sommets[i]->getIndice_degre();
        std::string indiceDegre = oss1.str();
        oss2 << "CVP : " << m_sommets[i]->getIndice_vecteur_propre();
        std::string indiceVecteur_propre = oss2.str();
        oss3 << "CP : ";
        std::string indiceProximite = oss3.str();
        switch(m_sommets[i]->getVoisins().size())
        {
        case 1 :
            couleur = "yellow";
            break;
        case 2 :
            couleur = "green";
            break;
        case 3 :
            couleur = "orange";
            break;
        case 4 :
            couleur = "red";
            break;
        case 5 :
            couleur = "purple";
            break;
        }
        svgout.addDisk(m_sommets[i]->getX() * 100, m_sommets[i]->getY() * 100, 7, couleur);
        svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 15, m_sommets[i]->getNom());
        svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 30, indiceProximite);
        svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 45, indiceVecteur_propre);
        svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 60, indiceDegre);
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
        while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6)
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
            centralite_degre(1);
            break;
        case 2 :
            centralite_vecteur_propre();
            break;
        case 3 :
            indice_proximite(0);
            indice_proximite_normalise(3);
            break;
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
}

void Graphe::supprimerAretes()
{
    int choix = 0;
    while(choix != 50)
    {
        system("cls");
        std::cout << "Entrez 50 pour revenir au menu principal" << std::endl;
        std::cout << "Indiquez l'indice de l'arete a supprimer : ";
        std::cin >> choix;
        if(choix == 50)
            continue;
        if(areteExistante(choix))
        {
            int tmp = getPositionByIndice(choix);
            delete getAreteByIndice(choix);
            m_aretes.erase(m_aretes.begin() + tmp);
            --m_taille;
            dessiner();
        }
        else
        {
            std::cout << std::endl << "L'arete n'existe pas" << std::endl;
        }
        Sleep(3000);
    }
}

bool Graphe::areteExistante(int indice)
{
    int i = 0;
    while(m_aretes[i]->getIndice() != indice)
    {
        if(i == (m_taille - 1))
        {
            return 0;
        }
        ++i;
    }
    return 1;
}

int Graphe::getPositionByIndice(int indice)
{
    int i = 0;
    while(m_aretes[i]->getIndice() != indice)
    {
        ++i;
    }
    return i;
}

int Graphe::getOrdre() const
{
    return m_ordre;
}

int Graphe::getTaille()
{
    return m_taille;
}

void Graphe::centralite_degre(bool valeur)
{
    for(int i=0 ; i<m_ordre ; ++i)
    {
        m_sommets[i]->setIndice_degre(m_sommets[i]->getVoisins().size());
    }

    if(valeur)
    {
    system("cls");
    std::cout << "                                              Centralite de degre" << std::endl << std::endl << std::endl;
    std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   " << m_sommets[i]->getIndice_degre() << "               " << m_sommets[i]->getIndice_degre() / (m_ordre-1) << std::endl;
    }
    std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
    while(getch() != 13)
    {

    }
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
            //std::cout<<longueur[y]-longueur[y+1];
            if(y!=longueur.size()-2)
                int a = 1;
            //std::cout<<"+";
            else
                //std::cout<<"="<<dists[num_Sf]<<std::endl;
                cpt=dists[num_Sf];



        }
    }
    //std::cout<<"cpt="<<cpt;
    return cpt;
}

float Graphe::indice_proximite(int a)
{

    float calcul;
    float distance=0;
    float res;
    //res=Dijkstrat(a, 1);

    for(size_t i=0; i<m_sommets.size(); i++)
    {

        if(a == m_sommets[i]->getIndice())
        {
            i++;
        }
        std::cout<<m_sommets[i]->getIndice()<<std::endl;
        res=Dijkstrat(a, m_sommets[i]->getIndice());
        distance+=res;
        std::cout<<distance<<std::endl;

    }
    std::cout<<"distance final ="<<distance<<std::endl;
    calcul=1/distance;
    std::cout<<"final = "<<calcul;
    return calcul;
}

float Graphe::indice_proximite_normalise(int s)
{
    float calcul;
    float indice;
    indice = indice_proximite(s);
    std::cout<<indice<<std::endl;
    std::cout<<"ordre-1"<<m_ordre-1<<std::endl;
    calcul= (m_ordre-1)*indice;
    std::cout<<calcul;
    return calcul;
}
