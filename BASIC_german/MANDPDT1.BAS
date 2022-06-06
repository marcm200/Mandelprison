1 GOTO 5229
10 REM Mandelprison - Free Benoit!
11 REM text adventure in style of Thor - Trilogy for Schneider CPC464 from the 80s
12 REM Marc Meidlinger May 2022
1000 comp%=4:room%=0:perc%=c04perc%:hc%=0:mult!=0.96317:GOSUB 50000
1001 doors$="0001":GOSUB 50100
1002 PRINT dash$:PRINT"Du siehst:":PRINT
1003 IF nfa0400%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 1008
1004 PRINT"* eine Notiz:":PEN 2
1005 PRINT" Die Flaeche dieser Komponente ist"
1006 PRINT" 3/8*PI."
1007 PEN 1
1008 :
1009 GOSUB 50200
1010 IF ve%=7 AND ob%=12 THEN GOTO 1100
1011 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0400%=1:GOTO 1000
1012 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1000
1100 comp%=4:room%=1:perc%=c04perc%:hc%=0:mult!=0.1226:GOSUB 50000
1101 doors$="1011":GOSUB 50100
1102 PRINT dash$:PRINT"Du siehst:":PRINT
1103 GOSUB 50200
1104 IF ve%=7 AND ob%=9 THEN GOTO 1400
1105 IF ve%=7 AND ob%=11 THEN GOTO 1000
1106 IF ve%=7 AND ob%=12 THEN GOTO 1200
1107 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1100
1200 comp%=4:room%=2:perc%=c04perc%:hc%=1:mult!=0.010479:GOSUB 50000
1201 doors$="0010":GOSUB 50100
1202 PRINT dash$:PRINT"Du siehst:":PRINT
1203 PRINT"* ein inaktiver Transmitter"
1204 PRINT"* Benoit Mandelbrot in einer Gefaengniszelle"
1205 GOSUB 50200
1206 IF ve%=7 AND ob%=11 THEN GOTO 1100
1207 IF (ve%=3 AND ob%=3)OR(ve%=4 AND ob%=6) THEN GOTO 1209
1208 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1200
1209 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"Benoits Zellentuer zu oeffnen."
1210 PRINT:PRINT"Aber Vorsicht! Du hast nur eine begrenzte Anzahl an Versuchen.":PRINT
1211 PEN 2
1212 PRINT" Konjugiere affin die Mandelbrotmenge"
1213 PRINT" p(z)=z^2+d zur logistischen Gleichung"
1214 PRINT" f(z)=c*z*(1-z) mittels h(z)=v*z+w, so"
1215 PRINT" dass h(p(z))=f(h(z))."
1216 PEN 1:PRINT
1217 PRINT"  (0) v=1/c,w=1/2,d=(2*c+c^2)/4"
1218 PRINT"  (1) v=1/c,w=2,d=(2*c+c^2)/5"
1219 PRINT"  (2) v=-1/c,w=1/2,d=-(c^2-2*c)/4"
1220 PRINT"  (3) v=sqrt(1/c),w=-1/2,d=-(c^2-2*c)/4"
1221 IF hex%>0 THEN PRINT"Das Orakel sagt: '2'"
1222 cellc%=0:FOR cellloop%=2 TO 1 STEP -1
1223 PRINT:PRINT"Deine Antwort (";cellloop%;"Versuche noch) ";:INPUT"> ",cellans%
1224 IF cellans%=2 THEN cellloop%=0:cellc%=1
1225 NEXT
1226 IF cellc%<=0 THEN PRINT:PRINT"Ein Alarm geht los. Du wirst nun":PRINT"zurueck zum Spielstart teleportiert,":PRINT"aber behaeltst Dein Wissen.":INPUT"[bitte ENTER druecken]",waitkey$:GOTO 5000
1227 CLS:PRINT dash$:PRINT"Glueckwunsch!":PRINT dash$:PRINT"Du hast Deine Aufgabe erfolgreich"
1228 PRINT"geloest! Benoit Mandelbrot ist wieder":PRINT"frei, und die Mathematik gerettet!":PRINT:END
1300 comp%=4:room%=3:perc%=c04perc%:hc%=0:mult!=0.97926:GOSUB 50000
1301 doors$="0021":GOSUB 50100
1302 PRINT dash$:PRINT"Du siehst:":PRINT
1303 GOSUB 50200
1304 IF ve%=7 AND ob%=11 THEN pinc%=1:GOSUB 52800:IF pinout%>0 THEN c04perc%=1:GOTO 1700 ELSE GOTO 1300
1305 IF ve%=7 AND ob%=12 THEN GOTO 1400
1306 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1300
1400 comp%=4:room%=4:perc%=c04perc%:hc%=0:mult!=0.75237:GOSUB 50000
1401 doors$="1110":GOSUB 50100
1402 PRINT dash$:PRINT"Du siehst:":PRINT
1403 GOSUB 50200
1404 IF ve%=7 AND ob%=9 THEN GOTO 1500
1405 IF ve%=7 AND ob%=10 THEN GOTO 1100
1406 IF ve%=7 AND ob%=11 THEN GOTO 1300
1407 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1400
1500 comp%=4:room%=5:perc%=c04perc%:hc%=0:mult!=0.84248:GOSUB 50000
1501 doors$="0101":GOSUB 50100
1502 PRINT dash$:PRINT"Du siehst:":PRINT
1503 GOSUB 50200
1504 IF ve%=7 AND ob%=10 THEN GOTO 1400
1505 IF ve%=7 AND ob%=12 THEN GOTO 1600
1506 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1500
1600 comp%=4:room%=6:perc%=c04perc%:hc%=0:mult!=0.9584:GOSUB 50000
1601 doors$="0010":GOSUB 50100
1602 PRINT dash$:PRINT"Du siehst:":PRINT
1603 GOSUB 50200
1604 IF ve%=7 AND ob%=11 THEN GOTO 1500
1605 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1600
1700 comp%=6:room%=0:perc%=c06perc%:hc%=0:mult!=0.92797:GOSUB 50000
1701 doors$="1002":GOSUB 50100
1702 PRINT dash$:PRINT"Du siehst:":PRINT
1703 IF ncl0600%>0 THEN PRINT"* eine verschlossene Kiste":GOTO 1707
1704 PRINT"* eine Kiste mit einer Notiz:":PEN 2
1705 PRINT" Die aktuelle Periode ist 5."
1706 PEN 1
1707 :
1708 GOSUB 50200
1709 IF ve%=7 AND ob%=9 THEN GOTO 1900
1710 IF ve%=7 AND ob%=12 THEN pinc%=5:GOSUB 52800:IF pinout%>0 THEN c06perc%=5:GOTO 1300 ELSE GOTO 1700
1711 IF ncl0600%>0 AND ve%=3 AND ob%=2 THEN GOTO 1713
1712 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1700
1713 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"die Kiste zu oeffnen.":PRINT
1714 PEN 2
1715 PRINT" Der Akkumulationspunkt der"
1716 PRINT" klassischen Periodenverdopplung auf"
1717 PRINT" der reellen Achse liegt in"
1718 PEN 1:PRINT
1719 PRINT"  (0) [-1.437 .. -1.436]"
1720 PRINT"  (1) [-1.423 .. -1.422]"
1721 PRINT"  (2) {-1.402 .. -1.401]"
1722 PRINT"  (3) [-1.401 .. -1.400]"
1723 PRINT:IF hex%>0 THEN PRINT"Das Orakel sagt: 2":PRINT
1724 INPUT"Deine Antwort > ",nicans%
1725 IF nicans%=2 THEN ncl0600%=0 ELSE PRINT"Falsch.":GOSUB 52700
1726 GOTO 1700
1800 comp%=6:room%=1:perc%=c06perc%:hc%=0:mult!=0.16636:GOSUB 50000
1801 doors$="1001":GOSUB 50100
1802 PRINT dash$:PRINT"Du siehst:":PRINT
1803 GOSUB 50200
1804 IF ve%=7 AND ob%=9 THEN GOTO 2200
1805 IF ve%=7 AND ob%=12 THEN GOTO 1900
1806 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1800
1900 comp%=6:room%=2:perc%=c06perc%:hc%=0:mult!=0.42176:GOSUB 50000
1901 doors$="0110":GOSUB 50100
1902 PRINT dash$:PRINT"Du siehst:":PRINT
1903 IF nbh0602%>0 THEN PRINT"* ein Spiegel, an einer Ecke aufgehaengt":GOTO 1910
1904 IF nbh0602%<=0 AND nba0602%<=0 THEN PRINT"* eine Notiz hinter dem Spiegel":GOTO 1910
1905 PRINT"* eine Notiz hinter dem Spiegel:":PEN 2
1906 PRINT" Der Manhattan-Abstand dieses Raumes"
1907 PRINT" zum Zentrum des Hauptkardioids is"
1908 PRINT" ungefaehr 1.0321"
1909 PEN 1
1910 :
1911 GOSUB 50200
1912 IF ve%=7 AND ob%=10 THEN GOTO 1700
1913 IF ve%=7 AND ob%=11 THEN GOTO 1800
1914 IF nbh0602%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba0602%=1:GOTO 1900
1915 IF nbh0602%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh0602%=0:GOTO 1900
1916 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 1900
2000 comp%=6:room%=3:perc%=c06perc%:hc%=0:mult!=0.90907:GOSUB 50000
2001 doors$="0021":GOSUB 50100
2002 PRINT dash$:PRINT"Du siehst:":PRINT
2003 IF ncl0603%>0 THEN PRINT"* eine verschlossene Kiste":GOTO 2009
2004 PRINT"* eine Kiste mit einer Notiz:":PEN 2
2005 PRINT" Der euklidische Abstand dieses"
2006 PRINT" Raumes zum Zentrum des"
2007 PRINT" Hauptkardioids is ungefaehr 0.7789"
2008 PEN 1
2009 :
2010 GOSUB 50200
2011 IF ve%=7 AND ob%=11 THEN pinc%=5:GOSUB 52800:IF pinout%>0 THEN c06perc%=5:GOTO 3200 ELSE GOTO 2000
2012 IF ve%=7 AND ob%=12 THEN GOTO 2100
2013 IF ncl0603%>0 AND ve%=3 AND ob%=2 THEN GOTO 2015
2014 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2000
2015 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"die Kiste zu oeffnen.":PRINT
2016 PRINT:PEN 2
2017 PRINT" Wieviele Petals hat die Julia-Menge"
2018 PRINT" zu"
2019 PRINT" z^2+(-0.22252093395631458717-0.974927"
2020 PRINT" 91218182361934*i)*z"
2021 PEN 1:PRINT
2022 IF hex%>0 THEN PRINT"Das Orakel sagt: 7":PRINT
2023 INPUT"Deine Antwort > ",nicans$
2024 IF nicans$="7" THEN ncl0603%=0 ELSE PRINT"Falsch.":GOSUB 52700
2025 GOTO 2000
2100 comp%=6:room%=4:perc%=c06perc%:hc%=0:mult!=0.45868:GOSUB 50000
2101 doors$="0011":GOSUB 50100
2102 PRINT dash$:PRINT"Du siehst:":PRINT
2103 GOSUB 50200
2104 IF ve%=7 AND ob%=11 THEN GOTO 2000
2105 IF ve%=7 AND ob%=12 THEN GOTO 2200
2106 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2100
2200 comp%=6:room%=5:perc%=c06perc%:hc%=1:mult!=0.012029:GOSUB 50000
2201 doors$="1111":GOSUB 50100
2202 PRINT dash$:PRINT"Du siehst:":PRINT
2203 IF nfa0605%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 2210
2204 PRINT"* eine Notiz:":PEN 2
2205 PRINT" Der euklidische Abstand der reellen"
2206 PRINT" Koordinate dieses Raumes zum"
2207 PRINT" Zentrum des noerdlichen"
2208 PRINT" Period-3-Bulbs ist ungefaehr 0.3851"
2209 PEN 1
2210 :
2211 GOSUB 50200
2212 IF ve%=7 AND ob%=9 THEN GOTO 2400
2213 IF ve%=7 AND ob%=10 THEN GOTO 1800
2214 IF ve%=7 AND ob%=11 THEN GOTO 2100
2215 IF ve%=7 AND ob%=12 THEN GOTO 2300
2216 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0605%=1:GOTO 2200
2217 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2200
2300 comp%=6:room%=6:perc%=c06perc%:hc%=0:mult!=0.14003:GOSUB 50000
2301 doors$="1010":GOSUB 50100
2302 PRINT dash$:PRINT"Du siehst:":PRINT
2303 GOSUB 50200
2304 IF ve%=7 AND ob%=9 THEN GOTO 2600
2305 IF ve%=7 AND ob%=11 THEN GOTO 2200
2306 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2300
2400 comp%=6:room%=7:perc%=c06perc%:hc%=0:mult!=0.26844:GOSUB 50000
2401 doors$="0101":GOSUB 50100
2402 PRINT dash$:PRINT"Du siehst:":PRINT
2403 IF nfa0607%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 2408
2404 PRINT"* eine Notiz:":PEN 2
2405 PRINT" Die aktuelle Periode ist eine"
2406 PRINT" Primzahl."
2407 PEN 1
2408 :
2409 GOSUB 50200
2410 IF ve%=7 AND ob%=10 THEN GOTO 2200
2411 IF ve%=7 AND ob%=12 THEN GOTO 2500
2412 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0607%=1:GOTO 2400
2413 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2400
2500 comp%=6:room%=8:perc%=c06perc%:hc%=0:mult!=0.31206:GOSUB 50000
2501 doors$="0010":GOSUB 50100
2502 PRINT dash$:PRINT"Du siehst:":PRINT
2503 GOSUB 50200
2504 IF ve%=7 AND ob%=11 THEN GOTO 2400
2505 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2500
2600 comp%=6:room%=9:perc%=c06perc%:hc%=0:mult!=0.91578:GOSUB 50000
2601 doors$="0100":GOSUB 50100
2602 PRINT dash$:PRINT"Du siehst:":PRINT
2603 IF nfa0609%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 2609
2604 PRINT"* eine Notiz:":PEN 2
2605 PRINT" Der euklidische Abstand dieses"
2606 PRINT" Raumes zum Zentrum des"
2607 PRINT" Hauptkardioid is ungefaehr 0.7712"
2608 PEN 1
2609 :
2610 GOSUB 50200
2611 IF ve%=7 AND ob%=10 THEN GOTO 2300
2612 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0609%=1:GOTO 2600
2613 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2600
2700 comp%=7:room%=0:perc%=c07perc%:hc%=0:mult!=0.065867:GOSUB 50000
2701 doors$="1001":GOSUB 50100
2702 PRINT dash$:PRINT"Du siehst:":PRINT
2703 IF nbh0700%>0 THEN PRINT"* ein Spiegel, an einer Ecke aufgehaengt":GOTO 2709
2704 IF nbh0700%<=0 AND nba0700%<=0 THEN PRINT"* eine Notiz hinter dem Spiegel":GOTO 2709
2705 PRINT"* eine Notiz hinter dem Spiegel:":PEN 2
2706 PRINT" Die Komponente hat nur genau eine"
2707 PRINT" parabolische Tuer."
2708 PEN 1
2709 :
2710 GOSUB 50200
2711 IF ve%=7 AND ob%=9 THEN GOTO 2900
2712 IF ve%=7 AND ob%=12 THEN GOTO 2800
2713 IF nbh0700%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba0700%=1:GOTO 2700
2714 IF nbh0700%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh0700%=0:GOTO 2700
2715 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2700
2800 comp%=7:room%=1:perc%=c07perc%:hc%=0:mult!=0.27556:GOSUB 50000
2801 doors$="1010":GOSUB 50100
2802 PRINT dash$:PRINT"Du siehst:":PRINT
2803 IF ncl0701%>0 THEN PRINT"* eine verschlossene Kiste":GOTO 2807
2804 PRINT"* eine Kiste mit einer Notiz:":PEN 2
2805 PRINT" Die aktuelle Periode ist 15."
2806 PEN 1
2807 :
2808 GOSUB 50200
2809 IF ve%=7 AND ob%=9 THEN GOTO 3100
2810 IF ve%=7 AND ob%=11 THEN GOTO 2700
2811 IF ncl0701%>0 AND ve%=3 AND ob%=2 THEN GOTO 2813
2812 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2800
2813 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"die Kiste zu oeffnen.":PRINT
2814 PEN 2
2815 PRINT" Wann erschien Mandelbrots erste"
2816 PRINT" Veroeffentlichung ueber die nach ihm"
2817 PRINT" benannte Menge?"
2818 PEN 1:PRINT
2819 PRINT"  (0) 1976"
2820 PRINT"  (1) 1980"
2821 PRINT"  (2) 1986"
2822 PRINT"  (3) 1990"
2823 PRINT:IF hex%>0 THEN PRINT"Das Orakel sagt: 1":PRINT
2824 INPUT"Deine Antwort > ",nicans%
2825 IF nicans%=1 THEN ncl0701%=0 ELSE PRINT"Falsch.":GOSUB 52700
2826 GOTO 2800
2900 comp%=7:room%=2:perc%=c07perc%:hc%=1:mult!=0.0046402:GOSUB 50000
2901 doors$="1100":GOSUB 50100
2902 PRINT dash$:PRINT"Du siehst:":PRINT
2903 PRINT"* ein aktiver Transmitter"
2904 GOSUB 50200
2905 IF ve%=7 AND ob%=9 THEN GOTO 3000
2906 IF ve%=7 AND ob%=10 THEN GOTO 2700
2907 IF ve%=5 AND ob%=5 THEN GOTO 4100
2908 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 2900
3000 comp%=7:room%=3:perc%=c07perc%:hc%=0:mult!=0.0051678:GOSUB 50000
3001 doors$="0101":GOSUB 50100
3002 PRINT dash$:PRINT"Du siehst:":PRINT
3003 GOSUB 50200
3004 IF ve%=7 AND ob%=10 THEN GOTO 2900
3005 IF ve%=7 AND ob%=12 THEN GOTO 3100
3006 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3000
3100 comp%=7:room%=4:perc%=c07perc%:hc%=0:mult!=0.20437:GOSUB 50000
3101 doors$="1111":GOSUB 50100
3102 PRINT dash$:PRINT"Du siehst:":PRINT
3103 GOSUB 50200
3104 IF ve%=7 AND ob%=9 THEN GOTO 3300
3105 IF ve%=7 AND ob%=10 THEN GOTO 2800
3106 IF ve%=7 AND ob%=11 THEN GOTO 3000
3107 IF ve%=7 AND ob%=12 THEN GOTO 3200
3108 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3100
3200 comp%=7:room%=5:perc%=c07perc%:hc%=0:mult!=0.92438:GOSUB 50000
3201 doors$="0012":GOSUB 50100
3202 PRINT dash$:PRINT"Du siehst:":PRINT
3203 GOSUB 50200
3204 IF ve%=7 AND ob%=11 THEN GOTO 3100
3205 IF ve%=7 AND ob%=12 THEN pinc%=15:GOSUB 52800:IF pinout%>0 THEN c07perc%=15:GOTO 2000 ELSE GOTO 3200
3206 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3200
3300 comp%=7:room%=6:perc%=c07perc%:hc%=0:mult!=0.39744:GOSUB 50000
3301 doors$="0100":GOSUB 50100
3302 PRINT dash$:PRINT"Du siehst:":PRINT
3303 IF nfa0706%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 3308
3304 PRINT"* eine Notiz:":PEN 2
3305 PRINT" die Ziffer '1', die durchgestrichen"
3306 PRINT" ist"
3307 PEN 1
3308 :
3309 GOSUB 50200
3310 IF ve%=7 AND ob%=10 THEN GOTO 3100
3311 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0706%=1:GOTO 3300
3312 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3300
3400 comp%=8:room%=0:perc%=c08perc%:hc%=0:mult!=0.95037:GOSUB 50000
3401 doors$="1000":GOSUB 50100
3402 PRINT dash$:PRINT"Du siehst:":PRINT
3403 GOSUB 50200
3404 IF ve%=7 AND ob%=9 THEN GOTO 3500
3405 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3400
3500 comp%=8:room%=1:perc%=c08perc%:hc%=0:mult!=0.31411:GOSUB 50000
3501 doors$="0101":GOSUB 50100
3502 PRINT dash$:PRINT"Du siehst:":PRINT
3503 IF ncl0801%>0 THEN PRINT"* eine verschlossene Kiste":GOTO 3508
3504 PRINT"* eine Kiste mit einer Notiz:":PEN 2
3505 PRINT" Diese Komponente hat exakt eine"
3506 PRINT" parabolische Tuer."
3507 PEN 1
3508 :
3509 GOSUB 50200
3510 IF ve%=7 AND ob%=10 THEN GOTO 3400
3511 IF ve%=7 AND ob%=12 THEN GOTO 3600
3512 IF ncl0801%>0 AND ve%=3 AND ob%=2 THEN GOTO 3514
3513 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3500
3514 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"die Kiste zu oeffnen.":PRINT
3515 PRINT:PEN 2
3516 PRINT" Wieviele Cardioide besitzen die"
3517 PRINT" Perioden 1-5 insgesamt?"
3518 PEN 1:PRINT
3519 IF hex%>0 THEN PRINT"Das Orakel sagt: 15":PRINT
3520 INPUT"Deine Antwort > ",nicans$
3521 IF nicans$="15" THEN ncl0801%=0 ELSE PRINT"Falsch.":GOSUB 52700
3522 GOTO 3500
3600 comp%=8:room%=2:perc%=c08perc%:hc%=0:mult!=0.093982:GOSUB 50000
3601 doors$="1010":GOSUB 50100
3602 PRINT dash$:PRINT"Du siehst:":PRINT
3603 GOSUB 50200
3604 IF ve%=7 AND ob%=9 THEN GOTO 4000
3605 IF ve%=7 AND ob%=11 THEN GOTO 3500
3606 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3600
3700 comp%=8:room%=3:perc%=c08perc%:hc%=0:mult!=0.90663:GOSUB 50000
3701 doors$="0021":GOSUB 50100
3702 PRINT dash$:PRINT"Du siehst:":PRINT
3703 GOSUB 50200
3704 IF ve%=7 AND ob%=11 THEN pinc%=15:GOSUB 52800:IF pinout%>0 THEN c08perc%=15:GOTO 4700 ELSE GOTO 3700
3705 IF ve%=7 AND ob%=12 THEN GOTO 3800
3706 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3700
3800 comp%=8:room%=4:perc%=c08perc%:hc%=0:mult!=0.10566:GOSUB 50000
3801 doors$="1010":GOSUB 50100
3802 PRINT dash$:PRINT"Du siehst:":PRINT
3803 GOSUB 50200
3804 IF ve%=7 AND ob%=9 THEN GOTO 3900
3805 IF ve%=7 AND ob%=11 THEN GOTO 3700
3806 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3800
3900 comp%=8:room%=5:perc%=c08perc%:hc%=0:mult!=0.070789:GOSUB 50000
3901 doors$="0101":GOSUB 50100
3902 PRINT dash$:PRINT"Du siehst:":PRINT
3903 GOSUB 50200
3904 IF ve%=7 AND ob%=10 THEN GOTO 3800
3905 IF ve%=7 AND ob%=12 THEN GOTO 4000
3906 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 3900
4000 comp%=8:room%=6:perc%=c08perc%:hc%=0:mult!=0.004486:GOSUB 50000
4001 doors$="0111":GOSUB 50100
4002 PRINT dash$:PRINT"Du siehst:":PRINT
4003 IF nfa0806%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 4009
4004 PRINT"* eine Notiz:":PEN 2
4005 PRINT" Diese Komponente liegt vollstaendig"
4006 PRINT" in der positiv-imaginaeren"
4007 PRINT" komplexen Ebenenhaelfte."
4008 PEN 1
4009 :
4010 GOSUB 50200
4011 IF ve%=7 AND ob%=10 THEN GOTO 3600
4012 IF ve%=7 AND ob%=11 THEN GOTO 3900
4013 IF ve%=7 AND ob%=12 THEN GOTO 4100
4014 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0806%=1:GOTO 4000
4015 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4000
4100 comp%=8:room%=7:perc%=c08perc%:hc%=1:mult!=0.0065632:GOSUB 50000
4101 doors$="0010":GOSUB 50100
4102 PRINT dash$:PRINT"Du siehst:":PRINT
4103 PRINT"* ein aktiver Transmitter"
4104 GOSUB 50200
4105 IF ve%=7 AND ob%=11 THEN GOTO 4000
4106 IF ve%=5 AND ob%=5 THEN GOTO 2700
4107 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4100
4200 comp%=9:room%=0:perc%=c09perc%:hc%=0:mult!=0.15309:GOSUB 50000
4201 doors$="1000":GOSUB 50100
4202 PRINT dash$:PRINT"Du siehst:":PRINT
4203 IF ncl0900%>0 THEN PRINT"* eine verschlossene Kiste":GOTO 4207
4204 PRINT"* eine Kiste mit einer Notiz:":PEN 2
4205 PRINT" Die aktuelle Periode ist 105."
4206 PEN 1
4207 :
4208 GOSUB 50200
4209 IF ve%=7 AND ob%=9 THEN GOTO 4500
4210 IF ncl0900%>0 AND ve%=3 AND ob%=2 THEN GOTO 4212
4211 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4200
4212 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"die Kiste zu oeffnen.":PRINT
4213 PRINT:PEN 2
4214 PRINT" Welches ist die kleinste Periode p,"
4215 PRINT" die 1 Million oder mehr hyperbolische"
4216 PRINT" Komponenten mit genau dieser"
4217 PRINT" Periodizitaet aufweist?"
4218 PEN 1:PRINT
4219 IF hex%>0 THEN PRINT"Das Orakel sagt: 21":PRINT
4220 INPUT"Deine Antwort > ",nicans$
4221 IF nicans$="21" THEN ncl0900%=0 ELSE PRINT"Falsch.":GOSUB 52700
4222 GOTO 4200
4300 comp%=9:room%=1:perc%=c09perc%:hc%=0:mult!=0.31494:GOSUB 50000
4301 doors$="1001":GOSUB 50100
4302 PRINT dash$:PRINT"Du siehst:":PRINT
4303 IF nfa0901%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 4310
4304 PRINT"* eine Notiz:":PEN 2
4305 PRINT" Die beiden hoechstwertigsten"
4306 PRINT" Ziffern der Periode sind durch die"
4307 PRINT" Buchstaben 'J' auf einfache Art"
4308 PRINT" kodiert."
4309 PEN 1
4310 :
4311 GOSUB 50200
4312 IF ve%=7 AND ob%=9 THEN GOTO 4800
4313 IF ve%=7 AND ob%=12 THEN GOTO 4400
4314 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0901%=1:GOTO 4300
4315 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4300
4400 comp%=9:room%=2:perc%=c09perc%:hc%=1:mult!=0.0039899:GOSUB 50000
4401 doors$="0011":GOSUB 50100
4402 PRINT dash$:PRINT"Du siehst:":PRINT
4403 IF duh0902%>0 THEN PRINT"* ein Teppisch mit umgelegter Ecke":GOTO 4406
4404 IF duh0902%<=0 AND dup0902%<=0 THEN PRINT"* nur ein einfacher Teppisch":GOTO 4406
4405 PRINT"* ein elektronisches Bauteil markiert '3'"
4406 :
4407 GOSUB 50200
4408 IF ve%=7 AND ob%=11 THEN GOTO 4300
4409 IF ve%=7 AND ob%=12 THEN GOTO 4500
4410 IF duh0902%>0 AND ve%=2 AND (pp%=1 OR pp%=3) AND ob%=7 THEN duh0902%=0:GOTO 4400
4411 IF duh0902%<=0 AND dup0902%>0 AND ve%=6 AND ob%=4 THEN IF parts%(3)>0 THEN PRINT"You already carry this part.":GOSUB 52700:GOTO 4400 ELSE parts%(3)=1:dup0902%=0:heromdet%=heromdet%+1:GOTO 4400
4412 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4400
4500 comp%=9:room%=3:perc%=c09perc%:hc%=0:mult!=0.11574:GOSUB 50000
4501 doors$="1110":GOSUB 50100
4502 PRINT dash$:PRINT"Du siehst:":PRINT
4503 IF nbh0903%>0 THEN PRINT"* ein Spiegel, an einer Ecke aufgehaengt":GOTO 4510
4504 IF nbh0903%<=0 AND nba0903%<=0 THEN PRINT"* eine Notiz hinter dem Spiegel":GOTO 4510
4505 PRINT"* eine Notiz hinter dem Spiegel:":PEN 2
4506 PRINT" Die niedrigstwertige Stelle ist"
4507 PRINT" kodiert in einer einfachen"
4508 PRINT" Verschluesselung als Buchstabe 'E'."
4509 PEN 1
4510 :
4511 GOSUB 50200
4512 IF ve%=7 AND ob%=9 THEN GOTO 4600
4513 IF ve%=7 AND ob%=10 THEN GOTO 4200
4514 IF ve%=7 AND ob%=11 THEN GOTO 4400
4515 IF nbh0903%<=0 AND((ve%=1 AND ob%=1)OR(ve%=2 AND pp%=1 AND ob%=1)) THEN nba0903%=1:GOTO 4500
4516 IF nbh0903%>0 AND(ve%=2 AND (pp%=2 OR pp%=1) AND ob%=8) THEN nbh0903%=0:GOTO 4500
4517 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4500
4600 comp%=9:room%=4:perc%=c09perc%:hc%=0:mult!=0.16999:GOSUB 50000
4601 doors$="0101":GOSUB 50100
4602 PRINT dash$:PRINT"Du siehst:":PRINT
4603 GOSUB 50200
4604 IF ve%=7 AND ob%=10 THEN GOTO 4500
4605 IF ve%=7 AND ob%=12 THEN GOTO 4700
4606 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4600
4700 comp%=9:room%=5:perc%=c09perc%:hc%=0:mult!=0.82915:GOSUB 50000
4701 doors$="0012":GOSUB 50100
4702 PRINT dash$:PRINT"Du siehst:":PRINT
4703 GOSUB 50200
4704 IF ve%=7 AND ob%=11 THEN GOTO 4600
4705 IF ve%=7 AND ob%=12 THEN pinc%=105:GOSUB 52800:IF pinout%>0 THEN c09perc%=105:GOTO 3700 ELSE GOTO 4700
4706 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4700
4800 comp%=9:room%=6:perc%=c09perc%:hc%=0:mult!=0.56857:GOSUB 50000
4801 doors$="1101":GOSUB 50100
4802 PRINT dash$:PRINT"Du siehst:":PRINT
4803 IF nfa0906%<=0 THEN PRINT"* eine Notiz auf dem Boden":GOTO 4807
4804 PRINT"* eine Notiz:":PEN 2
4805 PRINT" Die aktuelle Periode ist 3-stellig."
4806 PEN 1
4807 :
4808 GOSUB 50200
4809 IF ve%=7 AND ob%=9 THEN GOTO 5000
4810 IF ve%=7 AND ob%=10 THEN GOTO 4300
4811 IF ve%=7 AND ob%=12 THEN GOTO 4900
4812 IF (ve%=1 AND ob%=1) OR (ve%=2 AND pp%=1 AND ob%=1) THEN nfa0906%=1:GOTO 4800
4813 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4800
4900 comp%=9:room%=7:perc%=c09perc%:hc%=0:mult!=0.47288:GOSUB 50000
4901 doors$="1010":GOSUB 50100
4902 PRINT dash$:PRINT"Du siehst:":PRINT
4903 GOSUB 50200
4904 IF ve%=7 AND ob%=9 THEN GOTO 5100
4905 IF ve%=7 AND ob%=11 THEN GOTO 4800
4906 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 4900
5000 comp%=9:room%=8:perc%=c09perc%:hc%=0:mult!=0.67785:GOSUB 50000
5001 doors$="0101":GOSUB 50100
5002 PRINT dash$:PRINT"Du siehst:":PRINT
5003 IF dcl0908%>0 THEN PRINT"* eine verschlossene Kiste":GOTO 5008
5004 IF dcl0908%<=0 AND dcp0908%<=0 THEN PRINT"* eine offene aber leere Kiste":GOTO 5008
5005 PRINT"* die Kiste enthaelt:"
5006 PRINT" ein elektronisches Bauteil markiert"
5007 PRINT" '1'"
5008 :
5009 GOSUB 50200
5010 IF ve%=7 AND ob%=10 THEN GOTO 4800
5011 IF ve%=7 AND ob%=12 THEN GOTO 5100
5012 IF dcl0908%>0 AND ve%=3 AND ob%=2 THEN GOTO 5015
5013 IF dcl0908%<=0 AND dcp0908%>0 AND ve%=6 AND ob%=4 THEN IF parts%(1)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 5000 ELSE parts%(1)=1:heromdet%=heromdet%+1:dcp0908%=0:GOTO 5000
5014 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 5000
5015 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"die Kiste zu oeffnen.":PRINT
5016 PEN 2
5017 PRINT" Wo hat Benoit Mandelbrat viele Jahre"
5018 PRINT" gearbeitet?"
5019 PEN 1:PRINT
5020 PRINT"  (0) International Business Machines Corporation"
5021 PRINT"  (1) Advanced Micro Devices"
5022 PRINT"  (2) Federal Reserve Bank"
5023 PRINT"  (3) Dornier"
5024 PRINT:IF hex%>0 THEN PRINT"Das Orakel sagt: 0":PRINT
5025 INPUT"Deine Antwort > ",dicans%
5026 IF dicans%=0 THEN dcl0908%=0 ELSE PRINT"Falsch.":GOSUB 52700
5027 GOTO 5000
5100 comp%=9:room%=9:perc%=c09perc%:hc%=0:mult!=0.58353:GOSUB 50000
5101 doors$="0110":GOSUB 50100
5102 PRINT dash$:PRINT"Du siehst:":PRINT
5103 IF dcl0909%>0 THEN PRINT"* eine verschlossene Kiste":GOTO 5108
5104 IF dcl0909%<=0 AND dcp0909%<=0 THEN PRINT"* eine offene aber leere Kiste":GOTO 5108
5105 PRINT"* die Kiste enthaelt:"
5106 PRINT" ein elektronisches Bauteil markiert"
5107 PRINT" '2'"
5108 :
5109 GOSUB 50200
5110 IF ve%=7 AND ob%=10 THEN GOTO 4900
5111 IF ve%=7 AND ob%=11 THEN GOTO 5000
5112 IF dcl0909%>0 AND ve%=3 AND ob%=2 THEN GOTO 5115
5113 IF dcl0909%<=0 AND dcp0909%>0 AND ve%=6 AND ob%=4 THEN IF parts%(2)>0 THEN PRINT"You already have this part.":GOSUB 52700:GOTO 5100 ELSE parts%(2)=1:heromdet%=heromdet%+1:dcp0909%=0:GOTO 5100
5114 PRINT"Befehl nicht applikabel.":GOSUB 52700:GOTO 5100
5115 CLS:PRINT dash$:PRINT"Du musst eine Frage beantworten, um":PRINT"die Kiste zu oeffnen.":PRINT
5116 PEN 2
5117 PRINT" Die c-Parameter-Menge fuer z^d+c hat"
5118 PRINT" als Limit fuer d->inf welches"
5119 PRINT" mathematische Objekt?"
5120 PEN 1:PRINT
5121 PRINT"  (0) {c | c in C, ||Re(c)|| < 1 and ||Im(c)|| <= 1}"
5122 PRINT"  (1) {c | c in C, ||c+3/4|| <= 1}"
5123 PRINT"  (2) {c | c in C, ||c|| < 1}"
5124 PRINT"  (3) {c | c in C, ||c|| <= 1}"
5125 PRINT:IF hex%>0 THEN PRINT"Das Orakel sagt: 3":PRINT
5126 INPUT"Deine Antwort > ",dicans%
5127 IF dicans%=3 THEN dcl0909%=0 ELSE PRINT"Falsch.":GOSUB 52700
5128 GOTO 5100
5229 MODE 1:CLS
5230 direction$="NSWO":DIM param$(4):INK 2,26
5231 heromdet%=0:DIM parts%(3):parts%(1)=0:parts%(2)=0:parts%(3)=0:hex%=0:dash$="---------------------------------------"
5232 c04perc%=0:nfa0400%=0:c06perc%=0:ncl0600%=1:nba0602%=0:nbh0602%=1:ncl0603%=1:nfa0605%=0:nfa0607%=0:nfa0609%=0:c07perc%=0:nba0700%=0:nbh0700%=1:ncl0701%=1:nfa0706%=0
5233 c08perc%=0:ncl0801%=1:nfa0806%=0:c09perc%=0:ncl0900%=1:nfa0901%=0:duh0902%=1:dup0902%=3:nba0903%=0:nbh0903%=1:nfa0906%=0:dcl0908%=1:dcp0908%=1:dcl0909%=1:dcp0909%=2
5234 GOTO 5000
50000 CLS:LOCATE 1,1:PRINT dash$:PRINT"Raum ";room%;" Komponente ";comp%;
50001 IF perc%>0 THEN PRINT"Periode ";perc%;
50002 IF hc%>0 THEN PRINT"hyperb. Zentrum" ELSE PRINT
50003 IF heromdet%>=3 THEN PRINT"Multiplier=";mult!
50004 PRINT dash$:IF heromdet%>0 AND heromdet%<3 THEN PRINT"Multiplier-Detektor ";heromdet%;"/3 fertig."
50005 RETURN
50100 PRINT:PRINT"Tueren:  ";:FOR printdoors%=1 TO 4:printdoorstmp%=ASC(MID$(doors$,printdoors%,1))-48
50101 IF printdoorstmp%=1 THEN PRINT MID$(direction$,printdoors%,1);" "; ELSE IF printdoorstmp%=2 THEN PRINT MID$(direction$,printdoors%,1);" parabolisch verschlossen  ";
50102 NEXT:PRINT:RETURN
50200 PRINT dash$:INPUT"Taylor> ",paramin$:GOSUB 51200
50201 IF paranz%=1 AND LEN(param$(1))=1 THEN paranz%=2:param$(2)=param$(1):param$(1)="GEHE"
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
52400 DATA LESE,1,LIES,1,SCHA,2,BETR,2,OEFF,3
52401 DATA BEFR,4,RETT,4,NUTZ,5,BENU,5,NIMM,6
52402 DATA "GEH",7,"GEHE",7,"ENDE",8
52403 DATA "EXIT",8,"QUIT",8,ABRA,9,"/",-1
52500 DATA "AUF",1,HINT,2,UNTE,3,"/",-1
52600 DATA NOTI,1,BOX,2,KIST,2,ZELL,3,BENO,6
52601 DATA MAND,6,TEIL,4,BAUT,4,TRAN,5,TEPP,7
52602 DATA ZETT,1,SPIE,8,NORD,9,N,9
52603 DATA SUED,10,S,10,WEST,11,W,11
52604 DATA OST,12,O,12,OSTE,12,"/",-1
52700 FOR waitloop%=1 TO 2100:NEXT:RETURN
52800 IF hex%>0 THEN PRINT:PRINT"Das Orakel sagt: ";pinc%:PRINT
52801 INPUT"Gib PIN ein: ",pintmp%:IF pintmp%=pinc% THEN pinout%=1 ELSE pinout%=0:PRINT"Falsch.":GOSUB 52700
52802 RETURN
