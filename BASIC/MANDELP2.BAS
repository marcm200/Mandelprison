1 GOTO 8722
10 REM Mandelprison - Free Benoit!
11 REM text adventure in style of Thor - Trilogy for Schneider CPC464 from the 80s
12 REM Marc Meidlinger May 2022
1000 comp%=4:room%=0:perc%=c04perc%:hc%=0:mult!=0.96317:GOSUB 50000
1001 doors$="0001":GOSUB 50100
1002 PRINT dash$:PRINT"You see:":PRINT
1003 IF nfa0400%<=0 THEN PRINT"* a note on the floor":GOTO 1007
1004 PRINT"* a note saying:":PEN 2
1005 PRINT" This component's area equals 3/8*PI."
1006 PEN 1
1007 :
1008 GOSUB 50200
1009 IF ve%=7 AND ob%=12 THEN GOTO 1100
1010 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0400%=1:GOTO 1000
1011 PRINT"Command not applicable.":GOSUB 52700:GOTO 1000
1100 comp%=4:room%=1:perc%=c04perc%:hc%=0:mult!=0.1226:GOSUB 50000
1101 doors$="1011":GOSUB 50100
1102 PRINT dash$:PRINT"You see:":PRINT
1103 GOSUB 50200
1104 IF ve%=7 AND ob%=9 THEN GOTO 1400
1105 IF ve%=7 AND ob%=11 THEN GOTO 1000
1106 IF ve%=7 AND ob%=12 THEN GOTO 1200
1107 PRINT"Command not applicable.":GOSUB 52700:GOTO 1100
1200 comp%=4:room%=2:perc%=c04perc%:hc%=1:mult!=0.010479:GOSUB 50000
1201 doors$="0010":GOSUB 50100
1202 PRINT dash$:PRINT"You see:":PRINT
1203 PRINT"* an inactive transmitter"
1204 PRINT"* Benoit Mandelbrot in a prison cell"
1205 GOSUB 50200
1206 IF ve%=7 AND ob%=11 THEN GOTO 1100
1207 IF (ve%=3 AND ob%=3)OR(ve%=4 AND ob%=6) THEN GOTO 1209
1208 PRINT"Command not applicable.":GOSUB 52700:GOTO 1200
1209 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"Benoit's cell door."
1210 PRINT:PRINT"But beware! You only have a limited":PRINT"number of  !":PRINT
1211 PEN 2
1212 PRINT" Affinely conjugate the Mandelbrot"
1213 PRINT" set p(z)=z^2+d with the logistic map"
1214 PRINT" f(z)=c*z*(1-z) via h(z)=v*z+w such"
1215 PRINT" that h(p(z))=f(h(z))."
1216 PEN 1:PRINT
1217 PRINT"  (0) v=1/c,w=1/2,d=(2*c+c^2)/4"
1218 PRINT"  (1) v=1/c,w=2,d=(2*c+c^2)/5"
1219 PRINT"  (2) v=-1/c,w=1/2,d=-(c^2-2*c)/4"
1220 PRINT"  (3) v=sqrt(1/c),w=-1/2,d=-(c^2-2*c)/4"
1221 IF hex%>0 THEN PRINT"The magic oracle tells: '2'"
1222 cellc%=0:FOR cellloop%=1 TO 1 STEP -1
1223 PRINT:PRINT"Your answer (";cellloop%;"attempts left) ";:INPUT"> ",cellans%
1224 IF cellans%=2 THEN cellloop%=0:cellc%=1
1225 NEXT
1226 IF cellc%<=0 THEN PRINT:PRINT"An alarm went off. You will be":PRINT"teleported back to the game start":PRINT"but retain your knowledge.":INPUT"[please press enter]",waitkey$:GOTO 8100
1227 CLS:PRINT dash$:PRINT"Congratulations!":PRINT dash$:PRINT"You have successfully completed your"
1228 PRINT"task! Benoit Mandelbrot has been":PRINT"rescued, and mathematics saved!":PRINT:END
1300 comp%=4:room%=3:perc%=c04perc%:hc%=0:mult!=0.97926:GOSUB 50000
1301 doors$="0001":GOSUB 50100
1302 PRINT dash$:PRINT"You see:":PRINT
1303 GOSUB 50200
1304 IF ve%=7 AND ob%=12 THEN GOTO 1400
1305 PRINT"Command not applicable.":GOSUB 52700:GOTO 1300
1400 comp%=4:room%=4:perc%=c04perc%:hc%=0:mult!=0.75237:GOSUB 50000
1401 doors$="1110":GOSUB 50100
1402 PRINT dash$:PRINT"You see:":PRINT
1403 GOSUB 50200
1404 IF ve%=7 AND ob%=9 THEN GOTO 1500
1405 IF ve%=7 AND ob%=10 THEN GOTO 1100
1406 IF ve%=7 AND ob%=11 THEN GOTO 1300
1407 PRINT"Command not applicable.":GOSUB 52700:GOTO 1400
1500 comp%=4:room%=5:perc%=c04perc%:hc%=0:mult!=0.84248:GOSUB 50000
1501 doors$="0101":GOSUB 50100
1502 PRINT dash$:PRINT"You see:":PRINT
1503 GOSUB 50200
1504 IF ve%=7 AND ob%=10 THEN GOTO 1400
1505 IF ve%=7 AND ob%=12 THEN GOTO 1600
1506 PRINT"Command not applicable.":GOSUB 52700:GOTO 1500
1600 comp%=4:room%=6:perc%=c04perc%:hc%=0:mult!=0.9584:GOSUB 50000
1601 doors$="0012":GOSUB 50100
1602 PRINT dash$:PRINT"You see:":PRINT
1603 GOSUB 50200
1604 IF ve%=7 AND ob%=11 THEN GOTO 1500
1605 IF ve%=7 AND ob%=12 THEN pinc%=1:GOSUB 52800:IF pinout%>0 THEN c04perc%=1:GOTO 8300 ELSE GOTO 1600
1606 PRINT"Command not applicable.":GOSUB 52700:GOTO 1600
1700 comp%=10:room%=0:perc%=c10perc%:hc%=0:mult!=0.52545:GOSUB 50000
1701 doors$="1000":GOSUB 50100
1702 PRINT dash$:PRINT"You see:":PRINT
1703 GOSUB 50200
1704 IF ve%=7 AND ob%=9 THEN GOTO 1900
1705 PRINT"Command not applicable.":GOSUB 52700:GOTO 1700
1800 comp%=10:room%=1:perc%=c10perc%:hc%=0:mult!=0.96924:GOSUB 50000
1801 doors$="1021":GOSUB 50100
1802 PRINT dash$:PRINT"You see:":PRINT
1803 IF ncl1001%>0 THEN PRINT"* a locked case":GOTO 1807
1804 PRINT"* a case with a note saying:":PEN 2
1805 PRINT" Current component's period equals 3."
1806 PEN 1
1807 :
1808 GOSUB 50200
1809 IF ve%=7 AND ob%=9 THEN GOTO 2000
1810 IF ve%=7 AND ob%=11 THEN pinc%=3:GOSUB 52800:IF pinout%>0 THEN c10perc%=3:GOTO 3000 ELSE GOTO 1800
1811 IF ve%=7 AND ob%=12 THEN GOTO 1900
1812 IF ncl1001%>0 AND ve%=3 AND ob%=2 THEN GOTO 1814
1813 PRINT"Command not applicable.":GOSUB 52700:GOTO 1800
1814 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
1815 PEN 2
1816 PRINT" The algorithm by Figueiredo et al to"
1817 PRINT" draw a superset of the filled-in"
1818 PRINT" Julia set of a polynomial owns a key"
1819 PRINT" feature, which is ..."
1820 PEN 1:PRINT
1821 PRINT"  (0) cell-mapping with 1-iterate"
1822 PRINT"  (1) tremendously high precision"
1823 PRINT"  (2) a time complexiy of sub-linear"
1824 PRINT"  (3) highly parallelized"
1825 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 0":PRINT
1826 INPUT"Your answer > ",nicans%
1827 IF nicans%=0 THEN ncl1001%=0 ELSE PRINT"Incorrect.":GOSUB 52700
1828 GOTO 1800
1900 comp%=10:room%=2:perc%=c10perc%:hc%=0:mult!=0.10525:GOSUB 50000
1901 doors$="0110":GOSUB 50100
1902 PRINT dash$:PRINT"You see:":PRINT
1903 GOSUB 50200
1904 IF ve%=7 AND ob%=10 THEN GOTO 1700
1905 IF ve%=7 AND ob%=11 THEN GOTO 1800
1906 PRINT"Command not applicable.":GOSUB 52700:GOTO 1900
2000 comp%=10:room%=3:perc%=c10perc%:hc%=0:mult!=0.95365:GOSUB 50000
2001 doors$="0121":GOSUB 50100
2002 PRINT dash$:PRINT"You see:":PRINT
2003 GOSUB 50200
2004 IF ve%=7 AND ob%=10 THEN GOTO 1800
2005 IF ve%=7 AND ob%=11 THEN pinc%=3:GOSUB 52800:IF pinout%>0 THEN c10perc%=3:GOTO 2600 ELSE GOTO 2000
2006 IF ve%=7 AND ob%=12 THEN GOTO 2100
2007 PRINT"Command not applicable.":GOSUB 52700:GOTO 2000
2100 comp%=10:room%=4:perc%=c10perc%:hc%=1:mult!=0.00010751:GOSUB 50000
2101 doors$="0010":GOSUB 50100
2102 PRINT dash$:PRINT"You see:":PRINT
2103 IF nbh1004%>0 THEN PRINT"* a mirror hinging on one corner":GOTO 2110
2104 IF nbh1004%<=0 AND nba1004%<=0 THEN PRINT"* a note behind the mirror":GOTO 2110
2105 PRINT"* a note behind the mirror saying:":PEN 2
2106 PRINT" The Manhattan distance from this"
2107 PRINT" room to the center of the main"
2108 PRINT" cardioid is approximately 1.75483"
2109 PEN 1
2110 :
2111 GOSUB 50200
2112 IF ve%=7 AND ob%=11 THEN GOTO 2000
2113 IF nbh1004%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba1004%=1:GOTO 2100
2114 IF nbh1004%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh1004%=0:GOTO 2100
2115 PRINT"Command not applicable.":GOSUB 52700:GOTO 2100
2200 comp%=11:room%=0:perc%=c11perc%:hc%=0:mult!=0.93319:GOSUB 50000
2201 doors$="0021":GOSUB 50100
2202 PRINT dash$:PRINT"You see:":PRINT
2203 GOSUB 50200
2204 IF ve%=7 AND ob%=11 THEN pinc%=6:GOSUB 52800:IF pinout%>0 THEN c11perc%=6:GOTO 8200 ELSE GOTO 2200
2205 IF ve%=7 AND ob%=12 THEN GOTO 2300
2206 PRINT"Command not applicable.":GOSUB 52700:GOTO 2200
2300 comp%=11:room%=1:perc%=c11perc%:hc%=0:mult!=0.57011:GOSUB 50000
2301 doors$="1011":GOSUB 50100
2302 PRINT dash$:PRINT"You see:":PRINT
2303 GOSUB 50200
2304 IF ve%=7 AND ob%=9 THEN GOTO 2500
2305 IF ve%=7 AND ob%=11 THEN GOTO 2200
2306 IF ve%=7 AND ob%=12 THEN GOTO 2400
2307 PRINT"Command not applicable.":GOSUB 52700:GOTO 2300
2400 comp%=11:room%=2:perc%=c11perc%:hc%=0:mult!=0.59979:GOSUB 50000
2401 doors$="0010":GOSUB 50100
2402 PRINT dash$:PRINT"You see:":PRINT
2403 GOSUB 50200
2404 IF ve%=7 AND ob%=11 THEN GOTO 2300
2405 PRINT"Command not applicable.":GOSUB 52700:GOTO 2400
2500 comp%=11:room%=3:perc%=c11perc%:hc%=1:mult!=0.000045962:GOSUB 50000
2501 doors$="0101":GOSUB 50100
2502 PRINT dash$:PRINT"You see:":PRINT
2503 IF nbh1103%>0 THEN PRINT"* a mirror hinging on one corner":GOTO 2510
2504 IF nbh1103%<=0 AND nba1103%<=0 THEN PRINT"* a note behind the mirror":GOTO 2510
2505 PRINT"* a note behind the mirror saying:":PEN 2
2506 PRINT" The Manhattan distance from this"
2507 PRINT" room to the center of the main"
2508 PRINT" cardioid is approximately 1.772895"
2509 PEN 1
2510 :
2511 PRINT"* an inactive transmitter"
2512 GOSUB 50200
2513 IF ve%=7 AND ob%=10 THEN GOTO 2300
2514 IF ve%=7 AND ob%=12 THEN GOTO 2600
2515 IF nbh1103%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba1103%=1:GOTO 2500
2516 IF nbh1103%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh1103%=0:GOTO 2500
2517 PRINT"Command not applicable.":GOSUB 52700:GOTO 2500
2600 comp%=11:room%=4:perc%=c11perc%:hc%=0:mult!=0.95346:GOSUB 50000
2601 doors$="0012":GOSUB 50100
2602 PRINT dash$:PRINT"You see:":PRINT
2603 IF ncl1104%>0 THEN PRINT"* a locked case":GOTO 2607
2604 PRINT"* a case with a note saying:":PEN 2
2605 PRINT" Current component's period equals 6."
2606 PEN 1
2607 :
2608 GOSUB 50200
2609 IF ve%=7 AND ob%=11 THEN GOTO 2500
2610 IF ve%=7 AND ob%=12 THEN pinc%=6:GOSUB 52800:IF pinout%>0 THEN c11perc%=6:GOTO 2000 ELSE GOTO 2600
2611 IF ncl1104%>0 AND ve%=3 AND ob%=2 THEN GOTO 2613
2612 PRINT"Command not applicable.":GOSUB 52700:GOTO 2600
2613 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
2614 PEN 2
2615 PRINT" f(z)=z^3+(-0.5-1.875*i)*z^2+(-2+0.875"
2616 PRINT" *i)*z+(0.75+i) harbours two"
2617 PRINT" attracting cycles: length 16 and 17."
2618 PRINT" What happens to the cycles if one"
2619 PRINT" considers the 2-iterate G(z) :="
2620 PRINT" f(f(z))?"
2621 PEN 1:PRINT
2622 PRINT"  (0) the cycles in G stay the same as in f"
2623 PRINT"  (1) the critical points of f swap the cycle they enter in G"
2624 PRINT"  (2) the odd cycle doubles its length and the even cycle remains unchanged in G"
2625 PRINT"  (3) the odd cycle remains unchanged, the even cycle splits into two cycles       of half the length in G"
2626 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 3":PRINT
2627 INPUT"Your answer > ",nicans%
2628 IF nicans%=3 THEN ncl1104%=0 ELSE PRINT"Incorrect.":GOSUB 52700
2629 GOTO 2600
2700 comp%=12:room%=0:perc%=c12perc%:hc%=0:mult!=0.19283:GOSUB 50000
2701 doors$="0001":GOSUB 50100
2702 PRINT dash$:PRINT"You see:":PRINT
2703 GOSUB 50200
2704 IF ve%=7 AND ob%=12 THEN GOTO 2800
2705 PRINT"Command not applicable.":GOSUB 52700:GOTO 2700
2800 comp%=12:room%=1:perc%=c12perc%:hc%=0:mult!=0.16523:GOSUB 50000
2801 doors$="1010":GOSUB 50100
2802 PRINT dash$:PRINT"You see:":PRINT
2803 IF ncl1201%>0 THEN PRINT"* a locked case":GOTO 2808
2804 PRINT"* a case with a note saying:":PEN 2
2805 PRINT" This component does not hide a clue"
2806 PRINT" to its periodicity."
2807 PEN 1
2808 :
2809 GOSUB 50200
2810 IF ve%=7 AND ob%=9 THEN GOTO 2900
2811 IF ve%=7 AND ob%=11 THEN GOTO 2700
2812 IF ncl1201%>0 AND ve%=3 AND ob%=2 THEN GOTO 2814
2813 PRINT"Command not applicable.":GOSUB 52700:GOTO 2800
2814 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
2815 PEN 2
2816 PRINT" f(z)=z^2+z*e^(2*PI*i*A) has an"
2817 PRINT" indifferent fix point at z=0. Which"
2818 PRINT" set below with respect to the value A"
2819 PRINT" is the largest (in the sense of"
2820 PRINT" strict superset), that allows the"
2821 PRINT" existence of a Siegel disk?"
2822 PEN 1:PRINT
2823 PRINT"  (0) Q+ (positive rational numbers)"
2824 PRINT"  (1) R-Q (all strictly irrational numbers)"
2825 PRINT"  (2) CT (strictly irrational numbers of constant type continued fraction expansion)"
2826 PRINT"  (3) Brjuno set (strictly irrational numbers fulfilling the Brjuno condition sum[log(q_(n+1))/q_n] < inf       with q_n being the denominator of the n-th rational approximation"
2827 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 3":PRINT
2828 INPUT"Your answer > ",nicans%
2829 IF nicans%=3 THEN ncl1201%=0 ELSE PRINT"Incorrect.":GOSUB 52700
2830 GOTO 2800
2900 comp%=12:room%=2:perc%=c12perc%:hc%=1:mult!=0.0014747:GOSUB 50000
2901 doors$="0101":GOSUB 50100
2902 PRINT dash$:PRINT"You see:":PRINT
2903 PRINT"* an active transmitter"
2904 GOSUB 50200
2905 IF ve%=7 AND ob%=10 THEN GOTO 2800
2906 IF ve%=7 AND ob%=12 THEN GOTO 3000
2907 IF ve%=5 AND ob%=5 THEN GOTO 3600
2908 PRINT"Command not applicable.":GOSUB 52700:GOTO 2900
3000 comp%=12:room%=3:perc%=c12perc%:hc%=0:mult!=0.75638:GOSUB 50000
3001 doors$="0012":GOSUB 50100
3002 PRINT dash$:PRINT"You see:":PRINT
3003 IF nfa1203%<=0 THEN PRINT"* a note on the floor":GOTO 3008
3004 PRINT"* a note saying:":PEN 2
3005 PRINT" The Euclidean distance to Benoit's"
3006 PRINT" cell is approx. 1.76826"
3007 PEN 1
3008 :
3009 GOSUB 50200
3010 IF ve%=7 AND ob%=11 THEN GOTO 2900
3011 IF ve%=7 AND ob%=12 THEN pinc%=63:GOSUB 52800:IF pinout%>0 THEN c12perc%=63:GOTO 1800 ELSE GOTO 3000
3012 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa1203%=1:GOTO 3000
3013 PRINT"Command not applicable.":GOSUB 52700:GOTO 3000
3100 comp%=13:room%=0:perc%=c13perc%:hc%=0:mult!=0.86814:GOSUB 50000
3101 doors$="1001":GOSUB 50100
3102 PRINT dash$:PRINT"You see:":PRINT
3103 GOSUB 50200
3104 IF ve%=7 AND ob%=9 THEN GOTO 3600
3105 IF ve%=7 AND ob%=12 THEN GOTO 3200
3106 PRINT"Command not applicable.":GOSUB 52700:GOTO 3100
3200 comp%=13:room%=1:perc%=c13perc%:hc%=0:mult!=0.77511:GOSUB 50000
3201 doors$="1011":GOSUB 50100
3202 PRINT dash$:PRINT"You see:":PRINT
3203 GOSUB 50200
3204 IF ve%=7 AND ob%=9 THEN GOTO 3700
3205 IF ve%=7 AND ob%=11 THEN GOTO 3100
3206 IF ve%=7 AND ob%=12 THEN GOTO 3300
3207 PRINT"Command not applicable.":GOSUB 52700:GOTO 3200
3300 comp%=13:room%=2:perc%=c13perc%:hc%=0:mult!=0.83031:GOSUB 50000
3301 doors$="1010":GOSUB 50100
3302 PRINT dash$:PRINT"You see:":PRINT
3303 GOSUB 50200
3304 IF ve%=7 AND ob%=9 THEN GOTO 3800
3305 IF ve%=7 AND ob%=11 THEN GOTO 3200
3306 PRINT"Command not applicable.":GOSUB 52700:GOTO 3300
3400 comp%=13:room%=3:perc%=c13perc%:hc%=0:mult!=0.90679:GOSUB 50000
3401 doors$="1001":GOSUB 50100
3402 PRINT dash$:PRINT"You see:":PRINT
3403 IF ncl1303%>0 THEN PRINT"* a locked case":GOTO 3408
3404 PRINT"* a case with a note saying:":PEN 2
3405 PRINT" The leftmost digit of the"
3406 PRINT" periodicity is a 6."
3407 PEN 1
3408 :
3409 GOSUB 50200
3410 IF ve%=7 AND ob%=9 THEN GOTO 4000
3411 IF ve%=7 AND ob%=12 THEN GOTO 3500
3412 IF ncl1303%>0 AND ve%=3 AND ob%=2 THEN GOTO 3414
3413 PRINT"Command not applicable.":GOSUB 52700:GOTO 3400
3414 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
3415 PEN 2
3416 PRINT" Let f(z)=[(z^2+L-1)/(2*z+L-2)]^5 with"
3417 PRINT" L=1.824. The point z0=-1.1484375 has"
3418 PRINT" a particular property, which is ..."
3419 PEN 1:PRINT
3420 PRINT"  (0) a parabolic fix point"
3421 PRINT"  (1) a pole of f(z)"
3422 PRINT"  (2) lies inside a buried real interval in the Julia set"
3423 PRINT"  (3) forms a single point Fatou component"
3424 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 2":PRINT
3425 INPUT"Your answer > ",nicans%
3426 IF nicans%=2 THEN ncl1303%=0 ELSE PRINT"Incorrect.":GOSUB 52700
3427 GOTO 3400
3500 comp%=13:room%=4:perc%=c13perc%:hc%=0:mult!=0.78284:GOSUB 50000
3501 doors$="1011":GOSUB 50100
3502 PRINT dash$:PRINT"You see:":PRINT
3503 IF ncl1304%>0 THEN PRINT"* a locked case":GOTO 3510
3504 PRINT"* a case with a note saying:":PEN 2
3505 PRINT" The series 1,1,2,4 (or a"
3506 PRINT" permutation thereof) depicts a"
3507 PRINT" route to the exit, once you've"
3508 PRINT" found the STARTing room."
3509 PEN 1
3510 :
3511 GOSUB 50200
3512 IF ve%=7 AND ob%=9 THEN GOTO 4800
3513 IF ve%=7 AND ob%=11 THEN GOTO 3400
3514 IF ve%=7 AND ob%=12 THEN GOTO 3600
3515 IF ncl1304%>0 AND ve%=3 AND ob%=2 THEN GOTO 3517
3516 PRINT"Command not applicable.":GOSUB 52700:GOTO 3500
3517 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
3518 PEN 2
3519 PRINT" How many ghost components does the"
3520 PRINT" Mandelbrot set have?"
3521 PEN 1:PRINT
3522 PRINT"  (0) 0"
3523 PRINT"  (1) finitely many"
3524 PRINT"  (2) currently unknown"
3525 PRINT"  (3) infinitely many"
3526 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 2":PRINT
3527 INPUT"Your answer > ",nicans%
3528 IF nicans%=2 THEN ncl1304%=0 ELSE PRINT"Incorrect.":GOSUB 52700
3529 GOTO 3500
3600 comp%=13:room%=5:perc%=c13perc%:hc%=0:mult!=0.64922:GOSUB 50000
3601 doors$="1111":GOSUB 50100
3602 PRINT dash$:PRINT"You see:":PRINT
3603 IF nfa1305%<=0 THEN PRINT"* a note on the floor":GOTO 3610
3604 PRINT"* a note saying:":PEN 2
3605 PRINT" Almost all of the many rooms in"
3606 PRINT" this component are empty. But don't"
3607 PRINT" give up! There is important"
3608 PRINT" information to be found."
3609 PEN 1
3610 :
3611 GOSUB 50200
3612 IF ve%=7 AND ob%=9 THEN GOTO 4100
3613 IF ve%=7 AND ob%=10 THEN GOTO 3100
3614 IF ve%=7 AND ob%=11 THEN GOTO 3500
3615 IF ve%=7 AND ob%=12 THEN GOTO 3700
3616 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa1305%=1:GOTO 3600
3617 PRINT"Command not applicable.":GOSUB 52700:GOTO 3600
3700 comp%=13:room%=6:perc%=c13perc%:hc%=0:mult!=0.57482:GOSUB 50000
3701 doors$="1111":GOSUB 50100
3702 PRINT dash$:PRINT"You see:":PRINT
3703 GOSUB 50200
3704 IF ve%=7 AND ob%=9 THEN GOTO 4200
3705 IF ve%=7 AND ob%=10 THEN GOTO 3200
3706 IF ve%=7 AND ob%=11 THEN GOTO 3600
3707 IF ve%=7 AND ob%=12 THEN GOTO 3800
3708 PRINT"Command not applicable.":GOSUB 52700:GOTO 3700
3800 comp%=13:room%=7:perc%=c13perc%:hc%=0:mult!=0.70335:GOSUB 50000
3801 doors$="1111":GOSUB 50100
3802 PRINT dash$:PRINT"You see:":PRINT
3803 GOSUB 50200
3804 IF ve%=7 AND ob%=9 THEN GOTO 4300
3805 IF ve%=7 AND ob%=10 THEN GOTO 3300
3806 IF ve%=7 AND ob%=11 THEN GOTO 3700
3807 IF ve%=7 AND ob%=12 THEN GOTO 3900
3808 PRINT"Command not applicable.":GOSUB 52700:GOTO 3800
3900 comp%=13:room%=8:perc%=c13perc%:hc%=0:mult!=0.87542:GOSUB 50000
3901 doors$="1010":GOSUB 50100
3902 PRINT dash$:PRINT"You see:":PRINT
3903 GOSUB 50200
3904 IF ve%=7 AND ob%=9 THEN GOTO 4500
3905 IF ve%=7 AND ob%=11 THEN GOTO 3800
3906 PRINT"Command not applicable.":GOSUB 52700:GOTO 3900
4000 comp%=13:room%=9:perc%=c13perc%:hc%=0:mult!=0.7953:GOSUB 50000
4001 doors$="1101":GOSUB 50100
4002 PRINT dash$:PRINT"You see:":PRINT
4003 GOSUB 50200
4004 IF ve%=7 AND ob%=9 THEN GOTO 4700
4005 IF ve%=7 AND ob%=10 THEN GOTO 3400
4006 IF ve%=7 AND ob%=12 THEN GOTO 4100
4007 PRINT"Command not applicable.":GOSUB 52700:GOTO 4000
4100 comp%=13:room%=10:perc%=c13perc%:hc%=0:mult!=0.46802:GOSUB 50000
4101 doors$="1111":GOSUB 50100
4102 PRINT dash$:PRINT"You see:":PRINT
4103 GOSUB 50200
4104 IF ve%=7 AND ob%=9 THEN GOTO 4900
4105 IF ve%=7 AND ob%=10 THEN GOTO 3600
4106 IF ve%=7 AND ob%=11 THEN GOTO 4000
4107 IF ve%=7 AND ob%=12 THEN GOTO 4200
4108 PRINT"Command not applicable.":GOSUB 52700:GOTO 4100
4200 comp%=13:room%=11:perc%=c13perc%:hc%=0:mult!=0.42608:GOSUB 50000
4201 doors$="1111":GOSUB 50100
4202 PRINT dash$:PRINT"You see:":PRINT
4203 GOSUB 50200
4204 IF ve%=7 AND ob%=9 THEN GOTO 5000
4205 IF ve%=7 AND ob%=10 THEN GOTO 3700
4206 IF ve%=7 AND ob%=11 THEN GOTO 4100
4207 IF ve%=7 AND ob%=12 THEN GOTO 4300
4208 PRINT"Command not applicable.":GOSUB 52700:GOTO 4200
4300 comp%=13:room%=12:perc%=c13perc%:hc%=0:mult!=0.47387:GOSUB 50000
4301 doors$="1111":GOSUB 50100
4302 PRINT dash$:PRINT"You see:":PRINT
4303 GOSUB 50200
4304 IF ve%=7 AND ob%=9 THEN GOTO 6100
4305 IF ve%=7 AND ob%=10 THEN GOTO 3800
4306 IF ve%=7 AND ob%=11 THEN GOTO 4200
4307 IF ve%=7 AND ob%=12 THEN GOTO 4400
4308 PRINT"Command not applicable.":GOSUB 52700:GOTO 4300
4400 comp%=13:room%=13:perc%=c13perc%:hc%=0:mult!=0.63106:GOSUB 50000
4401 doors$="1011":GOSUB 50100
4402 PRINT dash$:PRINT"You see:":PRINT
4403 GOSUB 50200
4404 IF ve%=7 AND ob%=9 THEN GOTO 5700
4405 IF ve%=7 AND ob%=11 THEN GOTO 4300
4406 IF ve%=7 AND ob%=12 THEN GOTO 4500
4407 PRINT"Command not applicable.":GOSUB 52700:GOTO 4400
4500 comp%=13:room%=14:perc%=c13perc%:hc%=0:mult!=0.78835:GOSUB 50000
4501 doors$="1110":GOSUB 50100
4502 PRINT dash$:PRINT"You see:":PRINT
4503 GOSUB 50200
4504 IF ve%=7 AND ob%=9 THEN GOTO 5100
4505 IF ve%=7 AND ob%=10 THEN GOTO 3900
4506 IF ve%=7 AND ob%=11 THEN GOTO 4400
4507 PRINT"Command not applicable.":GOSUB 52700:GOTO 4500
4600 comp%=13:room%=15:perc%=c13perc%:hc%=0:mult!=0.87544:GOSUB 50000
4601 doors$="1001":GOSUB 50100
4602 PRINT dash$:PRINT"You see:":PRINT
4603 IF nfa1315%<=0 THEN PRINT"* a note on the floor":GOTO 4609
4604 PRINT"* a note saying:":PEN 2
4605 PRINT" This component does not have a"
4606 PRINT" parabolic door. You have to look"
4607 PRINT" for a different exit."
4608 PEN 1
4609 :
4610 GOSUB 50200
4611 IF ve%=7 AND ob%=9 THEN GOTO 5300
4612 IF ve%=7 AND ob%=12 THEN GOTO 4700
4613 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa1315%=1:GOTO 4600
4614 PRINT"Command not applicable.":GOSUB 52700:GOTO 4600
4700 comp%=13:room%=16:perc%=c13perc%:hc%=0:mult!=0.72858:GOSUB 50000
4701 doors$="1111":GOSUB 50100
4702 PRINT dash$:PRINT"You see:":PRINT
4703 GOSUB 50200
4704 IF ve%=7 AND ob%=9 THEN GOTO 5400
4705 IF ve%=7 AND ob%=10 THEN GOTO 4000
4706 IF ve%=7 AND ob%=11 THEN GOTO 4600
4707 IF ve%=7 AND ob%=12 THEN GOTO 4800
4708 PRINT"Command not applicable.":GOSUB 52700:GOTO 4700
4800 comp%=13:room%=17:perc%=c13perc%:hc%=0:mult!=0.42533:GOSUB 50000
4801 doors$="1111":GOSUB 50100
4802 PRINT dash$:PRINT"You see:":PRINT
4803 GOSUB 50200
4804 IF ve%=7 AND ob%=9 THEN GOTO 6600
4805 IF ve%=7 AND ob%=10 THEN GOTO 3500
4806 IF ve%=7 AND ob%=11 THEN GOTO 4700
4807 IF ve%=7 AND ob%=12 THEN GOTO 4900
4808 PRINT"Command not applicable.":GOSUB 52700:GOTO 4800
4900 comp%=13:room%=18:perc%=c13perc%:hc%=0:mult!=0.27865:GOSUB 50000
4901 doors$="1111":GOSUB 50100
4902 PRINT dash$:PRINT"You see:":PRINT
4903 GOSUB 50200
4904 IF ve%=7 AND ob%=9 THEN GOTO 5500
4905 IF ve%=7 AND ob%=10 THEN GOTO 4100
4906 IF ve%=7 AND ob%=11 THEN GOTO 4800
4907 IF ve%=7 AND ob%=12 THEN GOTO 5000
4908 PRINT"Command not applicable.":GOSUB 52700:GOTO 4900
5000 comp%=13:room%=19:perc%=c13perc%:hc%=0:mult!=0.22971:GOSUB 50000
5001 doors$="1111":GOSUB 50100
5002 PRINT dash$:PRINT"You see:":PRINT
5003 GOSUB 50200
5004 IF ve%=7 AND ob%=9 THEN GOTO 5600
5005 IF ve%=7 AND ob%=10 THEN GOTO 4200
5006 IF ve%=7 AND ob%=11 THEN GOTO 4900
5007 IF ve%=7 AND ob%=12 THEN GOTO 5100
5008 PRINT"Command not applicable.":GOSUB 52700:GOTO 5000
5100 comp%=13:room%=20:perc%=c13perc%:hc%=0:mult!=0.6406:GOSUB 50000
5101 doors$="1111":GOSUB 50100
5102 PRINT dash$:PRINT"You see:":PRINT
5103 GOSUB 50200
5104 IF ve%=7 AND ob%=9 THEN GOTO 6300
5105 IF ve%=7 AND ob%=10 THEN GOTO 4500
5106 IF ve%=7 AND ob%=11 THEN GOTO 5000
5107 IF ve%=7 AND ob%=12 THEN GOTO 5200
5108 PRINT"Command not applicable.":GOSUB 52700:GOTO 5100
5200 comp%=13:room%=21:perc%=c13perc%:hc%=0:mult!=0.8737:GOSUB 50000
5201 doors$="1010":GOSUB 50100
5202 PRINT dash$:PRINT"You see:":PRINT
5203 GOSUB 50200
5204 IF ve%=7 AND ob%=9 THEN GOTO 5800
5205 IF ve%=7 AND ob%=11 THEN GOTO 5100
5206 PRINT"Command not applicable.":GOSUB 52700:GOTO 5200
5300 comp%=13:room%=22:perc%=c13perc%:hc%=0:mult!=0.87592:GOSUB 50000
5301 doors$="0101":GOSUB 50100
5302 PRINT dash$:PRINT"You see:":PRINT
5303 GOSUB 50200
5304 IF ve%=7 AND ob%=10 THEN GOTO 4600
5305 IF ve%=7 AND ob%=12 THEN GOTO 5400
5306 PRINT"Command not applicable.":GOSUB 52700:GOTO 5300
5400 comp%=13:room%=23:perc%=c13perc%:hc%=0:mult!=0.62241:GOSUB 50000
5401 doors$="1111":GOSUB 50100
5402 PRINT dash$:PRINT"You see:":PRINT
5403 GOSUB 50200
5404 IF ve%=7 AND ob%=9 THEN GOTO 6500
5405 IF ve%=7 AND ob%=10 THEN GOTO 4700
5406 IF ve%=7 AND ob%=11 THEN GOTO 5300
5407 IF ve%=7 AND ob%=12 THEN GOTO 5500
5408 PRINT"Command not applicable.":GOSUB 52700:GOTO 5400
5500 comp%=13:room%=24:perc%=c13perc%:hc%=0:mult!=0.18078:GOSUB 50000
5501 doors$="1111":GOSUB 50100
5502 PRINT dash$:PRINT"You see:":PRINT
5503 GOSUB 50200
5504 IF ve%=7 AND ob%=9 THEN GOTO 6700
5505 IF ve%=7 AND ob%=10 THEN GOTO 4900
5506 IF ve%=7 AND ob%=11 THEN GOTO 5400
5507 IF ve%=7 AND ob%=12 THEN GOTO 5600
5508 PRINT"Command not applicable.":GOSUB 52700:GOTO 5500
5600 comp%=13:room%=25:perc%=c13perc%:hc%=0:mult!=0.07978:GOSUB 50000
5601 doors$="1111":GOSUB 50100
5602 PRINT dash$:PRINT"You see:":PRINT
5603 GOSUB 50200
5604 IF ve%=7 AND ob%=9 THEN GOTO 6000
5605 IF ve%=7 AND ob%=10 THEN GOTO 5000
5606 IF ve%=7 AND ob%=11 THEN GOTO 5500
5607 IF ve%=7 AND ob%=12 THEN GOTO 5700
5608 PRINT"Command not applicable.":GOSUB 52700:GOTO 5600
5700 comp%=13:room%=26:perc%=c13perc%:hc%=0:mult!=0.35555:GOSUB 50000
5701 doors$="1111":GOSUB 50100
5702 PRINT dash$:PRINT"You see:":PRINT
5703 GOSUB 50200
5704 IF ve%=7 AND ob%=9 THEN GOTO 6200
5705 IF ve%=7 AND ob%=10 THEN GOTO 4400
5706 IF ve%=7 AND ob%=11 THEN GOTO 5600
5707 IF ve%=7 AND ob%=12 THEN GOTO 5800
5708 PRINT"Command not applicable.":GOSUB 52700:GOTO 5700
5800 comp%=13:room%=27:perc%=c13perc%:hc%=0:mult!=0.8164:GOSUB 50000
5801 doors$="1110":GOSUB 50100
5802 PRINT dash$:PRINT"You see:":PRINT
5803 GOSUB 50200
5804 IF ve%=7 AND ob%=9 THEN GOTO 6400
5805 IF ve%=7 AND ob%=10 THEN GOTO 5200
5806 IF ve%=7 AND ob%=11 THEN GOTO 5700
5807 PRINT"Command not applicable.":GOSUB 52700:GOTO 5800
5900 comp%=13:room%=28:perc%=c13perc%:hc%=1:mult!=0.0061531:GOSUB 50000
5901 doors$="0001":GOSUB 50100
5902 PRINT dash$:PRINT"You see:":PRINT
5903 PRINT"* an active transmitter"
5904 GOSUB 50200
5905 IF ve%=7 AND ob%=12 THEN GOTO 6000
5906 IF ve%=5 AND ob%=5 THEN GOTO 8600
5907 PRINT"Command not applicable.":GOSUB 52700:GOTO 5900
6000 comp%=13:room%=29:perc%=c13perc%:hc%=0:mult!=0.026725:GOSUB 50000
6001 doors$="1111":GOSUB 50100
6002 PRINT dash$:PRINT"You see:":PRINT
6003 GOSUB 50200
6004 IF ve%=7 AND ob%=9 THEN GOTO 7300
6005 IF ve%=7 AND ob%=10 THEN GOTO 5600
6006 IF ve%=7 AND ob%=11 THEN GOTO 5900
6007 IF ve%=7 AND ob%=12 THEN GOTO 6100
6008 PRINT"Command not applicable.":GOSUB 52700:GOTO 6000
6100 comp%=13:room%=30:perc%=c13perc%:hc%=0:mult!=0.15555:GOSUB 50000
6101 doors$="1111":GOSUB 50100
6102 PRINT dash$:PRINT"You see:":PRINT
6103 GOSUB 50200
6104 IF ve%=7 AND ob%=9 THEN GOTO 6800
6105 IF ve%=7 AND ob%=10 THEN GOTO 4300
6106 IF ve%=7 AND ob%=11 THEN GOTO 6000
6107 IF ve%=7 AND ob%=12 THEN GOTO 6200
6108 PRINT"Command not applicable.":GOSUB 52700:GOTO 6100
6200 comp%=13:room%=31:perc%=c13perc%:hc%=0:mult!=0.33155:GOSUB 50000
6201 doors$="1111":GOSUB 50100
6202 PRINT dash$:PRINT"You see:":PRINT
6203 GOSUB 50200
6204 IF ve%=7 AND ob%=9 THEN GOTO 6900
6205 IF ve%=7 AND ob%=10 THEN GOTO 5700
6206 IF ve%=7 AND ob%=11 THEN GOTO 6100
6207 IF ve%=7 AND ob%=12 THEN GOTO 6300
6208 PRINT"Command not applicable.":GOSUB 52700:GOTO 6200
6300 comp%=13:room%=32:perc%=c13perc%:hc%=0:mult!=0.5356:GOSUB 50000
6301 doors$="1111":GOSUB 50100
6302 PRINT dash$:PRINT"You see:":PRINT
6303 GOSUB 50200
6304 IF ve%=7 AND ob%=9 THEN GOTO 7000
6305 IF ve%=7 AND ob%=10 THEN GOTO 5100
6306 IF ve%=7 AND ob%=11 THEN GOTO 6200
6307 IF ve%=7 AND ob%=12 THEN GOTO 6400
6308 PRINT"Command not applicable.":GOSUB 52700:GOTO 6300
6400 comp%=13:room%=33:perc%=c13perc%:hc%=0:mult!=0.803:GOSUB 50000
6401 doors$="1110":GOSUB 50100
6402 PRINT dash$:PRINT"You see:":PRINT
6403 GOSUB 50200
6404 IF ve%=7 AND ob%=9 THEN GOTO 7100
6405 IF ve%=7 AND ob%=10 THEN GOTO 5800
6406 IF ve%=7 AND ob%=11 THEN GOTO 6300
6407 PRINT"Command not applicable.":GOSUB 52700:GOTO 6400
6500 comp%=13:room%=34:perc%=c13perc%:hc%=0:mult!=0.76084:GOSUB 50000
6501 doors$="0101":GOSUB 50100
6502 PRINT dash$:PRINT"You see:":PRINT
6503 GOSUB 50200
6504 IF ve%=7 AND ob%=10 THEN GOTO 5400
6505 IF ve%=7 AND ob%=12 THEN GOTO 6600
6506 PRINT"Command not applicable.":GOSUB 52700:GOTO 6500
6600 comp%=13:room%=35:perc%=c13perc%:hc%=0:mult!=0.56796:GOSUB 50000
6601 doors$="0111":GOSUB 50100
6602 PRINT dash$:PRINT"You see:":PRINT
6603 GOSUB 50200
6604 IF ve%=7 AND ob%=10 THEN GOTO 4800
6605 IF ve%=7 AND ob%=11 THEN GOTO 6500
6606 IF ve%=7 AND ob%=12 THEN GOTO 6700
6607 PRINT"Command not applicable.":GOSUB 52700:GOTO 6600
6700 comp%=13:room%=36:perc%=c13perc%:hc%=0:mult!=0.26048:GOSUB 50000
6701 doors$="1111":GOSUB 50100
6702 PRINT dash$:PRINT"You see:":PRINT
6703 GOSUB 50200
6704 IF ve%=7 AND ob%=9 THEN GOTO 7200
6705 IF ve%=7 AND ob%=10 THEN GOTO 5500
6706 IF ve%=7 AND ob%=11 THEN GOTO 6600
6707 IF ve%=7 AND ob%=12 THEN GOTO 6800
6708 PRINT"Command not applicable.":GOSUB 52700:GOTO 6700
6800 comp%=13:room%=37:perc%=c13perc%:hc%=0:mult!=0.19102:GOSUB 50000
6801 doors$="0111":GOSUB 50100
6802 PRINT dash$:PRINT"You see:":PRINT
6803 GOSUB 50200
6804 IF ve%=7 AND ob%=10 THEN GOTO 6100
6805 IF ve%=7 AND ob%=11 THEN GOTO 6700
6806 IF ve%=7 AND ob%=12 THEN GOTO 6900
6807 PRINT"Command not applicable.":GOSUB 52700:GOTO 6800
6900 comp%=13:room%=38:perc%=c13perc%:hc%=0:mult!=0.37496:GOSUB 50000
6901 doors$="1111":GOSUB 50100
6902 PRINT dash$:PRINT"You see:":PRINT
6903 IF ncl1338%>0 THEN PRINT"* a locked case":GOTO 6909
6904 PRINT"* a case with a note saying:":PEN 2
6905 PRINT" The rightmost digit of the"
6906 PRINT" periodicity is half the leftmost"
6907 PRINT" one."
6908 PEN 1
6909 :
6910 GOSUB 50200
6911 IF ve%=7 AND ob%=9 THEN GOTO 7400
6912 IF ve%=7 AND ob%=10 THEN GOTO 6200
6913 IF ve%=7 AND ob%=11 THEN GOTO 6800
6914 IF ve%=7 AND ob%=12 THEN GOTO 7000
6915 IF ncl1338%>0 AND ve%=3 AND ob%=2 THEN GOTO 6917
6916 PRINT"Command not applicable.":GOSUB 52700:GOTO 6900
6917 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
6918 PEN 2
6919 PRINT" Let f_d(z)=1/(z^17+d). The points z=0"
6920 PRINT" and z=inf have a particular property"
6921 PRINT" for f_0, which is ..."
6922 PEN 1:PRINT
6923 PRINT"  (0) the only two exceptional poins"
6924 PRINT"  (1) two of infinitely many exceptional points"
6925 PRINT"  (2) lie both in the Julia set J_f"
6926 PRINT"  (3) are both poles of f_0(z)"
6927 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 0":PRINT
6928 INPUT"Your answer > ",nicans%
6929 IF nicans%=0 THEN ncl1338%=0 ELSE PRINT"Incorrect.":GOSUB 52700
6930 GOTO 6900
7000 comp%=13:room%=39:perc%=c13perc%:hc%=0:mult!=0.62467:GOSUB 50000
7001 doors$="1111":GOSUB 50100
7002 PRINT dash$:PRINT"You see:":PRINT
7003 GOSUB 50200
7004 IF ve%=7 AND ob%=9 THEN GOTO 7500
7005 IF ve%=7 AND ob%=10 THEN GOTO 6300
7006 IF ve%=7 AND ob%=11 THEN GOTO 6900
7007 IF ve%=7 AND ob%=12 THEN GOTO 7100
7008 PRINT"Command not applicable.":GOSUB 52700:GOTO 7000
7100 comp%=13:room%=40:perc%=c13perc%:hc%=0:mult!=0.81078:GOSUB 50000
7101 doors$="0110":GOSUB 50100
7102 PRINT dash$:PRINT"You see:":PRINT
7103 GOSUB 50200
7104 IF ve%=7 AND ob%=10 THEN GOTO 6400
7105 IF ve%=7 AND ob%=11 THEN GOTO 7000
7106 PRINT"Command not applicable.":GOSUB 52700:GOTO 7100
7200 comp%=13:room%=41:perc%=c13perc%:hc%=0:mult!=0.62109:GOSUB 50000
7201 doors$="0101":GOSUB 50100
7202 PRINT dash$:PRINT"You see:":PRINT
7203 GOSUB 50200
7204 IF ve%=7 AND ob%=10 THEN GOTO 6700
7205 IF ve%=7 AND ob%=12 THEN GOTO 7300
7206 PRINT"Command not applicable.":GOSUB 52700:GOTO 7200
7300 comp%=13:room%=42:perc%=c13perc%:hc%=0:mult!=0.28365:GOSUB 50000
7301 doors$="0111":GOSUB 50100
7302 PRINT dash$:PRINT"You see:":PRINT
7303 GOSUB 50200
7304 IF ve%=7 AND ob%=10 THEN GOTO 6000
7305 IF ve%=7 AND ob%=11 THEN GOTO 7200
7306 IF ve%=7 AND ob%=12 THEN GOTO 7400
7307 PRINT"Command not applicable.":GOSUB 52700:GOTO 7300
7400 comp%=13:room%=43:perc%=c13perc%:hc%=0:mult!=0.53592:GOSUB 50000
7401 doors$="0111":GOSUB 50100
7402 PRINT dash$:PRINT"You see:":PRINT
7403 GOSUB 50200
7404 IF ve%=7 AND ob%=10 THEN GOTO 6900
7405 IF ve%=7 AND ob%=11 THEN GOTO 7300
7406 IF ve%=7 AND ob%=12 THEN GOTO 7500
7407 PRINT"Command not applicable.":GOSUB 52700:GOTO 7400
7500 comp%=13:room%=44:perc%=c13perc%:hc%=0:mult!=0.7124:GOSUB 50000
7501 doors$="0110":GOSUB 50100
7502 PRINT dash$:PRINT"You see:":PRINT
7503 IF nfa1344%<=0 THEN PRINT"* a note on the floor":GOTO 7508
7504 PRINT"* a note saying:":PEN 2
7505 PRINT" The multiplier detector might be of"
7506 PRINT" help here to find an exit."
7507 PEN 1
7508 :
7509 GOSUB 50200
7510 IF ve%=7 AND ob%=10 THEN GOTO 7000
7511 IF ve%=7 AND ob%=11 THEN GOTO 7400
7512 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa1344%=1:GOTO 7500
7513 PRINT"Command not applicable.":GOSUB 52700:GOTO 7500
7600 comp%=14:room%=0:perc%=c14perc%:hc%=0:mult!=0.41368:GOSUB 50000
7601 doors$="1001":GOSUB 50100
7602 PRINT dash$:PRINT"You see:":PRINT
7603 IF dcl1400%>0 THEN PRINT"* a locked case":GOTO 7607
7604 IF dcl1400%<=0 AND dcp1400%<=0 THEN PRINT"* an open and empty case":GOTO 7607
7605 PRINT"* the case contains:"
7606 PRINT" an electronic device labelled '1'"
7607 :
7608 GOSUB 50200
7609 IF ve%=7 AND ob%=9 THEN GOTO 8100
7610 IF ve%=7 AND ob%=12 THEN GOTO 7700
7611 IF dcl1400%>0 AND ve%=3 AND ob%=2 THEN GOTO 7614
7612 IF dcl1400%<=0 AND dcp1400%>0 AND ve%=6 AND ob%=4 THEN IF parts%(1)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 7600 ELSE parts%(1)=1:heromdet%=heromdet%+1:dcp1400%=0:GOTO 7600
7613 PRINT"Command not applicable.":GOSUB 52700:GOTO 7600
7614 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
7615 PEN 2
7616 PRINT" Let N(d) denote the number of"
7617 PRINT" iterations the point z0=0 needs under"
7618 PRINT" z_(n+1)=(z_n)^2+c for c=0.25+d and"
7619 PRINT" positive d until ||z_n|| exceeds 2."
7620 PRINT" Does lim (d->0) sqrt(d)*N(d) exist,"
7621 PRINT" and if so, what does it value to?"
7622 PEN 1:PRINT
7623 PRINT"  (0) no limit exists"
7624 PRINT"  (1) the area of the Mandelbrot set"
7625 PRINT"  (2) pi"
7626 PRINT"  (3) Euler's constant divided by pi"
7627 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 2":PRINT
7628 INPUT"Your answer > ",dicans%
7629 IF dicans%=2 THEN dcl1400%=0 ELSE PRINT"Incorrect.":GOSUB 52700
7630 GOTO 7600
7700 comp%=14:room%=1:perc%=c14perc%:hc%=0:mult!=0.23609:GOSUB 50000
7701 doors$="1010":GOSUB 50100
7702 PRINT dash$:PRINT"You see:":PRINT
7703 IF dcl1401%>0 THEN PRINT"* a locked case":GOTO 7707
7704 IF dcl1401%<=0 AND dcp1401%<=0 THEN PRINT"* an open and empty case":GOTO 7707
7705 PRINT"* the case contains:"
7706 PRINT" an electronic device labelled '2'"
7707 :
7708 GOSUB 50200
7709 IF ve%=7 AND ob%=9 THEN GOTO 8000
7710 IF ve%=7 AND ob%=11 THEN GOTO 7600
7711 IF dcl1401%>0 AND ve%=3 AND ob%=2 THEN GOTO 7714
7712 IF dcl1401%<=0 AND dcp1401%>0 AND ve%=6 AND ob%=4 THEN IF parts%(2)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 7700 ELSE parts%(2)=1:heromdet%=heromdet%+1:dcp1401%=0:GOTO 7700
7713 PRINT"Command not applicable.":GOSUB 52700:GOTO 7700
7714 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
7715 PEN 2
7716 PRINT" What, besides the famous set, has"
7717 PRINT" been named after Benoit Mandelbrot?"
7718 PEN 1:PRINT
7719 PRINT"  (0) Subway station"
7720 PRINT"  (1) Asteroid"
7721 PRINT"  (2) Beetle specias"
7722 PRINT"  (3) Computer chip layout"
7723 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 1":PRINT
7724 INPUT"Your answer > ",dicans%
7725 IF dicans%=1 THEN dcl1401%=0 ELSE PRINT"Incorrect.":GOSUB 52700
7726 GOTO 7700
7800 comp%=14:room%=2:perc%=c14perc%:hc%=1:mult!=0.0058013:GOSUB 50000
7801 doors$="1000":GOSUB 50100
7802 PRINT dash$:PRINT"You see:":PRINT
7803 IF nfa1402%<=0 THEN PRINT"* a note on the floor":GOTO 7812
7804 PRINT"* a note saying:":PEN 2
7805 PRINT" Let P (<100) be the periodicity of"
7806 PRINT" the current component. Then there"
7807 PRINT" are a total of"
7808 PRINT" 9671406556914834240182310"
7809 PRINT" hyperbolic components with exactly"
7810 PRINT" that period in z^2+c."
7811 PEN 1
7812 :
7813 GOSUB 50200
7814 IF ve%=7 AND ob%=9 THEN GOTO 7900
7815 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa1402%=1:GOTO 7800
7816 PRINT"Command not applicable.":GOSUB 52700:GOTO 7800
7900 comp%=14:room%=3:perc%=c14perc%:hc%=0:mult!=0.015047:GOSUB 50000
7901 doors$="0101":GOSUB 50100
7902 PRINT dash$:PRINT"You see:":PRINT
7903 IF nfa1403%<=0 THEN PRINT"* a note on the floor":GOTO 7909
7904 PRINT"* a note saying:":PEN 2
7905 PRINT" Let P be the periodicity of the"
7906 PRINT" current component. Then P-13 is"
7907 PRINT" part of a twin prime."
7908 PEN 1
7909 :
7910 GOSUB 50200
7911 IF ve%=7 AND ob%=10 THEN GOTO 7800
7912 IF ve%=7 AND ob%=12 THEN GOTO 8000
7913 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa1403%=1:GOTO 7900
7914 PRINT"Command not applicable.":GOSUB 52700:GOTO 7900
8000 comp%=14:room%=4:perc%=c14perc%:hc%=0:mult!=0.093796:GOSUB 50000
8001 doors$="0110":GOSUB 50100
8002 PRINT dash$:PRINT"You see:":PRINT
8003 IF dcl1404%>0 THEN PRINT"* a locked case":GOTO 8007
8004 IF dcl1404%<=0 AND dcp1404%<=0 THEN PRINT"* an open and empty case":GOTO 8007
8005 PRINT"* the case contains:"
8006 PRINT" an electronic device labelled '3'"
8007 :
8008 GOSUB 50200
8009 IF ve%=7 AND ob%=10 THEN GOTO 7700
8010 IF ve%=7 AND ob%=11 THEN GOTO 7900
8011 IF dcl1404%>0 AND ve%=3 AND ob%=2 THEN GOTO 8014
8012 IF dcl1404%<=0 AND dcp1404%>0 AND ve%=6 AND ob%=4 THEN IF parts%(3)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 8000 ELSE parts%(3)=1:heromdet%=heromdet%+1:dcp1404%=0:GOTO 8000
8013 PRINT"Command not applicable.":GOSUB 52700:GOTO 8000
8014 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
8015 PRINT:PEN 2
8016 PRINT" How many Misiureqicz points of exact"
8017 PRINT" preperiod 2 and exact period 3 does"
8018 PRINT" z^2+c harbour? (Fewer than 11)"
8019 PEN 1:PRINT
8020 IF hex%>0 THEN PRINT"The magic oracle tells: 6":PRINT
8021 INPUT"Your answer > ",dicans$
8022 IF dicans$="6" THEN dcl1404%=0 ELSE PRINT"Incorrect.":GOSUB 52700
8023 GOTO 8000
8100 comp%=14:room%=5:perc%=c14perc%:hc%=0:mult!=0.6287:GOSUB 50000
8101 doors$="0101":GOSUB 50100
8102 PRINT dash$:PRINT"You see:":PRINT
8103 GOSUB 50200
8104 IF ve%=7 AND ob%=10 THEN GOTO 7600
8105 IF ve%=7 AND ob%=12 THEN GOTO 8200
8106 PRINT"Command not applicable.":GOSUB 52700:GOTO 8100
8200 comp%=14:room%=6:perc%=c14perc%:hc%=0:mult!=0.84113:GOSUB 50000
8201 doors$="0012":GOSUB 50100
8202 PRINT dash$:PRINT"You see:":PRINT
8203 GOSUB 50200
8204 IF ve%=7 AND ob%=11 THEN GOTO 8100
8205 IF ve%=7 AND ob%=12 THEN pinc%=84:GOSUB 52800:IF pinout%>0 THEN c14perc%=84:GOTO 2200 ELSE GOTO 8200
8206 PRINT"Command not applicable.":GOSUB 52700:GOTO 8200
8300 comp%=15:room%=0:perc%=c15perc%:hc%=0:mult!=0.88362:GOSUB 50000
8301 doors$="0021":GOSUB 50100
8302 PRINT dash$:PRINT"You see:":PRINT
8303 GOSUB 50200
8304 IF ve%=7 AND ob%=11 THEN pinc%=63:GOSUB 52800:IF pinout%>0 THEN c15perc%=63:GOTO 1600 ELSE GOTO 8300
8305 IF ve%=7 AND ob%=12 THEN GOTO 8400
8306 PRINT"Command not applicable.":GOSUB 52700:GOTO 8300
8400 comp%=15:room%=1:perc%=c15perc%:hc%=0:mult!=0.49573:GOSUB 50000
8401 doors$="0011":GOSUB 50100
8402 PRINT dash$:PRINT"You see:":PRINT
8403 GOSUB 50200
8404 IF ve%=7 AND ob%=11 THEN GOTO 8300
8405 IF ve%=7 AND ob%=12 THEN GOTO 8500
8406 PRINT"Command not applicable.":GOSUB 52700:GOTO 8400
8500 comp%=15:room%=2:perc%=c15perc%:hc%=0:mult!=0.41959:GOSUB 50000
8501 doors$="1010":GOSUB 50100
8502 PRINT dash$:PRINT"You see:":PRINT
8503 GOSUB 50200
8504 IF ve%=7 AND ob%=9 THEN GOTO 8600
8505 IF ve%=7 AND ob%=11 THEN GOTO 8400
8506 PRINT"Command not applicable.":GOSUB 52700:GOTO 8500
8600 comp%=15:room%=3:perc%=c15perc%:hc%=1:mult!=0.0085872:GOSUB 50000
8601 doors$="0100":GOSUB 50100
8602 PRINT dash$:PRINT"You see:":PRINT
8603 PRINT"* an active transmitter"
8604 IF nfa1503%<=0 THEN PRINT"* a note on the floor":GOTO 8616
8605 PRINT"* a note saying:":PEN 2
8606 PRINT" The current component's period"
8607 PRINT" consists of two digits. The 2nd is"
8608 PRINT" the period of the attracting cycle"
8609 PRINT" for z^2-1.765625. The 1st is the"
8610 PRINT" number of iterations the point"
8611 PRINT" z0=1.919531256020779220571441553319"
8612 PRINT" 10811798336541288694335038397109589"
8613 PRINT" 140005053853 needs to land in an"
8614 PRINT" immediate basin of the cycle."
8615 PEN 1
8616 :
8617 GOSUB 50200
8618 IF ve%=7 AND ob%=10 THEN GOTO 8500
8619 IF ve%=5 AND ob%=5 THEN GOTO 2700
8620 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa1503%=1:GOTO 8600
8621 PRINT"Command not applicable.":GOSUB 52700:GOTO 8600
8722 MODE 1:CLS
8723 direction$="NSWE":DIM param$(4):INK 2,26
8724 heromdet%=0:DIM parts%(3):parts%(1)=0:parts%(2)=0:parts%(3)=0:hex%=0:dash$="---------------------------------------"
8725 c04perc%=0:nfa0400%=0:c10perc%=0:ncl1001%=1:nba1004%=0:nbh1004%=1:c11perc%=0:nba1103%=0:nbh1103%=1:ncl1104%=1:c12perc%=0:ncl1201%=1:nfa1203%=0:c13perc%=0:ncl1303%=1
8726 ncl1304%=1:nfa1305%=0:nfa1315%=0:ncl1338%=1:nfa1344%=0:c14perc%=0:dcl1400%=1:dcp1400%=1:dcl1401%=1:dcp1401%=2:nfa1402%=0:nfa1403%=0:dcl1404%=1:dcp1404%=3:c15perc%=0
8727 nfa1503%=0
8728 GOTO 8100
50000 CLS:LOCATE 1,1:PRINT dash$:PRINT"room ";room%;" component ";comp%;
50001 IF perc%>0 THEN PRINT"period ";perc%;
50002 IF hc%>0 THEN PRINT"hyperbolic center" ELSE PRINT
50003 IF heromdet%>=3 THEN PRINT"multiplier=";mult!
50004 PRINT dash$:IF heromdet%>0 AND heromdet%<3 THEN PRINT"multiplier detector ";heromdet%;"/3rd built."
50005 RETURN
50100 PRINT:PRINT"Doors:  ";:FOR printdoors%=1 TO 4:printdoorstmp%=ASC(MID$(doors$,printdoors%,1))-48
50101 IF printdoorstmp%=1 THEN PRINT MID$(direction$,printdoors%,1);" "; ELSE IF printdoorstmp%=2 THEN PRINT MID$(direction$,printdoors%,1);" parabolic locked  ";
50102 NEXT:PRINT:RETURN
50200 PRINT dash$:INPUT"Taylor> ",paramin$:GOSUB 51200
50201 IF paranz%=1 AND LEN(param$(1))=1 THEN paranz%=2:param$(2)=param$(1):param$(1)="GO"
50202 ve%=0:pp%=0:ob%=0
50203 FOR parse%=1 TO paranz%:IF LEN(param$(parse%))>4 THEN param$(parse%)=LEFT$(param$(parse%),4)
50204 datin$=param$(parse%):RESTORE 52400:GOSUB 51400:IF datout%>0 THEN ve%=datout%
50205 datin$=param$(parse%):RESTORE 52500:GOSUB 51400:IF datout%>0 THEN pp%=datout%
50206 datin$=param$(parse%):RESTORE 52600:GOSUB 51400:IF datout%>0 THEN ob%=datout%
50207 NEXT
50208 IF ve%=8 THEN PRINT"program aborted.":END
50209 IF ve%=9 THEN hex%=1:RETURN
50210 RETURN
51200 IF LEN(paramin$)>200 THEN paramin$=LEFT$(paramin$,200)
51201 paramin$=UPPER$(paramin$)+" ":paranz%=0:parstatus%=1
51202 FOR pari%=1 TO LEN(paramin$):IF paranz%>=3 THEN parstatus%=3
51203 IF parstatus%<0 THEN parstatus%=-parstatus%
51204 parasc%=ASC(MID$(paramin$,pari%,1))
51205 IF parstatus%=1 THEN IF parasc%>64 AND parasc%<91 THEN par0%=pari%:parstatus%=-2
51206 IF parstatus%=2 THEN IF parasc%<65 OR parasc>90 THEN paranz%=paranz%+1:param$(paranz%)=MID$(paramin$,par0%,pari%-par0%):parstatus%=-1
51207 NEXT:RETURN
51400 datout%=-1:READ getvpo$,getno%:IF getvpo$=datin$ THEN datout%=getno%:RETURN
51401 IF getno%<0 THEN RETURN
51402 GOTO 51400
52400 DATA READ,1,LOOK,2,WATC,2,INVE,2,OPEN,3
52401 DATA FREE,4,RESC,4,SAVE,4,USE,5,TAKE,6
52402 DATA "GRAB",6,"GO",7,"WALK",7,"TRAV",7,"END",8
52403 DATA "EXIT",8,"QUIT",8,ABRA,9,"/",-1
52500 DATA "AT",1,BEHI,2,UNDE,3,"/",-1
52600 DATA NOTE,1,CASE,2,BOX,2,CELL,3,BENO,6
52601 DATA MAND,6,PART,4,DEVI,4,TRAN,5,CARP,7
52602 DATA RUG,7,MIRR,8,NORT,9,N,9
52603 DATA SOUT,10,S,10,WEST,11,W,11
52604 DATA EAST,12,E,12,"/",-1
52700 FOR waitloop%=1 TO 2100:NEXT:RETURN
52800 IF hex%>0 THEN PRINT:PRINT"The magic oracle tells: ";pinc%:PRINT
52801 INPUT"Enter PIN: ",pintmp%:IF pintmp%=pinc% THEN pinout%=1 ELSE pinout%=0:PRINT"Incorrect pin.":GOSUB 52700
52802 RETURN
