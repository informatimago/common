1 ****************************************************************
2 ****************************************************************
3 IDENTIFICATION DIVISION.
4 PROGRAM-ID. SBCRIB.
5 AUTHOR. BOULARD.
6 *******************************************************
7 * *
8 * LE MODULE SBCRIB PERMET DE VERIFIER LA *
9 * VALIDITE D'UN R.I.B *
lu * *
11 * SYNTAXE : CALL "SBCRIB" USING RFCT RENT RSOR. *
12 * (COPY CYWRIB EN WSS DU PROGR) *
13 * *
14 *******************************************************
15 ENVIRONMENT DIVISION.
16 CONFIGURATION SECTION.
17 SOURCE-COMPUTER. LEVEL-64.
18 OBJECT-COMPUTER. LEVEL-64.
19 /
20 INPUT-OUTPUT SECTION.
21 FILE-CONTROL.
22 COPY SELECT-PMGCBANQ.
23 DATA DIVISION.
24 FILE SECTION.
25 COPY FD-PMGCBANQ .
26 WORKING-STORAGE SECTION.
27 COPY CYWGCOMMUN .
28 *
29 77 WS-I PIC 9(4) VALUE zERO.
30 77 WS-RESTE PIC 99 VALUE zERO.
31 77 WS-QUOT PIC 9(22) VALUE zERO.
3 2 01 WS -RI B-R.
33 03 WS-COBANQ PIC X ( 5 ) .
34 03 WS-COGUIC PIC X ( 5 ) .
35 03 WS-COMPTE PIC X (11 ) .
3 6 0 3 WS -CLERI B PI C XX .
37 01 WS-RIB REDEFINES WS-RIB-R PIC 9(23).
38 01 WS-RIB-D REDEFINES WS-RIB-R.
39 03 WS-RIB-I PIC X OCCURS 23.
40 01 WS-LETTRE PIC X.
41 88 UN VALUE "A" "J" .
42 88 DEUX VALUE "B" "K" "S".
43 88 TROT S VALUE " C " " L " " T " .
44 88 QUATRE VALUE "D" "U" "M".
45 88 CINQ VALUE "E" "N" "V".
46 88 SIX VALUE "F" "O" "W".
47 88 SEPT VALUE "G" "P" "X".
48 88 HUIT VALUE "H" "Q" "Y".
49 88 NEUF VALUE "I" "R" "z".
50 01WS-DOMICI PIC X(20).
51 /
52 LINKAGE SECTION.
53 ****************** ZONE D,ECHANGE AVEC LES pRoG Es ***************
54 01 RENT.
55 * ZONES OBLIGATOIRES EN ENTREE
56 02 RIBECOBANQ PIC X(5).
57 02 RIBECOGUIC PIC X(5).
58 02 RIBEDOMICI PIC X(24).
59 02 RIBECLERIB PIC 9(02).
60 02 RIBENOCPTE PIC X(11).
61 *
62 01 RSOR.
63 02 RIND PIC X.
64 * ZONE MESSAGE ERREUR
65 *--->1 CES ZONES DOIVENT ETRE NUMERIQUES
66 *--->2 R.I.B. ERRONE
67 *--->3 CODES BANQUE ET GUICHET ERRONES
68 *--->4 CODE DIFFERENT DE zERO
69 *--->5 CODE DIFFERENT D'ESPACE
70 *--->6 ZONE ERRONEE
71 * ZONES RENDUES EN SORTIE
72 02 RIBSCOBANQ PIC X(5).
73 02 RIBSCOGUIC PIC X(5).
74 02 RIBSDOMICI PIC X(24).
75 02 RIBSCLERIB PIC 9(02).
76 02 RIBSNOCPTE PIC X(11).
77 *
78 /
79 PROCEDURE DIVISION USING RENT RSOR.
80 MAIN SECTION.
81 00.
82 MOVE "0" TO RIND.
83
84 PERFORM TEST-RIB.
85
86 99. EXIT PROGRAM.
87 /***RECHERCHE DU RIB *
88 ********************************
89 TEST-RIB SECTION.
90 00.
91 01.
92 * CONTROLES REPRIS DE GCI *
93 ****************************************************************
94 * CONTROLE EXISTANCE CODE BANQUE ET CODE GUICHET *
95 * ACCES A LA TABLE PMGCBANQ *
96 ****************************************************************
97 MOVE RIBECOBANQ TO FGBQ-COBANQ.
98 MOVE RIBECOGUIC TO FGBQ-COGUIC.
1 DISPLAY "FGBQ-COBANQ " FGBQ-COBANQ.
2 DISPLAY "FBGQ-COGUIC " FGBQ-COGUIC.
99 READ PMGCBANQ INVALID KEY
100 DISPLAY " READ PMGCBANQ INVALID "
101 MOVE "3" TO RIND
102 MOVE RIBECOBANQ TO RIBSCOBANQ
103 MOVE RIBECOGUIC TO RIBSCOGUIC
104 GO TO 99.
105 10.
106 DISPLAY " 10 ".
io7 ****************************************************************
108 * REAFFICHAGE DE LA DOMICILIATION *
io9 ****************************************************************
l10 MOVE FGBQ-LIABDO TO WS-DOMICI.
Ill IF WS-DOMICI NOT = RIBEDOMICI
l12 DISPLAY " WS-DOMICI " WS-DOMICI
l13 DISPLAY " RIBEDOMICI " RIBEDOMICI
l14 MOVE WS-DOMICI TO RIBSDOMICI.
ils 15.
l16 DISPLAY " 15 ".
i17 ****************************************************************
l18 * CONTROLE VALIDITE DU RIB *
i19 ****************************************************************
120 EXAMINE RIBENOCPTE REPLACING LEADING SPACES BY zEROES.
121 INITIALIzE WS-RIB-R.
122 MOVE RIBENOCPTE TO WS-COMPTE.
123 MOVE RIBECOBANQ TO WS-COBANQ.
124 MOVE RIBECOGUIC TO WS-COGUIC.
125 MOVE RIBECLERIB TO WS-CLERIB.
126 16.
127 DISPLAY " 16 ".
128 EXAMINE WS-RIB-R REPLACING ALL SPACES BY zEROES.
129 MOVE zERO TO WS-1.
130 17.
131 DISPLAY " 17 TRANSFORMATION ".
132 PERFORM TRANSFORMATION.
133 18.
134 DISPLAY " 18 ".
135 IF WS-RIB-R NOT NUMERIC
136 MOVE "1" TO RIND
137 MOVE WS-COMPTE TO RIBSNOCPTE
138 MOVE WS-COBANQ TO RIBSCOBANQ
139 MOVE WS-COGUIC TO RIBSCOGUIC
140 MOVE WS-CLERIB TO RIBSCLERIB
141 GO TO 99.
142 19.
143 DISPLAY " 19 ".
144 MOVE zERO TO WS-QUOT WS-RESTE.
145 DIVIDE WS-RIB BY 97 GIVING WS-QUOT REMAINDER WS-RESTE.
146 IF WS-RESTE NOT = zERO
147 DISPLAY " WS-RESTE NOT = 0 "
148 MOVE "2" TO RIND
149 MOVE WS-COMPTE TO RIBSNOCPTE
150 MOVE WS-COBANQ TO RIBSCOBANQ
lsl MOVE WS-COGUIC TO RIBSCOGUIC
152 MOVE WS-CLERIB TO RIBSCLERIB
153 GO TO 99.
154 20.
155 DISPLAY " 20 ".
156 MOVE WS-DOMICI TO RIBSDOMICI
157 MOVE WS-COMPTE TO RIBSNOCPTE
158 MOVE WS-COBANQ TO RIBSCOBANQ
159 MOVE WS-COGUIC TO RIBSCOGUIC
160 MOVE WS-CLERIB TO RIBSCLERIB
161
162 99. EXIT.
163 /***TRANSFORMATION *
164 ********************************
165 TRANSFORMATION SECTION.
166 00.
167 DISPLAY " 00 TRANSF".
168 ADD 1 TO WS-1.
169 IF WS-1 > 23
170 GO TO 99.
171 *************************************************************
172 * TRANSFORMATION LETTRE COMPTE EN CHIFFRE *
173 *************************************************************
174 IF WS-RIB-I (WS-I) NUMERIC
175 GO TO 00.
176 MOVE WS-RIB-I (WS-I) TO WS-LETTRE.
177 IF UN MOVE "1" TO WS-RIB-I (WS-1).
178 IF DEUX MOVE "2" TO WS-RIB-I (WS-1).
179 IF TROIS MOVE "3" TO WS-RIB-I (WS-1).
180 IF QUATRE MOVE "4" TO WS-RIB-I (WS-1).
181 IF CINQ MOVE "5" TO WS-RIB-I (WS-1).
182 IF SIX MOVE "6" TO WS-RIB-I (WS-I).
183 IF SEPT MOVE "7" TO WS-RIB-I (WS-1).
184 IF HUIT MOVE "8" TO WS-RIB-I (WS-1).
185 IF NEUF MOVE "9" TO WS-RIB-I (WS-1).
186 GO TO 00.
187 99.
188 EXIT.

