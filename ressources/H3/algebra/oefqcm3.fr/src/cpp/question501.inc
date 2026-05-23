\title{Question 501 Programme de calcul (Scratch)}
\keywords{quizz,algorithmics,calculation}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-b-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }
\language{fr}

\format{html}
#define TYPEQUEST 0

\text{n=randint(1..5)}
\integer{nb_depart=randint(0..10)}
\text{nom_fichier=\imagedir/../pgm_calcul_\n.svg}

\if{\n = 1}{
  \integer{etape1=8*\nb_depart}
  \integer{etape2=8*\nb_depart+2}
  \integer{reponse=4*\nb_depart+1}
  \text{feedback=Le résultat vaut \reponse&nbsp;&#58<br>}
  \text{feedback=\feedback 8 × <strong>\nb_depart</strong> = \etape1<br>}
  \text{feedback=\feedback \etape1 + 2 = \etape2<br>}
  \text{feedback=\feedback \etape2 ÷ 2 = \reponse}
}
\if{\n = 2}{
  \integer{etape1=4*\nb_depart}
  \integer{etape2=4*\nb_depart+8}
  \integer{reponse=2*\nb_depart+4}
  \text{feedback=Le résultat vaut \reponse&nbsp;&#58<br>}
  \text{feedback=\feedback 4 × <strong>\nb_depart</strong> = \etape1<br>}
  \text{feedback=\feedback \etape1 + 8 = \etape2<br>}
  \text{feedback=\feedback \etape2 ÷ 2 = \reponse}
}
\if{\n = 3}{
  \integer{etape1=9*\nb_depart}
  \integer{etape2=9*\nb_depart+6}
  \integer{reponse=3*\nb_depart+2}
  \text{feedback=Le résultat vaut \reponse&nbsp;&#58<br>}
  \text{feedback=\feedback 9 × <strong>\nb_depart</strong> = \etape1<br>}
  \text{feedback=\feedback \etape1 + 6 = \etape2<br>}
  \text{feedback=\feedback \etape2 ÷ 3 = \reponse}
}
\if{\n = 4}{
  \integer{etape1=20*\nb_depart}
  \integer{etape2=20*\nb_depart+15}
  \integer{reponse=4*\nb_depart+3}
  \text{feedback=Le résultat vaut \reponse&nbsp;&#58<br>}
  \text{feedback=\feedback 20 × <strong>\nb_depart</strong> = \etape1<br>}
  \text{feedback=\feedback \etape1 + 15 = \etape2<br>}
  \text{feedback=\feedback \etape2 ÷ 5 = \reponse}
}
\if{\n = 5}{
  \integer{etape1=8*\nb_depart}
  \integer{etape2=8*\nb_depart+12}
  \integer{reponse=2*\nb_depart+3}
  \text{feedback=Le résultat vaut \reponse&nbsp;&#58;<br>}
  \text{feedback=\feedback 8 × <strong>\nb_depart</strong> = \etape1<br>}
  \text{feedback=\feedback \etape1 + 12 = \etape2<br>}
  \text{feedback=\feedback \etape2 ÷ 4 = \reponse}
}


\text{rep=\reponse}
\text{typerep=numeric}

\text{enonce=<p>On considère l'algorithme suivant&nbsp;&#58;</p>
<div class="wimscenter"><img style="height:40%;width:40%;" src="\imagedir/../pgm_calcul_\n.svg" alt=""></div>
<p>Quel résultat obtient-on si on choisit \nb_depart comme nombre de départ&nbsp;&#63;<p>}
\text{enonceb=}
