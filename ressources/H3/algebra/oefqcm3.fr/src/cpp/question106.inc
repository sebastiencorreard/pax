\title{Question 106&#8718; Repérer une fraction sur la ligne numérique}
\keywords{quizz,fraction,number_line}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-a-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }

% Nom des points
\text{lettres=A,B,C,E,F,G,H,I,J,K,L,M,N,P,R,S,T,U,V,W,X,Y,Z}
\text{sh=shuffle(items(\lettres))}
\text{A=\lettres[\sh[1]]}

% Dénominateur
\integer{denominateur=randint(2..6)}

% Numérateur
\integer{numerateur=randint(randint(1..(\denominateur-1)),randint((\denominateur+1)..(2*\denominateur-1)))}

\text{rep=\(\numerateur/\denominateur)}

%% distracteurs
\if{\numerateur<\denominateur}{
    % "complément" à l'unité
    \integer{a=\denominateur-\numerateur}
    \text{distracteurs=\(\numerateur.\a),\(\numerateur/\a),\(\denominateur/\numerateur),\(0.\numerateur)}
  \if{\a!=\numerateur}{
    \text{distracteurs=\distracteurs,\(\a/\denominateur),\(\a/\numerateur),\(\denominateur/\a)}
  }
}

\if{\numerateur>\denominateur}{
  % en plus de l'unité
  \integer{a=\numerateur-\denominateur}
  \text{distracteurs=\(1/\denominateur),\(\denominateur.\a),\(\numerateur/\numerateur),\(\denominateur/\numerateur),\(\a/\numerateur)}
  %%% MB si \a=1 on avait un double affichage
  \if{\a!=1}{\text{distracteurs=\distracteurs,\(\a/\denominateur)}}
}

% Tirage distracteurs
\integer{n_distracteurs=items(\distracteurs)}
\text{shuffle=shuffle(\n_distracteurs)}
\text{shuffle=item(1..3,\shuffle)}
\text{distracteurs=\distracteurs[\shuffle[1]],\distracteurs[\shuffle[2]],\distracteurs[\shuffle[3]]}

\text{good=\rep}
\text{bads=\distracteurs}

%% ligne numérique

% Préparation dessin
\if{\denominateur=2}{
\integer{size_unite_x=randint(40..60)}
}
\if{\denominateur=3}{
\integer{size_unite_x=randint(30..45)}
}
\if{\denominateur=4}{
\integer{size_unite_x=randint(25..40)}
}
\if{\denominateur>4}{
\integer{size_unite_x=randint(20..30)}
}
\integer{size_unite_y=25}

\real{xmin=-1.5}
\real{xmax=max(\denominateur,\numerateur)+1.5}
\real{ymin=-1}
\real{ymax=1}

% Correction décalage lettres pour nom du point
\real{correction_x=4/\size_unite_x}
\real{correction_y=-8/\size_unite_y}

% Tracé lignes verticales
\text{lignes_verticales=}
\for{k=ceil(\xmin) to floor(\xmax)}{
  \text{lignes_verticales=\lignes_verticales
    segment \k,\ymin,\k,\ymax,grey}
}


\integer{size_x=(\xmax-\xmin)*\size_unite_x}
\integer{size_y=(\ymax-\ymin)*\size_unite_y}

\text{ligne_numerique=draw(\size_x,\size_y
xrange \xmin,\xmax
yrange \ymin,\ymax
\lignes_verticales
line 0,0,10,0,black
crosshairs black, 0,0, \denominateur,0, \numerateur,0
text black, 0-\correction_x, \correction_y,giant,0
text black, \denominateur-\correction_x, \correction_y,giant,1
text black, \numerateur-\correction_x, \correction_y,giant,\A
)}


%% Enoncé

\text{enonce=<div class="wimscenter"><img src="\ligne_numerique" alt=""><br> Quelle est l'abscisse du point \A&nbsp;&#63;</div> }
\text{enonceb=}




%% Feedback
% Préparation feedback
\text{nom_denominateur=unités,demis,tiers,quarts,cinquièmes,sixièmes,septièmes,huitièmes,neuvièmes,dixièmes}
\text{nom_denominateur=\nom_denominateur[\denominateur]}

\text{feedback=
L'unité est partagée en \denominateur morceaux de la même taille&#44; ce sont donc des \nom_denominateur.
<br>Il y a \numerateur morceaux jusqu'au point \A. 
<br>
<br>Le point \A a donc pour abscisse \(\numerateur/\denominateur).
}
