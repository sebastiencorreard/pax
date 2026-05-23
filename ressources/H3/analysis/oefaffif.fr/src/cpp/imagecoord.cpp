target=imagecoord1 imagecoord2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=randint(1..4)}
\integer{b=randint(1..5)}
\integer{c=random(-1,1)}
\if{\c=1}{
  \real{x1=(-7-\b)/\a}
  \real{x2=(7-\b)/\a}
}{
  \real{x1=(-7+\b)/\a}
  \real{x2=(7+\b)/\a}
}
\real{x1=max(\x1,-7)}
\real{x2=min(\x2,7)}
\integer{x=random(\x1..\x2)}
\integer{d=\c*\a}
\integer{y=\d*\x+\b}
\function{g=simplify(\d*x +  \b)}
\text{taille=200}
#if defined TARGET_imagecoord1
\text{dessinvar=fcircle \x,0,6,green}
\text{dessinfeed= dsegment green,\x,0,\x,\y,0,\y
  fcircle 0,\y,6,green
  text green,0.3,\y,medium,y}
#endif
#if defined TARGET_imagecoord2
\text{dessinvar=fcircle 0,\y,6,green}
\text{dessinfeed=dpolyline  green,\x,0,\x,\y,0,\y
  fcircle \x,0,6,green
  text green,\x+0.3,+1,medium,x}
#endif
\text{dessin =
  xrange -7.2,7.2
  yrange -7.2,7.2
  parallel -7,-7,7,-7,0,1,16, grey
  parallel -7,-7,-7,7,1,0,16, grey
  hline 0,0,black
  arrow 0,0,1,0,8, black
  arrow 0,0,0,1,8, black
  text black,7-0.5,+0.8,medium,x
  text black,-0.5,7,medium,y
  vline 0,0,black
  \dessinvar
  linewidth 2
  plot blue, \g
}
\text{A=draw(\taille,\taille
\dessin)}
#if defined TARGET_imagecoord1
\text{PP=slib(draw/convpixel 0,\y,\taille,\taille,-7.2,7.2,-7.2,7.2,0,pixels)}
#endif
#if defined TARGET_imagecoord2
\text{PP=slib(draw/convpixel \x,0,\taille,\taille,-7.2,7.2,-7.2,7.2,0,pixels)}
#endif
\text{Px=\PP[1]}
\text{Py=\PP[2]}
\statement{\name_enonce
#if defined TARGET_imagecoord1
\(y = g(\x)\).
#endif
#if defined TARGET_imagecoord2
\(f(x)=\y\).
#endif
 <div class="wimscenter">\embed{reply1} </div>
}
\answer{}{\A;point,\Px,\Py}{type=coord}
\feedback{ \result1 = -1 }{ \name_feed
  <p class="wimscenter">
  \draw{ \taille,\taille }{
  \dessin
  \dessinfeed
} </p>}
