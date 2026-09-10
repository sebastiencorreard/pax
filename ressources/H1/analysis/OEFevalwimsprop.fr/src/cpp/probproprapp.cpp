target=oefprobproprapp1 oefprobproprapp2 oefprobproprapp3 oefprobproprapp4 oefprobproprapp5
#include "author.inc"

\range{-5..5}
\precision{10000}

#if defined TARGET_oefprobproprapp1
# define NUM 1
#endif
#if defined TARGET_oefprobproprapp2
# define NUM 2
#endif
#if defined TARGET_oefprobproprapp3
# define NUM 3
#endif
#if defined TARGET_oefprobproprapp4
# define NUM 4
#endif
#if defined TARGET_oefprobproprapp5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefprobproprapp1 || defined TARGET_oefprobproprapp2 || defined TARGET_oefprobproprapp3
\integer{a=randint(1..5)}
\integer{b=randint(1..5)}
\text{t=row(\a,\name_t)}
\integer{v1=\t[4+2*\b]}
\integer{v2=\t[5+2*\b]}

\statement{
<div class="wims_question">
\t[1] \v1 \t[2] \v2. \t[3] \v2 \t[4] \v1 \t[5]
# if defined TARGET_oefprobproprapp1 || defined TARGET_oefprobproprapp3
<table class="wimscenter wimsborder">
<tr><th>\t[16]</th><td>\v2</td></tr>
<tr><th>\t[17]</th><td>\v1</td></tr>
</table>
# endif
</div>
<div class="spacer">
\name_instruction:
</div>
# if defined TARGET_oefprobproprapp3
<div class="wimscenter">
\(\v2\times \frac{\v1}{\v2}\)=\embed{r1,3}.
</div>
# endif
# if defined TARGET_oefprobproprapp1 || defined TARGET_oefprobproprapp2
<div class="wimscenter">
\special{mathmlinput [\frac{reply1}{reply2}],5,noanswer
reply1
reply2}
</div>
# endif
}

\answer{}{\v1}{type=numeric}
# if defined TARGET_oefprobproprapp1 || defined TARGET_oefprobproprapp2
\answer{}{\v2}{type=numeric}
# endif
#endif

#if defined TARGET_oefprobproprapp4 || defined TARGET_oefprobproprapp5

\integer{a=randint(1..5)}
\integer{b=randint(1..5)}
\text{t=row(\a,\name_t)}
\text{q=row(\a,\name_q)}
\integer{v1=\t[4+2*\b]}
\integer{v2=\t[5+2*\b]}
\integer{m=randint(3..12)}
\integer{n1=\v1*\m}
\integer{n2=\v2*\m}

\statement{
<div class="wims_question">
\t[1] \v1 \t[2] \v2.<p>\q[1] \n2 \q[2].</p>

# if defined TARGET_oefprobproprapp4
<table class="wimscenter wimsborder">
<tr><th>\t[16]</th><td>\v2</td><td>\n2</td></tr>
<tr><th>\t[17]</th> <td>\v1</td><td></td></tr>
</table>
# endif
# if defined TARGET_oefprobproprapp5
<table class="wimscenter wimsborder">
<tr><th>\t[16]</th><td>\v2</td><td>\n2</td></tr>
<tr><th>\t[17]</th> <td>\v1</td><td>\embed{r5,5}</td></tr>
</table>
# endif
</div>
<div class="spacer">
\name_instruction:
</div>
# if defined TARGET_oefprobproprapp4
<div class="wimscenter">
\special{mathmlinput [reply2\times\frac{reply1}{reply3}],3
reply1
reply2
reply3}
</div>
# endif
#if defined TARGET_oefprobproprapp5
<div class="wimscenter">
\special{mathmlinput [reply2\times\frac{reply1}{reply3}=reply4],3
reply1
reply2
reply3
reply4}
</div>
# endif
}

\answer{}{\v1}{type=numeric}
\answer{}{\n2}{type=numeric}
\answer{}{\v2}{type=numeric}
# if defined TARGET_oefprobproprapp5
\answer{}{\n1}{type=numeric}
\answer{}{\n1}{type=numeric}
# endif
#endif

%%%%% Code pour Latex un peu a part %%%%%%%%%%
#if defined TARGET_oefprobproprapp1
\latex{
\begin{statement}
\t[1] \v1 \t[2] \v2 \t[3] \v2 \t[4] \v1 \t[5]
\begin{center}
	\begin{tabular}{|l|c|}
		\hline
		\t[16] & \v2 \\ \hline
		\t[17] & \v1 \\ \hline
	\end{tabular}
\end{center}
\name_instruction \dotfill
\end{statement}
\begin{solution}
\name_solution : \( \dfrac{\v1}{\v2} \)
\end{solution}
}
#endif

#if defined TARGET_oefprobproprapp2
\latex{
\begin{statement}
\t[1] \v1 \t[2] \v2 \t[3] \v2 \t[4] \v1 \t[5]
\par
\name_instruction \dotfill
\end{statement}
\begin{solution}
\name_solution: \( \dfrac{\v1}{\v2} \)
\end{solution}
}
#endif

#if defined TARGET_oefprobproprapp3
\latex{
\begin{statement}
\t[1] \v1 \t[2] \v2 \t[3] \v2 \t[4] \v1 \t[5]
\begin{center}
	\begin{tabular}{|l|c|}
		\hline
		\t[16] & \v2 \\ \hline
		\t[17] & \v1 \\ \hline
	\end{tabular}
\end{center}
\name_instruction \par
\[ \v2 \times \dfrac{\v1}{\v2} = \ldots \]
\end{statement}
\begin{solution}
On a \[ \v2 \times \dfrac{\v1}{\v2} = \v1\]
\end{solution}
}
#endif

#if defined TARGET_oefprobproprapp4
\latex{
\begin{statement}
	\t[1] \v1 \t[2] \v2.\par
	 \q[1] \n2 \q[2]\par
	 \begin{center}
	 	\begin{tabular}{|l|c|c|}
	 		\hline
			\t[16] & \v2 & \n2 \\ \hline
			\t[17] & \v1 & \\ \hline
	 	\end{tabular}
	 \end{center}

	\name_instruction:\par
	\[ \ldots \times \dfrac{\ldots}{\ldots}\]
\end{statement}

\begin{solution}
	\name_solution : \( \n2 \times \dfrac{\v1}{\v2} \)
\end{solution}
}
#endif

#if defined TARGET_oefprobproprapp5
\latex{
\begin{statement}
	\t[1] \v1 \t[2] \v2.\par
	 \q[1] \n2 \q[2]\par
	 \begin{center}
	 	\begin{tabular}{|l|c|c|}
	 		\hline
			\t[16] & \v2 & \n2 \\ \hline
			\t[17] & \v1 & \ldots \\ \hline
	 	\end{tabular}
	 \end{center}

	\name_instruction:\par
	\[ \ldots \times \dfrac{\ldots}{\ldots}=\ldots\]
\end{statement}

\begin{solution}
	\name_solution: \( \n2 \times \dfrac{\v1}{\v2} = \n1 \)
 \begin{center}
 	\begin{tabular}{|l|c|c|}
 		\hline
		\t[16] & \v2 & \n2 \\ \hline
		\t[17] & \v1 & \n1 \\ \hline
 	\end{tabular}
 \end{center}
\end{solution}
}
#endif
