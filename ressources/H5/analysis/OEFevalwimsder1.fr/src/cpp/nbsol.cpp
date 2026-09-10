target=nbsol1 nbsol2 nbsol3 nbsol4 nbsol5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer{yes}
\css{<style>
table.tab_var {margin-left:auto;margin-right:auto;
   border:solid 1px black;}
table.tab_var tr, table.tab_var td, table.tab_var th {
   padding:7pt;margin-top:10px; margin-bottom:10px;
   text-align:center; border-collapse:collapse; min-width:10pt;
   }
table.tab_var th { border:solid 1px black}
table.tab_var tr { border:solid 1px black}
</style>
}

#define TITRE Nombre de solutions et encadrement
#include "nbsol.inc"

#if defined TARGET_nbsol1
\statement{
   On considère la fonction \(f) définie sur \(\lbrack -10^3;10^3 \rbrack) par
<div class="wimscenter"> \(f(x)=\ft) </div>
<p>
   On note \(f(-10^3)=L_1) et \(f(10^3)=L_2) avec \tbornes.</p><p>
   On veut déterminer <b>sans calculatrice </b> le nombre de solutions de l'équation
</p>
<div class="wimscenter"> \(f(x)=0)</div>
<ol>
<li> Compléter le tableau des variations de \(f)&nbsp;:
<table class="var_tab">
<tr>
  <th style="width:15%;"> \(x)</th>
      <td style="width:15%;">\(-10^3)</td>
      <td style="width:15%;"></td>
      <td style="width:15%;">\embed{reply1,3}</td>
      <td style="width:15%;"></td>
      <td style="width:15%;">\embed{reply2,3}</td>
      <td style="width:15%;"></td>
      <td style="width:15%;text-align:right">\(+10^3)</td>
</tr><tr>
  <th style="width:15%;"> sg \(f'(x))</th>
      <td style="width:15%;text-align:left"> &nbsp;</td>
      <td style="width:15%;">\embed{reply3,\size}</td>
      <td style="width:15%;">0</td>
      <td style="width:15%;">\embed{reply4,\size}</td>
      <td style="width:15%;">0</td>
      <td style="width:15%;">\embed{reply5,\size}</td>
      <td style="width:15%;">&nbsp;</td>
</tr><tr>
  <th style="width:15%;">\(var f)</th>
     <td style="width:15%;text-align:left"> \(L_1)</td>
     <td style="width:15%;vertical-align:middle"> \embed{reply6,\size} </td>
     <td style="width:15%;vertical-align:middle"> ? </td>
     <td style="width:15%;vertical-align:middle"> \embed{reply7,\size} </td>
     <td style="width:15%;vertical-align:middle"> ? </td>
     <td style="width:15%;vertical-align:middle"> \embed{reply8,\size} </td>
     <td style="width:15%;text-align:right;vertical-align:middle"> \(L_2) </td>
      </tr>
</table>
</li><li>
   Soit \(x_0) la racine non nulle de \(f').
\if{\x1=\x2}
  {
 Quel est le signe de \(f(x_0))? \embed{reply13}</li>
  }
  {
 Encadrer \(x_0) par deux entiers consécutifs&nbsp;:
<div class="wimscenter"> \embed{reply9,3} < \(x_0) < \embed{reply10,3}</div></li>
<li> En déduire une \tencad judicieuse de \(f(x_0))&nbsp;:
<div class="wimscenter"> \(f(x_0)) \symb \embed{reply11,7}</div></li>
  }
<li> En déduire le nombre de solutions de l'équation \(f(x)=0)&nbsp;:
<div class="wimscenter"> Nombre de solutions = \embed{reply12,2} </div></li>
</ol>
}
\answer{singularité}{\singg}{type=numexp}
\answer{singularité}{\singd}{type=numexp}
\answer{signe dérivée gauche}{\sd[1];\lstrep}{type=clickfill}
\answer{signe dérivée milieu}{\sd[2];\lstrep}{type=clickfill}
\answer{signe dérivée droite}{\sd[3];\lstrep}{type=clickfill}
\answer{sens variation gauche}{\sv[1];\lstrep}{type=clickfill}
\answer{sens variation milieu}{\sv[2];\lstrep}{type=clickfill}
\answer{sens variation droite}{\sv[3];\lstrep}{type=clickfill}
\answer{borne gauche}{\x1}{type=numeric}
\answer{borne droite}{\x2}{type=numeric}
\answer{\tencad}{\z}{type=numeric}
\answer{nb solution}{\nbsol}{type=numeric}
\answer{signe de \(f(x_0))}{\sx0;Positif,Négatif}{type=radio}

#endif

#if (defined TARGET_nbsol2 || defined TARGET_nbsol5 )

\statement{
   On considère la fonction \(f) définie sur \(\lbrack -10^3;10^3 \rbrack) par
<div class="wimscenter"> \(f(x)=\ft) </div>
<p>
   On note \(f(-10^3)=L_1) et \(f(10^3)=L_2) avec \tbornes.</p>
#if defined TARGET_nbsol2
   On veut déterminer <b>sans calculatrice </b> le nombre de solutions de l'équation
<div class="wimscenter"> \(f(x)=0)</div>
<ol>
#else
   On veut encadrer \(f(x)) sur l'intervalle [\bg;\bd].
<ol>
<li> Calculer \(f(\bg))=\embed{reply13,4} et \(f(\bd))=\embed{reply14,4}</li>
#endif
<li> Compléter le tableau des variations de \(f)&nbsp;:
<table class="var_tab">
<tr>
  <th style="width:12%;"> \(x)</th>
      <td style="width:12%;">\(-10^3)</td>
      <td style="width:12%;"></td>
      <td style="width:12%;">\embed{reply1,3}</td>
      <td style="width:12%;"></td>
      <td style="width:12%;">\embed{reply2,3}</td>
      <td style="width:12%;"></td>
      <td style="width:12%;text-align:right">\(+10^3)</td>
</tr><tr>
  <th style="width:12%;"> sg \(f'(x))</th>
      <td style="width:12%;text-align:left"> &nbsp;</td>
      <td style="width:12%;">\embed{reply3,\size}</td>
      <td style="width:12%;">0</td>
      <td style="width:12%;">\embed{reply4,\size}</td>
      <td style="width:12%;">0</td>
      <td style="width:12%;">\embed{reply5,\size}</td>
      <td style="width:12%;">&nbsp;</td>
</tr><tr>
  <th style="width:12%;">\(var f)</th>
     <td style="width:12%;text-align:left" > \(L_1)</td>
     <td style="width:12%;vertical-align:middle"> \embed{reply6,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply7,\size2} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply8,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply9,\size2} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply10,\size} </td>
     <td style="width:12%;text-align:right;vertical-align:middle"> \(L_2) </td>
      </tr>
</table>
</li>
#if defined TARGET_nbsol2

<li> En déduire le nombre de solutions de \(f(x)=0)&nbsp;:
<div class="wimscenter"> Nombre de solutions = \embed{reply11,2} </div></li>
#else
<li> En déduire l'encadrement cherché&nbsp;:
<div class="wimscenter"> \embed{reply11,2} \( \leq f(x) \leq ) \embed{reply12,2} </div></li>
#endif
</ol>
}
\answer{singularité gauche}{\x1}{type=numexp}
\answer{singularité droite}{\x2}{type=numexp}
\answer{signe dérivée gauche}{\sd[1];\lstrep}{type=clickfill}
\answer{signe dérivée milieu}{\sd[2];\lstrep}{type=clickfill}
\answer{signe dérivée droite}{\sd[3];\lstrep}{type=clickfill}
\answer{sens variation gauche}{\sv[1];\lstrep}{type=clickfill}

#if defined TARGET_nbsol2
\answer{signe image singularité gauche}{\sg[1];\lstrep}{type=clickfill}
#else
\answer{image singularité gauche}{\u1}{type=numexp}
#endif
\answer{sens variation milieu}{\sv[2];\lstrep}{type=clickfill}
#if defined TARGET_nbsol2
\answer{signe image singularité droite}{\sg[2];\lstrep}{type=clickfill}
#else
\answer{image singularité droite}{\u2}{type=numexp}
#endif
\answer{sens variation droite}{\sv[3];\lstrep}{type=clickfill}
#if defined TARGET_nbsol2
\answer{nb solution}{\nbsol}{type=numeric}
#else
\answer{borne gauche}{\z1}{type=numexp}
\answer{borne droite}{\z2}{type=numexp}
\answer{image de \bg}{\zg}{type=numeric}
\answer{image de \bd}{\zd}{type=numeric}
#endif
#endif

#if defined TARGET_nbsol3
\title{TITRE 3}
\statement{
On considère la fonction \(f) définie sur \(\lbrack -10^3;10^3 \rbrack) par
<div class="wimscenter"> \(f(x)=\ft) </div>
<p>
On note \(f(-10^3)=L_1) et \(f(10^3)=L_2) avec \tbornes.
</p><p>
On veut déterminer <b>sans calculatrice </b> le nombre de solutions de l'équation.
</p>
<div class="wimscenter"> \(f(x)=0)</div>
<ol>
<li> Compléter le tableau des variations de \(f)&nbsp;:
<table class="var_tab">
<tr>
  <th style="width:10%;"> \(x)</th>
      <td style="width:10%;">\(-10^3)</td>
      <td style="width:10%;"></td>
      <td style="width:10%;">\embed{reply1,3}</td>
      <td style="width:10%;"></td>
      <td style="width:10%;">\embed{reply2,3}</td>
      <td style="width:10%;"></td>
      <td style="width:10%;">\embed{reply3,3}</td>
      <td style="width:10%;"></td>
      <td style="width:10%;text-align:right">\(+10^3)</td>
</tr><tr>
  <th style="width:10%;"> sg \(f'(x)\)</th>
      <td style="width:10%;text-align:left"> &nbsp;</td>
      <td style="width:10%;">\embed{reply4,\size}</td>
      <td style="width:10%;">0</td>
      <td style="width:10%;">\embed{reply5,\size}</td>
      <td style="width:10%;">0</td>
      <td style="width:10%;">\embed{reply6,\size}</td>
      <td style="width:10%;">0</td>
      <td style="width:10%;">\embed{reply7,\size}</td>
      <td style="width:10%;">&nbsp;</td>
</tr><tr>
  <th style="width:10%;">\(var f)</th>
     <td style="width:10%;text-align:left" > \(L_1)</td>
     <td style="width:10%;vertical-align:middle"> \embed{reply8,\size} </td>
     <td style="width:10%;vertical-align:middle"> \embed{reply9,\size} </td>
     <td style="width:10%;vertical-align:middle"> \embed{reply10,\size} </td>
     <td style="width:10%;vertical-align:middle"> \embed{reply11,\size} </td>
     <td style="width:10%;vertical-align:middle"> \embed{reply12,\size} </td>
     <td style="width:10%;vertical-align:middle"> \embed{reply13,\size} </td>
     <td style="width:10%;vertical-align:middle"> \embed{reply14,\size} </td>
     <td style="width:10%;text-align:right;vertical-align:middle"> \(L_2) </td>
      </tr>
</table>
</li>
<li> En déduire le nombre de solutions de \(f(x)=0)&nbsp;:
<div class="wimscenter"> Nombre de solutions = \embed{reply15,2} </div>
</li></ol>
}
\answer{singularité gauche}{\x1}{type=numexp}
\answer{singularité milieu}{\x2}{type=numexp}
\answer{singularité droite}{\x3}{type=numexp}
\answer{signe dérivée gauche}{\sd[1];\lstrep}{type=clickfill}
\answer{signe dérivée milieu gauche}{\sd[2];\lstrep}{type=clickfill}
\answer{signe dérivée milieu droite}{\sd[3];\lstrep}{type=clickfill}
\answer{signe dérivée droite}{\sd[4];\lstrep}{type=clickfill}
\answer{sens variation gauche}{\sv[1];\lstrep}{type=clickfill}
\answer{signe image singularité gauche}{\sg[1];\lstrep}{type=clickfill}
\answer{sens variation milieu gauche}{\sv[2];\lstrep}{type=clickfill}
\answer{signe image singularité milieu}{\sg[2];\lstrep}{type=clickfill}
\answer{sens variation milieu droite}{\sv[3];\lstrep}{type=clickfill}
\answer{signe image singularité droite}{\sg[3];\lstrep}{type=clickfill}
\answer{sens variation droite}{\sv[4];\lstrep}{type=clickfill}
\answer{nb solution}{\nbsol}{type=numeric}
#endif

#if defined TARGET_nbsol4
\title{TITRE 4}
\statement{
On considère la fonction \(f) définie sur \(\lbrack -10^3;10^3 \rbrack) par
<div class="wimscenter"> \(f(x)=\ft) </div>
<p>
On note \(f(-10^3)=L_1) et \(f(10^3)=L_2) avec \tbornes.
</p><p>
On veut déterminer <b>sans calculatrice </b> le nombre de solutions de l'équation.
</p>
<div class="wimscenter"> \(f(x)=0)</div>
<ol>
<li> Compléter les deux premières lignes du tableau des variations de \(f)&nbsp;:
<div class="wims_instruction"> Taper <span class="tt">sqrt(a)</span> pour \(\sqrt{a})</div>
<table class="var_tab">
<tr>
  <th style="width:12%;"> \(x)</th>
      <td style="width:12%;">\(-10^3)</td>
      <td style="width:12%;"></td>
      <td style="width:12%;">\embed{reply1,8}</td>
      <td style="width:12%;"></td>
      <td style="width:12%;">\embed{reply2,8}</td>
      <td style="width:12%;"></td>
      <td style="width:12%;text-align:right">\(+10^3)</td>
</tr><tr>
  <th style="width:12%;"> sg \(f'(x))</th>
      <td style="width:12%;text-align:left"> &nbsp;</td>
      <td style="width:12%;">\embed{reply3,\size}</td>
      <td style="width:12%;">0</td>
      <td style="width:12%;">\embed{reply4,\size}</td>
      <td style="width:12%;">0</td>
      <td style="width:12%;">\embed{reply5,\size}</td>
      <td style="width:12%;">&nbsp;</td>
</tr><tr>
  <th style="width:12%;">\(var f)</th>
     <td style="width:12%;text-align:left" > \(L_1)</td>
     <td style="width:12%;vertical-align:middle"> \embed{reply6,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply7,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply8,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply9,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply10,\size} </td>
     <td style="width:12%;text-align:right;vertical-align:middle"> \(L_2) </td>
      </tr>
</table>
</li><li>
On note \(x_1) et \(x_2), avec \(x_1 < x_2) les deux valeurs de \(x) annulant la dérivée \(f'(x)).<br>
Encader \(x_1) et \(x_2) par deux entiers consécutifs&nbsp;:
<div class="wimscenter"> \embed{reply11,3} \(< x_1 <) \embed{reply12,3} </div>
<div class="wimscenter"> \embed{reply13,3} \(< x_2 <) \embed{reply14,3} </div>
</li><li>
En déduire les signes de \(f(x_1)) et \(f(x_2)) et compléter la dernière ligne du tableau des variations.
</li><li>
En déduire le nombre de solutions de \(f(x)=0)&nbsp;:
<div class="wimscenter"> Nombre de solutions = \embed{reply15,2} </div>
</li></ol>
}
\answer{singularité gauche}{\x1}{type=numeric}
\answer{singularité droite}{\x2}{type=numeric}
\answer{signe dérivée gauche}{\sd[1];\lstrep}{type=clickfill}
\answer{signe dérivée milieu}{\sd[2];\lstrep}{type=clickfill}
\answer{signe dérivée droite}{\sd[3];\lstrep}{type=clickfill}
\answer{sens variation gauche}{\sv[1];\lstrep}{type=clickfill}
\answer{signe image singularité gauche}{\sg[1];\lstrep}{type=clickfill}
\answer{sens variation milieu}{\sv[2];\lstrep}{type=clickfill}
\answer{signe image singularité droite}{\sg[2];\lstrep}{type=clickfill}
\answer{sens variation droite}{\sv[3];\lstrep}{type=clickfill}
\answer{borne gauche de \(x_1)}{\xa1}{type=numeric}
\answer{borne droite de \(x_1)}{\xb1}{type=numeric}
\answer{borne gauche de \(x_1)}{\xa2}{type=numeric}
\answer{borne droite de \(x_1)}{\xb2}{type=numeric}

\answer{nb solution}{\nbsol}{type=numeric}
#endif
