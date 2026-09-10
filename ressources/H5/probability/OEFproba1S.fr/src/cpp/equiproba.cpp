target=equiproba1 equiproba2 equiproba3

#include "header.inc"

\precision{10000}
\keywords{events,probability,combinatorics}

#if defined TARGET_equiproba1
#define NUM 1
#endif

#if defined TARGET_equiproba2
#define NUM 2
#endif

#if defined TARGET_equiproba3
#define NUM 3
#endif

#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_equiproba1
\integer{n=randint(6..10)}
\integer{tot=\n*(\n-1)*(\n-2)}
\rational{p=1/\tot}
\statement{
 \(\n\) \name_statement1.
<div class="wims_question">
<ol>
<li><label for="reply1">\name_statement2?</label> \embed{reply1,6}</li>
<li> \name_statement3.<br>
<label for="reply2">\name_statement4?</label> \embed{reply2,8}
</li>
</ol>
</div>
<div class="wims_instruction">\name_consig</div>
}
\answer{\name_answer1}{\tot}{type=numexp}
\answer{\name_answer2}{\p}{type=numeric}{option=absolute}
\latex{
\begin{statement}
\n \name_statement1.
\begin{enumerate}
\item \name_statement2?
\item \name_statement3. \name_statement4?
\end{enumerate}
\end{statement}
}
#endif

#if defined TARGET_equiproba2
\integer{ig=randint(1..5)}
\integer{if=randint(1..5)}

\integer{n=randint(10,12,15,20)}
\integer{tot=\n*(\n-1)}
\integer{tot2=\tot/2}
\rational{p1=1/\tot}
\rational{p2=2/\tot}
\statement{
\name_g[\ig] \name_and \name_f[\if] \name_statement1 \n \name_people.
<div class="wims_question">
<ol>
<li> \name_statement2.<br>
<label for="reply1">\name_statement3[1] \name_g[\ig] \name_statement3[2]
\name_f[\if] \name_statement3[3]?</label>
<div class="wimscenter">\embed{reply1,7}</div>
</li>
<li> \name_statement4.<br>
<label for="reply2">\name_question[1]
\name_g[\ig] \name_and \name_f[\if] \name_question[2]?</label>
<div class="wimscenter"> \embed{reply2,7}</div></li>
</ol>
</div>
<div class="wims_instruction">\name_consig</div>
}
\answer{\name_answer 1}{\p1}{type=numexp}
\answer{\name_answer 2}{\p2}{type=numexp}
\solution{ \name_solution1 \(\n \times (\n-1)=\tot\) \name_solution2.<br>
\name_solution3 \(\frac{\tot}{2}=\tot2\) \name_solution4.
}
\latex{
\begin{statement}
\name_g[\ig] \name_and \name_f[\if] \name_statement1 \n \name_people.
\begin{enumerate}
\item \name_statement2.\newline
\name_statement3[1] \name_g[\ig] \name_statement3[2]
\name_f[\if] \name_statement3[3]?
\item 
\name_statement4.\newline
\name_question[1] \name_g[\ig] \name_and \name_f[\if] \name_question[2]?
\end{enumerate}
\end{statement}
\begin{solution}
\name_solution1 \(\n \times (\n-1)=\tot\) \name_solution2.\newline
\name_solution3 \(\frac{\tot}{2}=\tot2\) \name_solution4.
\end{solution}

}
#endif
#if defined TARGET_equiproba3
\integer{n=randint(3..4)}
\integer{n1=\n-1}
\integer{tot=2*\n}
\integer{ntot=(\tot!)/(\n!)^2}
\rational{pA=(\n+1)/(\ntot)}
\rational{pB=2/(\ntot)}
\rational{pC=(\n+1)/(\ntot)}
\statement{
\name_statement1 \n \name_statement2 \n \name_statement3.
\name_statement4 \tot \name_statement5.
<div class="wims_question">
\name_statement6:
<ol>
<li>
 A <span class="wims_emph">"\name_cond1 \n \name_cond2"</span>
<div class="wimscenter"><label for="reply1">\(P(A)\)</label> =\embed{reply1,7}</div></li>
<li>
 B <span class="wims_emph">"\name_cond3"</span>
<div class="wimscenter"><label for="reply2">\(P(B)\)</label> =\embed{reply2,7}</div></li>
<li>
 C <span class="wims_emph">"\name_cond1 \n1 \name_cond4"</span>
<div class="wimscenter"><label for="reply4">\(P(C)\)</label> =\embed{reply3,7}</div></li>
</ol>
</div>
<div class="wims_instruction">\name_consig</div>
}
\answer{\(P(A)\)}{\pA}{type=numexp}
\answer{\(P(B)\)}{\pB}{type=numexp}
\answer{\(P(C)\)}{\pC}{type=numexp}
\solution{
\name_solution1 \(\tot!\) \name_solution2.
\name_solution3 \n \name_solution4 \(\n!\).
\name_solution5 \n \name_solution6 \(\n!\).
\name_solution7 \(\frac{\tot!}{(\n!)^2}=\ntot\) \name_solution8.

<ol>
<li> \name_solution9?
0 \name_or 1 \name_or \(\ldots\) \name_or \n. 
\name_solution10 \(P(A)=\frac{\n+1}{\ntot}=\pA\).
</li>
<li> \name_solution11.
\name_solution10 \(P(B)=\frac{2}{\ntot}=\pB\).
</li>
<li> \name_solution12?
\name_solution13 \(\n+1\) \name_solution14.
\name_solution10 \(P(C)=\frac{\n+1}{\ntot}=\pC\).
</ol>
}
\latex{
\begin{statement}
\name_statement1 \n \name_statement2 \n \name_statement3.
\name_statement4 \tot \name_statement5.\newline
\name_statement6:
\begin{enumerate}
\item  A "\emph{\name_cond1 \n \name_cond2}"
\item  B "\emph{\name_cond3}"
\item  C "\emph{\name_cond1 \n1 \name_cond4}"
\end{enumerate}
\end{statement}
\begin{solution}
\name_solution1 \(\tot!\) \name_solution2.
\name_solution3 \n \name_solution4 \(\n!\).
\name_solution5 \n \name_solution6 \(\n!\).
\name_solution7 \(\frac{\tot!}{(\n!)^2}=\ntot\) \name_solution8.

\begin{enumerate}
\item  \name_solution9?
0 \name_or 1 \name_or \(\ldots\) \name_or \n. 
\name_solution10 \(P(A)=\frac{\n+1}{\ntot}=\pA\).
\item 
 \name_solution11.
\name_solution10 \(P(B)=\frac{2}{\ntot}=\pB\).
\item \name_solution12?
\name_solution13 \(\n+1\) \name_solution14.
\name_solution10 \(P(C)=\frac{\n+1}{\ntot}=\pC\).
\end{enumerate}
\end{solution}
}

#endif
