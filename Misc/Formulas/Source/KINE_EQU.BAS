DECLARE SUB df3 ()
DECLARE SUB vff3 ()
DECLARE SUB vof3 ()
DECLARE SUB tf3 ()
DECLARE SUB vff2 ()
DECLARE SUB vof2 ()
DECLARE SUB af2 ()
DECLARE SUB tf2 ()
DECLARE SUB vavef1 ()
DECLARE SUB df1 ()
DECLARE SUB tf1 ()
DECLARE SUB vof5 ()
DECLARE SUB df5 ()
DECLARE SUB af5 ()
DECLARE SUB df4 ()
DECLARE SUB vof4 ()
DECLARE SUB af4 ()
DECLARE SUB vff5 ()
SCREEN 12
COLOR 2
PRINT "ษอออออออออออออออออออออออออออออออออออป"
PRINT "บ ๚๙*The New And Improved!!*๙๚      บ"
PRINT "บ   *K*I*N*E*M*A*T*I*C*             บ"
PRINT "บ          *E*Q*U*A*T*I*O*N*        บ"
PRINT "บ           Program --v6.2--        บ"
PRINT "ฬอออออออออออออออออออออออออออออออออออน"
PRINT "บ              Written              บ"
PRINT "บ                by                 บ"
PRINT "บ              Andrew               บ"
PRINT "บ             Martineau             บ"
PRINT "ศอออออออออออออออออออออออออออออออออออผ"
PRINT ""
PRINT "      --Press Enter to continue--"
INPUT "", nothing
10
COLOR 3
CLS
PRINT "What kinematic formula would you like to use?"
PRINT "1= Vave = d/t"
PRINT "2= Vf = Vo + at"
PRINT "3= d = [(Vf + Vo)/2]t"
PRINT "4= d = Vot + ซatý"
PRINT "5= Vfý = Voý + 2ad"
INPUT equation%
SELECT CASE equation%
    CASE IS >= 5
        CLS
        PRINT "Vfý = Voý + 2ad"
        INPUT "Is 'Vf' your variable? (1=yes, 2=no) ", vfvar5
        IF vfvar5 = 1 THEN
            GOTO 200
        ELSE
            GOTO 20
        END IF
20
        INPUT "is 'Vo' your variable? (1=yes, 2=no) ", vovar5
        IF vovar5 = 1 THEN
            GOTO 201
        ELSE
            GOTO 30
        END IF
30
        INPUT "Is 'a' your variable? (1=yes, 2=no) ", avar5
        IF avar5 = 1 THEN
            GOTO 202
        ELSE
            GOTO 40
        END IF
40
        INPUT "is 'd' your variable? (1=yes, 2=no) ", dvar5
        IF dvar5 = 1 THEN
            GOTO 203
        ELSE
            GOTO 10
        END IF
200
        CALL vff5
        GOTO 10
201
        CALL vof5
        GOTO 10
202
        CALL af5
        GOTO 10
203
        CALL df5
        GOTO 10
    CASE IS >= 4
        CLS
        PRINT "d = Vot + ซatý"
        INPUT "Is your variable 'd'? (1=yes, 2=no) ", dvar4
        IF dvar4 = 1 THEN
            GOTO 300
        ELSE
            GOTO 50
        END IF
50
        INPUT "Is your variable 'Vo'? (1=yes, 2=no) ", vovar4
        IF vovar4 = 1 THEN
            GOTO 301
        ELSE
            GOTO 60
        END IF
60
        INPUT "Is your variable 'a'? (1=yes, 2=no) ", avar4
        IF avar4 = 1 THEN
            GOTO 302
        ELSE
            GOTO 70
        END IF
70
        PRINT "If your variable is 't', then tough beans, do it on your own"
        GOTO 10
300
        CALL df4
        GOTO 10
301
        CALL vof4
        GOTO 10
302
        CALL af4
        GOTO 10
    CASE IS >= 3
        CLS
        PRINT "d = [(Vf + Vo)/2]t"
        INPUT "Is your variable 'd'? (1=yes, 2=no) ", dvar3
        IF dvar3 = 1 THEN
            GOTO 400
        ELSE
            GOTO 80
        END IF
80
        INPUT "Is your variable 'Vf'? (1=yes, 2=no) ", vfvar3
        IF vfvar3 = 1 THEN
            GOTO 401
        ELSE
            GOTO 90
        END IF
90
        INPUT "Is your variable 'Vo'? (1=yes, 2=no) ", vovar3
        IF vovar3 = 1 THEN
            GOTO 402
        ELSE
            GOTO 100
        END IF
100
        INPUT "is your variable 't'? (1=yes, 2=no) ", tvar3
        IF tvar3 = 1 THEN
            GOTO 403
        ELSE
            GOTO 10
        END IF
400
        CALL df3
        GOTO 10
401
        CALL vff3
        GOTO 10
402
        CALL vof3
        GOTO 10
403
        CALL tf3
        GOTO 10
    CASE IS >= 2
        CLS
        PRINT "Vf = Vo + at"
        INPUT "Is your variable 'Vf'? (1=yes, 2=no) ", vfvar2
        IF vfvar2 = 1 THEN
            GOTO 500
        ELSE
            GOTO 110
        END IF
110
        INPUT "Is your variable 'Vo'? (1=yes, 2=no) ", vovar2
        IF vovar2 = 1 THEN
            GOTO 501
        ELSE
            GOTO 120
        END IF
120
        INPUT "Is your variable 'a'? (1=yes, 2=no) ", avar2
        IF avar2 = 1 THEN
            GOTO 502
        ELSE
            GOTO 130
        END IF
130
        INPUT "Is your variable 't'? (1=yes, 2=no) ", tvar2
        IF tvar2 = 1 THEN
            GOTO 503
        ELSE
            GOTO 10
        END IF
500
        CALL vff2
        GOTO 10
501
        CALL vof2
        GOTO 10
502
        CALL af2
        GOTO 10
503
        CALL tf2
        GOTO 10
    CASE IS >= 1
        CLS
        PRINT "Vave = d/t"
        INPUT "Is your variable 'Vave'? (1=yes, 2=no) ", vavevar1
        IF vavevar1 = 1 THEN
            GOTO 600
        ELSE
            GOTO 140
        END IF
140
        INPUT "Is your variable 'd'? (1=yes, 2=no) ", dvar1
        IF dvar1 = 1 THEN
            GOTO 601
        ELSE
            GOTO 150
        END IF
150
        INPUT "Is your variable 't'? (1=yes, 2=no) ", tvar1
        IF tvar1 = 1 THEN
            GOTO 602
        ELSE
            GOTO 10
        END IF
600
        CALL vavef1
        GOTO 10
601
        CALL df1
        GOTO 10
602
        CALL tf1
        GOTO 10
END SELECT

SUB af2
COLOR 9
INPUT "what is the value of Vf? ", vf22
INPUT "what is the value of Vo? ", vo22
INPUT "what is the value of t? ", t22
a22 = ((vf22 - vo22) / t22)
COLOR 14
PRINT "the acceleration is: "; a22; "m/sý"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB af4
COLOR 9
INPUT "what is the value of Vo? ", vo42
INPUT "what is the value of d? ", d42
INPUT "what is the value of t? ", t42
a42 = ((d42 - (vo42 * t42)) / (.5 * (t42 * t42)))
COLOR 14
PRINT "the acceleration is: "; a42; "m/sý"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB af5
COLOR 9
INPUT "what is the value of Vf? ", vf52
INPUT "what is the value of Vo? ", vo52
INPUT "what is the value if d? ", d52
a52 = ((vf52 * vf52 - vo52 * vo52) / (2 * d52))
COLOR 14
PRINT "the acceleration is: "; a52; "m/sý"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB df1
COLOR 9
INPUT "what is the value of Vave? ", vave12
INPUT "what is the value of t? ", t12
d12 = (t12 * vave12)
COLOR 14
PRINT "the distance is: "; d12; "meters"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB df3
COLOR 9
INPUT "what is the value of Vf? ", vf3
INPUT "what is the value of Vo? ", vo3
INPUT "what is the value of t? ", t3
d3 = (((vf3 + vo3) / 2) * t3)
COLOR 14
PRINT "The distance is: "; d3; "meters"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB df4
COLOR 9
INPUT "what is the value of Vo? ", vo4
INPUT "what is the value of t? ", t4
INPUT "what is the value of a? ", a4
d4 = ((vo4 * t) + (.5 * a4 * (t4 * t4)))
COLOR 14
PRINT "the distance is: "; d4; "meters"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB df5
COLOR 9
INPUT "what is the value of Vf? ", vf53
INPUT "what is the value of Vo? ", vo53
INPUT "what is the value of a? ", a53
d53 = ((vf53 * vf53 - vo53 * vo53) / (2 * a53))
COLOR 14
PRINT "the distance is: "; d53; "meters"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB tf1
COLOR 9
INPUT "what is the value of Vave? ", vave13
INPUT "what is the value of d? ", d13
t13 = (d13 / vave13)
COLOR 14
PRINT "the time is: "; t13; "seconds"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB tf2
COLOR 9
INPUT "what is the value of Vf? ", vf23
INPUT "what is the value of Vo? ", vo23
INPUT "what is the value of a? ", a23
t23 = ((vf23 - vo23) / a23)
COLOR 14
PRINT "the time is: "; t23'"seconds"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB tf3
COLOR 9
INPUT "what is the value of Vf? ", vf33
INPUT "what is the value of Vo? ", vo33
INPUT "what is the value of d? ", d33
t33 = ((2 * d33) / (vf33 + vo33))
COLOR 14
PRINT "the time is: "; t33; "seconds"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB vavef1
COLOR 9
INPUT "what is the value of d? ", d1
INPUT "what is the value of t? ", t1
vave1 = (d1 / t1)
COLOR 14
PRINT "the average velocity is: "; vave1; "m/s"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB vff2
COLOR 9
INPUT "what is the value of Vo? ", vo2
INPUT "what is the value of a? ", a2
INPUT "what is the value of t? ", t2
vf2 = (vo2 + (a2 * t2))
COLOR 14
PRINT "the final velocity is: "; vf2; "m/s"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB vff3
COLOR 9
INPUT "what is the value of d? ", d31
INPUT "what is the value of Vo? ", vo31
INPUT "what is the value of t? ", t31
vf31 = (((2 * d31) / t31) - vo31)
COLOR 14
PRINT "the final velocity is: "; vf31; "m/s"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB vff5
COLOR 9
INPUT "What is the value of Vo? ", vo5
INPUT "what is the value of a? ", a5
INPUT "what is the value of d? ", d5
vf5 = SQR(vo5 * vo5 + (2 * (ABS(a5)) * (ABS(d5))))
COLOR 14
PRINT "the final velocity is: "; vf5; "m/s"
PRINT "--Press spacebar to continue--"
SLEEP 1000
END SUB

SUB vof2
COLOR 9
INPUT "what is the value of Vf? ", vf21
INPUT "what is the value of a? ", a21
INPUT "what is the value of t? ", t21
vo21 = (vf21 - (a21 * t21))
COLOR 14
PRINT "the initial velocity is: "; vo21; "m/s"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB vof3
COLOR 9
INPUT "what is the value of d? ", d32
INPUT "what is the value of Vf? ", vf32
INPUT "what is the value of t? ", t32
vo32 = (((2 * d32) / t32) - vf32)
COLOR 14
PRINT "the initial velocity is: "; vo32; "m/s"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB vof4
COLOR 9
INPUT "what is the value of d? ", d41
INPUT "what is the value of a? ", a41
INPUT "what is the value of t? ", t41
vo41 = ((d41 - (.5 * a41 * (t41 * t41))) / t41)
COLOR 14
PRINT "the initial velocity is "; vo41; "m/s"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

SUB vof5
COLOR 9
INPUT "what is the value of Vf? ", vf51
INPUT "what is the value of a? ", a51
INPUT "what is the value of d? ", d51
vo51 = SQR(vf51 * vf51 + (2 * (ABS(a51)) * (ABS(d51))))
COLOR 14
PRINT "the initial velocity is "; vo51; "m/s"
PRINT "--press spacebar to continue--"
SLEEP 1000
END SUB

