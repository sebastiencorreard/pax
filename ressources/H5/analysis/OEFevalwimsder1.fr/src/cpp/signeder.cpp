target=signeder1 signeder2 signeder3 signeder4 signeder5
\author{Régine, Mangeard ; Maguy, Bruno}
\email{regine@mangeard.fr}
\format{html}
\precision{100}
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
#define TITRE Signe de la dérivée et variations
#if defined TARGET_signeder1
\title{TITRE 1}
\integer{x0=-5-randint(0..9)}
\integer{x1=randint(-4..-1)}
\integer{x2=randint(1..4)}
\integer{x3=5+randint(0..9)}
\integer{choix=randint(1,2)}
\if{\choix=2}
 {
  \integer{y2=randint(1..9)}
  \integer{y0=\y2+randint(1..9)}
  \integer{y1=randint(-9..-1)}
  \integer{y1=\y1=\x1?\y1-1}
  \integer{y3=0}
  \integer{s=\y2}
  \integer{t=\y1}
  \integer{t2=\t-1}
  \integer{u=\y0}
  \integer{xmin=\x1}
  \integer{xmax=\x0}
  \text{monotone = \(\searrow),\(\nearrow),\(\searrow)}
  \text{pos=top,bottom,top,bottom}
  \text{variations = décroissante,décroissante}
  \text{rep=2,1,2}
 }
 {
  \integer{y1=randint(1..9)}
  \integer{y3=\y1+randint(1..9)}
  \integer{y2=randint(-9..-1)}
  \integer{y0=0}
  \integer{s=\y1}
  \integer{t=\y2}
  \integer{t2=\t-1}
  \integer{u=\y3}
  \integer{xmin=\x2}
  \integer{xmax=\x3}
  \text{pos=bottom,top,bottom,top}
  \text{monotone = \(\nearrow),\(\searrow),\(\nearrow)}
  \text{variations = croissante,décroissante}
  \text{rep=1,2,1}
 }
\text{lstsigne=positif,négatif}

\statement{
On considère une fonction \(f) définie sur &#91; \x0; \x3 &#93;,
dont on connaît le tableau des variations
<table class="tab_var">
<tr>
  <th style="width:15%;"> \(x)</th>
      <td style="width:15%;text-align:left"> \x0</td>
      <td style="width:8%;"></td>
      <td style="width:15%;">\x1</td>
      <td style="width:8%;"></td>
      <td style="width:15%;">\x2</td>
      <td style="width:8%;"></td>
      <td style="width:15%;text-align:right">\x3</td>
</tr><tr>
  <th style="vertical-align:middle;width:15%;">\(var f)</th>
     <td style="width:15%;text-align:left;vertical-align:\pos[1]"> \y0 </td>
     <td style="width:8%;">\monotone[1] </td>
     <td style="width:15%;vertical-align:\pos[2]"> \y1 </td>
     <td style="width:8%;"> \monotone[2]  </td>
     <td style="width:15%;vertical-align:\pos[3]"> \y2 </td>
     <td style="width:8%;"> \monotone[3] </td>
     <td style="width:15%;text-align:right;vertical-align:\pos[4]"> \y3 </td>
      </tr>
</table>
<p>
Quel est le signe de \(f'(x))
</p>
<ol>
<li> sur [\x0;\x1]&nbsp;: \embed{reply1} </li>
<li> sur [\x1;\x2]&nbsp;: \embed{reply2} </li>
<li> sur [\x2;\x3]&nbsp;: \embed{reply3} </li>
</ol>
}
\answer{sur [\x0;\x1]}{\rep[1];\lstsigne}{type=radio}
\answer{sur [\x1;\x2]}{\rep[2];\lstsigne}{type=radio}
\answer{sur [\x2;\x3]}{\rep[3];\lstsigne}{type=radio}
#endif

#if defined TARGET_signeder2
\title{TITRE 2}
\integer{choix=randint(1,2)}
\integer{x1=randint(-10..5)}
\integer{x2=\x1+randint(3..10)}
\integer{y1=randint(-10..10)}
\integer{y2=\choix=1?\y1+randint(3..10):\y1-randint(3..10)}

### la liste des objets que l'on peut cliquer pour résoudre l'exercice ###
\text{vse=\(\searrow)}
\text{vne=\(\nearrow)}
\text{vx1=\(\x1)}
\text{vx2=\(\x2)}
\text{vy1=\(\y1)}
\text{vy2=\(\y2)}
\text{permut=shuffle(\vx1,\vx2,\vy1,\vy2)}
\text{permut= wims(listuniq \permut)}

\text{clicList=\vse,\vne,\permut}
## taille des symboles et des champs à remplir par clic LxHxnb ##
\text{size=60x40x1}

## préâration de la réponse
\text{signe=\choix=1?-,+,-:+,-,+}
\text{monotone=\choix=1?\vse,\vne,\vse:\vne,\vse,\vne}
\text{grepfx=\monotone[1],\vy1,\monotone[2],\vy2,\monotone[3]}

\statement{Compléter le tableau des variations d'une fonction \(f) dérivable
sur \(\,\RR) sachant que
<div class="wimscenter"> \(f(\x1)=\y1) et \(f(\x2)=\y2) </div>
<table class="tab_var">
<tr>
  <th style="width:15%;"> \(x)</th>
      <td style="width:12%;text-align:left"> \(-\infty)</td>
      <td style="width:12%;"></td>
      <td style="width:12%;">\x1</td>
      <td style="width:12%;"></td>
      <td style="width:12%;">\x2</td>
      <td style="width:12%;"></td>
      <td style="width:12%;text-align:right">\(+\infty)</td>
</tr><tr>
  <th style="width:15%;"> sg \(f'(x))</th>
      <td style="width:12%;text-align:left"> &nbsp;</td>
      <td style="width:12%;">\signe[1]</td>
      <td style="width:12%;">0</td>
      <td style="width:12%;">\signe[2]</td>
      <td style="width:12%;">0</td>
      <td style="width:12%;">\signe[1]</td>
      <td style="width:12%;text-align:right">&nbsp;</td>
</tr><tr>
  <th  style="width:15%;">\(var f)</th>
     <td style="width:12%;text-align:left" > &nbsp;</td>
     <td style="width:12%;vertical-align:middle"> \embed{reply1,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply2,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply3,\size}  </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply4,\size} </td>
     <td style="width:12%;vertical-align:middle"> \embed{reply5,\size} </td>
     <td style="width:12%;text-align:right;vertical-align:middle"> &nbsp; </td>
      </tr>
</table>

}
\answer{}{\grepfx[1];\clicList}{type=clickfill}
\answer{}{\grepfx[2];\clicList}{type=clickfill}
\answer{}{\grepfx[3];\clicList}{type=clickfill}
\answer{}{\grepfx[4];\clicList}{type=clickfill}
\answer{}{\grepfx[5];\clicList}{type=clickfill}
#endif


#if defined TARGET_signeder3
\title{TITRE 3}
\integer{choix=randint(1,2)}
\integer{x1=randint(-10..5)}
\integer{x2=\x1+randint(3..10)}
\integer{x3=\x2+randint(3..10)}
\integer{y1=randint(-10..10)}
\integer{y2=\choix=1?\y1+randint(3..10):\y1-randint(3..10)}
\integer{y3=\choix=1?\y2-randint(3..10):\y2+randint(3..10)}

### la liste des objets que l'on peut cliquer pour résoudre l'exercice ###
\text{vse=\(\searrow)}
\text{vne=\(\nearrow)}
\text{vplus=<font size=+2>+</font>}
\text{vmoins=<font size=+2>-</font>}

\text{vx1=\(\x1)}
\text{vx2=\(\x2)}
\text{vx3=\(\x3)}
\text{vy1=\(\y1)}
\text{vy2=\(\y2)}
\text{vy3=\(\y3)}
\text{v0=\(0)}
\text{permut=shuffle(\vx1,\vx2,\vx3,\vy1,\vy2,\vy3,\v0)}
\text{permut= wims(listuniq \permut)}

\text{clicList=\vse,\vne,\permut,\vplus,\vmoins}
## taille des symboles et des champs à remplir par clic LxHxnb ##
\text{size=60x40x1}

## choix des consignes
\if{\choix=1}
 {
\text{cons1=\(f'(x) > 0) sur &#93; \x1;\x2 &#91;}
\text{cons2=\(f'(x) < 0) sur &#93; \x2;\x3 &#91;}
\integer{xmin=\y1>\y3?\x3:\x1}
\integer{xa=\y1>\y3?\x1:\x3}
\integer{ymin=\y1>\y3?\y3:\y1}
\integer{ya=\y1>\y3?\y1:\y3}
\text{cons3=\(f) admet un minimum en \xmin égal à \ymin, un maximum égal à \y2 et \(f(\xa)=\ya)}

 }
 {
\text{cons1=\(f'(x) < 0) sur &#93; \x1;\x2 &#91;}
\text{cons2=\(f'(x) > 0) sur &#93; \x2;\x3 &#91;}
\integer{xmax=\y1>\y3?\x1:\x3}
\integer{xa=\y1>\y3?\x3:\x1}
\integer{ymax=\y1>\y3?\y1:\y3}
\integer{ya=\y1>\y3?\y3:\y1}
\text{cons3=\(f) admet un maximum en \xmax égal à \ymax, un minimum égal à \y2 et \(f(\xa)=\ya)}
 }
%%%% préparation de la réponse
\text{signe=\choix=1?\vplus,\vmoins:\vmoins,\vplus}
\text{monotone=\choix=1?\vne,\vse:\vse,\vne}
\text{grepfx=\vy1,\monotone[1],\vy2,\monotone[2],\vy3}
\text{grepfp=\signe[1],\v0,\signe[2]}

\statement{
<p>
  Compléter le tableau des variations d'une fonction \(f) dérivable
  sur \(\,\RR) sachant que
</p>
<div class="wimscenter"> \cons1 et \cons2,<br>
\cons3 </div>

<table class="tab_var"><tr>
  <th style="width:15%;"> \(x)</th>
      <td style="width:15%;">\x1</td>
      <td style="width:15%;"></td>
      <td style="width:15%;">\x2</td>
      <td style="width:15%;"></td>
      <td style="width:15%;text-align:right">\x3</td>
</tr><tr>
  <th style="width:15%;"> sg \(f'(x))</th>
      <td style="width:15%;text-align:left"> &nbsp;</td>
      <td style="width:15%;">\embed{reply1,\size}</td>
      <td style="width:15%;">\embed{reply2,\size}</td>
      <td style="width:15%;">\embed{reply3,\size}</td>
      <td style="width:15%;">&nbsp;</td>
</tr><tr>
  <th style="width:15%;">\(var f)</th>
     <td style="width:15%;text-align:left"> \embed{reply4,\size}</td>
     <td style="width:15%;vertical-align:middle"> \embed{reply5,\size} </td>
     <td style="width:15%;vertical-align:middle"> \embed{reply6,\size} </td>
     <td style="width:15%;vertical-align:middle"> \embed{reply7,\size} </td>
     <td style="width:15%;vertical-align:middle"> \embed{reply8,\size} </td>
      </tr>
</table>

}
\answer{}{\grepfp[1];\clicList}{type=clickfill}
\answer{}{\grepfp[2];\clicList}{type=clickfill}
\answer{}{\grepfp[3];\clicList}{type=clickfill}
\answer{}{\grepfx[1];\clicList}{type=clickfill}
\answer{}{\grepfx[2];\clicList}{type=clickfill}
\answer{}{\grepfx[3];\clicList}{type=clickfill}
\answer{}{\grepfx[4];\clicList}{type=clickfill}
\answer{}{\grepfx[5];\clicList}{type=clickfill}
#endif


#if defined TARGET_signeder4
\title{TITRE 4}
\integer{a=randint(1,2)*randint(1,-1)}
\integer{b=randint(1..3)*randint(1,-1)}
\integer{c=\a+randint(-2..2)}
\text{fdata=1/x^2,-1,6,-3,3
1/x-\a,-\a-3,-\a+3,-3,3
ln(abs(x))-\a*x,-\a-2,-\a+4,-\a-2,-\a+4
x^3/3-1.5*x^2+x,-3,3,-3,3
2*\b*arctan(x)-\b*x,-4,4,-4,4
\a/(x^2+1)-\c,-\c-4,-\c+4,-3,3
}
\text{ind=shuffle(6)}

\text{size=160}

\text{graphFct=}
\text{graphDer=}

\for{k=1 to 4}{
  \text{cedata=row(\ind[\k],\fdata)}
  \function{f=\cedata[1]}
  \function{fd=diff(\f,x)}
  \integer{yminf=\cedata[2]}
  \integer{ymaxf=\cedata[3]}
  \integer{ymind=\cedata[4]}
  \integer{ymaxd=\cedata[5]}
  \text{graph=
    <img src="
    draw(\size,\size
 xrange -4,4
 yrange \yminf,\ymaxf
 parallel -4,\yminf,4,\yminf,0,1,\ymaxf-\yminf+1,gray
 parallel -4,\yminf,-4,\ymaxf,1,0,9,gray
 arrow -4,0,4,0,10,black
 arrow 0,\yminf,0,\ymaxf,10,black
 plot red,\f
    )"
    width="\size"
    height="\size"
    alt="">
    }
  \text{graphFct=wims(append item \graph to \graphFct)}

  \text{graphd=
    <img src="
    draw(\size,\size
 xrange -4,4
 yrange \ymind,\ymaxd
 parallel -4,\ymind,4,\ymind,0,1,\ymaxd-\ymind+1,gray
 parallel -4,\ymind,-4,\ymaxd,1,0,9,gray
 arrow -4,0,4,0,10,black
 arrow 0,\ymind,0,\ymaxd,10,black
 plot blue,\fd
    )"
    width="\size"
    height="\size"
    alt="" >
    }

  \text{graphDer=wims(append item \graphd to \graphDer)}

}

\text{taille=\size x\size x\size}
%%% enoncé de l'exo
\statement{
On a dessiné les courbes représentatives de 4 fonctions (en rouge)
et de leurs dérivées (en bleu).
<p>
Associez à la courbe de chaque fonction, celle de sa dérivée.
</p>
<div class="wimscenter">
  \embed{reply 1,\taille}
</div>
}
#### soumission de réponse
\reply{Correspondance graphe/fonction}{\graphFct;\graphDer}{type=correspond}
#endif
#if defined TARGET_signeder5
\title{TITRE 5}
\integer{choix=randint(1,2)}
%%% choix =1 on affiche la dérivée
   choix = 2 on affiche la fonction

#include "datasigne5.inc"
\statement{
On conviendra que la partie visible du graphique respecte le tableau de variation de \(f).
<p>
Cocher les bonnes propositions&nbsp;:
</p>
<ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
  <li>\embed{reply1,3}</li>
  <li>\embed{reply1,4}</li>
  <li>\embed{reply1,5}</li>
\if{\choix=2}
{
  <li>\embed{reply1,6}</li>
}
</ul>
<div class="wimscenter">
\draw{300,300}{\dessin}
</div>
}
\answer{}{\grep;\lstrep}{type=checkbox}
#endif
