target= progcalcul

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\title{TITRE}

\integer{nb1=random(randint(-30..-1),randint(1..30))}
\integer{nb2=random(randint(-30..-1),randint(1..30))}
\integer{absnb2=abs(\nb2)}
\if{\nb2<0}{\text{snb2=-}
            \text{snb2opp=+}}
            {\text{snb2=+}
            \text{snb2opp=-}}
\integer{nb5=}
\integer{choix=randint(2)}
\integer{aux=-\nb2}
\if{\nb2<0}{\text{tnb2=\nb2}}{\text{tnb2=\plus\nb2}}
\if{\nb1<0}{\text{tnb1=\nb1}}{\text{tnb1=\plus\nb1}}
\if{\choix=1}{\integer{nb3=\nb1+\nb2}
              \text{prog=<ul><li>On choisit un nombre.</li><li>On lui ajoute \(\tnb2\)</li><li>On trouve <span class="nowrap">\(\nb3\).</span></li></ul>}
              \text{u=+(\snb2\absnb2)}
              \text{v=-(\snb2\absnb2)}
              \text{A=slib(graph/graphviz [0,\u;0,0],[?,\nb3],edge)}
              \text{B=slib(graph/graphviz [0,\u;\v,0],[?,\nb3],edge)}
              \text{sign=-}
              \if{\nb3<0}{\text{tnb3=\nb3}}{\text{tnb3=\plus\nb3}}
              \text{ope=\(?=(\tnb3)\plus(\snb2opp\absnb2)\)<p>\(?=\nb1\)</p>}}
              {\integer{nb3=\nb1-\nb2}
              \text{prog=<ul><li>On choisit un nombre.</li><li>On soustrait \(\tnb2\)</li><li>On trouve <span class="nowrap">\(\nb3\).</span></li></ul>}
              \text{u=-(\snb2\absnb2)}
              \text{v=+(\snb2\absnb2)}
              \text{A=slib(graph/graphviz [0,\u;0,0],[?,\nb3],edge)}
              \text{B=slib(graph/graphviz [0,\u;\v,0],[?,\nb3],edge)}
              \text{sign=+}
              \text{ope=\(?=\nb1\)}}
\if{\nb3<0}{\text{tnb3=\nb3}}{\text{tnb3=\plus\nb3}}  
\statement{<p>On considère le programme de calcul suivant&nbsp;:
\prog
<label for="reply1">Quel nombre a été choisi au départ ?</label> \embed{r1,5}}
\answer{}{\nb1}{type=numexp}
\hint{Cela revient à trouver le nombre inconnu dans l'égalité
\if{\choix=1}{<span class="nowrap">\((&#46;&#46;?&#46;&#46;)+(\tnb2)=\nb3\).</span>}
              {<span class="nowrap">\((&#46;&#46;?&#46;&#46;)-(\tnb2)=\nb3\).</span>}}
\solution{Le nombre choisi au départ est \(\tnb1\) car 
<p>
\if{\choix=1}{<ul><li>On choisit un nombre&nbsp;:\(\tnb1\)</li>
                  <li>On ajoute \(\tnb2\)&nbsp;:\((\tnb1)+(\tnb2)=\nb3\)</li>
                  <li>On obtient bien <span class="nowrap">\(\nb3\).</span></li></ul>}
\if{\choix=2}{<ul><li>On choisit un nombre&nbsp;:\(\tnb1\)</li>
              \if{\nb2>0}{<li>On soustrait \(\tnb2\)&nbsp;:\((\tnb1)-(\tnb2)=(\tnb1)+(\minus\nb2)=\nb3\)
                          <li>On obtient bien <span class="nowrap">\(\nb3\).</span></li></ul>}
              \if{\nb2<0}{<li>On soustrait \(\tnb2\)&nbsp;:\((\tnb1)-(\tnb2)=(\tnb1)+(\plus\aux)=\nb3\)
                          <li>On obtient bien <span class="nowrap">\(\nb3\).</span></li></ul>}
            }
Pour aller plus loin, on peut essayer de trouver le nombre manquant par un calcul en observant le schéma suivant&nbsp;:<br>
<div class="wimscenter">\A</div>
et trouver le nombre de départ en inversant le chemin&nbsp;:
<div class="wimscenter">\B</div>
donc en effectuant le calcul&nbsp;:\(?=(\tnb3)\sign(\snb2\absnb2)\)
<p>\ope</p>}
%%Test de la réponse élève en cas d'erreur
\integer{nb5=\reply1}
\integer{nb4=\nb5+\nb2}
\integer{nb6=\nb5-\nb2}
\if{\nb5>0}{\text{tnb5=\plus \nb5}}
           {\text{tnb5=\minus \nb5}}
\if{\choix=1}{\text{progel=<ul><li>Vous avez choisi&nbsp;: \(\nb5\)</li>
                  <li>Vous avez ajouté \(\tnb2\)&nbsp;: \((\tnb5)+(\tnb2)=\nb4\)</li>
                  <li><span style="color:red">Vous n'avez pas obtenu <span class="nowrap">\(\nb3\).</span></span></li></ul>}}
\if{\choix=2}{\text{progel1=<ul><li>Vous avez choisi&nbsp;: \(\nb5\)</li>}
              \if{\nb2>0}{\text{progel2=<li>Vous avez soustrait \(\tnb2\)&nbsp;: \((\tnb5)-(\tnb2)=(\tnb5)+(\minus\nb2)=\nb6\)
                          <li><span style="color:red">Vous n'avez pas obtenu <span class="nowrap">\(\nb3\).</span></span></li></ul>}}
              \if{\nb2<0}{\text{progel2=<li>Vous avez soustrait \(\tnb2\)&nbsp;: \((\tnb5)-(\tnb2)=(\tnb5)+(\plus\aux)=\nb6\)
                          <li><span style="color:red">Vous n'avez pas obtenu <span class="nowrap">\(\nb3\).</span></span></li></ul>}}
              \text{progel=\progel1
              \progel2}}                                  
\feedback{\sc_reply1=0}{<div class="macss">\progel</div>}
