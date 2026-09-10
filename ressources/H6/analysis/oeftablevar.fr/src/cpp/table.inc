<table class="wimscenter wimsnoborder" style="border: solid black 1px;">
<tr style="border: solid black 1px;"><th style="border-right: solid black 1px;">\(x)</th>
\for{t=1 to \tabcnt}{<td>\xshow[\t]</td><td></td>}
<td>\xshow[\tabcnt+1]</td></tr>
<tr style="border: solid black 1px;">
 <th style="border: solid black 1px;">\(f(x)\)</th>
\for{t=1 to \tabcnt}{
 <td valign="\pos[\t]">\yshow[\t]</td>
 <td><img src="\imagedir/\arrows[\t]\arrowlen.gif" alt="\arrows[\t]"></td>
}
<td valign="\pos[\tabcnt+1]">\yshow[\tabcnt+1]</td></tr>
</table>
