target=formule1,formule2,formule3,formule4,formule5
#include "author.inc"
#if defined TARGET_formule1
 #define NUM 1
#endif
#if defined TARGET_formule2
 #define NUM 2
#endif
#if defined TARGET_formule3
 #define NUM 3
#endif
#if defined TARGET_formule4
 #define NUM 4
#endif
#if defined TARGET_formule5
 #define NUM 5
#endif
#include "lang_titles.inc"
\text{x=x}

#if defined TARGET_formule1
 \text{name=slib(lang/fname fr,boy)}
 \integer{v1=randint(9..17)}
 \real{v2=randint(5..19)/100}
 \text{enonce=L'abonnement téléphonique de \name est composé d'un forfait de base de \v1 euros et d'un prix pour chaque heure de communication de \v2 euros.<br>
  Ecrire le prix à payer en euros pour \x heures de communication}
 \text{rep=\v1+\v2*\x}
#endif
#if defined TARGET_formule2
 \text{name=slib(lang/fname fr,boy)}
 \integer{v1=randint(12..18)*100}
 \real{v2=randint(2..6)}
 \text{enonce=\name est vendeur dans un grand magazin. Son salaire est composée d'une partie fixe de \v1 euros et d'une partie variable correspondant à \v2% du montant de ces ventes.<br>
  Quel est le montant de son salaire s'il a vendu pour \x  euros}
 \text{rep=\v1+\v2/100*\x}
#endif
#if defined TARGET_formule3
 \text{name=slib(lang/fname fr,boy)}
 \integer{v1=randint(12..18)*100}
 \real{v2=randint(2..15)}
 \text{enonce=Une cuve contient \v1 litres d'eau. Une fuite lui fait perdre \v2 litres par heures.<br>
  Quelle est la quantité d'eau dans la cuve au bout de x heures}
 \text{rep=\v1-\v2*\x}
#endif
#if defined TARGET_formule4
 \integer{v1=randint(8..13)*10}
 \text{enonce=Une voiture roule à la vitesse de \v1 Km/H.<br>
  Quelle distance (en kilomètres) parcourt-elle en x heures}
 \text{rep=\v1*\x}
#endif
#if defined TARGET_formule5
 \text{name=slib(lang/fname fr,boy)}
 \integer{v1=randint(18..30)*100}
 \real{v2=randint(30..50)*6}
 \text{enonce=Un parachutiste saute d'un avion à \v1 mètres d'altitude. Sa vitesse de chute est de \v2 Km/H.<br>
  Quelle est son altitude en mètre après x minutes de descente}
 \text{s=simplify(\v2*100/6)}
 \text{rep=simplify(\v1-\s*\x)}
#endif
\statement{
\enonce ?
}

\answer{Réponse}{\rep}{type=auto}
