#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
} Noeud;

Noeud* cree(int _valeur) {
    Noeud *n = (Noeud*)malloc(sizeof(Noeud));
    if (n != NULL) {
        n->valeur = _valeur;
        n->suivant = NULL;
    }
    return n;
}

void affiche(Noeud *debut) {
    Noeud *tmp = debut;
    printf("Liste : ");
    while (tmp != NULL) {
        printf("%d -> ", tmp->valeur);
        tmp = tmp->suivant;
    }
    printf("NULL\n");
}

Noeud* ajouterD(Noeud *debut, int _valeur) {
    Noeud *n = cree(_valeur);
    if (n != NULL) {
        n->suivant = debut;
        debut = n;
    }
    return debut;
}

Noeud* ajouterF(Noeud *debut, int _valeur) {
    Noeud *n = cree(_valeur);
    if (n == NULL) return debut;
    if (debut == NULL) return n;
    Noeud *tmp = debut;
    while (tmp->suivant != NULL) {
        tmp = tmp->suivant;
    }
    tmp->suivant = n;
    return debut;
}

int taille(Noeud *debut) {
    int count = 0;
    while (debut != NULL) {
        count++;
        debut = debut->suivant;
    }
    return count;
}

Noeud* insertion(Noeud *debut, int pos, int _valeur) {
    if (pos < 1 || pos > taille(debut) + 1) {
        printf("Position invalide\n");
        return debut;
    }
    if (pos == 1) return ajouterD(debut, _valeur);
    Noeud *n = cree(_valeur);
    if (n == NULL) return debut;
    Noeud *tmp = debut;
    for (int i = 1; i < pos - 1; i++) {
        tmp = tmp->suivant;
    }
    n->suivant = tmp->suivant;
    tmp->suivant = n;
    return debut;
}

void rechercher(Noeud *debut, int _valeur) {
    int pos = 1;
    while (debut != NULL) {
        if (debut->valeur == _valeur) {
            printf("Valeur trouvee a la position %d\n", pos);
            return;
        }
        debut = debut->suivant;
        pos++;
    }
    printf("Valeur non trouvee\n");
}

Noeud* suppressionD(Noeud *debut) {
    if (debut == NULL) return NULL;
    Noeud *tmp = debut;
    debut = debut->suivant;
    free(tmp);
    return debut;
}

Noeud* suppressionF(Noeud *debut) {
    if (debut == NULL || debut->suivant == NULL) {
        free(debut);
        return NULL;
    }
    Noeud *tmp = debut;
    while (tmp->suivant->suivant != NULL) {
        tmp = tmp->suivant;
    }
    free(tmp->suivant);
    tmp->suivant = NULL;
    return debut;
}

Noeud* suppressionP(Noeud *debut, int pos) {
    if (pos < 1 || pos > taille(debut)) {
        printf("Position invalide\n");
        return debut;
    }
    if (pos == 1) return suppressionD(debut);
    Noeud *tmp = debut;
    for (int i = 1; i < pos - 1; i++) {
        tmp = tmp->suivant;
    }
    Noeud *supp = tmp->suivant;
    tmp->suivant = supp->suivant;
    free(supp);
    return debut;
}

Noeud* modifierD(Noeud *debut, int _valeur) {
    if (debut != NULL) {
        debut->valeur = _valeur;
    }
    return debut;
}

Noeud* modifierF(Noeud *debut, int _valeur) {
    if (debut == NULL) return debut;
    Noeud *tmp = debut;
    while (tmp->suivant != NULL) {
        tmp = tmp->suivant;
    }
    tmp->valeur = _valeur;
    return debut;
}

Noeud* modifierP(Noeud *debut, int pos, int _valeur) {
    if (pos < 1 || pos > taille(debut)) {
        printf("Position invalide\n");
        return debut;
    }
    Noeud *tmp = debut;
    for (int i = 1; i < pos; i++) {
        tmp = tmp->suivant;
    }
    tmp->valeur = _valeur;
    return debut;
}

int main() {
    Noeud *liste = NULL;

    liste = ajouterF(liste, 10);
    liste = ajouterF(liste, 20);
    liste = ajouterF(liste, 30);
    affiche(liste);

    liste = ajouterD(liste, 5);
    affiche(liste);

    liste = insertion(liste, 3, 15);
    affiche(liste);

    rechercher(liste, 20);
    rechercher(liste, 100);

    liste = modifierD(liste, 1);
    liste = modifierF(liste, 99);
    liste = modifierP(liste, 3, 42);
    affiche(liste);

    liste = suppressionD(liste);
    liste = suppressionF(liste);
    liste = suppressionP(liste, 2);
    affiche(liste);

    printf("Taille de la liste : %d\n", taille(liste));

    return 0;
}
