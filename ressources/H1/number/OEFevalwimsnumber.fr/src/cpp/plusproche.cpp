target=plusproche
#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{choix=randint(1..3)}
\integer{xmin=randint(0..10)}
\text{nxmin=wims(replace internal . by , in \xmin)}
\if{\choix=1}{
\text{precis=à l'unité}
\integer{xmax=\xmin+1}
\text{nxmax=wims(replace internal . by , in \xmax)}
\text{liste=\xmin,\xmax}
\text{nliste=\nxmin,\nxmax}
\real{xmil=(\xmin+\xmax)/2}
\text{nxmil=wims(replace internal . by , in \xmil)}
\real{xpt=random(\xmin..\xmax)}
\text{nxpt=wims(replace internal . by , in \xpt)}
\if{\xpt<\xmil}{\integer{good=1}
\integer{bad=2}
}{\integer{good=2}
\integer{bad=1}
}
\real{rangemin=\xmin-0.125}
\real{rangemax=\xmax+0.125}
\text{droite=range \rangemin,\rangemax,-3,3
linewidth 2
arrow \rangemin,0,\rangemax,0,40/2,black
linewidth 3
parallel \xmin,-0.5,\xmin,0.5,1,0,2,red
parallel \xmax,-0.5,\xmax,0.5,1,0,2,red
text red,\xmin-0.03,-0.65,medium,\xmin
linewidth 2
parallel \xmin,-0.3,\xmin,0.3,0.1,0,10,red
segment \xmil,-0.3,\xmil,0.3,blue
crosshair \xpt,0,black
text black,\xpt-0.03,0.6,medium,\xpt
text blue,\xmil-0.03,-0.4,medium,\xmil
text red,\xmax-0.03,-0.65,medium,\xmax
}
}
\if{\choix=2}{
\text{precis=au dixième}
\real{deci=randint(0..9)/10}
\real{xmin=\xmin+\deci}
\text{nxmin=wims(replace internal . by , in \xmin)}
\real{xmax=\xmin+0.1}
\text{nxmax=wims(replace internal . by , in \xmax)}
\text{liste=\xmin,\xmax}
\text{nliste=\nxmin,\nxmax}
\real{xmil=(\xmin+\xmax)/2}
\text{nxmil=wims(replace internal . by , in \xmil)}
\real{xpt=random(\xmin..\xmax)}
\text{nxpt=wims(replace internal . by , in \xpt)}
\if{\xpt<\xmil}{\integer{good=1}
\integer{bad=2}
}{\integer{good=2}
\integer{bad=1}
}
\real{rangemin=\xmin-0.0125}
\real{rangemax=\xmax+0.0125}
\text{droite=
range \rangemin,\rangemax,-3,3
linewidth 2
arrow \rangemin,0,\rangemax,0,40/2,black
linewidth 3
parallel \xmin,-0.5,\xmin,0.5,1,0,2,red
parallel \xmax,-0.5,\xmax,0.5,1,0,2,red
text red,\xmin-0.003,-0.65,medium,\xmin
linewidth 2
parallel \xmin,-0.3,\xmin,0.3,0.01,0,10,red
segment \xmil,-0.3,\xmil,0.3,blue
crosshair \xpt,0,black
text black,\xpt-0.003,0.6,medium,\xpt
text blue,\xmil-0.003,-0.4,medium,\xmil
text red,\xmax-0.003,-0.65,medium,\xmax
}
}

\if{\choix=3}{
\text{precis=au centième}
\real{deci=randint(0..9)/10}
\real{centi=randint(0..9)/100}
\real{xmin=\xmin+\deci+\centi}
\text{nxmin=wims(replace internal . by , in \xmin)}
\real{xmax=\xmin+0.01}
\text{nxmax=wims(replace internal . by , in \xmax)}
\text{liste=\xmin,\xmax}
\text{nliste=\nxmin,\nxmax}
\real{xmil=(\xmin+\xmax)/2}
\text{nxmil=wims(replace internal . by , in \xmil)}
\real{xpt=random(\xmin..\xmax)}
\text{nxpt=wims(replace internal . by , in \xpt)}
\if{\xpt<\xmil}{\integer{good=1}
\integer{bad=2}
}{\integer{good=2}
\integer{bad=1}
}
\real{rangemin=\xmin-0.00125}
\real{rangemax=\xmax+0.00125}
\text{droite=
range \rangemin,\rangemax,-3,3
linewidth 2
arrow \rangemin,0,\rangemax,0,40/2,black
linewidth 3
parallel \xmin,-0.5,\xmin,0.5,1,0,2,red
parallel \xmax,-0.5,\xmax,0.5,1,0,2,red
text red,\xmin-0.0003,-0.65,medium,\xmin
linewidth 2
parallel \xmin,-0.3,\xmin,0.3,0.001,0,5,red
parallel \xmil+0.001,-0.3,\xmil+0.001,0.3,0.001,0,4,red
segment \xmil,-0.3,\xmil,0.3,blue
crosshair \xpt,0,black
text black,\xpt-0.0003,0.6,medium,\xpt
text blue,\xmil-0.0003,-0.6,medium,\xmil
text red,\xmax-0.0003,-0.65,medium,\xmax
}
}
\text{url=draw(400,200
\droite)}
\statement{\name_enonce[1] \(\xpt\) \name_enonce[2]:
<div class="wimscenter"><img src="\url" alt=""></div>
\name_question[1] \(\xmin\) \name_question[2] \(\xmax\) \name_question[3]?
<div class="wimscenter">\embed{reply1}</div>}
\answer{}{\good;\liste}{type=click}

\feedback{1=1}{<div class="macss">\name_feed[1]:<p>
\(\xmin\) \name_feed[2] \precis \name_feed[3]
<span style="color:red"><b>\name_feed[4]</b></span> \name_feed[6] \(\xpt\).
</p><p>
\(\xmax\) \name_feed[2] \precis \name_feed[3]
<span style="color:red"><b>\name_feed[5]</b></span> \name_feed[6] \(\xpt\).
</p>
\name_feed1[1] \(\xpt\) \name_feed1[2] <span style="color:red"><b>\name_feed1[3]</b></span>
\name_feed1[4] \(\liste[\good]\) \name_feed1[5] \(\liste[\bad]\), \name_feed1[6] <p>
\(\liste[\good]\) \name_feed1[7] <span style="color:red"><b>\name_feed1[8] \precis</b></span>
\name_feed1[9] \(\xpt\).</div>}
