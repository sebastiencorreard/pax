target=vectcoplan
#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
\precision{100}
\text{confparm1= \confparm1 = ? 2 : \confparm1}
#include "css.inc"
#include "lang.inc"
** donnée de trois vecteurs indépendants
\matrix{V=slib(matrix/invertible 3,3)}

%% coordonnées de u
\matrix{u=\V[1;]}

%% coordonnées de v
\matrix{v=\V[2;]}
\matrix{t=\V[3;]}

%% coordonnées de w
\integer{k=random(1,2)}
%% k= 1 coplanaires, 2 non coplanaires

\integer{x=random(1..5)*random(1,-1)}
\integer{y=random(1..5)*random(1,-1)}
\matrix{w=pari(print([\u]*(\x)+[\v]*(\y)))}

\if{\k=1}{
\text{rep=coplanaires}
\text{symbeq=\(=\)}
}{
\text{rep=non coplanaires}
\matrix{w=pari(print([\w]+[\t]))}
\text{symbeq=\(\not =\)}
}

%%preparation de la solution rédigée
\text{eq1=texmath(\u[1]*x+(\v[1])*y)}
\text{eq2=texmath(\u[2]*x+(\v[2])*y)}
\text{eq3=texmath(\u[3]*x+(\v[3])*y)}
\integer{tdet=(\u[1])*(\v[2])-(\u[2])*(\v[1])}
\integer{tx=(\w[1])*(\v[2])-(\w[2])*(\v[1])}
\integer{ty=(\u[1])*(\w[2])-(\u[2])*(\w[1])}
\text{eq4=\((\u[3]) \times \frac{\tx}{\tdet} + (\v[3]) \times \frac{\ty}{\tdet})}

\text{rep=\k=1? \liste[1]:\liste[2]}
\if{\k=1}{
\text{textsol=\name_textsol[1]:<br>
<div class="wimscenter">
\(\overrightarrow{B C}= \j \overrightarrow{A B})
</div>
\name_textsol[2]}
}{
\text{textsol=\name_textsol[3], \name_textsol[4]}
}

\statement{
<div class="\style1">
<p>
Les vecteurs \(\overrightarrow{u}\), \(\overrightarrow{v}\) et \(\overrightarrow{w}\)
 dont les coordonnées dans un repère donné sont respectivement
</p>
<div class="wimscenter">
  \(\overrightarrow{u}\left(\begin{array}{c}\u[1]\\ \u[2]\\ \u[3]\end{array}\right)\),
  \(\overrightarrow{v}\left(\begin{array}{c}\v[1]\\ \v[2]\\ \v[3]\end{array}\right)\),
  \(\overrightarrow{w}\left(\begin{array}{c}\w[1]\\ \w[2]\\ \w[3]\end{array}\right)\)
</div>
sont-ils coplanaires&nbsp;?
</div>
<div class="\style2">
 Votre réponse : Les vecteurs sont \embed{choice1,\size}.
</div>
}

\choice{}{\rep}{\liste}
\hint{Si \(\overrightarrow{u}\) et \(\overrightarrow{v}\) ne sont pas colinéaires,
  il faut chercher (x,y) tel que
\(\overrightarrow{w} = x \overrightarrow{u} + y \overrightarrow{v}\).}
\solution{On constate tout d'abord que \(\overrightarrow{u}\) et \(\overrightarrow{v}\) ne sont pas colinéaires.<br>
Cherchons \((x,y)\) tel que
\(\overrightarrow{w} = x \overrightarrow{u} + y \overrightarrow{u}\).<br>
On doit résoudre le système:<br>
\(\left \lbrace \begin{array}{rcl} \w[1]&=&\eq1 \\ \w[2]&=&\eq2 \\ \w[3]&=&\eq3 \end{array}\)<br>
On résoud le système formé des deux premières équations : le déterminant du système vaut \tdet donc il possède une unique solution.<br>
On trouve \(x = \frac{\tx}{\tdet}\) et \(y=\frac{\ty}{\tdet}\).<br>
Si les vecteurs sont coplanaires on doit avoir une égalité numérique en reportant les valeurs de \(x\) et de \(y\) dans la troisième équation:<br>
\(\w[3]\) \symbeq \eq4 donc les vecteurs sont \rep.
}
