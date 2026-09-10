target=signeexp2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}

\integer{sa=random(1,-1)}
\integer{a0=random(1..10)}
\integer{a=\a0*\sa}

\integer{sb=random(1,-1)}
\integer{b0=random(1..10)}
\integer{b=\b0*\sb}
\integer{sc=random(1,-1)}
\integer{c=random(1..10)*\sc}
\integer{d=random(-10..10)}
\text{x=randitem(x,t)}
\function{u=(\b=0)?\a\x:\a\x+\b}
\function{f=(\d=0)? \c*e^(\u):\c*e^(\u) - \d}

!!!! signe de f(x)= cexp(ax+b) - d
!!!! coefficients simples

\text{symb=>}
!!! chgment sens inégalité si division par c negatif
\text{symb1=(\c>0)?\symb:<}
\rational{rep1=\d/\c}
\text{signe=(\rep1=0)?\name_posneg[3]}
\text{signe=(\rep1>0)?\name_posneg[1]}
\text{signe=(\rep1<0)?\name_posneg[2]}
\integer{takeln=(\signe issametext \name_posneg[1])?1:2}

\integer{m = 1}
\if{\takeln=2}{\integer{m = (\c > 0)?2:3}}
\text{rep0 = item(\m,\liste)}

\integer{chge=\a*\c}
\text{symb2=(\chge>0)?\symb:<}
\function{rep11= ln(\rep1)}
\function{rep2=(\a=1)?ln(\rep1)-\b:(ln(\rep1)-\b)/(\a)}
\function{rep2=(\a=-1)?\b-ln(\rep1)}

!!! pretty printing for rep2
\text{oppb=(\b<0)?+\b0:-\b}
\text{texrep2=(\a=1)?\ln(\rep1) \oppb:\frac{\ln(\rep1) \oppb}{\a}}

\integer{pprint=(\a<0 || \rep1=1)?1:0}

\if{\pprint=1}{
    \rational{pprep2=(\rep1=1)?-\b/\a}
    \text{pprep2=(\rep1!=1 && \a<0)?\frac{\b - \ln(\rep1)}{\a0}}
    \text{pprep2=(\rep1!=1 && \a=-1)?\b - \ln(\rep1)}}
    { \text{pprep2=\texrep2} }
\text{ineq= \f \symb 0}
!!! intervalle des solutions

\if{\takeln=2}{
\integer{typesol=(\symb1 issametext <)?1:2}}

\if{\takeln=1}{
     \text{s1=\symb2 issametext <?+:-}
     \text{s2=\symb2 issametext <?-:+}
}
\if{\takeln=2}{\text{s3=\typesol=2?+:-}}
\text{laregle= la règle \(e^u \symb1 v \Longleftrightarrow u \symb1 ln(v)\)}

!!!!!! QUESTIONS / ANSWERS
\if{\takeln=1}{
  \text{questionstep2=choice2,reply1,choice3,reply2,choice4,reply3}
  \text{questionstep3=choice5,choice6}
}{
  \text{questionstep2=choice7}
}

\steps{choice1
\questionstep2
\questionstep3
}

!!! STATEMENT
\statement{
  On veut étudier en fonction de \(\x) le signe de : \(\f\) .
  \if{\step=1}{
  <p>
  Pour ce faire, on commence par regarder si ce signe peut être déterminé de manière immédiate.
  </p>
  Sachant que \(e^{\x}>0) pour tout réel \x, on conclut que le signe de \(\f)
  \embed{choice1}.
  }
  \if{\step=2 && \takeln=1}{
    Le signe de \(f\) ne pouvant pas être trouvé de manière immédiate,
    on résout l'inéquation : \(\ineq\).
   On peut écrire les équivalences suivantes :
    <div class="wimscenter">
      (\ineq) \(\Longleftrightarrow) \(e^(\u)) \embed{choice2} \embed{reply1,5}
    </div><div class="wimscenter">
    \(\Longleftrightarrow) \(\u) \embed{choice3} \embed{reply2,10}.
    </div><div class="wimscenter">
    \(\Longleftrightarrow) \(\x) \embed{choice4} \embed{reply3}.
    </div>
  }
  \if{\step=2 && \takeln=2}{
    <div>
    Sachant que \(e^{t}>0\) pour tout réel \(t\),
    le signe de \(\f\) <span style="color:blue">\rep0</span>.
    </div>
    On dresse alors le tableau de signes suivant :
    <table style="width:60%" class="wimsborder wimscenter">
    <tr>
    <td style="width:15%;">\(\x\)</td>
    <td style="width:5%;">\(-\infty\)</td>
    <td style="width:75%;"></td>
    <td style="width:5%;"> \(+\infty)</td>
    </tr><tr>
    <td>\(\f\)</td>
    <td></td>
    <td>\embed{choice7}</td>
    <td></td>
    </tr>
    </table>
  }
  \if{\step=3 && \takeln=1}{
    <p>En résolvant \(\ineq\) on obtient :</p>
    <div class="wimscenter">\(\ineq) \(\Longleftrightarrow) \(\x) \symb2 \(\pprep2)</font>.
    </div>
    Posons \(\alpha = \pprep2 \).
    On dresse alors le tableau de signes suivant :
    <table style="width:75%" class="wimsborder wimscenter">
    <tr>
    <td style="width:15%;">\(\x\)</td>
    <td style="width:40%;text-align:left">\(-\infty\)</td>
    <td style="width:5%;">\(\,\alpha\)</td>
    <td style="width:40%;text-align:right"> \(+\infty\)</td>
    </tr><tr>
    <td>\(\f)</td>
    <td>\embed{choice5}</td>
    <td>0</td>
    <td>\embed{choice6}</td>
    </tr>
    </table>
  }
}
\choice{Première question}{\rep0}{\liste}{option=noidontknow}
\choice{Deuxième question a1.}{\symb1}{<,>}{option = nonstop, noidontknow}
\answer{Deuxième question a2.}{\rep1}{type=numexp}{option=nonstop}
\choice{Deuxième question b1.}{\symb1}{<,>}{option = nonstop, noidontknow}
\answer{Deuxième question b2.}{\rep11}{type=formal}{option=nonstop}
\choice{Deuxième question c1.}{\symb2}{<,>}{option=nonstop, noidontknow}
\answer{Deuxième question c2.}{\rep2}{type=formal}{weight=2}{option=nonstop}
\choice{Tableau de signes a.}{\s1}{+,-}{option = noidontknow}
\choice{Tableau de signes b.}{\s2}{+,-}{option = noidontknow}
\choice{Tableau de signes}{\s3}{+,-}{option = noidontknow}

!!!!! RESOLUTION FEEDBACK
\feedback{0=0}{
  <b>Voici une étude de signe détaillée de \(\f) :</b>
  <p>La fonction exponentielle est définie sur \(\,\RR\),
  donc il n'y a pas de précaution de définition à prendre.</p>
  \if{\takeln=1}{
    <p> Le signe de \(\f) ne peut pas être déterminé de manière
    immédiate en utilisant le fait que l'exponentielle
    est strictement positive,
    car c'est la somme d'un terme positif et d'un terme négatif.
    On résout donc l'inéquation \(\ineq\) :
     </p><div class="wimscenter">
    \(\ineq\) \(\Longleftrightarrow) \(e^(\u)) \symb1 \rep1
    </div>
    On peut appliquer \laregle, car le logarithme du
    second membre est défini (\rep1 > 0\):
    <div class="wimscenter">
    \(\ineq) \(\Longleftrightarrow) \(\u \symb1 ln(\rep1))
    <br>
    \(\ineq) \(\Longleftrightarrow) \(\a\x \symb1 ln(\rep1) \oppb )
     <br>
    \(\ineq) \(\Longleftrightarrow) \(\x \symb2 \texrep2 )
     <br>
    \if{\pprint=1}{\(\ineq) \(\Longleftrightarrow) \(\x \symb2 \pprep2 )}
    </div>
    <p>On obtient le tableau de signes suivant, où \( \alpha = \pprep2\)</p> :
    <table style="width:75%" class="wimsborder wimscenter">
    <tr>
    <td style="width:15%;">\(\x)</td>
    <td style="width:40%;text-align:left">\(-\infty\)</td>
    <td style="width:5%;">\(\alpha)</td>
    <td style="width:40%;text-align:right"> \(+\infty\)</td>
    </tr><tr>
    <td>\(\f\)</td>
    <td>\s1</td>
    <td>0</td>
    <td>\s2</td>
    </tr></table>
  }
  \if{\takeln=2}{
    <p>On sait que \(e^{\alpha}>0\) pour tout réel \(\alpha\).</p>
    <p>On en déduit
    \if{\typesol=1}{que \(\f) est la somme de deux nombres strictement négatifs.</p>
    Donc, \(\f\) a toujours le signe -. }
    {que \(\f\) est la somme de deux nombres strictement positifs.</p>
    Donc, \(\f\) a toujours le signe +. }
    <p>D'où le tableau de signes suivant :</p>
    <table style="width:60%" class="wimsborder wimscenter">
    <tr>
    <td style="width:10%;">\(\x\)</td>
    <td style="width:5%;">\(-\infty\)</td>
    <td style="width:80%;"> </td>
    <td style="width:5%;"> \(+\infty\)</td>
    </tr><tr>
    <td>\(\f\)</td>
    <td></td>
    <td>\s3</td>
    <td></td>
    </tr></table>
  }
}
