1 GOTO 5228
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
1222 cellc%=0:FOR cellloop%=2 TO 1 STEP -1
1223 PRINT:PRINT"Your answer (";cellloop%;"attempts left) ";:INPUT"> ",cellans%
1224 IF cellans%=2 THEN cellloop%=0:cellc%=1
1225 NEXT
1226 IF cellc%<=0 THEN PRINT:PRINT"An alarm went off. You will be":PRINT"teleported back to the game start":PRINT"but retain your knowledge.":INPUT"[please press enter]",waitkey$:GOTO 5000
1227 CLS:PRINT dash$:PRINT"Congratulations!":PRINT dash$:PRINT"You have successfully completed your"
1228 PRINT"task! Benoit Mandelbrot has been":PRINT"rescued, and mathematics saved!":PRINT:END
1300 comp%=4:room%=3:perc%=c04perc%:hc%=0:mult!=0.97926:GOSUB 50000
1301 doors$="0021":GOSUB 50100
1302 PRINT dash$:PRINT"You see:":PRINT
1303 GOSUB 50200
1304 IF ve%=7 AND ob%=11 THEN pinc%=1:GOSUB 52800:IF pinout%>0 THEN c04perc%=1:GOTO 1700 ELSE GOTO 1300
1305 IF ve%=7 AND ob%=12 THEN GOTO 1400
1306 PRINT"Command not applicable.":GOSUB 52700:GOTO 1300
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
1601 doors$="0010":GOSUB 50100
1602 PRINT dash$:PRINT"You see:":PRINT
1603 GOSUB 50200
1604 IF ve%=7 AND ob%=11 THEN GOTO 1500
1605 PRINT"Command not applicable.":GOSUB 52700:GOTO 1600
1700 comp%=6:room%=0:perc%=c06perc%:hc%=0:mult!=0.92797:GOSUB 50000
1701 doors$="1002":GOSUB 50100
1702 PRINT dash$:PRINT"You see:":PRINT
1703 IF ncl0600%>0 THEN PRINT"* a locked case":GOTO 1707
1704 PRINT"* a case with a note saying:":PEN 2
1705 PRINT" The current periodicty is 5."
1706 PEN 1
1707 :
1708 GOSUB 50200
1709 IF ve%=7 AND ob%=9 THEN GOTO 1900
1710 IF ve%=7 AND ob%=12 THEN pinc%=5:GOSUB 52800:IF pinout%>0 THEN c06perc%=5:GOTO 1300 ELSE GOTO 1700
1711 IF ncl0600%>0 AND ve%=3 AND ob%=2 THEN GOTO 1713
1712 PRINT"Command not applicable.":GOSUB 52700:GOTO 1700
1713 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
1714 PEN 2
1715 PRINT" The accumulation point of the"
1716 PRINT" classical period doubling on the real"
1717 PRINT" axis lies within"
1718 PEN 1:PRINT
1719 PRINT"  (0) [-1.437 .. -1.436]"
1720 PRINT"  (1) [-1.423 .. -1.422]"
1721 PRINT"  (2) {-1.402 .. -1.401]"
1722 PRINT"  (3) [-1.401 .. -1.400]"
1723 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 2":PRINT
1724 INPUT"Your answer > ",nicans%
1725 IF nicans%=2 THEN ncl0600%=0 ELSE PRINT"Incorrect.":GOSUB 52700
1726 GOTO 1700
1800 comp%=6:room%=1:perc%=c06perc%:hc%=0:mult!=0.16636:GOSUB 50000
1801 doors$="1001":GOSUB 50100
1802 PRINT dash$:PRINT"You see:":PRINT
1803 GOSUB 50200
1804 IF ve%=7 AND ob%=9 THEN GOTO 2200
1805 IF ve%=7 AND ob%=12 THEN GOTO 1900
1806 PRINT"Command not applicable.":GOSUB 52700:GOTO 1800
1900 comp%=6:room%=2:perc%=c06perc%:hc%=0:mult!=0.42176:GOSUB 50000
1901 doors$="0110":GOSUB 50100
1902 PRINT dash$:PRINT"You see:":PRINT
1903 IF nbh0602%>0 THEN PRINT"* a mirror hinging on one corner":GOTO 1910
1904 IF nbh0602%<=0 AND nba0602%<=0 THEN PRINT"* a note behind the mirror":GOTO 1910
1905 PRINT"* a note behind the mirror saying:":PEN 2
1906 PRINT" The Manhattan distance from this"
1907 PRINT" room to the center of the main"
1908 PRINT" cardioid is approximately 1.0321"
1909 PEN 1
1910 :
1911 GOSUB 50200
1912 IF ve%=7 AND ob%=10 THEN GOTO 1700
1913 IF ve%=7 AND ob%=11 THEN GOTO 1800
1914 IF nbh0602%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba0602%=1:GOTO 1900
1915 IF nbh0602%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh0602%=0:GOTO 1900
1916 PRINT"Command not applicable.":GOSUB 52700:GOTO 1900
2000 comp%=6:room%=3:perc%=c06perc%:hc%=0:mult!=0.90907:GOSUB 50000
2001 doors$="0021":GOSUB 50100
2002 PRINT dash$:PRINT"You see:":PRINT
2003 IF ncl0603%>0 THEN PRINT"* a locked case":GOTO 2009
2004 PRINT"* a case with a note saying:":PEN 2
2005 PRINT" The Euclidean distance from this"
2006 PRINT" room to the center of the main"
2007 PRINT" cardioid is approximately 0.7789"
2008 PEN 1
2009 :
2010 GOSUB 50200
2011 IF ve%=7 AND ob%=11 THEN pinc%=5:GOSUB 52800:IF pinout%>0 THEN c06perc%=5:GOTO 3200 ELSE GOTO 2000
2012 IF ve%=7 AND ob%=12 THEN GOTO 2100
2013 IF ncl0603%>0 AND ve%=3 AND ob%=2 THEN GOTO 2015
2014 PRINT"Command not applicable.":GOSUB 52700:GOTO 2000
2015 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
2016 PRINT:PEN 2
2017 PRINT" How many petals shows the Julia set"
2018 PRINT" of"
2019 PRINT" z^2+(-0.22252093395631458717-0.974927"
2020 PRINT" 91218182361934*i)*z"
2021 PEN 1:PRINT
2022 IF hex%>0 THEN PRINT"The magic oracle tells: 7":PRINT
2023 INPUT"Your answer > ",nicans$
2024 IF nicans$="7" THEN ncl0603%=0 ELSE PRINT"Incorrect.":GOSUB 52700
2025 GOTO 2000
2100 comp%=6:room%=4:perc%=c06perc%:hc%=0:mult!=0.45868:GOSUB 50000
2101 doors$="0011":GOSUB 50100
2102 PRINT dash$:PRINT"You see:":PRINT
2103 GOSUB 50200
2104 IF ve%=7 AND ob%=11 THEN GOTO 2000
2105 IF ve%=7 AND ob%=12 THEN GOTO 2200
2106 PRINT"Command not applicable.":GOSUB 52700:GOTO 2100
2200 comp%=6:room%=5:perc%=c06perc%:hc%=1:mult!=0.012029:GOSUB 50000
2201 doors$="1111":GOSUB 50100
2202 PRINT dash$:PRINT"You see:":PRINT
2203 IF nfa0605%<=0 THEN PRINT"* a note on the floor":GOTO 2210
2204 PRINT"* a note saying:":PEN 2
2205 PRINT" The Euclidean distance of the real"
2206 PRINT" coordinate from this room to the"
2207 PRINT" center of the north period-3 bulb"
2208 PRINT" is approximately 0.3851"
2209 PEN 1
2210 :
2211 GOSUB 50200
2212 IF ve%=7 AND ob%=9 THEN GOTO 2400
2213 IF ve%=7 AND ob%=10 THEN GOTO 1800
2214 IF ve%=7 AND ob%=11 THEN GOTO 2100
2215 IF ve%=7 AND ob%=12 THEN GOTO 2300
2216 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0605%=1:GOTO 2200
2217 PRINT"Command not applicable.":GOSUB 52700:GOTO 2200
2300 comp%=6:room%=6:perc%=c06perc%:hc%=0:mult!=0.14003:GOSUB 50000
2301 doors$="1010":GOSUB 50100
2302 PRINT dash$:PRINT"You see:":PRINT
2303 GOSUB 50200
2304 IF ve%=7 AND ob%=9 THEN GOTO 2600
2305 IF ve%=7 AND ob%=11 THEN GOTO 2200
2306 PRINT"Command not applicable.":GOSUB 52700:GOTO 2300
2400 comp%=6:room%=7:perc%=c06perc%:hc%=0:mult!=0.26844:GOSUB 50000
2401 doors$="0101":GOSUB 50100
2402 PRINT dash$:PRINT"You see:":PRINT
2403 IF nfa0607%<=0 THEN PRINT"* a note on the floor":GOTO 2407
2404 PRINT"* a note saying:":PEN 2
2405 PRINT" The current periodicity is prime."
2406 PEN 1
2407 :
2408 GOSUB 50200
2409 IF ve%=7 AND ob%=10 THEN GOTO 2200
2410 IF ve%=7 AND ob%=12 THEN GOTO 2500
2411 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0607%=1:GOTO 2400
2412 PRINT"Command not applicable.":GOSUB 52700:GOTO 2400
2500 comp%=6:room%=8:perc%=c06perc%:hc%=0:mult!=0.31206:GOSUB 50000
2501 doors$="0010":GOSUB 50100
2502 PRINT dash$:PRINT"You see:":PRINT
2503 GOSUB 50200
2504 IF ve%=7 AND ob%=11 THEN GOTO 2400
2505 PRINT"Command not applicable.":GOSUB 52700:GOTO 2500
2600 comp%=6:room%=9:perc%=c06perc%:hc%=0:mult!=0.91578:GOSUB 50000
2601 doors$="0100":GOSUB 50100
2602 PRINT dash$:PRINT"You see:":PRINT
2603 IF nfa0609%<=0 THEN PRINT"* a note on the floor":GOTO 2609
2604 PRINT"* a note saying:":PEN 2
2605 PRINT" The Euclidean distance from this"
2606 PRINT" room to the center of the main"
2607 PRINT" cardioid is approximately 0.7712"
2608 PEN 1
2609 :
2610 GOSUB 50200
2611 IF ve%=7 AND ob%=10 THEN GOTO 2300
2612 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0609%=1:GOTO 2600
2613 PRINT"Command not applicable.":GOSUB 52700:GOTO 2600
2700 comp%=7:room%=0:perc%=c07perc%:hc%=0:mult!=0.065867:GOSUB 50000
2701 doors$="1001":GOSUB 50100
2702 PRINT dash$:PRINT"You see:":PRINT
2703 IF nbh0700%>0 THEN PRINT"* a mirror hinging on one corner":GOTO 2709
2704 IF nbh0700%<=0 AND nba0700%<=0 THEN PRINT"* a note behind the mirror":GOTO 2709
2705 PRINT"* a note behind the mirror saying:":PEN 2
2706 PRINT" This component only harbours one"
2707 PRINT" parabolic door."
2708 PEN 1
2709 :
2710 GOSUB 50200
2711 IF ve%=7 AND ob%=9 THEN GOTO 2900
2712 IF ve%=7 AND ob%=12 THEN GOTO 2800
2713 IF nbh0700%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba0700%=1:GOTO 2700
2714 IF nbh0700%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh0700%=0:GOTO 2700
2715 PRINT"Command not applicable.":GOSUB 52700:GOTO 2700
2800 comp%=7:room%=1:perc%=c07perc%:hc%=0:mult!=0.27556:GOSUB 50000
2801 doors$="1010":GOSUB 50100
2802 PRINT dash$:PRINT"You see:":PRINT
2803 IF ncl0701%>0 THEN PRINT"* a locked case":GOTO 2807
2804 PRINT"* a case with a note saying:":PEN 2
2805 PRINT" The current periodicty is 15."
2806 PEN 1
2807 :
2808 GOSUB 50200
2809 IF ve%=7 AND ob%=9 THEN GOTO 3100
2810 IF ve%=7 AND ob%=11 THEN GOTO 2700
2811 IF ncl0701%>0 AND ve%=3 AND ob%=2 THEN GOTO 2813
2812 PRINT"Command not applicable.":GOSUB 52700:GOTO 2800
2813 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
2814 PEN 2
2815 PRINT" In which year did Mandelbrot publish"
2816 PRINT" for the first time about his set?"
2817 PEN 1:PRINT
2818 PRINT"  (0) 1976"
2819 PRINT"  (1) 1980"
2820 PRINT"  (2) 1986"
2821 PRINT"  (3) 1990"
2822 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 1":PRINT
2823 INPUT"Your answer > ",nicans%
2824 IF nicans%=1 THEN ncl0701%=0 ELSE PRINT"Incorrect.":GOSUB 52700
2825 GOTO 2800
2900 comp%=7:room%=2:perc%=c07perc%:hc%=1:mult!=0.0046402:GOSUB 50000
2901 doors$="1100":GOSUB 50100
2902 PRINT dash$:PRINT"You see:":PRINT
2903 PRINT"* an active transmitter"
2904 GOSUB 50200
2905 IF ve%=7 AND ob%=9 THEN GOTO 3000
2906 IF ve%=7 AND ob%=10 THEN GOTO 2700
2907 IF ve%=5 AND ob%=5 THEN GOTO 4100
2908 PRINT"Command not applicable.":GOSUB 52700:GOTO 2900
3000 comp%=7:room%=3:perc%=c07perc%:hc%=0:mult!=0.0051678:GOSUB 50000
3001 doors$="0101":GOSUB 50100
3002 PRINT dash$:PRINT"You see:":PRINT
3003 GOSUB 50200
3004 IF ve%=7 AND ob%=10 THEN GOTO 2900
3005 IF ve%=7 AND ob%=12 THEN GOTO 3100
3006 PRINT"Command not applicable.":GOSUB 52700:GOTO 3000
3100 comp%=7:room%=4:perc%=c07perc%:hc%=0:mult!=0.20437:GOSUB 50000
3101 doors$="1111":GOSUB 50100
3102 PRINT dash$:PRINT"You see:":PRINT
3103 GOSUB 50200
3104 IF ve%=7 AND ob%=9 THEN GOTO 3300
3105 IF ve%=7 AND ob%=10 THEN GOTO 2800
3106 IF ve%=7 AND ob%=11 THEN GOTO 3000
3107 IF ve%=7 AND ob%=12 THEN GOTO 3200
3108 PRINT"Command not applicable.":GOSUB 52700:GOTO 3100
3200 comp%=7:room%=5:perc%=c07perc%:hc%=0:mult!=0.92438:GOSUB 50000
3201 doors$="0012":GOSUB 50100
3202 PRINT dash$:PRINT"You see:":PRINT
3203 GOSUB 50200
3204 IF ve%=7 AND ob%=11 THEN GOTO 3100
3205 IF ve%=7 AND ob%=12 THEN pinc%=15:GOSUB 52800:IF pinout%>0 THEN c07perc%=15:GOTO 2000 ELSE GOTO 3200
3206 PRINT"Command not applicable.":GOSUB 52700:GOTO 3200
3300 comp%=7:room%=6:perc%=c07perc%:hc%=0:mult!=0.39744:GOSUB 50000
3301 doors$="0100":GOSUB 50100
3302 PRINT dash$:PRINT"You see:":PRINT
3303 IF nfa0706%<=0 THEN PRINT"* a note on the floor":GOTO 3307
3304 PRINT"* a note saying:":PEN 2
3305 PRINT" digit '1' with strikethrough"
3306 PEN 1
3307 :
3308 GOSUB 50200
3309 IF ve%=7 AND ob%=10 THEN GOTO 3100
3310 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0706%=1:GOTO 3300
3311 PRINT"Command not applicable.":GOSUB 52700:GOTO 3300
3400 comp%=8:room%=0:perc%=c08perc%:hc%=0:mult!=0.95037:GOSUB 50000
3401 doors$="1000":GOSUB 50100
3402 PRINT dash$:PRINT"You see:":PRINT
3403 GOSUB 50200
3404 IF ve%=7 AND ob%=9 THEN GOTO 3500
3405 PRINT"Command not applicable.":GOSUB 52700:GOTO 3400
3500 comp%=8:room%=1:perc%=c08perc%:hc%=0:mult!=0.31411:GOSUB 50000
3501 doors$="0101":GOSUB 50100
3502 PRINT dash$:PRINT"You see:":PRINT
3503 IF ncl0801%>0 THEN PRINT"* a locked case":GOTO 3508
3504 PRINT"* a case with a note saying:":PEN 2
3505 PRINT" This component harbours exactly one"
3506 PRINT" parabolic door."
3507 PEN 1
3508 :
3509 GOSUB 50200
3510 IF ve%=7 AND ob%=10 THEN GOTO 3400
3511 IF ve%=7 AND ob%=12 THEN GOTO 3600
3512 IF ncl0801%>0 AND ve%=3 AND ob%=2 THEN GOTO 3514
3513 PRINT"Command not applicable.":GOSUB 52700:GOTO 3500
3514 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
3515 PRINT:PEN 2
3516 PRINT" How many cardioids are there with"
3517 PRINT" periods 1-5?"
3518 PEN 1:PRINT
3519 IF hex%>0 THEN PRINT"The magic oracle tells: 15":PRINT
3520 INPUT"Your answer > ",nicans$
3521 IF nicans$="15" THEN ncl0801%=0 ELSE PRINT"Incorrect.":GOSUB 52700
3522 GOTO 3500
3600 comp%=8:room%=2:perc%=c08perc%:hc%=0:mult!=0.093982:GOSUB 50000
3601 doors$="1010":GOSUB 50100
3602 PRINT dash$:PRINT"You see:":PRINT
3603 GOSUB 50200
3604 IF ve%=7 AND ob%=9 THEN GOTO 4000
3605 IF ve%=7 AND ob%=11 THEN GOTO 3500
3606 PRINT"Command not applicable.":GOSUB 52700:GOTO 3600
3700 comp%=8:room%=3:perc%=c08perc%:hc%=0:mult!=0.90663:GOSUB 50000
3701 doors$="0021":GOSUB 50100
3702 PRINT dash$:PRINT"You see:":PRINT
3703 GOSUB 50200
3704 IF ve%=7 AND ob%=11 THEN pinc%=15:GOSUB 52800:IF pinout%>0 THEN c08perc%=15:GOTO 4700 ELSE GOTO 3700
3705 IF ve%=7 AND ob%=12 THEN GOTO 3800
3706 PRINT"Command not applicable.":GOSUB 52700:GOTO 3700
3800 comp%=8:room%=4:perc%=c08perc%:hc%=0:mult!=0.10566:GOSUB 50000
3801 doors$="1010":GOSUB 50100
3802 PRINT dash$:PRINT"You see:":PRINT
3803 GOSUB 50200
3804 IF ve%=7 AND ob%=9 THEN GOTO 3900
3805 IF ve%=7 AND ob%=11 THEN GOTO 3700
3806 PRINT"Command not applicable.":GOSUB 52700:GOTO 3800
3900 comp%=8:room%=5:perc%=c08perc%:hc%=0:mult!=0.070789:GOSUB 50000
3901 doors$="0101":GOSUB 50100
3902 PRINT dash$:PRINT"You see:":PRINT
3903 GOSUB 50200
3904 IF ve%=7 AND ob%=10 THEN GOTO 3800
3905 IF ve%=7 AND ob%=12 THEN GOTO 4000
3906 PRINT"Command not applicable.":GOSUB 52700:GOTO 3900
4000 comp%=8:room%=6:perc%=c08perc%:hc%=0:mult!=0.004486:GOSUB 50000
4001 doors$="0111":GOSUB 50100
4002 PRINT dash$:PRINT"You see:":PRINT
4003 IF nfa0806%<=0 THEN PRINT"* a note on the floor":GOTO 4009
4004 PRINT"* a note saying:":PEN 2
4005 PRINT" The component resides entirely in"
4006 PRINT" the positive imaginary part of the"
4007 PRINT" complex plane."
4008 PEN 1
4009 :
4010 GOSUB 50200
4011 IF ve%=7 AND ob%=10 THEN GOTO 3600
4012 IF ve%=7 AND ob%=11 THEN GOTO 3900
4013 IF ve%=7 AND ob%=12 THEN GOTO 4100
4014 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0806%=1:GOTO 4000
4015 PRINT"Command not applicable.":GOSUB 52700:GOTO 4000
4100 comp%=8:room%=7:perc%=c08perc%:hc%=1:mult!=0.0065632:GOSUB 50000
4101 doors$="0010":GOSUB 50100
4102 PRINT dash$:PRINT"You see:":PRINT
4103 PRINT"* an active transmitter"
4104 GOSUB 50200
4105 IF ve%=7 AND ob%=11 THEN GOTO 4000
4106 IF ve%=5 AND ob%=5 THEN GOTO 2700
4107 PRINT"Command not applicable.":GOSUB 52700:GOTO 4100
4200 comp%=9:room%=0:perc%=c09perc%:hc%=0:mult!=0.15309:GOSUB 50000
4201 doors$="1000":GOSUB 50100
4202 PRINT dash$:PRINT"You see:":PRINT
4203 IF ncl0900%>0 THEN PRINT"* a locked case":GOTO 4207
4204 PRINT"* a case with a note saying:":PEN 2
4205 PRINT" Current component's period is 105."
4206 PEN 1
4207 :
4208 GOSUB 50200
4209 IF ve%=7 AND ob%=9 THEN GOTO 4500
4210 IF ncl0900%>0 AND ve%=3 AND ob%=2 THEN GOTO 4212
4211 PRINT"Command not applicable.":GOSUB 52700:GOTO 4200
4212 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
4213 PRINT:PEN 2
4214 PRINT" Which is the smallest period p in"
4215 PRINT" z^2+c that allows for 1 million or"
4216 PRINT" more hyperbolic compoennts of that"
4217 PRINT" exact period?"
4218 PEN 1:PRINT
4219 IF hex%>0 THEN PRINT"The magic oracle tells: 21":PRINT
4220 INPUT"Your answer > ",nicans$
4221 IF nicans$="21" THEN ncl0900%=0 ELSE PRINT"Incorrect.":GOSUB 52700
4222 GOTO 4200
4300 comp%=9:room%=1:perc%=c09perc%:hc%=0:mult!=0.31494:GOSUB 50000
4301 doors$="1001":GOSUB 50100
4302 PRINT dash$:PRINT"You see:":PRINT
4303 IF nfa0901%<=0 THEN PRINT"* a note on the floor":GOTO 4309
4304 PRINT"* a note saying:":PEN 2
4305 PRINT" The two leftmost digits of the"
4306 PRINT" current periodicity were encoded in"
4307 PRINT" a simple cipher by the letter 'J'-"
4308 PEN 1
4309 :
4310 GOSUB 50200
4311 IF ve%=7 AND ob%=9 THEN GOTO 4800
4312 IF ve%=7 AND ob%=12 THEN GOTO 4400
4313 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0901%=1:GOTO 4300
4314 PRINT"Command not applicable.":GOSUB 52700:GOTO 4300
4400 comp%=9:room%=2:perc%=c09perc%:hc%=1:mult!=0.0039899:GOSUB 50000
4401 doors$="0011":GOSUB 50100
4402 PRINT dash$:PRINT"You see:":PRINT
4403 IF duh0902%>0 THEN PRINT"* a carpet with a loose corner":GOTO 4406
4404 IF duh0902%<=0 AND dup0902%<=0 THEN PRINT"* just a carpet with nothing underneath":GOTO 4406
4405 PRINT"* an electronic device labelled '3'"
4406 :
4407 GOSUB 50200
4408 IF ve%=7 AND ob%=11 THEN GOTO 4300
4409 IF ve%=7 AND ob%=12 THEN GOTO 4500
4410 IF duh0902%>0 AND ve%=2 AND (pp%=1 OR pp%=3) AND ob%=7 THEN duh0902%=0:GOTO 4400
4411 IF duh0902%<=0 AND dup0902%>0 AND ve%=6 AND ob%=4 THEN IF parts%(3)>0 THEN PRINT"You already carry this part.":GOSUB 52700:GOTO 4400 ELSE parts%(3)=1:dup0902%=0:heromdet%=heromdet%+1:GOTO 4400
4412 PRINT"Command not applicable.":GOSUB 52700:GOTO 4400
4500 comp%=9:room%=3:perc%=c09perc%:hc%=0:mult!=0.11574:GOSUB 50000
4501 doors$="1110":GOSUB 50100
4502 PRINT dash$:PRINT"You see:":PRINT
4503 IF nbh0903%>0 THEN PRINT"* a mirror hinging on one corner":GOTO 4510
4504 IF nbh0903%<=0 AND nba0903%<=0 THEN PRINT"* a note behind the mirror":GOTO 4510
4505 PRINT"* a note behind the mirror saying:":PEN 2
4506 PRINT" The rightmost digit of the period"
4507 PRINT" was encoded in a simple by letter"
4508 PRINT" 'E'."
4509 PEN 1
4510 :
4511 GOSUB 50200
4512 IF ve%=7 AND ob%=9 THEN GOTO 4600
4513 IF ve%=7 AND ob%=10 THEN GOTO 4200
4514 IF ve%=7 AND ob%=11 THEN GOTO 4400
4515 IF nbh0903%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba0903%=1:GOTO 4500
4516 IF nbh0903%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh0903%=0:GOTO 4500
4517 PRINT"Command not applicable.":GOSUB 52700:GOTO 4500
4600 comp%=9:room%=4:perc%=c09perc%:hc%=0:mult!=0.16999:GOSUB 50000
4601 doors$="0101":GOSUB 50100
4602 PRINT dash$:PRINT"You see:":PRINT
4603 GOSUB 50200
4604 IF ve%=7 AND ob%=10 THEN GOTO 4500
4605 IF ve%=7 AND ob%=12 THEN GOTO 4700
4606 PRINT"Command not applicable.":GOSUB 52700:GOTO 4600
4700 comp%=9:room%=5:perc%=c09perc%:hc%=0:mult!=0.82915:GOSUB 50000
4701 doors$="0012":GOSUB 50100
4702 PRINT dash$:PRINT"You see:":PRINT
4703 GOSUB 50200
4704 IF ve%=7 AND ob%=11 THEN GOTO 4600
4705 IF ve%=7 AND ob%=12 THEN pinc%=105:GOSUB 52800:IF pinout%>0 THEN c09perc%=105:GOTO 3700 ELSE GOTO 4700
4706 PRINT"Command not applicable.":GOSUB 52700:GOTO 4700
4800 comp%=9:room%=6:perc%=c09perc%:hc%=0:mult!=0.56857:GOSUB 50000
4801 doors$="1101":GOSUB 50100
4802 PRINT dash$:PRINT"You see:":PRINT
4803 IF nfa0906%<=0 THEN PRINT"* a note on the floor":GOTO 4807
4804 PRINT"* a note saying:":PEN 2
4805 PRINT" Current periodicity has 3 digits."
4806 PEN 1
4807 :
4808 GOSUB 50200
4809 IF ve%=7 AND ob%=9 THEN GOTO 5000
4810 IF ve%=7 AND ob%=10 THEN GOTO 4300
4811 IF ve%=7 AND ob%=12 THEN GOTO 4900
4812 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0906%=1:GOTO 4800
4813 PRINT"Command not applicable.":GOSUB 52700:GOTO 4800
4900 comp%=9:room%=7:perc%=c09perc%:hc%=0:mult!=0.47288:GOSUB 50000
4901 doors$="1010":GOSUB 50100
4902 PRINT dash$:PRINT"You see:":PRINT
4903 GOSUB 50200
4904 IF ve%=7 AND ob%=9 THEN GOTO 5100
4905 IF ve%=7 AND ob%=11 THEN GOTO 4800
4906 PRINT"Command not applicable.":GOSUB 52700:GOTO 4900
5000 comp%=9:room%=8:perc%=c09perc%:hc%=0:mult!=0.67785:GOSUB 50000
5001 doors$="0101":GOSUB 50100
5002 PRINT dash$:PRINT"You see:":PRINT
5003 IF dcl0908%>0 THEN PRINT"* a locked case":GOTO 5007
5004 IF dcl0908%<=0 AND dcp0908%<=0 THEN PRINT"* an open and empty case":GOTO 5007
5005 PRINT"* the case contains:"
5006 PRINT" an electronic device labelled '1'"
5007 :
5008 GOSUB 50200
5009 IF ve%=7 AND ob%=10 THEN GOTO 4800
5010 IF ve%=7 AND ob%=12 THEN GOTO 5100
5011 IF dcl0908%>0 AND ve%=3 AND ob%=2 THEN GOTO 5014
5012 IF dcl0908%<=0 AND dcp0908%>0 AND ve%=6 AND ob%=4 THEN IF parts%(1)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 5000 ELSE parts%(1)=1:heromdet%=heromdet%+1:dcp0908%=0:GOTO 5000
5013 PRINT"Command not applicable.":GOSUB 52700:GOTO 5000
5014 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
5015 PEN 2
5016 PRINT" Benoit Mandelbrot worked for many"
5017 PRINT" years at:"
5018 PEN 1:PRINT
5019 PRINT"  (0) International Business Machines Corporation"
5020 PRINT"  (1) Advanced Micro Devices"
5021 PRINT"  (2) Federal Reserve Bank"
5022 PRINT"  (3) Dornier"
5023 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 0":PRINT
5024 INPUT"Your answer > ",dicans%
5025 IF dicans%=0 THEN dcl0908%=0 ELSE PRINT"Incorrect.":GOSUB 52700
5026 GOTO 5000
5100 comp%=9:room%=9:perc%=c09perc%:hc%=0:mult!=0.58353:GOSUB 50000
5101 doors$="0110":GOSUB 50100
5102 PRINT dash$:PRINT"You see:":PRINT
5103 IF dcl0909%>0 THEN PRINT"* a locked case":GOTO 5107
5104 IF dcl0909%<=0 AND dcp0909%<=0 THEN PRINT"* an open and empty case":GOTO 5107
5105 PRINT"* the case contains:"
5106 PRINT" an electronic device labelled '2'"
5107 :
5108 GOSUB 50200
5109 IF ve%=7 AND ob%=10 THEN GOTO 4900
5110 IF ve%=7 AND ob%=11 THEN GOTO 5000
5111 IF dcl0909%>0 AND ve%=3 AND ob%=2 THEN GOTO 5114
5112 IF dcl0909%<=0 AND dcp0909%>0 AND ve%=6 AND ob%=4 THEN IF parts%(2)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 5100 ELSE parts%(2)=1:heromdet%=heromdet%+1:dcp0909%=0:GOTO 5100
5113 PRINT"Command not applicable.":GOSUB 52700:GOTO 5100
5114 CLS:PRINT dash$:PRINT"You have to answer a question to open":PRINT"the case.":PRINT
5115 PEN 2
5116 PRINT" The c-parameter space for z^d+c"
5117 PRINT" limits for d->inf to which"
5118 PRINT" mathematical object?"
5119 PEN 1:PRINT
5120 PRINT"  (0) {c | c in C, ||Re(c)|| < 1 and ||Im(c)|| <= 1}"
5121 PRINT"  (1) {c | c in C, ||c+3/4|| <= 1}"
5122 PRINT"  (2) {c | c in C, ||c|| < 1}"
5123 PRINT"  (3) {c | c in C, ||c|| <= 1}"
5124 PRINT:IF hex%>0 THEN PRINT"The magic oracle tells: 3":PRINT
5125 INPUT"Your answer > ",dicans%
5126 IF dicans%=3 THEN dcl0909%=0 ELSE PRINT"Incorrect.":GOSUB 52700
5127 GOTO 5100
5228 MODE 1:CLS
5229 direction$="NSWE":DIM param$(4):INK 2,26
5230 heromdet%=0:DIM parts%(3):parts%(1)=0:parts%(2)=0:parts%(3)=0:hex%=0:dash$="---------------------------------------"
5231 c04perc%=0:nfa0400%=0:c06perc%=0:ncl0600%=1:nba0602%=0:nbh0602%=1:ncl0603%=1:nfa0605%=0:nfa0607%=0:nfa0609%=0:c07perc%=0:nba0700%=0:nbh0700%=1:ncl0701%=1:nfa0706%=0
5232 c08perc%=0:ncl0801%=1:nfa0806%=0:c09perc%=0:ncl0900%=1:nfa0901%=0:duh0902%=1:dup0902%=3:nba0903%=0:nbh0903%=1:nfa0906%=0:dcl0908%=1:dcp0908%=1:dcl0909%=1:dcp0909%=2
5233 GOTO 5000
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
