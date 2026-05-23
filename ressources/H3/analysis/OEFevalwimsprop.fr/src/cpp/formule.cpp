target=formule1 formule2 formule3 formule4 formule5
\keywords{conversion}
#define TITRE Formule
#include "author.inc"
#if defined TARGET_formule1
# define NUM 1
#endif
#if defined TARGET_formule2
# define NUM 2
#endif
#if defined TARGET_formule3
# define NUM 3
#endif
#if defined TARGET_formule4
# define NUM 4
#endif
#if defined TARGET_formule5
# define NUM 5
#endif
#include "lang_titles.inc"

#if defined TARGET_formule1
\text{don=randrow(kilomètres,heures,km/h,randint(2..5),randint(4..11)*10
 mètres,secondes,m/s,randint(20..80),randint(2..9)
 mètres,minutes,m/min,randint(20..40),randint(50..200))}
\text{t=item(4,\don)}
\text{vunit=item(3,\don)}
\text{unit=item(1,\don)}
\text{tunit=item(2,\don)}
\integer{v=item(5,\don)}
\real{rep=\v*\t}
\text{enonce=En se déplaçant à \v \vunit, quelle distance parcourt-on en \t \tunit &#63;}
#endif
#if defined TARGET_formule3
\text{don=randrow(kilomètres,heures,km/h,randint(2..5),randint(4..11)*10
  mètres,secondes,m/s,randint(20..80),randint(2..9)
  mètres,minutes,m/min,randint(20..40),randint(50..200))}
\text{t=item(4,\don)}
\text{vunit=item(3,\don)}
\text{dunit=item(1,\don)}
\text{unit=item(2,\don)}
\integer{v=item(5,\don)}
\integer{d=\v*\t}
\text{enonce=Combien de temps faut-il pour parcourir \d \dunit à la vitesse de \v \vunit &#63;}
\real{rep=\t}
#endif
#if defined TARGET_formule4
\integer{t=3*randint(3..19)}
\integer{v=9*randint(4..11)}
\text{unit=secondes}
\real{d=\v*\t/36*10}
\text{rep=\t}
\text{enonce=Combien de temps faut-il pour parcourir \d mètres à la vitesse de \v km/h &#63;}
#endif
#if defined TARGET_formule2
\integer{d=randitem(5,10,20)*10}
\integer{t=randitem(15,12,6,45,30)}
\text{name1=slib(lang/fname fr,boy)}
\text{name2=slib(lang/fname fr,boy)}
\if{\name1=\name2}{
  \text{name1=Anthony}
  \text{name2=Matthieu}
}
\text{unit=heures}
\real{rep=1000/\d*\t/60}
\text{enonce=\name1 parcourt \d mètres de plus que \name2 toutes les \t minutes.
 Dans combien de temps aura-t-il 1 kilomètre d'avance &#63;}
#endif
#if defined TARGET_formule5
\integer{v=randint(4..13)*10}
\text{enonce=On estime qu'il faut une seconde à un conducteur pour réagir à un événement.
  Quelle distance, en mètres, parcourt-il s'il roule à \v km/h &#63;}
\integer{rep=\v*1000/3600}
\text{unit=mètres}
\text{remarque=<div class="wims_smallremark">Vous devez arrondir le résultat à l'entier le plus proche.</div>}
#endif

\statement{
\enonce
<div class="spacer">
<label for="reply1"><b>Votre réponse :</b></label> \embed{r1,5} \unit.</div>
\remarque}

\answer{}{\rep}{type=numexp}
