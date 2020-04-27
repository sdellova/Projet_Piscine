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

std::string Graphe::ponderation()
{
    int choix;
    std::string nomFichier;
    std::cout << "Le graphe est-il pondere ?" << std::endl;
    std::cout << "Ecrivez 1 pour oui, 2 pour non : ";
    std::cin >> choix;
    if(choix)
    {
        std::cout << "Ecrivez le nom du fichier de ponderation : ";
        std::cin >> nomFichier;
        return nomFichier;
    }
    else
        return "0";
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
