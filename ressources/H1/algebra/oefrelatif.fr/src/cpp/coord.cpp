target=coord
#include "lang_titles.inc"
#include "author.inc"
\precision{10000}

#include "lang.inc"
\text{a=-4,-3,-2,-1,0,1,2,3,4}
\text{a=shuffle(-4,-3,-2,-1,0,1,2,3,4)}
\text{b=shuffle(-4,-3,-2,-1,0,1,2,3,4)}
\text{a1=item(1,\a)}
\text{a2=item(1,\b)}
\text{b1=item(2,\a)}
\text{b2=item(2,\b)}
\text{c1=item(3,\a)}
\text{c2=item(3,\b)}
\text{dessin=xrange -5.2,5.2
yrange -5.2,5.2
parallel -5,-5,5,-5,0,1,10, grey
parallel -5,-5,-5,5,1,0,10, grey
hline 0,0,black
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
vline 0,0,black
disk \a1,\a2, 7, blue
disk \b1,\b2, 7, blue
disk \c1,\c2, 7, blue
text black, \a1-0.2,\a2-0.2,medium,A
 text black,\b1-0.2,\b2-0.2,medium,B
 text black,\c1-0.2,\c2-0.2,medium,C}
 \text{dessintikz=drawtikz(200,200
\dessin)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
 \draw{200,200}{\dessin}
</div><div class="medium_size text_col">
\name_instruction \(A\), \(B\) \name_and \(C\) :
<div class="wimscenter"><label for="reply1">\(A=\) </label>( \embed{reply 1,6}, \embed{reply 2 ,6})</div>
<div class="wimscenter"><label for="reply3">\(B=\)</label>( \embed{reply 3 ,6}, \embed{reply 4 ,6})</div>
<div class="wimscenter"><label for="reply5">\(C=\)</label>( \embed{reply 5 ,6}, \embed{reply 6 ,6})</div>
</div></div>
}
\answer{\(x_A\)}{\a1}{type=numexp}
\answer{\(y_A\)}{\a2}{type=numexp}
\answer{\(x_B\)}{\b1}{type=numexp}
\answer{\(y_B\)}{\b2}{type=numexp}
\answer{\(x_C\)}{\c1}{type=numexp}
\answer{\(y_C\)}{\c2}{type=numexp}

\feedback{\reply1=-\a1 and \a1!=0}{<div class="wims_msg alert">\warning1 \(x_A\).</div>}
\feedback{\reply2=-\a2 and \a2!=0}{<div class="wims_msg alert">\warning1 \(y_A\).</div>}
\feedback{\reply3=-\b1 and \b1!=0}{<div class="wims_msg alert">\warning1 \(x_B\).</div>}
\feedback{\reply4=-\b2 and \b2!=0}{<div class="wims_msg alert">\warning1 \(y_B\).</div>}
\feedback{\reply5=-\c1 and \c1!=0}{<div class="wims_msg alert">\warning1 \(x_C\).</div>}
\feedback{\reply6=-\c2 and \c2!=0}{<div class="wims_msg alert">\warning1 \(y_C\).</div>}
\feedback{\reply1=\a2 and \reply2=\a1 and \a1!=\a2}{<div class="wims_msg alert">\warning2 \(A\).</div>}
\feedback{\reply3=\b2 and \reply4=\b1 and \b1!=\b2}{<div class="wims_msg alert">\warning2 \(B\).</div>}
\feedback{\reply5=\c2 and \reply6=\c1 and \c1!=\c2}{<div class="wims_msg alert">\warning2 \(C\).</div>}

\latex{
\begin{statement}
\name_instruction \(A\), \(B\) \name_and \(C\) :
\begin{center}
\dessintikz
\end{center}
\begin{itemize}
\item \(A= (\cdots, \cdots)\)
\item \(B= (\cdots, \cdots)\)
\item \(C= (\cdots, \cdots)\)
\end{itemize}

\end{statement}
}
