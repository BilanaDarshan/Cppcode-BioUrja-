# Cppcode-BioUrja-
Code in cpp for 3rd assesment of biourja

# Dispatch.cpp
This is the main code file,
Algorithm used:
1. first adjust the regional forecast values according to the state forecast value as it is the most accurate one
2. Then use these adjusted values to adjust the individual values region wise
3. After adjustment we check if the values now exceed max capacity
4. If the exceed the max capacity, set those individual plants to max capacity and then distribute the difference to other individual plants of the same zone
5. In both adjustments the ratio of each plant supply to the total zonal supply is kept nearly same as asked.
6. Ratio of each zonal supply to the state supply is also nearly the same as asked.

#input.csv 
the input file used to fetch data

#output1.csv 
The values of individual plants after regional wise adjustments

#output2.csv 
The values of individual plants after adjusting so the max capacity is not crossed.


