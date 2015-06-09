#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDirModel>
#include <QStandardItemModel>

#include "agenda.h"
#include "dialogprecedence.h"

namespace Ui {
class MainWindow;
}

/**
 * @class MainWindow
 * @brief fenêtre principale
 */
class MainWindow : public QMainWindow, public Observateur
{
    Q_OBJECT

private:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MainWindow& operator=(const MainWindow& m);
    MainWindow(const MainWindow& m);

    Ui::MainWindow *ui;
    static MainWindow* instance;

    ProjetManager* pm;
    PrecedenceManager* pre;
    Agenda* ag;


public:
    static MainWindow& getInstance(QWidget* parent = 0);
    static void libererInstance();


    virtual void update(const QString& s1="", const QString& s2="");

    /**
     * @brief supprimerProgrammation : suppression de programmation
     * @param v QGraphicsView
     */
    void supprimerProgrammation(QGraphicsView& v);

    /**
     * @brief getInformation : affiche les informations des programmations
     * @param v QGraphicsView
     */
    void getInformation(QGraphicsView& v);

    /**
     * @brief initCalendar : initialise le calendrier
     * @param d date
     */
    void initCalendar(QDate d);

    /**
      * @brief closeEvent : ferme l'application et libère l'instance de MainWindow qui
      * va elle libérer les instance de Agenda, ProjetManager et PrecedenceManager
      * @param event
      */
     void closeEvent(QCloseEvent* event){
         libererInstance();
     }

public slots:
    void adaptForm(bool etat);
    void adaptForm2(bool etat);
    void expand();

    void sauvegarder();
    void charger();

    void ajouter();
    void supprimerItem();
    void afficherInfo(QModelIndex idx);

    void ajouterPrecedence();
    void supprimerPrecedence();

    void programmerTache();
    void ajouterEvt();
    void changeDate();


    void lundi();
    void mardi();
    void mercredi();
    void jeudi();
    void vendredi();
    void samedi();
    void dimanche();

    void exporterSemaine();






};




#endif // MAINWINDOW_H
