\title{Question 705 NS Comparaison de séries statistiques}
\keywords{quizz,median,mean}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }
\integer{cas=randomitem(1,2,3,4)}
\text{donnees=Les deux séries ont la même moyenne et la même médiane.,Les deux séries ont la même moyenne mais pas la même médiane.,Les deux séries ont la même médiane mais pas la même moyenne.,Les deux séries n’ont ni la même moyenne ni la même médiane.}
\if{\cas=1}{%%%Les deux séries ont la même moyenne et la même médiane.
  \text{good=\donnees[1]}
  \text{bad1=\donnees[2]}
  \text{bad2=\donnees[3]}
  \text{bad3=\donnees[4]}
  \integer{med=randint(7..11)}
  \integer{moy=\med}
  \text{templist=shuffle(\med-1)}
  \integer{temp=\templist[1]}
  \integer{A1=\moy-\temp}
  \integer{A2=\med}
  \integer{A3=\moy+\temp}
  \integer{temp=\templist[2]}
  \integer{B1=\med-\temp}
  \integer{B2=\med}
  \integer{B3=\med+\temp}
  }
\if{\cas=2}{%%%Les deux séries ont la même moyenne mais pas la même médiane.
  \text{good=\donnees[2]}
  \text{bad1=\donnees[3]}
  \text{bad2=\donnees[4]}
  \text{bad3=\donnees[1]}
  \text{templist=randint(1..10),randint(11..20),randint(40..60)}
  \integer{somme=\templist[1]+\templist[2]+\templist[3]}
  \integer{med=\templist[2]}
  \integer{A1=\templist[1]}
  \integer{A2=\med}
  \integer{A3=\templist[3]}
  \integer{temp=(3+\moy)/2}
  %%%%%%%%%%%%%%%%
  \integer{B2=\med+randomitem(2,1,-1,-2)}
  \integer{B1=randint(1..\med-2)}
  \integer{B3=\somme-\B1-\B2}
  }
\if{\cas=3}{%%%Les deux séries ont la même médiane mais pas la même moyenne.
  \text{good=\donnees[3]}
  \text{bad1=\donnees[2]}
  \text{bad2=\donnees[4]}
  \text{bad3=\donnees[1]}
  \text{templist=randint(3..10),randint(11..20),randint(40..60)}
  \integer{somme=\templist[1]+\templist[2]+\templist[3]}
  \integer{med=\templist[2]}
  \integer{A1=\templist[1]}
  \integer{A2=\med}
  \integer{A3=\templist[3]}
  \integer{temp=(3+\moy)/2}
  %%%%%%%%%%%%%%%%
  \integer{B2=\med}
  \integer{temp00=\templist[1]-randint(1,2)}
  \text{B1=randomitem(0.5,0.5,\temp00)}
  \integer{B3=randomitem(100,80,90,\somme-\B1-\B2+randomitem(10,20,30,40))}
  }
\if{\cas=4}{%%%Les deux séries n’ont ni la même moyenne ni la même médiane
  \text{good=\donnees[4]}
  \text{bad1=\donnees[2]}
  \text{bad2=\donnees[3]}
  \text{bad3=\donnees[1]}
  \text{templist=randint(3..10),randint(11..20),randint(40..60)}
  \integer{somme=\templist[1]+\templist[2]+\templist[3]}
  \integer{med=\templist[2]}
  \integer{A1=\templist[1]}
  \integer{A2=\med}
  \integer{A3=\templist[3]}
  \integer{temp=(3+\moy)/2}
  %%%%%%%%%%%%%%%%
  \integer{decal=randint(1..10)}
  \integer{B2=\A2+\decal}
  \integer{B1=\A1+\decal}
  \integer{B3=\A3+\decal}
  }
\text{enonce=Voici deux séries de valeurs. <br><span class="nowrap"><b>série A&nbsp;&#58; \A1 &#59; \A2 &#59; \A3 </b></span>  <br>  <span class="nowrap"><b>série B&nbsp;&#58; \B1 &#59; \B2 &#59; \B3  </b>.</span> <br>Une seule de ces affirmations est exacte&nbsp;&#58;}

\text{bads=\bad1,\bad2,\bad3}
\text{compmed=\A2=\B2?\(\A2=\B2\):\(\A2 \ne \B2\)}
\text{compmoy=\A1+\A2+\A3=\B1+\B2+\B3?\(\A1+\A2+\A3=\B1+\B2+\B3\):\(\A1+\A2+\A3\ne\B1+\B2+\B3\)}
\text{feedback=La bonne réponse est <b>"\good"</b>. <ul class="wims_nopuce"><li>Pour les médianes&nbsp;&#58;</li> <ul><li>Les trois nombres de chaque série sont classés par ordre croissant&#44; la médiane est donc la seconde.</li><li>Ici \compmed.</li></ul>
<li>Pour les moyennes&nbsp;&#58;</li> <ul><li>On peut comparer la somme des trois nombres (qu'il faudrait diviser par trois pour obtenir la moyenne).</li><li>Ici \compmoy.</li></ul></ul>}
