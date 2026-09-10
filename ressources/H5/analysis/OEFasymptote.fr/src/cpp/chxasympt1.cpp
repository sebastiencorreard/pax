target=chxasympt1

\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\text{infg=\(-\infty\)}
\text{infd=\(+\infty\)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}

\integer{xmin=-5}
\integer{xmax=5}
\integer{ymin=-5}
\integer{ymax=5}

\integer{a=random(1,2,-1,-2)}
\integer{g=random(1,1,1,2,3)}
\rational{aa=simplify(\a / \g)}
\text{aa=\aa}
\text{aa=wims(replace internal / by , in \aa)}
\integer{a=\aa[1]}
\integer{g=items(\aa)=1?1:\aa[2]}
\text{ta=\g=1?\a:\(\frac{\a}{\g})}
\text{ta=\ta=1?:\ta}
\text{ta=\ta=-1?-:\ta}

\integer{b=random(1..3)}
\integer{c=random(1..5)}
\integer{c2=10*\c}
\integer{d=random(1..5)}
\integer{e=random(1..3)}
\integer{f=random(1..5)}

\text{flist= +\c*10/((\d*x+\e)^2+\f), - \c*10/((\d*x+\e)^2+\f),+\c/(\d*x+\e),+ \c/((\d*x+\e)*(\b*x-\f))}
\text{denlist= (\d*x+\e)^2+\f,(\d*x+\e)^2+\f,\d*x+\e,(\d*x+\e)*(\b*x-\f)}
\text{fslist=}
\text{ftlist=}
\text{ftplist=}
\integer{ind=random(1..4)}
\for{i=1 to 4}{
  \function{fi=\a/\g*x+\b \flist[\i]}
  \function{fi=simplify(\fi)}
  \text{fil=wims(replace internal / by , in \fi)}
  \text{numfi=wims(declosing \fil[1])}
  \text{denfi=wims(declosing \fil[2])}

  \text{den=\denlist[\i]}
  \text{ft=\(\frac{texmath(\numfi)}{texmath(\denfi)})}
  \function{ftp=\i<3?\(\frac{\c2}{texmath(\den)}):\(\frac{\c}{texmath(\den)})}

  \text{fslist=wims(append item \fi to \fslist)}
  \text{ftlist=wims(append item \ft to \ftlist)}
  \text{ftplist=wims(append item \ftp to \ftplist)}
}
\text{textsol=\name_textsol:<br>
\ftlist[1]=\ta x + \b + \ftplist[1]<br>
\ftlist[2]=\ta x + \b - \ftplist[2]<br>
\ftlist[3]=\ta x + \b + \ftplist[3]<br>
\ftlist[4]=\ta x + \b + \ftplist[4]<br>}
\text{name_textsol1=wims(replace internal XXXX by \position[\ind] in \name_textsol1)}
\if{\ind=1 or \ind=2}{
  text{name_textsol1=wims(replace internal XXXX by \position[\ind] in \name_textsol1)}
  \text{textsol=\textsol \name_textsol1, \name_goodexpr \ftlist[\ind].}
  \text{graphasymp=}
}
\if{\ind=3}{
  \text{textsol=\textsol \name_textsol2, \name_goodexpr \ftlist[\ind].}
  \text{graphasymp=dsegment -\e/\d,\ymin,-\e/\d,\ymax,red}
}
\if{\ind=4}{
  \text{textsol=\textsol \name_textsol1, \name_goodexpr \ftlist[\ind].}
  \text{graphasymp=dsegment -\e/\d,\ymin,-\e/\d,\ymax,red
  dsegment \f/\b,\ymin,\f/\b,\ymax,red
  }
}
#include "confparm.inc"
\statement{
<div class="float_right">
\draw{300,300}{
   xrange \xmin, \xmax
   yrange \ymin,\ymax
   parallel \xmin,\ymin,\xmin,\ymax,1,0,\xmax - \xmin +1,grey
   parallel \xmin,\ymin,\xmax,\ymin,0,1,\ymax -\ymin +1,grey
   hline 0,0,black
   arrow  0,0,1,0,6,black
   arrow 0,0,0,1,6,black
   vline 0,0,black
   linewidth 2
   \graphasymp
   plot blue, \fslist[\ind]
   dsegment \xmin,\a/\g*\xmin+\b,\xmax,\a/\g*\xmax+\b,red
 }
</div>
\name_enonce
<div class="wims_question">\name_question
 <ul>
 <li>\embed{reply1,1}</li><li>\embed{reply1,2}</li>
 <li>\embed{reply1,3}</li><li>\embed{reply1,4}</li>
</ul>
</div>
}

\answer{}{\ind;\ftlist}{type = radio}{option=shuffle}
\feedback{1=1}{\textsol}
