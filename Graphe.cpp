#include "Graphe.h"
#include <cstdlib>
#include <ctime>
#include <queue>

///constructeur de la classe graphe permettant de lire et charger un fichier d'apres son nom///
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
    indice_proximite(0);
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

        oss4 << "CDn = " << m_sommets[i]->getIndice_degreNormalise();
        std::string indiceDegreNormalise = oss4.str();
        oss5 << "CVPn = " << m_sommets[i]->getIndice_vecteur_propreNormalise();
        std::string indiceVecteur_propreNormalise = oss5.str();
        oss6 << "CPn = " << m_sommets[i]->getIndice_proximiteNormalise();
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
        if(valeur == 3)
        {
            if(m_sommets[i]->getContamine())
                couleur = "grey";
        }
        svgout.addDisk(m_sommets[i]->getX() * 100, m_sommets[i]->getY() * 100, 7, couleur);
        svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 15, m_sommets[i]->getNom(), couleur);
        if(valeur == 2)
        {
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 30, indiceProximite, couleur);
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 45, indiceVecteur_propre, couleur);
            svgout.addText((m_sommets[i]->getX() * 100) - 6, (m_sommets[i]->getY() * 100) - 60, indiceDegre, couleur);
        }
        if(valeur == 1)
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

///retourn un sommet grace a son indice///
Sommet* Graphe::getSommetByIndice(int indice)
{
    int i = 0;
    while(m_sommets[i]->getIndice() != indice)
    {
        ++i;
    }
    return m_sommets[i];
}

///retourne une arrete grace a son indice///
Arete* Graphe::getAreteByIndice(int indice)
{
    int i = 0;
    while(m_aretes[i]->getIndice() != indice)
    {
        ++i;
    }
    return m_aretes[i];
}

///affiche le menu et grace au switch permet d'utliser les methodes de graphe///
void Graphe::menu()
{
    int choix;
    while(choix != 15)
    {
        choix = 0;
        while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8 && choix != 9 && choix != 10 && choix != 11 && choix != 12 && choix != 13 && choix!= 14 && choix != 15)
        {
            system("cls");
            std::cout << "1) Calculer les indices de centralite de degre" << std::endl;
            std::cout << "2) Calculer les indices de centralite de vecteur propre" << std::endl;
            std::cout << "3) Calculer les indices de centralite de proximite" << std::endl;
            std::cout << "4) Calculer les indices de centralite d'intermediarite" << std::endl << std::endl;
            std::cout << "5) Afficher les indices de centralite normalises sur le svg" << std::endl;
            std::cout << "6) Afficher les indices de centralite non normalises sur le svg" << std::endl;
            std::cout << "7) Masquer les indices de centralite sur le svg" << std::endl << std::endl;
            std::cout << "8) Etudier la connexite du graphe" << std::endl << std::endl;
            std::cout << "9) Ajouter des aretes au graphe" << std::endl;
            std::cout << "10) Supprimer des aretes du graphe" << std::endl;
            std::cout << "11) Ajouter des sommets au graphe" << std::endl;
            std::cout << "12) Supprimer des sommets du graphe" << std::endl << std::endl;
            std::cout << "13) Lancer la simulation" << std::endl << std::endl;
            std::cout << "14) Charger un nouveau fichier de ponderation" << std::endl;
            std::cout << "15) Quitter" << std::endl << std::endl;
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
            intermediarite();
            break;
        case 5 :
            dessiner(1);
            break;
        case 6 :
            dessiner(2);
            break;
        case 7 :
            dessiner();
            break;
        case 8 :
            connexite();
            break;
        case 9 :
            ajouterAretes();
            break;
        case 10 :
            supprimerAretes();
            break;
        case 11 :
            ajouterSommets();
            break;
        case 12 :
            supprimerSommets();
            break;
        case 13 :
            simulation();
            break;
        case 14 :
            ponderation();
            break;
        case 15 :
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
            indice_proximite(0);
            sauvegarde();
            dessiner();
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

///d'apres l'indice de l'arrete///
///retourne 1 si l'arrete existe 0 sinon///
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

///grace a son nom et son indice permet de savoir si un sommet existe///
///retourne 1 si il existe 0 sinon///
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

///retourne la position dans le vecteur d'arrete de l'arrete choisi grace a son indice///
int Graphe::getPositionAreteByIndice(int indice)
{
    int i = 0;
    while(m_aretes[i]->getIndice() != indice)
    {
        ++i;
    }
    return i;
}

///retourne la position dans le vecteur de sommet le sommet choisi grace a son indice///
int Graphe::getPositionSommetByIndice(int indice)
{
    int i = 0;
    while(m_sommets[i]->getIndice() != indice)
    {
        ++i;
    }
    return i;
}

///retourne l'ordre du graphe///
int Graphe::getOrdre() const
{
    return m_ordre;
}

///retourne la taille du graphe///
int Graphe::getTaille()
{
    return m_taille;
}

///permet de calculer la centralite de gre normalise et non normalise de tout les sommets du graphe///
///affiche aussi les resultats obtenue///
void Graphe::centralite_degre(bool valeur)
{
    double ordre=m_ordre;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        ///calcul le nombre de voisin d'un sommet soit son degree///
        m_sommets[i]->setIndice_degre(m_sommets[i]->getVoisins().size());
        ///puis normalise le degre de chaque sommet///
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

///calcul et affiche la centralite de vecteur propre non normalise et normalise de chaque sommet///
void Graphe::centralite_vecteur_propre(bool valeur)
{
    std::vector<double> tmp(m_ordre);
    double a;
    double lambda = 0;
    double ancienLambda;
    ///on initialise tout les indices des sommets a 1///
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
            ///calcul la centralite de vecteur propre de chaque sommet///
            m_sommets[i]->setIndice_vecteur_propre(tmp[i] / lambda);
            ///puis le normalise///
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
    std::vector<Arete*> aretes(0);
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
            std::vector<Arete*> a;
            for(size_t i=0 ; i<getAretesBySommet(s2).size() ; ++i)
            {
                a.push_back(getAretesBySommet(s2)[i]);
            }
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
                    if((dMin+dis2)<dists[id2] ||dists[id2]== -1)//1=poids arrete (s2.second)
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
            connexe = 0;
        }
        if(j<m_sommets.size())
        {
            for(size_t i=0; i<m_sommets.size(); i++)
            {
                if(i<m_sommets.size())
                {
                    if(m_sommets[i]->getVoisins().size()==0)
                    {
                        i++;
                    }
                }
                if(i<m_sommets.size())
                {

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
            }
        }
        calcul=1/distance;
        if(j<m_sommets.size())
        {
            m_sommets[j]->setIndice_proximite(calcul);
            m_sommets[j]->setIndice_proximiteNormalise(calcul * (m_ordre - 1));
        }
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



void Graphe::connexite()
{
    int degreMax = getDegreMax();
    system("cls");
    if(appelBFS())
    {
        std::cout << "Le graphe est connexe." << std::endl << std::endl;
        bool a;
        int k = 1;
        do
        {
            a = effectue(m_taille, k);
            ++k;
            Sleep(1000);
        }
        while(k <= degreMax && a);
        std::cout << "Le graphe est " << k-1 << "-arete-connexe." << std::endl << std::endl;
    }
    else
    {
        std::cout << "Le graphe n'est pas connexe" << std::endl << std::endl;
    }
    std::cout << "Tapez enter pour revenir au menu principal";
    while(getch() != 13)
    {

    }
}

std::vector<int> Graphe::Dijkstrat2(int num_s0, int num_Sf)
{
    ///Initialisation
    std::vector<int> couleurs((int)m_sommets.size(),0);
    std::vector<int> couleurs2((int)m_sommets.size(),0);
    std::vector<int> preds((int)m_sommets.size(),-1);
    std::vector<double> dists((int)m_sommets.size(),-1);
    std::vector<int> chemin;
    std::vector<int> pointerchemin;
    std::vector<int> nul {};

    srand (time(NULL));

    dists[num_s0]=0;
    float CPT=0;

    /*Sommet* j = getSommetByIndice(num_s0);

    if(p!=20)
    {

        for(int i=0; i<j->getVoisins().size(); i++)
        {
            Sommet* a =j->getVoisins()[i];
            int id3 = a->getIndice();
            couleurs2[id3]=1;


        }
        Sommet*b = j->getVoisins()[p];
        //std::cout<<b->getNom();
        id4 = b->getIndice();
        couleurs2[id4]= 0;

        for(int i=0; i<b->getVoisins().size(); i++)
        {
            Sommet* a =b->getVoisins()[i];
            int id3 = a->getIndice();
            //std::cout<<id3<<std::endl;
            couleurs2[id3]=1;

        }
        Sommet*c = b->getVoisins()[rand() % (b->getVoisins().size()-1)];
        int id5 = c->getIndice();
        ///std::cout<<id5<<std::endl;
        couleurs2[id5]= 0;

    }*/


    ///Boucle de recherche
    do
    {
        int dMin=-1;
        Sommet* s;



        for(size_t i=0; i<dists.size(); ++i)
        {
            if(dists[i]!=-1 && couleurs[i]!=1)


            {
                if(dists[i]<=dMin || dMin==-1)
                {
                    dMin=dists[i];
                    s=m_sommets[i];
                }
            }
        }

        int id=s->getIndice();
        couleurs[id]=1;

        if(couleurs[id]==1)
        {
            for(size_t i=0; i<s->getVoisins().size(); i++)
            {
                Sommet* a =s->getVoisins()[i];
                int id3 = a->getIndice();

                couleurs2[id3]=1;

            }


            Sommet*c = s->getVoisins()[rand()%(s->getVoisins().size())];
            int id5 = c->getIndice();
            couleurs2[id5]= 0;
        }

        for(auto s2:s->getVoisins())
        {
            int id2 = s2->getIndice();
            std::vector<Arete*> a ;
            a = getAretesBySommet(s2);


            CPT++;
            if(CPT>70)
            {
                return nul;
            }
            int dis2;
            for(size_t o =0; o<a.size(); o++)
            {

                dis2=a[o]->getPoids();
                if(!(couleurs2[id2])&& couleurs[id2]!=1)
                {
                    if((dMin+dis2)<=dists[id2] || dists[id2]==-1)//1=poids arrete (s2.second)
                    {
                        dists[id2]=dMin+dis2;//pareil que ligne 149
                        preds[id2]=id;
                        //couleurs[id2]=1;
                    }
                }
            }


        }

    }
    while(couleurs[num_Sf]==0 );


    ///Affichage du parcours
    std::vector<int> longueur;
    bool b=true;
    int a=0;
    int i=num_Sf;
    if(i!=num_s0)
    {
        if(preds[i]!=-1)
        {
            //std::cout<<i<<" <-- ";
            //std::cout<<"dist  :"<<dists[i];
            chemin.push_back(i);
            longueur.push_back(dists[i]);


            int j=preds[i];
            while(j!=num_s0)
            {
                //std::cout<<j<<" <-- ";
                chemin.push_back(j);
                longueur.push_back(dists[j]);
                j=preds[j];

            }
            //std::cout<<j<<" : longueur ";
        }
        longueur.push_back(0);
        for(size_t y=0; y<longueur.size()-1; ++y)
        {
            if(y!=longueur.size()-2)
            {
                a+=1;
                //std::cout<<"+";

            }
            else
            {
                if(b)
                {
                    chemin.push_back(num_s0);

                    b=false;
                }

            }

        }
    }


    int lc=0;

    for(size_t i=0; i<chemin.size()-1; i++)
    {

        Sommet*a=getSommetByIndice(chemin[i]);
        Sommet*b=getSommetByIndice(chemin[i+1]);

        std::vector<Arete*> ar = getAretesBy2Sommets(a,b);
        Arete* z = ar[0];

        if(ar.size()!=0)
        {
            for(size_t j=1; j<ar.size(); j++)
            {
                Arete* y = ar[j];
                if(y->getPoids()>z->getPoids())
                {
                    z=y;
                }

            }
        }
        lc+=z->getPoids();

    }
    chemin.insert(chemin.begin(), lc);

    return chemin;

}

void Graphe::calculintermediarite(int indice1, int indice2)
{

    int valref;
    int nbrchemin=0;
    /// Appel de Dijkstrat pour trouver la valeur de reference, la plus courte distance entre 2 sommets
    valref = Dijkstrat( indice1, indice2);
    std::cout<<"valeur ref : "<<valref<<std::endl;
    /// Initialisation vector de vector de chemin;
    std::vector<std::vector<int>> listechemins;


    for(int i=0; i<m_ordre*5; i++)
    {
        ///On cree un vector de int pour recuperer le chemin cree par dijkstrat
        std::vector<int>nouvchemin;
        nouvchemin=Dijkstrat2(indice1, indice2);
        if(nouvchemin.size()!=0)
        {
            if(nouvchemin[0]==valref)       ///On verifie qu'il s'agit bien d'un chemin le plus court
            {
                listechemins.push_back(nouvchemin);
                nbrchemin++; /// incrementation du nombre de chemin le plus court
            }
        }
        Sleep(800);
    }
    for(size_t k=0; k<listechemins.size()-1; k++)  ///On parcours le vector de vector de chemin pour supprimer les doublons
    {
        for(size_t j=k+1; j<listechemins.size(); j++)
        {
            if(listechemins[k].size()==listechemins[j].size())
            {
                int taille = listechemins[k].size()-1;
                int cpt=0;
                for(size_t i=1; i<listechemins[k].size(); i++)
                {
                   if(listechemins[k][i]==listechemins[j][i])
                   {
                       cpt++;
                   }
                }
                if(cpt==taille)
                {
                    listechemins.erase(listechemins.cbegin()+j);  ///Supression de 2 chemins identique
                    j--;
                }
            }
        }
    }
    for(size_t k=0; k<m_sommets.size(); k++)
    {
        getSommetByIndice(k)->setzeronbrchemin(); /// remise a zero du nombre de chemin passant par le point d'indice k
        for(size_t i=0; i<listechemins.size(); i++)
        {
            for(size_t j=2; j<listechemins[i].size()-1; j++) /// recherche du sommet k dans un des chemins
            {
                if(listechemins[i][j]==(int)k)
                {
                    getSommetByIndice(k)->ajoutnbrchemin(); /// compteur du nombres de chemin existant passant par le sommet d'indice k
                }
            }
        }
        float calcul = getSommetByIndice(k)->getnbrchemin()/listechemins.size(); /// calcul de l'indice de centralite d'intermediarite
        getSommetByIndice(k)->setIndice_intermediarite(calcul); /// Indice intermediarite incremente a celui d'avant
    }
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
        indice_proximite(0);
        sauvegarde();
        dessiner();
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
        indice_proximite(0);
        sauvegarde();
        dessiner();
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
            indice_proximite(0);
            sauvegarde();
            dessiner();
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

void Graphe::simulation()
{
    int choix;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        delete m_sommets[i];
    }
    m_sommets.clear();
    for(int i=0 ; i<m_taille ; ++i)
    {
        delete m_aretes[i];
    }
    m_aretes.clear();
    m_orientation = 0;
    m_indiceCentraliteProximiteGlobal = 0;
    m_taille = 0;
    srand(time(NULL));
    double interactions;

    system("cls");
    std::cout << "Entrez le nombre de personnes : ";
    std::cin >> m_ordre;
    do
    {
        std::cout << "Entrez le pourcentage d'interactions : ";
        std::cin >> interactions;
    }
    while(interactions < 0 || interactions > 100);

    for(int i=0 ; i<m_ordre ; ++i)
    {
        double x = cos(i * 2 * M_PI / m_ordre);
        double y = sin(i * 2 * M_PI / m_ordre);
        m_sommets.push_back(new Sommet{i, std::to_string(i), x + 2, y + 2});
    }
    int taille_tmp = m_ordre * (m_ordre - 1) / 2 * interactions / 100;
    for(int i=0 ; i<taille_tmp ; ++i)
    {
        int random1 = 0;
        int random2 = 0;
        do
        {
            random1 = rand()%(m_ordre);
            Sleep(100);
            random2 = rand()%(m_ordre);
            Sleep(100);
        }
        while(getAretesBy2Sommets(getSommetByIndice(random1), getSommetByIndice(random2)).size() != 0 || random1 == random2);
        m_aretes.push_back(new Arete{i, getSommetByIndice(random1), getSommetByIndice(random2)});
        getSommetByIndice(random1)->ajouter_voisins(getSommetByIndice(random2));
        getSommetByIndice(random2)->ajouter_voisins(getSommetByIndice(random1));
        ++ m_taille;
    }
    dessiner();
    int entree;
    do
    {
        bool var;
        do
        {
            var = 0;
            system("cls");
            std::cout << "Entrez l'indice du sommet a contaminer : ";
            std::cin >> choix;
            if(!sommetExistant(choix))
            {
                std::cout << std::endl << "Le sommet n'existe pas.";
                Sleep(2000);
            }
            if(sommetExistant(choix))
            {
                if(getSommetByIndice(choix)->getContamine())
                {
                    std::cout << std::endl << "Le sommet a deja ete contamine.";
                    Sleep(2000);
                    var = 1;
                }
            }
        }
        while(!sommetExistant(choix) || var);


        dessiner(3);
        int nbre = 0;
        for(int i=0 ; i<m_ordre ; ++i)
        {
            if(m_sommets[i]->getContamine())
                ++nbre;
        }
        std::cout << std::endl << std::endl << nbre/m_ordre * 100 << "% de la population a ete contaminee.";
        std::cout << std::endl << "Le seuil epidemique est de " << 1 / m_ordre * 100 << "% ." << std::endl << std::endl;
        do
        {
            std::cout << "1) Contaminer une autre personne" << std::endl;
            std::cout << "2) Immuniser une personne" << std::endl;
            std::cout << "3) Quitter" << std::endl;
            std::cout << "Que voulez-vous faire ? ";
            std::cin >> entree;
        }
        while(entree != 1 && entree != 2 && entree != 3);
    }
    while(entree == 1);
    for(int i=0; i<m_ordre; ++i)
    {
        m_sommets[i]->setContamine(0);
    }
}


void Graphe::parcours(Sommet* sommet)
{
    if(sommet->getVoisins().size() == 0)
    {
        return;
    }
    for(size_t i = 0 ; i < sommet->getVoisins().size() ; ++i)
    {
        if(sommet->getVoisins()[i]->getContamine()==0)
        {
            sommet->getVoisins()[i]->setContamine(1);
            dessiner(3);
            Sleep(500);
            parcours(sommet->getVoisins()[i]);
        }

    }


}

bool Graphe::appelBFS()
{
    bool a;
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        std::vector<int> arbre_BFS=BFS(m_sommets[i]->getIndice());
        a=afficher_parcours(m_sommets[i]->getIndice(),arbre_BFS);
        if(!a)
        {
            return 0;
        }
    }
    return 1;
}

bool Graphe::afficher_parcours(int num,const std::vector<int>& arbre)
{
    std::vector<int> tout_i;
    for(size_t i=0;i<arbre.size();++i)
        {
        if((int)i!=num)
        {
            if(arbre[i]!=-1)
            {
                tout_i.push_back(i);

            }
        }
    }
    for(size_t i=0; i<tout_i.size(); ++i)
    {
        std::cout<<"tout i:"<<tout_i[i]<<std::endl;
    }
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        std::cout<<"sommets i:"<<m_sommets[i]->getIndice()<<std::endl;
    }

    if(tout_i.size()!=(m_sommets.size()-1))
    {
        return 0;
    }
    return 1;
}

std::vector<int> Graphe::BFS(int num_s0)const
{
    ///Algorithme BFS du TP2 , base du code de Mme Palasi
    /// d�claration de la file
    std::queue<Sommet*> file;
    /// pour le marquage
    std::vector<int> couleurs((int)m_sommets.size(),0);
    ///pour noter les pr�d�cesseurs : on note les num�ros des pr�d�cesseurs (on pourrait stocker des pointeurs sur ...)
    std::vector<int> preds((int)m_sommets.size(),-1);
    ///�tape initiale : on enfile et on marque le sommet initial
    file.push(m_sommets[num_s0]);
    couleurs[num_s0] = 1;

    Sommet* s;
    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        s = file.front();
        ///on d�file le prochain sommet
        couleurs[file.front()->getIndice()] = 2;
        file.pop();

        ///pour chaque successeur du sommet d�fil�
        for(auto succ:s->getVoisins())
        {
            int id = succ->getIndice();
            if(couleurs[id] == 0)                               ///s'il n'est pas marqu�
            {
                couleurs[id] = 1;                              ///on le marque
                preds[id] = s->getIndice();                        ///on note son pr�decesseur (=le sommet d�fil�)
                file.push(m_sommets[id]);                      ///on le met dans la file

            }
        }
    }
    return preds;
}

bool Graphe::combinaisons(int n, int p, int k, int *L, int *t, int r)
{
    int i, j, j1, t2[n];
    if(r<p-k)
        return 1;
    if(k==p)
    {
        Sommet* sommet1_tmp;
        Sommet* sommet2_tmp;
        int indice_tmp;
        for(i=0; i<p; i++)
        {
            indice_tmp = m_aretes[L[i] - i]->getIndice();
            sommet1_tmp = m_aretes[L[i] - i]->getExtremites().first;
            sommet2_tmp = m_aretes[L[i] - i]->getExtremites().second;
            m_aretes[L[i] - i]->getExtremites().first->retirer_voisins(m_aretes[L[i] - i]->getExtremites().second);
            m_aretes[L[i] - i]->getExtremites().second->retirer_voisins(m_aretes[L[i] - i]->getExtremites().first);
            delete getAreteByIndice(indice_tmp);
            m_aretes.erase(m_aretes.begin() + L[i] - i);
            --m_taille;
        }
        bool a = appelBFS();
        if(!a)
            return 0;
        for(i=0; i<k; ++i)
        {
            sommet1_tmp->ajouter_voisins(sommet2_tmp);
            sommet2_tmp->ajouter_voisins(sommet1_tmp);
            m_aretes.insert(m_aretes.begin() + L[i] - i, new Arete{indice_tmp, sommet1_tmp, sommet2_tmp});
            ++m_taille;
        }
        return 1;
    }
    for(i=0; i<r; i++)
    {
        L[k] = t[i];
        for(j=i+1, j1=0; j<r; j++, j1++)
        {
            t2[j1] = t[j];
        }
        bool x = combinaisons(n, p, k+1, L, t2, j1);
        if(!x)
        {
            return 0;
        }
    }
    return 1; // uniquement pour le warning
}

bool Graphe::effectue(int n, int p)
{
    int L[p], t[n], i;
    for(i=0; i<n; i++)
    {
        t[i] = i;
    }
    return combinaisons(n, p, 0, L, t, n);
}

void Graphe::intermediarite()
{
    ///Appel de la fonction calculintermediarite pour tout les couples i et j possibles
    for(size_t i=0 ; i<m_sommets.size()-1; i++)
    {
        for(size_t j=i+1; j<m_sommets.size(); j++)
        {
            calculintermediarite( i, j);
        }
    }

    for(size_t k=0; k<m_sommets.size(); k++)
    {
        float indice_non_norm = getSommetByIndice(k)->getIndice_intermediarite();
        float calcul= (2*indice_non_norm)/((m_ordre*m_ordre)+((-3)*m_ordre)+2);

        getSommetByIndice(k)->setIndice_intermediarite_normalise(calcul);

    }
    ///affichage des resultats
    system("cls");
    std::cout << "                                              Centralite d'intermediarite" << std::endl << std::endl << std::endl;
    std::cout << "             Non normalise          Normalise" << std::endl << std::endl;
    for(int i=0 ; i<m_ordre ; ++i)
    {
        std::cout << "Sommet " << m_sommets[i]->getIndice() << " :   " << m_sommets[i]->getIndice_intermediarite() << "               \t" << m_sommets[i]->getIndice_intermediarite_normalise() << std::endl;
    }
    std::cout << std::endl <<std::endl << "Tapez enter pour revenir au menu principal" << std::endl;
    while(getch() != 13)
    {

    }

}
