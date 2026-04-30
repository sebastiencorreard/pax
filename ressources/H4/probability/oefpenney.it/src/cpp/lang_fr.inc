#if defined TARGET_partita
\text{name_intro1=Nous allons jouer à un jeu de pile ou face. Choisissez une suite de trois piles (\croce) ou faces (\testa), puis l'ordinateur fait de même. La pièce sera lancée jusqu'à ce qu'un des deux triplets choisis apparaisse. Si le triplet de l'ordinateur apparaît, alors il gagne. Si votre triplet apparaît, alors vous gagnez. }
#endif
#if defined TARGET_giocatore
\text{name_intro1=Nous allons jouer à un jeu de pile ou face. Choisissez la suite de trois piles ou faces sur laquelle vous pariez. L'ordinateur choisira également un triplet de piles ou faces. Nous lancerons la pièce jusqu'à ce qu'un des deux triplets apparaisse. Si le triplet de l'ordinateur apparaît, alors l'ordinateur gagne un point et nous commencerons une nouvelle partie. Si votre triplet apparaît, alors vous gagnez un point et nous commencerons une nouvelle partie. Celui qui obtient le plus de points gagne. }
#endif
#if defined TARGET_computer
\text{name_intro1=Nous allons jouer à pile ou face. L'ordinateur parie sur une suite de trois piles (\croce) ou faces (\testa). C'est maintenant à votre tour de choisir votre triplet. Ensuite, nous lancerons la pièce jusqu'à ce que l'un des deux triplets apparaisse. Si le triplet de l'ordinateur apparaît, alors l'ordinateur gagne un point et nous commencerons une nouvelle partie. Si votre triplet apparaît, alors vous gagnez un point et nous commencerons une nouvelle partie. Celui qui obtient le plus de points gagne. }
#endif
#if defined TARGET_partita || defined TARGET_giocatore
\text{name_intro3=Choisissez votre suite de trois piles (\croce) ou faces (\testa).}
#endif
#if defined TARGET_computer
\text{name_intro3=Choisissez un triplet différent de celui de l'ordinateur}
#endif
#if defined TARGET_partita
\text{name_estrazione=Lancer}
\text{name_avanti=Vous avez gagné,L'ordinateur a gagné,Encore un lancer}
#endif
#if defined TARGET_computer || defined TARGET_giocatore
\text{name_estrazione=Partie}
\text{name_intro2=Nous allons jouer,parties.}
\text{name_avanti=Partie suivante,Fin du jeu}
\text{name_condition2=Avez-vous effectué le bon nombre de parties&nbsp;?}
\text{name_feedback_log=Voici les suites obtenues au cours des,parties}
#endif
#if defined TARGET_partita || defined TARGET_giocatore
\text{name_choice_list=Vous choisissez,Ensuite l'ordinateur choisit}
\text{name_answer=Avez-vous compris quand la partie se termine et qui gagne&nbsp;?}
#endif
#if defined TARGET_computer
\text{name_choice_list=Vous choisissez,L'ordinateur choisit}
#endif
#if defined TARGET_partita
\text{name_instruction=Cliquer sur le bouton <span class="wims_button oef_renew disabled">Encore un lancer</span> jusqu'à ce qu'un des triplets apparaisse  et dire alors qui est le gagnant.}
#endif
#if defined TARGET_partita || defined TARGET_computer || defined TARGET_giocatore
\text{name_condition1=Avez-vous suivi les instructions&nbsp;?}
\text{name_punteggio=Score}
\text{name_player_list=Vous,l'ordinateur}
\text{name_whoscore_list=Vous marquez un point&nbsp;,L'ordinateur marque un point&nbsp;}
\text{name_help=<p>Supposons que nous puissions lancer une pièce de monnaie aussi souvent que nous le voulons et que celle-ci tombe sur pile (P) ou face (F) avec probabilité 1/2 à chaque lancer.</p>
<p>Le premier joueur choisit un triplet (ex. <span class="wims_emph">PFF</span>), ensuite le deuxième joueur choisit un autre triplet (ex. <span class="wims_emph">FPF</span>). La pièce est lancée jusqu'à ce qu'un de ces triplets choisis apparaisse. Le joueur dont le triplet apparaît en premier gagne.</p>
<p>Avec les choix ci-dessus, si les premiers lancers donne la suite <span class="wims_emph">FPPPFPPFF</span>, alors la partie s'arrête et le premier joueur gagne puisque le triplet <span class="wims_emph">PFF</span> est apparu. Par contre, si la suite de lancers commence par <span class="wims_emph">FPPFPF</span>, le second joueur gagne.</p>
<p>Gardez à l'esprit que lorsque nous commençons une partie, nous n'avons aucun moyen de savoir combien de lancers seront nécessaires pour terminer cette partie. </p>}
#endif
#if defined TARGET_pairs1 || defined TARGET_pairs2 || defined TARGET_pairs3 || defined TARGET_pairs4
note for translators: keep commas
\text{name_statement_list=Lors d'une série de lancers d'une pièce&#44; vous pariez sur l'apparition du triplet,tandis que l'ordinateur choisit}
#endif
#if defined TARGET_single1
\text{name_statement=Dans un jeu de pile ou face la probabilité que le triplet,apparaisse dans les 3 premiers lancers est}
#endif
#if defined TARGET_single2
\text{name_statement=Dans le jeu de pile ou face la probabilité que le triplet,apparaisse dans les 4 premiers lancers est}
#endif
#if defined TARGET_pairs3
\text{name_question=La probabilité que vous gagniez la partie en 4 lancers (c'est-à-dire que le triplet que vous avez choisi apparaisse avant celui de l'ordinateur et au cours des 4 premiers lancers) est de}
#endif
#if defined TARGET_pairs4
note for translators: keep commas
\text{name_statement=Si,la probabilité que,est,alors}
\text{name_players=vous gagniez,l'ordinateur gagne}
#endif
#if defined TARGET_pairs1
\text{name_statement=Si à un certain stade d'une partie }
\text{name_cases_list=la dernière pièce lancée est,les deux dernières pièces lancées sont}
\text{name_then=alors}
#endif
#if defined TARGET_pairs1
\text{ans_list=vous gagnerez certainement la partie,l'ordinateur gagnera certainement la partie,il n'est pas encore possible de dire qui va gagner la partie}
#endif
#if defined TARGET_pairs2
\text{ans_list=C'est vous qui avez le plus de chance de gagner.,C'est l'ordinateur qui a le plus de chance de gagner.,Vous avez tous les deux la même chance de gagner.,Je ne sais pas.}
#endif
