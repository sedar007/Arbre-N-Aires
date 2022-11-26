#include <cstddef>
#include <iostream>
using namespace std;

struct noeudMult{
    float val; 
    int nb_fils;
    noeudMult *fils[100]; //Ensemble des fils du noeud
};

struct File{
    noeudMult *noeud;
    File *next;
};

void enqueue(File **file, noeudMult *noeud){
    //Fonction qui permet d'enfiler des noeuds
    File *ptr = *file;
    File *nv = new File;

    nv->noeud = noeud;
    nv->next = nullptr;

    if (*file == nullptr) *file = nv; //Verifie si la file est vide
    
    else{
        while(ptr->next != nullptr) ptr = ptr->next;
        ptr->next = nv;
    }
}

noeudMult *dequeue(File **file){
    //Permet de defiler des noeuds
    if (*file != nullptr){
        noeudMult *noeud = (*file)->noeud;
        (*file) = (*file)->next;
        return noeud;
    }
    return nullptr;   // Retourne nullptr si la file est vide
}


void createArbreNAire(noeudMult **noeud, File *file){
    //creation de mon arbre de maniere en largeur
    if( *noeud != nullptr){
        
        cout<<"Saisir la valeur du noeud: ";
        cin>> (*noeud)->val;

        cout<<"Saisir le nombre de fils du noeud: ";
        cin>> (*noeud)->nb_fils;
        
        for(int i=0; i<(*noeud)->nb_fils; i++){
            //Enfile les fils du noeud
            (*noeud)->fils[i] = new noeudMult;
            enqueue(&file,(*noeud)->fils[i]);    
        }

        //Defile les noeuds dans la file
        noeudMult *p = dequeue(&file);
        createArbreNAire(&p, file);// Creation des valeurs des noeuds de la file   
    }
}

void createArbreNAireProfondeur(noeudMult **noeud){
    //creation de mon arbre de maniere en profondeur
    if( *noeud != nullptr){
        
        cout<<"Saisir la valeur du noeud: ";
        cin>> (*noeud)->val;

        cout<<"Saisir le nombre de fils du noeud: ";
        cin>> (*noeud)->nb_fils;
        
        for(int i=0; i<(*noeud)->nb_fils; i++){
            (*noeud)->fils[i] = new noeudMult;
            createArbreNAireProfondeur(&(*noeud)->fils[i]);    
        }
 
    }
}
void afficherEnLargeur(noeudMult *noeud, File *file){
    //Affiche les valeurs en largeur
    if( noeud != nullptr){        
        cout<<noeud->val<< " "; //
         
        //Enfile les fils du noeud
        for(int i=0; i<noeud->nb_fils; i++) enqueue(&file,noeud->fils[i]);

        //Defile les noeuds de la file
        noeudMult *p = dequeue(&file);
        afficherEnLargeur(p, file);// Affiche les valeurs des noeuds de la file  
    }

}


void afficherEnProfondeur(noeudMult *noeud){
    //Affiche les valeurs en profondeur
    if (noeud != nullptr){
        cout<<noeud->val<<" ";

        //Affiche les valeurs des fils jusqu'a arrive ou il y a plus de fils 
        for(int i=0; i< noeud->nb_fils; i++) afficherEnProfondeur(noeud->fils[i]);        
    }
}

void afficherNiveau(noeudMult *noeud, int prof){
    //Affiche les valeurs d'un niveau passe en parametre
    if (noeud != nullptr ){
        if(prof == 0) cout<<noeud->val<<" "; // Si la valeur de prof est egale a 0, on affiche les valeurs
        if (prof > 0){
            for(int i=0; i< noeud->nb_fils; i++) afficherNiveau(noeud->fils[i],prof-1);
        }
    }
}


void rechercheHauteur(noeudMult *noeud, int *max, int cpt){
    //Recherche la hauteur de l'arbre
    for(int i=0; i< noeud->nb_fils; i++) rechercheHauteur(noeud->fils[i],max, cpt+1);

    if(cpt >= *max) *max = cpt;   
}

void afficherEnLargeur2(noeudMult *noeud){
    //Permet d'afficher les valeurs en largeurs
    int max = 0;
    cout<<noeud->val<<" ";
    rechercheHauteur(noeud, &max, 0);
    for(int i=0; i< max; i++) afficherNiveau(noeud,  i+1);
}


int main(){
    noeudMult *arbre = new noeudMult;
    File *file = nullptr;
    int niveau = 0;
    int prof;

    // cout<<"Creation d'un arbre N-Aire en Largeur"<<endl;
    // createArbreNAire(&arbre, file);

    cout<<"Creation d'un arbre N-Aire en profondeur"<<endl;
    createArbreNAireProfondeur(&arbre);

    cout<<"Affichage en largeur"<<endl;
    afficherEnLargeur(arbre, file);cout<<endl;

    cout<<"Affichage en profondeur"<<endl;
    afficherEnProfondeur( arbre);cout<<endl;

    cout<<"Entrer les niveaux a afficher";
    cin>>prof;
    afficherNiveau(arbre, prof);cout<<endl;
    
    rechercheHauteur(arbre, &niveau, 0);
    cout<<"La hauteur de l'arbre est: "<<niveau<<endl;

    cout<<"Affichage en profondeur 2"<<endl;
    afficherEnLargeur2(arbre);
    

}

