#!/usr/bin/env python3
import serial
import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    print("aici")
    plt.close('all')
    plt.figure();
    plt.ion();
    plt.show();
    print("aici")
    data = np.array([]);
    data1 = np.array([]);
    i = 0
    ser = serial.Serial('/dev/serial0', 9600, timeout=1)
    ser.flush()
    nextis =0
    while i <= 200:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            if line == "H" :
                nextis = 1
            elif nextis == 0 :
                tmp = float(line)
                data = np.append(data,tmp)
            else:
                nextis = 0
                hm = float(line)
                data1= np.append(data1, hm)
            print(tmp)
            plt.cla()
            plt.plot(data, label="T")
            plt.plot(data1, label="H")
            plt.pause(0.01)
            i= i+1
    plt.savefig('test.svg')
    ser.close()
        
