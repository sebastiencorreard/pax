target=propprop1 propprop2 propprop3 propprop4 propprop5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{10000}
\css{<style>
.feedback{margin-right:0}
</style>
}
#define TITLE Proportion de proportion
\text{data=Dans un magasin,des articles,pantalons,pour les filles,pantalons pour fille,des articles du magasin,
  Chez un fleuriste,des fleurs, roses, rouges,roses rouges,des fleurs du fleuriste,
  Dans une confiserie,des bonbons, sucettes,à l'anis,sucettes à l'anis,des bonbons de la confiserie}
\integer{p1=randint(20,30,40,45,60,75,80)}
\integer{p2=randint(20,30,40,45,50,60,75,80)}
\real{p=\p1*\p2/100}
\real{pp=\p/100}
\real{pp2=\p2/100}
\real{pp1=\p1/100}
\text{cedata=randomrow(\data)}
\text{tintro=blablabla}

#if defined TARGET_propprop1 || defined TARGET_propprop2 || defined TARGET_propprop3
# if defined TARGET_propprop1
\title{TITLE 1}
\text{tintro=\cedata[1], \p1 % \cedata[2] sont des \cedata[3]. <br>
  Parmi les \cedata[3], \p2 % sont \cedata[4].}
\text{tintro2=Quelle est la proportion, en pourcentage, des \cedata[5]
  parmi l'ensemble \cedata[6]}
\real{rep=\p}
\text{tfeed=Il s'agit de \p2 % de \p1 % du total.<br>
  Calcul : \(\frac{\p1}{100} \times \frac{\p2}{100} \times 100=\p\)<br>
  La proportion des \cedata[5] parmi l'ensemble \cedata[6] est de \p&nbsp;%.}
# endif

# if defined TARGET_propprop2
\title{TITLE 2}
\text{tintro=\cedata[1], \p1 % \cedata[2] sont des \cedata[3]. <br>
  Parmi l'ensemble \cedata[6], \p % sont des \cedata[5].}
\text{tintro2=Quelle est la proportion, en pourcentage, des \cedata[5] parmi
  l'ensemble des \cedata[3]}
\real{rep=\p2}
\text{tfeed=Soit \(p\) la proportion cherchée.<br>
  D'après l'énoncé, \(p \times \frac{\p1}{100}=\frac{\p}{100}\) <br>
  d'où \(p =\frac{\p}{\p1}\) <br>
  \(p =\pp2\) <br>
  \(p=\frac{\p2}{100}\)<br>
  La proportion des \cedata[5] parmi l'ensemble des \cedata[3] est de \p2&nbsp;%.}

# endif

#if defined TARGET_propprop3
\title{TITLE 3}
\text{tintro=\cedata[1], parmi l'ensemble des \cedata[3], \p2 % sont des \cedata[5]. <br>
  Parmi l'ensemble \cedata[6], \p % sont des \cedata[5].}
\text{tintro2=Quelle est la proportion, en pourcentage, des \cedata[3]
  parmi l'ensemble \cedata[6]}
\real{rep=\p1}
\text{tfeed=Soit \(p\) la proportion cherchée.<br>
  D'après l'énoncé, \(p \times \frac{\p2}{100}=\frac{\p}{100}\) <br>
  d'où \(p = \frac{\p}{\p2}\) <br>
  \(p=\pp1\) <br>
  \(p=\frac{\rep}{100}\)<br>
  La proportion, en pourcentage, des \cedata[3] parmi l'ensemble \cedata[6] est de \p1&nbsp;%.}
#endif

\statement{
\tintro <p><label for="reply1">\tintro2&nbsp;?</label></p>
<div class="wimscenter">\embed{reply1,4}%</div>
}
\answer{}{\rep}{type=numeric}
\feedback{\reply1<>\rep}{<p class="feedback">\tfeed</p>}
#endif


#if defined TARGET_propprop4 || defined TARGET_propprop5
# if defined TARGET_propprop4
\title{TITLE 4}
# else
\title{TITLE 4bis (autre solution)}
# endif

\text{data=Dans un club de hip-hop, filles, garçons, ont plus de 20 ans, d'adhérents de plus de 20 ans dans le club, de plus de 20 ans dans le club,
  Dans un bouquet composé de roses et d'oeillets, roses, oeillets, sont rouges, des fleurs rouges dans le bouquet,rouges dans le bouquet,
  Dans une armoire contenant des pantalons et des jupes, pantalons, jupes,sont rouges, des vêtements rouges dans l'armoire,rouges dans l'armoire}
\text{cedata=randomrow(\data)}
\integer{p1=randint(20,30,40,45,60,75,80)}
\integer{p2=100-\p1}
\integer{p3=randint(20,30,40,45,50,60,75,80)}
\integer{p4=randint(20,30,40,45,50,60,75,80)}
\real{rep=(\p1*\p3+\p2*\p4)/100}
\real{x1=\p1*\p3/100}
\real{x2=\p2*\p4/100}

#if defined TARGET_propprop5
\text{\solbis=
 La proportion des \cedata[2] est \p1 %, donc celle des \cedata[3] est \p2&nbsp;%.<br>
 La proportion des \cedata[2] \cedata[6] est <span class="nowrap">\(\frac{\p1}{100} \times \frac{\p3}{100}=\frac{\x1}{100}\).</span><br>
 La proportion des \cedata[3] \cedata[6] est <span class="nowrap">\(\frac{\p2}{100} \times \frac{\p4}{100}=\frac{\x2}{100}\).</span><br>
 Donc la proportion \cedata[5] est \(\frac{\x1}{100}+\frac{\x2}{100}=\frac{\rep}{100}\) soit \rep&nbsp;%.
}
#endif
\statement{
<p>
\cedata[1], il y a \p1 % de \cedata[2].<br>
\p3 % des \cedata[2] et \p4 % des \cedata[3] \cedata[4].</p><p>
  <label for="reply1">Quelle est la proportion, en pourcentage, \cedata[5] ?</label>
</p>
<div class="wimscenter">\embed{reply1}%</div>
}
\answer{}{\rep}{type=numeric}


#if defined TARGET_propprop4
\feedback{\reply1<>\rep}{<p class="feedback">
  La proportion des \cedata[2] est \p1 %, donc celle des \cedata[3] est \p2&nbsp;%.<br>
  La proportion des \cedata[2] \cedata[6] est <span class="nowrap">\(\frac{\p1 \times \p3}{100}\) %</span> soit \x1&nbsp;%.<br>
  La proportion des \cedata[3] \cedata[6] est <span class="nowrap">\(\frac{\p2 \times \p4}{100}\) %</span> soit \x2&nbsp;%.<br>
  Donc la proportion, en pourcentage, \cedata[5] est \x1+\x2 soit \rep&nbsp;%.</p>}
#else
\solution{\solbis}
#endif

#endif
