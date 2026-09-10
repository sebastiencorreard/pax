target=oefutigraph1
#include "author.inc"
#define NUM 1
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\text{effs=shuffle(0,4,7)}
\for{k=1 to 3}{\text{effs=\effs,randint(2..6)}}
\text{effs=shuffle(\effs)}
\text{a=shuffle(6)}
\integer{n1=4*(\a[1]-1)}
\integer{n2=4*(\a[2]-1)}

\text{bat1=frect 1,0,2,\effs[1],red}
\text{bat2=frect 3,0,4,\effs[2],red}
\text{bat3=frect 5,0,6,\effs[3],red}
\text{bat4=frect 7,0,8,\effs[4],red}
\text{bat5=frect 9,0,10,\effs[5],red}
\text{bat6=frect 11,0,12,\effs[6],red}

\integer{rp=\effs[1]}
\for{i=2 to 6}{\integer{rp=\rp+\effs[\i]}}

\text{gradu=}
\for{k=0 to 20 step 4}{
  \text{gradu=\gradu
  text black,\k/2+1.4,-0.2,small,\k}}
\for{k=1 to 10}{
  \text{gradu=\gradu
  text black,-0.7,\k+0.2,small,\k}}

\text{fond=fill 0,0,220,220,255}
\text{pic=draw(506,308
  xrange -1,22
  yrange -1,8
  \fond
  parallel 1,0,1,8,1,0,20,grey
  parallel 0,0.5,21,0.5,0,0.5,16,grey
  linewidth 2
  arrow -1,0,21,0,10,black
  arrow 0,-1,0,8,10,black
  text black,18.6,0.8,medium,\name_header[1]
  text black,0.5,7.9,medium,\name_header[2]
  \gradu
\bat1
\bat2
\bat3
\bat4
\bat5
\bat6
 )}
#include "solution.inc"
\statement{<div class="wims_columns">
 <div class="medium_size img_col">
   <img src="\pic" alt="">
 </div>
 <div class="medium_size text_col">
  \name_instruction
  <p>\name_instruction1 :</p>
  <div class="spacer">
  <label for="reply1">\name_question ? </label>\embed{r1,5}</div>
  </div></div>
}

\answer{}{\rp}{type=numeric}
\solution{\sol}
