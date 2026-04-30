target=agrdred2,agrdred3,agrdred4,agrdred5
#define TITRE Agrandissement et réduction
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

\text{Liste=un agrandissement,une réduction}

#if defined TARGET_agrdred2 
 \title{TITRE 2}
 \real{coef=randint(101..10000)/100}
 \text{enonce=multiplie}
 \text{good=item(1,\Liste)}
#endif

#if defined TARGET_agrdred3 
 \title{TITRE 3}
 \real{coef=randint(1..99)/100}
 \text{enonce=multiplie}
 \text{good=item(2,\Liste)}
#endif

#if defined TARGET_agrdred4 
 \title{TITRE 4}
 \real{coef=randint(101..10000)/100}
 \text{enonce=divise}
 \text{good=item(2,\Liste)}
#endif

#if defined TARGET_agrdred5 
 \title{TITRE 5}
 \real{coef=randint(1..99)/100}
 \text{enonce=divise}
 \text{good=item(1,\Liste)}
#endif

\statement{
On \enonce toutes les longueurs d'une figure par \(\coef).
Est-ce un agrandissement ou une réduction ?
<p>
<b>Votre réponse :</b></p>
  c'est \embed{c1}.
}

\choice{réponse}{\good}{\Liste}
