\title{Question 500&#8718; Programme de calcul (Scratch)}
\keywords{quizz,algorithmics,calculation}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-b-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }
\language{fr}

\format{html}

\text{n=shuffle(5)}
\integer{nb_depart=randint(3..10)}
\integer{index_pgm_choisi=randint(1..4)}
\integer{pgm_choisi=\n[\index_pgm_choisi]}
\text{nom_fichier1=\imagedir/../pgm_calcul_\n[1].svg}
\text{nom_fichier2=\imagedir/../pgm_calcul_\n[2].svg}
\text{nom_fichier3=\imagedir/../pgm_calcul_\n[3].svg}
\text{nom_fichier4=\imagedir/../pgm_calcul_\n[4].svg}

\integer{reponse1=4*\nb_depart+1}
\integer{reponse2=2*\nb_depart+4}
\integer{reponse3=3*\nb_depart+2}
\integer{reponse4=4*\nb_depart+3}
\integer{reponse5=2*\nb_depart+3}
\text{reponses=\reponse1,\reponse2,\reponse3,\reponse4,\reponse5}
\text{good1=\imagedir/../pgm_calcul_\pgm_choisi.svg}
\text{good=<img src="\good1" alt="">}
\text{feedback=La bonne réponse est&nbsp;&#58; <div class="wimscenter">\good </div>Le résultat \reponses[\pgm_choisi] est obtenu en faisant le calcul suivant&nbsp;&#58; }
\if{\pgm_choisi = 1}{\text{feedback=\feedback &#40; &#40;8 × <strong>\nb_depart</strong>&#41; + 2&#41; ÷ 2}}
\if{\pgm_choisi = 2}{\text{feedback=\feedback &#40; &#40;4 × <strong>\nb_depart</strong>&#41; + 8&#41; ÷ 2}}
\if{\pgm_choisi = 3}{\text{feedback=\feedback &#40; &#40;9 × <strong>\nb_depart</strong>&#41; + 6&#41; ÷ 3}}
\if{\pgm_choisi = 4}{\text{feedback=\feedback &#40; &#40;20 × <strong>\nb_depart</strong>&#41; + 15&#41; ÷ 5}}
\if{\pgm_choisi = 5}{\text{feedback=\feedback &#40; &#40;8 × <strong>\nb_depart</strong>&#41; + 12&#41; ÷ 4}}


\text{bads = }
\for{i = 1 to 4}{
  \if{\i != \pgm_choisi}{
    \if{\bads = }{
      \text{bads = <img src="\imagedir/../pgm_calcul_\i.svg" alt="">}
    }{
      \text{bads = \bads,<img src="\imagedir/../pgm_calcul_\i.svg" alt="">}
    }
  }
}
\text{enonce=Voici un programme Scratch.
<br>Si le nombre de départ vaut \nb_depart&#44; quel programme va donner \reponses[\pgm_choisi]&nbsp;&#63;<br>}
\text{enonceb=}
