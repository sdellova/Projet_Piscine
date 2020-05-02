#include "Graphe.h"


Graphe::Graphe(std::ifstream ifs)
{
    int indice, extremite1, extremite2;
    double x, y;
    std::string nom;
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
            repere:
            std::cout << "Ecrivez le nom du fichier de ponderation : ";
            std::cin >> nomFichier;
            std::ifstream ifs{nomFichier};
            if (!ifs)
            {
                std::cout << "Impossible d'ouvrir " << nomFichier << std::endl << std::endl;
                goto repere;
            }
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

void Graphe::dessiner(int valeur)
{
    Svgfile svgout;
    std::string couleur;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        std::ostringstream oss1;
        std::ostringstream oss2;
        std::ostringstream oss3;

        oss1 << "CD = " << m_sommets[i]->getIndice_degre();
        std::string indiceDegre = oss1.str();
        oss2 << "CVP = " << m_sommets[i]->getIndice_vecteur_propre();
        std::string indiceVecteur_propre = oss2.str();
        oss3 << "CP = " << m_sommets[i]->getIndice_proximite();
        std::string indiceProximite = oss3.str();

        std::ostringstream oss4;
        std::ostringstream oss5;
        std::ostringstream oss6;

        oss4 << "CDn = " << m_sommets[i]->getIndice_degre();
        std::string indiceDegreNormalise = oss4.str();
        oss5 << "CVPn = " << m_sommets[i]->getIndice_vecteur_propre();
        std::string indiceVecteur_propreNormalise = oss5.str();
        oss6 << "CPn = " << m_sommets[i]->getIndice_proximite();
        std::string indiceProximiteNormalise = oss6.str();

        switch(m_sommets[i]->getVoisins().size())
        {
        case 0 :
            couleur = "cyan";
            break;
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
            couleur = "pink";
            break;
        case 6 :
            couleur = "purple";
            break;
        case 7 :
            couleur = "brown";
            break;
        }
        svgout.addDisk(m_sommets[i]->getX() * 100, m_sommets[i]->getY() * 100, 7, couleur);
        svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 15, m_sommets[i]->getNom(), couleur);
        if(valeur == 1)
        {
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 30, indiceProximite, couleur);
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 45, indiceVecteur_propre, couleur);
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 60, indiceDegre, couleur);
        }
        if(valeur == 2)
        {
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 30, indiceProximiteNormalise, couleur);
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 45, indiceVecteur_propreNormalise, couleur);
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 60, indiceDegreNormalise, couleur);
        }
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
        while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8 && choix != 9 && choix != 10 && choix != 11 && choix != 12 && choix != 13)
        {
            system("cls");
            std::cout << "1) Calculer les indices de centralite de degre" << std::endl;
            std::cout << "2) Calculer les indices de centralite de vecteur propre" << std::endl;
            std::cout << "3) Calculer les indices de centralite de proximite" << std::endl << std::endl;
            std::cout << "4) Afficher les indices de centralite normalises sur le svg" << std::endl;
            std::cout << "5) Afficher les indices de centralite non normalises sur le svg" << std::endl;
            std::cout << "6) Masquer les indices de centralite sur le svg" << std::endl << std::endl;
            std::cout << "7) Etudier la connexite du graphe" << std::endl << std::endl;
            std::cout << "8) Ajouter des aretes au graphe" << std::endl;
            std::cout << "9) Supprimer des aretes du graphe" << std::endl;
            std::cout << "10) Ajouter des sommets au graphe" << std::endl;
            std::cout << "11) Supprimer des sommets du graphe" << std::endl << std::endl;
            std::cout << "12) Charger un nouveau fichier de ponderation" << std::endl;
            std::cout << "13) Quitter" << std::endl << std::endl;
            std::cout << "Que choisissez-vous ? ";
            std::cin >> choix;
        }
        switch(choix)
        {
        case 1:
            centralite_degre(1);
            break;
        case 2 :
            centralite_vecteur_propre(1);
            break;
        case 3 :
            indice_proximite(1);
            break;
        case 4 :
            dessiner(1);
            break;
        case 5 :
            dessiner(2);
            break;
        case 6 :
            dessiner(0);
            break;
        case 7 :
            connexite();
            break;
        case 8 :
            ajouterAretes();
            break;
        case 9 :
            supprimerAretes();
            break;
        case 10 :
            ajouterSommets();
            break;
        case 11 :
            supprimerSommets();
            break;
        case 12 :
            ponderation();
            break;
        case 13 :
            exit(1);
            break;
        }
    }
}

void Graphe::supprimerAretes()
{
    int choix = 0;
    int entree = 0;
    while(entree != 2)
    {
        system("cls");
        std::cout << "Indiquez l'indice de l'arete a supprimer : ";
        std::cin >> choix;
        if(areteExistante(choix))
        {
            int tmp = getPositionAreteByIndice(choix);
            m_aretes[tmp]->getExtremites().first->retirer_voisins(m_aretes[tmp]->getExtremites().second);
            m_aretes[tmp]->getExtremites().second->retirer_voisins(m_aretes[tmp]->getExtremites().first);
            delete getAreteByIndice(choix);
            m_aretes.erase(m_aretes.begin() + tmp);
            --m_taille;
            double indiceProximiteGlobal_tmp = m_indiceCentraliteProximiteGlobal;
            std::vector<double> indiceDegre_tmp{};
            std::vector<double> indiceVecteur_propre_tmp{};
            std::vector<double> indiceProximite_tmp{};
            std::vector<double> indiceDegreNormalise_tmp{};
            std::vector<double> indiceVecteur_propreNormalise_tmp{};
            std::vector<double> indiceProximiteNormalise_tmp{};
            for(int i=0 ; i<m_ordre ; ++i)
            {
                indiceDegre_tmp.push_back(m_sommets[i]->getIndice_degre());
                indiceVecteur_propre_tmp.push_back(m_sommets[i]->getIndice_vecteur_propre());
                indiceProximite_tmp.push_back(m_sommets[i]->getIndice_proximite());
                indiceDegreNormalise_tmp.push_back(m_sommets[i]->getIndice_degreNormalise());
                indiceVecteur_propreNormalise_tmp.push_back(m_sommets[i]->getIndice_vecteur_propreNormalise());
                indiceProximiteNormalise_tmp.push_back(m_sommets[i]->getIndice_proximiteNormalise());
            }
            centralite_degre(0);
            centralite_vecteur_propre(0);
            //indice_proximite(0);
            sauvegarde();
            dessiner(0);
            std::cout << std::endl << "L'arete a ete supprimee";
            std::cout << std::endl << std::endl << "                             Comparaison avant-apres" << std::endl << std::endl << std::endl;
            std::cout << "           Avant\t\t\t\tApres\t\t\t\tEcart en %" << std::endl << std::endl;
            std::cout << "           CPg = " << indiceProximiteGlobal_tmp << "\t\t\t\tCPg = " << m_indiceCentraliteProximiteGlobal << "\t\t\t" << (m_indiceCentraliteProximiteGlobal / indiceProximiteGlobal_tmp * 100) - 100 << std::endl << std::endl;
            for(int i=0 ; i<m_ordre ; ++i)
            {
                std::cout << "Sommet " << m_sommets[i]->getIndice() << " : " << std::endl;
                std::cout << "          CD = " << indiceDegre_tmp[i] << "\t\t\t\tCD = " << m_sommets[i]->getIndice_degre() << "\t\t\t\t" << (m_sommets[i]->getIndice_degre() / indiceDegre_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CVP = " << indiceVecteur_propre_tmp[i] << "\t\t\tCVP = " << m_sommets[i]->getIndice_vecteur_propre() << "\t\t\t" << (m_sommets[i]->getIndice_vecteur_propre() / indiceVecteur_propre_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CP = " << indiceProximite_tmp[i] << "\t\t\t\tCP = " << m_sommets[i]->getIndice_proximite() <<  "\t\t\t" << (m_sommets[i]->getIndice_proximite() / indiceProximite_tmp[i] * 100) - 100 << std::endl << std::endl;
                std::cout << "          CDn = " << indiceDegreNormalise_tmp[i] << "\t\t\t\tCDn = " << m_sommets[i]->getIndice_degreNormalise() <<  "\t\t\t" << (m_sommets[i]->getIndice_degreNormalise() / indiceDegreNormalise_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CVPn = " << indiceVecteur_propreNormalise_tmp[i] << "\t\t\tCVPn = " << m_sommets[i]->getIndice_vecteur_propreNormalise() << "\t\t" << (m_sommets[i]->getIndice_vecteur_propreNormalise() / indiceVecteur_propreNormalise_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CPn = " << indiceProximiteNormalise_tmp[i] << "\t\t\tCPn = " << m_sommets[i]->getIndice_proximiteNormalise() << "\t\t\t" << (m_sommets[i]->getIndice_proximiteNormalise() / indiceProximiteNormalise_tmp[i] * 100) - 100 << std::endl << std::endl;
            }
            std::cout << "Voulez-vouz supprimer une autre arete ?" << std::endl;

            std::cout << "Ecrivez 1 pour oui, 2 pour non : ";
            std::cin >> entree;

        }
        else
        {
            std::cout << std::endl << "L'arete n'existe pas";
            Sleep(2000);
        }
    }
}

bool Graphe::areteExistante(int indice)
{
    if(m_taille == 0)
        return 0;
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

bool Graphe::sommetExistant(int indice, std::string nom)
{
    if(m_ordre == 0)
        return 0;
    int i = 0;
    while(m_sommets[i]->getIndice() != indice && m_sommets[i]->getNom() != nom)
    {
        if(i == (m_ordre - 1))
        {
            return 0;
        }
        ++i;
    }
    return 1;
}

int Graphe::getPositionAreteByIndice(int indice)
{
    int i = 0;
    while(m_aretes[i]->getIndice() != indice)
    {
        ++i;
    }
    return i;
}

int Graphe::getPositionSommetByIndice(int indice)
{
    int i = 0;
    while(m_sommets[i]->getIndice() != indice)
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
    double ordre=m_ordre;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        m_sommets[i]->setIndice_degre(m_sommets[i]->getVoisins().size());
        m_sommets[i]->setIndice_degreNormalise(m_sommets[i]->getVoisins().size()/(ordre-1));
    }

    if(valeur)
    {
        system("cls");
        std::cout << "                                              Centralite de degre" << std::endl << std::endl << std::endl;
        std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
        for(int i=0 ; i<m_ordre ; ++i)
        {
            std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   " << m_sommets[i]->getIndice_degre() << "               " << m_sommets[i]->getIndice_degreNormalise() << std::endl;
        }
        std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
        while(getch() != 13)
        {

        }
    }
}

void Graphe::centralite_vecteur_propre(bool valeur)
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
            m_sommets[i]->setIndice_vecteur_propreNormalise(m_sommets[i]->getIndice_vecteur_propre() / (m_ordre-1));
        }
    }
    while((lambda < (0.95 * ancienLambda)) || (lambda > (1.05 * ancienLambda)));
    if(valeur)
    {
        system("cls");
        std::cout << "                                              Centralite de vecteur propre" << std::endl << std::endl << std::endl;
        std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
        for(int i=0 ; i<m_ordre ; ++i)
        {
            std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   "<< m_sommets[i]->getIndice_vecteur_propre() << "               " << m_sommets[i]->getIndice_vecteur_propreNormalise() << std::endl;
        }

        std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
        while(getch() != 13)
        {

        }
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

std::vector<Arete*> Graphe::getAretesBy2Sommets(Sommet* sommet1, Sommet* sommet2)
{
    std::vector<Arete*> aretes;
    for(int i=0 ; i<m_taille ; ++i)
    {
        if((m_aretes[i]->getExtremites().first->getIndice() == sommet1->getIndice() && m_aretes[i]->getExtremites().second->getIndice() == sommet2->getIndice()) || (m_aretes[i]->getExtremites().first->getIndice() == sommet2->getIndice() && m_aretes[i]->getExtremites().second->getIndice() == sommet1->getIndice()))
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
    float CPT=0;


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
            CPT++;
            if(CPT>50)
            {
                return 0;
            }
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
    int a=0;
    float cpt=0;
    int i=num_Sf;
    if(i!=num_s0)
    {
        if(preds[i]!=-1)
        {
            // std::cout<<i<<" <-- ";
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
            if(y!=longueur.size()-2)
                a+=1;
            //std::cout<<"+";
            else
                // std::cout<<"="<<dists[num_Sf]<<std::endl;
                cpt=dists[num_Sf];
        }
    }
    return cpt;

}


bool Graphe::indice_proximite(bool a)
{
    bool connexe=1;
    float calcul;
    float distance=0;
    float res=0;
    for(size_t j=0; j<m_sommets.size(); j++)
    {
        calcul=0;
        distance=0;
        res=0;
        if(m_sommets[j]->getVoisins().size()==0)
        {
            m_sommets[j]->setIndice_proximite(0);
            m_sommets[j]->setIndice_proximiteNormalise(0);

            j++;
        }

        for(size_t i=0; i<m_sommets.size(); i++)
        {
            if(m_sommets[i]->getVoisins().size()==0)
            {
                i++;
            }

            if(m_sommets[j]->getIndice() == m_sommets[i]->getIndice())
            {
                i++;
            }
            if(i<m_sommets.size())
            {
                res=Dijkstrat(m_sommets[j]->getIndice(), m_sommets[i]->getIndice());
                distance+=res;
                if(res==0)
                {
                    connexe=0;
                }
            }
        }
        calcul=1/distance;

        m_sommets[j]->setIndice_proximite(calcul);
        m_sommets[j]->setIndice_proximiteNormalise(calcul * (m_ordre - 1));
    }
    double x = 0;
    for(int i = 0 ; i<m_ordre ; ++i)
    {
        x += getIndiceProximiteMax() - m_sommets[i]->getIndice_proximite();
    }
    x/= (pow(m_ordre, 2) - (3 * m_ordre) + 2)/((2 * m_ordre) - 3);
    m_indiceCentraliteProximiteGlobal = x;
    if(a)
    {
        system("cls");
        std::cout << "                                              Centralite de proximite" << std::endl << std::endl << std::endl;
        std::cout << "Indice de centralite de proximite global : " << m_indiceCentraliteProximiteGlobal << std::endl << std::endl;
        std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
        for(int i=0 ; i<m_ordre ; ++i)
        {
            std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   "<< m_sommets[i]->getIndice_proximite() << "\t\t\t" << m_sommets[i]->getIndice_proximiteNormalise() << std::endl;
        }

        std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
        while(getch() != 13)
        {

        }
    }
    return connexe;
}

void Graphe::sauvegarde()
{
    std::ofstream ofs;
    ofs.open ("Indices.txt", std::ofstream::out | std::ofstream::app);
    if(ofs)
    {
        for(int i=0 ; i<m_ordre ; ++i)
        {
            ofs << "Sommet " << m_sommets[i]->getIndice() << " : CD = " << m_sommets[i]->getIndice_degre() << "     ;     CDn = " << m_sommets[i]->getIndice_degreNormalise() << "     ;     CVP = " << m_sommets[i]->getIndice_vecteur_propre() << "     ;     CVPn = " << m_sommets[i]->getIndice_vecteur_propreNormalise() << "     ;     CP = " << m_sommets[i]->getIndice_proximite() << "     ;     CPn = " << m_sommets[i]->getIndice_proximiteNormalise() << "     ;     CPg = " << m_indiceCentraliteProximiteGlobal << std::endl;
        }
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier indice.txt" << std::endl;
    }
}

void Graphe::intermediarite()
{
    //float res=0;
    //res=Dijkstrat(0,4);
    //std::cout<<"=" <<res<<std::endl;

}

void Graphe::connexite()
{
    int degreMax = getDegreMax();
    system("cls");
    if(indice_proximite(0))
    {
        std::cout << "Le graphe est connexe." << std::endl << std::endl;
        bool a;
        int k = 1;
        do
        {
            a = effectue(m_taille, k);
            ++k;
        }
        while(k <= degreMax && a);
        std::cout << "Le graphe est " << k-1 << "-arete-connexe." << std::endl << std::endl;
    }
    else
    {
        std::cout << "Le graphe n'est pas connexe" << std::endl << std::endl;
    }
    std::cout << "Tapez enter pour revenir au menu principal";
}

void Graphe::ajouterAretes()
{
    int entree;
    int indice, sommet1, sommet2;
    while(entree != 2)
    {
        do
        {
            system("cls");
            std::cout << "Indice : ";
            std::cin >> indice;
        }
        while(areteExistante(indice));
        do
        {
            std::cout << std::endl << "Indice du sommet 1 : ";
            std::cin >> sommet1;
            std::cout << std::endl << "Indice du sommet 2 : ";
            std::cin >> sommet2;
        }
        while(!sommetExistant(sommet1) || !sommetExistant(sommet2));
        std::cout << "L'arete " << indice << " a ete rajoutee.";
        m_aretes.push_back(new Arete{indice, getSommetByIndice(sommet1), getSommetByIndice(sommet2)});
        getSommetByIndice(sommet1)->ajouter_voisins(getSommetByIndice(sommet2));
        getSommetByIndice(sommet2)->ajouter_voisins(getSommetByIndice(sommet1));
        ++m_taille;
        double indiceProximiteGlobal_tmp = m_indiceCentraliteProximiteGlobal;
        std::vector<double> indiceDegre_tmp{};
        std::vector<double> indiceVecteur_propre_tmp{};
        std::vector<double> indiceProximite_tmp{};
        std::vector<double> indiceDegreNormalise_tmp{};
        std::vector<double> indiceVecteur_propreNormalise_tmp{};
        std::vector<double> indiceProximiteNormalise_tmp{};
        for(int i=0 ; i<m_ordre ; ++i)
        {
            indiceDegre_tmp.push_back(m_sommets[i]->getIndice_degre());
            indiceVecteur_propre_tmp.push_back(m_sommets[i]->getIndice_vecteur_propre());
            indiceProximite_tmp.push_back(m_sommets[i]->getIndice_proximite());
            indiceDegreNormalise_tmp.push_back(m_sommets[i]->getIndice_degreNormalise());
            indiceVecteur_propreNormalise_tmp.push_back(m_sommets[i]->getIndice_vecteur_propreNormalise());
            indiceProximiteNormalise_tmp.push_back(m_sommets[i]->getIndice_proximiteNormalise());
        }
        centralite_degre(0);
        centralite_vecteur_propre(0);
        //indice_proximite(0);
        sauvegarde();
        dessiner(0);
        std::cout << std::endl << "L'arete a ete rajoutee";
        std::cout << std::endl << std::endl << "                             Comparaison avant-apres" << std::endl << std::endl << std::endl;
        std::cout << "           Avant\t\t\t\tApres\t\t\t\tEcart en %" << std::endl << std::endl;
            std::cout << "           CPg = " << indiceProximiteGlobal_tmp << "\t\t\t\tCPg = " << m_indiceCentraliteProximiteGlobal << "\t\t\t" << (m_indiceCentraliteProximiteGlobal / indiceProximiteGlobal_tmp * 100) - 100 << std::endl << std::endl;
        for(int i=0 ; i<m_ordre ; ++i)
        {
            std::cout << "Sommet " << m_sommets[i]->getIndice() << " : " << std::endl;
            std::cout << "          CD = " << indiceDegre_tmp[i] << "\t\t\t\tCD = " << m_sommets[i]->getIndice_degre() << "\t\t\t\t" << (m_sommets[i]->getIndice_degre() / indiceDegre_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CVP = " << indiceVecteur_propre_tmp[i] << "\t\t\tCVP = " << m_sommets[i]->getIndice_vecteur_propre() << "\t\t\t" << (m_sommets[i]->getIndice_vecteur_propre() / indiceVecteur_propre_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CP = " << indiceProximite_tmp[i] << "\t\t\t\tCP = " << m_sommets[i]->getIndice_proximite() <<  "\t\t\t" << (m_sommets[i]->getIndice_proximite() / indiceProximite_tmp[i] * 100) - 100 << std::endl << std::endl;
            std::cout << "          CDn = " << indiceDegreNormalise_tmp[i] << "\t\t\t\tCDn = " << m_sommets[i]->getIndice_degreNormalise() <<  "\t\t\t" << (m_sommets[i]->getIndice_degreNormalise() / indiceDegreNormalise_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CVPn = " << indiceVecteur_propreNormalise_tmp[i] << "\t\t\tCVPn = " << m_sommets[i]->getIndice_vecteur_propreNormalise() << "\t\t" << (m_sommets[i]->getIndice_vecteur_propreNormalise() / indiceVecteur_propreNormalise_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CPn = " << indiceProximiteNormalise_tmp[i] << "\t\t\tCPn = " << m_sommets[i]->getIndice_proximiteNormalise() << "\t\t\t" << (m_sommets[i]->getIndice_proximiteNormalise() / indiceProximiteNormalise_tmp[i] * 100) - 100 << std::endl << std::endl;
        }
        std::cout << "Voulez-vouz rajouter une autre arete ?" << std::endl;
        std::cout << "Ecrivez 1 pour oui, 2 pour non : ";
        std::cin >> entree;
    }
}

void Graphe::ajouterSommets()
{
    int entree;
    int indice;
    std::string nom;
    double x, y;
    while(entree != 2)
    {
        do
        {
            system("cls");
            std::cout << "Indice : ";
            std::cin >> indice;
            std::cout << std::endl << "Nom : ";
            std::cin >> nom;
        }
        while(sommetExistant(indice, nom));
        std::cout << std::endl << "x : ";
        std::cin >> x;
        std::cout << std::endl << "y : ";
        std::cin >> y;
        m_sommets.push_back(new Sommet{indice, nom, x, y});
        ++ m_ordre;
        double indiceProximiteGlobal_tmp = m_indiceCentraliteProximiteGlobal;
        std::vector<double> indiceDegre_tmp{};
        std::vector<double> indiceVecteur_propre_tmp{};
        std::vector<double> indiceProximite_tmp{};
        std::vector<double> indiceDegreNormalise_tmp{};
        std::vector<double> indiceVecteur_propreNormalise_tmp{};
        std::vector<double> indiceProximiteNormalise_tmp{};
        for(int i=0 ; i<m_ordre ; ++i)
        {
            indiceDegre_tmp.push_back(m_sommets[i]->getIndice_degre());
            indiceVecteur_propre_tmp.push_back(m_sommets[i]->getIndice_vecteur_propre());
            indiceProximite_tmp.push_back(m_sommets[i]->getIndice_proximite());
            indiceDegreNormalise_tmp.push_back(m_sommets[i]->getIndice_degreNormalise());
            indiceVecteur_propreNormalise_tmp.push_back(m_sommets[i]->getIndice_vecteur_propreNormalise());
            indiceProximiteNormalise_tmp.push_back(m_sommets[i]->getIndice_proximiteNormalise());
        }
        centralite_degre(0);
        centralite_vecteur_propre(0);
        //indice_proximite(0);
        sauvegarde();
        dessiner(0);
        std::cout << std::endl << "Le sommet a ete rajoute";
        std::cout << std::endl << std::endl << "                             Comparaison avant-apres" << std::endl << std::endl << std::endl;
        std::cout << "           Avant\t\t\t\tApres\t\t\t\tEcart en %" << std::endl << std::endl;
            std::cout << "           CPg = " << indiceProximiteGlobal_tmp << "\t\t\t\tCPg = " << m_indiceCentraliteProximiteGlobal << "\t\t\t" << (m_indiceCentraliteProximiteGlobal / indiceProximiteGlobal_tmp * 100) - 100 << std::endl << std::endl;
        for(int i=0 ; i<m_ordre ; ++i)
        {
            std::cout << "Sommet " << m_sommets[i]->getIndice() << " : " << std::endl;
            std::cout << "          CD = " << indiceDegre_tmp[i] << "\t\t\t\tCD = " << m_sommets[i]->getIndice_degre() << "\t\t\t\t" << (m_sommets[i]->getIndice_degre() / indiceDegre_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CVP = " << indiceVecteur_propre_tmp[i] << "\t\t\tCVP = " << m_sommets[i]->getIndice_vecteur_propre() << "\t\t\t" << (m_sommets[i]->getIndice_vecteur_propre() / indiceVecteur_propre_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CP = " << indiceProximite_tmp[i] << "\t\t\t\tCP = " << m_sommets[i]->getIndice_proximite() <<  "\t\t\t" << (m_sommets[i]->getIndice_proximite() / indiceProximite_tmp[i] * 100) - 100 << std::endl << std::endl;
            std::cout << "          CDn = " << indiceDegreNormalise_tmp[i] << "\t\t\t\tCDn = " << m_sommets[i]->getIndice_degreNormalise() <<  "\t\t\t" << (m_sommets[i]->getIndice_degreNormalise() / indiceDegreNormalise_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CVPn = " << indiceVecteur_propreNormalise_tmp[i] << "\t\t\tCVPn = " << m_sommets[i]->getIndice_vecteur_propreNormalise() << "\t\t" << (m_sommets[i]->getIndice_vecteur_propreNormalise() / indiceVecteur_propreNormalise_tmp[i] * 100) - 100 << std::endl;
            std::cout << "          CPn = " << indiceProximiteNormalise_tmp[i] << "\t\t\tCPn = " << m_sommets[i]->getIndice_proximiteNormalise() << "\t\t\t" << (m_sommets[i]->getIndice_proximiteNormalise() / indiceProximiteNormalise_tmp[i] * 100) - 100 << std::endl << std::endl;
        }
        std::cout << "Voulez-vouz rajouter un autre sommet ?" << std::endl;
        std::cout << "Ecrivez 1 pour oui, 2 pour non : ";
        std::cin >> entree;
    }
}

void Graphe::supprimerSommets()
{
    int choix = 0;
    int entree = 0;
    while(entree != 2)
    {
        system("cls");
        std::cout << "Indiquez l'indice du sommet a supprimer : ";
        std::cin >> choix;
        if(sommetExistant(choix))
        {
            for(int i=0 ; i<getSommetByIndice(choix)->getIndice_degre() ; ++i)
            {
                int tmp = getPositionAreteByIndice(getAretesBySommet(getSommetByIndice(choix))[0]->getIndice());
                m_aretes[tmp]->getExtremites().first->retirer_voisins(m_aretes[tmp]->getExtremites().second);
                m_aretes[tmp]->getExtremites().second->retirer_voisins(m_aretes[tmp]->getExtremites().first);
                delete getAreteByIndice(getAretesBySommet(getSommetByIndice(choix))[0]->getIndice());
                m_aretes.erase(m_aretes.begin() + tmp);
                --m_taille;
            }
            int tmp = getPositionSommetByIndice(choix);
            delete getSommetByIndice(choix);
            m_sommets.erase(m_sommets.begin() + tmp);
            --m_ordre;
            double indiceProximiteGlobal_tmp = m_indiceCentraliteProximiteGlobal;
            std::vector<double> indiceDegre_tmp{};
            std::vector<double> indiceVecteur_propre_tmp{};
            std::vector<double> indiceProximite_tmp{};
            std::vector<double> indiceDegreNormalise_tmp{};
            std::vector<double> indiceVecteur_propreNormalise_tmp{};
            std::vector<double> indiceProximiteNormalise_tmp{};
            for(int i=0 ; i<m_ordre ; ++i)
            {
                indiceDegre_tmp.push_back(m_sommets[i]->getIndice_degre());
                indiceVecteur_propre_tmp.push_back(m_sommets[i]->getIndice_vecteur_propre());
                indiceProximite_tmp.push_back(m_sommets[i]->getIndice_proximite());
                indiceDegreNormalise_tmp.push_back(m_sommets[i]->getIndice_degreNormalise());
                indiceVecteur_propreNormalise_tmp.push_back(m_sommets[i]->getIndice_vecteur_propreNormalise());
                indiceProximiteNormalise_tmp.push_back(m_sommets[i]->getIndice_proximiteNormalise());
            }
            centralite_degre(0);
            centralite_vecteur_propre(0);
            //indice_proximite(0);
            sauvegarde();
            dessiner(0);
            std::cout << std::endl << "Le sommet a ete supprime";
            std::cout << std::endl << std::endl << "                             Comparaison avant-apres" << std::endl << std::endl << std::endl;
            std::cout << "           Avant\t\t\t\tApres\t\t\t\tEcart en %" << std::endl << std::endl;
            std::cout << "           CPg = " << indiceProximiteGlobal_tmp << "\t\t\t\tCPg = " << m_indiceCentraliteProximiteGlobal << "\t\t\t" << (m_indiceCentraliteProximiteGlobal / indiceProximiteGlobal_tmp * 100) - 100 << std::endl << std::endl;
            for(int i=0 ; i<m_ordre ; ++i)
            {
                std::cout << "Sommet " << m_sommets[i]->getIndice() << " : " << std::endl;
                std::cout << "          CD = " << indiceDegre_tmp[i] << "\t\t\t\tCD = " << m_sommets[i]->getIndice_degre() << "\t\t\t\t" << (m_sommets[i]->getIndice_degre() / indiceDegre_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CVP = " << indiceVecteur_propre_tmp[i] << "\t\t\tCVP = " << m_sommets[i]->getIndice_vecteur_propre() << "\t\t\t" << (m_sommets[i]->getIndice_vecteur_propre() / indiceVecteur_propre_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CP = " << indiceProximite_tmp[i] << "\t\t\t\tCP = " << m_sommets[i]->getIndice_proximite() <<  "\t\t\t" << (m_sommets[i]->getIndice_proximite() / indiceProximite_tmp[i] * 100) - 100 << std::endl << std::endl;
                std::cout << "          CDn = " << indiceDegreNormalise_tmp[i] << "\t\t\t\tCDn = " << m_sommets[i]->getIndice_degreNormalise() <<  "\t\t\t" << (m_sommets[i]->getIndice_degreNormalise() / indiceDegreNormalise_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CVPn = " << indiceVecteur_propreNormalise_tmp[i] << "\t\t\tCVPn = " << m_sommets[i]->getIndice_vecteur_propreNormalise() << "\t\t" << (m_sommets[i]->getIndice_vecteur_propreNormalise() / indiceVecteur_propreNormalise_tmp[i] * 100) - 100 << std::endl;
                std::cout << "          CPn = " << indiceProximiteNormalise_tmp[i] << "\t\t\tCPn = " << m_sommets[i]->getIndice_proximiteNormalise() << "\t\t\t" << (m_sommets[i]->getIndice_proximiteNormalise() / indiceProximiteNormalise_tmp[i] * 100) - 100 << std::endl << std::endl;
            }
            std::cout << "Voulez-vouz supprimer un autre sommet ?" << std::endl;
            std::cout << "Ecrivez 1 pour oui, 2 pour non : ";
            std::cin >> entree;
        }
        else
        {
            std::cout << std::endl << "Le sommet n'existe pas";
            Sleep(2000);
        }
    }
}

bool Graphe::effectue(int taille, int k)
{
    int L[k], t[taille], i;
    for(i=0; i<taille; ++i)
    {
        t[i] = i;
    }
    return combinaisons(taille, k, 0, L, t, taille);
}

bool Graphe::combinaisons(int taille, int k, int x, int *L, int *t, int r)
{
    int i, j, j1, t2[taille];
    if(r<k-x)
        return 1;
    if(x==k)
    {
        Sommet* sommet1_tmp;
        Sommet* sommet2_tmp;
        for(i=0; i<k; ++i)
        {
            sommet1_tmp = m_aretes[L[i]]->getExtremites().first;
            sommet2_tmp = m_aretes[L[i]]->getExtremites().second;
            int tmp = getPositionAreteByIndice(m_aretes[L[i]]->getIndice());
            m_aretes[tmp]->getExtremites().first->retirer_voisins(m_aretes[tmp]->getExtremites().second);
            m_aretes[tmp]->getExtremites().second->retirer_voisins(m_aretes[tmp]->getExtremites().first);
            --m_taille;
        }
        bool a = indice_proximite(0);
        if(!a)
            return 0;
        for(i=0; i<k; ++i)
        {
            sommet1_tmp->ajouter_voisins(sommet2_tmp);
            sommet2_tmp->ajouter_voisins(sommet1_tmp);
        }
        return 1;
    }
    for(i=0; i<r; ++i)
    {
        L[x] = t[i];
        for(j=i+1, j1=0; j<r; ++j, ++j1)
        {
            t2[j1] = t[j];
        }
        combinaisons(taille, k, x+1, L, t2, j1);
    }
    return 1;
}

int Graphe::getDegreMax()
{
    int a = 0;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        if(m_sommets[i]->getIndice_degre() > a)
            a = m_sommets[i]->getIndice_degre();
    }
    return a;
}

std::ifstream Graphe::afficherMenu()
{
    std::string nomFichier;
    repere:
    std::cout << "Ecrivez le nom du graphe a charger : ";
    std::cin >> nomFichier;
    std::ifstream ifs{nomFichier};
    if(!ifs)
    {
        std::cout << "Impossible d'ouvrir " << nomFichier << std::endl << std::endl;
        goto repere;
    }
    return ifs;
}

double Graphe::getIndiceProximiteMax()
{
    double a = 0;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        if(m_sommets[i]->getIndice_proximite() > a)
            a = m_sommets[i]->getIndice_proximite();
    }
    return a;
}
