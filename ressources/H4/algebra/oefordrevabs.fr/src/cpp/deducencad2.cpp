target=deducencad2

%%
\observation{L'objet de l'exercice est d'obtenir une inégalité concernant f(x) à partir d'une inégalité sur x ici l'encadrement utilisé avant de passer au carré ou à l'inverse n'est pas positif}
%%
\language{fr}
\computeanswer{yes}
\precision{1000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}

#include "css.inc"
%% Choix du type d'exercice
\integer{kf=random(1,2)}
 kf= 1 carré, =2 inverse
 integer{kf=1}
\integer{kt=random(1,2)}
 kt= 1 inégalité, =2 encadrement
   \integer{kt=1}

%% Choix des constantes on veut a<b et -a not = b
\integer{aa=random(1..10)*random(1,-1)}
\integer{bb=random(1..10)*random(1,-1)}
\integer{bb=\aa=\bb?2*\bb:\bb}
\integer{mbb=\bb*(-1)}
\integer{aa=\aa=\mbb?2*\aa:\aa}
\integer{a=\aa<\bb?\aa:\bb}
\integer{b=\aa<\bb?\bb:\aa}

%% la liste des symboles d'inégalité %%
\text{sgt=>}
\text{sge=\(\ge )}
\text{slt=<}
\text{sle=\(\le )}

\text{symboles=\slt,\sle,\sgt,\sge}
\text{swapsymb=3,4,1,2}
\integer{symbx1=randint(1..2)}
\integer{symbx2=randint(1..2)}
\integer{symbx=\symbx1+2*(\symbx2-1)}
%% Choix de l'hypothèse
\integer{kt=\kf=1?2:\kt}
%% le cas kt=1 n'est pas interessant pour les carrés
\if{\kt=2}
  {
    \text{eqx=\a \symboles[\symbx1] \(x) \symboles[\symbx2] \b }
  }
  {
       \if{\symbx2=1 and \b>0}{
         \text{eqx= 0 \slt \(x) \symboles[\symbx] \b}
       }
       \if{\symbx2=2 and \b>0}{
         \text{eqx= \(x) \symboles[\symbx] \b}
        }
       \if{\symbx2=2 and \b<0}{
         \text{eqx= 0 \sgt \(x) \symboles[\symbx] \b }
        }
       \if{\symbx2=1 and \b<0}{
         \text{eqx= \(x) \symboles[\symbx] \b}
       }
  }
\text{eqfx=\kf=1?\(texmath(maxima((x)^2;))):\(texmath(maxima(1/x;)))}

%% calcul de la réponse %%
%%préparation des étapes intermédiaires pour la solution
\if{\kf=1}
  {
%% debut kt=2
%% valeurs des constantes intervenant dans les réponses possibles
     \integer{bb2=(\b)^2}
     \integer{aa2=(\a)^2}
     \integer{a2=\aa2<\bb2?\aa2:\bb2}
     \integer{b2=\aa2<\bb2?\bb2:\aa2}
     \integer{ma2=-\a2}
     \integer{mb2=-\b2}
     \integer{s=\a*(\b)}

%% liste des réponses possibles
     \text{x1= \a2 \slt \(x^2) \slt \b2}
     \text{x2= \a2 \sle \(x^2) \slt \b2}
     \text{x3= \a2 \slt \(x^2) \sle \b2}
     \text{x4= \a2 \sle \(x^2) \sle \b2}
     \text{x5= \ma2 \slt \(x^2) \sle \b2 }
     \text{x6= \mb2 \slt \(x^2) \sle \a2 }
     \text{x7= 0 \slt \(x^2) \slt \a2 }
     \text{x8= 0 \sle \(x^2) \slt \a2 }
     \text{x9= 0 \slt \(x^2) \sle \a2 }
     \text{x10= 0 \sle \(x^2) \sle \a2 }
     \text{x11= 0 \slt \(x^2) \slt \b2}
     \text{x12= 0 \sle \(x^2) \slt \b2 }
     \text{x13= 0 \slt \(x^2) \sle \b2}
     \text{x14= 0 \sle \(x^2) \sle \b2}

     \text{repList=\x1,\x2,\x3,\x4,\x5,\x6,\x7,\x8,\x9,\x10,\x11,\x12,\x13,\x14}
     \if{\s>0}
        {
%% a et b sont de meme signe
             \integer{gind=\aa2<\bb2?\symbx1+2*(\symbx2-1):\symbx2+2*(\symbx1-1)}
             \text{greplist=\gind}
       }
       {
%% a negatif et b positif
              \integer{gind=\aa2<\bb2?12+2*(\symbx2-1):12+2*(\symbx1-1)}
              \text{greplist=\gind}
  }
%% fin kf=1
}
{
%% début kf = 2 fonction inverse
     \rational{ib=1/(\b)}
     \rational{mib=-1/(\b)}
     \integer{mb=-1*(\b)}
     \rational{ia=1/(\a)}
     \rational{mia=-1/(\a)}
     \integer{ma=-1*(\a)}
     \integer{ab=\a*(\b)}
  \if{\kt=1}
    {
     \if{\b>0 }
     {
        \text{x1=0 \slt \(texmath(maxima(1/x;))) \slt \ib}
        \text{x2=0 \slt \(texmath(maxima(1/x;))) \sle \ib}
        \text{x3= \ib \slt \(texmath(maxima(1/x;)))}
        \text{x4= \ib \sle \(texmath(maxima(1/x;)))}
        \text{x5= \mb \slt \(texmath(maxima(1/x;))) \slt 0}
        \text{x6= \mb \sle \(texmath(maxima(1/x;))) \slt 0}
        \text{x7= \(texmath(maxima(1/x;))) \slt \mb}
        \text{x8= \(texmath(maxima(1/x;))) \sle \mb}
        \text{x9= \mib \slt \(texmath(maxima(1/x;))) \slt 0}
        \text{x10= \mib \sle \(texmath(maxima(1/x;))) \slt 0}
        \text{x11= \(texmath(maxima(1/x;))) \slt \mib}
        \text{x12= \(texmath(maxima(1/x;))) \sle \mib}
        \if{\symbx2=1}{
                 \integer{gind=2+\symbx1}
                 }
                 {
                 \integer{gind=\symbx1}
                 }
        \text{greplist=\gind}
       }
       {
        \text{x1=\ib \slt \(texmath(maxima(1/x;))) \slt 0}
        \text{x2=\ib \sle \(texmath(maxima(1/x;))) \slt 0}
        \text{x3= \(texmath(maxima(1/x;))) \slt \ib}
        \text{x4= \(texmath(maxima(1/x;))) \sle \ib}
        \text{x5= \mb \slt \(texmath(maxima(1/x;))) }
        \text{x6= \mb \sle \(texmath(maxima(1/x;))) }
        \text{x7= 0 \slt \(texmath(maxima(1/x;))) \slt \mb}
        \text{x8= 0 \slt \(texmath(maxima(1/x;))) \sle \mb}
        \text{x9= \mib \slt \(texmath(maxima(1/x;))) }
        \text{x10= \mib \sle \(texmath(maxima(1/x;)))}
        \text{x11= 0 \slt \(texmath(maxima(1/x;))) \slt \mib}
        \text{x12= 0 \slt \(texmath(maxima(1/x;))) \sle \mib}
        \if{\symbx2=2}{
                    \integer{gind=2+\symbx1}
                   }
                 {
                 \integer{gind=\symbx1}
                 }
        \text{greplist=\gind}
       }
     \text{repList=\x1,\x2,\x3,\x4,\x5,\x6,\x7,\x8,\x9,\x10,\x11,\x12}
%% fin kt=1
    }
    {
%% debut kt=2
      \if{\ab>0}
        {
%% a et b de meme signe
     \text{eqx0=}

        \text{x1=\ia \slt \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \slt \ib}
        \text{x2=\ia \slt \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \sle \ib}
        \text{x3=\ia \sle \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \slt \ib}
        \text{x4=\ia \sle \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \sle \ib}
        \text{x5=\ib \slt \(texmath(maxima(1/x;))) \slt \ia}
        \text{x6=\ib \slt \(texmath(maxima(1/x;))) \sle \ia}
        \text{x7=\ib \sle \(texmath(maxima(1/x;))) \slt \ia}
        \text{x8=\ib \sle \(texmath(maxima(1/x;))) \sle \ia}
        \integer{gind=4+\symbx1+2*(\symbx2-1)}
        \text{greplist=\gind}
        }
        {
%% a négatif et b positif
     \text{eqx0= et x \(\not =) 0}
        \text{eqx=\eqx \eqx0}
        \text{x1=\ia \slt \(texmath(maxima(1/x;))) \slt \ib \eqx0}
        \text{x2=\ia \slt \(texmath(maxima(1/x;))) \sle \ib \eqx0}
        \text{x3=\ia \sle \(texmath(maxima(1/x;))) \slt \ib \eqx0}
        \text{x4=\ia \sle \(texmath(maxima(1/x;))) \sle \ib \eqx0}
        \text{x5=\ib \slt \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \slt \ia}
        \text{x6=\ib \slt \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \sle \ia}
        \text{x7=\ib \sle \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \slt \ia}
        \text{x8=\ib \sle \(texmath(maxima(1/x;))) \name_or \(texmath(maxima(1/x;))) \sle \ia}
        \integer{gind=4+\symbx1+2*(\symbx2-1)}
        \text{greplist=\gind}
        }
        \text{x9=\mb \slt \(texmath(maxima(1/x;))) \slt \ma \eqx0}
        \text{x10=\mb \slt \(texmath(maxima(1/x;))) \sle \ma \eqx0}
        \text{x11=\mb \sle \(texmath(maxima(1/x;))) \slt \ma \eqx0}
        \text{x12=\mb \sle \(texmath(maxima(1/x;))) \sle \ma \eqx0}
        \text{x13=\mia \slt \(texmath(maxima(1/x;))) \slt \mib \eqx0}
        \text{x14=\mia \slt \(texmath(maxima(1/x;))) \sle \mib \eqx0}
        \text{x15=\mia \sle \(texmath(maxima(1/x;))) \slt \mib \eqx0}
        \text{x16=\mia \sle \(texmath(maxima(1/x;))) \sle \mib \eqx0}
     \text{repList=\x1,\x2,\x3,\x4,\x5,\x6,\x7,\x8,\x9,\x10,\x11,\x12}
    }
%% fin kf = 2

}
\text{srepList=shuffle(\repList)}
\text{greplist=wims( positionof item \repList[\gind] in \srepList)}

%% preparation de la présentation des cases à cocher
\integer{nbrep=items(\srepList)}
\integer{nbrows=floor((\nbrep+1)/2)}
\text{col1=wims ( values i for i=1 to \nbrows)}
\text{col2=wims ( values i+\nbrows for i=1 to \nbrows)}
\text{clicList=
\slt,\sle
}

%% préparation d'un exemple
\integer{\exa=random(1..10)*(-1)}
\integer{\exb=random(1..10)}
\integer{exa2=(\exa)^2}
\integer{exb2=(\exb)^2}
\if{\exa2>\exb2}
  {\integer{exc=\exa2}\text{signd=\slt}}
  {\integer{exc=\exb2}\text{signd=\le}}

\text{size=\confparm1=1 ? :x-large}
%% Maintenant, rédigeons l'énoncé %%
\statement{
<div class="rm">
  \name_question[1] \eqx, \name_question[2]
  \eqfx ?
  <ol>
  \for{k=1 to \nbrows}{
    <li>
    \embed{r1,\col1[\k]}</li><li>\embed{r1,\col2[\k]}
    </li>
  }
  </ol>
</div>
}

%% Récupération des réponses %%
\answer{}{\greplist;\srepList}{type=radio}
%% une indication sous forme de rappel des théoremes %%
\hint{
<div class="hint">
  Servez-vous de théorèmes sur les inégalités
<ul>
<li> On peut <span style="color:green">ajouter </span>un même nombre aux deux membres d'une inégalité:<br>
 \(a < b \Leftrightarrow a+c < b+c\) pour tout réel \(c\).
</li><li> On peut <span style="color:green">multiplier</span> par un même réel <span style="color:red">strictement positif</span> les deux membres d'une inégalité :<br>
 \(a < b \Leftrightarrow a \times c < b \times c \) pour tout \(c > 0).
</li><li> On peut <span style="color:green">multiplier</span> par un même réel <span style="color:red">strictement négatif</span> les deux membres
 d'une inégalité <span style="color:red"> en changeant le symbole de l'inégalité :</span><br>
 \(a < b \Leftrightarrow a \times c > b \times c\) pour tout \(c < 0\).
</li><li> <span style="color:blue">Les nombres positifs</span> sont rangés dans <span style="color:green">le même ordre que leurs carrés :</span> <br>
 \(0 < a < b \Leftrightarrow a^2 < b^2)
</li><li> <span style="color:blue">Les nombres positifs</span> sont rangés dans <span style="color:red">l'ordre inverse de leurs inverses :</span> <br>
 \(0 < a < b \Leftrightarrow \frac{1}{a} > \frac{1}{b})
</li></ul>
Attention, lorsque \(x\) est compris entre un nombre négatif et un nombre positif, il faut éclater
l'encadrement en 2 et traiter séparément les deux inégalités avant de conclure
<br>
Exemple :
\(\exa < x \le \exb \Leftrightarrow \exa < x \le 0) \name_or \( 0 \le x \le \exb).<br>
En élevant au carré, on obtient : \(\exa < x \le \exb \Leftrightarrow 0 \le x^2 < \exa2) \name_or \(0 \le x^2 \le \exb2\). <br>
On en déduit que  \(\exa < x \le \exb \Leftrightarrow 0 \le x \signd \exc).
</div>
}
