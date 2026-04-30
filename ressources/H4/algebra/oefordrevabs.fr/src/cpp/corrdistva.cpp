target=corrdistva
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

\text{taille=45x100x100}
\text{donnees=slib(draw/repere 800,30,10,-12,12,-1,0,1,0,black,white)}

\text{tmp=row(1,\donnees)}
%%coordonnéées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}

\integer{Ox=0}
\integer{ex=1}

%% On prépare le dessin
\text{image= xrange -16,16
  yrange -3,3
  hline 0,0,red
  arrow 15,0,16,0,15,red
  parallel -15,-0.2,-15,0.2,1,0,5,blue
  parallel -10,-0.4,-10,0.4,5,0,5,blue
  parallel -9,-0.2,-9,0.2,1,0,4,blue
  parallel -4,-0.2,-4,0.2,1,0,4,blue
  parallel 1,-0.2,1,0.2,1,0,4,blue
  parallel 6,-0.2,6,0.2,1,0,4,blue
  parallel 11,-0.2,11,0.2,1,0,5,blue
  text red,-0.1,1.5,medium,O
}

\integer{xmin=-15}
\integer{xoffset=4}
\text{pt=A,B,C,D,E,F}
\integer{nbpt=items(\pt)}
\integer{pty=\Oy}
\text{listx=}
\text{listpt=}
\text{listquest=}
\text{listrep=}
\text{indlist=shuffle(\nbpt)}

%% on choisit les points et on les met sur le dessin
\for{i=1 to \nbpt/2}
{
\integer{x=random(\xmin+(\i-1)*\xoffset .. \xmin+\i*\xoffset-1)}
\integer{x2=-1*(\x)}
\integer{ptx=\Ox+\x*\ex}
\integer{ptx2=\Ox+\x2*\ex}
\text{image=\image
 text red,\ptx-0.1,1.5,medium,\pt[\indlist[\i]]
 text red,\ptx-0.1,-1,medium,\x
 segment \ptx,-0.2,\ptx,0.2,red
 text red,\ptx2-0.1,1.5,medium,\pt[\indlist[\i+\nbpt/2]]
 text red,\ptx2-0.1,-1,medium,\x2
 segment \ptx2,-0.2,\ptx2,0.2,red
}
\text{listx=wims(append item \x to \listx)}
\text{listpt=wims(append item \ptx to \listpt)}
\text{questxlist=\(texmath(abs(x-(\x)))),\(texmath(abs((\x)-x))),\(texmath(abs(-x+(\x)))),\(texmath(abs(-(\x)+x)))}
\text{questx=randomitem(\questxlist)}
\text{listquest=wims(append item \questx to \listquest)}
\text{repx=M\pt[\indlist[\i]],\pt[\indlist[\i]]M}
\text{listrep=wims(append item randomitem(\repx) to \listrep)}

\text{listx=wims(append item \x2 to \listx)}
\text{listpt=wims(append item \ptx2 to \listpt)}
\text{questxlist=\(texmath(abs(x-(\x2)))),\(texmath(abs((\x2)-x))),\(texmath(abs(-x+(\x2)))),\(texmath(abs(-(\x2)+x)))}
\text{questx=randomitem(\questxlist)}
\text{listquest=wims(append item \questx to \listquest)}
\text{repx=M\pt[\indlist[\i+\nbpt/2]],\pt[\indlist[\i+\nbpt/2]]M}
\text{listrep=wims(append item randomitem(\repx) to \listrep)}
}
#include "css.inc"
\text{size=\confparm1=1 ? :x-large}
\statement{
<div class="rm spacer">
  \name_enonce <span class="nowrap">\(\mathrm{O}\).</span>
  <div class="wimscenter">
    \draw{800,64}{\image}
  </div>
  \name_question
</div>
<div class="wimscenter">
 \embed{reply 1,\taille}
</div>
}

\reply{Correspondance objet/equation}{\listrep;\listquest}{type=correspond}{option=split}

\solution{
<div class="flex_box">
    \for{kk=1 to 6}{
    <div class="wimscenter wims_question">
      <div>\listrep[\kk] =  \listquest[\kk]</div>
    </div>}
</div>
}

\hint{
<div class="hint">
Pour tous réels \(x\) et <span class="nowrap">\(y\),</span> <br>
\(\mathrm{d}\left(x,y\right)= \left|x - y\right|\)<br>
\(\phantom{\mathrm{d}\left(x,y\right)}= \left|y - x\right|\)<br>
\(\phantom{\mathrm{d}\left(x,y\right)}=\mathrm{d}\left(y,x\right)\)
</div>}
