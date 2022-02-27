import numpy as np
import pandas as pd
import random
import matplotlib.pyplot as plt

# Add Fiber
newnano = np.loadtxt('newnano.txt')
newnano = pd.DataFrame(newnano)
fiberNew = np.zeros((len(newnano),7))
fiberNew = pd.DataFrame(fiberNew)
fiberNew[0] = newnano[0]
fiberNew[1] = newnano[1]
fiberNew[2] = newnano[1]+ 4
fiberNew[4] = newnano[2] + 20
fiberNew[5] = newnano[3] + 20
fiberNew[6] = newnano[4] + 0
fiberNew = pd.DataFrame(fiberNew)

# Add Cementpaste
cementZero1 = np.loadtxt('Hamid.data')
cementZero1 = pd.DataFrame(cementZero1)
cementZero1[3] = cementZero1[3] + 3
cementZero2 = np.loadtxt('Hamid.data')
cementZero2 = pd.DataFrame(cementZero2)
cementZero2[3] = cementZero2[3] + 21
cementZero3 = np.loadtxt('Hamid.data')
cementZero3 = pd.DataFrame(cementZero3)
cementZero3[4] = cementZero3[4] + 15
cementZero4 = np.loadtxt('Hamid.data')
cementZero4 = pd.DataFrame(cementZero4)
cementZero4[3] = cementZero4[3] + 25
cementZero4[4] = cementZero4[4] + 17
cementZero5 = np.loadtxt('Hamid.data')
cementZero5 = pd.DataFrame(cementZero5)
cementZero5[3] = cementZero5[3] + 3
cementZero5[4] = cementZero5[4] + 32
cementZero6 = np.loadtxt('Hamid.data')
cementZero6 = pd.DataFrame(cementZero6)
cementZero6[3] = cementZero6[3] + 21
cementZero6[4] = cementZero6[4] + 32
cement = np.array([])
cement = pd.DataFrame(cement)
cement = cement.append(cementZero1, ignore_index=True)
cement = cement.append(cementZero2, ignore_index=True)
cement = cement.append(cementZero3, ignore_index=True)
cement = cement.append(cementZero4, ignore_index=True)
cement = cement.append(cementZero5, ignore_index=True)
cement = cement.append(cementZero6, ignore_index=True)
np.savetxt('layer1_cement.txt', cement)

cementz = np.loadtxt('layer1_cement.txt')
cementz = pd.DataFrame(cementz)
cementz[5] = cementz[5] + 24.67
cement = cement.append(cementz, ignore_index=True)
np.savetxt('full_cement.txt', cement)

# Add Gravel
gravelZero = np.loadtxt('rigidCarbon_MillisilW12.txt')
gravelZero = pd.DataFrame(gravelZero)
gravelNew = gravelZero
stackGravel = np.array([])
stackGravel = pd.DataFrame(stackGravel)

for x in range(2140):
    dx = random.random() * (50-1.15)
    dy = random.random() * (20-1.15*2)
    dz = random.random() * (100-1.15)
    gravelNew[4] = gravelZero[4]+dx
    gravelNew[5] = gravelZero[5]+dy
    gravelNew[6] = gravelZero[6]+dz
    gravelNew[1] = x+2
    stackGravel = stackGravel.append(gravelNew, ignore_index=True)
    gravelZero = np.loadtxt('rigidCarbon_MillisilW12.txt')
    gravelZero = pd.DataFrame(gravelZero)

print(stackGravel.shape)

material = np.loadtxt('full_cement.txt')
material = pd.DataFrame(material)
materialnew = np.zeros((len(material),7))
materialnew = pd.DataFrame(materialnew)
materialnew[0] = material[0]
materialnew[2] = material[1]
materialnew[3] = material[2]
materialnew[4] = material[3]
materialnew[5] = material[4]
materialnew[6] = material[5]
materialnew = pd.DataFrame(materialnew)
materialnew = materialnew.append(fiberNew, ignore_index=True)
materialnew[0] = range(1, 2109)
newmaterial = np.array(materialnew)

with open('material.data', 'w') as data:
    data.write('# Input file for Test-Specimen\n\n')
    data.write(f'{int(newmaterial.shape[0])}'+' atoms\n')
    data.write('5 atom types\n\n')

    data.write('0   41 xlo xhi\n')
    data.write('0   46 ylo yhi\n')
    data.write('0   46 zlo zhi\n\n')

    data.write('Masses\n\n')
    data.write('1   40.080	#Ca\n')
    data.write('2   28.090	#Si\n')
    data.write('3   16.000	#O\n')
    data.write('4   1.000	#H\n')
    data.write('5   12.010700	# Mass of C\n\n')

    data.write('Atoms\n\n')

    for i, a_p in enumerate(newmaterial):
        data.write(f'{int(a_p[0])} {int(a_p[1])} {int(a_p[2])} {int(a_p[3])} {(a_p[4])} {(a_p[5])} {(a_p[6])}\n')

with open('config_Model.data', 'w') as data:
    data.write('# Configuration File to perform equilibrium\n')
    data.write('units		metal	# Definition of used Units\n')
    data.write('dimension	3	# Definition of used dimensions\n')
    data.write('processors	* * *	# Allowance to use the processors the simulations thinks to need\n')
    data.write('boundary	p p p	# Definition of boundary conditions\n\n')
    data.write('pair_style hybrid/overlay buck 3.0 sw coul/long 3.0 lj/cut 3.0 airebo 3.0\n')
    data.write('kspace_style ewald 0.0001 #how to calculate long-range coulomb interaction\n')

    data.write('# Definition of Attributes for the Atoms in the data-file, reading data\n')
    data.write('atom_style  full        # molecular+charge\n')
    data.write('read_data   material.data   # Read specific data-file\n\n')

    data.write('# interaction styles (Here to add)\n')
    data.write('pair_coeff 1 1 buck 4369.01 0.29 0.0	#for buck, A and ro and C\n')
    data.write('pair_coeff 2 2 buck 1171.52 0.29 0.0\n')
    data.write('pair_coeff 3 3 buck 452.5051 0.29 0.0\n')
    data.write('pair_coeff 4 4 buck 21.228 0.35 0.0\n')
    data.write('pair_coeff 1 2 buck 1382.4811 0.29 0.0\n')
    data.write('pair_coeff 1 3 buck 3557.62 0.29 0.0\n')
    data.write('pair_coeff 2 3 buck 1848.7174 0.29 0.0\n')
    data.write('pair_coeff 3 4 buck 248.6324 0.29 0.0\n')
    data.write('pair_coeff 2 4 buck 430.6566 0.29 0.0\n')
    data.write('pair_coeff 5 5 lj/cut 0.0537	2.8	# C (27 K = 0.0537 kcal/mol, energy units; distance units)\n')
    data.write('pair_coeff 1 5 lj/cut 0.0000228325 4.480\n')
    data.write('pair_coeff 2 5 lj/cut 0.0000138095 3.351\n')
    data.write('pair_coeff 3 5 lj/cut 0.00401324 3.282\n')
    data.write('pair_coeff * * airebo CH.airebo NULL NULL NULL H C\n\n')
    data.write('pair_coeff * * coul/long\n')
    data.write('pair_coeff * * sw potential.sw NULL Si O NULL NULL\n')

    data.write('velocity all create 100.0 53244 dist gaussian mom no rot no\n')
    
    data.write('# Definition of the different groups\n')
    data.write('group clump'+f'{int(1)}'+' id <> '+f'{int(1728)}'+' '+f'{int(2108)}\n')
    
    data.write('\n')
    data.write('\n')

    data.write('# Fix assigned to the groups\n')
    data.write('fix ' + f'{int(111)}' + ' clump' + f'{int(1)}' + ' rigid/nve molecule\n')
        

    data.write('\n')
    data.write('# Performing the simulation (Here to add)\n')
    data.write('neighbor 2.0 bin\n')
    data.write('neigh_modify every 1 delay 0 check yes\n')

    data.write('#equilibrate\n')
    data.write('min_style cg\n')
    data.write('thermo 5\n')
    data.write('minimize 1.0e-4 1.0e-6 120 1000\n')

    data.write('# 300-NPT\n')
    data.write('velocity all create 300.0 5812775\n')
    data.write('# fix 1 all npt 300.0 300.0 0.001 xyz 0.0 0.0 1.0 drag 1.0\n')
    data.write('fix 1 all npt temp 300.0 300.0 0.001 aniso 0.0 0.0 0.005 drag 2.0\n')
    data.write('thermo 1000\n')
    data.write('thermo_style custom step temp etotal press vol\n')
    data.write('thermo_modify flush yes\n')
    data.write('dump 2 all custom 1000 equlibration.csh id type x y z\n')
    data.write('timestep 0.0001\n')
    data.write('run 100000\n')
    data.write('unfix 1\n')