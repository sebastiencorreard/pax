target=oefregle31 oefregle32 oefregle33 oefregle34 oefregle35
#include "author.inc"
#if defined TARGET_oefregle31
# define NUM 1
#endif
#if defined TARGET_oefregle32
# define NUM 2
#endif
#if defined TARGET_oefregle33
# define NUM 3
#endif
#if defined TARGET_oefregle34
# define NUM 4
#endif
#if defined TARGET_oefregle35
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"

\precision{100000}
\integer{a=randint(1..3)}
\text{t=row(\a,\name_t)}
\text{q=row(\a,\name_q)}

\text{n=shuffle(2,3,4,5,6,7,8,9)}
\integer{u=\t[4]*randint(2..8)}

\integer{r=\n[1]*\u}
\integer{rep=\n[2]*\u}

\text{e=row(\a,\name_e)}
#if defined TARGET_oefregle31
\text{rep1=\e[1]}
\text{rep2=\r \(\div\) \n[1] = \u }
\text{rep3=\name_instruction1[2;] \u \e[2] 1 \e[3]}
\text{rep4=\name_instruction1[3;] &#44; \e[4] \n[2] \e[5]}
\text{rep5=\u \(\times\) \n[2] = \rep }
\text{rep6=\name_instruction1[4;] \rep \e[2] \n[2] \e[5]}

\text{size=400x50}
%petit ajout par JBF pour l enonce en latex
\text{phrases=shuffle(\item \fbox{\rep1},\item \fbox{\rep2},\item \fbox{\rep3}, \item \fbox{\rep4},\item \fbox{\rep5},\item \fbox{\rep6})}
\statement{
\t[1] \n[1] \t[2] \r \t[3].

\q[1] \n[2] \q[2]
<div>
\name_instruction
</div>
<ul class="wims_nopuce"><li>\embed{r1,\size}</li>
<li>\embed{r2}</li>
<li>\embed{r3}</li>
<li>\embed{r4}</li>
<li>\embed{r5}</li>
<li>\embed{r6}</li>
</ul>
}

\answer{}{\rep1}{type=dragfill}
\answer{}{\rep2}{type=dragfill}
\answer{}{\rep3}{type=dragfill}
\answer{}{\rep4}{type=dragfill}
\answer{}{\rep5}{type=dragfill}
\answer{}{\rep6}{type=dragfill}
\latex{
\begin{statement}
	\t[1] \n[1] \t[2] \r \t[3].
	\q[1] \n[2] \q[2]\par
	\name_instruction\par
	\begin{itemize}
		\phrases
	\end{itemize}
\end{statement}
\begin{solution}
	\begin{itemize}
		\item \rep1
		\item \rep2
		\item \rep3
		\item \rep4
		\item \rep5
		\item \rep6
	\end{itemize}
\end{solution}}
#endif
#if defined TARGET_oefregle32 || defined TARGET_oefregle33 || defined TARGET_oefregle34 || defined TARGET_oefregle35
\text{rep1=\r}
\text{rep2=\(\div\)}
\text{rep3=\n[1]}
\text{rep4 = \u}

\text{rep5=\u }
\text{rep6=\(\times\)}
\text{rep7=\n[2]}
\text{rep8= \rep}
%petit ajout par JBF pour l enonce en latex
\text{phrases=shuffle( \fbox{\rep1}, \fbox{\rep2}, \fbox{\rep3}, \fbox{\rep4}, \fbox{\rep5}, \fbox{\rep6}, \fbox{\rep7}, \fbox{\rep8})}

# if defined TARGET_oefregle35
\text{size=5}
# else
\text{size=100x20}
# endif
#endif
#if defined TARGET_oefregle32
\statement{
\t[1] \n[1] \t[2] \r \t[3].
<p>\q[1] \n[2] \q[2]</p>
<div class="spacer">
\name_instruction1[1;]:
</div>
<ul class="wims_nopuce"><li>\e[1]
</li><li>
\embed{r1,size}\embed{r2}\embed{r3} = \embed{r4}
</li><li>
\name_instruction1[2;] \u \e[2] 1 \e[3]
</li><li>
\name_instruction1[3;], \e[4] \n[2] \e[5]
</li><li>
\embed{r5}\embed{r6} \embed{r7} = \embed{r8}
</li><li>
\name_instruction1[4;] \rep \e[2] \n[2] \e[5]
</li></ul>
<div class="wims_instruction">
\name_instruction1[5;].
</div>
}
\latex{
\begin{statement}
\t[1] \n[1] \t[2] \r \t[3].
\q[1] \n[2] \q[2]\par

\name_instruction1[1;]
\begin{itemize}
	\item \e[1]
	\item \dotfill
	\item \name_instruction1[2;] \u \e[2] 1 \e[3]
	\item \name_instruction1[3;] \e[4] \n[2] \e[5]
	\item \dotfill
	\item \name_instruction1[4;] \rep \e[2] \n[2] \e[5]
\end{itemize}
\name_instruction1[5;]:
	\begin{itemize}
		\item \phrases[1], \phrases[2], \phrases[3], \phrases[4]
		\item \phrases[5], \phrases[6], \phrases[7], \phrases[8]
	\end{itemize}
\end{statement}

\begin{solution}
	\begin{itemize}
	\item \e[1]
	\item \rep1 \rep2 \rep3 = \rep4
	\item \name_instruction1[2;] \u \e[2] 1 \e[3]
	\item \name_instruction1[3;]:\e[4] \n[2] \e[5]
	\item \rep5 \rep6 \rep7 = \rep8
	\item \name_instruction1[4;] \rep \e[2] \n[2] \e[5]
	\end{itemize}
\end{solution}
}
\answer{}{\rep1}{type=dragfill}
\answer{}{\rep2}{type=dragfill}
\answer{}{\rep3}{type=dragfill}
\answer{}{\rep4}{type=dragfill}
\answer{}{\rep5|\rep7}{type=dragfill}
\answer{}{\rep6}{type=dragfill}
\answer{}{\rep7|\rep5}{type=dragfill}
\answer{}{\rep8}{type=dragfill}
#endif

#if defined TARGET_oefregle33
%petit ajout par JBF pour l enonce en latex
\text{phrases=shuffle( \fbox{\rep1}, \fbox{\rep2}, \fbox{\rep3}, \fbox{\rep4}, \fbox{\rep5}, \fbox{\rep6}, \fbox{\rep7}, \fbox{\rep8}, \fbox{1}, \fbox{\u}, \fbox{1},\fbox{\n[2]}, \fbox{\rep},\fbox{\n[2]})}
\statement{
\t[1] \n[1] \t[2] \r \t[3].
<p>\q[1] \n[2] \q[2]</p>
\name_instruction1[1;]:

<ul class="wims_nopuce"><li>\e[1] \embed{r9,\size} \e[2]</li>
<li>\embed{r1,size}\embed{r2}\embed{r3} = \embed{r4}</li>
<li>\name_instruction1[2;] \embed{r10} \e[3] \embed{r11} \e[4]</li>
<li>\name_instruction1[3;], \e[5] \embed{r12} \e[6]</li>
<li>\embed{r5}\embed{r6} \embed{r7} = \embed{r8} </li>
<li>\name_instruction1[4;] \embed{r13} \e[3] \embed{r14} \e[6]</li>
</ul>
<div class="wims_instruction">
\name_instruction1[5;].
</div>
}

\latex{
\begin{statement}
\t[1] \n[1] \t[2] \r \t[3].
\q[1] \n[2] \q[2]\par

\name_instruction1[1;]:
\begin{itemize}
	\item \e[1] \ldots \e[2]
	\item \dotfill
	\item \name_instruction1[2;] \ldots \e[3] \ldots \e[4]
	\item \name_instruction1[3;], \e[5] \ldots \e[6]
	\item \dotfill
	\item \name_instruction1[4;] \ldots \e[3] \ldots \e[6]
\end{itemize}
\name_instruction1[5;]:
	\begin{itemize}
		\item \phrases[1], \phrases[2], \phrases[3], \phrases[4], \phrases[5], \phrases[6], \phrases[7]
		\item \phrases[8], \phrases[9], \phrases[10], \phrases[11], \phrases[12], \phrases[13], \phrases[14]
	\end{itemize}
\end{statement}

\begin{solution}
	\begin{itemize}
	\item \e[1] 1 \e[2]
	\item \rep1 \rep2 \rep3 = \rep4
	\item \name_instruction1[2;] \u \e[3] 1 \e[4]
	\item \name_instruction1[3;], \e[5] \n[2] \e[6]
	\item \rep5 \rep6 \rep7 =\rep8
	\item \name_instruction1[4;] \rep \e[3] \n[2] \e[6]
	\end{itemize}
\end{solution}
}
\answer{}{\rep1}{type=dragfill}
\answer{}{\rep2}{type=dragfill}
\answer{}{\rep3}{type=dragfill}
\answer{}{\rep4}{type=dragfill}
\answer{}{\rep5|\rep7}{type=dragfill}
\answer{}{\rep6}{type=dragfill}
\answer{}{\rep7|\rep5}{type=dragfill}
\answer{}{\rep8}{type=dragfill}
\answer{}{1}{type=dragfill}
\answer{}{\u}{type=dragfill}
\answer{}{1}{type=dragfill}
\answer{}{\n[2]}{type=dragfill}
\answer{}{\rep}{type=dragfill}
\answer{}{\n[2]}{type=dragfill}
#endif

#if defined TARGET_oefregle34
%petit ajout par JBF pour l enonce en latex
\text{phrases=shuffle(\fbox{1}, \fbox{\u}, \fbox{1},\fbox{\n[2]}, \fbox{\rep}, \fbox{\n[2]})}

\statement{
\t[1] \n[1] \t[2] \r \t[3].
<p>\q[1] \n[2] \q[2]</p>
<div class="spacer">
\name_instruction1[1;]:
</div>
<ul class="wims_nopuce"><li>\e[1] \embed{r1,\size} \e[2]
</li><li>
\name_instruction1[2;] \embed{r2} \e[3] \embed{r3} \e[4]
</li><li>
\name_instruction1[3;], \e[5] \embed{r4} \e[6]
</li><li>
\name_instruction1[4;] \embed{r5} \e[3] \embed{r6} \e[6]
</li></ul>
<div class="wims_instruction">
\name_instruction1[5;].
</div>
}
\latex{
\begin{statement}
\t[1] \n[1] \t[2] \r \t[3].
\q[1] \n[2] \q[2]\par

\name_instruction1[1;]:
\begin{itemize}
	\item \e[1] \ldots \e[2]
	\item \name_instruction1[2;] \ldots \e[3] \ldots \e[4]
	\item \name_instruction1[3;] \e[5] \ldots \e[6]
	\item \name_instruction1[4;] \ldots \e[3] \ldots \e[6]
\end{itemize}
\name_instruction1[5;]:
	\begin{itemize}
		\item \phrases[1], \phrases[2], \phrases[3], \phrases[4], \phrases[5], \phrases[6]
	\end{itemize}
\end{statement}

\begin{solution}
	\begin{itemize}
	\item \e[1] 1 \e[2]
	\item \name_instruction1[2;] \u \e[3] 1 \e[4]
	\item \name_instruction1[3;] \e[5] \n[2] \e[6]
	\item \name_instruction1[4;] \rep \e[3] \n[2] \e[6]
	\end{itemize}
\end{solution}
}
\answer{}{1}{type=dragfill}
\answer{}{\u}{type=dragfill}
\answer{}{1}{type=dragfill}
\answer{}{\n[2]}{type=dragfill}
\answer{}{\rep}{type=dragfill}
\answer{}{\n[2]}{type=dragfill}
#endif

#if defined TARGET_oefregle35
%petit ajout par JBF pour l enonce en latex
\text{phrases=shuffle(\fbox{1}, \fbox{\u}, \fbox{1},\fbox{\n[2]}, \fbox{\rep}, \fbox{\n[2]})}
\statement{
\t[1] \n[1] \t[2] \r \t[3].
<p>\q[1] \n[2] \q[2]</p>
\name_instruction1[1;]:
<ul class="wims_nopuce">
<li>
<label for="reply1">\e[1]</label> \embed{r1,\size} \e[2]
</li><li>
<label for="reply2">\name_instruction1[2;] </label> \embed{r2,\size}
<label for="reply3">\e[3]</label> \embed{r3,\size} \e[4]
</li><li>
  <label for="reply4">\e[1]</label> \embed{r4,\size} \e[6]
</li><li>
<label for="reply5">\name_instruction1[4;]</label> \embed{r5,\size} <label for="reply6">\e[3]</label> \embed{r6,\size} \e[6]
</li></ul>
}
\latex{
\begin{statement}
\t[1] \n[1] \t[2] \r \t[3].
\q[1] \n[2] \q[2]\par

\name_instruction1[1;]:
\begin{itemize}
	\item \e[1] \ldots \e[2]
	\item \name_instruction1[2;] \ldots \e[3] \ldots \e[4]
	\item \name_instruction1[3;]: \e[5] \ldots \e[6]
	\item \name_instruction1[4;] \ldots \e[3] \ldots \e[6]
\end{itemize}
\name_instruction1[5;]:
	\begin{itemize}
		\item \phrases[1], \phrases[2], \phrases[3], \phrases[4], \phrases[5], \phrases[6]
	\end{itemize}
\end{statement}

\begin{solution}
	\begin{itemize}
	\item \e[1] 1 \e[2]
	\item \name_instruction1[2;] \u \e[3] 1 \e[4]
	\item \name_instruction1[3;]: \e[5] \n[2] \e[6]
	\item \name_instruction1[4;] \rep \e[3] \n[2] \e[6]
	\end{itemize}
\end{solution}
}
\answer{}{1}{type=numeric}
\answer{}{\u}{type=numeric}
\answer{}{1}{type=numeric}
\answer{}{\n[2]}{type=numeric}
\answer{}{\rep}{type=numeric}
\answer{}{\n[2]}{type=numeric}
#endif
