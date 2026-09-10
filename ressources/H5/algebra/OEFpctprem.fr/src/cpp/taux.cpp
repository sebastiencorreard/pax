target=taux1 taux2 taux3 taux4 taux5

\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{100}

\text{verbe=augmente,baisse}
\text{evol=hausse,baisse}
\integer{k=randint(1,2)}
#define TITLE Taux d'évolution
#if defined TARGET_taux1 || defined TARGET_taux2 || defined TARGET_taux3

\integer{av=randint(1000..3000)}
\integer{t=randint(10..90)}
\rational{cm=\k=1?1+\t/100:1-\t/100}
\text{cmsol=\k=1?1+\frac{\t}{100}:1-\frac{\t}{100}}
\rational{nv=\av*\cm}
\real{nv2=\nv}
\real{nv1=round(10*\nv)/10}
\integer{nv0=round(\nv)}
\text{av_aff=slib(numeration/ecriturenombre \av,tex)}
\text{nv2_aff=slib(numeration/ecriturenombre \nv2,comma tex)}
\text{nv1_aff=slib(numeration/ecriturenombre \nv1,comma tex)}

# if defined TARGET_taux1
\title{TITLE 1}
\text{tsol=On peut multiplier la valeur initale \(\av_aff\) par le coefficient multiplicateur \(\cmsol\)
  qui correspond à la \evol[\k] de <span class="nowrap">\(\t\) %.</span>
  <br>
  Le nouveau prix est \(\av \times \left(\cmsol\right)\) ce qui donne \(\nv2_aff\) euros.}
# endif
# if defined TARGET_taux2
\title{TITLE 2}
\text{signe=\k=1? :-}
\text{tsol=Rappel du cours&nbsp;:
    <p>Le taux d'évolution (ou taux de variation), en pourcentage, d'une grandeur qui évolue de AV (ancienne valeur)
      à NV (nouvelle valeur) est <span class="nowrap">\(t\) %</span>, avec \(t= \frac{NV-AV}{AV} \times 100\).<br>
    <i>Remarque</i> : \(t>0\) lorsqu'il s'agit d'une augmentation et \(t<0\)
    lorsqu'il s'agit d'une diminution.
    </p>
    <p class="spacer">
    \(\frac{\nv2_aff-\av_aff}{\av_aff} \times 100 = \signe \t\)<br>
    Le prix a subi une \evol[\k] de <span class="nowrap">\(\t\) %.</span>
    </p>
  }
# endif
# if defined TARGET_taux3
  \title{TITLE 3}
  \text{tsol=On peut diviser la nouvelle valeur \(\nv1_aff\) par le coefficient multiplicateur \(\cmsol\)
  qui correspond à la \evol[\k] de <span class="nowrap">\(\t\) %.</span>
    <br>
    Le prix initial est \(\dfrac{\nv1_aff}{\cmsol}\) ce qui donne \(\av_aff\) euros.}
# endif
\statement{
<p>
# if defined TARGET_taux1
    Un bien coûte \(\av_aff\) euros.<br>
    Il \verbe[\k] de <span class="nowrap">\(\t\) %.</span>
  </p><p>
    <label for="reply1">Quel est son nouveau prix ?</label>
  </p>
  <div class="wimscenter">\embed{reply1}euros</div>
  <div class="wims_instruction"> Donner la valeur exacte.</div>
  }

  \answer{Réponse : }{\reponse}{type=numeric} la réponse attendue est \nv
  \real{di=abs(\reponse-\nv)}
  \text{testar=\di<=1 and \di<>0 ? 1:0}
  \condition{Le raisonnement semble correct&nbsp;}{\di<=1}{weight=19}
  \condition{Valeur exacte donnée&nbsp;}{\di=0}{weight=1}
  \feedback{\testar=1}{Vous avez sans doute effectué le bon calcul
    mais c'est la valeur exacte qui est demandée.}
# endif
# if defined TARGET_taux2
    Un bien coûte \(\av_aff\) euros.<br>
    Son prix passe à \(\nv2_aff\) euros.
  </p>
  <div class="wimscenter"><label for="reply1">
  Il a subi une</label> \embed{reply1} <label for="reply2">de</label> <span class="nowrap">\embed{reply2,4} %.</span>
  </div>
  }
  \answer{évolution}{\k;\evol}{type=menu}{weight=1}
  \answer{taux}{\t}{type=numexp}{weight=9}
# endif
# if defined TARGET_taux3
    Un bien coûte \(\nv1_aff\) euros, après avoir subi une \evol[\k] de <span class="nowrap">\(\t\) %.</span>
  </p><p>
    <label for="reply1">Quel était son prix initial&nbsp;?</label>
  </p>
  <div class="wimscenter">\embed{reply1,10} euros.</div>
  <div class="wims_instruction">Arrondir à l'euro.</div>
  }

  \answer{Réponse : }{\reponse}{type=numeric} la réponse attendue est \av
  \text{testentier=\reponse=round(\reponse) ? 1:0}
  \real{di=abs(\reponse-\av)}
  \text{testar=\di<=1 and \di<>0 ? 1:0}
  \condition{Bonne réponse&nbsp;}{\di<=1}{weight=19}
  \condition{Arrondi demandé respecté&nbsp;}{\di=0}{weight=1}
  \feedback{\testentier=0}{Attention : la réponse doit être un nombre entier. }
  \feedback{\testar=1}{Vous avez sans doute effectué le bon calcul mais vous avez mal arrondi le résultat.}
# endif

\solution{\tsol}
#endif

#if defined TARGET_taux4
\title{TITLE 4}

\integer{n1=randint(2..5)}
\text{listpartie1=son double,son triple,son quadruple,son quintuple,son sextuple}
\text{listpartie1b=doublé,triplé,quadruplé,quintuplé,sextuplé}
\text{listpartie2=sa moitié,son quart,son dixième}
\text{div=2,4,10}
\integer{t1=\n1*100}
\integer{cm1h=1+\n1}
\integer{cm1b=1-\n1}
\text{partie1V=\listpartie1[\n1-1]}
\text{partie1F=\listpartie1[\n1]}

\integer{alea=randint(1..3)}
\integer{n2=\div[\alea]}
\integer{t2=100/\n2}
\text{partie2=\listpartie2[\alea]}
\rational{cm2h=1+\t2/100}
\text{cm2h_aff=texmath(\cm2h)}
\rational{cm2b=1-\t2/100}
\text{cm2b_aff=texmath(\cm2b)}
\text{augm=Pour augmenter une valeur \(v\) de}
\text{dimi=Pour diminuer une valeur \(v\) de}
\text{mult=il suffit de multiplier \(v\) par}
\text{divi=il suffit de diviser \(v\) par}
\text{ajout=il suffit d'ajouter à \(v\)}
\text{ret=il suffit de retrancher à \(v\)}
\text{hausse=Un prix \(p\) peut subir une hausse de}
\text{baisse=Un prix \(p\) peut subir une baisse de}
\text{notEqual=et ceci n'est pas égal à}

\if{\t2=50}
  {\text{aff=\dimi \t2&nbsp;% &#44; \divi <span class="nowrap">\(\n2\).</span>,1,<span class="nowrap">\(v \times \left(1-\frac{\t2}{100}\right) = \frac{v}{\n2} \).</span>}}
  {\text{aff=\dimi \t2&nbsp;% &#44; \divi <span class="nowrap">\(\n2\).</span>,2,\(v \times \left(1-\frac{\t2}{100}\right) = v \times \cm2b_aff \) \notEqual <span class="nowrap">\(\frac{v}{\n2}\).</span>}}

\matrix{data=\augm 100&nbsp;% &#44; \mult <span class="nowrap">\(2\).</span>,1,<span class="nowrap">\(v \times \left( 1 + \frac{100}{100}\right) = v \times 2\).</span>
\dimi 100&nbsp;% &#44; \divi <span class="nowrap">\(2\).</span>,2,\(v \times \left( 1 - \frac{100}{100}\right) = 0\) \notEqual <span class="nowrap">\(\frac{v}{2}\).</span>
\augm \t1&nbsp;% &#44; \mult <span class="nowrap">\(\n1\).</span>,2,\(v \times \left( 1 + \frac{\t1}{100}\right) = v \times \cm1h\) \notEqual <span class="nowrap">\(v \times \n1\).</span>
\augm \t1&nbsp;% &#44; \mult <span class="nowrap">\(\cm1h\).</span>,1,<span class="nowrap">\(v \times \left( 1 + \frac{\t1}{100}\right) = v \times \cm1h\).</span>
\augm \t1&nbsp;% &#44; \ajout \partie1V.,1,<span class="nowrap">\(v + \left(\frac{\t1}{100}\right) \times v = v + \n1 v \).</span>
\augm \t1&nbsp;% &#44; \ajout \partie1F.,2,\(v + \left(\frac{\t1}{100}\right) \times v = v + \n1 v \) \notEqual <span class="nowrap">\(v + \cm1h v\).</span>
\augm \t2&nbsp;% &#44; \ajout \partie2.,1,<span class="nowrap">\(v + \left(\frac{\t2}{100}\right) \times v = v + \frac{1}{\n2} v \).</span>
\augm \t2&nbsp;% &#44; \mult <span class="nowrap">\(\cm2h_aff\).</span>,1,<span class="nowrap">\(v \times \left( 1 + \frac{\t2}{100}\right) = v \times \cm2h_aff\).</span>
\augm \t2&nbsp;% &#44; \mult <span class="nowrap">\(\cm2b_aff\).</span>,2,\(v \times \left( 1 + \frac{\t2}{100}\right) = v \times \cm2h_aff\) \notEqual <span class="nowrap">\(v \times \cm2b_aff\).</span>
\dimi \t2&nbsp;% &#44; \ret \partie2.,1,<span class="nowrap">\(v - \left(\frac{\t2}{100}\right) \times v = v - \frac{1}{\n2} v \).</span>
\aff
\dimi \t2&nbsp;% &#44; \mult <span class="nowrap">\(\cm2b_aff\).</span>,1,<span class="nowrap">\(v \times \left(1-\frac{\t2}{100}\right) = v \times \cm2b_aff \).</span>
\hausse 100&nbsp;%.,1,\(p \times \left( 1 + \frac{100}{100}\right) = p \times 2\) et le prix \(p\) a alors doublé.
\baisse 100&nbsp;%.,1,\(p \times \left( 1 - \frac{100}{100}\right) = 0\) et le prix \(p\) est devenu nul.
\hausse \t1&nbsp;%.,1,\(p \times \left( 1 + \frac{\t1}{100}\right) = p \times \cm1h\) et le prix \(p\) a alors \listpartie1b[\n1].
\baisse \t1&nbsp;%.,2,\(p \times \left( 1 - \frac{\t1}{100}\right) = p \times (\cm1b)\) ce qui n'est pas possible.
}


\integer{alearow=randint(1..rows(\data))}
\text{cedata=\data[\alearow;]}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\text{lstrep=Vrai,Faux}
\text{lstrep2=vraie,fausse}
\if{\alearow<=12}{\text{intro=Soit \(v\) un nombre non nul.}}{\text{intro=Soit \(p\) un nombre strictement positif.}}
\text{sol=<p>\intro</p><p>\quest</p>
<p>Cette affirmation est <b>\lstrep2[\cedata[2]]</b>, en effet, \cedata[3]</p>}
\statement{
<p>\intro</p>
<p>
  Cliquer sur la bonne réponse :
</p>
<div class="wimscenter"> \quest</div>
<div class="wimscenter spacer">\embed{reply1}</div>
}
\answer{}{\rep;\lstrep}{type=radio}
\solution{\sol}
#endif
#if defined TARGET_taux5
\title{TITLE 5}
\text{lsttaux=}
\text{lstcoef=}
\text{lstsol=}
\for{i=1 to 2}{
 \integer{t=randint(5..95)}
 \text{taux=augmentation de \t&nbsp;%}
 \text{lsttaux=wims(append item \taux to \lsttaux)}
 \real{c=1+\t/100}
 \text{lstcoef=wims(append item \c to \lstcoef)}
 \text{solu=\(\c= 1 + \frac{\t}{100}\)}
 \text{lstsol=wims(append item \solu to \lstsol)}
 \text{taux=baisse de \t&nbsp;%}
 \text{lsttaux=wims(append item \taux to \lsttaux)}
 \real{c=1-\t/100}
 \text{lstcoef=wims(append item \c to \lstcoef)}
 \text{solu=\(\c= 1 - \frac{\t}{100}\)}
 \text{lstsol=wims(append item \solu to \lstsol)}
}
\integer{t=randint(0,25,50)+randint(1..4)*100}
 \text{taux=augmentation de \t&nbsp;%}
 \text{lsttaux=wims(append item \taux to \lsttaux)}
 \real{c=1+\t/100}
 \text{lstcoef=wims(append item \c to \lstcoef)}
 \text{solu=\(\c= 1 + \frac{\t}{100}\)}
 \text{lstsol=wims(append item \solu to \lstsol)}

\text{matrixTab=Coefficient<br> multiplicateur,Évolution}
\for{gg=1 to 5}
  {\text{matrixTab=\matrixTab;\lstcoef[\gg],\lstsol[\gg] <br> correspond à une \lsttaux[\gg]}
  }
\text{tabSol=slib(text/matrixhtml [\matrixTab],1 center wimsborder,TH=[1;])}
\statement{<p>
  Associer chaque coefficient multiplicateur à l'évolution correspondante&nbsp;:
</p>
<div class="wimscenter">\embed{reply1,50x80x200}</div>
}
\answer{}{\lstcoef;\lsttaux}{type=correspond}
\solution{<div class="table-scroll">\tabSol</div>}
#endif
