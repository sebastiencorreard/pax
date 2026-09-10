target=frequence
\title{La musique}
\language{fr}
\range{-5..5}
\author{Rémi, Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{10000}

#define TYPE 2
%%Plusieurs méthodes sont proposées et peuvent être consultées sans réponses intermédiaires%%

%% Liste des méthodes et icones %%
\text{\list=1,3,4,5,6,7,8}
\text{\list2=1,3,4,5,6,7,8}
\integer{methcnt=items(\list2)}
%%Choix de la méthode%%
#include "methode.inc"

\real{r=2^(1/12)}

%% Axe
\text{graph = xrange -5,5
yrange -2,24
linewidth 1
parallel -4,-1,-4,23,4,0,3,grey
parallel -5,0,6,0,0,1,24,grey
linewidth 2
segment -4,0,-4,12,black
linewidth 3
arrow -2,-2,-2,24,8,black

text black,-4,0.8, medium,DO
text black,-3.1,0.4, medium, 3
text black,-4,1.8, medium,DO#
text black,-4,2.8, medium,RE
text black,-4,3.8, medium,RE#
text black,-4,4.8, medium,MI
text black,-4,5.8, medium,FA
text black,-4,6.8, medium,FA#
text black,-4,7.8, medium,SOL
text black,-4,8.8, medium,SOL#
text black,-4,9.8, medium,LA
text black,-3.1,9.4, medium,3
text black,-4,10.8, medium,LA#
text black,-4,11.8, medium,SI
text black,-4,12.8, medium,DO
text black,-3.1,12.4, medium, 4
text black,-4,13.8, medium,DO#
text black,-4,14.8, medium,RE
text black,-4,15.8, medium,RE#
text black,-4,16.8, medium,MI
text black,-4,17.8, medium,FA
text black,-4,18.8, medium,FA#
text black,-4,19.8, medium,SOL
text black,-4,20.8, medium,SOL#
text black,-4,21.8, medium,LA
text black,-3.1,21.4, medium,4

text black,0.1,9.8, large, 440
text black,0.1,21.8, large, 880
}
\text{url = draw(150,390
\graph)}

\text{Arc=
xrange 0,14
yrange -12,14

arc 2,5.5,12,12,-90,90,black
arrow 2,11.5,0,11.5,20,black
segment 0,11.5,2,11.5,black
text black,9,6,large, x 2

arc 2,6,3,1,-90,90,black
arrow 2,6.5,0,6.5,20,black
segment 0,5.5,2,5.5,black
text black,4,7,large, x ...?
}
\text{url1 = draw(210,390
\Arc)}

\text{Arcs=
xrange 0,24
yrange -11.5,14.5

arc 16,6,10,12,-90,90,black
arrow 16,12,14,12,20,black
text black,22,6,large,x 2
segment 14,0,16,0,black

arc 9,9,6,6,-90,90,black
arrow 9,12,7,12,20,black
text black,12,10,large, x ...?
segment 7,6,9,6,black

arc 9,3,6,6,-90,90,black
arrow 9,6,7,6,20,black
text black,12,4,large, x ...?
segment 7,0,9,0,black

arc 1,1.5,3,3,-90,90,black
arrow 1,3,0,3,10,black
text black,3,2.5,large, x ...?
segment 0,0,1,0,black

arc 1,4.5,3,3,-90,90,black
arrow 1,6,0,6,10,black
text black,3,5.5,large, x ...?
segment 0,3,1,3,black
}
\text{url2 = draw(360,390
\Arcs)}

\text{F12=
xrange -1,4
yrange -1,9
parallel -1,-1,-1,9,1,0, 11, lightblue
parallel -1,-1,4,-1,0,1, 17, lightblue
arrow -1,0,4,0,8, black
arrow 0,-1,0,9,8, black

text black,0,-0.1 , small, 0
text black,1,-0.1 , small, 1
text black,2,-0.1 , small, 2
text black,3,-0.1 , small, 3

text black,-0.5,0.4, small, 0
text black,-0.5,1.4, small, 1
text black,-0.5,2.4, small, 2
text black,-0.5,3.4, small, 3
text black,-0.5,4.4, small, 4
text black,-0.5,5.4, small, 5
text black,-0.5,6.4, small, 6
text black,-0.5,7.4, small, 7
text black,-0.5,8.4, small, 8
text black,-0.5,9.4, small, 9
plot red, x^12+0*sqrt(x)
dsegment 0,2,1.06,2,black
dsegment 1.06,0,1.06,2,black
}
\text{MM=wims(makelist 0 for x=1 to \methcnt)}
\text{W=}
\text{testsolution=}
\text{ETAPE=r1}
\text{COND=1}
\nextstep{\ETAPE}
\conditions{\COND}

\statement{
  <div class="wims_question">
  <ul class="wims_nopuce">
  <li>La gamme tempérée est constituée de 12 notes en montant de demi-ton en demi-ton :</li>
  <li>DO, DO#, RE, RE#, MI, FA, FA#, SOL, SOL#, LA, LA#, SI.</li>
  <li>Après la note SI, on recommence une nouvelle octave à DO.</li>
  <li>Pour distinguer les notes des octaves distinctes, on écrit DO<sub>1</sub> puis DO<sub>2</sub>, DO<sub>3</sub>, DO<sub>4</sub>...</li>
  <li>Ainsi LA<sub>3</sub> est compris entre DO<sub>3</sub> et DO<sub>4</sub>.</li>
  <li>On sait que la fréquence double chaque fois qu'on monte d'une octave.</li>
  <li>Par exemple, le LA<sub>3</sub> de la 3<sup>ème</sup> octave a pour fréquence 440 Hz et le LA<sub>4</sub>
  a pour fréquence 880 Hz.</li>
  <li>Pour passer d'une note à la suivante, un demi-ton plus haut, on multiplie la fréquence toujours par le même nombre.</li>
  <li>Quel est le coefficient multiplicateur qui permet de passer d'une note à la suivante, un demi-ton plus haut ?</li>
  </ul>
  </div>
  \if{\step=1}{
#include "listmeth.inc"
  }
  \if{\step>1}{
    \if{\W=\trep[1]}{
      <div>
      <label for="reply2">Il faudra multiplier la fréquence par :</label> \embed{reply2,5} (à 0,0001 près).
      </div>
    }{
      <p>\name_help <strong>\W</strong>.</p>
      <div class="wims_question">
      \if{\W=\trep[2]}{
        <p>
        Un dessin comme celui-ci aide à comprendre l'énoncé.
        </p><p><img src="\url"><img src="\url1"></p>
      }
      \if{\W=\trep[3]}{
        <img src="\url"><img src="\url2">
        <p>
          De la note La<sub>3</sub> à LA<sub>4</sub>, la fréquence est multipliée par 2.
        </p><p>
        De la note LA<sub>3</sub> à RE#, puis de RE# à LA<sub>4</sub>, la fréquence est multipliée
        par le même nombre \(x).
        </p>
        <p>Quelle équation vérifie ce nombre \(x) ? Quelle est la valeur exacte de \(x) ?
        et sa valeur approchée ?</p>
        <p>
        On appelle \(k) le nombre par lequel il faut multiplier la fréquence
        de LA<sub>3</sub> pour obtenir celle de DO<sub>4</sub>.</p>
        <p>Quelle équation vérifie ce nombre \(k) ? Quelle est la valeur exacte de \(k) ?
        et sa valeur approchée ?</p>
        <p>
        On appelle \(r) le nombre par lequel il faut multiplier la fréquence de LA<sub>3</sub>
        pour obtenir celle de LA#.</p>
        <p>Quelle équation vérifie ce nombre \(r) ? Quelle est la valeur exacte de \(r) ?
        et sa valeur approchée ?</p>
      }
      \if{\W=\trep[4]}{
        <ul>
        <li>On peut appeler \(r) le nombre par lequel est multiplié la fréquence lorsqu'on monte d'un demi-ton.</li>
        <li>Quelle équation vérifie \(r) ?</li></ul>
      }
      \if{\W=\trep[5]}{
        <p>On considère la fonction \(f) définie sur &#91 0 ; \(+\infty)&#91 par \(x \mapsto x^12).</p>
        <ul>
        <li>Combien le nombre 2 a-t-il d'antécédents ?</li>
        <li>Comment nommer et noter la fonction qui associe à chaque nombre réel positif,
        son antécédent par la fonction \(f) ?</li>
        <li>Tracer la courbe de la fonction \(f) et éventuellement de sa fonction réciproque.</li>
        <li>En déduire une valeur approchée du nombre cherché.</li>
        </ul>
      }
      \if{\W=\trep[6]}{
        <ul>
        <li>Rentrer la fonction \(f) définie sur \(\,\RR) par \(x \mapsto x^12) dans la calculatrice.</li>
        <li>Avec le tableau de valeurs de la calculatrice, encadrer l'antécédent de 2 avec un pas de plus en plus petit.</li>
        </ul>
      }
      \if{\W=\trep[7]}{
        <p>Le nombre recherché est compris entre \(a=1) et \(b=2).</p>
        <ul><li>
        Réaliser un programme qui calcule la moyenne \(x) de \(a) et \(b), puis calcule \(x^12)
        pour déterminer si le nombre cherché est entre \(a) et \(x) ou entre \(x) et \(b), puis
        remplace \(a) ou \(b) par \(x) pour donner un meilleur encadrement du nombre cherché.
        </li><li>
        Réaliser une boucle pour répéter l'opération jusqu'à obtenir la précision cherchée,
        c'est-à-dire que la différence \(b-a) soit suffisamment petite.
        </li></ul>
      }
      </div>
      <p>\consigne2</p>
#include "listmeth.inc"
    }
  }
}

\answer{Méthode}{\var1;\trep}{type=click}{option=nonstop}
\answer{Coefficient}{\r}{type=numeric}
\condition{Choix de la méthode}{1=1}
\condition{Coefficient}{\r2=\r}

#include "etape.inc"
\integer{testsolution=pari(M=[\MM]; sum(j=2,\methcnt,M[j]))}
\solution{
  Vous avez choisi
  \if{\testsolution<1}{
    de répondre directement.
  }{
    \if{\MM[2]=1}{
      <h3>\name_method <strong>\trep[2]</strong>.</h3>
      <img src="\url"><img src="\url1">
    }
    \if{\MM[3]=1}{
      <h3>\name_method <strong>\trep[3]</strong>.</h3>
      <img src="\url"><img src="\url2"><br>
      De LA<sub>3</sub> à RE# la fréquence est multipliée par \(x = \sqrt{2})<br>
      De LA<sub>3</sub> à DO<sub>4</sub> la fréquence est multipliée par \(k = \sqrt[4]{2})<br>
      De LA<sub>3</sub> à LA# la fréquence est multipliée par \(r = \sqrt[12]{2})
    }
    \if{\MM[4]=1}{
      <h3>\name_method <strong>\trep[4]</strong>.</h3>
      Si on appelle \(r) le nombre par lequel est multiplié la fréquence lorsqu'on monte d'un demi-ton alors \(r^12=2).<br>
    Donc \(r = \sqrt[12]{2} \approx) \r.
  }
  \if{\MM[5]=1}{
    <h3>\name_method <strong>\trep[5]</strong>.</h3>
    Par la fonction cube \(f) définie sur &#91 0 ; \(+\infty)&#91 par \(x \mapsto x^12), le nombre 2 a un antécédent.<br>
    La courbe de \(f) est :<br>
    \draw{200,400}{\F12}
  }
  \if{\MM[6]=1}{
    <h3>\name_method <strong>\trep[6]</strong>.</h3>
    Voici un tableau de valeurs.
    <table class="wimscenter wimsborder">
    <tr><th>\(x)</td><td>1,05</td><td>1,055</td><td>1,059</td><td>1,0594</td><td>1,0595</td><td>1,06</td><td>1,065</td></tr>
    <tr><th>\(x^12)</td><td>1,796</td><td>1,901</td><td>1,9895</td><td>1,9986</td><td>2,0008</td><td>2,012</td><td>2,129</td></tr>
    </table>
  }
  \if{\MM[7]=1}{
    <h3>\name_method <strong>\trep[7]</strong>.</h3>
    Algorithme possible :
    <ul>
      <li>A \(\leftarrow) 1</li>
      <li>B \(\leftarrow) 2</li>
      <li>P \(\leftarrow) 0,001 (<i>P est la précision voulue.</i>)</li>
      <li>Tant que B \(-) A \(\gt) P faire :
      <ul>
        <li>X \(\leftarrow) (A + B)/2</li>
        <li>Y \(\leftarrow) X^3</li>
        <li>Si Y \(\gt) 2 alors B \(\leftarrow) X sinon A \(\leftarrow) X</li>
        <li>Fin Tant que</li>
      </ul></li>
      <li>Afficher A, Afficher B</li>
    </ul>
    }
  }
  <p>La bonne réponse est \(\sqrt[12]{2} \approx) \r.</p>
}
