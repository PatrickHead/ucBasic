print "naked line"
10 gosub 1000
20 print "Hello, world"
25 print "This is ""special"""
print "Input loop parameters (start end): ":
input i,l
rem let I = 1
30 print I, " ", I * 2
LET I = I + 1
if I <= L then goto 30
poke 1000, 31
let a = peek(1000)
print "a=",a
goto 60000
1000 print "in a gosub"
return
60000 print "end of program"
rem Just a remark
