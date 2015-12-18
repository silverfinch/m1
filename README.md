# Midterm 1
  Dennis Scheglov, Joshua Pelton
  
  This project involved the Leibniz and Bailey-Borwein-Plouffe series for the value of pi.
  The goal was to see how precise each series gets as one increases the value of index n in relation to the actual value
  of pi, defined as a constant in the program. Iterations ceased when the absolute error dropped below 10^-6.
  Another goal was to measure the exact time per function call for two functions, one corresponding to Leibniz and the 
  other to BBP, as well as the ratio between the two.

## Results
   Leibniz took 6.794813e-2 seconds per call.
   BBP took 3.893282e-8 seconds per call.
   Leibniz converged to pi 1.745266e06 times more slowly than BBP.
