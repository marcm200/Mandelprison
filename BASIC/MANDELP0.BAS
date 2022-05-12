1 GOTO 4214
10 REM Mandelprison - Free Benoit!
11 REM text adventure in style of Thor - Trilogy for Schneider CPC464 from the 80s
12 REM Marc Meidlinger May 2022
1000 comp%=0:room%=0:perc%=c00perc%:hc%=0:mult!=0.075618:GOSUB 50000
1001 doors$="1000":GOSUB 50100
1002 PRINT dash$:PRINT"You see:":PRINT
1003 IF dcl0000%>0 THEN PRINT"* a locked case":GOTO 1007
1004 IF dcl0000%<=0 AND dcp0000%<=0 THEN PRINT"* an open and empty case":GOTO 1007
1005 PRINT"* the case contains:"
1006 PRINT" an electronic device labelled '3'"
1007 :
1008 GOSUB 50200
1009 IF ve%=7 AND ob%=9 THEN GOTO 1200
1010 IF dcl0000%>0 AND ve%=3 AND ob%=2 THEN GOTO 1013
1011 IF dcl0000%<=0 AND dcp0000%>0 AND ve%=6 AND ob%=4 THEN IF parts%(3)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 1000 ELSE parts%(3)=1:heromdet%=heromdet%+1:dcp0000%=0:GOTO 1000
1012 PRINT"Command not applicable.":GOSUB 52700:GOTO 1000
1013 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
1014 PEN 2
1015 PRINT" Who proved the no-wandering theorem"
1016 PRINT" for rational functions?"
1017 PEN 1:PRINT
1018 PRINT"  (0) Pierre Fatou"
1019 PRINT"  (1) Leonhard Euler"
1020 PRINT"  (2) Dennis Sullivan"
1021 PRINT"  (3) Gaston Julia"
1022 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 2":PRINT
1023 INPUT"Your answer > ",dicans%
1024 IF dicans%=2 THEN dcl0000%=0 ELSE PRINT"Incorrect.":GOSUB 52700
1025 GOTO 1000
1100 comp%=0:room%=1:perc%=c00perc%:hc%=0:mult!=0.93756:GOSUB 50000
1101 doors$="0021":GOSUB 50100
1102 PRINT dash$:PRINT"You see:":PRINT
1103 GOSUB 50200
1104 IF ve%=7 AND ob%=11 THEN pinc%=8:GOSUB 52800:IF pinout%>0 THEN c00perc%=8:GOTO 1700 ELSE GOTO 1100
1105 IF ve%=7 AND ob%=12 THEN GOTO 1200
1106 PRINT"Command not applicable.":GOSUB 52700:GOTO 1100
1200 comp%=0:room%=2:perc%=c00perc%:hc%=0:mult!=0.031585:GOSUB 50000
1201 doors$="0111":GOSUB 50100
1202 PRINT dash$:PRINT"You see:":PRINT
1203 IF dcl0002%>0 THEN PRINT"* a locked case":GOTO 1207
1204 IF dcl0002%<=0 AND dcp0002%<=0 THEN PRINT"* an open and empty case":GOTO 1207
1205 PRINT"* the case contains:"
1206 PRINT" an electronic device labelled '1'"
1207 :
1208 GOSUB 50200
1209 IF ve%=7 AND ob%=10 THEN GOTO 1000
1210 IF ve%=7 AND ob%=11 THEN GOTO 1100
1211 IF ve%=7 AND ob%=12 THEN GOTO 1300
1212 IF dcl0002%<=0 AND dcp0002%>0 AND ve%=6 AND ob%=4 THEN IF parts%(1)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 1200 ELSE parts%(1)=1:heromdet%=heromdet%+1:dcp0002%=0:GOTO 1200
1214 PRINT"Command not applicable.":GOSUB 52700:GOTO 1200
1300 comp%=0:room%=3:perc%=c00perc%:hc%=1:mult!=0.017378:GOSUB 50000
1301 doors$="1011":GOSUB 50100
1302 PRINT dash$:PRINT"You see:":PRINT
1303 PRINT"* an inactive transmitter"
1304 IF dcl0003%>0 THEN PRINT"* a locked case":GOTO 1308
1305 IF dcl0003%<=0 AND dcp0003%<=0 THEN PRINT"* an open and empty case":GOTO 1308
1306 PRINT"* the case contains:"
1307 PRINT" an electronic device labelled '2'"
1308 :
1309 GOSUB 50200
1310 IF ve%=7 AND ob%=9 THEN GOTO 1500
1311 IF ve%=7 AND ob%=11 THEN GOTO 1200
1312 IF ve%=7 AND ob%=12 THEN GOTO 1400
1313 IF dcl0003%>0 AND ve%=3 AND ob%=2 THEN GOTO 1316
1314 IF dcl0003%<=0 AND dcp0003%>0 AND ve%=6 AND ob%=4 THEN IF parts%(2)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 1300 ELSE parts%(2)=1:heromdet%=heromdet%+1:dcp0003%=0:GOTO 1300
1315 PRINT"Command not applicable.":GOSUB 52700:GOTO 1300
1316 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
1317 PRINT:PEN 2
1318 PRINT" How many distinct attracting cycles"
1319 PRINT" does the Julia set to"
1320 PRINT" z^3+(-1.1057+i*0.6074)*z^2+(0.7111-1."
1321 PRINT" 1915*i) own?"
1322 PEN 1:PRINT
1323 IF hex%>0 THEN PRINT"The magic oracle tells: 1":PRINT
1324 INPUT"Your answer > ",dicans$
1325 IF dicans$="1" THEN dcl0003%=0 ELSE PRINT"Incorrect.":GOSUB 52700
1326 GOTO 1300
1400 comp%=0:room%=4:perc%=c00perc%:hc%=0:mult!=0.93324:GOSUB 50000
1401 doors$="0012":GOSUB 50100
1402 PRINT dash$:PRINT"You see:":PRINT
1403 GOSUB 50200
1404 IF ve%=7 AND ob%=11 THEN GOTO 1300
1405 IF ve%=7 AND ob%=12 THEN pinc%=8:GOSUB 52800:IF pinout%>0 THEN c00perc%=8:GOTO 2000 ELSE GOTO 1400
1406 PRINT"Command not applicable.":GOSUB 52700:GOTO 1400
1500 comp%=0:room%=5:perc%=c00perc%:hc%=0:mult!=0.051434:GOSUB 50000
1501 doors$="0100":GOSUB 50100
1502 PRINT dash$:PRINT"You see:":PRINT
1503 IF nfa0005%<=0 THEN PRINT"* a note on the floor":GOTO 1510
1504 PRINT"* a note saying:":PEN 2
1505 PRINT" Current component's periodicity"
1506 PRINT" equals half the sum of the four"
1507 PRINT" digits of Benoit Mandelbrot's year"
1508 PRINT" of birth."
1509 PEN 1
1510 :
1511 GOSUB 50200
1512 IF ve%=7 AND ob%=10 THEN GOTO 1300
1513 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0005%=1:GOTO 1500
1514 PRINT"Command not applicable.":GOSUB 52700:GOTO 1500
1600 comp%=1:room%=0:perc%=c01perc%:hc%=1:mult!=0.0012861:GOSUB 50000
1601 doors$="0001":GOSUB 50100
1602 PRINT dash$:PRINT"You see:":PRINT
1603 PRINT"* an active transmitter"
1604 GOSUB 50200
1605 IF ve%=7 AND ob%=12 THEN GOTO 1700
1606 IF ve%=5 AND ob%=5 THEN GOTO 4100
1607 PRINT"Command not applicable.":GOSUB 52700:GOTO 1600
1700 comp%=1:room%=1:perc%=c01perc%:hc%=0:mult!=0.84518:GOSUB 50000
1701 doors$="0012":GOSUB 50100
1702 PRINT dash$:PRINT"You see:":PRINT
1703 IF nbh0101%>0 THEN PRINT"* a mirror hinging on one corner":GOTO 1708
1704 IF nbh0101%<=0 AND nba0101%<=0 THEN PRINT"* a note behind the mirror":GOTO 1708
1705 PRINT"* a note behind the mirror saying:":PEN 2
1706 PRINT" Current period is 16."
1707 PEN 1
1708 :
1709 GOSUB 50200
1710 IF ve%=7 AND ob%=11 THEN GOTO 1600
1711 IF ve%=7 AND ob%=12 THEN pinc%=16:GOSUB 52800:IF pinout%>0 THEN c01perc%=16:GOTO 1100 ELSE GOTO 1700
1712 IF nbh0101%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba0101%=1:GOTO 1700
1713 IF nbh0101%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh0101%=0:GOTO 1700
1714 PRINT"Command not applicable.":GOSUB 52700:GOTO 1700
1800 comp%=2:room%=0:perc%=c02perc%:hc%=0:mult!=0.014442:GOSUB 50000
1801 doors$="1001":GOSUB 50100
1802 PRINT dash$:PRINT"You see:":PRINT
1803 GOSUB 50200
1804 IF ve%=7 AND ob%=9 THEN GOTO 2100
1805 IF ve%=7 AND ob%=12 THEN GOTO 1900
1806 PRINT"Command not applicable.":GOSUB 52700:GOTO 1800
1900 comp%=2:room%=1:perc%=c02perc%:hc%=0:mult!=0.010016:GOSUB 50000
1901 doors$="1010":GOSUB 50100
1902 PRINT dash$:PRINT"You see:":PRINT
1903 GOSUB 50200
1904 IF ve%=7 AND ob%=9 THEN GOTO 2200
1905 IF ve%=7 AND ob%=11 THEN GOTO 1800
1906 PRINT"Command not applicable.":GOSUB 52700:GOTO 1900
2000 comp%=2:room%=2:perc%=c02perc%:hc%=0:mult!=0.93135:GOSUB 50000
2001 doors$="0021":GOSUB 50100
2002 PRINT dash$:PRINT"You see:":PRINT
2003 GOSUB 50200
2004 IF ve%=7 AND ob%=11 THEN pinc%=4:GOSUB 52800:IF pinout%>0 THEN c02perc%=4:GOTO 1400 ELSE GOTO 2000
2005 IF ve%=7 AND ob%=12 THEN GOTO 2100
2006 PRINT"Command not applicable.":GOSUB 52700:GOTO 2000
2100 comp%=2:room%=3:perc%=c02perc%:hc%=0:mult!=0.0083762:GOSUB 50000
2101 doors$="1111":GOSUB 50100
2102 PRINT dash$:PRINT"You see:":PRINT
2103 GOSUB 50200
2104 IF ve%=7 AND ob%=9 THEN GOTO 2500
2105 IF ve%=7 AND ob%=10 THEN GOTO 1800
2106 IF ve%=7 AND ob%=11 THEN GOTO 2000
2107 IF ve%=7 AND ob%=12 THEN GOTO 2200
2108 PRINT"Command not applicable.":GOSUB 52700:GOTO 2100
2200 comp%=2:room%=4:perc%=c02perc%:hc%=1:mult!=0.01547:GOSUB 50000
2201 doors$="1111":GOSUB 50100
2202 PRINT dash$:PRINT"You see:":PRINT
2203 PRINT"* an inactive transmitter"
2204 GOSUB 50200
2205 IF ve%=7 AND ob%=9 THEN GOTO 2400
2206 IF ve%=7 AND ob%=10 THEN GOTO 1900
2207 IF ve%=7 AND ob%=11 THEN GOTO 2100
2208 IF ve%=7 AND ob%=12 THEN GOTO 2300
2209 PRINT"Command not applicable.":GOSUB 52700:GOTO 2200
2300 comp%=2:room%=5:perc%=c02perc%:hc%=0:mult!=0.83869:GOSUB 50000
2301 doors$="0012":GOSUB 50100
2302 PRINT dash$:PRINT"You see:":PRINT
2303 GOSUB 50200
2304 IF ve%=7 AND ob%=11 THEN GOTO 2200
2305 IF ve%=7 AND ob%=12 THEN pinc%=4:GOSUB 52800:IF pinout%>0 THEN c02perc%=4:GOTO 2600 ELSE GOTO 2300
2306 PRINT"Command not applicable.":GOSUB 52700:GOTO 2300
2400 comp%=2:room%=6:perc%=c02perc%:hc%=0:mult!=0.033878:GOSUB 50000
2401 doors$="0100":GOSUB 50100
2402 PRINT dash$:PRINT"You see:":PRINT
2403 IF nfa0206%<=0 THEN PRINT"* a note on the floor":GOTO 2409
2404 PRINT"* a note saying:":PEN 2
2405 PRINT" The period is the number of"
2406 PRINT" components of periods up to and"
2407 PRINT" including 3 subtracted by one."
2408 PEN 1
2409 :
2410 GOSUB 50200
2411 IF ve%=7 AND ob%=10 THEN GOTO 2200
2412 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0206%=1:GOTO 2400
2413 PRINT"Command not applicable.":GOSUB 52700:GOTO 2400
2500 comp%=2:room%=7:perc%=c02perc%:hc%=0:mult!=0.89192:GOSUB 50000
2501 doors$="2100":GOSUB 50100
2502 PRINT dash$:PRINT"You see:":PRINT
2503 GOSUB 50200
2504 IF ve%=7 AND ob%=9 THEN pinc%=4:GOSUB 52800:IF pinout%>0 THEN c02perc%=4:GOTO 4000 ELSE GOTO 2500
2505 IF ve%=7 AND ob%=10 THEN GOTO 2100
2506 PRINT"Command not applicable.":GOSUB 52700:GOTO 2500
2600 comp%=3:room%=0:perc%=c03perc%:hc%=0:mult!=0.94641:GOSUB 50000
2601 doors$="0021":GOSUB 50100
2602 PRINT dash$:PRINT"You see:":PRINT
2603 IF nfa0300%<=0 THEN PRINT"* a note on the floor":GOTO 2608
2604 PRINT"* a note saying:":PEN 2
2605 PRINT" The first part of a sentence: 'The"
2606 PRINT" component is a perfect ...'"
2607 PEN 1
2608 :
2609 GOSUB 50200
2610 IF ve%=7 AND ob%=11 THEN pinc%=2:GOSUB 52800:IF pinout%>0 THEN c03perc%=2:GOTO 2300 ELSE GOTO 2600
2611 IF ve%=7 AND ob%=12 THEN GOTO 2700
2612 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0300%=1:GOTO 2600
2613 PRINT"Command not applicable.":GOSUB 52700:GOTO 2600
2700 comp%=3:room%=1:perc%=c03perc%:hc%=0:mult!=0.26588:GOSUB 50000
2701 doors$="1011":GOSUB 50100
2702 PRINT dash$:PRINT"You see:":PRINT
2703 GOSUB 50200
2704 IF ve%=7 AND ob%=9 THEN GOTO 3000
2705 IF ve%=7 AND ob%=11 THEN GOTO 2600
2706 IF ve%=7 AND ob%=12 THEN GOTO 2800
2707 PRINT"Command not applicable.":GOSUB 52700:GOTO 2700
2800 comp%=3:room%=2:perc%=c03perc%:hc%=1:mult!=0.005731:GOSUB 50000
2801 doors$="1011":GOSUB 50100
2802 PRINT dash$:PRINT"You see:":PRINT
2803 PRINT"* an inactive transmitter"
2804 GOSUB 50200
2805 IF ve%=7 AND ob%=9 THEN GOTO 3200
2806 IF ve%=7 AND ob%=11 THEN GOTO 2700
2807 IF ve%=7 AND ob%=12 THEN GOTO 2900
2808 PRINT"Command not applicable.":GOSUB 52700:GOTO 2800
2900 comp%=3:room%=3:perc%=c03perc%:hc%=0:mult!=0.91991:GOSUB 50000
2901 doors$="0012":GOSUB 50100
2902 PRINT dash$:PRINT"You see:":PRINT
2903 GOSUB 50200
2904 IF ve%=7 AND ob%=11 THEN GOTO 2800
2905 IF ve%=7 AND ob%=12 THEN pinc%=2:GOSUB 52800:IF pinout%>0 THEN c03perc%=2:GOTO 3300 ELSE GOTO 2900
2906 PRINT"Command not applicable.":GOSUB 52700:GOTO 2900
3000 comp%=3:room%=4:perc%=c03perc%:hc%=0:mult!=0.28205:GOSUB 50000
3001 doors$="0101":GOSUB 50100
3002 PRINT dash$:PRINT"You see:":PRINT
3003 GOSUB 50200
3004 IF ve%=7 AND ob%=10 THEN GOTO 2700
3005 IF ve%=7 AND ob%=12 THEN GOTO 3100
3006 PRINT"Command not applicable.":GOSUB 52700:GOTO 3000
3100 comp%=3:room%=5:perc%=c03perc%:hc%=0:mult!=0.067306:GOSUB 50000
3101 doors$="0011":GOSUB 50100
3102 PRINT dash$:PRINT"You see:":PRINT
3103 IF ncl0305%>0 THEN PRINT"* a locked case":GOTO 3107
3104 PRINT"* a case with a note saying:":PEN 2
3105 PRINT" circle"
3106 PEN 1
3107 :
3108 GOSUB 50200
3109 IF ve%=7 AND ob%=11 THEN GOTO 3000
3110 IF ve%=7 AND ob%=12 THEN GOTO 3200
3111 IF ncl0305%>0 AND ve%=3 AND ob%=2 THEN GOTO 3113
3112 PRINT"Command not applicable.":GOSUB 52700:GOTO 3100
3113 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
3114 PRINT:PEN 2
3115 PRINT" How many components of exact period 4"
3116 PRINT" does the Mandelbrot set have?"
3117 PEN 1:PRINT
3118 IF hex%>0 THEN PRINT"The magic oracle tells: 6":PRINT
3119 INPUT"Your answer > ",nicans$
3120 IF nicans$="6" THEN ncl0305%=0 ELSE PRINT"Incorrect.":GOSUB 52700
3121 GOTO 3100
3200 comp%=3:room%=6:perc%=c03perc%:hc%=0:mult!=0.017488:GOSUB 50000
3201 doors$="0110":GOSUB 50100
3202 PRINT dash$:PRINT"You see:":PRINT
3203 GOSUB 50200
3204 IF ve%=7 AND ob%=10 THEN GOTO 2800
3205 IF ve%=7 AND ob%=11 THEN GOTO 3100
3206 PRINT"Command not applicable.":GOSUB 52700:GOTO 3200
3300 comp%=4:room%=0:perc%=c04perc%:hc%=0:mult!=0.96317:GOSUB 50000
3301 doors$="0021":GOSUB 50100
3302 PRINT dash$:PRINT"You see:":PRINT
3303 IF nfa0400%<=0 THEN PRINT"* a note on the floor":GOTO 3307
3304 PRINT"* a note saying:":PEN 2
3305 PRINT" This component's area equals 3/8*PI."
3306 PEN 1
3307 :
3308 GOSUB 50200
3309 IF ve%=7 AND ob%=11 THEN pinc%=1:GOSUB 52800:IF pinout%>0 THEN c04perc%=1:GOTO 2900 ELSE GOTO 3300
3310 IF ve%=7 AND ob%=12 THEN GOTO 3400
3311 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0400%=1:GOTO 3300
3312 PRINT"Command not applicable.":GOSUB 52700:GOTO 3300
3400 comp%=4:room%=1:perc%=c04perc%:hc%=0:mult!=0.1226:GOSUB 50000
3401 doors$="1011":GOSUB 50100
3402 PRINT dash$:PRINT"You see:":PRINT
3403 GOSUB 50200
3404 IF ve%=7 AND ob%=9 THEN GOTO 3700
3405 IF ve%=7 AND ob%=11 THEN GOTO 3300
3406 IF ve%=7 AND ob%=12 THEN GOTO 3500
3407 PRINT"Command not applicable.":GOSUB 52700:GOTO 3400
3500 comp%=4:room%=2:perc%=c04perc%:hc%=1:mult!=0.010479:GOSUB 50000
3501 doors$="0010":GOSUB 50100
3502 PRINT dash$:PRINT"You see:":PRINT
3503 PRINT"* an inactive transmitter"
3504 PRINT"* Benoit Mandelbrot in a prison cell"
3505 GOSUB 50200
3506 IF ve%=7 AND ob%=11 THEN GOTO 3400
3507 IF (ve%=3 AND ob%=3)OR(ve%=4 AND ob%=6) THEN GOTO 3509
3508 PRINT"Command not applicable.":GOSUB 52700:GOTO 3500
3509 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"Benoit's cell door."
3510 PRINT:PRINT"But beware! You only have a limited":PRINT"number of  !":PRINT
3511 PEN 2
3512 PRINT" Affinely conjugate the Mandelbrot"
3513 PRINT" set p(z)=z^2+d with the logistic map"
3514 PRINT" f(z)=c*z*(1-z) via h(z)=v*z+w such"
3515 PRINT" that h(p(z))=f(h(z))."
3516 PEN 1:PRINT
3517 PRINT"  (0) v=1/c,w=1/2,d=(2*c+c^2)/4"
3518 PRINT"  (1) v=1/c,w=2,d=(2*c+c^2)/5"
3519 PRINT"  (2) v=-1/c,w=1/2,d=-(c^2-2*c)/4"
3520 PRINT"  (3) v=sqrt(1/c),w=-1/2,d=-(c^2-2*c)/4"
3521 IF hex%>0 THEN PRINT"The magic oracle tells: '2'"
3522 cellc%=0:FOR cellloop%=3 TO 1 STEP -1
3523 PRINT:PRINT"Your answer (";cellloop%;"attempts left) ";:INPUT"> ",cellans%
3524 IF cellans%=2 THEN cellloop%=0:cellc%=1
3525 NEXT
3526 IF cellc%<=0 THEN PRINT:PRINT"An alarm went off. You will be":PRINT"teleported back to the game start":PRINT"but retain your knowledge.":INPUT"[please press enter]",waitkey$:GOTO 1500
3527 CLS:PRINT dash$:PRINT"Congratulations!":PRINT dash$:PRINT"You have successfully completed your"
3528 PRINT"task! Benoit Mandelbrot has been":PRINT"rescued, and mathematics saved!":PRINT:END
3600 comp%=4:room%=3:perc%=c04perc%:hc%=0:mult!=0.97926:GOSUB 50000
3601 doors$="0001":GOSUB 50100
3602 PRINT dash$:PRINT"You see:":PRINT
3603 GOSUB 50200
3604 IF ve%=7 AND ob%=12 THEN GOTO 3700
3605 PRINT"Command not applicable.":GOSUB 52700:GOTO 3600
3700 comp%=4:room%=4:perc%=c04perc%:hc%=0:mult!=0.75237:GOSUB 50000
3701 doors$="1110":GOSUB 50100
3702 PRINT dash$:PRINT"You see:":PRINT
3703 GOSUB 50200
3704 IF ve%=7 AND ob%=9 THEN GOTO 3800
3705 IF ve%=7 AND ob%=10 THEN GOTO 3400
3706 IF ve%=7 AND ob%=11 THEN GOTO 3600
3707 PRINT"Command not applicable.":GOSUB 52700:GOTO 3700
3800 comp%=4:room%=5:perc%=c04perc%:hc%=0:mult!=0.84248:GOSUB 50000
3801 doors$="0101":GOSUB 50100
3802 PRINT dash$:PRINT"You see:":PRINT
3803 GOSUB 50200
3804 IF ve%=7 AND ob%=10 THEN GOTO 3700
3805 IF ve%=7 AND ob%=12 THEN GOTO 3900
3806 PRINT"Command not applicable.":GOSUB 52700:GOTO 3800
3900 comp%=4:room%=6:perc%=c04perc%:hc%=0:mult!=0.9584:GOSUB 50000
3901 doors$="0010":GOSUB 50100
3902 PRINT dash$:PRINT"You see:":PRINT
3903 GOSUB 50200
3904 IF ve%=7 AND ob%=11 THEN GOTO 3800
3905 PRINT"Command not applicable.":GOSUB 52700:GOTO 3900
4000 comp%=5:room%=0:perc%=c05perc%:hc%=0:mult!=0.84301:GOSUB 50000
4001 doors$="1200":GOSUB 50100
4002 PRINT dash$:PRINT"You see:":PRINT
4003 GOSUB 50200
4004 IF ve%=7 AND ob%=9 THEN GOTO 4100
4005 IF ve%=7 AND ob%=10 THEN pinc%=16:GOSUB 52800:IF pinout%>0 THEN c05perc%=16:GOTO 2500 ELSE GOTO 4000
4006 PRINT"Command not applicable.":GOSUB 52700:GOTO 4000
4100 comp%=5:room%=1:perc%=c05perc%:hc%=1:mult!=0.0057047:GOSUB 50000
4101 doors$="0100":GOSUB 50100
4102 PRINT dash$:PRINT"You see:":PRINT
4103 PRINT"* an active transmitter"
4104 IF nfa0501%<=0 THEN PRINT"* a note on the floor":GOTO 4108
4105 PRINT"* a note saying:":PEN 2
4106 PRINT" The periodicity is 16."
4107 PEN 1
4108 :
4109 GOSUB 50200
4110 IF ve%=7 AND ob%=10 THEN GOTO 4000
4111 IF ve%=5 AND ob%=5 THEN GOTO 1600
4112 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0501%=1:GOTO 4100
4113 PRINT"Command not applicable.":GOSUB 52700:GOTO 4100
4214 MODE 1:CLS
4215 direction$="NSWE":DIM param$(4):INK 2,26
4216 heromdet%=0:DIM parts%(3):parts%(1)=0:parts%(2)=0:parts%(3)=0:hex%=0:dash$="---------------------------------------"
4217 c00perc%=0:dcl0000%=1:dcp0000%=3:dcl0002%=0:dcp0002%=1:dcl0003%=1:dcp0003%=2:nfa0005%=0:c01perc%=0:nba0101%=0:nbh0101%=1:c02perc%=0:nfa0206%=0:c03perc%=0:nfa0300%=0
4218 ncl0305%=1:c04perc%=0:nfa0400%=0:c05perc%=0:nfa0501%=0
4219 GOTO 1500
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
