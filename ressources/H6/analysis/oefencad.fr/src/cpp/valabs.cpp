target=valabs

\language{fr}
\range{-5..5}
\author{Noémie,Cochi;Olivier,Dupuy}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"

\real{a=randint(1..9)*random(-1,1,-1,-1)}
\real{b=randint(\a+1..20)}
\real{res1=min(abs(\a),abs(\b))}
\real{res2=max(abs(\a),abs(\b))}
\real{res1= \a<0 and \b>0 ? 0}
\real{aa= min(-\a,\b)}
\real{bb= max(-\a,\b)}

\statement{\name_enonce \(\a \leq x \leq \b\).
  <label for="reply1">\name_bestappr \(abs(x)\)&nbsp;:</label>
  <div class="wimscenter">\embed{r1,3}
    <label for="reply2">\( \leq | x | \leq \; \)</label> \embed{r2,3}.</div>}

\answer{ }{\res1}{type=numeric}
\answer{ }{\res2}{type=numeric}

\feedback{(\reply1> \reply2 )}{\name_feed1 \reply1 > \reply2.}
\feedback{(\reply1=\aa and \reply2=\bb ) and (\a<0 and \b>0)}{\name_feed2 \aa \name_and \bb.}
\feedback{(\reply1=\a and \reply2=\b ) and \a<0 and \b<=0}{\name_feed3}
\feedback{(\reply1<>\res1 or \reply2<>\res2 ) and \a>0 and \b>0}{\name_feed4?}
\feedback{(\reply1<>\res1 and \reply2<>\res2 ) and \a<0 and \b<=0}{\name_feed5?}
\feedback{(\reply1<>\res1 or \reply2<>\res2 ) and \a<0 and \b>0}{\name_feed6 [\a,\b] ?}
