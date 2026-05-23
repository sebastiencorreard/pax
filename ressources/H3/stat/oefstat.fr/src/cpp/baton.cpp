target=baton

\language{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}
\text{means=randint(0..4)}
\for{k=2 to 15}{\text{means=\means,randint(0..4)}}
\text{scale=}
\for{k=2 to 20 step 2}{
  \text{scale=\scale
 text black,\k-0.15,-0.2,small,\k
 }
}
\for{k=1 to 5}{
  \text{scale=\scale
  text black,-0.5,\k+0.3,small,\k
  }
}
\text{fond=fill 1,1,220,220,255}
\text{pic=draw(506,154,
 xrange -1,22
 yrange -1,6
 \fond
 parallel 1,0,1,6,1,0,20,grey
 parallel 0,1,21,1,0,1,5,grey
 linewidth 2
 arrow -1,0,22,0,10,black
 arrow 0,-1,0,6,10,black
 text black,21.6,0.8,medium,x
 text black,-0.6,5.9,medium,M
 \scale
)}
\text{fillist=}
\integer{y=11}
\for{k=1 to 20}{
  \integer{s=\k+4}
  \integer{x=\k*22+14}
  \text{fillist=\fillist
r\k,\x,\y}
 }
  \text{smallgrill=
  \fond
 parallel 0,20,16,20,0,25,5,grey
}
\text{bat0=draw(16,144
\smallgrill
)}
\text{bat1=draw(16,144
\smallgrill
frect 0,119,15,143,red
)}
\text{bat2=draw(16,144
\smallgrill
frect 0,95,15,143,red
)}
\text{bat3=draw(16,144
\smallgrill
frect 0,71,15,143,red
)}
\text{bat4=draw(16,144
\smallgrill
frect 0,44,15,143,red
)}
\text{bat5=draw(16,144
\smallgrill
frect 0,20,15,143,red
)}
\text{batons=<img name="0" src="\bat0" alt="0">,
<img name="1" src="\bat1" alt="1">,
<img name="2" src="\bat2" alt="2">,
<img name="3" src="\bat3" alt="3">,
<img name="4" src="\bat4" alt="4">,
<img name="5" src="\bat5" alt="5">,
}

\text{rrr=\batons[1],\batons[1],\batons[1],\batons[1]}
\for{k=1 to 15}{\text{rrr=\rrr,\batons[\means[\k]+1]}}
\text{rrr=\rrr,\batons[1]}

\statement{\name_enonce[1] \matiere,
 \name_enonce[2]:
 <table class="wimscenter wimsborder">
 <tr><th>\name_head[1;1] <br> <small>\name_head[1;2]</small></th>
 \for{i=5 to 19}{<td>\i</td>}
 </tr>
 <tr><th>\name_head[2;1] <br><small>\name_head[2;2]<br> \name_head[2;3]</small></th>
 \for{i=1 to 15}{<td>\means[\i]</td>}</tr>
 </table>
 <div class="wims_question">\name_question
 <div class="wimscenter">
 \special{imagefill \pic,506x154,16x120
\fillist
 }
 </div>
 </div>
 }
 \reply{bâton 1}{\rr1;\batons}{type=clickfill}
 \reply{bâton 2}{\rr2}{type=clickfill}
 \reply{bâton 3}{\rr3}{type=clickfill}
 \reply{bâton 4}{\rr4}{type=clickfill}
 \reply{bâton 5}{\rr5}{type=clickfill}
 \reply{bâton 6}{\rr6}{type=clickfill}
 \reply{bâton 7}{\rr7}{type=clickfill}
 \reply{bâton 8}{\rr8}{type=clickfill}
 \reply{bâton 9}{\rr9}{type=clickfill}
 \reply{bâton 10}{\rr10}{type=clickfill}
 \reply{bâton 11}{\rr11}{type=clickfill}
 \reply{bâton 12}{\rr12}{type=clickfill}
 \reply{bâton 13}{\rr13}{type=clickfill}
 \reply{bâton 14}{\rr14}{type=clickfill}
 \reply{bâton 15}{\rr15}{type=clickfill}
 \reply{bâton 16}{\rr16}{type=clickfill}
 \reply{bâton 17}{\rr17}{type=clickfill}
 \reply{bâton 18}{\rr18}{type=clickfill}
 \reply{bâton 19}{\rr19}{type=clickfill}
 \reply{bâton 20}{\rr20}{type=clickfill}
\text{test=0}
\text{test1=}
\text{rrs=\rr1,\rr2,\rr3,\rr4,\rr5,\rr6,\rr7,\rr8,\rr9,\rr10,
 \rr11,\rr12,\rr13,\rr14,\rr15,\rr16,\rr17,\rr18,\rr19,\rr20}
\for{k=20 to 1 step -1}{
  \if{\rrs[\k] notsametext \rrr[\k]}{\text{test=\k}
  \text{test1=wims(append item \k to \test1)}}
}
\integer{test_cnt=items(\test1)}
\condition{\name_cond}{\test=0}
\feedback{\test>0}{
  \name_feed[1] \if{\test_cnt=1}{\name_feed[2]}{\name_feed[3]} \test1
  \name_feed[4]}
