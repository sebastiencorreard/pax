target=ajustement
#include "lang_titles.inc"

\language{fr}
\range{-5..5}
\author{Jean-Jacques, Kamdem; Bernadette, Perrin-Riou}
\email{bpr@math.u-psud.fr}
\computeanswer{yes}
\format{html}
\precision{10000}

\real{i=randint(2..4)}
\real{j=randint(1..4)}
\real{s=random(3..5)}

\text{listeg= y*x + z, \s*x^2 + y*x + z,exp(y*x + z), ln((y*x + z))}
\text{choix=randint(1..items(\listeg))}
\real{i=\choix<=3 ? \i*random(1,-1)}
\text{g=item(\choix,\listeg)}
\integer{N=100}

\text{a=slib(stat/random \N,0,4,R)}
\text{c=slib(stat/random \N,-0.8,0.8,R)}
\text{d=slib(stat/random \N,-0.8,0.8,R)}

\text{liste=}
\text{liste1=}
\text{dessin=}
\for{u=1 to \N}{
  \text{xa=item(\u,\a)}
  \text{xc=item(\u,\c)}
  \text{yd=item(\u,\d)}
  \real{yb=evalue(\g,x=\xa,y=\i+(\xc),z=\j+(\yd))}
  \text{liste=\liste,\yb}
  \if{\choix=2}{\real{yb1=\yb-\s*(\xa)^2}
    \text{liste1=\liste1,\yb1}}
    \text{liste=wims(nonempty item \liste)}
    \text{liste1=wims(nonempty item \liste1)}
    \text{dessin=\dessin
disk \xa,\yb,3, blue }}
    \text{listes=wims(sort numeric items \liste)}
    \real{borne1=item(1,\listes)}
    \real{borne1=min(\borne1,-1)}
    \real{borne2=item(-1,\listes)}

Determination de l'ajustement affine selon moindre carré
\text{b=\choix=1? \liste}
\text{b=\choix=2? \liste1}
\text{b=\choix=3? wims(values log(x) for x in \liste)}
\text{b=\choix=4? wims(values exp(x) for x in \liste)}

\matrix{covlin=row(1,slib(stat/covariance [\a],[\b]))}
\matrix{mcovlin=row(1,\covlin)}
\text{covlin=item(2,\mcovlin)}
\text{varlinx=item(1,\mcovlin)}

\text{moylinx=item(1,slib(stat/arithmean [\a]))}
\text{moyliny=item(1,slib(stat/arithmean [\b]))}
\real{palin=\covlin/\varlinx}
\real{pblin=\moyliny-(\palin)*(\moylinx)}

\function{f=\choix=1 ? \palin*x + \pblin}
\function{f=\choix=2? \s*x^2 + (\palin)*x + (\pblin)}
\function{f=\choix=3? exp(\palin*x + \pblin)}
\function{f=\choix=4? log(\palin*x + \pblin)}

#include "lang.inc"
\text{borne1= \choix=3? -\borne2/5}
\statement{\name_instruction0:
<div class="wimscenter">
\draw{200,200}{xrange -0.5,5
yrange \borne1-1,\borne2+0.5
hline 0,0,black
vline 0,0, black
\dessin
}
</div>
<div class="wims_question">
<label for="reply1">\name_instruction[1]</label> \embed{reply 1} \name_instruction[2] .
</div>
}
\answer{\name_prompt}{\choix;\question}{type=click}

\text{type=item(\choix,\question)}
\feedback{1=1}{\name_feedback:
<div class="wimscenter">\draw{200,200}{xrange -0.5,5
  yrange \borne1-1,\borne2+0.5
  hline 0,0,black
  vline 0,0, black
  plot red,\f
  \dessin}
</div>
}
