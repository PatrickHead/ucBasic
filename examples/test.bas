5 gosub 1000
10 print "Hello, world"
15 print "This is ""special"""
20 print "Input loop parameters (start end): ":
21 input i,l
25 rem let I = 1
30 print I, " ", I * 2
40 LET I = I + 1
50 if I <= L then goto 30
60 poke 1000, 31
70 let a = peek(1000)
80 print "a=",a
100 goto 60000
1000 print "in a gosub"
1010 return
60000 print "end of program"
60010 rem Just a remark
