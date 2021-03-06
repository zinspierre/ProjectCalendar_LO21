#ifndef AGENDA_H
#define AGENDA_H
#include "programmationpartietache.h"
#include "programmationrdv.h"
#include "jourscene.h"
#include "observable.h"
#include "xmlexporter.h"


/**
 * @class ProgComp
 * @brief Comparateur pour le set de l'agenda contenant les programmations
 */
class ProgComp
{
public:

    /**
     * @brief operator () : compare les dates et heure de début des programmations a et b
     * @param a première programmation
     * @param b seconde programmation
     * @return a < b
     */
    bool operator()(Programmation* a, Programmation* b)
    {
        return QDateTime(a->getDate(), a->getDebut()) < QDateTime(b->getDate(), b->getDebut());
    }
};




/**
 * @class Agenda
 * @brief Gère l'ensemble des programmations
 */
class Agenda : public Observable,  public XmlExporter
{
private:
    std::set<Programmation*, ProgComp> set_prog;
    std::vector<JourScene*> scenes;
    Agenda(){}
    Agenda(const Agenda& a);
    Agenda& operator=(const Agenda& a);
    ~Agenda();
    static Agenda* instance;

public:
    static Agenda& getInstance(){
        if(!instance) instance = new Agenda();
        return *instance;
    }
    static void libererInstance(){delete instance;}


    /**
     * @brief ajouterProgrammation : ajout d'une programmation dans l'agenda
     * @param type type de la programmation
     * @param date date de début
     * @param titre
     * @param desc description
     * @param debut
     * @param duree
     * @param lieu lieu : si rendez-vous
     * @param pers participants : si rendez-vous
     * @param tache tache correspondant à la programmation : si programmation de TacheUnitaire ou partie de Tache
     * @param projet projet correspondant à la programmation: si programmation de TacheUnitaire ou de partie de tache
     * @param num_partie numéro de la prtie : si programmation de partie de tache
     * @param nom_partie nom de la partie : si programmation de partie de tache
     */
    void ajouterProgrammation(int type, const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                              const Duree& duree,  const QString& lieu="", const QString& pers="",
                              TacheUnitaire* tache = 0, Projet* projet = 0, int num_partie=0,
                              const QString nom_partie="");


    /**
     * @brief ajouterProgrammationPlsJour : ajout d'une programmation sur plusieurs jours dans l'agenda
     * @param date date de début
     * @param titre
     * @param desc description
     * @param debut horaire de début
     * @param date_fin date de fin
     * @param fin horaire de fin
     */
    void ajouterProgrammationPlsJour(const QDate& date, const QString titre, const QString& desc, const QTime& debut,
                                     const QDate& date_fin, const QTime& fin);
    /**
     * @brief ajouterProgrammationPartieTache : ajout de programmations pour des parties de tâche
     * @param vec_date vecteur contenant les date de début
     * @param vec_titre vecteur contenant les titre des parties
     * @param vec_debut vecteur contenant les horaire de début des parties
     * @param vec_duree vecteur contenant les durées des parties
     * @param t tache unitaire correspondante
     * @param projet
     */
    void ajouterProgrammationPartieTache(std::vector<QDate>& vec_date, std::vector<QString>& vec_titre,
                                                 std::vector<QTime>& vec_debut, std::vector<Duree>& vec_duree,
                                         TacheUnitaire *t, Projet *projet);
    /**
     * @brief enleverProgrammation : suppression d'une programmation de l'agenda
     * @param prog programmation
     */
    void enleverProgrammation(Programmation* prog);

    /**
     * @brief verifProgrammation : vérification des contraintes d'une programmation
     * @param p programmation
     */
    void verifProgrammation(Programmation* p);

    /**
     * @brief ajouterScene : ajout d'une scene dans l'agenda
     * @param jour
     * @param date
     * @param h hauteur de la scene
     * @param w largeur de la scene
     * @param parent
     */
    void ajouterScene(const QString &jour, const QDate &date, qreal h, qreal w, QObject* parent = 0);


    JourScene& getScene(int i) const {return *scenes.at(i);}
    /**
     * @brief removeAllScenes : supprimer toutes les scenes
     */
    void removeAllScenes(){scenes.clear();}
    const std::set<Programmation*, ProgComp> getProgrammation() const {return set_prog;}

    /**
     * @brief notifier : va notifier tous ses observateurs
     * @param s1
     * @param s2
     */
    virtual void notifier(const QString& s1="", const QString& s2="") const;

    /**
     * @brief save : sauvegarde des programmations de l'agenda
     * @param f
     * @param contraintes
     */
    virtual void save(const QString& f, bool contraintes=false) const;

    /**
     * @brief load : chargement des programmations dans l'agenda
     * @param f
     */
    virtual void load(const QString& f);



    /**
     * @class Iterator
     * @brief Iterator sur les programmations de l'agenda
     */
    class Iterator : public std::set<Programmation*, ProgComp>::iterator
    {
    public:
        Iterator(std::set<Programmation*, ProgComp>::iterator deb) : std::set<Programmation*, ProgComp>::iterator(deb){}
        Programmation& operator*() const {return *std::set<Programmation*, ProgComp>::iterator::operator *();}
    };
    Iterator begin(){return Iterator(set_prog.begin());}
    Iterator end(){return Iterator(set_prog.end());}

    /**
     * @class ConstIterator
     * @brief ConstIterator sur les programmations de l'agenda
     */
    class ConstIterator : public std::set<Programmation*, ProgComp>::const_iterator
    {
    public:
        ConstIterator(std::set<Programmation*, ProgComp>::const_iterator deb) :
            std::set<Programmation*, ProgComp>::const_iterator(deb){}
        const Programmation& operator*() const {return *std::set<Programmation*, ProgComp>::const_iterator::operator *();}
    };

    ConstIterator begin() const {return ConstIterator(set_prog.begin());}
    ConstIterator end() const {return ConstIterator(set_prog.end());}
};

#endif // AGENDA_H
