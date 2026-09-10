target=oefplacfrasimpl1 oefplacfrasimpl2 oefplacfrasimpl3 oefplacfrasimpl4 oefplacfrasimpl5

#include "author.inc"
\precision{1000}
#if defined TARGET_oefplacfrasimpl1
# define NUM 1
#endif
#if defined TARGET_oefplacfrasimpl2
# define NUM 2
#endif
#if defined TARGET_oefplacfrasimpl3
# define NUM 3
#endif
#if defined TARGET_oefplacfrasimpl4
# define NUM 4
#endif
#if defined TARGET_oefplacfrasimpl5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefplacfrasimpl1
\integer{d=random(2,4)}
\integer{u1=1}
\integer{u2=\d}
\integer{m=1}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
  \integer{a=\i*1}
  \integer{s=\i}
  \text{dessin=\dessin
    text blue, \s,-1, medium,\a}}
\text{den=\d}
\text{num=1}
\rational{a=\num/\den}
#endif
#if defined TARGET_oefplacfrasimpl2
\integer{u1=1}
\integer{u2=randint(2..10)*2}
\integer{m=1}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
  \integer{a=\i*1}
  \integer{s=\i}
  \text{dessin=\dessin
    text blue, \s,-1, medium,\a}}
\text{den=2}
\text{num=1}
\rational{a=\num/\den}
#endif
#if defined TARGET_oefplacfrasimpl3
\integer{u1=1}
\integer{u2=randint(2..5)*4}
\integer{m=1}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
  \integer{a=\i*1}
  \integer{s=\i}
  \text{dessin=\dessin
    text blue, \s,-1, medium,\a}}
\text{den=4}
\text{num=1}
\rational{a=\num/\den}
#endif
#if defined TARGET_oefplacfrasimpl4
\integer{d=random(5,10)}
\integer{u1=1}
\integer{u2=\d}
\integer{m=1}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
  \integer{a=\i*1}
  \integer{s=\i}
  \text{dessin=\dessin
    text blue, \s,-1, medium,\a}}
\text{den=\d}
\text{num=1}
\rational{a=\num/\den}
#endif
#if defined TARGET_oefplacfrasimpl5
\integer{d=randitem(2,4,5,10)}
\integer{u1=1}
\integer{u2=\d}
\integer{m=2}
\integer{m1=0}
\text{a=0}
\text{dessin=}
\for{i=\m1 to \m}{
  \integer{a=\i*1}
  \integer{s=\i}
  \text{dessin=\dessin
    text blue, \s,-1, medium,\a}}
\integer{den=\d}
\integer{num=1}
\rational{a=\num/\den}
#endif
\text{gradu=draw(600,80
xrange \m1-0.1,\m+0.1
yrange -2,2.2
segment 0,0,2.2,0,black
parallel \m1,-0.8,\m1,0.4,1/\u1,0, 40, blue
parallel \m1,-0.3,\m1,0.3,1/\u2,0, 200, blue
parallel \m1,-0.8,\m1,0.6,1,0, 40, red
\dessin)
}
\integer{dep=600/(\m*10+2)}
\integer{pos=\dep+(600-2*\dep)*\num/(\m*\den)}
\statement{
\name_question[1;]
\(\frac{\num}{\den}) \name_question[2;]
<div class="wimscenter">
\embed{r1}
</div>
}
\answer{numérateur}{\gradu;rectangle,\pos-3,35,\pos+3,45}{type=coord}
