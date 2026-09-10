target=solde1 solde2
\language{fr}
\range{-5..5}
\author{Rémi,Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{10000}

#if defined TARGET_solde1
\title{Les soldes avec choix de méthode et schémas dans l'ordre}
\text{T = 1,2,3}
\text{Rq=Ils sont dans le même ordre que les questions.}
#endif

#if defined TARGET_solde2
\title{Les soldes avec choix de méthode et schémas mélangés}
\text{T = shuffle(3)}
\text{Rq=Attention ils ne sont peut-être pas dans l'ordre des questions.}
#endif

%%Choix de la méthode%%
%% Type 1-> Une seule méthode est développée %%
#define TYPE 1
#define SOLUTION 1
%% Liste des méthodes et icones %%
\text{list=1,2,3,4}
\text{list2=1,2,3,4}

#include "method.inc"

%%Choix du contexte%%
\text{L=chemise,casquette,veste,pull,pantalon,sweatshirt,sac,foulard,ballon}

\text{A = shuffle(9)}
\text{TQ = shuffle(3)}

%% bornes : prix minimum, pas, nombre de pas
\matrix{M=14.7,2.1,10
10.5,2.1,15
35,6.3,5
14.7,8.2,10
16.8,4.2,8
12.6,2.1,8
21,10.5,6
8.4,2.1,6
6.3,2.1,10
}

\integer{n=\A[1]}
\text{U1= \n < 4 ? une : un}
\text{U2= \n < 4 ? cette : ce }
\text{U3= \n < 4 ? étiquetée : étiqueté}
\text{\obj=\L[\n]}
\real{\vi1=\M[\n;1]+\M[\n;2]*randint(0..\M[\n;3])}
\integer{p1 = random(10,20,30,40,60,70)}
\real{\vp1=\vi1*0.01*\p1}
\integer{m=\TQ[1]}
\integer{ns=\m%3}

\text{L1=Flo a bénéficié d'une remise sur \U1 \obj de \p1 %. Flo a ainsi gagné \vp1 &euro;. Quel était le prix initial de \U2 \obj ?}

\text{L2=Sur le marché \U1 \obj est \U3 à \vi1 &euro;. Le vendeur fait une remise de \vp1 &euro;. Quel est le pourcentage de la remise sur le prix affiché ?}

\text{L3=Le prix affiché d'\U1 \obj est \vi1 &euro;. Pendant les soldes le prix est diminué de \p1 %. Quelle est la valeur de cette réduction ?}

\text{sy1= \ns = 2 ? %:&euro;}
\if{\ns=1}{
  \text{E1=\L1}
  \real{v1=\vi1}
}
\if{\ns=2}{
  \text{E1=\L2}
  \real{v1=\p1}
}
\if{\ns=0}{
  \text{E1=\L3}
  \real{v1=\vp1}
}

\integer{n=\A[2]}
\text{U1= \n < 4 ? une : un}
\text{U2= \n < 4 ? cette : ce }
\text{U3= \n < 4 ? étiquetée : étiqueté}
\text{\obj=\L[\n]}
\real{\vi2=\M[\n;1]+\M[\n;2]*randint(0..\M[\n;3])}
\integer{p2 = random(10,20,30,40)}
\integer{pa2 = 100 + \p2}
\real{\vp2=\vi2*0.01*\p2}
\real{\va2=\vi2+\vp2}
\integer{m=\TQ[2]}
\integer{ns=\m%3}

\text{L4=Le prix d'\U1 \obj a augmenté de \p2 % par rapport à l'an dernier. Quel était le prix l'an dernier d'\U1 \obj dont le prix est  \va2 &euro; cette année ?}
\text{L5=Dans une boutique \U1 \obj est \U3 \vi2 &euro; Hors Taxe et est vendu \va2 &euro; Toute Taxe Comprise. Quel est le pourcentage de la taxe par rapport au prix Hors taxe de \U2 \obj ? }
\text{L6=Le prix d'\U1 \obj a augmenté de \p2 % par rapport à l'an dernier. Quel est le prix d'\U1 \obj qui valait \vi2 &euro; l'an dernier ? }

\text{sy2= \ns = 2 ? %:&euro;}
\if{\ns=1}{
  \text{E2=\L4}
  \real{v2=\vi2}
}
\if{\ns=2}{
  \text{E2=\L5}
  \real{v2=\p2}
}
\if{\ns=0}{
  \text{E2=\L6}
  \real{v2=\va2}
}

\integer{n=\A[3]}
\text{U1= \n < 4 ? une : un}
\text{U2= \n < 4 ? cette : ce }
\text{U3= \n < 4 ? étiquetée : étiqueté}
\text{\obj=\L[\n]}
\real{\vi3=\M[\n;1]+\M[\n;2]*randint(0..\M[\n;3])}
\integer{p3 = random(10,20,30,40)}
\integer{pd3 = 100 - \p3}
\real{\vp3=\vi3*0.01*\p3}
\real{\vd3=\vi3-\vp3}
\integer{m=\TQ[3]}
\integer{ns=\m%3}

\text{L7=Grâce à une remise de \p3 % Dominique a payé \U1 \obj \vd3 &euro;. Quel était l'ancien prix de  \U2 \obj ?}
\text{L8=Dans un magasin Jo paye \vd3 &euro; \U1 \obj dont l'ancien prix était \vi3 &euro;. Quel est le pourcentage de la remise ?}
\text{L9=Camille a acheté \U1 \obj \U3 \vi3 &euro; mais Camille a droit à une réduction de \p3 %. Quel sera le prix final de \U2 \obj ?}

\text{sy3= \ns = 2 ? %:&euro;}
\if{\ns=1}{
  \text{E3=\L7}
  \real{v3=\vi3}
}
\if{\ns=2}{
  \text{E3=\L8}
  \real{v3=\p3}
}
\if{\ns=0}{
  \text{E3=\L9}
  \real{v3=\vd3}
}
%%Création d'un ordre aléatoire pour les énoncés pour solde2, dans l'ordre pour solde1
\text{ListeEn=\E1,\E2,\E3}
\text{ListeVn=\v1,\v2,\v3}
\text{ListeSy=\sy1,\sy2,\sy3}
\text{ListeTy=Pourcentage proportion,Pourcentage d'augmentation,Pourcentage de diminution}
\text{ListeQ=la valeur de la référence, le pourcentage, la valeur de la partie ou la valeur finale}
\text{Er1=\ListeEn[\T[1]]}
\text{Er2=\ListeEn[\T[2]]}
\text{Er3=\ListeEn[\T[3]]}
\text{sr1=\ListeSy[\T[1]]}
\text{sr2=\ListeSy[\T[2]]}
\text{sr3=\ListeSy[\T[3]]}
\text{vr1=\ListeVn[\T[1]]}
\text{vr2=\ListeVn[\T[2]]}
\text{vr3=\ListeVn[\T[3]]}

%% Diagrammes en barres
\text{bar1 = xrange 0,1000
yrange -10,340
text black, 0,330, giant,Pourcentage proportion
text black, 290,330, giant,Pourcentage d'augmentation
text black, 650,330, giant,Pourcentage de diminution
linewidth 1
arc 50,150,16,100,90,180,black
arc 34,150,16,100,270,360,black
arc 34,50,16,100,0,90,black
arc 50,50,16,100,180,270,black
arc 200,40,16,80,90,270,black
rectangle 490,200,570,260, black
arc 340,150,16,100,90,180,black
arc 324,150,16,100,270,360,black
arc 324,50,16,100,0,90,black
arc 340,50,16,100,180,270,black
arc 490,230,16,60,90,270,black
arc 570,195,16,130,0,90,black
arc 586,195,16,130,180,270,black
arc 586,65,16,130,90,180,black
arc 570,65,16,130,-90,0,black

rectangle 850,120,930,200, black
arc 700,150,16,100,90,180,black
arc 684,150,16,100,270,360,black
arc 684,50,16,100,0,90,black
arc 700,50,16,100,180,270,black
arc 850,160,16,80,90,270,black
arc 930,90,16,60,0,90,black
arc 946,90,16,60,180,270,black
arc 946,30,16,60,90,180,black
arc 930,30,16,60,-90,0,black

linewidth 3
rectangle 50,0,130,200, black
rectangle 200,0,280,80, blue
fill 240,5,pink
text black, 0, 110, medium, 100 %
text black, 60, 140, medium, référence
text black, 60, 120, medium, en euros
text blue, 210, 80, medium, partie
text blue, 210, 60, medium, en euros
text black, 180, 50, medium, %
segment 285,-10,285,350, red

rectangle 340,0,420,200, black
rectangle 490,0,570,260, blue
fill 500,5,pink
fill 500,255,pink
text black, 290, 110, medium, 100 %
text black, 350, 160, medium, valeur
text black, 350, 140, medium, initiale
text black, 350, 120, medium, en euros
text black, 470,240, medium, %
text blue, 500, 180, medium, valeur
text blue, 500, 160, medium, finale
text blue, 500, 140, medium,en euros
text black, 495, 250, small, augmentation
text black, 635,140, medium, %

segment 645,-10,645,350, red
rectangle 700,0,780,200, black
rectangle 850,0,930,120, blue
fill 900,5,pink
text black, 650, 110, medium, 100 %
text black, 710, 160, medium, valeur
text black, 710, 140, medium, initiale
text black, 710, 120, medium, en euros
text black, 860, 190, small, diminution
text black, 830,180, medium, %
text blue, 860, 90, medium, valeur
text blue, 860, 70, medium, finale
text blue, 860, 50, medium,en euros
text black, 990,70, medium, %
}
\text{url1 = draw(1000,350
\bar1)}
\text{bar2 = \bar1
text black, 60, 100, medium, \vi1
text blue, 210, 40, medium, \vp1
text black, 150, 50, medium, \p1
text black, 350, 100, medium, \vi2
text black, 440,240, medium, \p2
text blue, 500, 120, medium,\va2
text black, 495, 230, small, \vp2
text black, 605,140, medium, \pa2
text black, 710, 100, medium, \vi3
text black, 860, 170, small, \vp3
text black, 800,180, medium, \p3
text blue, 860, 30, medium,\vd3
text black, 960,70, medium, \pd3
}
\text{url2 = draw(1000,350
\bar2)}

\text{MM=wims(makelist 0 for x=1 to \nb_meth)}
\text{W=}
\text{ETAPE = r1}
\text{COND = 1}
\nextstep{\ETAPE}
\conditions{\COND}

\statement{
  <ol>
  <li>\Er1
<br />
  \if{\W=\trep[1]}{\embed{reply15,3} \sr1}
  </li>
  <li>\Er2
<br />
  \if{\W=\trep[1]}{\embed{reply16,3} \sr2}
  </li>
  <li>\Er3
<br />
  \if{\W=\trep[1]}{\embed{reply17,3} \sr3}
  </li>
  </ol>
  \if{\step=1}{
#include "listmethod.inc"
  }

  \if{\step=2}{
    \if{\W !=\trep[1]}{
      <p>
      La méthode choisie est développée ci-dessous et comporte les réponses aux questions.
      </p>
      \if{\W=\trep[2]}{
        Compléter les schémas suivants.
        <div class="wims_instruction">\Rq</div>
        \special{imageinput \url1, 1000x350, 3
        reply2, 60x240
        reply3, 140x290,1
        reply4, 210x300
        reply5, 350x240
        reply6, 430x100,1
        reply7, 510x110
        reply8, 510x220
        reply9, 590x200,1
        reply10, 710x240
        reply11, 790x160,1
        reply12, 860x170
        reply13, 860x310
        reply14, 950x270,1
      }
    }
    \if{\W=\trep[3]}{
      Compléter les tableaux de proportionnalité.
      <div class="wims_instruction">\Rq</div>
      <table class="wimscenter wimsborder">
      <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
      <tr><th>Tout</th><td>\embed{reply 2,3}</td><td>100 %</td></tr>
      <tr><th>Partie</th><td>\embed{reply 4,3}</td><td>\embed{reply 3,3} %</td></tr>
      </table>

      <table class="wimscenter wimsborder">
      <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
      <tr><th>Valeur initiale</th><td>\embed{reply 5,3}</td><td>100 %</td></tr>
      <tr><th>Augmentation</th><td>\embed{reply 7,3}</td><td>\embed{reply 6,2} %</td></tr>
      <tr><th>Valeur finale</th><td>\embed{reply 8,3}</td><td>\embed{reply 9,2} %</td></tr>
      </table>
      <table class="wimscenter wimsborder">
      <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
      <tr><th>Valeur initiale</th><td>\embed{reply 10,3}</td><td>100 %</td></tr>
      <tr><th>Diminution</th><td>\embed{reply 12,3}</td><td>\embed{reply 11,2} %</td></tr>
      <tr><th>Valeur finale</th><td>\embed{reply 13,3}</td><td>\embed{reply 14,2} %</td></tr>
      </table>
    }
    \if{\W=\trep[4]}{
      <p>Compléter les schémas suivants.</p>
      <div class="wims_instruction">\Rq</div>
      <p>
      Pourcentage proportion<br>
      \special{mathmlinput [\large{ reply2\; \overset{\phantom{xxx}reply3\%\phantom{xxxx}}{\mapsto}\; reply4}],5
reply2
reply3
reply4} </p>
      <p>
      Pourcentage d'augmentation<br>
      \special{mathmlinput [\large{ reply5\; \overset{\phantom{xxx}+ reply6\%\phantom{xxxx}}{\underset{\times reply9 /100}{\mapsto}}\; reply8}],5
reply5
reply6
reply9
reply8} </p>
      <p>
      Pourcentage de diminution<br>
      \special{mathmlinput [\large{ reply10\; \overset{\phantom{xxx}- reply11\%\phantom{xxxx}}{\underset{\times reply14 /100}{\mapsto}}\; reply13}],5
reply10
reply11
reply14
reply13} </p>
    }
  }
}
\if{\step>2}{
  \if{\MM[2]=1}{<img src="\url2">}
  \if{\MM[3]=1}{
    <table class="wimscenter wimsborder">
    <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
    <tr><th>Tout</th><td>\vi1</td><td>100 %</td></tr>
    <tr><th>Partie</th><td>\vp1</td><td>\p1 %</td></tr>
    </table>
    <table class="wimscenter wimsborder">
    <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
    <tr><th>Valeur initiale</th><td>\vi2</td><td>100 %</td></tr>
    <tr><th>Augmentation</th><td>\vp2</td><td>\p2 %</td></tr>
    <tr><th>Valeur finale</th><td>\va2</td><td>\pa2 %</td></tr>
    </table>
    <table class="wimscenter wimsborder">
    <tr><td></td><th>valeurs</th><th>pourcentage</th></tr>
    <tr><th>Valeur initiale</th><td>\vi3</td><td>100 %</td></tr>
    <tr><th>Diminution</th><td>\vp3</td><td>\p3 %</td></tr>
    <tr><th>Valeur finale</th><td>\vd3</td><td>\pd3 %</td></tr>
    </table>
  }
  \if{\MM[4]=1}{
   <ul class="inline">
    <li>\(\large{ \vi1\; \overset{\phantom{xxx} \p1 \%\phantom{xxx}}{\mapsto}\; \vp1})</li>
    <li>\(\large{ \vi2\; \overset{\phantom{xx}+\p2 \%\phantom{xx}}{\underset{\times \pa2/100}{\mapsto}}\; \va2})</li>
    <li>\(\large{ \vi3\; \overset{\phantom{xx}-\p3 \%\phantom{xx}}{\underset{\times \pd3/100}{\mapsto}}\; \vd3})</li>
   </ul>
    }
  }
}

\answer{Méthode}{\var1;\trep}{type=click}{option=nonstop}
\answer{ }{\vi1}{type=default}
\answer{ }{\p1}{type=default}
\answer{ }{\vp1}{type=default}
\answer{ }{\vi2}{type=default}
\answer{ }{\p2}{type=default}
\answer{ }{\vp2}{type=default}
\answer{ }{\va2}{type=default}
\answer{ }{\pa2}{type=default}
\answer{ }{\vi3}{type=default}
\answer{ }{\p3}{type=default}
\answer{ }{\vp3}{type=default}
\answer{ }{\vd3}{type=default}
\answer{ }{\pd3}{type=default}
\answer{ Question 1}{\vr1}
\answer{ Question 2}{\vr2}
\answer{ Question 3}{\vr3}
\condition{Choix de la méthode}{1=1}

\text{W=\var1}
\if{\step=2}{
  \if{\var1=\trep[1]}{
    \text{ETAPE=r15,r16,r17}
  }{
    \text{ETAPE=r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14}
    \for{t=2 to \nb_meth}{
      \if{\W=\trep[\t]}{\text{MM=wims(replace item number \t by 1 in \MM)}}
    }
    \if{\W=\trep[4]}{\text{ETAPE=r2,r3,r4,r5,r6,r8,r9,r10,r11,r13,r14}}
  }
}
\if{\step=3}{
  \if{\W=\trep[1]}{
     \text{ETAPE=}
     \text{MM=wims(replace item number 1 by 1 in \MM)}
   }{
     \text{W=\trep[1]}
     \text{ETAPE=r15,r16,r17}
  }
}
\if{\step=4}{
  \text{ETAPE=}
  \text{MM=wims(replace item number 1 by 1 in \MM)}
}

\solution{
<ol>
<li>réponse : \vr1
<br />Type : \ListeTy[\T[1]]
<br />Question : Rechercher \ListeQ[\TQ[\T[1]]]</li>
<li>réponse : \vr2
<br />Type : \ListeTy[\T[2]]
<br />Question : Rechercher \ListeQ[\TQ[\T[2]]]</li>
<li>réponse : \vr3
<br />Type : \ListeTy[\T[3]]
<br />Question : Rechercher \ListeQ[\TQ[\T[3]]]</li>
</ol>
<img src="\url2">
<p>
Pourcentage proportion
</p>
<div class="wimscenter">
\(\large{ \vi1\; \overset{\phantom{xxx} \p1 \%\phantom{xxx}}{\mapsto}\; \vp1})
</div>
<p>
Pourcentage d'augmentation
</p>
<div class="wimscenter">
\(\large{ \vi2\; \overset{\phantom{xx}+\p2 \%\phantom{xx}}{\underset{\times \pa2/100}{\mapsto}}\; \va2})
</div>
<p>
Pourcentage de diminution
</p>
<div class="wimscenter">
\(\large{ \vi3\; \overset{\phantom{xx}-\p3 \%\phantom{xx}}{\underset{\times \pd3/100}{\mapsto}}\; \vd3})</p>
</div>
}
