#if defined TARGET_evolmeth1
#define TITRE Êtres vivants plus proches parents
\text{instruction=Indiquez le ou les taxons les plus apparentés à}
#endif
#if defined TARGET_evolmeth2
#define TITRE Caractères partagés par des êtres vivants
\text{instruction=Indiquez les caractères dérivés partagés par les
  êtres vivants}
#endif
#if defined TARGET_evolmeth3
#define TITRE Ancêtres communs
\text{instruction=Marquez les ancêtres communs aux êtres vivants}
#endif
#if defined TARGET_evolmeth5
#define TITRE Ancêtre commun exclusif
\text{instruction=Marquer l'ancêtre commun exclusif des êtres vivants}
#endif
#if defined TARGET_evolmeth1 || defined TARGET_evolmeth2 || defined TARGET_evolmeth3 || defined TARGET_evolmeth5
%% le premier organisme possède le premier caractère.
\matrix{Data=\choix=1?Oreillard, Indri, Tarsier, Saki, Babouin, [Homme, Chimpanzé, Gibbon, Gorille, Orang Outan]
  ,[Ongles, Pouce opposable], Abscence de rhinarium, Orbite fermée, Narines, Queue absente}
\matrix{Data=\choix=2?Lamproie,Requin,Truite,Coelacanthe,Dipneuste,Salamandre,Zèbre,Tortue,Lézard,Moineau,Crocodile
  Vertèbres,Machoires,Squelette osseux,Appendices pairs,Poumons alvéolés,[4 membres, Doigts,Cou],Amnios,Quille ventrale sous les vertèbres,Deux fenêtres temporales,Fenêtre mandibulaire,Fenêtre temporale triangulaire}
\matrix{Data=\choix=3?Lamproie, Sardine, Coelacanthe, Crapaud,[Aigle,Crocodile], [Chat sauvage, Toupaie,Oreillard],Indri, [Babouin, Homme, Gorille]
  ,Machoires,Pièce basale unique,Choanes,Amnios,Placenta,Ongles,Orbites fermées}
\matrix{Data=\choix=4?Oreillard, Toupaïe, Maki,Ouistiti, Babouin, [Gibbon, Chimpanzé, Bonobo, Orang-Outan, Homme, Gorille]
  ,Pouce opposable, Ongles, [Orbites fermées, Pas de truffe],Narines rapprochées, Queue absente}
#endif
#if defined TARGET_evolmeth4
#define TITRE Choix d'un arbre le plus parcimonieux
\text{instruction=Dans le tableau suivant, nommé matrice des caractères, on a noté que
  chaque être vivant possède le caractère sous forme ancestrale (notée 0)
  ou sous sa forme dérivée (notée 1). Vous appuyant sur cette matrice,
  cliquez sur l'arbre de parenté qui correspond.
}
\text{name_orga=Être vivant}
\text{name_car=caract.}
#endif
