#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogprogevt.h"
#include "precedenceitem.h"
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

MainWindow* MainWindow::instance = 0;

MainWindow& MainWindow::getInstance(QWidget* parent)
{
    if(instance) return *instance;
    else{
        instance = new MainWindow(parent);
        return *instance;
    }
}

void MainWindow::libererInstance()
{
    delete instance;
    instance = 0;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    pm = &ProjetManager::getInstance();





    ui->treeView->setModel(&pm->getModel());
    ag = &Agenda::getInstance();
    pre = &PrecedenceManager::getInstance();
    pre->ajouterObservateur(this);
    ui->treeView->setAnimated(true);

    QDate d = Agenda::getInstance().getAuj();
    for(int i = -(d.dayOfWeek()-1); i < 7-(d.dayOfWeek()-1); ++i)
    {
        QDate tmp = d.addDays(i);
        Agenda::getInstance().ajouterScene(tmp.toString("dddd"),tmp, ui->v_lundi->height(), ui->v_lundi->width(), this);
    }
    /*Agenda::getInstance().ajouterScene("mardi",d, ui->v_mardi->height(), ui->v_mardi->width(), this);
    Agenda::getInstance().ajouterScene("mercredi",d, ui->v_mercredi->height(), ui->v_mercredi->width(), this);
    Agenda::getInstance().ajouterScene("jeudi",d, ui->v_jeudi->height(), ui->v_jeudi->width(), this);
    Agenda::getInstance().ajouterScene("vendredi",d, ui->v_vendredi->height(), ui->v_vendredi->width(), this);
    Agenda::getInstance().ajouterScene("samedi",d, ui->v_samedi->height(), ui->v_samedi->width(), this);
    Agenda::getInstance().ajouterScene("dimanche",d, ui->v_dimanche->height(), ui->v_dimanche->width(), this);*/

    ui->v_lundi->setScene(&Agenda::getInstance().getScene(0));
    ui->v_mardi->setScene(&Agenda::getInstance().getScene(1));
    ui->v_mercredi->setScene(&Agenda::getInstance().getScene(2));
    ui->v_jeudi->setScene(&Agenda::getInstance().getScene(3));
    ui->v_vendredi->setScene(&Agenda::getInstance().getScene(4));
    ui->v_samedi->setScene(&Agenda::getInstance().getScene(5));
    ui->v_dimanche->setScene(&Agenda::getInstance().getScene(6));




    Agenda::getInstance().ajouterProgrammation(0,QDate(2015,6,7),"ol","lyon", QTime(8,0), Duree(2,3));
    Agenda::getInstance().ajouterProgrammation(0,QDate(2015,6,6),"jdtyj","lyon", QTime(11,2), Duree(0,35));
    Agenda::getInstance().ajouterProgrammation(0,QDate(2015,6,6),"fdhg","lyon", QTime(17,30), Duree(0,30));
    Agenda::getInstance().ajouterProgrammation(0,QDate(2015,6,6),"rsth","lyon", QTime(20,30), Duree(1,0));



/*
    Agenda::getInstance().getScene(0).ajouterProgrammation("ol",QTime(9,30),Duree(5,3));
    Agenda::getInstance().getScene(0).ajouterProgrammation("ol",QTime(10,30),Duree(1,0));
    Agenda::getInstance().getScene(0).ajouterProgrammation("ly",QTime(17,30),Duree(0,30));
    Agenda::getInstance().getScene(0).ajouterProgrammation("ppp",QTime(9,30),Duree(0,30));


//    pm->update();


    /*
    QStand  ardItem *parentItem = model.invisibleRootItem();

    for (int i = 0; i < 4; ++i) {
        Projet *object = new Projet("oko",QDate(2000,5,2), QDate(2001,2,3));
        QVariant variant;
        variant.setValue(object);
        QStandardItem *item = new QStandardItem;
        item->setData(variant.toString());
        parentItem->appendRow(item);
        QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
        QStandardItem *item = new TacheUnitaire("ol","lyon",QDate(2000,2,2), QDate(2003,3,3),Duree(3,3));
        item->setText("hfghjol");
        parentItem->appendRow(item);
        parentItem = item;
    }
    ui->treeView->setModel(&model);
*/
    connect(ui->tacheunitaire, SIGNAL(toggled(bool)), this, SLOT(adaptForm(bool)));
    connect(ui->tachecomposite, SIGNAL(toggled(bool)), this, SLOT(adaptForm2(bool)));
    connect(ui->projet, SIGNAL(toggled(bool)), this, SLOT(adaptForm2(bool)));

    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
    connect(ui->precedence, SIGNAL(clicked()), this, SLOT(ajouterPrecedence()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(sauvegarder()));
    connect(ui->load, SIGNAL(clicked()), this, SLOT(charger()));
    connect(ui->expand, SIGNAL(clicked()), this, SLOT(expand()));
    connect(ui->supprimer, SIGNAL(clicked()), this, SLOT(supprimerItem()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(afficherInfo(QModelIndex)));
    connect(ui->supprimer_precedence, SIGNAL(clicked()), this, SLOT(supprimer_precedence()));

    connect(ui->ajouter_evt, SIGNAL(clicked()), this, SLOT(ajouterEvt()));

    ui->informations->setChecked(true);
    connect(ui->v_lundi->scene(), SIGNAL(selectionChanged()), this, SLOT(lundi()));
    connect(ui->v_mardi->scene(), SIGNAL(selectionChanged()), this, SLOT(mardi()));
    connect(ui->v_mercredi->scene(), SIGNAL(selectionChanged()), this, SLOT(mercredi()));
    connect(ui->v_jeudi->scene(), SIGNAL(selectionChanged()), this, SLOT(jeudi()));
    connect(ui->v_vendredi->scene(), SIGNAL(selectionChanged()), this, SLOT(vendredi()));
    connect(ui->v_samedi->scene(), SIGNAL(selectionChanged()), this, SLOT(samedi()));
    connect(ui->v_dimanche->scene(), SIGNAL(selectionChanged()), this, SLOT(dimanche()));
}


void MainWindow::lundi()
{
    if(ui->informations->isChecked())
        getInformation(*ui->v_lundi);
    else
        supprimerProgrammation(*ui->v_lundi);
}

void MainWindow::mardi()
{
    if(ui->informations->isChecked())
        getInformation(*ui->v_mardi);
    else
        supprimerProgrammation(*ui->v_mardi);
}

void MainWindow::mercredi()
{
    if(ui->informations->isChecked())
        getInformation(*ui->v_mercredi);
    else
        supprimerProgrammation(*ui->v_mercredi);
}

void MainWindow::jeudi()
{
    if(ui->informations->isChecked())
        getInformation(*ui->v_jeudi);
    else
        supprimerProgrammation(*ui->v_jeudi);
}

void MainWindow::vendredi()
{
    if(ui->informations->isChecked())
        getInformation(*ui->v_vendredi);
    else
        supprimerProgrammation(*ui->v_vendredi);
}

void MainWindow::samedi()
{
    if(ui->informations->isChecked())
        getInformation(*ui->v_samedi);
    else
        supprimerProgrammation(*ui->v_samedi);
}

void MainWindow::dimanche()
{
    if(ui->informations->isChecked())
        getInformation(*ui->v_samedi);
    else
        supprimerProgrammation(*ui->v_dimanche);
}


void MainWindow::supprimerProgrammation(QGraphicsView& v)
{
    if(v.scene()->selectedItems().size() >0)
    {
        for(QList<QGraphicsItem*>::iterator it =v.scene()->selectedItems().begin() ;
            it != v.scene()->selectedItems().end() ; ++it)
        {
            Programmation* p = dynamic_cast<ProgrammationItem*>(*it)->getProgrammation();
            Agenda::getInstance().enleverProgrammation(p);
        }
        Agenda::getInstance().notifier();
    }
}

void MainWindow::getInformation(QGraphicsView& v)
{
    if(v.scene()->selectedItems().size() >0)
    {
        for(QList<QGraphicsItem*>::iterator it =v.scene()->selectedItems().begin() ; it != v.scene()->selectedItems().end() ; ++it)
        {
            Programmation* p = dynamic_cast<ProgrammationItem*>(*it)->getProgrammation();
            QMessageBox* mess = new QMessageBox(this);
            mess->setTextFormat(Qt::RichText);
            mess->setText(p->toString());
            mess->exec();
            delete mess;
        }
        v.scene()->clearSelection();
    }
}




void MainWindow::ajouterPrecedence()
{
    DialogPrecedence* d = &DialogPrecedence::getInstance();
    d->show();
}

void MainWindow::ajouterEvt()
{
    DialogProgEvt* d = &DialogProgEvt::getInstance();
    d->show();
}
void MainWindow::expand()
{
    ui->treeView->expandAll();
}

void MainWindow::supprimer_precedence()
{
    PrecedenceItem* element = dynamic_cast<PrecedenceItem*>(ui->precedence_list->currentItem());
    pre->retirerPrecedence(*element->getPrecedence());
    delete element->getPrecedence();
    ui->precedence_list->removeItemWidget(ui->precedence_list->currentItem());
}


void MainWindow::afficherInfo(QModelIndex idx)
{

    ui->info->setHtml(pm->getInfo(idx));

}

void MainWindow::supprimerItem()
{
    QModelIndexList sel = ui->treeView->selectionModel()->selectedRows();
    for(int i = 0; i < sel.size(); ++i)
        pm->supprimerItem(sel[i]);


    std::cout << "=========================================" << std::endl;
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        std::cout << "\n" << (*it).getTitre().toStdString() << std::endl;
        for(Projet::Iterator i = (*it).begin(); i != (*it).end(); ++i)
        {
            std::cout <<"---" << (*i).getTitre().toStdString() << std::endl;
        }
    }
    std::cout << "=========================================" << std::endl;
}


void MainWindow::adaptForm(bool etat)
{
    if(etat == true)
    {
        ui->isPreemptive->show();
        ui->duree->show();
        ui->label_duree->show();
    }
    else
    {
        ui->duree->hide();
        ui->label_duree->hide();
        ui->isPreemptive->hide();
    }
}
void MainWindow::adaptForm2(bool etat)
{
    if(etat == false)
    {
        ui->isPreemptive->show();
        ui->duree->show();
        ui->label_duree->show();
    }
    else
    {
        ui->duree->hide();
        ui->label_duree->hide();
        ui->isPreemptive->hide();
    }
}



void MainWindow::ajouter()
{
    QModelIndexList sel = ui->treeView->selectionModel()->selectedRows();
    QModelIndex idx, idx_parent;
    if(sel.size() == 1)
    {
        idx = sel.at(0);
        idx_parent = idx;
        while(idx_parent.parent().data().toString() != "") idx_parent = idx_parent.parent();
    }
    if(ui->projet->isChecked() == true)
    {
        try
        {
            pm->verification(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date());
            pm->ajoutItemModel(ui->titre->text(), pm->getModel().invisibleRootItem()->index());
            pm->ajouterProjet(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date());
        }
        catch(CalendarException e)
        {
            QMessageBox::critical(this, "Erreur", e.getInfo());
        }

    }
    else if (sel.size() == 1 && (ui->tacheunitaire->isChecked() == true || ui->tachecomposite->isChecked() == true))
    {
        Projet* p;
        bool ajout_a_projet;
        if(idx.parent().data().toString() == "")
        {
            p = pm->getProjet(idx.data().toString());
            ajout_a_projet = true;
        }
        else
        {
            p = pm->getProjet(idx_parent.data().toString());
            ajout_a_projet = false;
        }

        if(p && (ajout_a_projet || p->getTache(idx.data().toString())->isComposite()))
        {
            try
            {
                p->verification(ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date(),
                                idx.data().toString());
                pm->ajoutItemModel(ui->titre->text(), idx);
                if(ui->tacheunitaire->isChecked())
                {
                    p->ajouterTache(QChar('U'), ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date(),
                                    Duree(ui->duree->time().hour(), ui->duree->time().minute()), ui->isPreemptive->isChecked());
                }
                else
                {
                    p->ajouterTache(QChar('C'), ui->titre->text(), ui->descr->toPlainText(), ui->dispo->date(), ui->eche->date(),
                                    Duree(ui->duree->time().hour(), ui->duree->time().minute()), ui->isPreemptive->isChecked());
                }
            }
            catch(CalendarException e)
            {
                QMessageBox::critical(this, "Erreur", e.getInfo());
            }
        }
    }
}


void MainWindow::sauvegarder()
{
    pm->save("projets.xml");
    pm->saveModel("model.xml");
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        (*it).save((*it).getTitre() + QString(".xml"));
    }

}

void MainWindow::charger()
{
   // QString chemin = QFileDialog::getOpenFileName();
    //supprimerAllItem();
    pm->load("projets.xml");
    pm->loadModel("model.xml");
    for(ProjetManager::Iterator it = pm->begin(); it != pm->end(); ++it)
    {
        (*it).load((*it).getTitre() + QString(".xml"));
    }

}

void MainWindow::update(const QString& s1, const QString& s2)
{
    ui->precedence_list->clear();
    for(PrecedenceManager::Iterator it = pre->begin(); it != pre->end(); ++it)
    {
        ui->precedence_list->addItem(new PrecedenceItem((*it).toString(),&(*it)));
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
