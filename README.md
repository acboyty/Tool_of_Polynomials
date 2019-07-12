# Tool_of_Polynomials

It is a mini program with which you can handle polynomial factorization, addition, multiplication, etc.

Java servlet is the bridge which links mini program and algorithm. We use Runtime.getRuntime().exec() to let C++ algorithm serve for JS mini program.

The polynomial degree of factorization should be <= 10, calculation <= 1000. Actually our algorithm of division support the degree of 10000, addition & subtraction & multiplication support 1000000. But considering Internet transportation, we set the limit 1000.
