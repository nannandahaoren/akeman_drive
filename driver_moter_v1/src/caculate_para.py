import numpy as np
import math
th33 = [-30,-25,-20,-10,-5,0,5,10,15,20,25,30,35,40,45]
th11 = [31.875815,33.0938372,34.41681,37.38114,39.02267,40.76926,42.61894,44.56874,46.61476,48.75212,50.97502,53.27681,55.65,58.08652,60.57737]

th333 = [45,50,55,60,65,70,75,80,85,90,94,89,88,72,95,93,100,101,102]
th111 = [60.57737,63.11307,65.68346,68.27771,70.88426,73.49082,76.08394,78.64909,81.17028,83.62963,85.53916,83.14364,82.65454,74.53046, 86.00703,85.06731,88.27947,88.71910,89.15325]
# print(f)
# th3 = [0,5]
# th1 = [27.980821,29.909165]
th3333 = [95,96,97,98,99,100,101,102,133,132,120,130,114,103,105,108,115,117,122,123,126,135,136]
th1111 = [86.00702787,86.470706,86.93,87.38470,87.83459,88.27947,88.719097,89.15324608,98.16922191,98.07793,95.71429,97.84037,93.83997,89.58168,
          90.42039,91.62911,94.17789,94.82428,96.24955,96.498366,97.16356,98.29330,98.32462]


th3 = th3333
th1 = th1111
# f = [0.001]*len(th1)
# rad_th3 = [math.radians(i) for i in th3]
# cos_th3 = [math.cos(i) for i in rad_th3]
# rad_th1 = [math.radians(i) for i in th1]
# sin_th1 = [math.sin(i) for i in rad_th1]
# th1_2 = [i*i for i in rad_th1]
# th1_3 = [i*i*i for i in rad_th1]
# th1_4 = [i*i for i in th1_2]
# th1_5 = [i*i*i*i*i for i in rad_th1]

def caculate_para(th1):
    # rad_th1 = [math.radians(i) for i in th1]
    th1_2 = [i*i for i in th1]
    th1_3 = [i*i*i for i in th1]
    # th1_4 = [i*i*i*i for i in th1]
    # th1_5 = [i*i*i*i*i for i in th1]
    # th1_6 = [i*i*i*i*i*i for i in th1]
    return th1_2,th1_3

y = np.ones((len(th3),1))
# yy = list()
# print(y.shape)
th1_2,th1_3= caculate_para(th1)
XT = np.mat([th1,th1_2,th1_3,th3])
X = XT.T

# print(X) 
# print(XT)
para = np.linalg.inv(XT*X)*XT*y

print(para)

valid = th1

th1_2,th1_3= caculate_para(valid)


# a0 = [para[0,0]*i for i in th1]
# a1 = [para[1,0]*i for i in th1_2]
# a2 = [para[2,0]*i for i in th1_3]
# a3 = [para[3,0]*i for i in th1_4]
# a4 = [para[4,0]*i for i in th1_5]
# a5 = [para[5,0]*i for i in th1_6]


a0 = [para[0,0]*i for i in valid]
a1 = [para[1,0]*i for i in th1_2]
a2 = [para[2,0]*i for i in th1_3]
# a3 = [para[3,0]*i for i in th1_4]

# a3 = [para[3,0]*i for i in th1_4]

# a4 = [para[4,0]*i for i in th1_5]
# a5 = [para[5,0]*i for i in th1_6]

# a3 = [para[3,0]*i for i in cos_th1]
# a4 = [para[4,0]*i for i in s_c_th1]
# a5 = [para[5,0]*i for i in s_s_th1]
# a6 = [para[6,0]*i for i in c_c_th1]



# sum = [(a+b+c+d+e+f) for a,b,c,d,e,f in zip(a0,a1,a2,a3,a4,a5) ]
# sum = [(a+b+c+e) for a,b,c,e in zip(a0,a1,a2,a3) ]
sum = [(a+b+c) for a,b,c in zip(a0,a1,a2) ]

a = [1.0-i for i in sum]

b = [i/para[3,0] for i in a]
print(b)
# print("para[0,0]: ",para[0,0])
# print("para[1,0]: ",para[1,0])

# th3 =[math.degrees(i) for i in b]

# print(th3)




# T = 0.29
# L = 0.485

# Maxa =0.6
# MaxR1 = L/math.tan(Maxa)
# # MaxR0 = L/tan(Max_sigma)
# # MaxR0 = MaxR1 + 0.5*T       
# Max_sigma = math.atan(L/(MaxR1 + 0.5*T ))
# print(math.degrees(Max_sigma))

# R0 = L/math.tan(abs(Max_sigma))
# R1 = R0 - 0.5*T
# R2 = R0 + 0.5*T
# leftangle = math.atan(L/R1)
# rightangle = math.atan(L/R2)
# print(math.degrees(leftangle),math.degrees(rightangle))