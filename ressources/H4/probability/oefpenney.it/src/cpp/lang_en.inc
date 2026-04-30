#if defined TARGET_partita
\text{name_intro1=Let's play a coin toss game. Choose a triplet of heads
(\testa) and tails (\croce), afterwards the computer chooses its triplet. The coin will be tossed until one of the two triplets appears. If the computer's triplet appears, then the computer wins. If your triplet appears, then you win.}
#endif
#if defined TARGET_giocatore
\text{name_intro1=Let's play a coin toss game. Choose a triplet of heads
(\testa) and tails (\croce), afterwards the computer chooses its triplet. We will toss the coin until one of the two triplets appears. If the computer's triplet appears, then the computer gains one point, and we will start over. If your triplet appears, then you gain one point, and we will start over. Whoever gains the most points wins.}
#endif
#if defined TARGET_computer
\text{name_intro1=Let's play a coin toss game. The computer has chosen its triplet of heads (\testa) and tails (\croce). Now it is your turn to choose your triplet. Afterward we will toss the coin until one of the two triplets appears. If the computer's triplet appears, then the computer gains one point, and we will start over. If your triplet appears, then you gain one point, and we will start over. Whoever gains the most points wins.}
#endif
#if defined TARGET_partita || defined TARGET_giocatore
\text{name_intro3=Choose your triplet.}
#endif
#if defined TARGET_computer
\text{name_intro3=Choose a triplet that is different from the computer's.}
#endif
#if defined TARGET_partita
\text{name_estrazione=Toss}
\text{name_avanti=You win,The computer wins,One more toss}
#endif
#if defined TARGET_computer || defined TARGET_giocatore
\text{name_estrazione=Game}
\text{name_intro2=We will play,games.}
\text{name_avanti=Next game,End game}
\text{name_condition2=Did you spot the end of the match?}
\text{name_feedback_log=Here is a log of the,games}
#endif
#if defined TARGET_partita || defined TARGET_giocatore
\text{name_choice_list=You choose,Thus the computer chooses}
\text{name_answer=Did you understand who won?}
#endif
#if defined TARGET_computer
\text{name_choice_list=You choose,The computer chooses}
#endif
#if defined TARGET_partita
\text{name_instruction=Click on <span class="wims_emph">One more toss</span> until one of the triplets appears and then say who is the winner.}
#endif
#if defined TARGET_partita || defined TARGET_computer || defined TARGET_giocatore
\text{name_condition1=Did you follow the instruction?}
\text{name_punteggio=Score}
\text{name_player_list=You,The computer}
\text{name_whoscore_list=You score one point,The computer scores one point}
\text{name_help=<p>Let's suppose we can toss a fair coin as many times as we want (i.e. a coin that gives heads and tails both with probability equal to 1/2).</p>
<p>The first player chooses a triplet (e.g. <span class="wims_emph">THH</span>), afterwards the second player chooses another triplet (e.g. <span class="wims_emph">HTH</span>). The coin is tossed until one of the chosen triplets appears. The player whose triplet appears first wins.</p>
<p>With the choices above, if the sequence of tosses is <span class="wims_emph">HTTTHTTHH</span>, then the first player wins because the triplet <span class="wims_emph">HTH</span> did not show up, while the triplet <span class="wims_emph">THH</span> appears in the last three tosses. Instead, if the sequence of tosses is <span class="wims_emph">HTTHTH</span>, the second player wins.</p>
<p>Keep in mind that when we start the game, we have no way of knowing how many tosses will be needed to end the game.</p>}
#endif
#if defined TARGET_pairs1 || defined TARGET_pairs2 || defined TARGET_pairs3 || defined TARGET_pairs4
note for translators: keep commas
\text{name_statement_list=In the game you choose,while the computer choose}
#endif
#if defined TARGET_single1
\text{name_statement=In the game the probability that the triplet,appears in the first 3 tosses is}
#endif
#if defined TARGET_single2
\text{name_statement=In the game the probability that the triplet,appears within the first 4 tosses is}
#endif
#if defined TARGET_pairs3
\text{name_question=The probability that you win the game withing the first 4 tosses is}
#endif
#if defined TARGET_pairs4
note for translators: keep commas
\text{name_statement=If,the probability that,is,then}
\text{name_players=you win,the computer wins}
#endif
#if defined TARGET_pairs1
\text{name_statement=At some stage of an ongoing game}
\text{name_cases_list=the last tossed coin is,the two last tossed coins are}
\text{name_then=Then}
#endif
#if defined TARGET_pairs1
\text{ans_list=You will certainly win,The computer will certainly win,It still not possibile to say who will win}
#endif
#if defined TARGET_pairs2
\text{ans_list=The odds are in your favour,The odds are in the computer favour,You both have the same odds,I do not know}
#endif
