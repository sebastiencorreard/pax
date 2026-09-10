\real{ab=\a*\b}
\real{cd=\c*\d}
\real{oppa=-\a}
\real{oppb=-\b}
\real{oppc=-\c}
\real{oppd=-\d}
\real{oppac=-\ac}
%% 1 %%
\if{\a>=0 and \c>=0}{
  \text{SOL=Les deux réels \(x\) et \(y\) sont positifs et vérifient les double-inégalités
  \({\a < x < \b}\) et \({\c < y < \d}\). On les multiplie terme à terme et
  l'on obtient :
  \({\ac < x \times y < \bd}\).}}
%% 2 %%
\if{\b<=0 and \d<=0}{
  \text{SOL=Les réels \(x\) et \(y\) sont négatifs. Les deux réels positifs \(-x\) et \(-y\)
  vérifient les double-inégalités
  \({\oppb < -x < \oppa}\) et \({\oppd < -y < \oppc}\). On les multiplie
  terme à terme et l'on obtient :
  \({\bd < x \times y < \ac}\).
  }
}
%% 3 %%
\if{\a>=0 and \d<=0}{
  \text{SOL=Le réel \(x\) est positif
  et \(y\) est négatif.
  Les deux réels positifs \(x\) et \(-y\) vérifient les double-inégalités
  \({\a < x < \b}\) et \({\oppd < -y < \oppc}\). On les multiplie terme à terme puis on multiplie l'encadrement de \(-(x\times y)\) par \(-1\) pour obtenir cet encadrement de \(x\times y\) :
  \({\bc < x \times y < \ad}\).
  }
}
%% 4 %%
\if{\c>=0 and \b<=0}{
  \text{SOL=Le réel \(x\) est négatif
  et \(y\) est positif.
  Les deux réels positifs \(-x\) et \(y\) vérifient les double-inégalités
  \({\oppb < -x < \oppa}\) et \({\c < x < \d}\). On les multiplie terme à terme puis on multiplie l'encadrement de \(-(x\times y)\) par \(-1\) pour obtenir cet encadrement de \(x\times y\) :
  \({\ad < x \times y < \bc}\).
  }
}
%% 5 %%
\if{\a>=0 and \cd<0}{
  \text{SOL=Le réel \(x\) est positif mais le signe de \(y\) varie selon sa position entre les bornes \(\c\) et \(\d\).
  <p>Dans le cas où \({\c < y \leq 0}\), les réels positifs \(x\) et \(-y\) vérifient les double-inégalités
  \({\a < x < \b}\) et \({0 \leq -y < \oppc}\).
  On les multiplie terme à terme puis on multiplie l'encadrement de \(-(x\times y)\) par \(-1\) pour obtenir cet encadrement partiel de \(x\times y\) :
   \({\bc < x \times y \leq 0}\).</p>
  <p>Dans le cas où \(0 \leq y < \d\), les réels positifs \(x\) et \(y\) vérifient les double-inégalités
  \({\a < x < \b}\) et \({0 \leq y < \d}\).
  On les multiplie terme à terme pour obtenir cet encadrement partiel de \(x\times y\) :
  \({0 \leq x \times y < \bd}\).</p>
  En joignant les deux cas, on obtient l'encadrement final \({\bc < x \times y < \bd}\).
  }
}
%% 6 %%
\if{\b<=0 and \cd<0}{
  \text{SOL=Le réel \(x\) est négatif mais le signe de \(y\) varie selon sa position entre les bornes \(\c\) et \(\d\).
  <p>Dans le cas où \({\c < y \leq 0}\), les réels positifs \(-x\) et \(-y\) vérifient les double-inégalités
  \({\oppb < -x < \oppa}\) et \({0 \leq -y < \oppc}\).
  On les multiplie terme à terme pour obtenir cet encadrement partiel de \(x\times y\) :
  \({0 \leq x \times y \leq \ac}\).</p>
  <p>Dans le cas où \({0 \leq y < \d}\), les deux réels positifs \(-x\) et \(y\) vérifient les double-inégalités \({\oppb < -x < \oppa}\) et \({0 \leq y < \d}\).
  On les multiplie terme à terme puis on multiplie l'encadrement de
  \(-(x\times y)\) par \(-1\) pour obtenir cet encadrement partiel de \(x\times y\) :
  \({\ad \leq x \times y \leq 0}\).</p>
  En joignant les deux cas on obtient l'encadrement final \({\ad < x \times y < \ac}\).
  }
}
%% 7 %%
\if{\ab<0 and \c>=0}{
  \text{SOL=On a \({y > 0}\), mais le signe de \(x\) varie selon sa position entre les bornes \(\a\) et \(\b\).
  <p>Dans le cas où \({\a < x \leq 0}\), les réels positifs \(-x\) et \(y\) vérifient les double-inégalités
  \({0 \leq -x < \oppa}\) et \({\c < y < \d}\).
  On multiplie leur produit terme à terme par \(-1\), d'où l'encadrement \({\ad < x \times y \leq 0}\).</p>
  <p>Dans le cas où \({0 \leq x < \b}\), les réels positifs \(x\) et \(y\) vérifient les double-inégalités
  \({0 \leq x < \b}\) et \({\c < y < \d}\).
  On les multiplie terme à terme, d'où \({0 \leq x \times y < \bd}\).</p>
  En joignant les deux cas on obtient l'encadrement \({\ad < x \times y < \bd}\).
  }
}
%% 8 %%
\if{\ab<0 and \d<=0}{
  \text{SOL=On a \({y < 0}\), mais le signe de \(x\) varie selon sa position entre les bornes \(\a\) et \(\b\).
  <p>Dans le cas où \({\a < x \leq 0}\), les réels positifs \(-x\) et \(-y\) vérifient les double-inégalités
  \({0 \leq -x < \oppa}\) et \({\oppd < -y < \oppc}\).
  On les multiplie terme à terme, d'où
  \({0 \leq x \times y < \ac}\).</p>
  <p>Dans le cas où \({\0 \leq x < \b}\), les réels positifs \(x\) et \(-y\) vérifient les double-inégalités
  \({\0 \leq x < \b}\) et \({\oppd < -y < \oppc}\).
  On les multiplie terme à terme ces et on multiplie le tout par \(-1\), d'où
  \({\bc \leq x \times y \leq 0}\).</p>
  En joignant les deux cas on obtient l'encadrement \({\bc < x \times y < \ac}\).
  }
}
%% 9 %%
\if{\ab<0 and \cd<0}{
  \text{SOL=Le signe de \(x\) varie selon sa position entre les bornes \(\a\) et \(\b\) et celui de \(y\) entre les bornes \(\c\) et \(\d\).
  <p>Dans le cas où \({0 \leq x < \b}\) et \({0 \leq y < \d}\), les deux réels \(x\) et \(y\) sont positifs. On multiplie terme à terme ces double-inégalités,
  d'où \({0 \leq x \times y < \bd}\).</p>
  <p>Dans le cas où \({\a < x \leq 0}\) et \({\c < y \leq 0}\), les réels positifs \(-x\) et \(-y\) vérifient les double-inégalités
  \({0 \leq -x < \oppa}\) et \({0 \leq -y < \oppc}\).
  On les multiplie terme à terme, d'où
  \({0 \leq x \times y < \ac}\).</p>
  <p>Dans le cas où \({\a < x \leq 0}\) et \({0 \leq y < \d}\), les réels positifs \(-x\) et \(y\) vérifient les double-inégalités \({0 \leq -x < \oppa}\) et \({0 \leq y < \d}\).
  On les multiplie terme à terme et on multiplie le tout par \(-1\), d'où \({\ad < x \times y \leq 0}\).</p>
  <p>Dans le cas où \({0 \leq x < \b}\) et \({\c < y \leq 0}\), les réels positifs \(x\) et \(-y\) vérifient les double-inégalités \({0 \leq x < \b}\) et \({0 \leq -y < \oppc}\).
  On les multiplie terme à terme et on multiplie le tout par \(-1\), d'où
  \({\bc < x \times y \leq 0}\).</p>
  En joignant les quatre cas on obtient l'encadrement \({P_1 < x \times y < P_2}\) avec pour bornes : \({P_1 = min(\ad, \bc) = \res1}\) et \({P_2 = max(\ac, \bd) = \res2}\).
  }
}

\text{Explication=<p>Dans le plan muni d'un repère
  \(( O \overrightarrow{x}\textrm{,} O \overrightarrow{y} )\),
  l'ensemble des points de coordonnées \((x,y)\) vérifiant les inégalités
  \({\a < x < \b}\) et \({\c < y <\d}\)
  est le rectangle <span style="color:red";>rouge</span> situé entre les deux courbes vertes
  (hyperboles) d'équations \(y = \frac{\res1}{x}\) et \(y = \frac{\res2}{x}\).</p>
  <p>Les coefficients \(\res1\) et \(\res2\) figurent les bornes
  qui encadrent le produit \(P = x\cdot y\) pour tout point \((x,y)\)
  du rectangle rouge.</em></p>
}
