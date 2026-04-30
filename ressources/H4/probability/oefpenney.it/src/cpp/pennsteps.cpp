target=pairs1 pairs2 pairs3 pairs4 single1

#if defined COMMENT
single2 is to be revised
#endif

#if defined TARGET_single1 || defined TARGET_pairs1 || defined TARGET_pairs4
# define LEVEL A
#endif
#if defined TARGET_pairs2 || defined TARGET_single2
# define LEVEL B
#endif
#if defined TARGET_pairs3
# define LEVEL C
#endif

#include "observation.inc"
#include "lang_titles.inc"
#include "setup.inc"

#include "lang.inc"

#if defined TARGET_pairs1
TODO: randomizzare giocatore1 e giocatore2
aggiungere un certi casi in cui non si può dire (?)
\matrix{cases=112,211,11,1
112,211,2,2
112,211,21,2
111,211,2,2
111,211,22,2
111,211,21,2
111,221,22,2
112,212,11,1
112,122,11,1
}
#endif
#if defined TARGET_pairs2
differs last
\matrix{cases=111,112,3
121,122,3
111,211,2
}
#endif
#if defined TARGET_pairs3
list to be completed
\matrix{cases=111,112,3/16,3/16
111,121,3/16,1/4
111,122,3/16,1/4
111,211,1/8,1/4
111,212,3/16,1/4
}
#endif
#if defined TARGET_pairs4
list to be completed
\matrix{cases=111,112
111,121
111,221
111,222
112,122
112,222
}
#endif
#if defined TARGET_single2
\matrix{cases=111,3/16
112,1/4
121,1/4
122,1/4
}
#endif

#if defined TARGET_single1 || defined TARGET_single2 || defined TARGET_pairs3
\computeanswer{yes}
#endif
#if defined TARGET_single1
\text{firstpl=shuffle(\longlist)}
\text{firstpl=item(1..3,\firstpl)}
\text{imgfir=wims(makelist \leftstr/t\midstr t\rightstr for t in \firstpl)}
\text{imgfir=wims(items2words \imgfir)}
#endif

#if defined TARGET_pairs1 || defined TARGET_pairs2 || defined TARGET_pairs3 || defined TARGET_pairs4 || defined TARGET_single2
\text{thisgame=randomrow(\cases)}
#endif

#if defined TARGET_pairs1 || defined TARGET_pairs2 || defined TARGET_pairs3 || defined TARGET_pairs4 || defined TARGET_single2
\text{firstpl=}
\for{kk=1 to 3}{
  \text{tmpstr=wims(char \kk of \thisgame[1])}
  \text{tmpstr=\rlist[\tmpstr]}
  \text{firstpl=\firstpl,\tmpstr}
}
\text{firstpl=wims(nonempty items \firstpl)}
\text{imgfir=wims(makelist \leftstr/t\midstr t\rightstr for t in \firstpl)}
\text{imgfir=wims(items2words \imgfir)}
#endif
#if defined TARGET_pairs1 || defined TARGET_pairs2 || defined TARGET_pairs3 || defined TARGET_pairs4
\text{seconpl=}
\for{kk=1 to 3}{
  \text{tmpstr=wims(char \kk of \thisgame[2])}
  \text{tmpstr=\rlist[\tmpstr]}
  \text{seconpl=\seconpl,\tmpstr}
}
\text{seconpl=wims(nonempty items \seconpl)}
\text{imgsec=wims(makelist \leftstr/t\midstr t\rightstr for t in \seconpl)}
\text{imgsec=wims(items2words \imgsec)}
#endif

#if defined TARGET_pairs1
\integer{numlast=wims(charcnt \thisgame[3])}
\text{imglast=}
\for{jj=1 to \numlast}{
\text{tmpstr=wims(char \jj of \thisgame[3])}
\text{tmpstr=\rlist[\tmpstr]}
\text{imglast=\imglast,\leftstr/\tmpstr\midstr \tmpstr\rightstr}
}
\text{imglast=wims(nonempty items \imglast)}
\text{imglast=wims(items2words \imglast)}
#endif

#if defined TARGET_single1
\real{prob=(1/2)^3}
#endif
#if defined TARGET_single2
\real{prob=\thisgame[2]}
#endif
#if defined TARGET_pairs3
\real{prob=\thisgame[3]}
#endif
#if defined TARGET_pairs4
\text{prob=p,1-p}
#endif

#if defined TARGET_pairs1 || defined TARGET_pairs2 || defined TARGET_pairs3 || defined TARGET_pairs4

\integer{nn=items(\ans_list)}

\statement{\name_statement_list[1] \imgfir \name_statement_list[2] \imgsec. 

#if defined TARGET_pairs1
\name_statement \name_cases_list[\numlast]
<div class="wimscenter">.... \imglast</div>
\name_then
#endif

#if defined TARGET_pairs1 || defined TARGET_pairs2
<ul>\for{h=1 to \nn}{<li>\embed{reply1,\h}</li>}</ul>
#endif
#if defined TARGET_pairs3
<div>\name_question
\embed{reply1}</div>
#endif
#if defined TARGET_pairs4
<div class="wims_question">\name_statement[1] \name_statement[2] \name_players[1] \name_statement[3] \(\prob[1]\), \name_statement[4] \name_statement[2] \name_players[2] \name_statement[3] \embed{reply1,4}</div>
#endif
}
#endif
#if defined TARGET_single1 || defined TARGET_single2
\statement{\name_statement[1]
<div class="wimscenter">\imgfir</div>
<div>\name_statement[2] \embed{reply1}</div>
}
#endif

#if defined TARGET_pairs1
\answer{}{\thisgame[4];\ans_list}{type=radio}
#endif

#if defined TARGET_pairs2
\answer{}{\thisgame[3];\ans_list}{type=radio}
#endif

#if defined TARGET_single1 || defined TARGET_single2 || defined TARGET_pairs3
\answer{}{\prob}{type=numexp}{option=noreduction}
#endif
#if defined TARGET_pairs4
\answer{}{\prob[2]}
#endif
