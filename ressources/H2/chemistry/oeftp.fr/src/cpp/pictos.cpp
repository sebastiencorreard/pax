target = dangers significations precautions

type=classify
textarea="data explain"

#if defined TARGET_dangers
:\title{Reconnaitre les dangers indiqués par les pictogrammes de sécurité.}
\text{question=Associer le pictogramme de sécurité en chimie au danger qu'il représente.}
#endif
#if defined TARGET_precautions
:\title{Reconnaitre les précautions à prendre suivant les pictogrammes de sécurité.}
\text{question=Associer la précaution à prendre à chacun des pictogrammes de sécurité présentés.}
#endif 

#if defined TARGET_significations
:\title{Reconnaitre la signification des pictogrammes de sécurité.}
\text{question=Associer la signification de chaque pictogramme de sécurité en chimie au danger qu'il représente.}

:Nombre de (paires) d'objets à faire correspondre
\integer{tot=9}
#endif

:\author{Thierry, Tousch;Marie-joëlle,Ramage}
:\email{tousch.thierry@mailoo.org}
:\credits{}

/* Pour ajouter des mots-clés qui ne sont pas recensés dans la liste officielle */
\keywords{pictogramme,sécurité}

:Nombre de (paires) d'objets à faire correspondre 
#if defined TARGET_dangers|precautions
\integer{tot=8}
#endif
#if defined TARGET_significations
\integer{tot=9}
#endif

/* Pour modifier le nombre de pictogrammes proposés, ici tirage aléatoire sur 5 éléments de la liste */
\integer{tot=5}


:La taille verticale des cases en pixels
\integer{sizev=70}

:La taille horizontale des cases à gauche en pixels
\integer{sizel=70}

:La taille horizontale des cases à droite en pixels
\integer{sizer=400}

:Données principales
#if defined TARGET_dangers
\matrix{data=<img src="\imagedir/comburant.jpg">, Peut aggraver un incendie.
<img src="\imagedir/corrosif.jpg">, Peut ronger la peau.
<img src="\imagedir/environnement.jpg">, Provoque des effets néfastes sur la couche d'ozone.
<img src="\imagedir/exclamation.jpg">, Peut entraîner des irritations.
<img src="\imagedir/explosif.jpg">, Peut exploser sous l'effet d'un choc.
<img src="\imagedir/inflammable.jpg">, S'enflamme au contact de l'eau.
<img src="\imagedir/silhouete.jpg">, Peut provoquer des mutations génétiques.
<img src="\imagedir/toxique.jpg">, Empoisonne rapidement même à faible dose.}
#endif

#if defined TARGET_precautions
\matrix{data=<img src="\imagedir/comburant.jpg">, Tenir à l'écart des combustibles.
<img src="\imagedir/corrosif.jpg">, Porter des lunettes.
<img src="\imagedir/environnement.jpg">, Éviter le rejet dans l'environnement.
<img src="\imagedir/explosif.jpg">, Éviter les chocs et les frictions.
<img src="\imagedir/gaz.jpg">, Ne pas percer.
<img src="\imagedir/inflammable.jpg">, Éviter tout contact avec les sources d'allumage.
<img src="\imagedir/silhouete.jpg">, Utiliser le matériel adéquat pour toute manipulation.
<img src="\imagedir/toxique.jpg">, Proscrire l'ingestion et l'inhalation.}
#endif

#if defined TARGET_significations
\matrix{data=<img src="\imagedir/comburant.jpg">, Comburant
<img src="\imagedir/corrosif.jpg">, Corrosif
<img src="\imagedir/environnement.jpg">, Dangereux pour l'environnement
<img src="\imagedir/exclamation.jpg">, Nocif&#44; irritant
<img src="\imagedir/explosif.jpg">, Explosif
<img src="\imagedir/gaz.jpg">, Gaz sous pression
<img src="\imagedir/inflammable.jpg">, Inflammable
<img src="\imagedir/silhouete.jpg">, Cancérogène&#44; Tératogène
<img src="\imagedir/toxique.jpg">, Toxique}
#endif

:Mise en aléatoire par des accolades emboitables
\text{accolade=item(1,1 oui, 2 non)}

\text{accolade=wims(word 1 of \accolade)}
\integer{datacnt=rows(\data)}
\integer{tot=\tot>\datacnt?\datacnt}

\text{shuf=item(1..\tot,shuffle(\datacnt))}
\text{data=row(\shuf,\data)}
\text{data=\accolade=1? wims(embraced randitem \data)}
\text{datal=column(1,\data)}
\text{datar=column(2,\data)}
\text{size=\sizev[]x\sizel[]x\sizer}
\text{explain=\accolade=1? wims(embraced randitem \explain)}

::Vous n'avez pas besoin de modifier ceci en général.
La commande pour afficher le tableau de correspondance,
c'est \embed{reply 1,\size}
\statement{
<div class="wims_question">\question
<div class="wimscenter">
\embed{reply 1,\size}
</div></div>}

:%%%%%%%%%%%%% Rien à modifier ci-après. %%%%%%%%%%%%%%%%%5
\answer{La réponse}{\datal;\datar}{type=correspond}{option=split}
